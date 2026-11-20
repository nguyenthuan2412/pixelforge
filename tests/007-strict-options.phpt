--TEST--
pixelforge: unknown option values are rejected, never silently replaced by a default
--EXTENSIONS--
pixelforge
--FILE--
<?php
use PixelForge\Image;
$img = fn () => Image::create(['width' => 40, 'height' => 30, 'channels' => 3]);
$cases = [
    'position'          => fn () => $img()->resize(10, 10, ['position' => 'topp']),
    'gravity'           => fn () => $img()->composite([['input' => $img(), 'gravity' => 'middle']]),
    'kernel'            => fn () => $img()->resize(10, 10, ['kernel' => 'lanczos9']),
    'fit'               => fn () => $img()->resize(10, 10, ['fit' => 'stretch']),
    'failOn'            => fn () => Image::fromBuffer('xxxxxxxx', ['failOn' => 'sometimes']),
    'extendWith'        => fn () => $img()->extend(['left' => 2, 'extendWith' => 'wrap']),
    'blur precision'    => fn () => $img()->blur(['sigma' => 2, 'precision' => 'double']),
    'chromaSubsampling' => fn () => $img()->jpeg(['chromaSubsampling' => '4:1:1']),
    'tiff compression'  => fn () => $img()->tiff(['compression' => 'zip']),
    'tiff predictor'    => fn () => $img()->tiff(['predictor' => 'vertical']),
    'heif compression'  => fn () => $img()->heif(['compression' => 'vp9']),
    'raw depth'         => fn () => Image::fromRaw(str_repeat("\0", 300), ['width' => 10, 'height' => 10, 'channels' => 3, 'depth' => 'int8']),
    'noise type'        => fn () => Image::create(['width' => 4, 'height' => 4, 'noise' => ['type' => 'perlin']]),
    'input array'       => fn () => $img()->composite([['input' => ['url' => 'x']]]),
    'input type'        => fn () => $img()->composite([['input' => 42]]),
];
foreach ($cases as $name => $fn) {
    try { $fn(); echo "$name: ACCEPTED\n"; }
    catch (InvalidArgumentException | PixelForge\PixelForgeException $e) { echo "$name: rejected\n"; }
}
?>
--EXPECT--
position: rejected
gravity: rejected
kernel: rejected
fit: rejected
failOn: rejected
extendWith: rejected
blur precision: rejected
chromaSubsampling: rejected
tiff compression: rejected
tiff predictor: rejected
heif compression: rejected
raw depth: rejected
noise type: rejected
input array: rejected
input type: rejected
