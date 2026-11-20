--TEST--
pixelforge: truncated and corrupted images never crash, warn or hang; they throw PixelForgeException
--EXTENSIONS--
pixelforge
--FILE--
<?php
use PixelForge\Image;
use PixelForge\PixelForgeException;
set_error_handler(function ($no, $msg) { throw new ErrorException($msg, 0, $no); });

$src = Image::create(['width' => 96, 'height' => 64, 'channels' => 4, 'noise' => ['type' => 'gaussian']]);
$available = PixelForge\PixelForge::format();
$formats = array_values(array_filter(['jpeg', 'png', 'webp', 'gif', 'tiff', 'avif'], fn ($f) => $available[$f]['output']));
mt_srand(42);
$ok = $thrown = 0;
foreach ($formats as $fmt) {
    $good = $src->clone()->toFormat($fmt)->toBuffer();
    $variants = [];
    foreach ([0.05, 0.25, 0.5, 0.75, 0.95] as $f) {                         // truncations
        $variants[] = substr($good, 0, max(8, (int) (strlen($good) * $f)));
    }
    for ($i = 0; $i < 12; $i++) {                                           // random byte flips
        $b = $good;
        for ($k = 0; $k < 1 + $i; $k++) {
            $pos = mt_rand(0, strlen($b) - 1);
            $b[$pos] = chr(mt_rand(0, 255));
        }
        $variants[] = $b;
    }
    $variants[] = substr($good, 0, 16) . str_repeat("\0", 4096);              // valid header, garbage body
    foreach ($variants as $bytes) {
        foreach ([
            fn () => Image::fromBuffer($bytes)->metadata(),
            fn () => Image::fromBuffer($bytes)->resize(32)->png()->toBuffer(),
            fn () => Image::fromBuffer($bytes, ['failOn' => 'none'])->resize(16)->jpeg()->toBuffer(),
            fn () => Image::fromBuffer($bytes)->stats(),
        ] as $op) {
            try { $op(); $ok++; } catch (PixelForgeException $e) { $thrown++; }
        }
    }
}
echo "no crash, no warning; outcomes per format: ", ($ok + $thrown) / count($formats), "\n";
var_dump($thrown > 0);
// zero-length and tiny garbage
foreach (["", "x", "GIF89a", "\x89PNG\r\n\x1a\n", "\xFF\xD8\xFF"] as $junk) {
    try { $junk === '' ? Image::fromBuffer($junk) : Image::fromBuffer($junk)->metadata(); echo "accepted?\n"; }
    catch (PixelForgeException $e) { echo "rejected\n"; }
}
?>
--EXPECT--
no crash, no warning; outcomes per format: 72
bool(true)
rejected
rejected
rejected
rejected
rejected
