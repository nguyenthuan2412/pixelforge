/**
 * PixelForge native core (libvips).
 *
 *  - Lazy pipeline: PHP methods only record steps into an ImageBox. The libvips graph is
 *    built and streamed (tile by tile) only when an output is requested.
 *  - Shrink-on-load identical to Node sharp (fastShrinkOnLoad): JPEG is decoded with
 *    shrink=2/4/8, WebP/SVG/PDF at scale, then a single vips_resize with the chosen kernel.
 *  - Sequential access unless a step really needs random access; when it does and the
 *    image was shrunk on load, only the small resized image is materialised.
 *  - Buffer and raw inputs keep a reference to the PHP zend_string (zero copy); encoded
 *    output is copied exactly once into the returned PHP string.
 *  - Automatic per-pipeline thread count (1 thread for small working sets, all allowed
 *    CPUs for large ones), respecting cgroup CPU quotas.
 *  - libvips operation cache disabled by default (lowest RSS for php-fpm).
 */
#include <phpx.h>
// libvips' C++ classes (VError, VImage...) must keep default visibility even though the
// extension is built with -fvisibility=hidden: otherwise typeinfo differs between this .so
// and libvips-cpp, and `catch (const vips::VError &)` silently misses on macOS (libc++).
#pragma GCC visibility push(default)
#include <vips/vips8>
#pragma GCC visibility pop
#if defined(__GLIBC__)
#include <malloc.h>
#endif

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace php;
using vips::VError;
using vips::VImage;

namespace pixelforge {

static const char *kExceptionClass = "PixelForge\\PixelForgeException";

// ================================================================ init / threads
static bool g_inited = false;
static int g_userThreads = 0;  // 0 = automatic
static int g_maxThreads = 1;
static bool g_trim = true;  // return freed memory to the OS after each output (glibc)
static double g_autoThreshold = 3.0e6;  // pixels: below this a single thread is fastest

static void silentLog(const gchar *, GLogLevelFlags, const gchar *, gpointer) {}

static int cgroupCpus() {
    long quota = -1, period = 0;
    if (FILE *f = fopen("/sys/fs/cgroup/cpu.max", "r")) {
        char q[32] = {0};
        if (fscanf(f, "%31s %ld", q, &period) == 2 && strcmp(q, "max") != 0) quota = atol(q);
        fclose(f);
    } else if (FILE *f1 = fopen("/sys/fs/cgroup/cpu/cpu.cfs_quota_us", "r")) {
        if (fscanf(f1, "%ld", &quota) != 1) quota = -1;
        fclose(f1);
        if (FILE *f2 = fopen("/sys/fs/cgroup/cpu/cpu.cfs_period_us", "r")) {
            if (fscanf(f2, "%ld", &period) != 1) period = 0;
            fclose(f2);
        }
    }
    int cores = (int) g_get_num_processors();
    if (quota > 0 && period > 0) return std::max(1, std::min(cores, (int) ((quota + period - 1) / period)));
    return cores;
}

static void ensureInit() {
    if (g_inited) return;
    if (VIPS_INIT("pixelforge")) throw VError("libvips initialisation failed");
    vips_cache_set_max(0);
    vips_cache_set_max_mem(0);
    vips_cache_set_max_files(0);
    if (!getenv("PIXELFORGE_VIPS_WARNINGS")) {
        g_log_set_handler("VIPS", (GLogLevelFlags) (G_LOG_LEVEL_WARNING | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION),
                          silentLog, nullptr);
    }
    g_maxThreads = cgroupCpus();
    if (const char *c = getenv("PIXELFORGE_CONCURRENCY")) g_userThreads = std::max(0, atoi(c));
    if (const char *t = getenv("PIXELFORGE_AUTO_THREADS_MP")) g_autoThreshold = atof(t) * 1e6;
    if (const char *t = getenv("PIXELFORGE_TRIM")) g_trim = atoi(t) != 0;
    vips_concurrency_set(g_userThreads > 0 ? g_userThreads : g_maxThreads);
    g_inited = true;
}

/** glibc keeps freed memory in per-thread arenas; hand it back so long-lived workers stay small. */
static void releaseMemory() {
#if defined(__GLIBC__)
    if (g_trim) malloc_trim(0);
#endif
}

struct TrimGuard {
    ~TrimGuard() { releaseMemory(); }
};

static void chooseThreads(double workPixels) {
    int n = g_userThreads > 0 ? g_userThreads : (workPixels <= g_autoThreshold ? 1 : g_maxThreads);
    if (vips_concurrency_get() != n) vips_concurrency_set(n);
}

// ================================================================ helpers
static std::vector<double> parseList(const std::string &s) {
    std::vector<double> out;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ',')) {
        if (item.empty()) continue;
        size_t used = 0;
        double v = 0;
        try {
            v = std::stod(item, &used);
        } catch (const std::exception &) {
            used = 0;
        }
        if (used != item.size()) throw VError("invalid number: " + item);
        out.push_back(v);
    }
    return out;
}

static std::string lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
    return s;
}

static std::string str(const String &s) {
    return std::string(s.data(), s.length());
}

static bool is16bit(VipsInterpretation i) {
    return i == VIPS_INTERPRETATION_RGB16 || i == VIPS_INTERPRETATION_GREY16;
}

static double maxAlpha(const VImage &img) {
    return is16bit(img.interpretation()) ? 65535.0 : 255.0;
}

/** Background RGBA (0-255) adapted to the band count / depth of `img`. */
static std::vector<double> adaptBackground(const VImage &img, const std::vector<double> &rgba) {
    double scale = is16bit(img.interpretation()) ? 256.0 : 1.0;
    std::vector<double> bg;
    bool alpha = img.has_alpha();
    int colour = alpha ? img.bands() - 1 : img.bands();
    if (colour <= 2) {
        bg.push_back(scale * (0.2126 * rgba[0] + 0.7152 * rgba[1] + 0.0722 * rgba[2]));
        for (int i = 1; i < colour; i++) bg.push_back(bg[0]);
    } else {
        for (int i = 0; i < colour; i++) bg.push_back(scale * rgba[std::min(i, 2)]);
    }
    if (alpha) bg.push_back(scale * rgba[3]);
    return bg;
}

static VImage withAlphaFor(VImage img, const std::vector<double> &rgba) {
    if (rgba.size() > 3 && rgba[3] < 255 && !img.has_alpha()) img = img.bandjoin_const({maxAlpha(img)});
    return img;
}

static const std::string &oneOf(const std::string &v, std::initializer_list<const char *> allowed, const char *what);

static const std::string &validGravity(const std::string &g, bool allowSmart) {
    if (allowSmart && (g == "entropy" || g == "attention")) return g;
    return oneOf(g, {"centre", "north", "northeast", "east", "southeast", "south", "southwest", "west", "northwest"},
                 allowSmart ? "position" : "gravity");
}

/** Gravity -> offset of an inner (w,h) box within an outer (W,H) box. */
static void gravityOffset(const std::string &g, int W, int H, int w, int h, int &x, int &y) {
    x = (W - w) / 2;
    y = (H - h) / 2;
    if (g.find("west") != std::string::npos) x = 0;
    if (g.find("east") != std::string::npos) x = W - w;
    if (g.rfind("north", 0) == 0) y = 0;
    if (g.rfind("south", 0) == 0) y = H - h;
}

static VipsInterpretation parseSpace(const std::string &s) {
    std::string v = lower(s);
    if (v == "srgb") return VIPS_INTERPRETATION_sRGB;
    if (v == "rgb") return VIPS_INTERPRETATION_RGB;
    if (v == "rgb16") return VIPS_INTERPRETATION_RGB16;
    if (v == "b-w" || v == "bw" || v == "grey" || v == "gray") return VIPS_INTERPRETATION_B_W;
    if (v == "grey16" || v == "gray16") return VIPS_INTERPRETATION_GREY16;
    if (v == "cmyk") return VIPS_INTERPRETATION_CMYK;
    if (v == "lab") return VIPS_INTERPRETATION_LAB;
    if (v == "labs") return VIPS_INTERPRETATION_LABS;
    if (v == "lch") return VIPS_INTERPRETATION_LCH;
    if (v == "cmc") return VIPS_INTERPRETATION_CMC;
    if (v == "xyz") return VIPS_INTERPRETATION_XYZ;
    if (v == "yxy") return VIPS_INTERPRETATION_YXY;
    if (v == "hsv") return VIPS_INTERPRETATION_HSV;
    if (v == "scrgb") return VIPS_INTERPRETATION_scRGB;
    if (v == "multiband") return VIPS_INTERPRETATION_MULTIBAND;
    throw VError("Unsupported colourspace: " + s);
}

static const char *nick(GType type, int value, const char *def) {
    const char *n = vips_enum_nick(type, value);
    return n ? n : def;
}

static int enumFromNick(GType type, const std::string &s, const char *what) {
    int v = vips_enum_from_nick("pixelforge", type, s.c_str());
    if (v < 0) {
        vips_error_clear();
        throw VError(std::string("Invalid ") + what + ": " + s);
    }
    return v;
}

static int parseFailOn(const std::string &s) {
    std::string v = lower(s);
    if (v == "none") return VIPS_FAIL_ON_NONE;
    if (v == "truncated") return VIPS_FAIL_ON_TRUNCATED;
    if (v == "error") return VIPS_FAIL_ON_ERROR;
    if (v == "warning") return VIPS_FAIL_ON_WARNING;
    throw VError("Invalid failOn: " + s + " (expected none, truncated, error or warning)");
}

/** Throws unless `v` is one of `allowed`. */
static const std::string &oneOf(const std::string &v, std::initializer_list<const char *> allowed, const char *what) {
    std::string list;
    for (const char *a : allowed) {
        if (v == a) return v;
        list += list.empty() ? a : std::string(", ") + a;
    }
    throw VError(std::string("Invalid ") + what + ": " + v + " (expected " + list + ")");
}

static VipsKernel parseKernel(const std::string &k) {
    std::string v = lower(k);
    if (v == "nearest") return VIPS_KERNEL_NEAREST;
    if (v == "linear") return VIPS_KERNEL_LINEAR;
    if (v == "cubic") return VIPS_KERNEL_CUBIC;
    if (v == "mitchell") return VIPS_KERNEL_MITCHELL;
    if (v == "lanczos2") return VIPS_KERNEL_LANCZOS2;
    if (v == "lanczos3") return VIPS_KERNEL_LANCZOS3;
#if VIPS_MAJOR_VERSION > 8 || (VIPS_MAJOR_VERSION == 8 && VIPS_MINOR_VERSION >= 17)
    if (v == "mks2013") return VIPS_KERNEL_MKS2013;
    if (v == "mks2021") return VIPS_KERNEL_MKS2021;
#else
    if (v == "mks2013" || v == "mks2021") throw VError("kernel " + v + " requires libvips >= 8.17");
#endif
    throw VError("Invalid kernel: " + k + " (expected nearest, linear, cubic, mitchell, lanczos2, lanczos3, mks2013, mks2021)");
}

static VImage castLike(const VImage &out, VipsBandFormat fmt) {
    return out.format() == fmt ? out : out.cast(fmt);
}

/** Split alpha off, apply fn to colour bands, re-join alpha. */
static VImage onColour(const VImage &img, const std::function<VImage(VImage)> &fn) {
    if (!img.has_alpha()) return fn(img);
    VImage colour = img.extract_band(0, VImage::option()->set("n", img.bands() - 1));
    VImage alpha = img.extract_band(img.bands() - 1);
    return fn(colour).bandjoin(alpha);
}

static VImage removeAlpha(const VImage &img) {
    return img.has_alpha() ? img.extract_band(0, VImage::option()->set("n", img.bands() - 1)) : img;
}

// ---------------------------------------------------------------- multi-page (animated) helpers
static int pageHeight(const VImage &img) {
    int ph = vips_image_get_page_height(img.get_image());
    return ph > 0 && ph < img.height() && img.height() % ph == 0 ? ph : img.height();
}

static int nPages(const VImage &img) {
    return img.height() / pageHeight(img);
}

static VImage setPageHeight(VImage img, int ph) {
    VImage out = img.copy();
    out.set(VIPS_META_PAGE_HEIGHT, ph);
    return out;
}

/** Apply a geometric operation to every frame of an animated image independently. */
static VImage perPage(const VImage &img, const std::function<VImage(VImage)> &fn) {
    int n = nPages(img);
    if (n <= 1) return fn(img);
    int ph = pageHeight(img);
    std::vector<VImage> frames;
    frames.reserve(n);
    for (int i = 0; i < n; i++) frames.push_back(fn(img.extract_area(0, i * ph, img.width(), ph)));
    VImage out = VImage::arrayjoin(frames, VImage::option()->set("across", 1));
    return setPageHeight(out, frames[0].height());
}

