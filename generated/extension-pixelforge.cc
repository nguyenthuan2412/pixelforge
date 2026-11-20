#include <cstring>
#include <phpx.h>
#include <phpx_helper.h>
#include <phpx_big_int.h>
#include <phpx_big_float.h>
#include <phpx_decimal.h>
#include <phpx_python.h>
#include <typephp_helper.h>
#include <typephp_fiber_generator.h>
#include <phpx_std.h>
#include <php_pixelforge_runtime_decl.h>
#include <php_pixelforge_src_pixelforge_7188de8b65_decl.h>
#include <php_pixelforge_src_Image_8bd677063f_decl.h>
#include <php_src_Image_arginfo.h>
#include <php_src_pixelforge_arginfo.h>
#include <new>
namespace typephp_project_pixelforge {

// global vars 
// class register functions 
static zend_class_entry *php_class_entry_RuntimeException = nullptr;
static zend_class_entry *php_class_entry_PixelForge_PixelForgeException = nullptr;
static zend_class_entry *php_class_entry_PixelForge_Image = nullptr;
static zend_class_entry *php_class_entry_PixelForge_Gravity = nullptr;
static zend_class_entry *php_class_entry_PixelForge_Color = nullptr;
static zend_class_entry *php_class_entry_PixelForge_PixelForge = nullptr;
// request-local caches 
struct php_request_cache_storage final {
    php_request_cache_storage() = default;
    php_request_cache_storage(const php_request_cache_storage &) = delete;
    php_request_cache_storage(php_request_cache_storage &&) = delete;
    php_request_cache_storage &operator=(const php_request_cache_storage &) = delete;
    php_request_cache_storage &operator=(php_request_cache_storage &&) = delete;
    zend_class_entry *class_map[1]{};
    zend_function *func_map[12]{};
    php::PropertyCacheSlot property_cache_map[1]{};
    php::MethodCallCacheSlot method_call_cache_map[1]{};
    php::FunctionCallCacheSlot function_call_cache_map[1]{};
    uint8_t function_resolution_cache_map[33]{};
};
static THREAD_LOCAL php_request_cache_storage *php_request_cache = nullptr;
// class entry 
static php::PersistentCacheSlot<zend_class_entry *> php_persistent_class_map[4]{};
// func 
static php::PersistentCacheSlot<zend_function *> php_persistent_func_map[14]{};
// property 
static php::PersistentCacheSlot<uint32_t> php_persistent_property_map[2]{};
// functions 
zend_class_entry *get_class(RequestClassId class_id, const php::Str &class_name) {
    const auto index = static_cast<uint32_t>(class_id);
    auto &slot = php_request_cache->class_map[index];
    if (UNEXPECTED(slot == nullptr)) {
        slot = php::getClassEntrySafe(class_name);
    }
    return slot;
}

zend_function *get_func(RequestFuncId func_id, const php::Str &func_name) {
    const auto index = static_cast<uint32_t>(func_id);
    auto &slot = php_request_cache->func_map[index];
    if (UNEXPECTED(slot == nullptr)) {
        slot = php::getFunction(func_name);
    }
    return slot;
}

zend_function *get_method(RequestFuncId func_id, const php::Str &method_name, RequestClassId class_id, const php::Str &class_name) {
    const auto index = static_cast<uint32_t>(func_id);
    auto &slot = php_request_cache->func_map[index];
    if (UNEXPECTED(slot == nullptr)) {
        auto ce = get_class(class_id, class_name);
        slot = php::getMethod(ce, method_name);
    }
    return slot;
}

zend_class_entry *get_persistent_class(PersistentClassId class_id, const php::Str &class_name) {
    const auto index = static_cast<uint32_t>(class_id);
    return php::getPersistentCache(php_persistent_class_map[index], [&]() {
        return php::getClassEntrySafe(class_name);
    });
}

zend_function *get_persistent_func(PersistentFuncId func_id, const php::Str &func_name) {
    const auto index = static_cast<uint32_t>(func_id);
    return php::getPersistentCache(php_persistent_func_map[index], [&]() {
        return php::getFunction(func_name);
    });
}

zend_function *get_persistent_method(PersistentFuncId func_id, const php::Str &method_name, PersistentClassId class_id, const php::Str &class_name) {
    const auto index = static_cast<uint32_t>(func_id);
    return php::getPersistentCache(php_persistent_func_map[index], [&]() {
        auto ce = get_persistent_class(class_id, class_name);
        return php::getMethod(ce, method_name);
    });
}

uint32_t get_persistent_prop(PersistentPropertyId prop_id, const php::Str &prop_name, const php::Str &class_name) {
    const auto index = static_cast<uint32_t>(prop_id);
    auto value = php::getPersistentCache(php_persistent_property_map[index], [&]() {
        return php::getPropertyOffset(class_name, prop_name) + 1024;
    });
    return value - 1024;
}

php::PropertyCacheSlot &get_property_cache(PropertyCacheId cache_id) noexcept {
    return php_request_cache->property_cache_map[static_cast<uint32_t>(cache_id)];
}

php::MethodCallCacheSlot &get_method_call_cache(MethodCallCacheId cache_id) noexcept {
    return php_request_cache->method_call_cache_map[static_cast<uint32_t>(cache_id)];
}

php::FunctionCallCacheSlot &get_function_call_cache(FunctionCallCacheId cache_id) noexcept {
    return php_request_cache->function_call_cache_map[static_cast<uint32_t>(cache_id)];
}

uint8_t &get_function_resolution_cache(FunctionResolutionCacheId cache_id) noexcept {
    return php_request_cache->function_resolution_cache_map[static_cast<uint32_t>(cache_id)];
}

// literal strings 
static php::Str _literal_strings[] = {
php::Str{ZEND_STRL("h"), true}, // [0]
php::Str{ZEND_STRL("PixelForge\\Image"), true}, // [1]
php::Str{ZEND_STRL("failOn"), true}, // [2]
php::Str{ZEND_STRL("warning"), true}, // [3]
php::Str{ZEND_STRL("autoOrient"), true}, // [4]
php::Str{ZEND_STRL("page"), true}, // [5]
php::Str{ZEND_STRL("density"), true}, // [6]
php::Str{ZEND_STRL("unlimited"), true}, // [7]
php::Str{ZEND_STRL("ignoreIcc"), true}, // [8]
php::Str{ZEND_STRL("raw"), true}, // [9]
php::Str{ZEND_STRL("width"), true}, // [10]
php::Str{ZEND_STRL("height"), true}, // [11]
php::Str{ZEND_STRL("channels"), true}, // [12]
php::Str{ZEND_STRL("depth"), true}, // [13]
php::Str{ZEND_STRL("uchar"), true}, // [14]
php::Str{ZEND_STRL("premultiplied"), true}, // [15]
php::Str{ZEND_STRL("background"), true}, // [16]
php::Str{ZEND_STRL("noise"), true}, // [17]
php::Str{ZEND_STRL("pixelforge_create"), true}, // [18]
php::Str{ZEND_STRL("r"), true}, // [19]
php::Str{ZEND_STRL("g"), true}, // [20]
php::Str{ZEND_STRL("b"), true}, // [21]
php::Str{ZEND_STRL("a"), true}, // [22]
php::Str{ZEND_STRL("type"), true}, // [23]
php::Str{ZEND_STRL("mean"), true}, // [24]
php::Str{ZEND_STRL("sigma"), true}, // [25]
php::Str{ZEND_STRL("PixelForge\\Color"), true}, // [26]
php::Str{ZEND_STRL("text"), true}, // [27]
php::Str{ZEND_STRL("font"), true}, // [28]
php::Str{ZEND_STRL("fontfile"), true}, // [29]
php::Str{ZEND_STRL("align"), true}, // [30]
php::Str{ZEND_STRL("left"), true}, // [31]
php::Str{ZEND_STRL("justify"), true}, // [32]
php::Str{ZEND_STRL("dpi"), true}, // [33]
php::Str{ZEND_STRL("rgba"), true}, // [34]
php::Str{ZEND_STRL("spacing"), true}, // [35]
php::Str{ZEND_STRL("wrap"), true}, // [36]
php::Str{ZEND_STRL("word"), true}, // [37]
php::Str{ZEND_STRL("animated"), true}, // [38]
php::Str{ZEND_STRL("across"), true}, // [39]
php::Str{ZEND_STRL("shim"), true}, // [40]
php::Str{ZEND_STRL("pixelforge_join_new"), true}, // [41]
php::Str{ZEND_STRL("halign"), true}, // [42]
php::Str{ZEND_STRL("valign"), true}, // [43]
php::Str{ZEND_STRL("top"), true}, // [44]
php::Str{ZEND_STRL("handle"), true}, // [45]
php::Str{ZEND_STRL("PixelForge\\is_array"), true}, // [46]
php::Str{ZEND_STRL("is_array"), true}, // [47]
php::Str{ZEND_STRL("create"), true}, // [48]
php::Str{ZEND_STRL("input"), true}, // [49]
php::Str{ZEND_STRL("PixelForge\\strlen"), true}, // [50]
php::Str{ZEND_STRL("strlen"), true}, // [51]
php::Str{ZEND_STRL("PixelForge\\str_contains"), true}, // [52]
php::Str{ZEND_STRL("str_contains"), true}, // [53]
php::Str{ZEND_STRL("\000"), true}, // [54]
php::Str{ZEND_STRL("PixelForge\\is_file"), true}, // [55]
php::Str{ZEND_STRL("is_file"), true}, // [56]
php::Str{ZEND_STRL("limitInputPixels"), true}, // [57]
php::Str{ZEND_STRL("pages"), true}, // [58]
php::Str{ZEND_STRL("keepFlags"), true}, // [59]
php::Str{ZEND_STRL("position"), true}, // [60]
php::Str{ZEND_STRL("gravity"), true}, // [61]
php::Str{ZEND_STRL("centre"), true}, // [62]
php::Str{ZEND_STRL("fit"), true}, // [63]
php::Str{ZEND_STRL("cover"), true}, // [64]
php::Str{ZEND_STRL("pixelforge_resize"), true}, // [65]
php::Str{ZEND_STRL("withoutEnlargement"), true}, // [66]
php::Str{ZEND_STRL("withoutReduction"), true}, // [67]
php::Str{ZEND_STRL("kernel"), true}, // [68]
php::Str{ZEND_STRL("lanczos3"), true}, // [69]
php::Str{ZEND_STRL("fastShrinkOnLoad"), true}, // [70]
php::Str{ZEND_STRL("PixelForge\\Gravity"), true}, // [71]
php::Str{ZEND_STRL("PixelForge\\Image::resize"), true}, // [72]
php::Str{ZEND_STRL("?int"), true}, // [73]
php::Str{ZEND_STRL("PixelForge\\is_int"), true}, // [74]
php::Str{ZEND_STRL("is_int"), true}, // [75]
php::Str{ZEND_STRL("bottom"), true}, // [76]
php::Str{ZEND_STRL("right"), true}, // [77]
php::Str{ZEND_STRL("extendWith"), true}, // [78]
php::Str{ZEND_STRL("pixelforge_extend"), true}, // [79]
php::Str{ZEND_STRL("PixelForge\\Image::extend"), true}, // [80]
php::Str{ZEND_STRL("extend"), true}, // [81]
php::Str{ZEND_STRL("int|array"), true}, // [82]
php::Str{ZEND_STRL("threshold"), true}, // [83]
php::Str{ZEND_STRL("pixelforge_trim"), true}, // [84]
php::Str{ZEND_STRL("lineArt"), true}, // [85]
php::Str{ZEND_STRL("pixelforge_rotate"), true}, // [86]
php::Str{ZEND_STRL("angle"), true}, // [87]
php::Str{ZEND_STRL("PixelForge\\Image::rotate"), true}, // [88]
php::Str{ZEND_STRL("?float"), true}, // [89]
php::Str{ZEND_STRL("pixelforge_affine"), true}, // [90]
php::Str{ZEND_STRL("bl"), true}, // [91]
php::Str{ZEND_STRL("al"), true}, // [92]
php::Str{ZEND_STRL("interpolator"), true}, // [93]
php::Str{ZEND_STRL("bicubic"), true}, // [94]
php::Str{ZEND_STRL("idx"), true}, // [95]
php::Str{ZEND_STRL("idy"), true}, // [96]
php::Str{ZEND_STRL("odx"), true}, // [97]
php::Str{ZEND_STRL("ody"), true}, // [98]
php::Str{ZEND_STRL("m1"), true}, // [99]
php::Str{ZEND_STRL("m2"), true}, // [100]
php::Str{ZEND_STRL("x1"), true}, // [101]
php::Str{ZEND_STRL("y2"), true}, // [102]
php::Str{ZEND_STRL("y3"), true}, // [103]
php::Str{ZEND_STRL("precision"), true}, // [104]
php::Str{ZEND_STRL("integer"), true}, // [105]
php::Str{ZEND_STRL("minAmplitude"), true}, // [106]
php::Str{ZEND_STRL("PixelForge\\Image::blur"), true}, // [107]
php::Str{ZEND_STRL("float|array"), true}, // [108]
php::Str{ZEND_STRL("pixelforge_flatten"), true}, // [109]
php::Str{ZEND_STRL("PixelForge\\Image::gamma"), true}, // [110]
php::Str{ZEND_STRL("gammaOut"), true}, // [111]
php::Str{ZEND_STRL("alpha"), true}, // [112]
php::Str{ZEND_STRL("lower"), true}, // [113]
php::Str{ZEND_STRL("upper"), true}, // [114]
php::Str{ZEND_STRL("normalise"), true}, // [115]
php::Str{ZEND_STRL("maxSlope"), true}, // [116]
php::Str{ZEND_STRL("greyscale"), true}, // [117]
php::Str{ZEND_STRL("grayscale"), true}, // [118]
php::Str{ZEND_STRL("PixelForge\\Image::linear"), true}, // [119]
php::Str{ZEND_STRL("brightness"), true}, // [120]
php::Str{ZEND_STRL("saturation"), true}, // [121]
php::Str{ZEND_STRL("hue"), true}, // [122]
php::Str{ZEND_STRL("lightness"), true}, // [123]
php::Str{ZEND_STRL("pixelforge_tint"), true}, // [124]
php::Str{ZEND_STRL("b-w"), true}, // [125]
php::Str{ZEND_STRL("toColourspace"), true}, // [126]
php::Str{ZEND_STRL("PixelForge\\is_string"), true}, // [127]
php::Str{ZEND_STRL("is_string"), true}, // [128]
php::Str{ZEND_STRL("red"), true}, // [129]
php::Str{ZEND_STRL("green"), true}, // [130]
php::Str{ZEND_STRL("blue"), true}, // [131]
php::Str{ZEND_STRL("Invalid channel: "), true}, // [132]
php::Str{ZEND_STRL("pixelforge_extract_channel"), true}, // [133]
php::Str{ZEND_STRL("channel"), true}, // [134]
php::Str{ZEND_STRL("InvalidArgumentException"), true}, // [135]
php::Str{ZEND_STRL("PixelForge\\Image::extractChannel"), true}, // [136]
php::Str{ZEND_STRL("int|string"), true}, // [137]
php::Str{ZEND_STRL("scale"), true}, // [138]
php::Str{ZEND_STRL("offset"), true}, // [139]
php::Str{ZEND_STRL("blend"), true}, // [140]
php::Str{ZEND_STRL("over"), true}, // [141]
php::Str{ZEND_STRL("tile"), true}, // [142]
php::Str{ZEND_STRL("output"), true}, // [143]
php::Str{ZEND_STRL("jpeg"), true}, // [144]
php::Str{ZEND_STRL("png"), true}, // [145]
php::Str{ZEND_STRL("webp"), true}, // [146]
php::Str{ZEND_STRL("avif"), true}, // [147]
php::Str{ZEND_STRL("heif"), true}, // [148]
php::Str{ZEND_STRL("gif"), true}, // [149]
php::Str{ZEND_STRL("tiff"), true}, // [150]
php::Str{ZEND_STRL("jxl"), true}, // [151]
php::Str{ZEND_STRL("quality"), true}, // [152]
php::Str{ZEND_STRL("lossless"), true}, // [153]
php::Str{ZEND_STRL("effort"), true}, // [154]
php::Str{ZEND_STRL("progressive"), true}, // [155]
php::Str{ZEND_STRL("interlace"), true}, // [156]
php::Str{ZEND_STRL("chromaSubsampling"), true}, // [157]
php::Str{ZEND_STRL("mozjpeg"), true}, // [158]
php::Str{ZEND_STRL("compressionLevel"), true}, // [159]
php::Str{ZEND_STRL("palette"), true}, // [160]
php::Str{ZEND_STRL("colours"), true}, // [161]
php::Str{ZEND_STRL("colors"), true}, // [162]
php::Str{ZEND_STRL("dither"), true}, // [163]
php::Str{ZEND_STRL("adaptiveFiltering"), true}, // [164]
php::Str{ZEND_STRL("nearLossless"), true}, // [165]
php::Str{ZEND_STRL("smartSubsample"), true}, // [166]
php::Str{ZEND_STRL("alphaQuality"), true}, // [167]
php::Str{ZEND_STRL("bitdepth"), true}, // [168]
php::Str{ZEND_STRL("compression"), true}, // [169]
php::Str{ZEND_STRL("predictor"), true}, // [170]
php::Str{ZEND_STRL("tileWidth"), true}, // [171]
php::Str{ZEND_STRL("tileHeight"), true}, // [172]
php::Str{ZEND_STRL("pyramid"), true}, // [173]
php::Str{ZEND_STRL("loop"), true}, // [174]
php::Str{ZEND_STRL("delay"), true}, // [175]
php::Str{ZEND_STRL("minSize"), true}, // [176]
php::Str{ZEND_STRL("mixed"), true}, // [177]
php::Str{ZEND_STRL("interFrameMaxError"), true}, // [178]
php::Str{ZEND_STRL("interPaletteMaxError"), true}, // [179]
php::Str{ZEND_STRL("reuse"), true}, // [180]
php::Str{ZEND_STRL("optimiseCoding"), true}, // [181]
php::Str{ZEND_STRL("optimizeCoding"), true}, // [182]
php::Str{ZEND_STRL("#ffffff"), true}, // [183]
php::Str{ZEND_STRL("size"), true}, // [184]
php::Str{ZEND_STRL("overlap"), true}, // [185]
php::Str{ZEND_STRL("layout"), true}, // [186]
php::Str{ZEND_STRL("dz"), true}, // [187]
php::Str{ZEND_STRL("container"), true}, // [188]
php::Str{ZEND_STRL("fs"), true}, // [189]
php::Str{ZEND_STRL("skipBlanks"), true}, // [190]
php::Str{ZEND_STRL("center"), true}, // [191]
php::Str{ZEND_STRL("basename"), true}, // [192]
php::Str{ZEND_STRL("id"), true}, // [193]
php::Str{ZEND_STRL("pixelforge_tile"), true}, // [194]
php::Str{ZEND_STRL("seconds"), true}, // [195]
php::Str{ZEND_STRL("keep"), true}, // [196]
php::Str{ZEND_STRL("keepMetadata"), true}, // [197]
php::Str{ZEND_STRL("\037"), true}, // [198]
php::Str{ZEND_STRL("PixelForge\\implode"), true}, // [199]
php::Str{ZEND_STRL("implode"), true}, // [200]
php::Str{ZEND_STRL("\036"), true}, // [201]
php::Str{ZEND_STRL("PixelForge\\Image::flattenExif"), true}, // [202]
php::Str{ZEND_STRL("string"), true}, // [203]
php::Str{ZEND_STRL("data"), true}, // [204]
php::Str{ZEND_STRL("PixelForge\\Image::toBuffer"), true}, // [205]
php::Str{ZEND_STRL("format"), true}, // [206]
php::Str{ZEND_STRL("?string"), true}, // [207]
php::Str{ZEND_STRL("PixelForge\\Image::toBufferWithInfo"), true}, // [208]
php::Str{ZEND_STRL(","), true}, // [209]
php::Str{ZEND_STRL("PixelForge\\Image::csv"), true}, // [210]
php::Str{ZEND_STRL("PixelForge\\strtolower"), true}, // [211]
php::Str{ZEND_STRL("strtolower"), true}, // [212]
php::Str{ZEND_STRL("PixelForge\\trim"), true}, // [213]
php::Str{ZEND_STRL("trim"), true}, // [214]
php::Str{ZEND_STRL("north"), true}, // [215]
php::Str{ZEND_STRL("northeast"), true}, // [216]
php::Str{ZEND_STRL("right top"), true}, // [217]
php::Str{ZEND_STRL("top right"), true}, // [218]
php::Str{ZEND_STRL("east"), true}, // [219]
php::Str{ZEND_STRL("southeast"), true}, // [220]
php::Str{ZEND_STRL("right bottom"), true}, // [221]
php::Str{ZEND_STRL("bottom right"), true}, // [222]
php::Str{ZEND_STRL("south"), true}, // [223]
php::Str{ZEND_STRL("southwest"), true}, // [224]
php::Str{ZEND_STRL("left bottom"), true}, // [225]
php::Str{ZEND_STRL("bottom left"), true}, // [226]
php::Str{ZEND_STRL("west"), true}, // [227]
php::Str{ZEND_STRL("northwest"), true}, // [228]
php::Str{ZEND_STRL("left top"), true}, // [229]
php::Str{ZEND_STRL("top left"), true}, // [230]
php::Str{ZEND_STRL("PixelForge\\Gravity::normalise"), true}, // [231]
php::Str{ZEND_STRL("transparent"), true}, // [232]
php::Str{ZEND_STRL("ffffff"), true}, // [233]
php::Str{ZEND_STRL("white"), true}, // [234]
php::Str{ZEND_STRL("000000"), true}, // [235]
php::Str{ZEND_STRL("black"), true}, // [236]
php::Str{ZEND_STRL("ff0000"), true}, // [237]
php::Str{ZEND_STRL("00ff00"), true}, // [238]
php::Str{ZEND_STRL("lime"), true}, // [239]
php::Str{ZEND_STRL("008000"), true}, // [240]
php::Str{ZEND_STRL("0000ff"), true}, // [241]
php::Str{ZEND_STRL("ffff00"), true}, // [242]
php::Str{ZEND_STRL("yellow"), true}, // [243]
php::Str{ZEND_STRL("00ffff"), true}, // [244]
php::Str{ZEND_STRL("cyan"), true}, // [245]
php::Str{ZEND_STRL("aqua"), true}, // [246]
php::Str{ZEND_STRL("ff00ff"), true}, // [247]
php::Str{ZEND_STRL("magenta"), true}, // [248]
php::Str{ZEND_STRL("fuchsia"), true}, // [249]
php::Str{ZEND_STRL("808080"), true}, // [250]
php::Str{ZEND_STRL("gray"), true}, // [251]
php::Str{ZEND_STRL("grey"), true}, // [252]
php::Str{ZEND_STRL("c0c0c0"), true}, // [253]
php::Str{ZEND_STRL("silver"), true}, // [254]
php::Str{ZEND_STRL("800000"), true}, // [255]
php::Str{ZEND_STRL("maroon"), true}, // [256]
php::Str{ZEND_STRL("808000"), true}, // [257]
php::Str{ZEND_STRL("olive"), true}, // [258]
php::Str{ZEND_STRL("000080"), true}, // [259]
php::Str{ZEND_STRL("navy"), true}, // [260]
php::Str{ZEND_STRL("008080"), true}, // [261]
php::Str{ZEND_STRL("teal"), true}, // [262]
php::Str{ZEND_STRL("800080"), true}, // [263]
php::Str{ZEND_STRL("purple"), true}, // [264]
php::Str{ZEND_STRL("ffa500"), true}, // [265]
php::Str{ZEND_STRL("orange"), true}, // [266]
php::Str{ZEND_STRL("ffc0cb"), true}, // [267]
php::Str{ZEND_STRL("pink"), true}, // [268]
php::Str{ZEND_STRL("a52a2a"), true}, // [269]
php::Str{ZEND_STRL("brown"), true}, // [270]
php::Str{ZEND_STRL("ffd700"), true}, // [271]
php::Str{ZEND_STRL("gold"), true}, // [272]
php::Str{ZEND_STRL("4b0082"), true}, // [273]
php::Str{ZEND_STRL("indigo"), true}, // [274]
php::Str{ZEND_STRL("ee82ee"), true}, // [275]
php::Str{ZEND_STRL("violet"), true}, // [276]
php::Str{ZEND_STRL("d3d3d3"), true}, // [277]
php::Str{ZEND_STRL("lightgray"), true}, // [278]
php::Str{ZEND_STRL("lightgrey"), true}, // [279]
php::Str{ZEND_STRL("a9a9a9"), true}, // [280]
php::Str{ZEND_STRL("darkgray"), true}, // [281]
php::Str{ZEND_STRL("darkgrey"), true}, // [282]
php::Str{ZEND_STRL("PixelForge\\str_starts_with"), true}, // [283]
php::Str{ZEND_STRL("str_starts_with"), true}, // [284]
php::Str{ZEND_STRL("#"), true}, // [285]
php::Str{ZEND_STRL("PixelForge\\substr"), true}, // [286]
php::Str{ZEND_STRL("substr"), true}, // [287]
php::Str{ZEND_STRL("PixelForge\\preg_match"), true}, // [288]
php::Str{ZEND_STRL("preg_match"), true}, // [289]
php::Str{ZEND_STRL("/^[0-9a-f]+$/"), true}, // [290]
php::Str{ZEND_STRL("Invalid colour: "), true}, // [291]
php::Str{ZEND_STRL("PixelForge\\hexdec"), true}, // [292]
php::Str{ZEND_STRL("hexdec"), true}, // [293]
php::Str{ZEND_STRL("pixelforge_concurrency"), true}, // [294]
php::Str{ZEND_STRL("n"), true}, // [295]
php::Str{ZEND_STRL("PixelForge\\PixelForge::concurrency"), true}, // [296]
php::Str{ZEND_STRL("PixelForge\\Image::fromFile"), true}, // [297]
php::Str{ZEND_STRL("path"), true}, // [298]
php::Str{ZEND_STRL("PixelForge\\Image::fromBuffer"), true}, // [299]
php::Str{ZEND_STRL("PixelForge\\Image::fromRaw"), true}, // [300]
php::Str{ZEND_STRL("PixelForge\\Image::median"), true}, // [301]
php::Str{ZEND_STRL("int"), true}, // [302]
php::Str{ZEND_STRL("gamma"), true}, // [303]
php::Str{ZEND_STRL("float"), true}, // [304]
php::Str{ZEND_STRL("PixelForge\\Image::threshold"), true}, // [305]
php::Str{ZEND_STRL("PixelForge\\Image::greyscale"), true}, // [306]
php::Str{ZEND_STRL("bool"), true}, // [307]
php::Str{ZEND_STRL("PixelForge\\Image::grayscale"), true}, // [308]
php::Str{ZEND_STRL("PixelForge\\Image::toColourspace"), true}, // [309]
php::Str{ZEND_STRL("space"), true}, // [310]
php::Str{ZEND_STRL("PixelForge\\Image::toColorspace"), true}, // [311]
php::Str{ZEND_STRL("PixelForge\\Image::ensureAlpha"), true}, // [312]
php::Str{ZEND_STRL("PixelForge\\Image::bandbool"), true}, // [313]
php::Str{ZEND_STRL("op"), true}, // [314]
php::Str{ZEND_STRL("PixelForge\\Image::boolean"), true}, // [315]
php::Str{ZEND_STRL("PixelForge\\Image::dilate"), true}, // [316]
php::Str{ZEND_STRL("PixelForge\\Image::erode"), true}, // [317]
php::Str{ZEND_STRL("PixelForge\\Image::toFormat"), true}, // [318]
php::Str{ZEND_STRL("PixelForge\\Image::output"), true}, // [319]
php::Str{ZEND_STRL("PixelForge\\Image::withIccProfile"), true}, // [320]
php::Str{ZEND_STRL("profile"), true}, // [321]
php::Str{ZEND_STRL("PixelForge\\Image::keep"), true}, // [322]
php::Str{ZEND_STRL("flags"), true}, // [323]
php::Str{ZEND_STRL("PixelForge\\Image::toFile"), true}, // [324]
php::Str{ZEND_STRL("PixelForge\\PixelForge::cache"), true}, // [325]
php::Str{ZEND_STRL("memoryMb"), true}, // [326]
php::Str{ZEND_STRL("files"), true}, // [327]
php::Str{ZEND_STRL("items"), true}, // [328]
php::Str{ZEND_STRL("pixelforge_from_file"), true}, // [329]
php::Str{ZEND_STRL("limitPixels"), true}, // [330]
php::Str{ZEND_STRL("pixelforge_from_buffer"), true}, // [331]
php::Str{ZEND_STRL("pixelforge_from_raw"), true}, // [332]
php::Str{ZEND_STRL("pixelforge_text"), true}, // [333]
php::Str{ZEND_STRL("pixelforge_extract"), true}, // [334]
php::Str{ZEND_STRL("with"), true}, // [335]
php::Str{ZEND_STRL("useBackground"), true}, // [336]
php::Str{ZEND_STRL("c"), true}, // [337]
php::Str{ZEND_STRL("d"), true}, // [338]
php::Str{ZEND_STRL("pixelforge_sharpen"), true}, // [339]
php::Str{ZEND_STRL("pixelforge_median"), true}, // [340]
php::Str{ZEND_STRL("pixelforge_blur"), true}, // [341]
php::Str{ZEND_STRL("pixelforge_gamma"), true}, // [342]
php::Str{ZEND_STRL("pixelforge_negate"), true}, // [343]
php::Str{ZEND_STRL("pixelforge_normalise"), true}, // [344]
php::Str{ZEND_STRL("pixelforge_clahe"), true}, // [345]
php::Str{ZEND_STRL("pixelforge_threshold"), true}, // [346]
php::Str{ZEND_STRL("pixelforge_linear"), true}, // [347]
php::Str{ZEND_STRL("pixelforge_modulate"), true}, // [348]
php::Str{ZEND_STRL("pixelforge_colourspace"), true}, // [349]
php::Str{ZEND_STRL("pixelforge_ensure_alpha"), true}, // [350]
php::Str{ZEND_STRL("pixelforge_bandbool"), true}, // [351]
php::Str{ZEND_STRL("pixelforge_boolean"), true}, // [352]
php::Str{ZEND_STRL("pixelforge_dilate"), true}, // [353]
php::Str{ZEND_STRL("pixelforge_erode"), true}, // [354]
php::Str{ZEND_STRL("pixelforge_convolve"), true}, // [355]
php::Str{ZEND_STRL("pixelforge_recomb"), true}, // [356]
php::Str{ZEND_STRL("matrix"), true}, // [357]
php::Str{ZEND_STRL("pixelforge_composite"), true}, // [358]
php::Str{ZEND_STRL("pixelforge_output"), true}, // [359]
php::Str{ZEND_STRL("chroma"), true}, // [360]
php::Str{ZEND_STRL("interframeMaxError"), true}, // [361]
php::Str{ZEND_STRL("interpaletteMaxError"), true}, // [362]
php::Str{ZEND_STRL("pixelforge_keep"), true}, // [363]
php::Str{ZEND_STRL("pixelforge_icc"), true}, // [364]
php::Str{ZEND_STRL("pixelforge_exif"), true}, // [365]
php::Str{ZEND_STRL("flat"), true}, // [366]
php::Str{ZEND_STRL("merge"), true}, // [367]
php::Str{ZEND_STRL("pixelforge_timeout"), true}, // [368]
php::Str{ZEND_STRL("pixelforge_to_buffer"), true}, // [369]
php::Str{ZEND_STRL("pixelforge_to_file"), true}, // [370]
php::Str{ZEND_STRL("pixelforge_cache"), true}, // [371]
};

ZEND_ATTRIBUTE_CONST php::Str &get_str(uint32_t index) noexcept {
    return _literal_strings[index];
}

}  // namespace typephp_project_pixelforge

