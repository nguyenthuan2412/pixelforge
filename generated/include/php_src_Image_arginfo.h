/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 0c61e917299340fe9883b4af5983c033e08d0371 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_PixelForge_Image___construct, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, handle, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_fromFile, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, options, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_fromBuffer, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, options, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_fromRaw, 0, 2, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, raw, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_create, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, options, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_text arginfo_class_PixelForge_Image_create

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_join, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, inputs, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, options, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_input, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, in, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_PixelForge_Image_limit, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, options, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_pages arginfo_class_PixelForge_Image_limit

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_clone, 0, 0, PixelForge\\Image, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_PixelForge_Image_handle, 0, 0, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_resize, 0, 0, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, width, IS_LONG, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, height, IS_LONG, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, options, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_extract, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, region, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_extend, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_MASK(0, extend, MAY_BE_LONG|MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_trim, 0, 0, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, options, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_rotate, 0, 0, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, angle, IS_DOUBLE, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, options, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_autoOrient arginfo_class_PixelForge_Image_clone

#define arginfo_class_PixelForge_Image_flip arginfo_class_PixelForge_Image_clone

#define arginfo_class_PixelForge_Image_flop arginfo_class_PixelForge_Image_clone

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_affine, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, matrix, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, options, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_sharpen arginfo_class_PixelForge_Image_trim

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_median, 0, 0, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, size, IS_LONG, 0, "3")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_blur, 0, 0, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_MASK(0, sigma, MAY_BE_DOUBLE|MAY_BE_ARRAY, "0.0")
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_flatten arginfo_class_PixelForge_Image_trim

#define arginfo_class_PixelForge_Image_unflatten arginfo_class_PixelForge_Image_clone

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_gamma, 0, 0, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, gamma, IS_DOUBLE, 0, "2.2")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, gammaOut, IS_DOUBLE, 1, "null")
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_negate arginfo_class_PixelForge_Image_trim

#define arginfo_class_PixelForge_Image_normalise arginfo_class_PixelForge_Image_trim

#define arginfo_class_PixelForge_Image_normalize arginfo_class_PixelForge_Image_trim

#define arginfo_class_PixelForge_Image_clahe arginfo_class_PixelForge_Image_create

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_threshold, 0, 0, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, threshold, IS_LONG, 0, "128")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, options, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_linear, 0, 0, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_MASK(0, a, MAY_BE_DOUBLE|MAY_BE_ARRAY, "1.0")
	ZEND_ARG_TYPE_MASK(0, b, MAY_BE_DOUBLE|MAY_BE_ARRAY, "0.0")
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_modulate arginfo_class_PixelForge_Image_create

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_tint, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, color, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_greyscale, 0, 0, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, grey, _IS_BOOL, 0, "true")
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_grayscale arginfo_class_PixelForge_Image_greyscale

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_toColourspace, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, space, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_toColorspace arginfo_class_PixelForge_Image_toColourspace

#define arginfo_class_PixelForge_Image_removeAlpha arginfo_class_PixelForge_Image_clone

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_ensureAlpha, 0, 0, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, alpha, IS_DOUBLE, 0, "1.0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_extractChannel, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_MASK(0, channel, MAY_BE_LONG|MAY_BE_STRING, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_joinChannel, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, images, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_bandbool, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, op, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_boolean, 0, 2, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, operand, IS_MIXED, 0)
	ZEND_ARG_TYPE_INFO(0, op, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_dilate, 0, 0, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, width, IS_LONG, 0, "1")
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_erode arginfo_class_PixelForge_Image_dilate

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_convolve, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, kernel, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_recomb, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, matrix, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_composite, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, layers, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_jpeg, 0, 0, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, o, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_png arginfo_class_PixelForge_Image_jpeg

#define arginfo_class_PixelForge_Image_webp arginfo_class_PixelForge_Image_jpeg

#define arginfo_class_PixelForge_Image_avif arginfo_class_PixelForge_Image_jpeg

