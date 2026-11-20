<?php
/**
 * Native (C++/libvips) functions. Implemented in pixelforge.cc — bodies must stay empty.
 * Prefer the fluent PixelForge\Image API; these are its low-level ABI.
 */

function pixelforge_from_file(string $path, string $failOn, int $limitPixels, bool $autoOrient, int $pages, int $page, float $density, bool $unlimited, bool $ignoreIcc): mixed {}
function pixelforge_from_buffer(string $data, string $failOn, int $limitPixels, bool $autoOrient, int $pages, int $page, float $density, bool $unlimited, bool $ignoreIcc): mixed {}
function pixelforge_from_raw(string $data, int $width, int $height, int $channels, string $depth, bool $premultiplied): mixed {}
function pixelforge_create(int $width, int $height, int $channels, float $r, float $g, float $b, float $a, string $noise, float $mean, float $sigma): mixed {}
function pixelforge_text(string $text, string $font, string $fontfile, int $width, int $height, string $align, bool $justify, int $dpi, bool $rgba, int $spacing, string $wrap): mixed {}
function pixelforge_join_new(bool $animated, int $across, int $shim, float $r, float $g, float $b, float $a, string $halign, string $valign): mixed {}
function pixelforge_join_add(mixed $h, mixed $input): bool {}
function pixelforge_clone(mixed $h): mixed {}

function pixelforge_resize(mixed $h, int $width, int $height, string $fit, string $position, float $r, float $g, float $b, float $a, bool $withoutEnlargement, bool $withoutReduction, string $kernel, bool $fastShrinkOnLoad): bool {}
function pixelforge_extract(mixed $h, int $left, int $top, int $width, int $height): bool {}
function pixelforge_extend(mixed $h, int $top, int $bottom, int $left, int $right, string $with, float $r, float $g, float $b, float $a): bool {}
function pixelforge_trim(mixed $h, float $threshold, bool $useBackground, float $r, float $g, float $b, bool $lineArt): bool {}
function pixelforge_rotate(mixed $h, float $angle, float $r, float $g, float $b, float $a): bool {}
function pixelforge_auto_orient(mixed $h): bool {}
function pixelforge_flip(mixed $h): bool {}
function pixelforge_flop(mixed $h): bool {}
function pixelforge_affine(mixed $h, float $a, float $b, float $c, float $d, float $r, float $g, float $bl, float $al, string $interpolator, float $idx, float $idy, float $odx, float $ody): bool {}

function pixelforge_sharpen(mixed $h, float $sigma, float $m1, float $m2, float $x1, float $y2, float $y3): bool {}
function pixelforge_median(mixed $h, int $size): bool {}
function pixelforge_blur(mixed $h, float $sigma, string $precision, float $minAmplitude): bool {}
function pixelforge_flatten(mixed $h, float $r, float $g, float $b): bool {}
function pixelforge_unflatten(mixed $h): bool {}
function pixelforge_gamma(mixed $h, float $gamma, float $gammaOut): bool {}
function pixelforge_negate(mixed $h, bool $alpha): bool {}
function pixelforge_normalise(mixed $h, float $lower, float $upper): bool {}
function pixelforge_clahe(mixed $h, int $width, int $height, int $maxSlope): bool {}
function pixelforge_threshold(mixed $h, int $threshold, bool $greyscale): bool {}
function pixelforge_linear(mixed $h, string $a, string $b): bool {}
function pixelforge_modulate(mixed $h, float $brightness, float $saturation, float $hue, float $lightness): bool {}
function pixelforge_tint(mixed $h, float $r, float $g, float $b): bool {}
function pixelforge_colourspace(mixed $h, string $space): bool {}
function pixelforge_remove_alpha(mixed $h): bool {}
function pixelforge_ensure_alpha(mixed $h, float $alpha): bool {}
function pixelforge_extract_channel(mixed $h, int $channel): bool {}
function pixelforge_join_channel(mixed $h, mixed $other): bool {}
function pixelforge_bandbool(mixed $h, string $op): bool {}
function pixelforge_boolean(mixed $h, mixed $other, string $op): bool {}
function pixelforge_dilate(mixed $h, int $width): bool {}
function pixelforge_erode(mixed $h, int $width): bool {}
function pixelforge_convolve(mixed $h, int $width, int $height, string $kernel, float $scale, float $offset): bool {}
function pixelforge_recomb(mixed $h, string $matrix): bool {}
function pixelforge_composite(mixed $h, mixed $overlay, string $gravity, int $left, int $top, string $blend, bool $tile, bool $premultiplied): bool {}

function pixelforge_output(mixed $h, string $format, int $quality, bool $lossless, int $effort, bool $progressive, string $chroma, bool $mozjpeg, int $compressionLevel, bool $palette, int $colours, float $dither, bool $adaptiveFiltering, int $nearLossless, bool $smartSubsample, int $alphaQuality, int $bitdepth, string $compression, string $predictor, bool $tile, int $tileWidth, int $tileHeight, bool $pyramid, int $loop, string $delay, bool $minSize, bool $mixed, float $interframeMaxError, float $interpaletteMaxError, bool $reuse, bool $optimizeCoding): bool {}
function pixelforge_tile(mixed $h, int $size, int $overlap, int $angle, string $layout, string $container, string $depth, bool $skipBlanks, bool $centre, string $basename, string $id, float $r, float $g, float $b, float $a): bool {}
function pixelforge_keep(mixed $h, int $flags): bool {}
function pixelforge_icc(mixed $h, string $profile): bool {}
function pixelforge_exif(mixed $h, string $flat, bool $merge): bool {}
function pixelforge_timeout(mixed $h, float $seconds): bool {}

function pixelforge_to_buffer(mixed $h, string $format): array {}
function pixelforge_to_file(mixed $h, string $path): array {}
function pixelforge_metadata(mixed $h): array {}
function pixelforge_stats(mixed $h): array {}

function pixelforge_concurrency(int $n): bool {}
function pixelforge_get_concurrency(): int {}
function pixelforge_cache(int $memoryMb, int $files, int $items): bool {}
function pixelforge_versions(): array {}
function pixelforge_formats(): array {}
function pixelforge_memory(): array {}
