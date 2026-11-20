--TEST--
pixelforge: extension loads and reports libvips
--EXTENSIONS--
pixelforge
--FILE--
<?php
var_dump(extension_loaded('pixelforge'));
var_dump(class_exists(PixelForge\Image::class));
var_dump((bool) preg_match('/^8\.\d+\.\d+/', PixelForge\PixelForge::versions()['vips']));
$f = PixelForge\PixelForge::format();
var_dump($f['jpeg']['output'], $f['png']['output'], $f['webp']['output']);
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