#define arginfo_class_PixelForge_Image_heif arginfo_class_PixelForge_Image_jpeg

#define arginfo_class_PixelForge_Image_gif arginfo_class_PixelForge_Image_jpeg

#define arginfo_class_PixelForge_Image_tiff arginfo_class_PixelForge_Image_jpeg

#define arginfo_class_PixelForge_Image_jxl arginfo_class_PixelForge_Image_jpeg

#define arginfo_class_PixelForge_Image_raw arginfo_class_PixelForge_Image_clone

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_toFormat, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, o, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_output, 0, 2, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, o, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_tile arginfo_class_PixelForge_Image_jpeg

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_timeout, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, o, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_keepMetadata arginfo_class_PixelForge_Image_clone

#define arginfo_class_PixelForge_Image_withMetadata arginfo_class_PixelForge_Image_clone

#define arginfo_class_PixelForge_Image_keepExif arginfo_class_PixelForge_Image_clone

#define arginfo_class_PixelForge_Image_keepIccProfile arginfo_class_PixelForge_Image_clone

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_withIccProfile, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, profile, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_withExif, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, exif, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_withExifMerge arginfo_class_PixelForge_Image_withExif

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_PixelForge_Image_flattenExif, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, exif, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_keepXmp arginfo_class_PixelForge_Image_clone

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PixelForge_Image_keep, 0, 1, PixelForge\\Image, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_PixelForge_Image_toFile, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_PixelForge_Image_toBuffer, 0, 0, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, format, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_PixelForge_Image_toBufferWithInfo, 0, 0, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, format, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_PixelForge_Image_metadata, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_Image_stats arginfo_class_PixelForge_Image_metadata

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_PixelForge_Image_csv, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, v, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_PixelForge_Gravity_normalise, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_PixelForge_Color_parse, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, c, IS_MIXED, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_PixelForge_PixelForge_concurrency, 0, 0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, n, IS_LONG, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_PixelForge_PixelForge_cache, 0, 0, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, memoryMb, IS_LONG, 0, "50")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, files, IS_LONG, 0, "20")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, items, IS_LONG, 0, "100")
ZEND_END_ARG_INFO()

#define arginfo_class_PixelForge_PixelForge_versions arginfo_class_PixelForge_Image_metadata

#define arginfo_class_PixelForge_PixelForge_format arginfo_class_PixelForge_Image_metadata

#define arginfo_class_PixelForge_PixelForge_memory arginfo_class_PixelForge_Image_metadata