// ================================================================ model
struct HeaderInfo {
    bool ok = false;
    std::string loader;
    int width = 0, height = 0, pageH = 0, pages = 1, orientation = 1;
};

class ImageBox;

struct Source {
    enum Kind { File, Buffer, Create, Raw, Text, Join } kind = File;
    std::string path;
    String buf;  // zero-copy reference to the PHP string (Buffer / Raw)
    // load options
    int failOn = VIPS_FAIL_ON_WARNING;
    long long limitPixels = 268402689;  // 0x3FFF * 0x3FFF, same as sharp
    bool autoOrient = false;
    int pages = 1, page = 0;  // pages = -1 -> all (animated)
    double density = 0;       // svg/pdf DPI (0 = loader default)
    bool unlimited = false;
    bool ignoreIcc = false;
    // create
    int cw = 0, ch = 0, cbands = 3;
    std::vector<double> cbg;
    std::string noise;  // "" or "gaussian"
    double noiseMean = 128, noiseSigma = 30;
    // raw
    int rw = 0, rh = 0, rbands = 3;
    VipsBandFormat rformat = VIPS_FORMAT_UCHAR;
    bool rpremultiplied = false;
    // text
    std::string text, font, fontfile, align = "left";
    int tw = 0, th = 0, dpi = 0, spacing = 0;
    bool justify = false, rgba = false;
    std::string wrap = "word";
    // join
    std::vector<std::shared_ptr<ImageBox>> inputs;
    bool joinAnimated = false;
    int across = 1, shim = 0;
    std::vector<double> joinBg{0, 0, 0, 255};
    std::string halign = "low", valign = "low";

    mutable HeaderInfo header;
};

struct ResizeSpec {
    int width = 0, height = 0;
    std::string fit = "cover";
    std::string position = "centre";
    std::vector<double> background{0, 0, 0, 255};
    bool withoutEnlargement = false;
    bool withoutReduction = false;
    VipsKernel kernel = VIPS_KERNEL_LANCZOS3;
    bool fastShrinkOnLoad = true;
};

enum class StepKind { Generic, Resize, AutoOrient };

struct Step {
    StepKind kind = StepKind::Generic;
    bool random = false;
    std::function<VImage(VImage)> fn;
    ResizeSpec rs;
};

struct OutSpec {
    std::string format;
    int quality = -1;
    bool lossless = false;
    int effort = -1;
    bool progressive = false;
    std::string chroma;
    bool mozjpeg = false;
    bool optimizeCoding = true;
    int compressionLevel = 6;
    bool palette = false;
    int colours = 256;
    double dither = 1.0;
    bool adaptiveFiltering = false;
    int nearLossless = -1;
    bool smartSubsample = false;
    int alphaQuality = 100;
    int bitdepth = 8;
    std::string compression;
    std::string predictor;
    bool tile = false;
    int tileWidth = 256, tileHeight = 256;
    bool pyramid = false;
    int loop = -1;               // animated: -1 = keep input
    std::vector<int> delay;      // animated: per-frame ms (1 value = all frames)
    bool minSize = false, mixed = false;
    double interframeMaxError = 0, interpaletteMaxError = 3;
    bool reuse = false;
};

struct TileSpec {
    bool enabled = false;
    int size = 256, overlap = 0, angle = 0;
    std::string layout = "dz", container = "fs", depth, basename, id;
    bool skipBlanks = false, centre = false;
    std::vector<double> background{255, 255, 255, 255};
};

class ImageBox : public Box {
  public:
    std::shared_ptr<Source> src;
    std::vector<Step> steps;
    OutSpec out;
    TileSpec tile;
    int keep = VIPS_FOREIGN_KEEP_NONE;
    std::string iccProfile;                       // withIccProfile
    std::vector<std::pair<std::string, std::string>> exif;  // withExif fields
    bool exifMerge = true;
    double timeoutSeconds = 0;
};

// ================================================================ loading
static bool hasArgument(const std::string &op, const char *name) {
    static std::map<std::string, bool> cache;
    std::string key = op + "/" + name;
    auto it = cache.find(key);
    if (it != cache.end()) return it->second;
    bool found = false;
    if (VipsOperation *o = vips_operation_new(op.c_str())) {
        GParamSpec *pspec;
        VipsArgumentClass *ac;
        VipsArgumentInstance *ai;
        found = vips_object_get_argument(VIPS_OBJECT(o), name, &pspec, &ac, &ai) == 0;
        g_object_unref(o);
    }
    vips_error_clear();
    cache[key] = found;
    return found;
}

static std::string findLoader(const Source &s) {
    const char *l = s.kind == Source::File ? vips_foreign_find_load(s.path.c_str())
                                           : vips_foreign_find_load_buffer(s.buf.data(), s.buf.length());
    if (!l) {
        vips_error_clear();
        if (s.kind == Source::File) {
            if (!g_file_test(s.path.c_str(), G_FILE_TEST_EXISTS)) throw VError("Input file is missing: " + s.path);
            throw VError("Input file contains unsupported image format: " + s.path);
        }
        throw VError("Input buffer contains unsupported image format");
    }
    // class name (e.g. VipsForeignLoadJpegFile) -> operation nickname (jpegload)
    const char *nickname = vips_nickname_find(g_type_from_name(l));
    return nickname ? nickname : l;
}

static vips::VOption *loadOptions(const Source &s, const std::string &loader, bool random) {
    auto o = VImage::option()
                 ->set("access", (int) (random ? VIPS_ACCESS_RANDOM : VIPS_ACCESS_SEQUENTIAL))
                 ->set("fail_on", s.failOn);
    if (hasArgument(loader, "n") && s.pages != 1) o->set("n", s.pages);
    if (hasArgument(loader, "page") && s.page > 0) o->set("page", s.page);
    if (s.density > 0 && hasArgument(loader, "dpi")) o->set("dpi", s.density);
    if (s.unlimited && hasArgument(loader, "unlimited")) o->set("unlimited", true);
    return o;
}

static VImage openWith(const Source &s, const std::string &loader, vips::VOption *o) {
    if (s.kind == Source::File) {
        o->set("filename", s.path.c_str());
    } else {
        VipsBlob *blob = vips_blob_new(nullptr, s.buf.data(), s.buf.length());
        o->set("buffer", blob);
        vips_area_unref(VIPS_AREA(blob));  // the option holds its own ref
    }
    VImage out;
    o->set("out", &out);
    VImage::call(loader.c_str(), o);
    return out;
}

static const HeaderInfo &header(const Source &s) {
    if (!s.header.ok) {
        std::string loader = findLoader(s);
        VImage img = openWith(s, loader, loadOptions(s, loader, false));
        HeaderInfo &h = s.header;
        h.loader = loader;
        h.width = img.width();
        h.height = img.height();
        h.pageH = pageHeight(img);
        h.pages = img.get_typeof(VIPS_META_N_PAGES) ? img.get_int(VIPS_META_N_PAGES) : 1;
        h.orientation = img.get_typeof(VIPS_META_ORIENTATION) ? img.get_int(VIPS_META_ORIENTATION) : 1;
        h.ok = true;
        if (s.limitPixels > 0 && (long long) h.width * h.pageH > s.limitPixels)
            throw VError("Input image exceeds pixel limit");
    }
    return s.header;
}

static VImage run(const ImageBox &b);

static VImage loadFile(const Source &s, bool random, const std::function<void(vips::VOption *)> &extra = nullptr) {
    const HeaderInfo &h = header(s);
    vips::VOption *o = loadOptions(s, h.loader, random);
    if (extra) extra(o);
    return openWith(s, h.loader, o);
}

static VImage loadOtherUnchecked(const Source &s);

static VImage loadOther(const Source &s) {
    VImage img = loadOtherUnchecked(s);
    if (s.limitPixels > 0 && (long long) img.width() * pageHeight(img) > s.limitPixels)
        throw VError("Input image exceeds pixel limit");
    return img;
}

static VImage loadOtherUnchecked(const Source &s) {
    switch (s.kind) {
        case Source::Create: {
            if (s.limitPixels > 0 && (long long) s.cw * s.ch > s.limitPixels) throw VError("Input image exceeds pixel limit");
            VImage img;
            if (s.noise == "gaussian") {
                std::vector<VImage> bands;
                for (int i = 0; i < s.cbands; i++)
                    bands.push_back(VImage::gaussnoise(s.cw, s.ch, VImage::option()->set("mean", s.noiseMean)->set(
                                                                       "sigma", s.noiseSigma)));
                img = VImage::bandjoin(bands).cast(VIPS_FORMAT_UCHAR);
            } else {
                std::vector<double> bg(s.cbg.begin(), s.cbg.begin() + std::min<size_t>(s.cbands, s.cbg.size()));
                if (s.cbands <= 2) {
                    double l = 0.2126 * s.cbg[0] + 0.7152 * s.cbg[1] + 0.0722 * s.cbg[2];
                    bg = s.cbands == 1 ? std::vector<double>{l} : std::vector<double>{l, s.cbg[3]};
                }
                img = VImage::black(s.cw, s.ch).new_from_image(bg).cast(VIPS_FORMAT_UCHAR);
            }
            return img.copy(VImage::option()->set(
                "interpretation", (int) (s.cbands <= 2 ? VIPS_INTERPRETATION_B_W : VIPS_INTERPRETATION_sRGB)));
        }
        case Source::Raw: {
            size_t need = (size_t) s.rw * s.rh * s.rbands * vips_format_sizeof(s.rformat);
            if (s.buf.length() < need) throw VError("Raw input buffer is too small for the given dimensions");
            VImage img = VImage::new_from_memory(const_cast<char *>(s.buf.data()), need, s.rw, s.rh, s.rbands,
                                                 s.rformat);
            bool sixteen = s.rformat == VIPS_FORMAT_USHORT;
            img = img.copy(VImage::option()->set(
                "interpretation", (int) (s.rbands <= 2 ? (sixteen ? VIPS_INTERPRETATION_GREY16 : VIPS_INTERPRETATION_B_W)
                                                       : (sixteen ? VIPS_INTERPRETATION_RGB16 : VIPS_INTERPRETATION_sRGB))));
            if (s.rpremultiplied && img.has_alpha()) img = castLike(img.unpremultiply(), s.rformat);
            return img;
        }
        case Source::Text: {
            auto o = VImage::option()->set("justify", s.justify)->set("rgba", s.rgba);
            if (!s.font.empty()) o->set("font", s.font.c_str());
            if (!s.fontfile.empty()) o->set("fontfile", s.fontfile.c_str());
            if (s.tw > 0) o->set("width", s.tw);
            if (s.th > 0) o->set("height", s.th);
            if (s.dpi > 0) o->set("dpi", s.dpi);
            if (s.spacing > 0) o->set("spacing", s.spacing);
            o->set("align", enumFromNick(VIPS_TYPE_ALIGN, s.align == "left" ? "low" : s.align == "right" ? "high" : s.align, "align"));
            o->set("wrap", enumFromNick(VIPS_TYPE_TEXT_WRAP, s.wrap == "word-char" ? "word-char" : s.wrap, "wrap"));
            VImage img = VImage::text(s.text.c_str(), o);
            if (!s.rgba) img = img.copy(VImage::option()->set("interpretation", (int) VIPS_INTERPRETATION_B_W));
            return img;
        }
        case Source::Join: {
            std::vector<VImage> imgs;
            for (auto &in : s.inputs) imgs.push_back(run(*in));
            if (imgs.empty()) throw VError("join: no inputs");
            if (s.joinAnimated) {
                int w = imgs[0].width(), h = imgs[0].height(), bands = imgs[0].bands();
                for (auto &im : imgs) {
                    if (im.width() != w || im.height() != h) throw VError("join animated: all frames must have the same size");
                    bands = std::max(bands, im.bands());
                }
                for (auto &im : imgs) {
                    if (im.bands() < bands) im = im.bandjoin_const({maxAlpha(im)});
                }
                VImage out = VImage::arrayjoin(imgs, VImage::option()->set("across", 1));
                out = setPageHeight(out, h);
                out.set(VIPS_META_N_PAGES, (int) imgs.size());
                return out;
            }
            int bands = 0;
            for (auto &im : imgs) bands = std::max(bands, im.bands());
            for (auto &im : imgs) {
                if (im.bands() < bands) im = im.bandjoin_const({maxAlpha(im)});
            }
            return VImage::arrayjoin(
                imgs, VImage::option()
                          ->set("across", std::max(1, s.across))
                          ->set("shim", s.shim)
                          ->set("background", adaptBackground(imgs[0], s.joinBg))
                          ->set("halign", enumFromNick(VIPS_TYPE_ALIGN, s.halign, "halign"))
                          ->set("valign", enumFromNick(VIPS_TYPE_ALIGN, s.valign, "valign")));
        }
        default:
            throw VError("internal: unexpected source kind");
    }
}

