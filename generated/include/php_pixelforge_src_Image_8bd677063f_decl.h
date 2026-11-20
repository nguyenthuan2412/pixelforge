#pragma once

#include <phpx.h>
#include <typephp_helper.h>
#include <typephp_fiber_generator.h>
#include <php_pixelforge_runtime_decl.h>
#include <php_pixelforge_src_pixelforge_7188de8b65_decl.h>

extern php::Array php_pixelforge__image__fromfile_arg_1_default_value();
extern php::Array php_pixelforge__image__frombuffer_arg_1_default_value();
extern php::Array php_pixelforge__image__join_arg_1_default_value();
extern php::Var php_pixelforge__image__resize_arg_0_default_value();
extern php::Var php_pixelforge__image__resize_arg_1_default_value();
extern php::Array php_pixelforge__image__resize_arg_2_default_value();
extern php::Array php_pixelforge__image__trim_arg_0_default_value();
extern php::Var php_pixelforge__image__rotate_arg_0_default_value();
extern php::Array php_pixelforge__image__rotate_arg_1_default_value();
extern php::Array php_pixelforge__image__affine_arg_1_default_value();
extern php::Array php_pixelforge__image__sharpen_arg_0_default_value();
extern php::Int php_pixelforge__image__median_arg_0_default_value();
extern php::Var php_pixelforge__image__blur_arg_0_default_value();
extern php::Array php_pixelforge__image__flatten_arg_0_default_value();
extern php::Float php_pixelforge__image__gamma_arg_0_default_value();
extern php::Var php_pixelforge__image__gamma_arg_1_default_value();
extern php::Array php_pixelforge__image__negate_arg_0_default_value();
extern php::Array php_pixelforge__image__normalise_arg_0_default_value();
extern php::Array php_pixelforge__image__normalize_arg_0_default_value();
extern php::Int php_pixelforge__image__threshold_arg_0_default_value();
extern php::Array php_pixelforge__image__threshold_arg_1_default_value();
extern php::Var php_pixelforge__image__linear_arg_0_default_value();
extern php::Var php_pixelforge__image__linear_arg_1_default_value();
extern php::Bool php_pixelforge__image__greyscale_arg_0_default_value();
extern php::Bool php_pixelforge__image__grayscale_arg_0_default_value();
extern php::Float php_pixelforge__image__ensurealpha_arg_0_default_value();
extern php::Int php_pixelforge__image__dilate_arg_0_default_value();
extern php::Int php_pixelforge__image__erode_arg_0_default_value();
extern php::Array php_pixelforge__image__jpeg_arg_0_default_value();
extern php::Array php_pixelforge__image__png_arg_0_default_value();
extern php::Array php_pixelforge__image__webp_arg_0_default_value();
extern php::Array php_pixelforge__image__avif_arg_0_default_value();
extern php::Array php_pixelforge__image__heif_arg_0_default_value();
extern php::Array php_pixelforge__image__gif_arg_0_default_value();
extern php::Array php_pixelforge__image__tiff_arg_0_default_value();
extern php::Array php_pixelforge__image__jxl_arg_0_default_value();
extern php::Array php_pixelforge__image__toformat_arg_1_default_value();
extern php::Array php_pixelforge__image__tile_arg_0_default_value();
extern php::Var php_pixelforge__image__tobuffer_arg_0_default_value();
extern php::Var php_pixelforge__image__tobufferwithinfo_arg_0_default_value();
extern php::Var php_pixelforge__pixelforge__concurrency_arg_0_default_value();
extern php::Int php_pixelforge__pixelforge__cache_arg_0_default_value();
extern php::Int php_pixelforge__pixelforge__cache_arg_1_default_value();
extern php::Int php_pixelforge__pixelforge__cache_arg_2_default_value();

