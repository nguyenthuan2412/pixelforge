--TEST--
pixelforge: create, resize, encode, decode round trip
--EXTENSIONS--
pixelforge
--FILE--
<?php
use PixelForge\Image;
$png = Image::create(['width' => 400, 'height' => 300, 'channels' => 4, 'background' => '#ff000080'])->png()->toBuffer();
$m = Image::fromBuffer($png)->metadata();
echo $m['format'], ' ', $m['width'], 'x', $m['height'], ' ', $m['channels'], "\n";
foreach (['jpeg', 'webp', 'png'] as $fmt) {
    $r = Image::fromBuffer($png)->resize(200, 200, ['fit' => 'cover'])->toFormat($fmt)->toBufferWithInfo();
    echo $fmt, ' ', $r['info']['width'], 'x', $r['info']['height'], ' ', Image::fromBuffer($r['data'])->metadata()['format'], "\n";
}
$r = Image::fromBuffer($png)->resize(100, 100, ['fit' => 'contain', 'background' => 'white'])->flatten(['background' => '#ffffff'])->raw()->toBufferWithInfo();
echo $r['info']['width'], 'x', $r['info']['height'], ' ', strlen($r['data']), "\n";
?>
--EXPECT--
png 400x300 4
jpeg 200x200 jpeg
webp 200x200 webp
png 200x200 png
100x100 30000