ZEND_METHOD(PixelForge_Image, __construct);
ZEND_METHOD(PixelForge_Image, fromFile);
ZEND_METHOD(PixelForge_Image, fromBuffer);
ZEND_METHOD(PixelForge_Image, fromRaw);
ZEND_METHOD(PixelForge_Image, create);
ZEND_METHOD(PixelForge_Image, text);
ZEND_METHOD(PixelForge_Image, join);
ZEND_METHOD(PixelForge_Image, input);
ZEND_METHOD(PixelForge_Image, limit);
ZEND_METHOD(PixelForge_Image, pages);
ZEND_METHOD(PixelForge_Image, clone);
ZEND_METHOD(PixelForge_Image, handle);
ZEND_METHOD(PixelForge_Image, resize);
ZEND_METHOD(PixelForge_Image, extract);
ZEND_METHOD(PixelForge_Image, extend);
ZEND_METHOD(PixelForge_Image, trim);
ZEND_METHOD(PixelForge_Image, rotate);
ZEND_METHOD(PixelForge_Image, autoOrient);
ZEND_METHOD(PixelForge_Image, flip);
ZEND_METHOD(PixelForge_Image, flop);
ZEND_METHOD(PixelForge_Image, affine);
ZEND_METHOD(PixelForge_Image, sharpen);
ZEND_METHOD(PixelForge_Image, median);
ZEND_METHOD(PixelForge_Image, blur);
ZEND_METHOD(PixelForge_Image, flatten);
ZEND_METHOD(PixelForge_Image, unflatten);
ZEND_METHOD(PixelForge_Image, gamma);
ZEND_METHOD(PixelForge_Image, negate);
ZEND_METHOD(PixelForge_Image, normalise);
ZEND_METHOD(PixelForge_Image, normalize);
ZEND_METHOD(PixelForge_Image, clahe);
ZEND_METHOD(PixelForge_Image, threshold);
ZEND_METHOD(PixelForge_Image, linear);
ZEND_METHOD(PixelForge_Image, modulate);
ZEND_METHOD(PixelForge_Image, tint);
ZEND_METHOD(PixelForge_Image, greyscale);
ZEND_METHOD(PixelForge_Image, grayscale);
ZEND_METHOD(PixelForge_Image, toColourspace);
ZEND_METHOD(PixelForge_Image, toColorspace);
ZEND_METHOD(PixelForge_Image, removeAlpha);
ZEND_METHOD(PixelForge_Image, ensureAlpha);
ZEND_METHOD(PixelForge_Image, extractChannel);
ZEND_METHOD(PixelForge_Image, joinChannel);
ZEND_METHOD(PixelForge_Image, bandbool);
ZEND_METHOD(PixelForge_Image, boolean);
ZEND_METHOD(PixelForge_Image, dilate);
ZEND_METHOD(PixelForge_Image, erode);
ZEND_METHOD(PixelForge_Image, convolve);
ZEND_METHOD(PixelForge_Image, recomb);
ZEND_METHOD(PixelForge_Image, composite);
ZEND_METHOD(PixelForge_Image, jpeg);
ZEND_METHOD(PixelForge_Image, png);
ZEND_METHOD(PixelForge_Image, webp);
ZEND_METHOD(PixelForge_Image, avif);
ZEND_METHOD(PixelForge_Image, heif);
ZEND_METHOD(PixelForge_Image, gif);
ZEND_METHOD(PixelForge_Image, tiff);
ZEND_METHOD(PixelForge_Image, jxl);
ZEND_METHOD(PixelForge_Image, raw);
ZEND_METHOD(PixelForge_Image, toFormat);
ZEND_METHOD(PixelForge_Image, output);
ZEND_METHOD(PixelForge_Image, tile);
ZEND_METHOD(PixelForge_Image, timeout);
ZEND_METHOD(PixelForge_Image, keepMetadata);
ZEND_METHOD(PixelForge_Image, withMetadata);
ZEND_METHOD(PixelForge_Image, keepExif);
ZEND_METHOD(PixelForge_Image, keepIccProfile);
ZEND_METHOD(PixelForge_Image, withIccProfile);
ZEND_METHOD(PixelForge_Image, withExif);
ZEND_METHOD(PixelForge_Image, withExifMerge);
ZEND_METHOD(PixelForge_Image, flattenExif);
ZEND_METHOD(PixelForge_Image, keepXmp);
ZEND_METHOD(PixelForge_Image, keep);
ZEND_METHOD(PixelForge_Image, toFile);
ZEND_METHOD(PixelForge_Image, toBuffer);
ZEND_METHOD(PixelForge_Image, toBufferWithInfo);
ZEND_METHOD(PixelForge_Image, metadata);
ZEND_METHOD(PixelForge_Image, stats);
ZEND_METHOD(PixelForge_Image, csv);
ZEND_METHOD(PixelForge_Gravity, normalise);
ZEND_METHOD(PixelForge_Color, parse);
ZEND_METHOD(PixelForge_PixelForge, concurrency);
ZEND_METHOD(PixelForge_PixelForge, cache);
ZEND_METHOD(PixelForge_PixelForge, versions);
ZEND_METHOD(PixelForge_PixelForge, format);
ZEND_METHOD(PixelForge_PixelForge, memory);

