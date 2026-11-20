# pixelforge

Fast, low-memory image processing for PHP, built on [libvips](https://www.libvips.org/), with a fluent API
modelled on Node.js [sharp](https://sharp.pixelplumbing.com/).

```php
use PixelForge\Image;

Image::fromFile('in.jpg')
    ->rotate()                                    // auto-orient from EXIF
    ->resize(800, 600, ['fit' => 'cover', 'position' => 'attention'])
    ->webp(['quality' => 80])
    ->toFile('out.webp');
```

- **As fast as sharp, with less memory.** Uses the same libvips build and the same shrink-on-load strategy as sharp.
  Speed is equal or better in every benchmark below, and peak RSS is 2–4× lower.
- **Covers most of sharp's API.** Resize (5 fits, gravity, smart crop, 8 kernels), composite, filters, colour
  management, animated GIF/WebP, text, raw pixels, Deep Zoom tiles, JPEG/PNG/WebP/AVIF/HEIF/GIF/TIFF/JXL output.
- **Builds with standard PHP tooling.** `phpize`, PECL and PIE all work. The C++ in `generated/` is produced by
  the [TypePHP](https://github.com/swoole/typephp) AOT compiler from [src/Image.php](src/Image.php), so building
  doesn't need TypePHP.

Requirements: PHP **8.4 or 8.5** (NTS), libvips **≥ 8.15** (`vips-cpp`), gmp, mpfr, a C++17 compiler.

## Installation

### 1. libvips

Use either your system package:

```bash
sudo apt install libvips-dev libgmp-dev libmpfr-dev pkg-config     # Debian / Ubuntu
brew install vips gmp mpfr pkg-config                               # macOS
```

or **the prebuilt bundle Node's sharp ships** (recommended for speed). It's a single self-contained library built
with mozjpeg, zlib-ng, libwebp 1.6, libheif + aom, and highway SIMD:

```bash
sudo scripts/install-libvips.sh /opt/sharp-libvips     # Linux glibc/musl x64/arm64, macOS x64/arm64
```

### 2. The extension

**PIE**

```bash
pie install nguyenthuan2412/pixelforge
# with the sharp-libvips bundle:
pie install nguyenthuan2412/pixelforge --with-pixelforge-vips=/opt/sharp-libvips
```

**PECL** (package from the [releases page](https://github.com/nguyenthuan2412/pixelforge/releases))

```bash
pecl install https://github.com/nguyenthuan2412/pixelforge/releases/download/v0.1.0/pixelforge-0.1.0.tgz
# then add extension=pixelforge to php.ini
```

**From source**

```bash
phpize && ./configure [--with-pixelforge-vips=/opt/sharp-libvips] && make && sudo make install
make test TESTS=tests/
```

**Docker**

```bash
docker build -t pixelforge .                                    # PHP 8.5 CLI + sharp-libvips
docker build --build-arg PHP_VARIANT=fpm -t pixelforge:fpm .    # PHP-FPM
docker build --build-arg PHP_VERSION=8.4 -t pixelforge:8.4 .
docker build --build-arg VIPS_FLAVOR=source -t pixelforge .     # libvips from source + Debian libs (adds JPEG XL)
docker run --rm pixelforge php /app/tests/run.php               # full functional suite
```

## Performance vs Node.js sharp

Both run the same libvips binary on a 24 MP JPEG, with `--cpus=4`, default settings on both sides, median of 7 rounds.
Reproduce with `ROUNDS=7 N=30 ./compare/run.sh`.

| Task | sharp ms | pixelforge ms | Speed | Peak RSS sharp / pf | RSS after work sharp / pf |
|---|---|---|---|---|---|
| metadata | 0.3 | 0.2 | **1.80×** | 69 / 38 MB | 69 / 38 MB |
| JPEG → 800px JPEG | 43.6 | 43.3 | 1.01× | 130 / 51 MB | 128 / 40 MB |
| → 800px WebP (buffer) | 73.8 | 74.2 | 0.99× | 104 / 54 MB | 104 / 42 MB |
| → 320×240 cover + sharpen | 38.2 | 36.9 | 1.04× | 104 / 45 MB | 103 / 39 MB |
| → 800px AVIF | 75.3 | 73.3 | 1.03× | 137 / 73 MB | 124 / 48 MB |
| PNG alpha → 200px | 8.3 | 8.6 | 0.97× | 94 / 48 MB | 93 / 41 MB |
| resize 1200 + watermark | 62.3 | 54.7 | **1.14×** | 148 / 55 MB | 148 / 40 MB |
| re-encode full 24MP | 149.1 | 136.7 | **1.09×** | 454 / 226 MB | 362 / 55 MB |
| mixed (5 tasks) | 272.5 | 280.2 | 0.97× | 414 / 224 MB | 249 / 54 MB |

Differences within ±3% are measurement noise. Output bytes match sharp or differ by less than 0.3%.

How it gets there:

- The same `fastShrinkOnLoad` logic as sharp: JPEG is decoded at 1/2, 1/4 or 1/8 scale, and WebP/SVG/PDF at the
  target scale.
- Alpha is premultiplied and kept in 8-bit, so `vips_resize` stays on its SIMD path.
- The thread count is picked per pipeline: one thread below 3 MP, otherwise every CPU the cgroup quota allows.
- `malloc_trim()` runs after each output, so long-lived FPM workers stay small: about 55 MB instead of 145 MB.
- The pipeline is lazy and reads sequentially. Inputs are not copied, and outputs are copied once.

Tuning through environment variables: `PIXELFORGE_CONCURRENCY` sets a fixed thread count, `PIXELFORGE_AUTO_THREADS_MP`
sets the auto threshold in megapixels, `PIXELFORGE_TRIM=0` disables `malloc_trim`, and `PIXELFORGE_VIPS_WARNINGS=1`
shows libvips warnings.

## API

All classes are in the `PixelForge` namespace. Errors throw `PixelForge\PixelForgeException`.

**Input:** `Image::fromFile($path, $o)`, `Image::fromBuffer($bytes, $o)`, `Image::fromRaw($pixels, [width, height, channels, depth, premultiplied])`,
`Image::create([width, height, channels, background, noise => [type => 'gaussian', mean, sigma]])`,
`Image::text([text (Pango markup), font, fontfile, width, height, align, justify, dpi, rgba, spacing, wrap])`,
`Image::join([...], [animated, across, shim, background, halign, valign])`.
Input options: `failOn`, `limitInputPixels`, `autoOrient`, `animated`, `pages`, `page`, `density`, `unlimited`, `ignoreIcc`, `raw`.

**Resize:** `resize(?w, ?h, [fit, position|gravity (incl. entropy/attention), background, kernel, withoutEnlargement, withoutReduction, fastShrinkOnLoad])`

**Geometry:** `extract`, `extend` (background|copy|repeat|mirror), `trim([threshold, background, lineArt])`, `rotate(?angle)`, `autoOrient`, `flip`, `flop`,
`affine([a,b,c,d], [background, interpolator, idx, idy, odx, ody])`

**Filters:** `sharpen`, `median`, `blur`, `flatten`, `unflatten`, `gamma`, `negate`, `normalise`, `clahe`, `threshold`, `linear`, `modulate`, `tint`,
`greyscale`, `convolve`, `recomb`, `dilate`, `erode`

**Channels:** `toColourspace`, `removeAlpha`, `ensureAlpha`, `extractChannel`, `joinChannel`, `bandbool`, `boolean`

**Composite:** `composite([[input (Image | path | bytes | ['create' => …] | ['text' => …]), gravity, left, top, blend, tile, premultiplied]])`

**Output:** `jpeg` (incl. `mozjpeg`), `png` (incl. palette), `webp`, `avif`, `heif`, `gif`, `tiff`, `jxl` (when libvips has it), `raw`, `toFormat`;
animation `loop`/`delay`; `tile([size, overlap, angle, layout dz|zoomify|google|iiif|iiif3, container fs|zip, depth, skipBlanks, centre, basename, id])`.

**Metadata:** stripped by default, like sharp. Keep it with `keepMetadata`, `keepExif`, `keepIccProfile` or `keepXmp`. Write it with `withIccProfile('srgb'|'p3'|'cmyk'|path)`,
`withExif([...])` or `withExifMerge([...])`.

**Sinks:** `toFile`, `toBuffer`, `toBufferWithInfo`, `metadata()` (header only), `stats()` (incl. entropy, sharpness, dominant colour),
`timeout(['seconds' => n])`, `clone()`

**Global:** `PixelForge::concurrency(?n)`, `PixelForge::cache()`, `PixelForge::versions()`, `PixelForge::format()`, `PixelForge::memory()`

## Differences from sharp

- No Node-style streams. Use `fromBuffer(stream_get_contents($fp))` and `fwrite($fp, $img->toBuffer())` instead.
- `pipelineColourspace` and gain maps are not implemented yet.
- `stats()` describes the processed image. sharp describes the input.
- With the sharp-libvips bundle, HEIF is AV1-only and JPEG XL, JPEG 2000 and PDF are unavailable, the same as in sharp.
- Only PHP 8.4/8.5 NTS is supported, because of the PHPX runtime.

## Repository layout

```
src/                 extension source: Image.php (PHP API, compiled by TypePHP), pixelforge.cc (libvips core), pixelforge.stub.php
generated/           C++ generated from src/*.php — do not edit, run scripts/generate.sh
deps/phpx/           vendored PHPX runtime (Apache-2.0) used by the generated code
config.m4            phpize build (PECL / PIE)
composer.json        PIE metadata · scripts/package.php → package.xml (PECL)
tests/*.phpt         make test · tests/run.php full suite (needs Docker fixtures)
compare/             benchmark against Node.js sharp
Dockerfile           vips → generate → build (phpize) → runtime
```

Edit `src/`, then run `scripts/generate.sh` (Docker) to refresh `generated/`.

## License

Apache-2.0. See [LICENSE](LICENSE) and [NOTICE](NOTICE) for the bundled third-party components.
