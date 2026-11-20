--TEST--
pixelforge: errors are thrown as PixelForgeException
--EXTENSIONS--
pixelforge
--FILE--
<?php
use PixelForge\Image;
use PixelForge\PixelForgeException;
foreach ([
    fn () => Image::fromFile('/definitely/missing.jpg')->toBuffer(),
    fn () => Image::fromBuffer('not an image')->metadata(),
    fn () => Image::create(['width' => 10, 'height' => 10])->extract(['left' => 0, 'top' => 0, 'width' => 50, 'height' => 5])->png()->toBuffer(),
] as $i => $fn) {
    try { $fn(); echo "$i: no exception\n"; }
    catch (PixelForgeException $e) { echo "$i: ", get_class($e), "\n"; }
}
?>
--EXPECT--
0: PixelForge\PixelForgeException
1: PixelForge\PixelForgeException
2: PixelForge\PixelForgeException