// ================================================================ resize
static void computeResize(const ResizeSpec &r, int W, int H, int &tw, int &th) {
    int w = r.width, h = r.height;
    if (w <= 0 && h <= 0) {
        tw = W;
        th = H;
        return;
    }
    double sx = w > 0 ? (double) w / W : (double) h / H;
    double sy = h > 0 ? (double) h / H : (double) w / W;
    if (r.fit == "fill") {
        if (r.withoutEnlargement) sx = std::min(sx, 1.0), sy = std::min(sy, 1.0);
        if (r.withoutReduction) sx = std::max(sx, 1.0), sy = std::max(sy, 1.0);
        tw = std::max(1, (int) std::lround(W * sx));
        th = std::max(1, (int) std::lround(H * sy));
        return;
    }
    double s = (r.fit == "inside" || r.fit == "contain") ? std::min(sx, sy) : std::max(sx, sy);
    if (r.withoutEnlargement) s = std::min(s, 1.0);
    if (r.withoutReduction) s = std::max(s, 1.0);
    tw = std::max(1, (int) std::lround(W * s));
    th = std::max(1, (int) std::lround(H * s));
    if (w > 0 && std::abs(tw - w) == 1) tw = w;
    if (h > 0 && std::abs(th - h) == 1) th = h;
}

/** Scale every frame to exactly tw x th with the chosen kernel (alpha premultiplied). */
static VImage scaleTo(VImage img, int tw, int th, VipsKernel kernel) {
    int ph = pageHeight(img), n = img.height() / ph;
    if (img.width() == tw && ph == th) return img;
    double hs = (double) tw / img.width();
    double vs = (double) (th * n) / img.height();
    VipsBandFormat fmt = img.format();
    bool alpha = img.has_alpha();
    // Premultiply and cast straight back to the integer format (as sharp does) so that
    // vips_resize stays on its SIMD 8/16-bit path instead of falling back to float.
    if (alpha) img = img.premultiply().cast(fmt);
    img = img.resize(hs, VImage::option()->set("vscale", vs)->set("kernel", (int) kernel));
    if (alpha) img = img.unpremultiply().cast(fmt);
    img = castLike(img, fmt);
    // guard against rounding: force exact geometry
    if (img.width() != tw || img.height() != th * n) {
        img = img.embed(0, 0, std::max(tw, img.width()), std::max(th * n, img.height()),
                        VImage::option()->set("extend", (int) VIPS_EXTEND_COPY))
                  .extract_area(0, 0, tw, th * n);
    }
    return n > 1 ? setPageHeight(img, th) : img;
}

/** Find where `crop` (an extract_area of `frame`) sits inside `frame`. Byte-exact, early-exit scan. */
static void locateCrop(const VImage &frame, const VImage &crop, int &x, int &y) {
    size_t flen = 0, clen = 0;
    auto *f = static_cast<unsigned char *>(frame.write_to_memory(&flen));
    auto *c = static_cast<unsigned char *>(crop.write_to_memory(&clen));
    const int W = frame.width(), H = frame.height(), cw = crop.width(), ch = crop.height();
    const size_t px = flen / ((size_t) W * H), row = (size_t) cw * px;
    x = y = 0;
    bool found = false;
    for (int y0 = 0; y0 + ch <= H && !found; y0++) {
        for (int x0 = 0; x0 + cw <= W && !found; x0++) {
            int r = 0;
            while (r < ch && memcmp(f + (((size_t) (y0 + r) * W) + x0) * px, c + (size_t) r * row, row) == 0) r++;
            if (r == ch) {
                x = x0;
                y = y0;
                found = true;
            }
        }
    }
    g_free(f);
    g_free(c);
    if (!found) throw VError("smart crop: could not locate the crop window");
}

/** Crop (cover) or embed (contain) after the scale step, per frame. */
static VImage resizePost(VImage img, const ResizeSpec &r) {
    int W = img.width(), H = pageHeight(img);
    int w = r.width > 0 ? r.width : W;
    int h = r.height > 0 ? r.height : H;
    if (r.fit == "cover" && (W > w || H > h)) {
        int cw = std::min(w, W), ch = std::min(h, H);
        bool smart = r.position == "entropy" || r.position == "attention";
        int interesting = r.position == "entropy" ? VIPS_INTERESTING_ENTROPY : VIPS_INTERESTING_ATTENTION;
        if (smart && nPages(img) == 1) {
            return img.smartcrop(cw, ch, VImage::option()->set("interesting", interesting));
        }
        int x, y;
        if (smart) {
            // animated: crop the first frame with libvips, locate that window, apply it to every frame
            VImage first = img.extract_area(0, 0, W, H);
            int ax = 0, ay = 0;
            VImage crop = first.smartcrop(
                cw, ch, VImage::option()->set("interesting", interesting)->set("attention_x", &ax)->set("attention_y", &ay));
            if (interesting == VIPS_INTERESTING_ATTENTION) {
                // attention_x/y is the centre of the chosen window
                x = std::max(0, std::min(W - cw, ax - cw / 2));
                y = std::max(0, std::min(H - ch, ay - ch / 2));
            } else {
                // entropy mode doesn't report its window: find the crop inside the first frame
                locateCrop(first, crop, x, y);
            }
        } else {
            gravityOffset(r.position, W, H, cw, ch, x, y);
        }
        return perPage(img, [=](VImage f) { return f.extract_area(x, y, cw, ch); });
    }
    if (r.fit == "contain" && (W < w || H < h)) {
        img = withAlphaFor(img, r.background);
        std::vector<double> bg = adaptBackground(img, r.background);
        int ow = std::max(w, W), oh = std::max(h, H), x, y;
        gravityOffset(r.position, ow, oh, W, H, x, y);
        return perPage(img, [=](VImage f) {
            return f.embed(x, y, ow, oh, VImage::option()->set("extend", (int) VIPS_EXTEND_BACKGROUND)->set("background", bg));
        });
    }
    return img;
}

static VImage resizeImage(VImage img, const ResizeSpec &r) {
    int tw, th;
    computeResize(r, img.width(), pageHeight(img), tw, th);
    return resizePost(scaleTo(img, tw, th, r.kernel), r);
}

/** sharp's shrink-on-load: decode at reduced size, then one exact resize. */
static VImage shrinkOnLoad(const Source &s, const ResizeSpec &r, bool orient, bool random, double &workPixels) {
    const HeaderInfo &h = header(s);
    int W = h.width, H = h.pageH;
    bool swap = orient && h.orientation >= 5 && h.orientation <= 8;
    int oW = swap ? H : W, oH = swap ? W : H;
    int tw, th;
    computeResize(r, oW, oH, tw, th);
    double shrink = std::min((double) oW / tw, (double) oH / th);
    const std::string &l = h.loader;
    VImage img;
    if (shrink > 1 && l.rfind("jpegload", 0) == 0) {
        int factor = r.fastShrinkOnLoad ? 1 : 2;
        int js = shrink >= 8 * factor ? 8 : shrink >= 4 * factor ? 4 : shrink >= 2 * factor ? 2 : 1;
        img = loadFile(s, random, [=](vips::VOption *o) {
            if (js > 1) o->set("shrink", js);
        });
    } else if (shrink > 1 && l.rfind("webpload", 0) == 0) {
        double scale = r.fastShrinkOnLoad ? 1.0 / shrink : std::min(1.0, 2.0 / shrink);
        img = loadFile(s, random, [=](vips::VOption *o) { o->set("scale", scale); });
        if (img.height() > 0 && h.pages > 1 && s.pages != 1) {
            // webp scale is applied per page; keep page-height consistent
            int nph = (int) std::lround(H * scale);
            if (img.height() % nph == 0) img = setPageHeight(img, nph);
        }
    } else if ((l.rfind("svgload", 0) == 0 || l.rfind("pdfload", 0) == 0) && hasArgument(l, "scale")) {
        // vector input: render at exactly the size we need (also for enlargement)
        double scale = std::max((double) tw / oW, (double) th / oH);
        img = loadFile(s, random, [=](vips::VOption *o) { o->set("scale", scale); });
    } else {
        img = loadFile(s, random);
    }
    workPixels = (double) img.width() * img.height();
    if (orient) img = img.autorot();
    return scaleTo(img, tw, th, r.kernel);
}

// ================================================================ execute
static VImage run(const ImageBox &b) {
    const Source &s = *b.src;
    size_t i = 0;
    bool orient = s.autoOrient;
    if (b.steps.size() > 1 && b.steps[0].kind == StepKind::AutoOrient && b.steps[1].kind == StepKind::Resize) {
        orient = true;
        i = 1;
    }
    bool fileLike = s.kind == Source::File || s.kind == Source::Buffer;
    bool anyRandom = false, laterRandom = false;
    for (size_t j = 0; j < b.steps.size(); j++) {
        anyRandom = anyRandom || b.steps[j].random;
        if (j > i) laterRandom = laterRandom || b.steps[j].random;
    }
    double work = 0;
    VImage img;
    if (fileLike && i < b.steps.size() && b.steps[i].kind == StepKind::Resize) {
        const ResizeSpec &rs = b.steps[i].rs;
        bool smart = rs.position == "entropy" || rs.position == "attention";
        img = shrinkOnLoad(s, rs, orient, false, work);
        if (laterRandom || smart) img = img.copy_memory();  // small, already resized
        img = resizePost(img, rs);
        i++;
    } else {
        if (fileLike) {
            img = loadFile(s, anyRandom || orient);
        } else {
            img = loadOther(s);
            // join reads its inputs sequentially; materialise it when a later step needs random access
            if (s.kind == Source::Join && anyRandom) img = img.copy_memory();
        }
        work = (double) img.width() * img.height();
        if (orient && fileLike) img = img.autorot();
        i = (i == 1) ? 0 : i;
    }
    for (; i < b.steps.size(); i++) img = b.steps[i].fn(img);
    chooseThreads(std::max(work, (double) img.width() * img.height()));
    return img;
}

// ================================================================ output
static std::string formatFromSuffix(const std::string &path) {
    auto dot = path.find_last_of('.');
    std::string ext = dot == std::string::npos ? "" : lower(path.substr(dot + 1));
    if (ext == "jpg" || ext == "jpeg" || ext == "jpe") return "jpeg";
    if (ext == "tif") return "tiff";
    if (ext == "heic") return "heif";
    if (ext == "dzi" || ext == "szi") return "dz";
    if (ext == "png" || ext == "webp" || ext == "avif" || ext == "heif" || ext == "gif" || ext == "tiff" ||
        ext == "jxl" || ext == "raw" || ext == "dz" || ext == "zip")
        return ext == "zip" ? "dz" : ext;
    throw VError("Unsupported output format for path: " + path);
}

static std::string formatFromLoader(const std::string &l) {
    for (const char *f : {"jpeg", "png", "webp", "gif", "tiff", "jxl", "heif", "svg", "pdf", "jp2k", "rad", "ppm", "fits",
                          "vips", "magick", "openslide", "matrix", "csv", "uhdr"}) {
        if (l.rfind(f, 0) == 0) return f;
    }
    return "unknown";
}

static std::string sourceFormat(const ImageBox &b) {
    if (b.src->kind == Source::File || b.src->kind == Source::Buffer) {
        std::string f = formatFromLoader(header(*b.src).loader);
        if (f == "jpeg" || f == "png" || f == "webp" || f == "gif" || f == "tiff" || f == "heif" || f == "jxl") return f;
    }
    return "png";
}

static VImage applyExif(VImage img, const ImageBox &b) {
    if (b.exif.empty()) return img;
    img = img.copy();
    if (!b.exifMerge) {
        gchar **fields = vips_image_get_fields(img.get_image());
        for (int i = 0; fields[i]; i++) {
            if (g_str_has_prefix(fields[i], "exif-")) img.remove(fields[i]);
        }
        g_strfreev(fields);
    }
    for (auto &kv : b.exif) img.set(kv.first.c_str(), kv.second.c_str());
    return img;
}