// native/import stub callbacks 
ZEND_FUNCTION(pixelforge_from_file) {
    PHPX_TRY {
        php::checkCallArgCount(9, 9, false);
        php::Var raw_arg_path = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_path.isString()))) {
            php::throwArgumentTypeError(raw_arg_path, get_str(329), 1, get_str(298), get_str(203));
        }
        php::Str arg_path = php::toString(raw_arg_path);
        php::Var raw_arg_failOn = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_failOn.isString()))) {
            php::throwArgumentTypeError(raw_arg_failOn, get_str(329), 2, get_str(2), get_str(203));
        }
        php::Str arg_failOn = php::toString(raw_arg_failOn);
        php::Var raw_arg_limitPixels = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_limitPixels.isInt()))) {
            php::throwArgumentTypeError(raw_arg_limitPixels, get_str(329), 3, get_str(330), get_str(302));
        }
        php::Int arg_limitPixels = php::toInt(raw_arg_limitPixels);
        php::Var raw_arg_autoOrient = php::getCallArg(3);
        if (UNEXPECTED(!(raw_arg_autoOrient.isBool()))) {
            php::throwArgumentTypeError(raw_arg_autoOrient, get_str(329), 4, get_str(4), get_str(307));
        }
        php::Bool arg_autoOrient = php::toBool(raw_arg_autoOrient);
        php::Var raw_arg_pages = php::getCallArg(4);
        if (UNEXPECTED(!(raw_arg_pages.isInt()))) {
            php::throwArgumentTypeError(raw_arg_pages, get_str(329), 5, get_str(58), get_str(302));
        }
        php::Int arg_pages = php::toInt(raw_arg_pages);
        php::Var raw_arg_page = php::getCallArg(5);
        if (UNEXPECTED(!(raw_arg_page.isInt()))) {
            php::throwArgumentTypeError(raw_arg_page, get_str(329), 6, get_str(5), get_str(302));
        }
        php::Int arg_page = php::toInt(raw_arg_page);
        php::Var raw_arg_density = php::getCallArg(6);
        if (UNEXPECTED(!((raw_arg_density.isFloat() || raw_arg_density.isInt())))) {
            php::throwArgumentTypeError(raw_arg_density, get_str(329), 7, get_str(6), get_str(304));
        }
        php::Float arg_density = php::toFloat(raw_arg_density);
        php::Var raw_arg_unlimited = php::getCallArg(7);
        if (UNEXPECTED(!(raw_arg_unlimited.isBool()))) {
            php::throwArgumentTypeError(raw_arg_unlimited, get_str(329), 8, get_str(7), get_str(307));
        }
        php::Bool arg_unlimited = php::toBool(raw_arg_unlimited);
        php::Var raw_arg_ignoreIcc = php::getCallArg(8);
        if (UNEXPECTED(!(raw_arg_ignoreIcc.isBool()))) {
            php::throwArgumentTypeError(raw_arg_ignoreIcc, get_str(329), 9, get_str(8), get_str(307));
        }
        php::Bool arg_ignoreIcc = php::toBool(raw_arg_ignoreIcc);
        auto retval = php_pixelforge_from_file(php::takeValue(arg_path),php::takeValue(arg_failOn),arg_limitPixels,arg_autoOrient,arg_pages,arg_page,arg_density,arg_unlimited,arg_ignoreIcc);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_from_buffer) {
    PHPX_TRY {
        php::checkCallArgCount(9, 9, false);
        php::Var raw_arg_data = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_data.isString()))) {
            php::throwArgumentTypeError(raw_arg_data, get_str(331), 1, get_str(204), get_str(203));
        }
        php::Str arg_data = php::toString(raw_arg_data);
        php::Var raw_arg_failOn = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_failOn.isString()))) {
            php::throwArgumentTypeError(raw_arg_failOn, get_str(331), 2, get_str(2), get_str(203));
        }
        php::Str arg_failOn = php::toString(raw_arg_failOn);
        php::Var raw_arg_limitPixels = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_limitPixels.isInt()))) {
            php::throwArgumentTypeError(raw_arg_limitPixels, get_str(331), 3, get_str(330), get_str(302));
        }
        php::Int arg_limitPixels = php::toInt(raw_arg_limitPixels);
        php::Var raw_arg_autoOrient = php::getCallArg(3);
        if (UNEXPECTED(!(raw_arg_autoOrient.isBool()))) {
            php::throwArgumentTypeError(raw_arg_autoOrient, get_str(331), 4, get_str(4), get_str(307));
        }
        php::Bool arg_autoOrient = php::toBool(raw_arg_autoOrient);
        php::Var raw_arg_pages = php::getCallArg(4);
        if (UNEXPECTED(!(raw_arg_pages.isInt()))) {
            php::throwArgumentTypeError(raw_arg_pages, get_str(331), 5, get_str(58), get_str(302));
        }
        php::Int arg_pages = php::toInt(raw_arg_pages);
        php::Var raw_arg_page = php::getCallArg(5);
        if (UNEXPECTED(!(raw_arg_page.isInt()))) {
            php::throwArgumentTypeError(raw_arg_page, get_str(331), 6, get_str(5), get_str(302));
        }
        php::Int arg_page = php::toInt(raw_arg_page);
        php::Var raw_arg_density = php::getCallArg(6);
        if (UNEXPECTED(!((raw_arg_density.isFloat() || raw_arg_density.isInt())))) {
            php::throwArgumentTypeError(raw_arg_density, get_str(331), 7, get_str(6), get_str(304));
        }
        php::Float arg_density = php::toFloat(raw_arg_density);
        php::Var raw_arg_unlimited = php::getCallArg(7);
        if (UNEXPECTED(!(raw_arg_unlimited.isBool()))) {
            php::throwArgumentTypeError(raw_arg_unlimited, get_str(331), 8, get_str(7), get_str(307));
        }
        php::Bool arg_unlimited = php::toBool(raw_arg_unlimited);
        php::Var raw_arg_ignoreIcc = php::getCallArg(8);
        if (UNEXPECTED(!(raw_arg_ignoreIcc.isBool()))) {
            php::throwArgumentTypeError(raw_arg_ignoreIcc, get_str(331), 9, get_str(8), get_str(307));
        }
        php::Bool arg_ignoreIcc = php::toBool(raw_arg_ignoreIcc);
        auto retval = php_pixelforge_from_buffer(php::takeValue(arg_data),php::takeValue(arg_failOn),arg_limitPixels,arg_autoOrient,arg_pages,arg_page,arg_density,arg_unlimited,arg_ignoreIcc);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_from_raw) {
    PHPX_TRY {
        php::checkCallArgCount(6, 6, false);
        php::Var raw_arg_data = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_data.isString()))) {
            php::throwArgumentTypeError(raw_arg_data, get_str(332), 1, get_str(204), get_str(203));
        }
        php::Str arg_data = php::toString(raw_arg_data);
        php::Var raw_arg_width = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_width.isInt()))) {
            php::throwArgumentTypeError(raw_arg_width, get_str(332), 2, get_str(10), get_str(302));
        }
        php::Int arg_width = php::toInt(raw_arg_width);
        php::Var raw_arg_height = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_height.isInt()))) {
            php::throwArgumentTypeError(raw_arg_height, get_str(332), 3, get_str(11), get_str(302));
        }
        php::Int arg_height = php::toInt(raw_arg_height);
        php::Var raw_arg_channels = php::getCallArg(3);
        if (UNEXPECTED(!(raw_arg_channels.isInt()))) {
            php::throwArgumentTypeError(raw_arg_channels, get_str(332), 4, get_str(12), get_str(302));
        }
        php::Int arg_channels = php::toInt(raw_arg_channels);
        php::Var raw_arg_depth = php::getCallArg(4);
        if (UNEXPECTED(!(raw_arg_depth.isString()))) {
            php::throwArgumentTypeError(raw_arg_depth, get_str(332), 5, get_str(13), get_str(203));
        }
        php::Str arg_depth = php::toString(raw_arg_depth);
        php::Var raw_arg_premultiplied = php::getCallArg(5);
        if (UNEXPECTED(!(raw_arg_premultiplied.isBool()))) {
            php::throwArgumentTypeError(raw_arg_premultiplied, get_str(332), 6, get_str(15), get_str(307));
        }
        php::Bool arg_premultiplied = php::toBool(raw_arg_premultiplied);
        auto retval = php_pixelforge_from_raw(php::takeValue(arg_data),arg_width,arg_height,arg_channels,php::takeValue(arg_depth),arg_premultiplied);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_create) {
    PHPX_TRY {
        php::checkCallArgCount(10, 10, false);
        php::Var raw_arg_width = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_width.isInt()))) {
            php::throwArgumentTypeError(raw_arg_width, get_str(18), 1, get_str(10), get_str(302));
        }
        php::Int arg_width = php::toInt(raw_arg_width);
        php::Var raw_arg_height = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_height.isInt()))) {
            php::throwArgumentTypeError(raw_arg_height, get_str(18), 2, get_str(11), get_str(302));
        }
        php::Int arg_height = php::toInt(raw_arg_height);
        php::Var raw_arg_channels = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_channels.isInt()))) {
            php::throwArgumentTypeError(raw_arg_channels, get_str(18), 3, get_str(12), get_str(302));
        }
        php::Int arg_channels = php::toInt(raw_arg_channels);
        php::Var raw_arg_r = php::getCallArg(3);
        if (UNEXPECTED(!((raw_arg_r.isFloat() || raw_arg_r.isInt())))) {
            php::throwArgumentTypeError(raw_arg_r, get_str(18), 4, get_str(19), get_str(304));
        }
        php::Float arg_r = php::toFloat(raw_arg_r);
        php::Var raw_arg_g = php::getCallArg(4);
        if (UNEXPECTED(!((raw_arg_g.isFloat() || raw_arg_g.isInt())))) {
            php::throwArgumentTypeError(raw_arg_g, get_str(18), 5, get_str(20), get_str(304));
        }
        php::Float arg_g = php::toFloat(raw_arg_g);
        php::Var raw_arg_b = php::getCallArg(5);
        if (UNEXPECTED(!((raw_arg_b.isFloat() || raw_arg_b.isInt())))) {
            php::throwArgumentTypeError(raw_arg_b, get_str(18), 6, get_str(21), get_str(304));
        }
        php::Float arg_b = php::toFloat(raw_arg_b);
        php::Var raw_arg_a = php::getCallArg(6);
        if (UNEXPECTED(!((raw_arg_a.isFloat() || raw_arg_a.isInt())))) {
            php::throwArgumentTypeError(raw_arg_a, get_str(18), 7, get_str(22), get_str(304));
        }
        php::Float arg_a = php::toFloat(raw_arg_a);
        php::Var raw_arg_noise = php::getCallArg(7);
        if (UNEXPECTED(!(raw_arg_noise.isString()))) {
            php::throwArgumentTypeError(raw_arg_noise, get_str(18), 8, get_str(17), get_str(203));
        }
        php::Str arg_noise = php::toString(raw_arg_noise);
        php::Var raw_arg_mean = php::getCallArg(8);
        if (UNEXPECTED(!((raw_arg_mean.isFloat() || raw_arg_mean.isInt())))) {
            php::throwArgumentTypeError(raw_arg_mean, get_str(18), 9, get_str(24), get_str(304));
        }
        php::Float arg_mean = php::toFloat(raw_arg_mean);
        php::Var raw_arg_sigma = php::getCallArg(9);
        if (UNEXPECTED(!((raw_arg_sigma.isFloat() || raw_arg_sigma.isInt())))) {
            php::throwArgumentTypeError(raw_arg_sigma, get_str(18), 10, get_str(25), get_str(304));
        }
        php::Float arg_sigma = php::toFloat(raw_arg_sigma);
        auto retval = php_pixelforge_create(arg_width,arg_height,arg_channels,arg_r,arg_g,arg_b,arg_a,php::takeValue(arg_noise),arg_mean,arg_sigma);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_text) {
    PHPX_TRY {
        php::checkCallArgCount(11, 11, false);
        php::Var raw_arg_text = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_text.isString()))) {
            php::throwArgumentTypeError(raw_arg_text, get_str(333), 1, get_str(27), get_str(203));
        }
        php::Str arg_text = php::toString(raw_arg_text);
        php::Var raw_arg_font = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_font.isString()))) {
            php::throwArgumentTypeError(raw_arg_font, get_str(333), 2, get_str(28), get_str(203));
        }
        php::Str arg_font = php::toString(raw_arg_font);
        php::Var raw_arg_fontfile = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_fontfile.isString()))) {
            php::throwArgumentTypeError(raw_arg_fontfile, get_str(333), 3, get_str(29), get_str(203));
        }
        php::Str arg_fontfile = php::toString(raw_arg_fontfile);
        php::Var raw_arg_width = php::getCallArg(3);
        if (UNEXPECTED(!(raw_arg_width.isInt()))) {
            php::throwArgumentTypeError(raw_arg_width, get_str(333), 4, get_str(10), get_str(302));
        }
        php::Int arg_width = php::toInt(raw_arg_width);
        php::Var raw_arg_height = php::getCallArg(4);
        if (UNEXPECTED(!(raw_arg_height.isInt()))) {
            php::throwArgumentTypeError(raw_arg_height, get_str(333), 5, get_str(11), get_str(302));
        }
        php::Int arg_height = php::toInt(raw_arg_height);
        php::Var raw_arg_align = php::getCallArg(5);
        if (UNEXPECTED(!(raw_arg_align.isString()))) {
            php::throwArgumentTypeError(raw_arg_align, get_str(333), 6, get_str(30), get_str(203));
        }
        php::Str arg_align = php::toString(raw_arg_align);
        php::Var raw_arg_justify = php::getCallArg(6);
        if (UNEXPECTED(!(raw_arg_justify.isBool()))) {
            php::throwArgumentTypeError(raw_arg_justify, get_str(333), 7, get_str(32), get_str(307));
        }
        php::Bool arg_justify = php::toBool(raw_arg_justify);
        php::Var raw_arg_dpi = php::getCallArg(7);
        if (UNEXPECTED(!(raw_arg_dpi.isInt()))) {
            php::throwArgumentTypeError(raw_arg_dpi, get_str(333), 8, get_str(33), get_str(302));
        }
        php::Int arg_dpi = php::toInt(raw_arg_dpi);
        php::Var raw_arg_rgba = php::getCallArg(8);
        if (UNEXPECTED(!(raw_arg_rgba.isBool()))) {
            php::throwArgumentTypeError(raw_arg_rgba, get_str(333), 9, get_str(34), get_str(307));
        }
        php::Bool arg_rgba = php::toBool(raw_arg_rgba);
        php::Var raw_arg_spacing = php::getCallArg(9);
        if (UNEXPECTED(!(raw_arg_spacing.isInt()))) {
            php::throwArgumentTypeError(raw_arg_spacing, get_str(333), 10, get_str(35), get_str(302));
        }
        php::Int arg_spacing = php::toInt(raw_arg_spacing);
        php::Var raw_arg_wrap = php::getCallArg(10);
        if (UNEXPECTED(!(raw_arg_wrap.isString()))) {
            php::throwArgumentTypeError(raw_arg_wrap, get_str(333), 11, get_str(36), get_str(203));
        }
        php::Str arg_wrap = php::toString(raw_arg_wrap);
        auto retval = php_pixelforge_text(php::takeValue(arg_text),php::takeValue(arg_font),php::takeValue(arg_fontfile),arg_width,arg_height,php::takeValue(arg_align),arg_justify,arg_dpi,arg_rgba,arg_spacing,php::takeValue(arg_wrap));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_join_new) {
    PHPX_TRY {
        php::checkCallArgCount(9, 9, false);
        php::Var raw_arg_animated = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_animated.isBool()))) {
            php::throwArgumentTypeError(raw_arg_animated, get_str(41), 1, get_str(38), get_str(307));
        }
        php::Bool arg_animated = php::toBool(raw_arg_animated);
        php::Var raw_arg_across = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_across.isInt()))) {
            php::throwArgumentTypeError(raw_arg_across, get_str(41), 2, get_str(39), get_str(302));
        }
        php::Int arg_across = php::toInt(raw_arg_across);
        php::Var raw_arg_shim = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_shim.isInt()))) {
            php::throwArgumentTypeError(raw_arg_shim, get_str(41), 3, get_str(40), get_str(302));
        }
        php::Int arg_shim = php::toInt(raw_arg_shim);
        php::Var raw_arg_r = php::getCallArg(3);
        if (UNEXPECTED(!((raw_arg_r.isFloat() || raw_arg_r.isInt())))) {
            php::throwArgumentTypeError(raw_arg_r, get_str(41), 4, get_str(19), get_str(304));
        }
        php::Float arg_r = php::toFloat(raw_arg_r);
        php::Var raw_arg_g = php::getCallArg(4);
        if (UNEXPECTED(!((raw_arg_g.isFloat() || raw_arg_g.isInt())))) {
            php::throwArgumentTypeError(raw_arg_g, get_str(41), 5, get_str(20), get_str(304));
        }
        php::Float arg_g = php::toFloat(raw_arg_g);
        php::Var raw_arg_b = php::getCallArg(5);
        if (UNEXPECTED(!((raw_arg_b.isFloat() || raw_arg_b.isInt())))) {
            php::throwArgumentTypeError(raw_arg_b, get_str(41), 6, get_str(21), get_str(304));
        }
        php::Float arg_b = php::toFloat(raw_arg_b);
        php::Var raw_arg_a = php::getCallArg(6);
        if (UNEXPECTED(!((raw_arg_a.isFloat() || raw_arg_a.isInt())))) {
            php::throwArgumentTypeError(raw_arg_a, get_str(41), 7, get_str(22), get_str(304));
        }
        php::Float arg_a = php::toFloat(raw_arg_a);
        php::Var raw_arg_halign = php::getCallArg(7);
        if (UNEXPECTED(!(raw_arg_halign.isString()))) {
            php::throwArgumentTypeError(raw_arg_halign, get_str(41), 8, get_str(42), get_str(203));
        }
        php::Str arg_halign = php::toString(raw_arg_halign);
        php::Var raw_arg_valign = php::getCallArg(8);
        if (UNEXPECTED(!(raw_arg_valign.isString()))) {
            php::throwArgumentTypeError(raw_arg_valign, get_str(41), 9, get_str(43), get_str(203));
        }
        php::Str arg_valign = php::toString(raw_arg_valign);
        auto retval = php_pixelforge_join_new(arg_animated,arg_across,arg_shim,arg_r,arg_g,arg_b,arg_a,php::takeValue(arg_halign),php::takeValue(arg_valign));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_join_add) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var arg_input = php::getCallArg(1);
        auto retval = php_pixelforge_join_add(php::takeValue(arg_h),php::takeValue(arg_input));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_clone) {
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_h = php::getCallArg(0);
        auto retval = php_pixelforge_clone(php::takeValue(arg_h));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_resize) {
    PHPX_TRY {
        php::checkCallArgCount(13, 13, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_width = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_width.isInt()))) {
            php::throwArgumentTypeError(raw_arg_width, get_str(65), 2, get_str(10), get_str(302));
        }
        php::Int arg_width = php::toInt(raw_arg_width);
        php::Var raw_arg_height = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_height.isInt()))) {
            php::throwArgumentTypeError(raw_arg_height, get_str(65), 3, get_str(11), get_str(302));
        }
        php::Int arg_height = php::toInt(raw_arg_height);
        php::Var raw_arg_fit = php::getCallArg(3);
        if (UNEXPECTED(!(raw_arg_fit.isString()))) {
            php::throwArgumentTypeError(raw_arg_fit, get_str(65), 4, get_str(63), get_str(203));
        }
        php::Str arg_fit = php::toString(raw_arg_fit);
        php::Var raw_arg_position = php::getCallArg(4);
        if (UNEXPECTED(!(raw_arg_position.isString()))) {
            php::throwArgumentTypeError(raw_arg_position, get_str(65), 5, get_str(60), get_str(203));
        }
        php::Str arg_position = php::toString(raw_arg_position);
        php::Var raw_arg_r = php::getCallArg(5);
        if (UNEXPECTED(!((raw_arg_r.isFloat() || raw_arg_r.isInt())))) {
            php::throwArgumentTypeError(raw_arg_r, get_str(65), 6, get_str(19), get_str(304));
        }
        php::Float arg_r = php::toFloat(raw_arg_r);
        php::Var raw_arg_g = php::getCallArg(6);
        if (UNEXPECTED(!((raw_arg_g.isFloat() || raw_arg_g.isInt())))) {
            php::throwArgumentTypeError(raw_arg_g, get_str(65), 7, get_str(20), get_str(304));
        }
        php::Float arg_g = php::toFloat(raw_arg_g);
        php::Var raw_arg_b = php::getCallArg(7);
        if (UNEXPECTED(!((raw_arg_b.isFloat() || raw_arg_b.isInt())))) {
            php::throwArgumentTypeError(raw_arg_b, get_str(65), 8, get_str(21), get_str(304));
        }
        php::Float arg_b = php::toFloat(raw_arg_b);
        php::Var raw_arg_a = php::getCallArg(8);
        if (UNEXPECTED(!((raw_arg_a.isFloat() || raw_arg_a.isInt())))) {
            php::throwArgumentTypeError(raw_arg_a, get_str(65), 9, get_str(22), get_str(304));
        }
        php::Float arg_a = php::toFloat(raw_arg_a);
        php::Var raw_arg_withoutEnlargement = php::getCallArg(9);
        if (UNEXPECTED(!(raw_arg_withoutEnlargement.isBool()))) {
            php::throwArgumentTypeError(raw_arg_withoutEnlargement, get_str(65), 10, get_str(66), get_str(307));
        }
        php::Bool arg_withoutEnlargement = php::toBool(raw_arg_withoutEnlargement);
        php::Var raw_arg_withoutReduction = php::getCallArg(10);
        if (UNEXPECTED(!(raw_arg_withoutReduction.isBool()))) {
            php::throwArgumentTypeError(raw_arg_withoutReduction, get_str(65), 11, get_str(67), get_str(307));
        }
        php::Bool arg_withoutReduction = php::toBool(raw_arg_withoutReduction);
        php::Var raw_arg_kernel = php::getCallArg(11);
        if (UNEXPECTED(!(raw_arg_kernel.isString()))) {
            php::throwArgumentTypeError(raw_arg_kernel, get_str(65), 12, get_str(68), get_str(203));
        }
        php::Str arg_kernel = php::toString(raw_arg_kernel);
        php::Var raw_arg_fastShrinkOnLoad = php::getCallArg(12);
        if (UNEXPECTED(!(raw_arg_fastShrinkOnLoad.isBool()))) {
            php::throwArgumentTypeError(raw_arg_fastShrinkOnLoad, get_str(65), 13, get_str(70), get_str(307));
        }
        php::Bool arg_fastShrinkOnLoad = php::toBool(raw_arg_fastShrinkOnLoad);
        auto retval = php_pixelforge_resize(php::takeValue(arg_h),arg_width,arg_height,php::takeValue(arg_fit),php::takeValue(arg_position),arg_r,arg_g,arg_b,arg_a,arg_withoutEnlargement,arg_withoutReduction,php::takeValue(arg_kernel),arg_fastShrinkOnLoad);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_extract) {
    PHPX_TRY {
        php::checkCallArgCount(5, 5, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_left = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_left.isInt()))) {
            php::throwArgumentTypeError(raw_arg_left, get_str(334), 2, get_str(31), get_str(302));
        }
        php::Int arg_left = php::toInt(raw_arg_left);
        php::Var raw_arg_top = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_top.isInt()))) {
            php::throwArgumentTypeError(raw_arg_top, get_str(334), 3, get_str(44), get_str(302));
        }
        php::Int arg_top = php::toInt(raw_arg_top);
        php::Var raw_arg_width = php::getCallArg(3);
        if (UNEXPECTED(!(raw_arg_width.isInt()))) {
            php::throwArgumentTypeError(raw_arg_width, get_str(334), 4, get_str(10), get_str(302));
        }
        php::Int arg_width = php::toInt(raw_arg_width);
        php::Var raw_arg_height = php::getCallArg(4);
        if (UNEXPECTED(!(raw_arg_height.isInt()))) {
            php::throwArgumentTypeError(raw_arg_height, get_str(334), 5, get_str(11), get_str(302));
        }
        php::Int arg_height = php::toInt(raw_arg_height);
        auto retval = php_pixelforge_extract(php::takeValue(arg_h),arg_left,arg_top,arg_width,arg_height);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_extend) {
    PHPX_TRY {
        php::checkCallArgCount(10, 10, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_top = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_top.isInt()))) {
            php::throwArgumentTypeError(raw_arg_top, get_str(79), 2, get_str(44), get_str(302));
        }
        php::Int arg_top = php::toInt(raw_arg_top);
        php::Var raw_arg_bottom = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_bottom.isInt()))) {
            php::throwArgumentTypeError(raw_arg_bottom, get_str(79), 3, get_str(76), get_str(302));
        }
        php::Int arg_bottom = php::toInt(raw_arg_bottom);
        php::Var raw_arg_left = php::getCallArg(3);
        if (UNEXPECTED(!(raw_arg_left.isInt()))) {
            php::throwArgumentTypeError(raw_arg_left, get_str(79), 4, get_str(31), get_str(302));
        }
        php::Int arg_left = php::toInt(raw_arg_left);
        php::Var raw_arg_right = php::getCallArg(4);
        if (UNEXPECTED(!(raw_arg_right.isInt()))) {
            php::throwArgumentTypeError(raw_arg_right, get_str(79), 5, get_str(77), get_str(302));
        }
        php::Int arg_right = php::toInt(raw_arg_right);
        php::Var raw_arg_with = php::getCallArg(5);
        if (UNEXPECTED(!(raw_arg_with.isString()))) {
            php::throwArgumentTypeError(raw_arg_with, get_str(79), 6, get_str(335), get_str(203));
        }
        php::Str arg_with = php::toString(raw_arg_with);
        php::Var raw_arg_r = php::getCallArg(6);
        if (UNEXPECTED(!((raw_arg_r.isFloat() || raw_arg_r.isInt())))) {
            php::throwArgumentTypeError(raw_arg_r, get_str(79), 7, get_str(19), get_str(304));
        }
        php::Float arg_r = php::toFloat(raw_arg_r);
        php::Var raw_arg_g = php::getCallArg(7);
        if (UNEXPECTED(!((raw_arg_g.isFloat() || raw_arg_g.isInt())))) {
            php::throwArgumentTypeError(raw_arg_g, get_str(79), 8, get_str(20), get_str(304));
        }
        php::Float arg_g = php::toFloat(raw_arg_g);
        php::Var raw_arg_b = php::getCallArg(8);
        if (UNEXPECTED(!((raw_arg_b.isFloat() || raw_arg_b.isInt())))) {
            php::throwArgumentTypeError(raw_arg_b, get_str(79), 9, get_str(21), get_str(304));
        }
        php::Float arg_b = php::toFloat(raw_arg_b);
        php::Var raw_arg_a = php::getCallArg(9);
        if (UNEXPECTED(!((raw_arg_a.isFloat() || raw_arg_a.isInt())))) {
            php::throwArgumentTypeError(raw_arg_a, get_str(79), 10, get_str(22), get_str(304));
        }
        php::Float arg_a = php::toFloat(raw_arg_a);
        auto retval = php_pixelforge_extend(php::takeValue(arg_h),arg_top,arg_bottom,arg_left,arg_right,php::takeValue(arg_with),arg_r,arg_g,arg_b,arg_a);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_trim) {
    PHPX_TRY {
        php::checkCallArgCount(7, 7, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_threshold = php::getCallArg(1);
        if (UNEXPECTED(!((raw_arg_threshold.isFloat() || raw_arg_threshold.isInt())))) {
            php::throwArgumentTypeError(raw_arg_threshold, get_str(84), 2, get_str(83), get_str(304));
        }
        php::Float arg_threshold = php::toFloat(raw_arg_threshold);
        php::Var raw_arg_useBackground = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_useBackground.isBool()))) {
            php::throwArgumentTypeError(raw_arg_useBackground, get_str(84), 3, get_str(336), get_str(307));
        }
        php::Bool arg_useBackground = php::toBool(raw_arg_useBackground);
        php::Var raw_arg_r = php::getCallArg(3);
        if (UNEXPECTED(!((raw_arg_r.isFloat() || raw_arg_r.isInt())))) {
            php::throwArgumentTypeError(raw_arg_r, get_str(84), 4, get_str(19), get_str(304));
        }
        php::Float arg_r = php::toFloat(raw_arg_r);
        php::Var raw_arg_g = php::getCallArg(4);
        if (UNEXPECTED(!((raw_arg_g.isFloat() || raw_arg_g.isInt())))) {
            php::throwArgumentTypeError(raw_arg_g, get_str(84), 5, get_str(20), get_str(304));
        }
        php::Float arg_g = php::toFloat(raw_arg_g);
        php::Var raw_arg_b = php::getCallArg(5);
        if (UNEXPECTED(!((raw_arg_b.isFloat() || raw_arg_b.isInt())))) {
            php::throwArgumentTypeError(raw_arg_b, get_str(84), 6, get_str(21), get_str(304));
        }
        php::Float arg_b = php::toFloat(raw_arg_b);
        php::Var raw_arg_lineArt = php::getCallArg(6);
        if (UNEXPECTED(!(raw_arg_lineArt.isBool()))) {
            php::throwArgumentTypeError(raw_arg_lineArt, get_str(84), 7, get_str(85), get_str(307));
        }
        php::Bool arg_lineArt = php::toBool(raw_arg_lineArt);
        auto retval = php_pixelforge_trim(php::takeValue(arg_h),arg_threshold,arg_useBackground,arg_r,arg_g,arg_b,arg_lineArt);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_rotate) {
    PHPX_TRY {
        php::checkCallArgCount(6, 6, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_angle = php::getCallArg(1);
        if (UNEXPECTED(!((raw_arg_angle.isFloat() || raw_arg_angle.isInt())))) {
            php::throwArgumentTypeError(raw_arg_angle, get_str(86), 2, get_str(87), get_str(304));
        }
        php::Float arg_angle = php::toFloat(raw_arg_angle);
        php::Var raw_arg_r = php::getCallArg(2);
        if (UNEXPECTED(!((raw_arg_r.isFloat() || raw_arg_r.isInt())))) {
            php::throwArgumentTypeError(raw_arg_r, get_str(86), 3, get_str(19), get_str(304));
        }
        php::Float arg_r = php::toFloat(raw_arg_r);
        php::Var raw_arg_g = php::getCallArg(3);
        if (UNEXPECTED(!((raw_arg_g.isFloat() || raw_arg_g.isInt())))) {
            php::throwArgumentTypeError(raw_arg_g, get_str(86), 4, get_str(20), get_str(304));
        }
        php::Float arg_g = php::toFloat(raw_arg_g);
        php::Var raw_arg_b = php::getCallArg(4);
        if (UNEXPECTED(!((raw_arg_b.isFloat() || raw_arg_b.isInt())))) {
            php::throwArgumentTypeError(raw_arg_b, get_str(86), 5, get_str(21), get_str(304));
        }
        php::Float arg_b = php::toFloat(raw_arg_b);
        php::Var raw_arg_a = php::getCallArg(5);
        if (UNEXPECTED(!((raw_arg_a.isFloat() || raw_arg_a.isInt())))) {
            php::throwArgumentTypeError(raw_arg_a, get_str(86), 6, get_str(22), get_str(304));
        }
        php::Float arg_a = php::toFloat(raw_arg_a);
        auto retval = php_pixelforge_rotate(php::takeValue(arg_h),arg_angle,arg_r,arg_g,arg_b,arg_a);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_auto_orient) {
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_h = php::getCallArg(0);
        auto retval = php_pixelforge_auto_orient(php::takeValue(arg_h));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_flip) {
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_h = php::getCallArg(0);
        auto retval = php_pixelforge_flip(php::takeValue(arg_h));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_flop) {
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_h = php::getCallArg(0);
        auto retval = php_pixelforge_flop(php::takeValue(arg_h));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_affine) {
    PHPX_TRY {
        php::checkCallArgCount(14, 14, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_a = php::getCallArg(1);
        if (UNEXPECTED(!((raw_arg_a.isFloat() || raw_arg_a.isInt())))) {
            php::throwArgumentTypeError(raw_arg_a, get_str(90), 2, get_str(22), get_str(304));
        }
        php::Float arg_a = php::toFloat(raw_arg_a);
        php::Var raw_arg_b = php::getCallArg(2);
        if (UNEXPECTED(!((raw_arg_b.isFloat() || raw_arg_b.isInt())))) {
            php::throwArgumentTypeError(raw_arg_b, get_str(90), 3, get_str(21), get_str(304));
        }
        php::Float arg_b = php::toFloat(raw_arg_b);
        php::Var raw_arg_c = php::getCallArg(3);
        if (UNEXPECTED(!((raw_arg_c.isFloat() || raw_arg_c.isInt())))) {
            php::throwArgumentTypeError(raw_arg_c, get_str(90), 4, get_str(337), get_str(304));
        }
        php::Float arg_c = php::toFloat(raw_arg_c);
        php::Var raw_arg_d = php::getCallArg(4);
        if (UNEXPECTED(!((raw_arg_d.isFloat() || raw_arg_d.isInt())))) {
            php::throwArgumentTypeError(raw_arg_d, get_str(90), 5, get_str(338), get_str(304));
        }
        php::Float arg_d = php::toFloat(raw_arg_d);
        php::Var raw_arg_r = php::getCallArg(5);
        if (UNEXPECTED(!((raw_arg_r.isFloat() || raw_arg_r.isInt())))) {
            php::throwArgumentTypeError(raw_arg_r, get_str(90), 6, get_str(19), get_str(304));
        }
        php::Float arg_r = php::toFloat(raw_arg_r);
        php::Var raw_arg_g = php::getCallArg(6);
        if (UNEXPECTED(!((raw_arg_g.isFloat() || raw_arg_g.isInt())))) {
            php::throwArgumentTypeError(raw_arg_g, get_str(90), 7, get_str(20), get_str(304));
        }
        php::Float arg_g = php::toFloat(raw_arg_g);
        php::Var raw_arg_bl = php::getCallArg(7);
        if (UNEXPECTED(!((raw_arg_bl.isFloat() || raw_arg_bl.isInt())))) {
            php::throwArgumentTypeError(raw_arg_bl, get_str(90), 8, get_str(91), get_str(304));
        }
        php::Float arg_bl = php::toFloat(raw_arg_bl);
        php::Var raw_arg_al = php::getCallArg(8);
        if (UNEXPECTED(!((raw_arg_al.isFloat() || raw_arg_al.isInt())))) {
            php::throwArgumentTypeError(raw_arg_al, get_str(90), 9, get_str(92), get_str(304));
        }
        php::Float arg_al = php::toFloat(raw_arg_al);
        php::Var raw_arg_interpolator = php::getCallArg(9);
        if (UNEXPECTED(!(raw_arg_interpolator.isString()))) {
            php::throwArgumentTypeError(raw_arg_interpolator, get_str(90), 10, get_str(93), get_str(203));
        }
        php::Str arg_interpolator = php::toString(raw_arg_interpolator);
        php::Var raw_arg_idx = php::getCallArg(10);
        if (UNEXPECTED(!((raw_arg_idx.isFloat() || raw_arg_idx.isInt())))) {
            php::throwArgumentTypeError(raw_arg_idx, get_str(90), 11, get_str(95), get_str(304));
        }
        php::Float arg_idx = php::toFloat(raw_arg_idx);
        php::Var raw_arg_idy = php::getCallArg(11);
        if (UNEXPECTED(!((raw_arg_idy.isFloat() || raw_arg_idy.isInt())))) {
            php::throwArgumentTypeError(raw_arg_idy, get_str(90), 12, get_str(96), get_str(304));
        }
        php::Float arg_idy = php::toFloat(raw_arg_idy);
        php::Var raw_arg_odx = php::getCallArg(12);
        if (UNEXPECTED(!((raw_arg_odx.isFloat() || raw_arg_odx.isInt())))) {
            php::throwArgumentTypeError(raw_arg_odx, get_str(90), 13, get_str(97), get_str(304));
        }
        php::Float arg_odx = php::toFloat(raw_arg_odx);
        php::Var raw_arg_ody = php::getCallArg(13);
        if (UNEXPECTED(!((raw_arg_ody.isFloat() || raw_arg_ody.isInt())))) {
            php::throwArgumentTypeError(raw_arg_ody, get_str(90), 14, get_str(98), get_str(304));
        }
        php::Float arg_ody = php::toFloat(raw_arg_ody);
        auto retval = php_pixelforge_affine(php::takeValue(arg_h),arg_a,arg_b,arg_c,arg_d,arg_r,arg_g,arg_bl,arg_al,php::takeValue(arg_interpolator),arg_idx,arg_idy,arg_odx,arg_ody);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_sharpen) {
    PHPX_TRY {
        php::checkCallArgCount(7, 7, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_sigma = php::getCallArg(1);
        if (UNEXPECTED(!((raw_arg_sigma.isFloat() || raw_arg_sigma.isInt())))) {
            php::throwArgumentTypeError(raw_arg_sigma, get_str(339), 2, get_str(25), get_str(304));
        }
        php::Float arg_sigma = php::toFloat(raw_arg_sigma);
        php::Var raw_arg_m1 = php::getCallArg(2);
        if (UNEXPECTED(!((raw_arg_m1.isFloat() || raw_arg_m1.isInt())))) {
            php::throwArgumentTypeError(raw_arg_m1, get_str(339), 3, get_str(99), get_str(304));
        }
        php::Float arg_m1 = php::toFloat(raw_arg_m1);
        php::Var raw_arg_m2 = php::getCallArg(3);
        if (UNEXPECTED(!((raw_arg_m2.isFloat() || raw_arg_m2.isInt())))) {
            php::throwArgumentTypeError(raw_arg_m2, get_str(339), 4, get_str(100), get_str(304));
        }
        php::Float arg_m2 = php::toFloat(raw_arg_m2);
        php::Var raw_arg_x1 = php::getCallArg(4);
        if (UNEXPECTED(!((raw_arg_x1.isFloat() || raw_arg_x1.isInt())))) {
            php::throwArgumentTypeError(raw_arg_x1, get_str(339), 5, get_str(101), get_str(304));
        }
        php::Float arg_x1 = php::toFloat(raw_arg_x1);
        php::Var raw_arg_y2 = php::getCallArg(5);
        if (UNEXPECTED(!((raw_arg_y2.isFloat() || raw_arg_y2.isInt())))) {
            php::throwArgumentTypeError(raw_arg_y2, get_str(339), 6, get_str(102), get_str(304));
        }
        php::Float arg_y2 = php::toFloat(raw_arg_y2);
        php::Var raw_arg_y3 = php::getCallArg(6);
        if (UNEXPECTED(!((raw_arg_y3.isFloat() || raw_arg_y3.isInt())))) {
            php::throwArgumentTypeError(raw_arg_y3, get_str(339), 7, get_str(103), get_str(304));
        }
        php::Float arg_y3 = php::toFloat(raw_arg_y3);
        auto retval = php_pixelforge_sharpen(php::takeValue(arg_h),arg_sigma,arg_m1,arg_m2,arg_x1,arg_y2,arg_y3);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_median) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_size = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_size.isInt()))) {
            php::throwArgumentTypeError(raw_arg_size, get_str(340), 2, get_str(184), get_str(302));
        }
        php::Int arg_size = php::toInt(raw_arg_size);
        auto retval = php_pixelforge_median(php::takeValue(arg_h),arg_size);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_blur) {
    PHPX_TRY {
        php::checkCallArgCount(4, 4, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_sigma = php::getCallArg(1);
        if (UNEXPECTED(!((raw_arg_sigma.isFloat() || raw_arg_sigma.isInt())))) {
            php::throwArgumentTypeError(raw_arg_sigma, get_str(341), 2, get_str(25), get_str(304));
        }
        php::Float arg_sigma = php::toFloat(raw_arg_sigma);
        php::Var raw_arg_precision = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_precision.isString()))) {
            php::throwArgumentTypeError(raw_arg_precision, get_str(341), 3, get_str(104), get_str(203));
        }
        php::Str arg_precision = php::toString(raw_arg_precision);
        php::Var raw_arg_minAmplitude = php::getCallArg(3);
        if (UNEXPECTED(!((raw_arg_minAmplitude.isFloat() || raw_arg_minAmplitude.isInt())))) {
            php::throwArgumentTypeError(raw_arg_minAmplitude, get_str(341), 4, get_str(106), get_str(304));
        }
        php::Float arg_minAmplitude = php::toFloat(raw_arg_minAmplitude);
        auto retval = php_pixelforge_blur(php::takeValue(arg_h),arg_sigma,php::takeValue(arg_precision),arg_minAmplitude);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_flatten) {
    PHPX_TRY {
        php::checkCallArgCount(4, 4, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_r = php::getCallArg(1);
        if (UNEXPECTED(!((raw_arg_r.isFloat() || raw_arg_r.isInt())))) {
            php::throwArgumentTypeError(raw_arg_r, get_str(109), 2, get_str(19), get_str(304));
        }
        php::Float arg_r = php::toFloat(raw_arg_r);
        php::Var raw_arg_g = php::getCallArg(2);
        if (UNEXPECTED(!((raw_arg_g.isFloat() || raw_arg_g.isInt())))) {
            php::throwArgumentTypeError(raw_arg_g, get_str(109), 3, get_str(20), get_str(304));
        }
        php::Float arg_g = php::toFloat(raw_arg_g);
        php::Var raw_arg_b = php::getCallArg(3);
        if (UNEXPECTED(!((raw_arg_b.isFloat() || raw_arg_b.isInt())))) {
            php::throwArgumentTypeError(raw_arg_b, get_str(109), 4, get_str(21), get_str(304));
        }
        php::Float arg_b = php::toFloat(raw_arg_b);
        auto retval = php_pixelforge_flatten(php::takeValue(arg_h),arg_r,arg_g,arg_b);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_unflatten) {
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_h = php::getCallArg(0);
        auto retval = php_pixelforge_unflatten(php::takeValue(arg_h));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_gamma) {
    PHPX_TRY {
        php::checkCallArgCount(3, 3, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_gamma = php::getCallArg(1);
        if (UNEXPECTED(!((raw_arg_gamma.isFloat() || raw_arg_gamma.isInt())))) {
            php::throwArgumentTypeError(raw_arg_gamma, get_str(342), 2, get_str(303), get_str(304));
        }
        php::Float arg_gamma = php::toFloat(raw_arg_gamma);
        php::Var raw_arg_gammaOut = php::getCallArg(2);
        if (UNEXPECTED(!((raw_arg_gammaOut.isFloat() || raw_arg_gammaOut.isInt())))) {
            php::throwArgumentTypeError(raw_arg_gammaOut, get_str(342), 3, get_str(111), get_str(304));
        }
        php::Float arg_gammaOut = php::toFloat(raw_arg_gammaOut);
        auto retval = php_pixelforge_gamma(php::takeValue(arg_h),arg_gamma,arg_gammaOut);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_negate) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_alpha = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_alpha.isBool()))) {
            php::throwArgumentTypeError(raw_arg_alpha, get_str(343), 2, get_str(112), get_str(307));
        }
        php::Bool arg_alpha = php::toBool(raw_arg_alpha);
        auto retval = php_pixelforge_negate(php::takeValue(arg_h),arg_alpha);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_normalise) {
    PHPX_TRY {
        php::checkCallArgCount(3, 3, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_lower = php::getCallArg(1);
        if (UNEXPECTED(!((raw_arg_lower.isFloat() || raw_arg_lower.isInt())))) {
            php::throwArgumentTypeError(raw_arg_lower, get_str(344), 2, get_str(113), get_str(304));
        }
        php::Float arg_lower = php::toFloat(raw_arg_lower);
        php::Var raw_arg_upper = php::getCallArg(2);
        if (UNEXPECTED(!((raw_arg_upper.isFloat() || raw_arg_upper.isInt())))) {
            php::throwArgumentTypeError(raw_arg_upper, get_str(344), 3, get_str(114), get_str(304));
        }
        php::Float arg_upper = php::toFloat(raw_arg_upper);
        auto retval = php_pixelforge_normalise(php::takeValue(arg_h),arg_lower,arg_upper);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_clahe) {
    PHPX_TRY {
        php::checkCallArgCount(4, 4, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_width = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_width.isInt()))) {
            php::throwArgumentTypeError(raw_arg_width, get_str(345), 2, get_str(10), get_str(302));
        }
        php::Int arg_width = php::toInt(raw_arg_width);
        php::Var raw_arg_height = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_height.isInt()))) {
            php::throwArgumentTypeError(raw_arg_height, get_str(345), 3, get_str(11), get_str(302));
        }
        php::Int arg_height = php::toInt(raw_arg_height);
        php::Var raw_arg_maxSlope = php::getCallArg(3);
        if (UNEXPECTED(!(raw_arg_maxSlope.isInt()))) {
            php::throwArgumentTypeError(raw_arg_maxSlope, get_str(345), 4, get_str(116), get_str(302));
        }
        php::Int arg_maxSlope = php::toInt(raw_arg_maxSlope);
        auto retval = php_pixelforge_clahe(php::takeValue(arg_h),arg_width,arg_height,arg_maxSlope);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_threshold) {
    PHPX_TRY {
        php::checkCallArgCount(3, 3, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_threshold = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_threshold.isInt()))) {
            php::throwArgumentTypeError(raw_arg_threshold, get_str(346), 2, get_str(83), get_str(302));
        }
        php::Int arg_threshold = php::toInt(raw_arg_threshold);
        php::Var raw_arg_greyscale = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_greyscale.isBool()))) {
            php::throwArgumentTypeError(raw_arg_greyscale, get_str(346), 3, get_str(117), get_str(307));
        }
        php::Bool arg_greyscale = php::toBool(raw_arg_greyscale);
        auto retval = php_pixelforge_threshold(php::takeValue(arg_h),arg_threshold,arg_greyscale);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_linear) {
    PHPX_TRY {
        php::checkCallArgCount(3, 3, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_a = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_a.isString()))) {
            php::throwArgumentTypeError(raw_arg_a, get_str(347), 2, get_str(22), get_str(203));
        }
        php::Str arg_a = php::toString(raw_arg_a);
        php::Var raw_arg_b = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_b.isString()))) {
            php::throwArgumentTypeError(raw_arg_b, get_str(347), 3, get_str(21), get_str(203));
        }
        php::Str arg_b = php::toString(raw_arg_b);
        auto retval = php_pixelforge_linear(php::takeValue(arg_h),php::takeValue(arg_a),php::takeValue(arg_b));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_modulate) {
    PHPX_TRY {
        php::checkCallArgCount(5, 5, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_brightness = php::getCallArg(1);
        if (UNEXPECTED(!((raw_arg_brightness.isFloat() || raw_arg_brightness.isInt())))) {
            php::throwArgumentTypeError(raw_arg_brightness, get_str(348), 2, get_str(120), get_str(304));
        }
        php::Float arg_brightness = php::toFloat(raw_arg_brightness);
        php::Var raw_arg_saturation = php::getCallArg(2);
        if (UNEXPECTED(!((raw_arg_saturation.isFloat() || raw_arg_saturation.isInt())))) {
            php::throwArgumentTypeError(raw_arg_saturation, get_str(348), 3, get_str(121), get_str(304));
        }
        php::Float arg_saturation = php::toFloat(raw_arg_saturation);
        php::Var raw_arg_hue = php::getCallArg(3);
        if (UNEXPECTED(!((raw_arg_hue.isFloat() || raw_arg_hue.isInt())))) {
            php::throwArgumentTypeError(raw_arg_hue, get_str(348), 4, get_str(122), get_str(304));
        }
        php::Float arg_hue = php::toFloat(raw_arg_hue);
        php::Var raw_arg_lightness = php::getCallArg(4);
        if (UNEXPECTED(!((raw_arg_lightness.isFloat() || raw_arg_lightness.isInt())))) {
            php::throwArgumentTypeError(raw_arg_lightness, get_str(348), 5, get_str(123), get_str(304));
        }
        php::Float arg_lightness = php::toFloat(raw_arg_lightness);
        auto retval = php_pixelforge_modulate(php::takeValue(arg_h),arg_brightness,arg_saturation,arg_hue,arg_lightness);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_tint) {
    PHPX_TRY {
        php::checkCallArgCount(4, 4, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_r = php::getCallArg(1);
        if (UNEXPECTED(!((raw_arg_r.isFloat() || raw_arg_r.isInt())))) {
            php::throwArgumentTypeError(raw_arg_r, get_str(124), 2, get_str(19), get_str(304));
        }
        php::Float arg_r = php::toFloat(raw_arg_r);
        php::Var raw_arg_g = php::getCallArg(2);
        if (UNEXPECTED(!((raw_arg_g.isFloat() || raw_arg_g.isInt())))) {
            php::throwArgumentTypeError(raw_arg_g, get_str(124), 3, get_str(20), get_str(304));
        }
        php::Float arg_g = php::toFloat(raw_arg_g);
        php::Var raw_arg_b = php::getCallArg(3);
        if (UNEXPECTED(!((raw_arg_b.isFloat() || raw_arg_b.isInt())))) {
            php::throwArgumentTypeError(raw_arg_b, get_str(124), 4, get_str(21), get_str(304));
        }
        php::Float arg_b = php::toFloat(raw_arg_b);
        auto retval = php_pixelforge_tint(php::takeValue(arg_h),arg_r,arg_g,arg_b);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_colourspace) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_space = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_space.isString()))) {
            php::throwArgumentTypeError(raw_arg_space, get_str(349), 2, get_str(310), get_str(203));
        }
        php::Str arg_space = php::toString(raw_arg_space);
        auto retval = php_pixelforge_colourspace(php::takeValue(arg_h),php::takeValue(arg_space));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_remove_alpha) {
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_h = php::getCallArg(0);
        auto retval = php_pixelforge_remove_alpha(php::takeValue(arg_h));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_ensure_alpha) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_alpha = php::getCallArg(1);
        if (UNEXPECTED(!((raw_arg_alpha.isFloat() || raw_arg_alpha.isInt())))) {
            php::throwArgumentTypeError(raw_arg_alpha, get_str(350), 2, get_str(112), get_str(304));
        }
        php::Float arg_alpha = php::toFloat(raw_arg_alpha);
        auto retval = php_pixelforge_ensure_alpha(php::takeValue(arg_h),arg_alpha);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_extract_channel) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_channel = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_channel.isInt()))) {
            php::throwArgumentTypeError(raw_arg_channel, get_str(133), 2, get_str(134), get_str(302));
        }
        php::Int arg_channel = php::toInt(raw_arg_channel);
        auto retval = php_pixelforge_extract_channel(php::takeValue(arg_h),arg_channel);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_join_channel) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var arg_other = php::getCallArg(1);
        auto retval = php_pixelforge_join_channel(php::takeValue(arg_h),php::takeValue(arg_other));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_bandbool) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_op = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_op.isString()))) {
            php::throwArgumentTypeError(raw_arg_op, get_str(351), 2, get_str(314), get_str(203));
        }
        php::Str arg_op = php::toString(raw_arg_op);
        auto retval = php_pixelforge_bandbool(php::takeValue(arg_h),php::takeValue(arg_op));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_boolean) {
    PHPX_TRY {
        php::checkCallArgCount(3, 3, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var arg_other = php::getCallArg(1);
        php::Var raw_arg_op = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_op.isString()))) {
            php::throwArgumentTypeError(raw_arg_op, get_str(352), 3, get_str(314), get_str(203));
        }
        php::Str arg_op = php::toString(raw_arg_op);
        auto retval = php_pixelforge_boolean(php::takeValue(arg_h),php::takeValue(arg_other),php::takeValue(arg_op));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_dilate) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_width = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_width.isInt()))) {
            php::throwArgumentTypeError(raw_arg_width, get_str(353), 2, get_str(10), get_str(302));
        }
        php::Int arg_width = php::toInt(raw_arg_width);
        auto retval = php_pixelforge_dilate(php::takeValue(arg_h),arg_width);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_erode) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_width = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_width.isInt()))) {
            php::throwArgumentTypeError(raw_arg_width, get_str(354), 2, get_str(10), get_str(302));
        }
        php::Int arg_width = php::toInt(raw_arg_width);
        auto retval = php_pixelforge_erode(php::takeValue(arg_h),arg_width);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_convolve) {
    PHPX_TRY {
        php::checkCallArgCount(6, 6, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_width = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_width.isInt()))) {
            php::throwArgumentTypeError(raw_arg_width, get_str(355), 2, get_str(10), get_str(302));
        }
        php::Int arg_width = php::toInt(raw_arg_width);
        php::Var raw_arg_height = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_height.isInt()))) {
            php::throwArgumentTypeError(raw_arg_height, get_str(355), 3, get_str(11), get_str(302));
        }
        php::Int arg_height = php::toInt(raw_arg_height);
        php::Var raw_arg_kernel = php::getCallArg(3);
        if (UNEXPECTED(!(raw_arg_kernel.isString()))) {
            php::throwArgumentTypeError(raw_arg_kernel, get_str(355), 4, get_str(68), get_str(203));
        }
        php::Str arg_kernel = php::toString(raw_arg_kernel);
        php::Var raw_arg_scale = php::getCallArg(4);
        if (UNEXPECTED(!((raw_arg_scale.isFloat() || raw_arg_scale.isInt())))) {
            php::throwArgumentTypeError(raw_arg_scale, get_str(355), 5, get_str(138), get_str(304));
        }
        php::Float arg_scale = php::toFloat(raw_arg_scale);
        php::Var raw_arg_offset = php::getCallArg(5);
        if (UNEXPECTED(!((raw_arg_offset.isFloat() || raw_arg_offset.isInt())))) {
            php::throwArgumentTypeError(raw_arg_offset, get_str(355), 6, get_str(139), get_str(304));
        }
        php::Float arg_offset = php::toFloat(raw_arg_offset);
        auto retval = php_pixelforge_convolve(php::takeValue(arg_h),arg_width,arg_height,php::takeValue(arg_kernel),arg_scale,arg_offset);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_recomb) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_matrix = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_matrix.isString()))) {
            php::throwArgumentTypeError(raw_arg_matrix, get_str(356), 2, get_str(357), get_str(203));
        }
        php::Str arg_matrix = php::toString(raw_arg_matrix);
        auto retval = php_pixelforge_recomb(php::takeValue(arg_h),php::takeValue(arg_matrix));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_composite) {
    PHPX_TRY {
        php::checkCallArgCount(8, 8, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var arg_overlay = php::getCallArg(1);
        php::Var raw_arg_gravity = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_gravity.isString()))) {
            php::throwArgumentTypeError(raw_arg_gravity, get_str(358), 3, get_str(61), get_str(203));
        }
        php::Str arg_gravity = php::toString(raw_arg_gravity);
        php::Var raw_arg_left = php::getCallArg(3);
        if (UNEXPECTED(!(raw_arg_left.isInt()))) {
            php::throwArgumentTypeError(raw_arg_left, get_str(358), 4, get_str(31), get_str(302));
        }
        php::Int arg_left = php::toInt(raw_arg_left);
        php::Var raw_arg_top = php::getCallArg(4);
        if (UNEXPECTED(!(raw_arg_top.isInt()))) {
            php::throwArgumentTypeError(raw_arg_top, get_str(358), 5, get_str(44), get_str(302));
        }
        php::Int arg_top = php::toInt(raw_arg_top);
        php::Var raw_arg_blend = php::getCallArg(5);
        if (UNEXPECTED(!(raw_arg_blend.isString()))) {
            php::throwArgumentTypeError(raw_arg_blend, get_str(358), 6, get_str(140), get_str(203));
        }
        php::Str arg_blend = php::toString(raw_arg_blend);
        php::Var raw_arg_tile = php::getCallArg(6);
        if (UNEXPECTED(!(raw_arg_tile.isBool()))) {
            php::throwArgumentTypeError(raw_arg_tile, get_str(358), 7, get_str(142), get_str(307));
        }
        php::Bool arg_tile = php::toBool(raw_arg_tile);
        php::Var raw_arg_premultiplied = php::getCallArg(7);
        if (UNEXPECTED(!(raw_arg_premultiplied.isBool()))) {
            php::throwArgumentTypeError(raw_arg_premultiplied, get_str(358), 8, get_str(15), get_str(307));
        }
        php::Bool arg_premultiplied = php::toBool(raw_arg_premultiplied);
        auto retval = php_pixelforge_composite(php::takeValue(arg_h),php::takeValue(arg_overlay),php::takeValue(arg_gravity),arg_left,arg_top,php::takeValue(arg_blend),arg_tile,arg_premultiplied);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_output) {
    PHPX_TRY {
        php::checkCallArgCount(31, 31, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_format = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_format.isString()))) {
            php::throwArgumentTypeError(raw_arg_format, get_str(359), 2, get_str(206), get_str(203));
        }
        php::Str arg_format = php::toString(raw_arg_format);
        php::Var raw_arg_quality = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_quality.isInt()))) {
            php::throwArgumentTypeError(raw_arg_quality, get_str(359), 3, get_str(152), get_str(302));
        }
        php::Int arg_quality = php::toInt(raw_arg_quality);
        php::Var raw_arg_lossless = php::getCallArg(3);
        if (UNEXPECTED(!(raw_arg_lossless.isBool()))) {
            php::throwArgumentTypeError(raw_arg_lossless, get_str(359), 4, get_str(153), get_str(307));
        }
        php::Bool arg_lossless = php::toBool(raw_arg_lossless);
        php::Var raw_arg_effort = php::getCallArg(4);
        if (UNEXPECTED(!(raw_arg_effort.isInt()))) {
            php::throwArgumentTypeError(raw_arg_effort, get_str(359), 5, get_str(154), get_str(302));
        }
        php::Int arg_effort = php::toInt(raw_arg_effort);
        php::Var raw_arg_progressive = php::getCallArg(5);
        if (UNEXPECTED(!(raw_arg_progressive.isBool()))) {
            php::throwArgumentTypeError(raw_arg_progressive, get_str(359), 6, get_str(155), get_str(307));
        }
        php::Bool arg_progressive = php::toBool(raw_arg_progressive);
        php::Var raw_arg_chroma = php::getCallArg(6);
        if (UNEXPECTED(!(raw_arg_chroma.isString()))) {
            php::throwArgumentTypeError(raw_arg_chroma, get_str(359), 7, get_str(360), get_str(203));
        }
        php::Str arg_chroma = php::toString(raw_arg_chroma);
        php::Var raw_arg_mozjpeg = php::getCallArg(7);
        if (UNEXPECTED(!(raw_arg_mozjpeg.isBool()))) {
            php::throwArgumentTypeError(raw_arg_mozjpeg, get_str(359), 8, get_str(158), get_str(307));
        }
        php::Bool arg_mozjpeg = php::toBool(raw_arg_mozjpeg);
        php::Var raw_arg_compressionLevel = php::getCallArg(8);
        if (UNEXPECTED(!(raw_arg_compressionLevel.isInt()))) {
            php::throwArgumentTypeError(raw_arg_compressionLevel, get_str(359), 9, get_str(159), get_str(302));
        }
        php::Int arg_compressionLevel = php::toInt(raw_arg_compressionLevel);
        php::Var raw_arg_palette = php::getCallArg(9);
        if (UNEXPECTED(!(raw_arg_palette.isBool()))) {
            php::throwArgumentTypeError(raw_arg_palette, get_str(359), 10, get_str(160), get_str(307));
        }
        php::Bool arg_palette = php::toBool(raw_arg_palette);
        php::Var raw_arg_colours = php::getCallArg(10);
        if (UNEXPECTED(!(raw_arg_colours.isInt()))) {
            php::throwArgumentTypeError(raw_arg_colours, get_str(359), 11, get_str(161), get_str(302));
        }
        php::Int arg_colours = php::toInt(raw_arg_colours);
        php::Var raw_arg_dither = php::getCallArg(11);
        if (UNEXPECTED(!((raw_arg_dither.isFloat() || raw_arg_dither.isInt())))) {
            php::throwArgumentTypeError(raw_arg_dither, get_str(359), 12, get_str(163), get_str(304));
        }
        php::Float arg_dither = php::toFloat(raw_arg_dither);
        php::Var raw_arg_adaptiveFiltering = php::getCallArg(12);
        if (UNEXPECTED(!(raw_arg_adaptiveFiltering.isBool()))) {
            php::throwArgumentTypeError(raw_arg_adaptiveFiltering, get_str(359), 13, get_str(164), get_str(307));
        }
        php::Bool arg_adaptiveFiltering = php::toBool(raw_arg_adaptiveFiltering);
        php::Var raw_arg_nearLossless = php::getCallArg(13);
        if (UNEXPECTED(!(raw_arg_nearLossless.isInt()))) {
            php::throwArgumentTypeError(raw_arg_nearLossless, get_str(359), 14, get_str(165), get_str(302));
        }
        php::Int arg_nearLossless = php::toInt(raw_arg_nearLossless);
        php::Var raw_arg_smartSubsample = php::getCallArg(14);
        if (UNEXPECTED(!(raw_arg_smartSubsample.isBool()))) {
            php::throwArgumentTypeError(raw_arg_smartSubsample, get_str(359), 15, get_str(166), get_str(307));
        }
        php::Bool arg_smartSubsample = php::toBool(raw_arg_smartSubsample);
        php::Var raw_arg_alphaQuality = php::getCallArg(15);
        if (UNEXPECTED(!(raw_arg_alphaQuality.isInt()))) {
            php::throwArgumentTypeError(raw_arg_alphaQuality, get_str(359), 16, get_str(167), get_str(302));
        }
        php::Int arg_alphaQuality = php::toInt(raw_arg_alphaQuality);
        php::Var raw_arg_bitdepth = php::getCallArg(16);
        if (UNEXPECTED(!(raw_arg_bitdepth.isInt()))) {
            php::throwArgumentTypeError(raw_arg_bitdepth, get_str(359), 17, get_str(168), get_str(302));
        }
        php::Int arg_bitdepth = php::toInt(raw_arg_bitdepth);
        php::Var raw_arg_compression = php::getCallArg(17);
        if (UNEXPECTED(!(raw_arg_compression.isString()))) {
            php::throwArgumentTypeError(raw_arg_compression, get_str(359), 18, get_str(169), get_str(203));
        }
        php::Str arg_compression = php::toString(raw_arg_compression);
        php::Var raw_arg_predictor = php::getCallArg(18);
        if (UNEXPECTED(!(raw_arg_predictor.isString()))) {
            php::throwArgumentTypeError(raw_arg_predictor, get_str(359), 19, get_str(170), get_str(203));
        }
        php::Str arg_predictor = php::toString(raw_arg_predictor);
        php::Var raw_arg_tile = php::getCallArg(19);
        if (UNEXPECTED(!(raw_arg_tile.isBool()))) {
            php::throwArgumentTypeError(raw_arg_tile, get_str(359), 20, get_str(142), get_str(307));
        }
        php::Bool arg_tile = php::toBool(raw_arg_tile);
        php::Var raw_arg_tileWidth = php::getCallArg(20);
        if (UNEXPECTED(!(raw_arg_tileWidth.isInt()))) {
            php::throwArgumentTypeError(raw_arg_tileWidth, get_str(359), 21, get_str(171), get_str(302));
        }
        php::Int arg_tileWidth = php::toInt(raw_arg_tileWidth);
        php::Var raw_arg_tileHeight = php::getCallArg(21);
        if (UNEXPECTED(!(raw_arg_tileHeight.isInt()))) {
            php::throwArgumentTypeError(raw_arg_tileHeight, get_str(359), 22, get_str(172), get_str(302));
        }
        php::Int arg_tileHeight = php::toInt(raw_arg_tileHeight);
        php::Var raw_arg_pyramid = php::getCallArg(22);
        if (UNEXPECTED(!(raw_arg_pyramid.isBool()))) {
            php::throwArgumentTypeError(raw_arg_pyramid, get_str(359), 23, get_str(173), get_str(307));
        }
        php::Bool arg_pyramid = php::toBool(raw_arg_pyramid);
        php::Var raw_arg_loop = php::getCallArg(23);
        if (UNEXPECTED(!(raw_arg_loop.isInt()))) {
            php::throwArgumentTypeError(raw_arg_loop, get_str(359), 24, get_str(174), get_str(302));
        }
        php::Int arg_loop = php::toInt(raw_arg_loop);
        php::Var raw_arg_delay = php::getCallArg(24);
        if (UNEXPECTED(!(raw_arg_delay.isString()))) {
            php::throwArgumentTypeError(raw_arg_delay, get_str(359), 25, get_str(175), get_str(203));
        }
        php::Str arg_delay = php::toString(raw_arg_delay);
        php::Var raw_arg_minSize = php::getCallArg(25);
        if (UNEXPECTED(!(raw_arg_minSize.isBool()))) {
            php::throwArgumentTypeError(raw_arg_minSize, get_str(359), 26, get_str(176), get_str(307));
        }
        php::Bool arg_minSize = php::toBool(raw_arg_minSize);
        php::Var raw_arg_mixed = php::getCallArg(26);
        if (UNEXPECTED(!(raw_arg_mixed.isBool()))) {
            php::throwArgumentTypeError(raw_arg_mixed, get_str(359), 27, get_str(177), get_str(307));
        }
        php::Bool arg_mixed = php::toBool(raw_arg_mixed);
        php::Var raw_arg_interframeMaxError = php::getCallArg(27);
        if (UNEXPECTED(!((raw_arg_interframeMaxError.isFloat() || raw_arg_interframeMaxError.isInt())))) {
            php::throwArgumentTypeError(raw_arg_interframeMaxError, get_str(359), 28, get_str(361), get_str(304));
        }
        php::Float arg_interframeMaxError = php::toFloat(raw_arg_interframeMaxError);
        php::Var raw_arg_interpaletteMaxError = php::getCallArg(28);
        if (UNEXPECTED(!((raw_arg_interpaletteMaxError.isFloat() || raw_arg_interpaletteMaxError.isInt())))) {
            php::throwArgumentTypeError(raw_arg_interpaletteMaxError, get_str(359), 29, get_str(362), get_str(304));
        }
        php::Float arg_interpaletteMaxError = php::toFloat(raw_arg_interpaletteMaxError);
        php::Var raw_arg_reuse = php::getCallArg(29);
        if (UNEXPECTED(!(raw_arg_reuse.isBool()))) {
            php::throwArgumentTypeError(raw_arg_reuse, get_str(359), 30, get_str(180), get_str(307));
        }
        php::Bool arg_reuse = php::toBool(raw_arg_reuse);
        php::Var raw_arg_optimizeCoding = php::getCallArg(30);
        if (UNEXPECTED(!(raw_arg_optimizeCoding.isBool()))) {
            php::throwArgumentTypeError(raw_arg_optimizeCoding, get_str(359), 31, get_str(182), get_str(307));
        }
        php::Bool arg_optimizeCoding = php::toBool(raw_arg_optimizeCoding);
        auto retval = php_pixelforge_output(php::takeValue(arg_h),php::takeValue(arg_format),arg_quality,arg_lossless,arg_effort,arg_progressive,php::takeValue(arg_chroma),arg_mozjpeg,arg_compressionLevel,arg_palette,arg_colours,arg_dither,arg_adaptiveFiltering,arg_nearLossless,arg_smartSubsample,arg_alphaQuality,arg_bitdepth,php::takeValue(arg_compression),php::takeValue(arg_predictor),arg_tile,arg_tileWidth,arg_tileHeight,arg_pyramid,arg_loop,php::takeValue(arg_delay),arg_minSize,arg_mixed,arg_interframeMaxError,arg_interpaletteMaxError,arg_reuse,arg_optimizeCoding);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_tile) {
    PHPX_TRY {
        php::checkCallArgCount(15, 15, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_size = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_size.isInt()))) {
            php::throwArgumentTypeError(raw_arg_size, get_str(194), 2, get_str(184), get_str(302));
        }
        php::Int arg_size = php::toInt(raw_arg_size);
        php::Var raw_arg_overlap = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_overlap.isInt()))) {
            php::throwArgumentTypeError(raw_arg_overlap, get_str(194), 3, get_str(185), get_str(302));
        }
        php::Int arg_overlap = php::toInt(raw_arg_overlap);
        php::Var raw_arg_angle = php::getCallArg(3);
        if (UNEXPECTED(!(raw_arg_angle.isInt()))) {
            php::throwArgumentTypeError(raw_arg_angle, get_str(194), 4, get_str(87), get_str(302));
        }
        php::Int arg_angle = php::toInt(raw_arg_angle);
        php::Var raw_arg_layout = php::getCallArg(4);
        if (UNEXPECTED(!(raw_arg_layout.isString()))) {
            php::throwArgumentTypeError(raw_arg_layout, get_str(194), 5, get_str(186), get_str(203));
        }
        php::Str arg_layout = php::toString(raw_arg_layout);
        php::Var raw_arg_container = php::getCallArg(5);
        if (UNEXPECTED(!(raw_arg_container.isString()))) {
            php::throwArgumentTypeError(raw_arg_container, get_str(194), 6, get_str(188), get_str(203));
        }
        php::Str arg_container = php::toString(raw_arg_container);
        php::Var raw_arg_depth = php::getCallArg(6);
        if (UNEXPECTED(!(raw_arg_depth.isString()))) {
            php::throwArgumentTypeError(raw_arg_depth, get_str(194), 7, get_str(13), get_str(203));
        }
        php::Str arg_depth = php::toString(raw_arg_depth);
        php::Var raw_arg_skipBlanks = php::getCallArg(7);
        if (UNEXPECTED(!(raw_arg_skipBlanks.isBool()))) {
            php::throwArgumentTypeError(raw_arg_skipBlanks, get_str(194), 8, get_str(190), get_str(307));
        }
        php::Bool arg_skipBlanks = php::toBool(raw_arg_skipBlanks);
        php::Var raw_arg_centre = php::getCallArg(8);
        if (UNEXPECTED(!(raw_arg_centre.isBool()))) {
            php::throwArgumentTypeError(raw_arg_centre, get_str(194), 9, get_str(62), get_str(307));
        }
        php::Bool arg_centre = php::toBool(raw_arg_centre);
        php::Var raw_arg_basename = php::getCallArg(9);
        if (UNEXPECTED(!(raw_arg_basename.isString()))) {
            php::throwArgumentTypeError(raw_arg_basename, get_str(194), 10, get_str(192), get_str(203));
        }
        php::Str arg_basename = php::toString(raw_arg_basename);
        php::Var raw_arg_id = php::getCallArg(10);
        if (UNEXPECTED(!(raw_arg_id.isString()))) {
            php::throwArgumentTypeError(raw_arg_id, get_str(194), 11, get_str(193), get_str(203));
        }
        php::Str arg_id = php::toString(raw_arg_id);
        php::Var raw_arg_r = php::getCallArg(11);
        if (UNEXPECTED(!((raw_arg_r.isFloat() || raw_arg_r.isInt())))) {
            php::throwArgumentTypeError(raw_arg_r, get_str(194), 12, get_str(19), get_str(304));
        }
        php::Float arg_r = php::toFloat(raw_arg_r);
        php::Var raw_arg_g = php::getCallArg(12);
        if (UNEXPECTED(!((raw_arg_g.isFloat() || raw_arg_g.isInt())))) {
            php::throwArgumentTypeError(raw_arg_g, get_str(194), 13, get_str(20), get_str(304));
        }
        php::Float arg_g = php::toFloat(raw_arg_g);
        php::Var raw_arg_b = php::getCallArg(13);
        if (UNEXPECTED(!((raw_arg_b.isFloat() || raw_arg_b.isInt())))) {
            php::throwArgumentTypeError(raw_arg_b, get_str(194), 14, get_str(21), get_str(304));
        }
        php::Float arg_b = php::toFloat(raw_arg_b);
        php::Var raw_arg_a = php::getCallArg(14);
        if (UNEXPECTED(!((raw_arg_a.isFloat() || raw_arg_a.isInt())))) {
            php::throwArgumentTypeError(raw_arg_a, get_str(194), 15, get_str(22), get_str(304));
        }
        php::Float arg_a = php::toFloat(raw_arg_a);
        auto retval = php_pixelforge_tile(php::takeValue(arg_h),arg_size,arg_overlap,arg_angle,php::takeValue(arg_layout),php::takeValue(arg_container),php::takeValue(arg_depth),arg_skipBlanks,arg_centre,php::takeValue(arg_basename),php::takeValue(arg_id),arg_r,arg_g,arg_b,arg_a);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_keep) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_flags = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_flags.isInt()))) {
            php::throwArgumentTypeError(raw_arg_flags, get_str(363), 2, get_str(323), get_str(302));
        }
        php::Int arg_flags = php::toInt(raw_arg_flags);
        auto retval = php_pixelforge_keep(php::takeValue(arg_h),arg_flags);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_icc) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_profile = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_profile.isString()))) {
            php::throwArgumentTypeError(raw_arg_profile, get_str(364), 2, get_str(321), get_str(203));
        }
        php::Str arg_profile = php::toString(raw_arg_profile);
        auto retval = php_pixelforge_icc(php::takeValue(arg_h),php::takeValue(arg_profile));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_exif) {
    PHPX_TRY {
        php::checkCallArgCount(3, 3, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_flat = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_flat.isString()))) {
            php::throwArgumentTypeError(raw_arg_flat, get_str(365), 2, get_str(366), get_str(203));
        }
        php::Str arg_flat = php::toString(raw_arg_flat);
        php::Var raw_arg_merge = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_merge.isBool()))) {
            php::throwArgumentTypeError(raw_arg_merge, get_str(365), 3, get_str(367), get_str(307));
        }
        php::Bool arg_merge = php::toBool(raw_arg_merge);
        auto retval = php_pixelforge_exif(php::takeValue(arg_h),php::takeValue(arg_flat),arg_merge);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_timeout) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_seconds = php::getCallArg(1);
        if (UNEXPECTED(!((raw_arg_seconds.isFloat() || raw_arg_seconds.isInt())))) {
            php::throwArgumentTypeError(raw_arg_seconds, get_str(368), 2, get_str(195), get_str(304));
        }
        php::Float arg_seconds = php::toFloat(raw_arg_seconds);
        auto retval = php_pixelforge_timeout(php::takeValue(arg_h),arg_seconds);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_to_buffer) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_format = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_format.isString()))) {
            php::throwArgumentTypeError(raw_arg_format, get_str(369), 2, get_str(206), get_str(203));
        }
        php::Str arg_format = php::toString(raw_arg_format);
        auto retval = php_pixelforge_to_buffer(php::takeValue(arg_h),php::takeValue(arg_format));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_to_file) {
    PHPX_TRY {
        php::checkCallArgCount(2, 2, false);
        php::Var arg_h = php::getCallArg(0);
        php::Var raw_arg_path = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_path.isString()))) {
            php::throwArgumentTypeError(raw_arg_path, get_str(370), 2, get_str(298), get_str(203));
        }
        php::Str arg_path = php::toString(raw_arg_path);
        auto retval = php_pixelforge_to_file(php::takeValue(arg_h),php::takeValue(arg_path));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_metadata) {
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_h = php::getCallArg(0);
        auto retval = php_pixelforge_metadata(php::takeValue(arg_h));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_stats) {
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var arg_h = php::getCallArg(0);
        auto retval = php_pixelforge_stats(php::takeValue(arg_h));
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_concurrency) {
    PHPX_TRY {
        php::checkCallArgCount(1, 1, false);
        php::Var raw_arg_n = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_n.isInt()))) {
            php::throwArgumentTypeError(raw_arg_n, get_str(294), 1, get_str(295), get_str(302));
        }
        php::Int arg_n = php::toInt(raw_arg_n);
        auto retval = php_pixelforge_concurrency(arg_n);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_get_concurrency) {
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge_get_concurrency();
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_cache) {
    PHPX_TRY {
        php::checkCallArgCount(3, 3, false);
        php::Var raw_arg_memoryMb = php::getCallArg(0);
        if (UNEXPECTED(!(raw_arg_memoryMb.isInt()))) {
            php::throwArgumentTypeError(raw_arg_memoryMb, get_str(371), 1, get_str(326), get_str(302));
        }
        php::Int arg_memoryMb = php::toInt(raw_arg_memoryMb);
        php::Var raw_arg_files = php::getCallArg(1);
        if (UNEXPECTED(!(raw_arg_files.isInt()))) {
            php::throwArgumentTypeError(raw_arg_files, get_str(371), 2, get_str(327), get_str(302));
        }
        php::Int arg_files = php::toInt(raw_arg_files);
        php::Var raw_arg_items = php::getCallArg(2);
        if (UNEXPECTED(!(raw_arg_items.isInt()))) {
            php::throwArgumentTypeError(raw_arg_items, get_str(371), 3, get_str(328), get_str(302));
        }
        php::Int arg_items = php::toInt(raw_arg_items);
        auto retval = php_pixelforge_cache(arg_memoryMb,arg_files,arg_items);
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_versions) {
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge_versions();
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_formats) {
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge_formats();
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

ZEND_FUNCTION(pixelforge_memory) {
    PHPX_TRY {
        php::checkCallArgCount(0, 0, false);
        auto retval = php_pixelforge_memory();
        php::move(retval, return_value);
        php::deref(return_value);
    } PHPX_CATCH(zend_object *, typephp_wrapper_exception) {
        /* EG(exception) is already set; return control to ZendVM for frame cleanup. */
    }
}

// default argument values 
php::Array php_pixelforge__image__fromfile_arg_1_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__frombuffer_arg_1_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__join_arg_1_default_value() {
return php::Array{};
}

php::Var php_pixelforge__image__resize_arg_0_default_value() {
return php::null;
}

php::Var php_pixelforge__image__resize_arg_1_default_value() {
return php::null;
}

php::Array php_pixelforge__image__resize_arg_2_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__trim_arg_0_default_value() {
return php::Array{};
}

php::Var php_pixelforge__image__rotate_arg_0_default_value() {
return php::null;
}

php::Array php_pixelforge__image__rotate_arg_1_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__affine_arg_1_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__sharpen_arg_0_default_value() {
return php::Array{};
}

php::Int php_pixelforge__image__median_arg_0_default_value() {
return 3L;
}

php::Var php_pixelforge__image__blur_arg_0_default_value() {
return 0.0;
}

php::Array php_pixelforge__image__flatten_arg_0_default_value() {
return php::Array{};
}

php::Float php_pixelforge__image__gamma_arg_0_default_value() {
return 2.2000000000000002;
}

php::Var php_pixelforge__image__gamma_arg_1_default_value() {
return php::null;
}

php::Array php_pixelforge__image__negate_arg_0_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__normalise_arg_0_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__normalize_arg_0_default_value() {
return php::Array{};
}

php::Int php_pixelforge__image__threshold_arg_0_default_value() {
return 128L;
}

php::Array php_pixelforge__image__threshold_arg_1_default_value() {
return php::Array{};
}

php::Var php_pixelforge__image__linear_arg_0_default_value() {
return 1.0;
}

php::Var php_pixelforge__image__linear_arg_1_default_value() {
return 0.0;
}

php::Bool php_pixelforge__image__greyscale_arg_0_default_value() {
return true;
}

php::Bool php_pixelforge__image__grayscale_arg_0_default_value() {
return true;
}

php::Float php_pixelforge__image__ensurealpha_arg_0_default_value() {
return 1.0;
}

php::Int php_pixelforge__image__dilate_arg_0_default_value() {
return 1L;
}

php::Int php_pixelforge__image__erode_arg_0_default_value() {
return 1L;
}

php::Array php_pixelforge__image__jpeg_arg_0_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__png_arg_0_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__webp_arg_0_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__avif_arg_0_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__heif_arg_0_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__gif_arg_0_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__tiff_arg_0_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__jxl_arg_0_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__toformat_arg_1_default_value() {
return php::Array{};
}

php::Array php_pixelforge__image__tile_arg_0_default_value() {
return php::Array{};
}

php::Var php_pixelforge__image__tobuffer_arg_0_default_value() {
return php::null;
}

php::Var php_pixelforge__image__tobufferwithinfo_arg_0_default_value() {
return php::null;
}

php::Var php_pixelforge__pixelforge__concurrency_arg_0_default_value() {
return php::null;
}

php::Int php_pixelforge__pixelforge__cache_arg_0_default_value() {
return 50L;
}

php::Int php_pixelforge__pixelforge__cache_arg_1_default_value() {
return 20L;
}

php::Int php_pixelforge__pixelforge__cache_arg_2_default_value() {
return 100L;
}

namespace typephp_project_pixelforge {

// constants 
// class 
static zend_object_handlers property_handlers_PixelForge_PixelForgeException;
static zend_object_handlers property_handlers_PixelForge_Image;
static zend_object_handlers property_handlers_PixelForge_Gravity;
static zend_object_handlers property_handlers_PixelForge_Color;
static zend_object_handlers property_handlers_PixelForge_PixelForge;
// clang-format off
static const zend_function_entry ext_functions[] = {
    ZEND_RAW_FENTRY("pixelforge_from_file", ZEND_FN(pixelforge_from_file), arginfo_pixelforge_from_file, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_from_buffer", ZEND_FN(pixelforge_from_buffer), arginfo_pixelforge_from_buffer, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_from_raw", ZEND_FN(pixelforge_from_raw), arginfo_pixelforge_from_raw, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_create", ZEND_FN(pixelforge_create), arginfo_pixelforge_create, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_text", ZEND_FN(pixelforge_text), arginfo_pixelforge_text, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_join_new", ZEND_FN(pixelforge_join_new), arginfo_pixelforge_join_new, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_join_add", ZEND_FN(pixelforge_join_add), arginfo_pixelforge_join_add, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_clone", ZEND_FN(pixelforge_clone), arginfo_pixelforge_clone, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_resize", ZEND_FN(pixelforge_resize), arginfo_pixelforge_resize, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_extract", ZEND_FN(pixelforge_extract), arginfo_pixelforge_extract, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_extend", ZEND_FN(pixelforge_extend), arginfo_pixelforge_extend, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_trim", ZEND_FN(pixelforge_trim), arginfo_pixelforge_trim, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_rotate", ZEND_FN(pixelforge_rotate), arginfo_pixelforge_rotate, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_auto_orient", ZEND_FN(pixelforge_auto_orient), arginfo_pixelforge_auto_orient, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_flip", ZEND_FN(pixelforge_flip), arginfo_pixelforge_flip, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_flop", ZEND_FN(pixelforge_flop), arginfo_pixelforge_flop, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_affine", ZEND_FN(pixelforge_affine), arginfo_pixelforge_affine, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_sharpen", ZEND_FN(pixelforge_sharpen), arginfo_pixelforge_sharpen, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_median", ZEND_FN(pixelforge_median), arginfo_pixelforge_median, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_blur", ZEND_FN(pixelforge_blur), arginfo_pixelforge_blur, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_flatten", ZEND_FN(pixelforge_flatten), arginfo_pixelforge_flatten, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_unflatten", ZEND_FN(pixelforge_unflatten), arginfo_pixelforge_unflatten, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_gamma", ZEND_FN(pixelforge_gamma), arginfo_pixelforge_gamma, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_negate", ZEND_FN(pixelforge_negate), arginfo_pixelforge_negate, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_normalise", ZEND_FN(pixelforge_normalise), arginfo_pixelforge_normalise, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_clahe", ZEND_FN(pixelforge_clahe), arginfo_pixelforge_clahe, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_threshold", ZEND_FN(pixelforge_threshold), arginfo_pixelforge_threshold, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_linear", ZEND_FN(pixelforge_linear), arginfo_pixelforge_linear, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_modulate", ZEND_FN(pixelforge_modulate), arginfo_pixelforge_modulate, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_tint", ZEND_FN(pixelforge_tint), arginfo_pixelforge_tint, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_colourspace", ZEND_FN(pixelforge_colourspace), arginfo_pixelforge_colourspace, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_remove_alpha", ZEND_FN(pixelforge_remove_alpha), arginfo_pixelforge_remove_alpha, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_ensure_alpha", ZEND_FN(pixelforge_ensure_alpha), arginfo_pixelforge_ensure_alpha, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_extract_channel", ZEND_FN(pixelforge_extract_channel), arginfo_pixelforge_extract_channel, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_join_channel", ZEND_FN(pixelforge_join_channel), arginfo_pixelforge_join_channel, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_bandbool", ZEND_FN(pixelforge_bandbool), arginfo_pixelforge_bandbool, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_boolean", ZEND_FN(pixelforge_boolean), arginfo_pixelforge_boolean, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_dilate", ZEND_FN(pixelforge_dilate), arginfo_pixelforge_dilate, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_erode", ZEND_FN(pixelforge_erode), arginfo_pixelforge_erode, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_convolve", ZEND_FN(pixelforge_convolve), arginfo_pixelforge_convolve, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_recomb", ZEND_FN(pixelforge_recomb), arginfo_pixelforge_recomb, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_composite", ZEND_FN(pixelforge_composite), arginfo_pixelforge_composite, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_output", ZEND_FN(pixelforge_output), arginfo_pixelforge_output, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_tile", ZEND_FN(pixelforge_tile), arginfo_pixelforge_tile, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_keep", ZEND_FN(pixelforge_keep), arginfo_pixelforge_keep, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_icc", ZEND_FN(pixelforge_icc), arginfo_pixelforge_icc, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_exif", ZEND_FN(pixelforge_exif), arginfo_pixelforge_exif, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_timeout", ZEND_FN(pixelforge_timeout), arginfo_pixelforge_timeout, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_to_buffer", ZEND_FN(pixelforge_to_buffer), arginfo_pixelforge_to_buffer, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_to_file", ZEND_FN(pixelforge_to_file), arginfo_pixelforge_to_file, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_metadata", ZEND_FN(pixelforge_metadata), arginfo_pixelforge_metadata, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_stats", ZEND_FN(pixelforge_stats), arginfo_pixelforge_stats, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_concurrency", ZEND_FN(pixelforge_concurrency), arginfo_pixelforge_concurrency, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_get_concurrency", ZEND_FN(pixelforge_get_concurrency), arginfo_pixelforge_get_concurrency, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_cache", ZEND_FN(pixelforge_cache), arginfo_pixelforge_cache, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_versions", ZEND_FN(pixelforge_versions), arginfo_pixelforge_versions, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_formats", ZEND_FN(pixelforge_formats), arginfo_pixelforge_formats, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_RAW_FENTRY("pixelforge_memory", ZEND_FN(pixelforge_memory), arginfo_pixelforge_memory, ZEND_ACC_STRICT_TYPES, NULL, NULL)
    ZEND_FE_END
};
// clang-format on

PHP_MINIT_FUNCTION(pixelforge) {
// class/interface class entries
if (typephp_install_reflection_attribute_handlers() != SUCCESS) {
    return FAILURE;
}
typephp_register_fiber_generator_class();
if (type == MODULE_TEMPORARY) {
    EG(current_module)->type = MODULE_PERSISTENT;
    zend_interned_strings_switch_storage(false);
}
php_class_entry_RuntimeException = php::getInternalClassEntrySafe("RuntimeException");
php_class_entry_PixelForge_PixelForgeException = php_register_class_PixelForge_PixelForgeException(php_class_entry_RuntimeException);
const auto *base_property_handlers_PixelForge_PixelForgeException = php_class_entry_PixelForge_PixelForgeException->default_object_handlers;
typephp_install_property_handlers(php_class_entry_PixelForge_PixelForgeException, &property_handlers_PixelForge_PixelForgeException);
property_handlers_PixelForge_PixelForgeException.read_property = base_property_handlers_PixelForge_PixelForgeException->read_property;
property_handlers_PixelForge_PixelForgeException.write_property = base_property_handlers_PixelForge_PixelForgeException->write_property;
php_class_entry_PixelForge_Image = php_register_class_PixelForge_Image();
const auto *base_property_handlers_PixelForge_Image = php_class_entry_PixelForge_Image->default_object_handlers;
typephp_install_property_handlers(php_class_entry_PixelForge_Image, &property_handlers_PixelForge_Image);
property_handlers_PixelForge_Image.read_property = base_property_handlers_PixelForge_Image->read_property;
property_handlers_PixelForge_Image.write_property = base_property_handlers_PixelForge_Image->write_property;
php_class_entry_PixelForge_Gravity = php_register_class_PixelForge_Gravity();
const auto *base_property_handlers_PixelForge_Gravity = php_class_entry_PixelForge_Gravity->default_object_handlers;
typephp_install_property_handlers(php_class_entry_PixelForge_Gravity, &property_handlers_PixelForge_Gravity);
property_handlers_PixelForge_Gravity.read_property = base_property_handlers_PixelForge_Gravity->read_property;
property_handlers_PixelForge_Gravity.write_property = base_property_handlers_PixelForge_Gravity->write_property;
php_class_entry_PixelForge_Color = php_register_class_PixelForge_Color();
const auto *base_property_handlers_PixelForge_Color = php_class_entry_PixelForge_Color->default_object_handlers;
typephp_install_property_handlers(php_class_entry_PixelForge_Color, &property_handlers_PixelForge_Color);
property_handlers_PixelForge_Color.read_property = base_property_handlers_PixelForge_Color->read_property;
property_handlers_PixelForge_Color.write_property = base_property_handlers_PixelForge_Color->write_property;
php_class_entry_PixelForge_PixelForge = php_register_class_PixelForge_PixelForge();
const auto *base_property_handlers_PixelForge_PixelForge = php_class_entry_PixelForge_PixelForge->default_object_handlers;
typephp_install_property_handlers(php_class_entry_PixelForge_PixelForge, &property_handlers_PixelForge_PixelForge);
property_handlers_PixelForge_PixelForge.read_property = base_property_handlers_PixelForge_PixelForge->read_property;
property_handlers_PixelForge_PixelForge.write_property = base_property_handlers_PixelForge_PixelForge->write_property;

// register symbols
if (type == MODULE_TEMPORARY) {
    zend_interned_strings_switch_storage(true);
    EG(current_module)->type = MODULE_TEMPORARY;
}
return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(pixelforge) {
for (auto &slot : php_persistent_class_map) {
    php::resetPersistentCache(slot);
}
for (auto &slot : php_persistent_func_map) {
    php::resetPersistentCache(slot);
}
for (auto &slot : php_persistent_property_map) {
    php::resetPersistentCache(slot);
}
typephp_unregister_fiber_generator_class();
typephp_uninstall_reflection_attribute_handlers();
return SUCCESS;
}

THREAD_LOCAL zval globals_array;
static void module_init() {
// register constants
// global vars 
// static property 
// class array constants
}

static void module_clean() {
// class array constants
}

PHP_RINIT_FUNCTION(pixelforge) {
if (UNEXPECTED(php_request_cache != nullptr)) {
    php_error_docref(nullptr, E_WARNING, "TypePHP request cache is already initialized");
    return FAILURE;
}
php_request_cache = new (std::nothrow) php_request_cache_storage{};
if (UNEXPECTED(php_request_cache == nullptr)) {
    php_error_docref(nullptr, E_WARNING, "Unable to allocate TypePHP request cache");
    return FAILURE;
}
php::request_init();
module_init();
return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(pixelforge) {
if (php_request_cache == nullptr) {
return SUCCESS;
}
php::request_shutdown();
module_clean();
delete php_request_cache;
php_request_cache = nullptr;
    return SUCCESS;
}
PHP_MINFO_FUNCTION(pixelforge) {
    php_info_print_table_start();
    php_info_print_table_header(2, "pixelforge support", "enabled");
    php_info_print_table_row(2, "Description", "High performance image processing for PHP (libvips), API modelled on sharp");
    php_info_print_table_row(2, "License", "Apache-2.0");
    php_info_print_table_end();
}

zend_module_entry pixelforge_module_entry = {
    STANDARD_MODULE_HEADER,
    "pixelforge",
    ext_functions,
    PHP_MINIT(pixelforge),
    PHP_MSHUTDOWN(pixelforge),
    PHP_RINIT(pixelforge),
    PHP_RSHUTDOWN(pixelforge),
    PHP_MINFO(pixelforge),
    "0.1.1",
    STANDARD_MODULE_PROPERTIES,
};

ZEND_GET_MODULE(pixelforge);
}  // namespace typephp_project_pixelforge