static const zend_function_entry class_PixelForge_Image_methods[] = {
	ZEND_ME(PixelForge_Image, __construct, arginfo_class_PixelForge_Image___construct, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PRIVATE)
	ZEND_ME(PixelForge_Image, fromFile, arginfo_class_PixelForge_Image_fromFile, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_Image, fromBuffer, arginfo_class_PixelForge_Image_fromBuffer, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_Image, fromRaw, arginfo_class_PixelForge_Image_fromRaw, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_Image, create, arginfo_class_PixelForge_Image_create, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_Image, text, arginfo_class_PixelForge_Image_text, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_Image, join, arginfo_class_PixelForge_Image_join, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_Image, input, arginfo_class_PixelForge_Image_input, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_Image, limit, arginfo_class_PixelForge_Image_limit, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_Image, pages, arginfo_class_PixelForge_Image_pages, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_Image, clone, arginfo_class_PixelForge_Image_clone, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, handle, arginfo_class_PixelForge_Image_handle, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, resize, arginfo_class_PixelForge_Image_resize, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, extract, arginfo_class_PixelForge_Image_extract, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, extend, arginfo_class_PixelForge_Image_extend, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, trim, arginfo_class_PixelForge_Image_trim, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, rotate, arginfo_class_PixelForge_Image_rotate, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, autoOrient, arginfo_class_PixelForge_Image_autoOrient, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, flip, arginfo_class_PixelForge_Image_flip, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, flop, arginfo_class_PixelForge_Image_flop, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, affine, arginfo_class_PixelForge_Image_affine, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, sharpen, arginfo_class_PixelForge_Image_sharpen, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, median, arginfo_class_PixelForge_Image_median, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, blur, arginfo_class_PixelForge_Image_blur, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, flatten, arginfo_class_PixelForge_Image_flatten, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, unflatten, arginfo_class_PixelForge_Image_unflatten, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, gamma, arginfo_class_PixelForge_Image_gamma, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, negate, arginfo_class_PixelForge_Image_negate, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, normalise, arginfo_class_PixelForge_Image_normalise, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, normalize, arginfo_class_PixelForge_Image_normalize, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, clahe, arginfo_class_PixelForge_Image_clahe, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, threshold, arginfo_class_PixelForge_Image_threshold, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, linear, arginfo_class_PixelForge_Image_linear, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, modulate, arginfo_class_PixelForge_Image_modulate, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, tint, arginfo_class_PixelForge_Image_tint, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, greyscale, arginfo_class_PixelForge_Image_greyscale, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, grayscale, arginfo_class_PixelForge_Image_grayscale, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, toColourspace, arginfo_class_PixelForge_Image_toColourspace, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, toColorspace, arginfo_class_PixelForge_Image_toColorspace, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, removeAlpha, arginfo_class_PixelForge_Image_removeAlpha, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, ensureAlpha, arginfo_class_PixelForge_Image_ensureAlpha, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, extractChannel, arginfo_class_PixelForge_Image_extractChannel, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, joinChannel, arginfo_class_PixelForge_Image_joinChannel, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, bandbool, arginfo_class_PixelForge_Image_bandbool, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, boolean, arginfo_class_PixelForge_Image_boolean, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, dilate, arginfo_class_PixelForge_Image_dilate, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, erode, arginfo_class_PixelForge_Image_erode, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, convolve, arginfo_class_PixelForge_Image_convolve, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, recomb, arginfo_class_PixelForge_Image_recomb, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, composite, arginfo_class_PixelForge_Image_composite, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, jpeg, arginfo_class_PixelForge_Image_jpeg, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, png, arginfo_class_PixelForge_Image_png, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, webp, arginfo_class_PixelForge_Image_webp, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, avif, arginfo_class_PixelForge_Image_avif, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, heif, arginfo_class_PixelForge_Image_heif, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, gif, arginfo_class_PixelForge_Image_gif, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, tiff, arginfo_class_PixelForge_Image_tiff, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, jxl, arginfo_class_PixelForge_Image_jxl, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, raw, arginfo_class_PixelForge_Image_raw, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, toFormat, arginfo_class_PixelForge_Image_toFormat, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, output, arginfo_class_PixelForge_Image_output, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PRIVATE)
	ZEND_ME(PixelForge_Image, tile, arginfo_class_PixelForge_Image_tile, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, timeout, arginfo_class_PixelForge_Image_timeout, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, keepMetadata, arginfo_class_PixelForge_Image_keepMetadata, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, withMetadata, arginfo_class_PixelForge_Image_withMetadata, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, keepExif, arginfo_class_PixelForge_Image_keepExif, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, keepIccProfile, arginfo_class_PixelForge_Image_keepIccProfile, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, withIccProfile, arginfo_class_PixelForge_Image_withIccProfile, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, withExif, arginfo_class_PixelForge_Image_withExif, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, withExifMerge, arginfo_class_PixelForge_Image_withExifMerge, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, flattenExif, arginfo_class_PixelForge_Image_flattenExif, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_Image, keepXmp, arginfo_class_PixelForge_Image_keepXmp, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, keep, arginfo_class_PixelForge_Image_keep, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PRIVATE)
	ZEND_ME(PixelForge_Image, toFile, arginfo_class_PixelForge_Image_toFile, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, toBuffer, arginfo_class_PixelForge_Image_toBuffer, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, toBufferWithInfo, arginfo_class_PixelForge_Image_toBufferWithInfo, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, metadata, arginfo_class_PixelForge_Image_metadata, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, stats, arginfo_class_PixelForge_Image_stats, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC)
	ZEND_ME(PixelForge_Image, csv, arginfo_class_PixelForge_Image_csv, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PRIVATE|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_PixelForge_Gravity_methods[] = {
	ZEND_ME(PixelForge_Gravity, normalise, arginfo_class_PixelForge_Gravity_normalise, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_PixelForge_Color_methods[] = {
	ZEND_ME(PixelForge_Color, parse, arginfo_class_PixelForge_Color_parse, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_PixelForge_PixelForge_methods[] = {
	ZEND_ME(PixelForge_PixelForge, concurrency, arginfo_class_PixelForge_PixelForge_concurrency, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_PixelForge, cache, arginfo_class_PixelForge_PixelForge_cache, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_PixelForge, versions, arginfo_class_PixelForge_PixelForge_versions, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_PixelForge, format, arginfo_class_PixelForge_PixelForge_format, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(PixelForge_PixelForge, memory, arginfo_class_PixelForge_PixelForge_memory, ZEND_ACC_STRICT_TYPES|ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static zend_class_entry *php_register_class_PixelForge_PixelForgeException(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "PixelForge", "PixelForgeException", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_RuntimeException, 0);
	typephp_finalize_property_hook_inheritance(class_entry);

	return class_entry;
}

static zend_class_entry *php_register_class_PixelForge_Image(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "PixelForge", "Image", class_PixelForge_Image_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, 0);

	zval const_KEEP_NONE_value;
	ZVAL_LONG(&const_KEEP_NONE_value, 0);
	zend_string *const_KEEP_NONE_name = zend_string_init_interned("KEEP_NONE", sizeof("KEEP_NONE") - 1, true);
	zend_hash_del(&class_entry->constants_table, const_KEEP_NONE_name);
	zend_declare_class_constant_ex(class_entry, const_KEEP_NONE_name, &const_KEEP_NONE_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release_ex(const_KEEP_NONE_name, true);

	zval const_KEEP_EXIF_value;
	ZVAL_LONG(&const_KEEP_EXIF_value, 1);
	zend_string *const_KEEP_EXIF_name = zend_string_init_interned("KEEP_EXIF", sizeof("KEEP_EXIF") - 1, true);
	zend_hash_del(&class_entry->constants_table, const_KEEP_EXIF_name);
	zend_declare_class_constant_ex(class_entry, const_KEEP_EXIF_name, &const_KEEP_EXIF_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release_ex(const_KEEP_EXIF_name, true);

	zval const_KEEP_XMP_value;
	ZVAL_LONG(&const_KEEP_XMP_value, 2);
	zend_string *const_KEEP_XMP_name = zend_string_init_interned("KEEP_XMP", sizeof("KEEP_XMP") - 1, true);
	zend_hash_del(&class_entry->constants_table, const_KEEP_XMP_name);
	zend_declare_class_constant_ex(class_entry, const_KEEP_XMP_name, &const_KEEP_XMP_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release_ex(const_KEEP_XMP_name, true);

	zval const_KEEP_IPTC_value;
	ZVAL_LONG(&const_KEEP_IPTC_value, 4);
	zend_string *const_KEEP_IPTC_name = zend_string_init_interned("KEEP_IPTC", sizeof("KEEP_IPTC") - 1, true);
	zend_hash_del(&class_entry->constants_table, const_KEEP_IPTC_name);
	zend_declare_class_constant_ex(class_entry, const_KEEP_IPTC_name, &const_KEEP_IPTC_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release_ex(const_KEEP_IPTC_name, true);

	zval const_KEEP_ICC_value;
	ZVAL_LONG(&const_KEEP_ICC_value, 8);
	zend_string *const_KEEP_ICC_name = zend_string_init_interned("KEEP_ICC", sizeof("KEEP_ICC") - 1, true);
	zend_hash_del(&class_entry->constants_table, const_KEEP_ICC_name);
	zend_declare_class_constant_ex(class_entry, const_KEEP_ICC_name, &const_KEEP_ICC_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release_ex(const_KEEP_ICC_name, true);

	zval const_KEEP_OTHER_value;
	ZVAL_LONG(&const_KEEP_OTHER_value, 16);
	zend_string *const_KEEP_OTHER_name = zend_string_init_interned("KEEP_OTHER", sizeof("KEEP_OTHER") - 1, true);
	zend_hash_del(&class_entry->constants_table, const_KEEP_OTHER_name);
	zend_declare_class_constant_ex(class_entry, const_KEEP_OTHER_name, &const_KEEP_OTHER_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release_ex(const_KEEP_OTHER_name, true);

	zval const_KEEP_ALL_value;
	ZVAL_LONG(&const_KEEP_ALL_value, 31);
	zend_string *const_KEEP_ALL_name = zend_string_init_interned("KEEP_ALL", sizeof("KEEP_ALL") - 1, true);
	zend_hash_del(&class_entry->constants_table, const_KEEP_ALL_name);
	zend_declare_class_constant_ex(class_entry, const_KEEP_ALL_name, &const_KEEP_ALL_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release_ex(const_KEEP_ALL_name, true);

	zval property_h_default_value;
	ZVAL_NULL(&property_h_default_value);
	zend_string *property_h_name = zend_string_init("h", sizeof("h") - 1, true);
	typephp_prepare_property_redeclaration(class_entry, property_h_name);
	zend_declare_typed_property(class_entry, property_h_name, &property_h_default_value, ZEND_ACC_PRIVATE, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ANY));
	zend_string_release_ex(property_h_name, true);

	zval property_keepFlags_default_value;
	ZVAL_LONG(&property_keepFlags_default_value, 0);
	zend_string *property_keepFlags_name = zend_string_init("keepFlags", sizeof("keepFlags") - 1, true);
	typephp_prepare_property_redeclaration(class_entry, property_keepFlags_name);
	zend_declare_typed_property(class_entry, property_keepFlags_name, &property_keepFlags_default_value, ZEND_ACC_PRIVATE, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release_ex(property_keepFlags_name, true);

	return class_entry;
}

static zend_class_entry *php_register_class_PixelForge_Gravity(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "PixelForge", "Gravity", class_PixelForge_Gravity_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	return class_entry;
}

static zend_class_entry *php_register_class_PixelForge_Color(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "PixelForge", "Color", class_PixelForge_Color_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	return class_entry;
}

static zend_class_entry *php_register_class_PixelForge_PixelForge(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "PixelForge", "PixelForge", class_PixelForge_PixelForge_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	return class_entry;
}