static VImage prepareForSave(VImage img, const std::string &fmt, const ImageBox &b) {
    int keep = b.keep;
    VipsInterpretation in = img.interpretation();
    bool keepIcc = (keep & VIPS_FOREIGN_KEEP_ICC) != 0;
    bool hasIcc = img.get_typeof(VIPS_META_ICC_NAME) != 0;
    int depth = is16bit(in) && fmt != "jpeg" && fmt != "webp" && fmt != "gif" ? 16 : 8;
    if (!b.iccProfile.empty()) {
        img = img.icc_transform(b.iccProfile.c_str(), VImage::option()
                                                         ->set("embedded", hasIcc && !b.src->ignoreIcc)
                                                         ->set("intent", (int) VIPS_INTENT_PERCEPTUAL)
                                                         ->set("depth", depth));
    } else if (hasIcc && !keepIcc && in != VIPS_INTERPRETATION_LAB && !b.src->ignoreIcc) {
        try {
            img = img.icc_transform("srgb", VImage::option()
                                                ->set("embedded", true)
                                                ->set("intent", (int) VIPS_INTENT_PERCEPTUAL)
                                                ->set("depth", depth));
        } catch (const std::exception &) {
            vips_error_clear();
        }
    }
    in = img.interpretation();
    if (b.iccProfile.empty() && in != VIPS_INTERPRETATION_sRGB && in != VIPS_INTERPRETATION_B_W &&
        in != VIPS_INTERPRETATION_RGB16 && in != VIPS_INTERPRETATION_GREY16 && in != VIPS_INTERPRETATION_MULTIBAND &&
        fmt != "raw") {
        img = img.colourspace(VIPS_INTERPRETATION_sRGB);
    }
    bool allow16 = fmt == "png" || fmt == "tiff" || fmt == "raw" || fmt == "heif" || fmt == "avif" || fmt == "jxl";
    if (img.format() == VIPS_FORMAT_USHORT && !allow16) {
        img = img.colourspace(img.bands() <= 2 ? VIPS_INTERPRETATION_B_W : VIPS_INTERPRETATION_sRGB);
    }
    if (img.format() != VIPS_FORMAT_UCHAR && img.format() != VIPS_FORMAT_USHORT && fmt != "raw" && fmt != "tiff") {
        img = img.cast(VIPS_FORMAT_UCHAR);
    }
    img = applyExif(img, b);
    if (b.out.loop >= 0 || !b.out.delay.empty()) {
        img = img.copy();
        if (b.out.loop >= 0) img.set("loop", b.out.loop);
        if (!b.out.delay.empty()) {
            std::vector<int> d = b.out.delay;
            int n = nPages(img);
            if ((int) d.size() < n) d.resize(n, d.back());
            img.set("delay", d);
        }
    }
    return img;
}

static VipsForeignTiffCompression tiffCompression(const std::string &c) {
    std::string v = lower(c);
    if (v == "jpeg") return VIPS_FOREIGN_TIFF_COMPRESSION_JPEG;
    if (v == "deflate") return VIPS_FOREIGN_TIFF_COMPRESSION_DEFLATE;
    if (v == "lzw") return VIPS_FOREIGN_TIFF_COMPRESSION_LZW;
    if (v == "packbits") return VIPS_FOREIGN_TIFF_COMPRESSION_PACKBITS;
    if (v == "webp") return VIPS_FOREIGN_TIFF_COMPRESSION_WEBP;
    if (v == "zstd") return VIPS_FOREIGN_TIFF_COMPRESSION_ZSTD;
    if (v == "ccittfax4") return VIPS_FOREIGN_TIFF_COMPRESSION_CCITTFAX4;
    if (v == "jp2k") return VIPS_FOREIGN_TIFF_COMPRESSION_JP2K;
    if (v == "none") return VIPS_FOREIGN_TIFF_COMPRESSION_NONE;
    throw VError("Invalid tiff compression: " + c + " (expected none, jpeg, deflate, lzw, packbits, webp, zstd, ccittfax4, jp2k)");
}

static void formatOptions(vips::VOption *opts, const OutSpec &o, const std::string &fmt) {
    // sharp defaults: JPEG 4:2:0 (always), HEIF/AVIF 4:4:4
    auto subsample = o.chroma == "4:4:4" ? VIPS_FOREIGN_SUBSAMPLE_OFF : VIPS_FOREIGN_SUBSAMPLE_ON;
    if (fmt == "jpeg") {
        opts->set("Q", o.quality > 0 ? o.quality : 80)
            ->set("interlace", o.progressive)
            ->set("optimize_coding", o.optimizeCoding)
            ->set("subsample_mode", (int) subsample);
        if (o.mozjpeg) {
            opts->set("trellis_quant", true)
                ->set("overshoot_deringing", true)
                ->set("optimize_scans", true)
                ->set("interlace", true)
                ->set("quant_table", 3);
        }
    } else if (fmt == "png") {
        opts->set("compression", o.compressionLevel)
            ->set("interlace", o.progressive)
            ->set("filter", (int) (o.adaptiveFiltering ? VIPS_FOREIGN_PNG_FILTER_ALL : VIPS_FOREIGN_PNG_FILTER_NONE));
        if (o.palette) {
            int bits = o.colours <= 2 ? 1 : o.colours <= 4 ? 2 : o.colours <= 16 ? 4 : 8;
            opts->set("palette", true)
                ->set("Q", o.quality > 0 ? o.quality : 100)
                ->set("effort", o.effort >= 0 ? o.effort : 7)
                ->set("dither", o.dither)
                ->set("bitdepth", bits);
        }
    } else if (fmt == "webp") {
        opts->set("Q", o.quality > 0 ? o.quality : 80)
            ->set("lossless", o.lossless)
            ->set("smart_subsample", o.smartSubsample)
            ->set("effort", o.effort >= 0 ? o.effort : 4)
            ->set("alpha_q", o.alphaQuality)
            ->set("min_size", o.minSize)
            ->set("mixed", o.mixed);
        if (o.nearLossless >= 0) opts->set("near_lossless", true)->set("Q", o.nearLossless);
    } else if (fmt == "avif" || fmt == "heif") {
        opts->set("Q", o.quality > 0 ? o.quality : 50)
            ->set("lossless", o.lossless)
            ->set("effort", o.effort >= 0 ? o.effort : 4)
            ->set("subsample_mode", (int) (o.chroma == "4:2:0" ? VIPS_FOREIGN_SUBSAMPLE_ON : VIPS_FOREIGN_SUBSAMPLE_OFF))
            ->set("bitdepth", o.bitdepth);
        std::string c = fmt == "avif" ? "av1" : (o.compression.empty() ? "av1" : lower(o.compression));
        opts->set("compression", (int) (c == "hevc" ? VIPS_FOREIGN_HEIF_COMPRESSION_HEVC : VIPS_FOREIGN_HEIF_COMPRESSION_AV1));
    } else if (fmt == "gif") {
        int bits = (int) std::ceil(std::log2(std::max(2, std::min(256, o.colours))));
        opts->set("effort", o.effort >= 0 ? o.effort : 7)
            ->set("dither", o.dither)
            ->set("bitdepth", bits)
            ->set("interlace", o.progressive)
            ->set("interframe_maxerror", o.interframeMaxError)
            ->set("interpalette_maxerror", o.interpaletteMaxError)
            ->set("reuse", o.reuse);
    } else if (fmt == "tiff") {
        opts->set("Q", o.quality > 0 ? o.quality : 80)
            ->set("compression", (int) tiffCompression(o.compression.empty() ? "jpeg" : o.compression))
            ->set("tile", o.tile || o.pyramid)
            ->set("tile_width", o.tileWidth)
            ->set("tile_height", o.tileHeight)
            ->set("pyramid", o.pyramid);
        std::string p = lower(o.predictor);
        std::string comp = lower(o.compression.empty() ? "jpeg" : o.compression);
        // libtiff only accepts a predictor with deflate / lzw / zstd
        if (!p.empty() && (comp == "deflate" || comp == "lzw" || comp == "zstd")) {
            opts->set("predictor", (int) (p == "float" ? VIPS_FOREIGN_TIFF_PREDICTOR_FLOAT
                                          : p == "none" ? VIPS_FOREIGN_TIFF_PREDICTOR_NONE
                                                        : VIPS_FOREIGN_TIFF_PREDICTOR_HORIZONTAL));
        }
        if (o.bitdepth == 1 || o.bitdepth == 2 || o.bitdepth == 4) opts->set("bitdepth", o.bitdepth);
    } else if (fmt == "jxl") {
        opts->set("Q", o.quality > 0 ? o.quality : 75)->set("lossless", o.lossless)->set("effort", o.effort >= 0 ? o.effort : 7);
    }
}

static const char *saverFor(const std::string &fmt) {
    if (fmt == "jpeg") return "jpegsave";
    if (fmt == "png") return "pngsave";
    if (fmt == "webp") return "webpsave";
    if (fmt == "avif" || fmt == "heif") return "heifsave";
    if (fmt == "gif") return "gifsave";
    if (fmt == "tiff") return "tiffsave";
    if (fmt == "jxl") return "jxlsave";
    if (fmt == "dz") return "dzsave";
    throw VError("Unsupported output format: " + fmt);
}

static std::string tileSuffix(const OutSpec &o) {
    std::string f = o.format.empty() || o.format == "dz" ? "jpeg" : o.format;
    std::string ext = f == "jpeg" ? ".jpg" : "." + f;
    std::string q = o.quality > 0 ? "[Q=" + std::to_string(o.quality) + "]" : "";
    return ext + q;
}

static vips::VOption *saveOptions(const ImageBox &b, const std::string &fmt, const VImage &img) {
    auto opts = VImage::option()->set("keep", b.keep | (b.exif.empty() ? 0 : (int) VIPS_FOREIGN_KEEP_EXIF) |
                                                  (b.iccProfile.empty() ? 0 : (int) VIPS_FOREIGN_KEEP_ICC));
    if (fmt == "dz") {
        const TileSpec &t = b.tile;
        opts->set("tile_size", t.size)
            ->set("overlap", t.overlap)
            ->set("suffix", tileSuffix(b.out).c_str())
            ->set("layout", enumFromNick(VIPS_TYPE_FOREIGN_DZ_LAYOUT, t.layout, "tile layout"))
            ->set("container", enumFromNick(VIPS_TYPE_FOREIGN_DZ_CONTAINER, t.container, "tile container"))
            ->set("centre", t.centre)
            ->set("background", adaptBackground(img, t.background));
        if (!t.depth.empty()) opts->set("depth", enumFromNick(VIPS_TYPE_FOREIGN_DZ_DEPTH, t.depth, "tile depth"));
        if (t.angle) opts->set("angle", (int) (t.angle == 90 ? VIPS_ANGLE_D90 : t.angle == 180 ? VIPS_ANGLE_D180 : VIPS_ANGLE_D270));
        if (t.skipBlanks) opts->set("skip_blanks", 5);
        if (!t.basename.empty()) opts->set("basename", t.basename.c_str());
        if (!t.id.empty()) opts->set("id", t.id.c_str());
    } else {
        formatOptions(opts, b.out, fmt);
    }
    return opts;
}

struct Deadline {
    double seconds;
    gint64 start = g_get_monotonic_time();  // microseconds; VipsProgress::run only has whole seconds
};

static void evalCallback(VipsImage *image, VipsProgress *, Deadline *d) {
    if (d->seconds > 0 && (g_get_monotonic_time() - d->start) / 1e6 >= d->seconds) vips_image_set_kill(image, TRUE);
}

static void armTimeout(VImage &img, Deadline &d) {
    if (d.seconds <= 0) return;
    vips_image_set_progress(img.get_image(), TRUE);
    g_signal_connect(img.get_image(), "eval", G_CALLBACK(evalCallback), &d);
}

static void checkTimeout(const VImage &img, const Deadline &d) {
    if (d.seconds > 0 && vips_image_iskilled(img.get_image())) throw VError("timeout: processing exceeded limit");
}

/** Rethrow a vips error, translating a kill caused by our deadline into a timeout error. */
[[noreturn]] static void rethrowTimeout(const Deadline &d) {
    try {
        throw;
    } catch (const std::exception &e) {
        if (d.seconds > 0 && strstr(e.what(), "killed")) {
            vips_error_clear();
            char limit[32];
            snprintf(limit, sizeof limit, "%gs", d.seconds);
            throw VError(std::string("timeout: processing exceeded ") + limit);
        }
        throw;
    }
}

static Array makeInfo(const VImage &img, const std::string &fmt, size_t size) {
    Array info;
    info.set("format", String(fmt));
    info.set("width", Variant((zend_long) img.width()));
    info.set("height", Variant((zend_long) pageHeight(img)));
    info.set("channels", Variant((zend_long) img.bands()));
    info.set("premultiplied", Variant(false));
    info.set("size", Variant((zend_long) size));
    if (nPages(img) > 1) {
        info.set("pages", Variant((zend_long) nPages(img)));
        info.set("pageHeight", Variant((zend_long) pageHeight(img)));
    }
    return info;
}

static std::string outputFormat(const ImageBox &b, const std::string &forced) {
    if (b.tile.enabled) return "dz";
    if (!forced.empty()) return forced == "jpg" ? "jpeg" : forced == "tif" ? "tiff" : forced;
    if (!b.out.format.empty()) return b.out.format;
    return sourceFormat(b);
}

