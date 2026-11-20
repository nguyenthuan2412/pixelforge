# pixelforge

[![CI](https://github.com/nguyenthuan2412/pixelforge/actions/workflows/ci.yml/badge.svg)](https://github.com/nguyenthuan2412/pixelforge/actions/workflows/ci.yml)
[![Release](https://img.shields.io/github/v/release/nguyenthuan2412/pixelforge)](https://github.com/nguyenthuan2412/pixelforge/releases)
![PHP](https://img.shields.io/badge/PHP-8.4%20%7C%208.5-777bb4)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue)](LICENSE)

**Fast, low-memory image processing for PHP.** Resize, crop, convert and watermark images
with a chainable API modelled on Node.js [sharp](https://sharp.pixelplumbing.com/), powered by [libvips](https://www.libvips.org/).

```php
use PixelForge\Image;

Image::fromFile('photo.jpg')->resize(800)->webp(['quality' => 80])->toFile('photo.webp');
```

- ⚡ **As fast as sharp**, about **3× faster than GD** and **20× faster than Imagick**, with 2–4× less memory ([benchmarks](#performance))
- 🖼️ JPEG, PNG, WebP, AVIF, HEIF, GIF, TIFF, animated GIF/WebP, SVG input
- 🧩 Installs with **PIE**, **PECL** or **Docker**. Linux and macOS.

---

## Contents

[Install](#install) · [Quick start](#quick-start) · [Recipes](#recipes) · [Options](#options) ·
[API](#api-reference) · [Performance](#performance) · [Troubleshooting](#troubleshooting) · [Limitations](#limitations)

---

## Install

You need **PHP 8.4 or 8.5** (non-thread-safe, the default build) and **libvips 8.15+**.
Pick the section that matches your system.

### Docker: try it in 1 minute

```bash
git clone https://github.com/nguyenthuan2412/pixelforge && cd pixelforge
docker build -t pixelforge .
docker run --rm -v "$PWD":/work -w /work pixelforge php -r '
  PixelForge\Image::fromFile("/app/fixtures/large.jpg")->resize(400)->toFile("thumb.jpg");
  echo "done\n";'
```

### Ubuntu / Debian

```bash
# 1. PHP 8.4/8.5 headers + libvips
sudo apt install php8.4-dev libvips-dev libgmp-dev libmpfr-dev pkg-config git unzip
#    (Ubuntu ships PHP 8.3: add `sudo add-apt-repository ppa:ondrej/php` first, then use php8.4-dev or php8.5-dev)

# 2. PIE, the official PHP extension installer
curl -fsSL -o pie.phar https://github.com/php/pie/releases/latest/download/pie.phar
sudo install pie.phar /usr/local/bin/pie

# 3. pixelforge (PIE builds it, writes the .ini and enables it)
pie repository:add vcs https://github.com/nguyenthuan2412/pixelforge
pie install nguyenthuan2412/pixelforge
```

### macOS (Homebrew)

```bash
brew install php vips gmp mpfr pkg-config pie
pie repository:add vcs https://github.com/nguyenthuan2412/pixelforge
pie install nguyenthuan2412/pixelforge
```

### In your own Dockerfile

```dockerfile
FROM php:8.5-fpm
RUN apt-get update && apt-get install -y --no-install-recommends libvips-dev libgmp-dev libmpfr-dev pkg-config \
 && curl -fsSLO https://github.com/nguyenthuan2412/pixelforge/releases/download/v0.1.3/pixelforge-0.1.3.tgz \
 && printf "\n" | pecl install pixelforge-0.1.3.tgz \
 && docker-php-ext-enable pixelforge \
 && rm pixelforge-0.1.3.tgz && rm -rf /var/lib/apt/lists/*
```

### In your own Dockerfile (Alpine)

```dockerfile
FROM php:8.5-cli-alpine
RUN apk add --no-cache --virtual .build vips-dev gmp-dev mpfr-dev build-base autoconf pkgconf linux-headers curl \
 && curl -fsSLO https://github.com/nguyenthuan2412/pixelforge/releases/download/v0.1.3/pixelforge-0.1.3.tgz \
 && printf "\n" | pecl install pixelforge-0.1.3.tgz \
 && docker-php-ext-enable pixelforge \
 && runDeps="$(scanelf --needed --nobanner --format '%n#p' --recursive /usr/local/lib/php/extensions \
      | tr ',' '\n' | sort -u | awk 'system("[ -e /usr/local/lib/" $1 " ]") == 0 { next } { print "so:" $1 }')" \
 && apk add --no-cache --virtual .pixelforge-rundeps $runDeps \
 && rm pixelforge-0.1.3.tgz && apk del .build
```

Alpine's libheif has no AV1 encoder, so `avif()` isn't available there. `PixelForge::format()` reports which
formats can be read and written on the current machine.

### PECL (without PIE)

```bash
curl -fsSLO https://github.com/nguyenthuan2412/pixelforge/releases/download/v0.1.3/pixelforge-0.1.3.tgz
pecl install pixelforge-0.1.3.tgz        # press Enter at the libvips prompt to use pkg-config
# then add `extension=pixelforge` to your php.ini
```

Download the `.tgz` first, because `pecl install <url>` can't follow GitHub's download redirect.

### Check it works

```bash
php --ri pixelforge
php -r 'print_r(PixelForge\PixelForge::versions());'
```

### Optional: the faster libvips build

Distro libvips works fine. For the fastest results (the numbers in [Performance](#performance)), use the same libvips
bundle that sharp ships, which is built with mozjpeg, zlib-ng and SIMD:

```bash
git clone https://github.com/nguyenthuan2412/pixelforge && cd pixelforge
sudo scripts/install-libvips.sh /opt/sharp-libvips          # Linux x64/arm64 (glibc or musl), macOS
pie install nguyenthuan2412/pixelforge --with-pixelforge-vips=/opt/sharp-libvips
```

---

## Quick start

```php
use PixelForge\Image;

// open → operations → format → save
Image::fromFile('photo.jpg')          // or Image::fromBuffer($bytes)
    ->rotate()                        // fix orientation from EXIF
    ->resize(300, 300)                // crop to fill 300×300 (default fit: cover)
    ->jpeg(['quality' => 85])         // pick a format (optional: inferred from the file name)
    ->toFile('thumb.jpg');            // or ->toBuffer() to get the bytes
```

Nothing is decoded until `toFile()` or `toBuffer()`. JPEG and WebP are decoded at reduced size when you shrink, which keeps
large photos fast and memory use low.

## Recipes

**Convert format**

```php
Image::fromFile('photo.jpg')->webp(['quality' => 80])->toFile('photo.webp');
Image::fromFile('photo.jpg')->avif()->toFile('photo.avif');
Image::fromFile('photo.png')->toFile('photo.jpg');           // format from the extension
```

**Handle an upload: make responsive sizes**

```php
$bytes = file_get_contents($_FILES['image']['tmp_name']);
foreach ([480, 960, 1920] as $w) {
    Image::fromBuffer($bytes)
        ->rotate()
        ->resize($w, null, ['withoutEnlargement' => true])   // keep aspect ratio, never upscale
        ->webp(['quality' => 78])
        ->toFile("uploads/photo-$w.webp");
}
```

**Serve an image over HTTP**

```php
$jpeg = Image::fromFile('photo.jpg')->resize(800)->jpeg(['quality' => 82, 'progressive' => true])->toBuffer();
header('Content-Type: image/jpeg');
echo $jpeg;
```

**Fit inside a box with a background / smart crop**

```php
Image::fromFile('photo.jpg')->resize(400, 400, ['fit' => 'contain', 'background' => 'white'])->toFile('boxed.png');
Image::fromFile('photo.jpg')->resize(400, 400, ['position' => 'attention'])->toFile('smart-crop.jpg');
```

**Watermark**

```php
Image::fromFile('photo.jpg')->resize(1200)
    ->composite([['input' => 'logo.png', 'gravity' => 'southeast']])
    ->toFile('watermarked.jpg');
```

**Read metadata** (reads the header only, without decoding pixels)

```php
$m = Image::fromFile('photo.jpg')->metadata();
echo "{$m['width']}x{$m['height']} {$m['format']}";   // 6000x4000 jpeg
```

**Animated GIF → animated WebP**

```php
Image::fromFile('anim.gif', ['animated' => true])->resize(200)->webp()->toFile('anim.webp');
```

**Text and blank canvases**

```php
Image::text(['text' => '<b>Hello</b> world', 'dpi' => 200, 'rgba' => true])->toFile('text.png');
Image::create(['width' => 300, 'height' => 200, 'channels' => 3, 'background' => 'navy'])->toFile('blank.png');
```

**Errors**

```php
use PixelForge\PixelForgeException;

try {
    Image::fromFile('missing.jpg')->toBuffer();
} catch (PixelForgeException $e) {
    echo $e->getMessage();   // Input file is missing: missing.jpg
}
```

Bad arguments, such as an unknown colour, fit, position, kernel or format, throw immediately. An invalid value
is never silently replaced by a default.

**Inputs for `composite()`, `join()`, `joinChannel()` and `boolean()`**

```php
$logo = Image::fromFile('logo.png');           // an Image
'logo.png'                                     // a file path
file_get_contents('logo.png')                  // encoded image bytes (never mistaken for a file name)
['file' => $path]  /  ['buffer' => $bytes]     // explicit, when the data comes from users
['create' => ['width' => 10, 'height' => 10, 'channels' => 4, 'background' => 'red']]
['text' => ['text' => 'Hello', 'rgba' => true]]
```

When the value comes from user input, use `['file' => …]` or `['buffer' => …]` so that what you pass can't be
interpreted any other way.

## Options

### `resize(width, height, options)`

Pass `null` for width or height to keep the aspect ratio.

| `fit` | Result |
|---|---|
| `cover` *(default)* | Fill the box, crop the overflow |
| `contain` | Fit inside the box, pad with `background` |
| `fill` | Stretch to exactly width × height |
| `inside` | Fit inside the box, no padding (result can be smaller) |
| `outside` | Cover the box, no crop (result can be larger) |

| Option | Values |
|---|---|
| `position` / `gravity` | `centre`, `north`, `northeast`, … `northwest`, `top`, `right bottom`, … , `entropy`, `attention` (smart crop; for animations the first frame picks the window) |
| `background` | `'white'`, `'#ff0000'`, `'#ff000080'`, `[255, 0, 0, 0.5]`, `'transparent'` |
| `withoutEnlargement` / `withoutReduction` | `true` to never upscale / downscale |
| `kernel` | `lanczos3` *(default)*, `lanczos2`, `nearest`, `linear`, `cubic`, `mitchell`, `mks2013`, `mks2021` |

### Output formats

| Method | Common options |
|---|---|
| `jpeg()` | `quality` (80), `progressive`, `chromaSubsampling` (`'4:4:4'`), `mozjpeg` |
| `png()` | `compressionLevel` (6), `palette`, `colours`, `quality`, `progressive` |
| `webp()` | `quality` (80), `lossless`, `nearLossless`, `alphaQuality`, `effort` (4) |
| `avif()` / `heif()` | `quality` (50), `lossless`, `effort` (4), `chromaSubsampling` |
| `gif()` | `colours` (256), `effort`, `dither`, `loop`, `delay` |
| `tiff()` | `quality`, `compression` (`jpeg`, `deflate`, `lzw`, `webp`, …), `tile`, `pyramid` |
| `jxl()` | `quality`, `lossless`, `effort` (only when libvips has JPEG XL) |
| `raw()` | uncompressed pixels |

Metadata (EXIF, ICC, XMP) is **removed by default**, as in sharp. Keep it with `keepMetadata()`, or write your own with
`withExif([...])` and `withIccProfile('p3')`.

## API reference

Everything is in the `PixelForge` namespace.

| Area | Methods |
|---|---|
| **Open** | `Image::fromFile($path, $o)`, `Image::fromBuffer($bytes, $o)`, `Image::fromRaw($pixels, [width, height, channels])`, `Image::create([...])`, `Image::text([...])`, `Image::join([...], [animated, across])` |
| **Open options** | `animated`, `page`, `pages`, `autoOrient`, `failOn`, `limitInputPixels` (default 268 MP; `false` to disable; applies to every source, including `create`, `text`, `fromRaw` and `join`), `density` (SVG/PDF DPI), `ignoreIcc` |
| **Resize & crop** | `resize`, `extract(['left','top','width','height'])`, `extend(int\|[top, bottom, left, right, background, extendWith])`, `trim()` |
| **Rotate & flip** | `rotate(?angle)` *(no angle = EXIF auto-orient)*, `autoOrient`, `flip`, `flop`, `affine` |
| **Adjust** | `sharpen`, `blur`, `median`, `gamma`, `negate`, `normalise`, `clahe`, `threshold`, `linear`, `modulate(['brightness','saturation','hue'])`, `tint`, `greyscale` |
| **Advanced** | `convolve`, `recomb`, `dilate`, `erode`, `boolean`, `bandbool`, `flatten`, `unflatten` |
| **Colour & channels** | `toColourspace`, `removeAlpha`, `ensureAlpha`, `extractChannel`, `joinChannel`, `withIccProfile` |
| **Combine** | `composite([[input, gravity \| left+top, blend, tile]])` |
| **Output** | `jpeg`, `png`, `webp`, `avif`, `heif`, `gif`, `tiff`, `jxl`, `raw`, `toFormat`, `tile` (Deep Zoom, Google Maps, IIIF) |
| **Metadata** | `keepMetadata`, `keepExif`, `keepIccProfile`, `withExif`, `withExifMerge` |
| **Run** | `toFile($path)`, `toBuffer(?$format)`, `toBufferWithInfo()`, `metadata()`, `stats()`, `clone()`, `timeout(['seconds' => n])` |
| **Global** | `PixelForge::versions()`, `PixelForge::format()`, `PixelForge::concurrency(?n)`, `PixelForge::cache()`, `PixelForge::memory()` |

The method names and options follow [sharp's documentation](https://sharp.pixelplumbing.com/api-constructor), so
most sharp examples translate line by line: JS `{ fit: 'contain' }` becomes PHP `['fit' => 'contain']`.

## Performance

Measured against Node.js sharp 0.35.5 on the same libvips build, with a 24 MP JPEG and 4 CPUs (median of 7 rounds):

| Task | sharp | pixelforge | Peak memory sharp → pixelforge |
|---|---|---|---|
| JPEG → 800px JPEG | 43.6 ms | **43.3 ms** | 130 → **51 MB** |
| JPEG → 800px AVIF | 75.3 ms | **73.3 ms** | 137 → **73 MB** |
| resize + watermark | 62.3 ms | **54.7 ms** | 148 → **55 MB** |
| re-encode full 24 MP | 149.1 ms | **136.7 ms** | 454 → **226 MB** |

Against PHP's built-in options on the same task (24 MP JPEG → 800px JPEG, 4 CPUs):

| | Time | Peak memory |
|---|---|---|
| **pixelforge** | **40–68 ms** | **58 MB** |
| GD | 130–224 ms (about 3× slower) | 137 MB |
| Imagick | 835–1231 ms (about 20× slower) | 205 MB |

Method and scripts: [compare/](compare/) (`./compare/run.sh` against sharp, `bench.Dockerfile` + `tests/bench.php` against GD/Imagick).

**PHP-FPM tip:** each worker already runs in parallel, so `PIXELFORGE_CONCURRENCY=1` is usually the best setting.
pixelforge also hands freed memory back to the OS after every image (`PIXELFORGE_TRIM=0` turns this off).

## Troubleshooting

| Problem | Fix |
|---|---|
| `libvips (vips-cpp >= 8.15) not found` | Install `libvips-dev` (Debian/Ubuntu) or `vips` (Homebrew), or pass `--with-pixelforge-vips=/prefix` |
| `libgmp not found` / `libmpfr not found` | `apt install libgmp-dev libmpfr-dev` or `brew install gmp mpfr` |
| `pixelforge requires PHP 8.4 or 8.5` | Install PHP 8.4/8.5 dev headers (`php8.4-dev`). Check `php-config --version` |
| PIE says ZTS is not supported | Use a non-thread-safe PHP build (the default for CLI and FPM) |
| `Class "PixelForge\Image" not found` | The extension isn't loaded: check `php --ri pixelforge` and your `extension=pixelforge` line |
| PIE: `git clone --mirror git@github.com:…` / `Could not read from remote repository` | GitHub API rate limit for anonymous Composer. Run `export COMPOSER_AUTH='{"github-oauth":{"github.com":"<a GitHub token>"}}'` and retry, or use the PECL steps |
| `pecl install https://…` fails | Download the `.tgz` first, then `pecl install pixelforge-x.y.z.tgz` |
| `Output format not available: jxl` / `heifsave: Unsupported compression` | Your libvips (or libheif) was built without that codec. `PixelForge::format()` lists what works. See [Limitations](#limitations) |
| `Fontconfig error` with `Image::text()` | Install a font config: `apt install fontconfig-config fonts-dejavu-core` |

## Limitations

The available codecs depend on how libvips was built. The sharp bundle has exactly the same limits as Node's sharp:

| Feature | sharp (Node) | pixelforge + sharp bundle | pixelforge + Debian libvips |
|---|---|---|---|
| TIFF with zstd | ❌ | ❌ | ✅ |
| JPEG XL | ❌ | ❌ | ✅ |
| HEIF with HEVC | ❌ | ❌ | ✅ (with the x265 plugin) |
| JPEG 2000, PDF input | ❌ | ❌ | install the OpenJPEG / poppler build of libvips |

Not implemented yet: Node-style streams (use `fromBuffer(stream_get_contents($fp))`), `pipelineColourspace`, gain maps.
`stats()` describes the processed image, while sharp's describes the input.

## Development

```
src/            the extension: Image.php (PHP API), pixelforge.cc (libvips core), pixelforge.stub.php
generated/      C++ generated from src/*.php by TypePHP. Don't edit; run scripts/generate.sh
deps/phpx/      bundled PHPX runtime used by the generated code
tests/          *.phpt (make test) and run.php (full suite, run in Docker)
compare/        benchmark against Node.js sharp
```

```bash
phpize && ./configure && make && make test TESTS=tests/     # build + quick tests
docker build -t pixelforge . && docker run --rm pixelforge php /app/tests/run.php   # full suite
scripts/generate.sh                                         # after editing src/Image.php or the stub
```

The PHP API in `src/Image.php` is compiled to C++ by the [TypePHP](https://github.com/swoole/typephp) AOT compiler.
You don't need TypePHP to build or install. To release, push a `vX.Y.Z` tag: CI builds the PECL package and the
GitHub release.

## License

Apache-2.0, see [LICENSE](LICENSE). Bundled third-party code (PHPX, mpdecimal, wren-gc) is listed in [NOTICE](NOTICE).
