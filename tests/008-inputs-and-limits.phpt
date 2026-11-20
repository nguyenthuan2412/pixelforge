--TEST--
pixelforge: composite/join input resolution (bytes vs paths) and pixel limits for every source
--EXTENSIONS--
pixelforge
--FILE--
<?php
use PixelForge\Image;
use PixelForge\PixelForgeException;
$dir = sys_get_temp_dir() . '/pf-008-' . getmypid();
@mkdir($dir);
$png = Image::create(['width' => 8, 'height' => 8, 'channels' => 4, 'background' => 'red'])->png()->toBuffer();
file_put_contents("$dir/logo.png", $png);
$base = fn () => Image::create(['width' => 32, 'height' => 32, 'channels' => 3]);

// image bytes, path, explicit forms
foreach (['bytes' => $png, 'path' => "$dir/logo.png", 'file' => ['file' => "$dir/logo.png"], 'buffer' => ['buffer' => $png]] as $k => $in) {
    $r = $base()->composite([['input' => $in, 'gravity' => 'northwest']])->raw()->toBuffer();
    echo $k, ': ', ord($r[0]) === 255 ? 'red' : 'not red', "\n";
}
// a string that is neither image bytes nor an existing file is a path -> clear error
try { $base()->composite([['input' => "$dir/missing.png"]])->png()->toBuffer(); }
catch (PixelForgeException $e) { echo str_contains($e->getMessage(), 'missing') ? "missing path: error\n" : $e->getMessage(); }
// image bytes are never used as a file name, even if such a file exists
file_put_contents($dir . '/' . md5($png), 'x');
echo 'bytes stay bytes: ', strlen($base()->composite([['input' => $png]])->png()->toBuffer()) > 0 ? "yes\n" : "no\n";

// pixel limits apply to every kind of source
$big = ['limitInputPixels' => 100];
foreach ([
    'create' => fn () => Image::create(['width' => 20, 'height' => 20, 'channels' => 3] + $big)->png()->toBuffer(),
    'raw'    => fn () => Image::fromRaw(str_repeat("\0", 1200), ['width' => 20, 'height' => 20, 'channels' => 3] + $big)->png()->toBuffer(),
    'text'   => fn () => Image::text(['text' => 'limit', 'dpi' => 300] + $big)->png()->toBuffer(),
    'join'   => fn () => Image::join([$base(), $base()], ['across' => 2] + $big)->png()->toBuffer(),
    'buffer' => fn () => Image::fromBuffer($png, ['limitInputPixels' => 10])->png()->toBuffer(),
] as $k => $fn) {
    try { $fn(); echo "$k: no limit\n"; } catch (PixelForgeException $e) { echo "$k: ", $e->getMessage(), "\n"; }
}
echo 'limit disabled: ', strlen(Image::create(['width' => 20, 'height' => 20, 'channels' => 3, 'limitInputPixels' => false])->png()->toBuffer()) > 0 ? "ok\n" : "fail\n";
array_map('unlink', glob("$dir/*")); rmdir($dir);
?>
--EXPECT--
bytes: red
path: red
file: red
buffer: red
missing path: error
bytes stay bytes: yes
create: Input image exceeds pixel limit
raw: Input image exceeds pixel limit
text: Input image exceeds pixel limit
join: Input image exceeds pixel limit
buffer: Input image exceeds pixel limit
limit disabled: ok