static Array encode(ImageBox &b, const std::string &forced) {
    std::string fmt = outputFormat(b, forced);
    VImage img = prepareForSave(run(b), fmt, b);
    Deadline d{b.timeoutSeconds};
    armTimeout(img, d);
    size_t len = 0;
    String data;
    if (fmt == "raw") {
        void *buf = img.write_to_memory(&len);
        checkTimeout(img, d);
        data = String((const char *) buf, len);
        g_free(buf);
    } else {
        std::string saver = std::string(saverFor(fmt)) + "_buffer";
        if (!vips_type_find("VipsOperation", saver.c_str())) throw VError("Output format not available: " + fmt);
        VipsBlob *blob = nullptr;
        vips::VOption *opts = saveOptions(b, fmt, img);
        if (fmt == "dz") opts->set("container", (int) VIPS_FOREIGN_DZ_CONTAINER_ZIP);
        opts->set("in", img)->set("buffer", &blob);
        try {
            VImage::call(saver.c_str(), opts);
        } catch (...) {
            rethrowTimeout(d);
        }
        len = VIPS_AREA(blob)->length;
        data = String((const char *) VIPS_AREA(blob)->data, len);  // single copy into the PHP string
        vips_area_unref(VIPS_AREA(blob));
    }
    Array result;
    result.set("data", data);
    result.set("info", makeInfo(img, fmt, len));
    return result;
}

static ImageBox *box(Variant &h) {
    return h.toBox<ImageBox>();
}

static Step generic(std::function<VImage(VImage)> fn, bool random = false) {
    Step s;
    s.fn = std::move(fn);
    s.random = random;
    return s;
}

static void fail(const std::exception &e) {
    std::string msg = e.what();
    while (!msg.empty() && (msg.back() == '\n' || msg.back() == ' ')) msg.pop_back();
    vips_error_clear();
    throwException(String(kExceptionClass), msg.c_str());
}

static std::shared_ptr<ImageBox> snapshot(const ImageBox *o) {
    auto c = std::make_shared<ImageBox>();
    c->src = o->src;
    c->steps = o->steps;
    return c;
}

static VipsBandFormat parseDepth(const std::string &d) {
    std::string v = lower(d);
    if (v == "char") return VIPS_FORMAT_CHAR;
    if (v == "ushort") return VIPS_FORMAT_USHORT;
    if (v == "short") return VIPS_FORMAT_SHORT;
    if (v == "uint") return VIPS_FORMAT_UINT;
    if (v == "int") return VIPS_FORMAT_INT;
    if (v == "float") return VIPS_FORMAT_FLOAT;
    if (v == "double") return VIPS_FORMAT_DOUBLE;
    if (v == "uchar") return VIPS_FORMAT_UCHAR;
    throw VError("Invalid raw depth: " + d + " (expected uchar, char, ushort, short, uint, int, float, double)");
}

#define PIXELFORGE_TRY try {
#define PIXELFORGE_CATCH(ret)                                                                                               \
    }                                                                                                                  \
    catch (const std::exception &e) {                                                                                  \
        fail(e);                                                                                                       \
        return ret;                                                                                                    \
    }

/** Like PIXELFORGE_STEP, but `pre` (argument parsing that may throw) also runs inside the try. */
#define PIXELFORGE_STEP_PRE(h, pre, expr)                                                                              \
    PIXELFORGE_TRY ImageBox *b = box(h);                                                                               \
    if (!b) return false;                                                                                              \
    pre;                                                                                                               \
    b->steps.push_back(expr);                                                                                          \
    return true;                                                                                                       \
    PIXELFORGE_CATCH(false)

#define PIXELFORGE_STEP(h, expr)                                                                                            \
    PIXELFORGE_TRY ImageBox *b = box(h);                                                                                    \
    if (!b) return false;                                                                                              \
    b->steps.push_back(expr);                                                                                          \
    return true;                                                                                                       \
    PIXELFORGE_CATCH(false)

static Variant newBox(std::shared_ptr<Source> src) {
    auto b = new ImageBox();
    b->src = std::move(src);
    return {b};
}

}  // namespace pixelforge

using namespace pixelforge;

// ================================================================= inputs
static std::shared_ptr<Source> inputSource(String failOn, Int limitPixels, Bool autoOrient, Int pages, Int page,
                                           Float density, Bool unlimited, Bool ignoreIcc) {
    auto s = std::make_shared<Source>();
    s->failOn = parseFailOn(str(failOn));
    s->limitPixels = limitPixels;
    s->autoOrient = autoOrient;
    s->pages = (int) pages;
    s->page = (int) page;
    s->density = density;
    s->unlimited = unlimited;
    s->ignoreIcc = ignoreIcc;
    return s;
}

Variant php_pixelforge_from_file(String path, String failOn, Int limitPixels, Bool autoOrient, Int pages, Int page,
                            Float density, Bool unlimited, Bool ignoreIcc) {
    PIXELFORGE_TRY ensureInit();
    auto s = inputSource(failOn, limitPixels, autoOrient, pages, page, density, unlimited, ignoreIcc);
    s->kind = Source::File;
    s->path = str(path);
    return newBox(s);
    PIXELFORGE_CATCH({})
}

Variant php_pixelforge_from_buffer(String data, String failOn, Int limitPixels, Bool autoOrient, Int pages, Int page,
                              Float density, Bool unlimited, Bool ignoreIcc) {
    PIXELFORGE_TRY ensureInit();
    if (data.length() == 0) throw VError("Input buffer is empty");
    auto s = inputSource(failOn, limitPixels, autoOrient, pages, page, density, unlimited, ignoreIcc);
    s->kind = Source::Buffer;
    s->buf = data;
    return newBox(s);
    PIXELFORGE_CATCH({})
}

Bool php_pixelforge_is_image(String data) {
    PIXELFORGE_TRY ensureInit();
    if (data.length() < 8) return false;
    bool found = vips_foreign_find_load_buffer(data.data(), data.length()) != nullptr;
    vips_error_clear();
    return found;
    PIXELFORGE_CATCH(false)
}

Variant php_pixelforge_from_raw(String data, Int width, Int height, Int channels, String depth, Bool premultiplied,
                               Int limitPixels) {
    PIXELFORGE_TRY ensureInit();
    if (width <= 0 || height <= 0 || channels < 1 || channels > 4) throw VError("raw: invalid width/height/channels");
    auto s = std::make_shared<Source>();
    s->kind = Source::Raw;
    s->buf = data;
    s->rw = (int) width;
    s->rh = (int) height;
    s->rbands = (int) channels;
    s->rformat = parseDepth(str(depth));
    s->rpremultiplied = premultiplied;
    s->limitPixels = limitPixels;
    if (s->limitPixels > 0 && (long long) s->rw * s->rh > s->limitPixels) throw VError("Input image exceeds pixel limit");
    return newBox(s);
    PIXELFORGE_CATCH({})
}

Variant php_pixelforge_create(Int width, Int height, Int channels, Float r, Float g, Float bl, Float a, String noise,
                         Float mean, Float sigma, Int limitPixels) {
    PIXELFORGE_TRY ensureInit();
    if (width <= 0 || height <= 0) throw VError("create(): width and height must be > 0");
    if (channels < 1 || channels > 4) throw VError("create(): channels must be 1-4");
    auto s = std::make_shared<Source>();
    s->kind = Source::Create;
    s->cw = (int) width;
    s->ch = (int) height;
    s->cbands = (int) channels;
    s->cbg = {r, g, bl, a};
    s->noise = oneOf(lower(str(noise)), {"", "gaussian"}, "noise type");
    s->limitPixels = limitPixels;
    if (s->limitPixels > 0 && (long long) s->cw * s->ch > s->limitPixels) throw VError("Input image exceeds pixel limit");
    s->noiseMean = mean;
    s->noiseSigma = sigma;
    return newBox(s);
    PIXELFORGE_CATCH({})
}

Variant php_pixelforge_text(String text, String font, String fontfile, Int width, Int height, String align, Bool justify,
                       Int dpi, Bool rgba, Int spacing, String wrap, Int limitPixels) {
    PIXELFORGE_TRY ensureInit();
    auto s = std::make_shared<Source>();
    s->kind = Source::Text;
    s->text = str(text);
    s->font = str(font);
    s->fontfile = str(fontfile);
    s->tw = (int) width;
    s->th = (int) height;
    s->align = lower(str(align));
    if (s->align == "center") s->align = "centre";
    s->justify = justify;
    s->dpi = (int) dpi;
    s->rgba = rgba;
    s->spacing = (int) spacing;
    s->wrap = lower(str(wrap));
    s->limitPixels = limitPixels;
    return newBox(s);
    PIXELFORGE_CATCH({})
}

Variant php_pixelforge_join_new(Bool animated, Int across, Int shim, Float r, Float g, Float bl, Float a, String halign,
                           String valign, Int limitPixels) {
    PIXELFORGE_TRY ensureInit();
    auto s = std::make_shared<Source>();
    s->kind = Source::Join;
    s->joinAnimated = animated;
    s->across = (int) across;
    s->shim = (int) shim;
    s->joinBg = {r, g, bl, a};
    auto al = [](std::string v) {
        v = lower(v);
        return v == "left" || v == "top" ? std::string("low") : v == "right" || v == "bottom" ? std::string("high") : v == "center" ? std::string("centre") : v;
    };
    s->halign = al(str(halign));
    s->valign = al(str(valign));
    s->limitPixels = limitPixels;
    return newBox(s);
    PIXELFORGE_CATCH({})
}

Bool php_pixelforge_join_add(Variant h, Variant input) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    ImageBox *in = box(input);
    if (!b || !in) return false;
    if (b->src->kind != Source::Join) throw VError("join_add: not a join pipeline");
    b->src->inputs.push_back(snapshot(in));
    return true;
    PIXELFORGE_CATCH(false)
}

Variant php_pixelforge_clone(Variant h) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return {};
    auto c = new ImageBox(*b);
    return {c};
    PIXELFORGE_CATCH({})
}

// ================================================================= geometry
Bool php_pixelforge_resize(Variant h, Int width, Int height, String fit, String position, Float r, Float g, Float bl, Float a,
                      Bool withoutEnlargement, Bool withoutReduction, String kernel, Bool fastShrinkOnLoad) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return false;
    Step s;
    s.kind = StepKind::Resize;
    s.rs.width = (int) width;
    s.rs.height = (int) height;
    s.rs.fit = lower(str(fit));
    s.rs.position = validGravity(lower(str(position)), true);
    s.rs.background = {r, g, bl, a};
    s.rs.withoutEnlargement = withoutEnlargement;
    s.rs.withoutReduction = withoutReduction;
    s.rs.kernel = parseKernel(str(kernel));
    s.rs.fastShrinkOnLoad = fastShrinkOnLoad;
    if (s.rs.fit != "cover" && s.rs.fit != "contain" && s.rs.fit != "fill" && s.rs.fit != "inside" &&
        s.rs.fit != "outside")
        throw VError("Invalid fit: " + s.rs.fit);
    s.random = s.rs.position == "entropy" || s.rs.position == "attention";
    ResizeSpec spec = s.rs;
    s.fn = [spec](VImage img) { return resizeImage(img, spec); };
    b->steps.push_back(s);
    return true;
    PIXELFORGE_CATCH(false)
}

Bool php_pixelforge_extract(Variant h, Int left, Int top, Int width, Int height) {
    int l = (int) left, t = (int) top, w = (int) width, hh = (int) height;
    PIXELFORGE_STEP(h, generic([=](VImage img) {
                   if (l < 0 || t < 0 || w <= 0 || hh <= 0 || l + w > img.width() || t + hh > pageHeight(img))
                       throw VError("extract(): area is outside the image");
                   return perPage(img, [=](VImage f) { return f.extract_area(l, t, w, hh); });
               }))
}

Bool php_pixelforge_extend(Variant h, Int top, Int bottom, Int left, Int right, String with, Float r, Float g, Float bl,
                      Float a) {
    int t = (int) top, btm = (int) bottom, l = (int) left, rt = (int) right;
    std::string mode;
    std::vector<double> bg{r, g, bl, a};
    PIXELFORGE_STEP_PRE(h, mode = oneOf(lower(str(with)), {"background", "copy", "repeat", "mirror"}, "extendWith"), generic(
                      [=](VImage img) {
                          int ext = mode == "copy" ? VIPS_EXTEND_COPY
                                    : mode == "repeat" ? VIPS_EXTEND_REPEAT
                                    : mode == "mirror" ? VIPS_EXTEND_MIRROR
                                                       : VIPS_EXTEND_BACKGROUND;
                          if (ext == VIPS_EXTEND_BACKGROUND) img = withAlphaFor(img, bg);
                          std::vector<double> b2 = adaptBackground(img, bg);
                          return perPage(img, [=](VImage f) {
                              return f.embed(l, t, f.width() + l + rt, f.height() + t + btm,
                                             VImage::option()->set("extend", ext)->set("background", b2));
                          });
                      },
                      mode == "repeat" || mode == "mirror"))
}

