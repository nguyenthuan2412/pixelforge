# Changelog

## 0.1.1 — 2026-11-20

Fixes found by a stricter test suite (warnings are now failures, plus a sweep of every public method and invalid input):

- **Crash fix:** an invalid `toColourspace()`, `bandbool()`, `linear()`, `convolve()` or `recomb()` argument aborted the
  PHP process instead of throwing `PixelForgeException`.
- Colours: CSS names (`red`, `navy`, `orange`, …) are supported. Invalid colours throw `InvalidArgumentException`
  instead of silently producing a wrong colour.
- TIFF: `predictor` is only applied to deflate/lzw/zstd, the compressions libtiff accepts it for.
- Builds against libvips 8.15/8.16 (the `mks2013`/`mks2021` kernels need 8.17+ and fall back to lanczos3).
- README rewritten around copy-paste install steps and recipes.

## 0.1.0 — 2026-11-20

First release.

- libvips 8.15+ engine with sharp-style shrink-on-load, per-pipeline thread selection and `malloc_trim` after each output.
- Inputs: file, buffer, raw pixels, blank/noise canvas, text (Pango), join (grid or animation), animated GIF/WebP pages.
- Operations: resize (5 fits, gravity, entropy/attention, 8 kernels), extract, extend, trim, rotate, flip/flop, affine,
  sharpen, blur, median, gamma, negate, normalise, CLAHE, threshold, linear, modulate, tint, greyscale, convolve,
  recomb, dilate/erode, boolean/bandbool, join/extract channels, composite (blend modes, tiling).
- Outputs: JPEG (mozjpeg options), PNG (palette), WebP, AVIF/HEIF, GIF, TIFF, JPEG XL (when available), raw,
  Deep Zoom/Zoomify/Google/IIIF tiles; ICC profile / EXIF writing; timeout.
- Installable with `phpize`, PECL (`package.xml`) and PIE (`composer.json`, type `php-ext`).
