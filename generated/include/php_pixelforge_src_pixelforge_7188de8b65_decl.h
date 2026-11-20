#pragma once

#include <phpx.h>
#include <typephp_helper.h>
#include <typephp_fiber_generator.h>
#include <php_pixelforge_runtime_decl.h>

extern php::Var php_pixelforge_from_file(php::Str path, php::Str failOn, php::Int limitPixels, php::Bool autoOrient, php::Int pages, php::Int page, php::Float density, php::Bool unlimited, php::Bool ignoreIcc);
extern php::Var php_pixelforge_from_buffer(php::Str data, php::Str failOn, php::Int limitPixels, php::Bool autoOrient, php::Int pages, php::Int page, php::Float density, php::Bool unlimited, php::Bool ignoreIcc);
extern php::Var php_pixelforge_from_raw(php::Str data, php::Int width, php::Int height, php::Int channels, php::Str depth, php::Bool premultiplied, php::Int limitPixels);
extern php::Bool php_pixelforge_is_image(php::Str data);
extern php::Var php_pixelforge_create(php::Int width, php::Int height, php::Int channels, php::Float r, php::Float g, php::Float b, php::Float a, php::Str noise, php::Float mean, php::Float sigma, php::Int limitPixels);
extern php::Var php_pixelforge_text(php::Str text, php::Str font, php::Str fontfile, php::Int width, php::Int height, php::Str align, php::Bool justify, php::Int dpi, php::Bool rgba, php::Int spacing, php::Str wrap, php::Int limitPixels);
extern php::Var php_pixelforge_join_new(php::Bool animated, php::Int across, php::Int shim, php::Float r, php::Float g, php::Float b, php::Float a, php::Str halign, php::Str valign, php::Int limitPixels);
extern php::Bool php_pixelforge_join_add(php::Var h, php::Var input);
extern php::Var php_pixelforge_clone(php::Var h);
extern php::Bool php_pixelforge_resize(php::Var h, php::Int width, php::Int height, php::Str fit, php::Str position, php::Float r, php::Float g, php::Float b, php::Float a, php::Bool withoutEnlargement, php::Bool withoutReduction, php::Str kernel, php::Bool fastShrinkOnLoad);
extern php::Bool php_pixelforge_extract(php::Var h, php::Int left, php::Int top, php::Int width, php::Int height);
extern php::Bool php_pixelforge_extend(php::Var h, php::Int top, php::Int bottom, php::Int left, php::Int right, php::Str with, php::Float r, php::Float g, php::Float b, php::Float a);
extern php::Bool php_pixelforge_trim(php::Var h, php::Float threshold, php::Bool useBackground, php::Float r, php::Float g, php::Float b, php::Bool lineArt);
extern php::Bool php_pixelforge_rotate(php::Var h, php::Float angle, php::Float r, php::Float g, php::Float b, php::Float a);
extern php::Bool php_pixelforge_auto_orient(php::Var h);
extern php::Bool php_pixelforge_flip(php::Var h);
extern php::Bool php_pixelforge_flop(php::Var h);
extern php::Bool php_pixelforge_affine(php::Var h, php::Float a, php::Float b, php::Float c, php::Float d, php::Float r, php::Float g, php::Float bl, php::Float al, php::Str interpolator, php::Float idx, php::Float idy, php::Float odx, php::Float ody);
extern php::Bool php_pixelforge_sharpen(php::Var h, php::Float sigma, php::Float m1, php::Float m2, php::Float x1, php::Float y2, php::Float y3);
extern php::Bool php_pixelforge_median(php::Var h, php::Int size);
extern php::Bool php_pixelforge_blur(php::Var h, php::Float sigma, php::Str precision, php::Float minAmplitude);
extern php::Bool php_pixelforge_flatten(php::Var h, php::Float r, php::Float g, php::Float b);
extern php::Bool php_pixelforge_unflatten(php::Var h);
extern php::Bool php_pixelforge_gamma(php::Var h, php::Float gamma, php::Float gammaOut);
extern php::Bool php_pixelforge_negate(php::Var h, php::Bool alpha);
extern php::Bool php_pixelforge_normalise(php::Var h, php::Float lower, php::Float upper);
extern php::Bool php_pixelforge_clahe(php::Var h, php::Int width, php::Int height, php::Int maxSlope);
extern php::Bool php_pixelforge_threshold(php::Var h, php::Int threshold, php::Bool greyscale);
extern php::Bool php_pixelforge_linear(php::Var h, php::Str a, php::Str b);
extern php::Bool php_pixelforge_modulate(php::Var h, php::Float brightness, php::Float saturation, php::Float hue, php::Float lightness);
extern php::Bool php_pixelforge_tint(php::Var h, php::Float r, php::Float g, php::Float b);
extern php::Bool php_pixelforge_colourspace(php::Var h, php::Str space);
extern php::Bool php_pixelforge_remove_alpha(php::Var h);
extern php::Bool php_pixelforge_ensure_alpha(php::Var h, php::Float alpha);
extern php::Bool php_pixelforge_extract_channel(php::Var h, php::Int channel);
extern php::Bool php_pixelforge_join_channel(php::Var h, php::Var other);
extern php::Bool php_pixelforge_bandbool(php::Var h, php::Str op);
extern php::Bool php_pixelforge_boolean(php::Var h, php::Var other, php::Str op);
extern php::Bool php_pixelforge_dilate(php::Var h, php::Int width);
extern php::Bool php_pixelforge_erode(php::Var h, php::Int width);
extern php::Bool php_pixelforge_convolve(php::Var h, php::Int width, php::Int height, php::Str kernel, php::Float scale, php::Float offset);
extern php::Bool php_pixelforge_recomb(php::Var h, php::Str matrix);
extern php::Bool php_pixelforge_composite(php::Var h, php::Var overlay, php::Str gravity, php::Int left, php::Int top, php::Str blend, php::Bool tile, php::Bool premultiplied);
extern php::Bool php_pixelforge_output(php::Var h, php::Str format, php::Int quality, php::Bool lossless, php::Int effort, php::Bool progressive, php::Str chroma, php::Bool mozjpeg, php::Int compressionLevel, php::Bool palette, php::Int colours, php::Float dither, php::Bool adaptiveFiltering, php::Int nearLossless, php::Bool smartSubsample, php::Int alphaQuality, php::Int bitdepth, php::Str compression, php::Str predictor, php::Bool tile, php::Int tileWidth, php::Int tileHeight, php::Bool pyramid, php::Int loop, php::Str delay, php::Bool minSize, php::Bool mixed, php::Float interframeMaxError, php::Float interpaletteMaxError, php::Bool reuse, php::Bool optimizeCoding);
extern php::Bool php_pixelforge_tile(php::Var h, php::Int size, php::Int overlap, php::Int angle, php::Str layout, php::Str container, php::Str depth, php::Bool skipBlanks, php::Bool centre, php::Str basename, php::Str id, php::Float r, php::Float g, php::Float b, php::Float a);
extern php::Bool php_pixelforge_keep(php::Var h, php::Int flags);
extern php::Bool php_pixelforge_icc(php::Var h, php::Str profile);
extern php::Bool php_pixelforge_exif(php::Var h, php::Str flat, php::Bool merge);
extern php::Bool php_pixelforge_timeout(php::Var h, php::Float seconds);
extern php::Array php_pixelforge_to_buffer(php::Var h, php::Str format);
extern php::Array php_pixelforge_to_file(php::Var h, php::Str path);
extern php::Array php_pixelforge_metadata(php::Var h);
extern php::Array php_pixelforge_stats(php::Var h);
extern php::Bool php_pixelforge_concurrency(php::Int n);
extern php::Int php_pixelforge_get_concurrency();
extern php::Bool php_pixelforge_cache(php::Int memoryMb, php::Int files, php::Int items);
extern php::Array php_pixelforge_versions();
extern php::Array php_pixelforge_formats();
extern php::Array php_pixelforge_memory();
#include <phpx.h>
#include <typephp_helper.h>


namespace typephp_project_pixelforge {
}  // namespace typephp_project_pixelforge
using namespace typephp_project_pixelforge;