Bool php_pixelforge_trim(Variant h, Float threshold, Bool useBackground, Float r, Float g, Float bl, Bool lineArt) {
    double th = threshold;
    bool useBg = useBackground, la = lineArt;
    std::vector<double> bg{r, g, bl, 255};
    PIXELFORGE_STEP(h, generic(
                      [=](VImage img) {
                          VImage first = img.extract_area(0, 0, img.width(), pageHeight(img));
                          VImage probe = first.has_alpha() ? first.flatten() : first;
                          auto opts = VImage::option()->set("threshold", th)->set("line_art", la);
                          if (useBg) opts->set("background", adaptBackground(probe, bg));
                          int top, width, height;
                          int left = probe.find_trim(&top, &width, &height, opts);
                          if (width <= 0 || height <= 0) return img;
                          return perPage(img, [=](VImage f) { return f.extract_area(left, top, width, height); });
                      },
                      true))
}

Bool php_pixelforge_rotate(Variant h, Float angle, Float r, Float g, Float bl, Float a) {
    double ang = std::fmod(std::fmod(angle, 360.0) + 360.0, 360.0);
    std::vector<double> bg{r, g, bl, a};
    PIXELFORGE_STEP(h, generic(
                      [=](VImage img) {
                          if (ang == 0) return img;
                          if (ang == 90 || ang == 180 || ang == 270) {
                              VipsAngle va = ang == 90 ? VIPS_ANGLE_D90 : ang == 180 ? VIPS_ANGLE_D180 : VIPS_ANGLE_D270;
                              return perPage(img, [=](VImage f) { return f.rot(va); });
                          }
                          img = withAlphaFor(img, bg);
                          std::vector<double> b2 = adaptBackground(img, bg);
                          return perPage(img, [=](VImage f) { return f.rotate(ang, VImage::option()->set("background", b2)); });
                      },
                      ang != 0 && ang != 180))
}

Bool php_pixelforge_auto_orient(Variant h) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return false;
    Step s = generic([](VImage img) { return img.autorot(); }, true);
    s.kind = StepKind::AutoOrient;
    b->steps.push_back(s);
    return true;
    PIXELFORGE_CATCH(false)
}

Bool php_pixelforge_flip(Variant h) {
    PIXELFORGE_STEP(h, generic([](VImage img) { return perPage(img, [](VImage f) { return f.flip(VIPS_DIRECTION_VERTICAL); }); }, true))
}

Bool php_pixelforge_flop(Variant h) {
    PIXELFORGE_STEP(h, generic([](VImage img) { return img.flip(VIPS_DIRECTION_HORIZONTAL); }))
}

Bool php_pixelforge_affine(Variant h, Float a, Float b2, Float c, Float d, Float r, Float g, Float bl, Float al,
                      String interp, Float idx, Float idy, Float odx, Float ody) {
    std::vector<double> m{a, b2, c, d};
    std::vector<double> bg{r, g, bl, al};
    std::string ip = lower(str(interp));
    double ix = idx, iy = idy, ox = odx, oy = ody;
    PIXELFORGE_STEP(h, generic(
                      [=](VImage img) {
                          img = withAlphaFor(img, bg);
                          std::vector<double> b3 = adaptBackground(img, bg);
                          return perPage(img, [=](VImage f) {
                              return f.affine(m, VImage::option()
                                                     ->set("background", b3)
                                                     ->set("idx", ix)
                                                     ->set("idy", iy)
                                                     ->set("odx", ox)
                                                     ->set("ody", oy)
                                                     ->set("interpolate", vips::VInterpolate::new_from_name(
                                                                              ip.empty() ? "bicubic" : ip.c_str())));
                          });
                      },
                      true))
}

// ================================================================= operations
Bool php_pixelforge_sharpen(Variant h, Float sigma, Float m1, Float m2, Float x1, Float y2, Float y3) {
    double s = sigma, a = m1, bb = m2, c = x1, d = y2, e = y3;
    PIXELFORGE_STEP(h, generic([=](VImage img) {
                   if (s <= 0) {
                       // fast, mild sharpen: integer convolution, identical to sharp
                       VImage mask = VImage::new_matrixv(3, 3, -1.0, -1.0, -1.0, -1.0, 32.0, -1.0, -1.0, -1.0, -1.0);
                       mask.set("scale", 24.0);
                       return img.conv(mask, VImage::option()->set("precision", (int) VIPS_PRECISION_INTEGER));
                   }
                   VipsInterpretation orig = img.interpretation();
                   VImage out = img.sharpen(VImage::option()
                                                ->set("sigma", s)
                                                ->set("m1", a)
                                                ->set("m2", bb)
                                                ->set("x1", c)
                                                ->set("y2", d)
                                                ->set("y3", e));
                   if (orig == VIPS_INTERPRETATION_RGB16 || orig == VIPS_INTERPRETATION_sRGB || orig == VIPS_INTERPRETATION_B_W)
                       out = out.colourspace(orig);
                   return out;
               }))
}

Bool php_pixelforge_median(Variant h, Int size) {
    int sz = (int) size;
    PIXELFORGE_STEP(h, generic([=](VImage img) { return img.median(sz); }))
}

Bool php_pixelforge_blur(Variant h, Float sigma, String precision, Float minAmplitude) {
    double s = sigma, ma = minAmplitude;
    std::string p;
    PIXELFORGE_STEP_PRE(h, p = oneOf(lower(str(precision)), {"integer", "float", "approximate"}, "blur precision"), generic([=](VImage img) {
                   if (s < 0.3) {
                       VImage mask = VImage::new_matrixv(3, 3, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
                       mask.set("scale", 9.0);
                       return img.conv(mask, VImage::option()->set("precision", (int) VIPS_PRECISION_INTEGER));
                   }
                   int prec = p == "float" ? VIPS_PRECISION_FLOAT : p == "approximate" ? VIPS_PRECISION_APPROXIMATE
                                                                                       : VIPS_PRECISION_INTEGER;
                   return img.gaussblur(s, VImage::option()->set("precision", prec)->set("min_ampl", ma));
               }))
}

Bool php_pixelforge_flatten(Variant h, Float r, Float g, Float bl) {
    std::vector<double> bg{r, g, bl, 255};
    PIXELFORGE_STEP(h, generic([=](VImage img) {
                   if (!img.has_alpha()) return img;
                   std::vector<double> b2 = adaptBackground(img, bg);
                   b2.pop_back();
                   return castLike(img.flatten(VImage::option()->set("background", b2)), img.format());
               }))
}

Bool php_pixelforge_unflatten(Variant h) {
    PIXELFORGE_STEP(h, generic([](VImage img) {
                   VImage base = removeAlpha(img);
                   double max = maxAlpha(base);
                   VImage white = (base >= max).bandand();
                   VImage alpha = white.ifthenelse(0, max).cast(base.format());
                   if (img.has_alpha()) alpha = alpha.boolean(img.extract_band(img.bands() - 1), VIPS_OPERATION_BOOLEAN_AND);
                   return base.bandjoin(alpha);
               }))
}

Bool php_pixelforge_gamma(Variant h, Float gamma, Float gammaOut) {
    double gi = gamma, go = gammaOut;
    PIXELFORGE_STEP(h, generic([=](VImage img) {
                   return onColour(img, [&](VImage c) {
                       VImage out = c.gamma(VImage::option()->set("exponent", 1.0 / gi));
                       out = out.gamma(VImage::option()->set("exponent", go));
                       return castLike(out, c.format());
                   });
               }))
}

Bool php_pixelforge_negate(Variant h, Bool alpha) {
    bool al = alpha;
    PIXELFORGE_STEP(h, generic([=](VImage img) {
                   if (al || !img.has_alpha()) return castLike(img.invert(), img.format());
                   return onColour(img, [](VImage c) { return castLike(c.invert(), c.format()); });
               }))
}

Bool php_pixelforge_normalise(Variant h, Float lowerPct, Float upperPct) {
    double lo = lowerPct, hi = upperPct;
    PIXELFORGE_STEP(h, generic(
                      [=](VImage img) {
                          return onColour(img, [&](VImage c) {
                              VipsInterpretation orig = c.interpretation();
                              VipsBandFormat fmt = c.format();
                              VImage lab = c.colourspace(VIPS_INTERPRETATION_LAB);
                              VImage L = lab.extract_band(0);
                              VImage hist = (L * 2.55).cast(VIPS_FORMAT_UCHAR);
                              double mn = hist.percent(lo) / 2.55;
                              double mx = hist.percent(hi) / 2.55;
                              if (mx <= mn) return c;
                              double f = 100.0 / (mx - mn);
                              VImage out = L.linear(f, -mn * f)
                                               .bandjoin(lab.extract_band(1, VImage::option()->set("n", 2)))
                                               .copy(VImage::option()->set("interpretation", (int) VIPS_INTERPRETATION_LAB));
                              out = out.colourspace(c.bands() == 1 ? VIPS_INTERPRETATION_B_W
                                                    : orig == VIPS_INTERPRETATION_RGB16 ? VIPS_INTERPRETATION_RGB16
                                                                                        : VIPS_INTERPRETATION_sRGB);
                              return castLike(out, fmt);
                          });
                      },
                      true))
}

Bool php_pixelforge_clahe(Variant h, Int width, Int height, Int maxSlope) {
    int w = (int) width, hh = (int) height, ms = (int) maxSlope;
    PIXELFORGE_STEP(h, generic([=](VImage img) { return img.hist_local(w, hh, VImage::option()->set("max_slope", ms)); }))
}

Bool php_pixelforge_threshold(Variant h, Int threshold, Bool greyscale) {
    double t = (double) threshold;
    bool grey = greyscale;
    PIXELFORGE_STEP(h, generic([=](VImage img) {
                   return onColour(img, [&](VImage c) {
                       if (grey && c.bands() > 1) c = c.colourspace(VIPS_INTERPRETATION_B_W);
                       return (c >= t).cast(c.format());
                   });
               }))
}

Bool php_pixelforge_linear(Variant h, String a, String b2) {
    std::vector<double> va, vb;
    PIXELFORGE_STEP_PRE(h, (va = parseList(str(a)), vb = parseList(str(b2))), generic([=](VImage img) {
                   return onColour(img, [&](VImage c) { return castLike(c.linear(va, vb), c.format()); });
               }))
}

Bool php_pixelforge_modulate(Variant h, Float brightness, Float saturation, Float hue, Float lightness) {
    double br = brightness, sa = saturation, hu = hue, li = lightness;
    PIXELFORGE_STEP(h, generic([=](VImage img) {
                   return onColour(img, [&](VImage c) {
                       VipsInterpretation orig = c.interpretation();
                       VipsBandFormat fmt = c.format();
                       if (c.bands() < 3) {
                           VImage out = c.colourspace(VIPS_INTERPRETATION_LAB).linear({br, 1, 1}, {li, 0, 0});
                           return castLike(out.colourspace(orig), fmt);
                       }
                       VImage out = c.colourspace(VIPS_INTERPRETATION_LCH).linear({br, sa, 1}, {li, 0, hu});
                       return castLike(out.colourspace(orig == VIPS_INTERPRETATION_RGB16 ? orig : VIPS_INTERPRETATION_sRGB), fmt);
                   });
               }))
}

Bool php_pixelforge_tint(Variant h, Float r, Float g, Float bl) {
    double tr = r, tg = g, tb = bl;
    PIXELFORGE_STEP(h, generic([=](VImage img) {
                   return onColour(img, [&](VImage c) {
                       VipsBandFormat fmt = c.format();
                       VImage px = VImage::black(1, 1).new_from_image({tr, tg, tb}).cast(VIPS_FORMAT_UCHAR).copy(
                           VImage::option()->set("interpretation", (int) VIPS_INTERPRETATION_sRGB));
                       std::vector<double> lab = px.colourspace(VIPS_INTERPRETATION_LAB).getpoint(0, 0);
                       VImage L = c.colourspace(VIPS_INTERPRETATION_LAB).extract_band(0);
                       VImage out = L.bandjoin_const({lab[1], lab[2]})
                                        .copy(VImage::option()->set("interpretation", (int) VIPS_INTERPRETATION_LAB))
                                        .colourspace(VIPS_INTERPRETATION_sRGB);
                       return castLike(out, fmt);
                   });
               }))
}

Bool php_pixelforge_colourspace(Variant h, String space) {
    VipsInterpretation sp;
    PIXELFORGE_STEP_PRE(h, sp = parseSpace(str(space)), generic([=](VImage img) { return img.colourspace(sp); }))
}

Bool php_pixelforge_remove_alpha(Variant h) {
    PIXELFORGE_STEP(h, generic([](VImage img) { return removeAlpha(img); }))
}

Bool php_pixelforge_ensure_alpha(Variant h, Float alpha) {
    double al = alpha;
    PIXELFORGE_STEP(h, generic([=](VImage img) {
                   if (img.has_alpha()) return img;
                   return img.bandjoin_const({maxAlpha(img) * al});
               }))
}

Bool php_pixelforge_extract_channel(Variant h, Int channel) {
    int ch = (int) channel;
    PIXELFORGE_STEP(h, generic([=](VImage img) {
                   if (ch < 0 || ch >= img.bands()) throw VError("extractChannel(): channel out of range");
                   return img.extract_band(ch).copy(VImage::option()->set(
                       "interpretation", (int) (is16bit(img.interpretation()) ? VIPS_INTERPRETATION_GREY16 : VIPS_INTERPRETATION_B_W)));
               }))
}

Bool php_pixelforge_join_channel(Variant h, Variant other) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    ImageBox *o = box(other);
    if (!b || !o) return false;
    auto ov = snapshot(o);
    b->steps.push_back(generic([=](VImage img) {
        VImage extra = run(*ov);
        VImage out = img.bandjoin(castLike(extra, img.format()));
        if (img.interpretation() == VIPS_INTERPRETATION_B_W && out.bands() >= 3)
            out = out.copy(VImage::option()->set("interpretation", (int) VIPS_INTERPRETATION_sRGB));
        return out;
    }));
    return true;
    PIXELFORGE_CATCH(false)
}