extern void php_pixelforge__image____construct(php::Object &this_, php::Var handle);
extern php::Object php_pixelforge__image__fromfile(php::Object &this_, php::Str path, php::Array options = php_pixelforge__image__fromfile_arg_1_default_value());
extern php::Object php_pixelforge__image__frombuffer(php::Object &this_, php::Str data, php::Array options = php_pixelforge__image__frombuffer_arg_1_default_value());
extern php::Object php_pixelforge__image__fromraw(php::Object &this_, php::Str data, php::Array raw);
extern php::Object php_pixelforge__image__create(php::Object &this_, php::Array options);
extern php::Object php_pixelforge__image__text(php::Object &this_, php::Array options);
extern php::Object php_pixelforge__image__join(php::Object &this_, php::Array inputs, php::Array options = php_pixelforge__image__join_arg_1_default_value());
extern php::Object php_pixelforge__image__input(php::Object &this_, php::Var in);
extern php::Int php_pixelforge__image__limit(php::Object &this_, php::Array options);
extern php::Int php_pixelforge__image__pages(php::Object &this_, php::Array options);
extern php::Object php_pixelforge__image__clone(php::Object &this_);
extern php::Var php_pixelforge__image__handle(php::Object &this_);
extern php::Object php_pixelforge__image__resize(php::Object &this_, php::Var width = php_pixelforge__image__resize_arg_0_default_value(), php::Var height = php_pixelforge__image__resize_arg_1_default_value(), php::Array options = php_pixelforge__image__resize_arg_2_default_value());
extern php::Object php_pixelforge__image__extract(php::Object &this_, php::Array region);
extern php::Object php_pixelforge__image__extend(php::Object &this_, php::Var extend);
extern php::Object php_pixelforge__image__trim(php::Object &this_, php::Array options = php_pixelforge__image__trim_arg_0_default_value());
extern php::Object php_pixelforge__image__rotate(php::Object &this_, php::Var angle = php_pixelforge__image__rotate_arg_0_default_value(), php::Array options = php_pixelforge__image__rotate_arg_1_default_value());
extern php::Object php_pixelforge__image__autoorient(php::Object &this_);
extern php::Object php_pixelforge__image__flip(php::Object &this_);
extern php::Object php_pixelforge__image__flop(php::Object &this_);
extern php::Object php_pixelforge__image__affine(php::Object &this_, php::Array matrix, php::Array options = php_pixelforge__image__affine_arg_1_default_value());
extern php::Object php_pixelforge__image__sharpen(php::Object &this_, php::Array options = php_pixelforge__image__sharpen_arg_0_default_value());
extern php::Object php_pixelforge__image__median(php::Object &this_, php::Int size = php_pixelforge__image__median_arg_0_default_value());
extern php::Object php_pixelforge__image__blur(php::Object &this_, php::Var sigma = php_pixelforge__image__blur_arg_0_default_value());
extern php::Object php_pixelforge__image__flatten(php::Object &this_, php::Array options = php_pixelforge__image__flatten_arg_0_default_value());
extern php::Object php_pixelforge__image__unflatten(php::Object &this_);
extern php::Object php_pixelforge__image__gamma(php::Object &this_, php::Float gamma = php_pixelforge__image__gamma_arg_0_default_value(), php::Var gammaOut = php_pixelforge__image__gamma_arg_1_default_value());
extern php::Object php_pixelforge__image__negate(php::Object &this_, php::Array options = php_pixelforge__image__negate_arg_0_default_value());
extern php::Object php_pixelforge__image__normalise(php::Object &this_, php::Array options = php_pixelforge__image__normalise_arg_0_default_value());
extern php::Object php_pixelforge__image__normalize(php::Object &this_, php::Array options = php_pixelforge__image__normalize_arg_0_default_value());
extern php::Object php_pixelforge__image__clahe(php::Object &this_, php::Array options);
extern php::Object php_pixelforge__image__threshold(php::Object &this_, php::Int threshold = php_pixelforge__image__threshold_arg_0_default_value(), php::Array options = php_pixelforge__image__threshold_arg_1_default_value());
extern php::Object php_pixelforge__image__linear(php::Object &this_, php::Var a = php_pixelforge__image__linear_arg_0_default_value(), php::Var b = php_pixelforge__image__linear_arg_1_default_value());
extern php::Object php_pixelforge__image__modulate(php::Object &this_, php::Array options);
extern php::Object php_pixelforge__image__tint(php::Object &this_, php::Var color);
extern php::Object php_pixelforge__image__greyscale(php::Object &this_, php::Bool grey = php_pixelforge__image__greyscale_arg_0_default_value());
extern php::Object php_pixelforge__image__grayscale(php::Object &this_, php::Bool grey = php_pixelforge__image__grayscale_arg_0_default_value());
extern php::Object php_pixelforge__image__tocolourspace(php::Object &this_, php::Str space);
extern php::Object php_pixelforge__image__tocolorspace(php::Object &this_, php::Str space);
extern php::Object php_pixelforge__image__removealpha(php::Object &this_);
extern php::Object php_pixelforge__image__ensurealpha(php::Object &this_, php::Float alpha = php_pixelforge__image__ensurealpha_arg_0_default_value());
extern php::Object php_pixelforge__image__extractchannel(php::Object &this_, php::Var channel);
extern php::Object php_pixelforge__image__joinchannel(php::Object &this_, php::Var images);
extern php::Object php_pixelforge__image__bandbool(php::Object &this_, php::Str op);
extern php::Object php_pixelforge__image__boolean(php::Object &this_, php::Var operand, php::Str op);
extern php::Object php_pixelforge__image__dilate(php::Object &this_, php::Int width = php_pixelforge__image__dilate_arg_0_default_value());
extern php::Object php_pixelforge__image__erode(php::Object &this_, php::Int width = php_pixelforge__image__erode_arg_0_default_value());
extern php::Object php_pixelforge__image__convolve(php::Object &this_, php::Array kernel);
extern php::Object php_pixelforge__image__recomb(php::Object &this_, php::Array matrix);
extern php::Object php_pixelforge__image__composite(php::Object &this_, php::Array layers);
extern php::Object php_pixelforge__image__jpeg(php::Object &this_, php::Array o = php_pixelforge__image__jpeg_arg_0_default_value());
extern php::Object php_pixelforge__image__png(php::Object &this_, php::Array o = php_pixelforge__image__png_arg_0_default_value());
extern php::Object php_pixelforge__image__webp(php::Object &this_, php::Array o = php_pixelforge__image__webp_arg_0_default_value());
extern php::Object php_pixelforge__image__avif(php::Object &this_, php::Array o = php_pixelforge__image__avif_arg_0_default_value());
extern php::Object php_pixelforge__image__heif(php::Object &this_, php::Array o = php_pixelforge__image__heif_arg_0_default_value());
extern php::Object php_pixelforge__image__gif(php::Object &this_, php::Array o = php_pixelforge__image__gif_arg_0_default_value());
extern php::Object php_pixelforge__image__tiff(php::Object &this_, php::Array o = php_pixelforge__image__tiff_arg_0_default_value());
extern php::Object php_pixelforge__image__jxl(php::Object &this_, php::Array o = php_pixelforge__image__jxl_arg_0_default_value());
extern php::Object php_pixelforge__image__raw(php::Object &this_);
extern php::Object php_pixelforge__image__toformat(php::Object &this_, php::Str format, php::Array o = php_pixelforge__image__toformat_arg_1_default_value());
extern php::Object php_pixelforge__image__output(php::Object &this_, php::Str format, php::Array o);
extern php::Object php_pixelforge__image__tile(php::Object &this_, php::Array o = php_pixelforge__image__tile_arg_0_default_value());
extern php::Object php_pixelforge__image__timeout(php::Object &this_, php::Array o);
extern php::Object php_pixelforge__image__keepmetadata(php::Object &this_);
extern php::Object php_pixelforge__image__withmetadata(php::Object &this_);
extern php::Object php_pixelforge__image__keepexif(php::Object &this_);
extern php::Object php_pixelforge__image__keepiccprofile(php::Object &this_);
extern php::Object php_pixelforge__image__withiccprofile(php::Object &this_, php::Str profile);
extern php::Object php_pixelforge__image__withexif(php::Object &this_, php::Array exif);
extern php::Object php_pixelforge__image__withexifmerge(php::Object &this_, php::Array exif);
extern php::Str php_pixelforge__image__flattenexif(php::Object &this_, php::Array exif);
extern php::Object php_pixelforge__image__keepxmp(php::Object &this_);
extern php::Object php_pixelforge__image__keep(php::Object &this_, php::Int flags);
extern php::Array php_pixelforge__image__tofile(php::Object &this_, php::Str path);
extern php::Str php_pixelforge__image__tobuffer(php::Object &this_, php::Var format = php_pixelforge__image__tobuffer_arg_0_default_value());
extern php::Array php_pixelforge__image__tobufferwithinfo(php::Object &this_, php::Var format = php_pixelforge__image__tobufferwithinfo_arg_0_default_value());
extern php::Array php_pixelforge__image__metadata(php::Object &this_);
extern php::Array php_pixelforge__image__stats(php::Object &this_);
extern php::Str php_pixelforge__image__csv(php::Object &this_, php::Var v);
extern php::Str php_pixelforge__gravity__normalise(php::Object &this_, php::Str g);
extern php::Array php_pixelforge__color__parse(php::Object &this_, php::Var c);
extern php::Int php_pixelforge__pixelforge__concurrency(php::Object &this_, php::Var n = php_pixelforge__pixelforge__concurrency_arg_0_default_value());
extern void php_pixelforge__pixelforge__cache(php::Object &this_, php::Int memoryMb = php_pixelforge__pixelforge__cache_arg_0_default_value(), php::Int files = php_pixelforge__pixelforge__cache_arg_1_default_value(), php::Int items = php_pixelforge__pixelforge__cache_arg_2_default_value());
extern php::Array php_pixelforge__pixelforge__versions(php::Object &this_);
extern php::Array php_pixelforge__pixelforge__format(php::Object &this_);
extern php::Array php_pixelforge__pixelforge__memory(php::Object &this_);
#include <phpx.h>
#include <typephp_helper.h>


namespace typephp_project_pixelforge {
extern php::Var class_const__pixelforge__gravity__ALIASES;

}  // namespace typephp_project_pixelforge
using namespace typephp_project_pixelforge;

