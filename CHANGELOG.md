# Changelog

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