Bool php_pixelforge_bandbool(Variant h, String op) {
    int o = 0;
    PIXELFORGE_STEP_PRE(h, o = enumFromNick(VIPS_TYPE_OPERATION_BOOLEAN, lower(str(op)), "boolean operation"), generic([=](VImage img) {
                   return img.bandbool((VipsOperationBoolean) o).copy(VImage::option()->set(
                       "interpretation", (int) VIPS_INTERPRETATION_B_W));
               }))
}

Bool php_pixelforge_boolean(Variant h, Variant other, String op) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    ImageBox *ob = box(other);
    if (!b || !ob) return false;
    int o = enumFromNick(VIPS_TYPE_OPERATION_BOOLEAN, lower(str(op)), "boolean operation");
    auto ov = snapshot(ob);
    b->steps.push_back(generic([=](VImage img) {
        VImage rhs = run(*ov);
        return castLike(img.boolean(rhs, (VipsOperationBoolean) o), img.format());
    }));
    return true;
    PIXELFORGE_CATCH(false)
}

static Bool morph(Variant h, Int width, VipsOperationMorphology op) {
    int w = std::max(1, (int) width);
    PIXELFORGE_STEP(h, generic([=](VImage img) {
                   int n = 2 * w + 1;
                   std::vector<double> m(n * n, 255.0);
                   VImage mask = VImage::new_matrix(n, n, m.data(), (int) m.size());
                   return onColour(img, [&](VImage c) { return castLike(c.morph(mask, op), c.format()); });
               }))
}

Bool php_pixelforge_dilate(Variant h, Int width) {
    return morph(h, width, VIPS_OPERATION_MORPHOLOGY_DILATE);
}

Bool php_pixelforge_erode(Variant h, Int width) {
    return morph(h, width, VIPS_OPERATION_MORPHOLOGY_ERODE);
}

Bool php_pixelforge_convolve(Variant h, Int width, Int height, String kernel, Float scale, Float offset) {
    int w = (int) width, hh = (int) height;
    std::vector<double> k;
    double sc = scale, off = offset;
    PIXELFORGE_STEP_PRE(h, {
        k = parseList(str(kernel));
        if (w <= 0 || hh <= 0 || (int) k.size() != w * hh) throw VError("convolve(): kernel size does not match width*height");
    }, generic([=](VImage img) {
                   VImage mask = VImage::new_matrix(w, hh, const_cast<double *>(k.data()), (int) k.size());
                   double s = sc;
                   if (s == 0) {
                       for (double v : k) s += v;
                       if (s == 0) s = 1;
                   }
                   mask.set("scale", s);
                   mask.set("offset", off);
                   return onColour(img, [&](VImage c) { return castLike(c.conv(mask), c.format()); });
               }))
}

Bool php_pixelforge_recomb(Variant h, String matrix) {
    std::vector<double> m;
    int n = 0;
    PIXELFORGE_STEP_PRE(h, {
        m = parseList(str(matrix));
        n = (int) std::lround(std::sqrt((double) m.size()));
        if (n < 1 || n * n != (int) m.size()) throw VError("recomb(): matrix must be square (3x3 or 4x4)");
    }, generic([=](VImage img) {
                   VImage mat = VImage::new_matrix(n, n, const_cast<double *>(m.data()), (int) m.size());
                   if (n == img.bands()) return castLike(img.recomb(mat), img.format());
                   return onColour(img, [&](VImage c) { return castLike(c.recomb(mat), c.format()); });
               }))
}

Bool php_pixelforge_composite(Variant h, Variant overlay, String gravity, Int left, Int top, String blend, Bool tile,
                         Bool premultiplied) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    ImageBox *o = box(overlay);
    if (!b || !o) return false;
    auto ov = snapshot(o);
    std::string grav = validGravity(lower(str(gravity)), false);
    std::string bl = lower(str(blend));
    int mode = enumFromNick(VIPS_TYPE_BLEND_MODE, bl.empty() ? "over" : bl, "blend mode");
    int l = (int) left, t = (int) top;
    bool tl = tile, pre = premultiplied;
    b->steps.push_back(generic([=](VImage img) {
        VImage over = run(*ov);
        int W = img.width(), H = pageHeight(img);
        if (tl && (over.width() < W || over.height() < H)) {
            int ax = (W + over.width() - 1) / over.width();
            int ay = (H + over.height() - 1) / over.height();
            over = over.replicate(ax, ay).extract_area(0, 0, W, H);
        }
        if (over.width() > W || over.height() > H)
            over = over.extract_area(0, 0, std::min(over.width(), W), std::min(over.height(), H));
        int x, y;
        if (l != INT32_MIN && t != INT32_MIN) {
            x = l;
            y = t;
        } else {
            gravityOffset(grav, W, H, over.width(), over.height(), x, y);
        }
        return perPage(img, [&](VImage f) {
            return f.composite2(over, (VipsBlendMode) mode,
                                VImage::option()->set("x", x)->set("y", y)->set("premultiplied", pre));
        });
    }));
    return true;
    PIXELFORGE_CATCH(false)
}

// ================================================================= output config
Bool php_pixelforge_output(Variant h, String format, Int quality, Bool lossless, Int effort, Bool progressive, String chroma,
                      Bool mozjpeg, Int compressionLevel, Bool palette, Int colours, Float dither,
                      Bool adaptiveFiltering, Int nearLossless, Bool smartSubsample, Int alphaQuality, Int bitdepth,
                      String compression, String predictor, Bool tile, Int tileWidth, Int tileHeight, Bool pyramid,
                      Int loop, String delay, Bool minSize, Bool mixed, Float interframeMaxError,
                      Float interpaletteMaxError, Bool reuse, Bool optimizeCoding) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return false;
    OutSpec &o = b->out;
    o.format = lower(str(format));
    if (o.format == "jpg") o.format = "jpeg";
    if (o.format == "tif") o.format = "tiff";
    if (o.format != "raw") saverFor(o.format);
    o.quality = (int) quality;
    o.lossless = lossless;
    o.effort = (int) effort;
    o.progressive = progressive;
    o.chroma = oneOf(str(chroma), {"", "4:2:0", "4:4:4"}, "chromaSubsampling");
    o.mozjpeg = mozjpeg;
    o.compressionLevel = (int) compressionLevel;
    o.palette = palette;
    o.colours = (int) colours;
    o.dither = dither;
    o.adaptiveFiltering = adaptiveFiltering;
    o.nearLossless = (int) nearLossless;
    o.smartSubsample = smartSubsample;
    o.alphaQuality = (int) alphaQuality;
    o.bitdepth = (int) bitdepth;
    o.compression = lower(str(compression));
    o.predictor = oneOf(lower(str(predictor)), {"", "none", "horizontal", "float"}, "tiff predictor");
    if (o.format == "tiff" && !o.compression.empty()) tiffCompression(o.compression);
    if (o.format == "heif" || o.format == "avif") oneOf(o.compression, {"", "av1", "hevc"}, "heif compression");
    o.tile = tile;
    o.tileWidth = (int) tileWidth;
    o.tileHeight = (int) tileHeight;
    o.pyramid = pyramid;
    o.loop = (int) loop;
    o.delay.clear();
    for (double d : parseList(str(delay))) o.delay.push_back((int) d);
    o.minSize = minSize;
    o.mixed = mixed;
    o.interframeMaxError = interframeMaxError;
    o.interpaletteMaxError = interpaletteMaxError;
    o.reuse = reuse;
    o.optimizeCoding = optimizeCoding;
    return true;
    PIXELFORGE_CATCH(false)
}

Bool php_pixelforge_tile(Variant h, Int size, Int overlap, Int angle, String layout, String container, String depth,
                    Bool skipBlanks, Bool centre, String basename, String id, Float r, Float g, Float bl, Float a) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return false;
    TileSpec &t = b->tile;
    t.enabled = true;
    t.size = (int) size;
    t.overlap = (int) overlap;
    t.angle = (int) angle;
    t.layout = lower(str(layout));
    if (t.layout == "iiif3") t.layout = "iiif3";
    t.container = lower(str(container));
    t.depth = lower(str(depth));
    t.skipBlanks = skipBlanks;
    t.centre = centre;
    t.basename = str(basename);
    t.id = str(id);
    t.background = {r, g, bl, a};
    return true;
    PIXELFORGE_CATCH(false)
}

Bool php_pixelforge_keep(Variant h, Int flags) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return false;
    b->keep = (int) flags;
    return true;
    PIXELFORGE_CATCH(false)
}

Bool php_pixelforge_icc(Variant h, String profile) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return false;
    b->iccProfile = str(profile);
    return true;
    PIXELFORGE_CATCH(false)
}

Bool php_pixelforge_exif(Variant h, String flat, Bool merge) {
    // flat = "IFD0\x1fCopyright\x1fvalue\x1e..." records
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return false;
    b->exif.clear();
    b->exifMerge = merge;
    std::string s = str(flat);
    size_t pos = 0;
    while (pos < s.size()) {
        size_t end = s.find('\x1e', pos);
        if (end == std::string::npos) end = s.size();
        std::string rec = s.substr(pos, end - pos);
        size_t a = rec.find('\x1f'), c = a == std::string::npos ? a : rec.find('\x1f', a + 1);
        if (a != std::string::npos && c != std::string::npos) {
            std::string ifd = lower(rec.substr(0, a)), tag = rec.substr(a + 1, c - a - 1), val = rec.substr(c + 1);
            b->exif.emplace_back("exif-" + ifd + "-" + tag, val);
        }
        pos = end + 1;
    }
    return true;
    PIXELFORGE_CATCH(false)
}

Bool php_pixelforge_timeout(Variant h, Float seconds) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return false;
    b->timeoutSeconds = seconds;
    return true;
    PIXELFORGE_CATCH(false)
}

// ================================================================= sinks
Array php_pixelforge_to_buffer(Variant h, String format) {
    TrimGuard trim;
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return Array();
    return encode(*b, lower(str(format)));
    PIXELFORGE_CATCH(Array())
}

Array php_pixelforge_to_file(Variant h, String path) {
    TrimGuard trim;
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return Array();
    std::string p = str(path);
    std::string fmt = b->tile.enabled ? "dz" : !b->out.format.empty() ? b->out.format : formatFromSuffix(p);
    VImage img = prepareForSave(run(*b), fmt, *b);
    Deadline d{b->timeoutSeconds};
    armTimeout(img, d);
    if (fmt == "raw") {
        size_t len = 0;
        void *buf = img.write_to_memory(&len);
        checkTimeout(img, d);
        FILE *f = fopen(p.c_str(), "wb");
        if (!f) {
            g_free(buf);
            throw VError("Cannot open output file: " + p);
        }
        size_t written = fwrite(buf, 1, len, f);
        fclose(f);
        g_free(buf);
        if (written != len) throw VError("Short write: " + p);
        return makeInfo(img, fmt, len);
    }
    const char *saver = saverFor(fmt);
    if (!vips_type_find("VipsOperation", saver)) throw VError(std::string("Output format not available: ") + fmt);
    vips::VOption *opts = saveOptions(*b, fmt, img);
    std::string target = p;
    if (fmt == "dz") {
        // dzsave wants the basename without extension; ".zip" selects the zip container
        std::string lp = lower(p);
        if (lp.size() > 4 && lp.compare(lp.size() - 4, 4, ".zip") == 0) opts->set("container", (int) VIPS_FOREIGN_DZ_CONTAINER_ZIP);
        if (lp.size() > 4 && lp.compare(lp.size() - 4, 4, ".szi") == 0) opts->set("container", (int) VIPS_FOREIGN_DZ_CONTAINER_SZI);
    }
    opts->set("in", img)->set("filename", target.c_str());
    try {
        VImage::call(saver, opts);
    } catch (...) {
        rethrowTimeout(d);
    }
    GStatBuf st;
    size_t size = g_stat(p.c_str(), &st) == 0 ? (size_t) st.st_size : 0;
    return makeInfo(img, fmt, size);
    PIXELFORGE_CATCH(Array())
}

// ================================================================= introspection
static void setBlob(Array &m, const VImage &img, const char *field, const char *key) {
    if (!img.get_typeof(field)) return;
    size_t len = 0;
    const void *data = img.get_blob(field, &len);
    if (data && len) m.set(key, String((const char *) data, len));
}

Array php_pixelforge_metadata(Variant h) {
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return Array();
    const Source &s = *b->src;
    bool fileLike = s.kind == Source::File || s.kind == Source::Buffer;
    VImage img = fileLike ? loadFile(s, false) : loadOther(s);
    Array m;
    std::string fmt = fileLike ? formatFromLoader(header(s).loader) : "raw";
    m.set("format", String(fmt));
    if (s.kind == Source::Buffer) m.set("size", Variant((zend_long) s.buf.length()));
    else if (s.kind == Source::File) {
        GStatBuf st;
        if (g_stat(s.path.c_str(), &st) == 0) m.set("size", Variant((zend_long) st.st_size));
    }
    int ph = pageHeight(img);
    m.set("width", Variant((zend_long) img.width()));
    m.set("height", Variant((zend_long) ph));
    m.set("space", String(nick(VIPS_TYPE_INTERPRETATION, img.interpretation(), "unknown")));
    m.set("channels", Variant((zend_long) img.bands()));
    m.set("depth", String(nick(VIPS_TYPE_BAND_FORMAT, img.format(), "uchar")));
    if (img.xres() != 1.0) m.set("density", Variant((zend_long) std::lround(img.xres() * 25.4)));
    if (img.get_typeof("resolution-unit")) m.set("resolutionUnit", String(img.get_string("resolution-unit")));
    if (img.get_typeof("jpeg-chroma-subsample")) m.set("chromaSubsampling", String(img.get_string("jpeg-chroma-subsample")));
    m.set("isProgressive", Variant(img.get_typeof("interlaced") ? img.get_int("interlaced") != 0 : false));
    if (img.get_typeof("palette")) m.set("isPalette", Variant(img.get_int("palette") != 0));
    if (img.get_typeof("bits-per-sample")) m.set("bitsPerSample", Variant((zend_long) img.get_int("bits-per-sample")));
    if (fmt == "heif" && img.get_typeof("heif-compression")) m.set("compression", String(img.get_string("heif-compression")));
    int pages = img.get_typeof(VIPS_META_N_PAGES) ? img.get_int(VIPS_META_N_PAGES) : 1;
    if (pages > 1 || img.get_typeof(VIPS_META_N_PAGES)) {
        m.set("pages", Variant((zend_long) pages));
        m.set("pageHeight", Variant((zend_long) ph));
    }
    if (img.get_typeof("loop")) m.set("loop", Variant((zend_long) img.get_int("loop")));
    if (img.get_typeof("delay")) {
        Array d;
        for (int v : img.get_array_int("delay")) d.append(Variant((zend_long) v));
        m.set("delay", d);
    }
    if (img.get_typeof("background")) {
        Array bg;
        for (double v : img.get_array_double("background")) bg.append(Variant(v));
        m.set("background", bg);
    }
    m.set("hasProfile", Variant(img.get_typeof(VIPS_META_ICC_NAME) != 0));
    m.set("hasAlpha", Variant(img.has_alpha()));
    int orientation = img.get_typeof(VIPS_META_ORIENTATION) ? img.get_int(VIPS_META_ORIENTATION) : 1;
    if (orientation != 1 || img.get_typeof(VIPS_META_ORIENTATION)) m.set("orientation", Variant((zend_long) orientation));
    Array ao;
    bool swap = orientation >= 5 && orientation <= 8;
    ao.set("width", Variant((zend_long) (swap ? ph : img.width())));
    ao.set("height", Variant((zend_long) (swap ? img.width() : ph)));
    m.set("autoOrient", ao);
    setBlob(m, img, VIPS_META_EXIF_NAME, "exif");
    setBlob(m, img, VIPS_META_ICC_NAME, "icc");
    setBlob(m, img, VIPS_META_IPTC_NAME, "iptc");
    setBlob(m, img, VIPS_META_XMP_NAME, "xmp");
    if (img.get_typeof("gainmap-data")) m.set("hasGainMap", Variant(true));
    return m;
    PIXELFORGE_CATCH(Array())
}

Array php_pixelforge_stats(Variant h) {
    TrimGuard trim;
    PIXELFORGE_TRY ImageBox *b = box(h);
    if (!b) return Array();
    VImage img = run(*b).copy_memory();
    VImage st = img.stats();
    Array channels;
    for (int band = 1; band < st.height(); band++) {
        std::vector<double> row;
        for (int col = 0; col < 10; col++) row.push_back(st.getpoint(col, band)[0]);
        Array c;
        c.set("min", Variant(row[0]));
        c.set("max", Variant(row[1]));
        c.set("sum", Variant(row[2]));
        c.set("squaresSum", Variant(row[3]));
        c.set("mean", Variant(row[4]));
        c.set("stdev", Variant(row[5]));
        c.set("minX", Variant((zend_long) row[6]));
        c.set("minY", Variant((zend_long) row[7]));
        c.set("maxX", Variant((zend_long) row[8]));
        c.set("maxY", Variant((zend_long) row[9]));
        channels.append(c);
    }
    Array out;
    out.set("channels", channels);
    bool opaque = true;
    if (img.has_alpha()) opaque = st.getpoint(0, img.bands())[0] >= maxAlpha(img);
    out.set("isOpaque", Variant(opaque));
    VImage grey = removeAlpha(img).colourspace(VIPS_INTERPRETATION_B_W);
    if (grey.format() != VIPS_FORMAT_UCHAR) grey = grey.cast(VIPS_FORMAT_UCHAR);
    out.set("entropy", Variant(grey.hist_find().hist_entropy()));
    VImage lap = VImage::new_matrixv(3, 3, -1.0, -1.0, -1.0, -1.0, 8.0, -1.0, -1.0, -1.0, -1.0);
    lap.set("scale", 9.0);
    out.set("sharpness", Variant(grey.conv(lap).deviate()));
    // dominant colour: 16x16x16 RGB histogram
    VImage rgb = removeAlpha(img);
    if (rgb.bands() < 3) rgb = rgb.colourspace(VIPS_INTERPRETATION_sRGB);
    if (rgb.format() != VIPS_FORMAT_UCHAR) rgb = rgb.cast(VIPS_FORMAT_UCHAR);
    VImage hist = rgb.extract_band(0, VImage::option()->set("n", 3)).hist_find_ndim(VImage::option()->set("bins", 16));
    size_t len = 0;
    unsigned int *hv = (unsigned int *) hist.cast(VIPS_FORMAT_UINT).write_to_memory(&len);
    size_t best = 0;
    for (size_t i = 1; i < len / sizeof(unsigned int); i++) {
        if (hv[i] > hv[best]) best = i;
    }
    g_free(hv);
    // memory layout: y (G) * width * bands + x (R) * bands + band (B)
    int bbin = (int) (best % 16), rbin = (int) ((best / 16) % 16), gbin = (int) (best / 256);
    Array dom;
    dom.set("r", Variant((zend_long) (rbin * 16 + 8)));
    dom.set("g", Variant((zend_long) (gbin * 16 + 8)));
    dom.set("b", Variant((zend_long) (bbin * 16 + 8)));
    out.set("dominant", dom);
    return out;
    PIXELFORGE_CATCH(Array())
}

// ================================================================= global config
Bool php_pixelforge_concurrency(Int n) {
    PIXELFORGE_TRY ensureInit();
    g_userThreads = std::max(0, (int) n);
    vips_concurrency_set(g_userThreads > 0 ? g_userThreads : g_maxThreads);
    return true;
    PIXELFORGE_CATCH(false)
}

Int php_pixelforge_get_concurrency() {
    PIXELFORGE_TRY ensureInit();
    return g_userThreads > 0 ? g_userThreads : g_maxThreads;
    PIXELFORGE_CATCH(0)
}

Bool php_pixelforge_cache(Int memoryMb, Int files, Int items) {
    PIXELFORGE_TRY ensureInit();
    vips_cache_set_max_mem((size_t) memoryMb * 1024 * 1024);
    vips_cache_set_max_files((int) files);
    vips_cache_set_max((int) items);
    return true;
    PIXELFORGE_CATCH(false)
}

Array php_pixelforge_versions() {
    PIXELFORGE_TRY ensureInit();
    Array v;
    v.set("vips", String(vips_version_string()));
    return v;
    PIXELFORGE_CATCH(Array())
}

/** heifsave can exist without an encoder plugin for a codec: probe by encoding a tiny image (cached). */
static bool canEncodeHeif(VipsForeignHeifCompression compression) {
    static int cache[2] = {-1, -1};
    int &c = cache[compression == VIPS_FOREIGN_HEIF_COMPRESSION_AV1 ? 0 : 1];
    if (c < 0) {
        c = 0;
        if (vips_type_find("VipsOperation", "heifsave_buffer")) {
            try {
                VImage px = VImage::black(8, 8, VImage::option()->set("bands", 3)).cast(VIPS_FORMAT_UCHAR).copy(
                    VImage::option()->set("interpretation", (int) VIPS_INTERPRETATION_sRGB));
                VipsBlob *blob = px.heifsave_buffer(VImage::option()->set("compression", (int) compression)->set("effort", 0));
                if (blob) vips_area_unref(VIPS_AREA(blob));
                c = 1;
            } catch (const std::exception &) {
                vips_error_clear();
            }
        }
    }
    return c == 1;
}

Array php_pixelforge_formats() {
    PIXELFORGE_TRY ensureInit();
    Array f;
    struct F {
        const char *name, *load, *save;
    };
    const F list[] = {{"jpeg", "jpegload", "jpegsave"}, {"png", "pngload", "pngsave"},   {"webp", "webpload", "webpsave"},
                      {"gif", "gifload", "gifsave"},    {"tiff", "tiffload", "tiffsave"}, {"heif", "heifload", "heifsave"},
                      {"avif", "heifload", "heifsave"}, {"jxl", "jxlload", "jxlsave"},    {"svg", "svgload", nullptr},
                      {"pdf", "pdfload", nullptr},      {"jp2k", "jp2kload", "jp2ksave"}, {"dz", nullptr, "dzsave"},
                      {"raw", nullptr, nullptr}};
    for (const F &x : list) {
        Array e;
        std::string name = x.name;
        bool out = x.save ? vips_type_find("VipsOperation", x.save) != 0 : name == "raw";
        if (name == "avif") out = canEncodeHeif(VIPS_FOREIGN_HEIF_COMPRESSION_AV1);
        if (name == "heif") out = canEncodeHeif(VIPS_FOREIGN_HEIF_COMPRESSION_AV1) || canEncodeHeif(VIPS_FOREIGN_HEIF_COMPRESSION_HEVC);
        e.set("input", Variant(x.load ? vips_type_find("VipsOperation", x.load) != 0 : name == "raw"));
        e.set("output", Variant(out));
        f.set(x.name, e);
    }
    return f;
    PIXELFORGE_CATCH(Array())
}

Array php_pixelforge_memory() {
    PIXELFORGE_TRY ensureInit();
    Array m;
    m.set("current", Variant((zend_long) vips_tracked_get_mem()));
    m.set("high", Variant((zend_long) vips_tracked_get_mem_highwater()));
    m.set("allocations", Variant((zend_long) vips_tracked_get_allocs()));
    m.set("files", Variant((zend_long) vips_tracked_get_files()));
    return m;
    PIXELFORGE_CATCH(Array())
}
