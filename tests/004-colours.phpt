--TEST--
pixelforge: colour parsing (hex, CSS names, arrays) and invalid colours
--EXTENSIONS--
pixelforge
--FILE--
<?php
use PixelForge\Image;
foreach (['red', '#00ff00', '#00f', 'navy', [255, 128, 0], ['r' => 10, 'g' => 20, 'b' => 30]] as $c) {
    $d = Image::create(['width' => 4, 'height' => 4, 'channels' => 3, 'background' => $c])->stats()['channels'];
    echo json_encode($c), ' => ', (int) $d[0]['mean'], ',', (int) $d[1]['mean'], ',', (int) $d[2]['mean'], "\n";
}
try { Image::create(['width' => 4, 'height' => 4, 'background' => 'not-a-colour']); }
catch (InvalidArgumentException $e) { echo $e->getMessage(), "\n"; }
?>
--EXPECT--
"red" => 255,0,0
"#00ff00" => 0,255,0
"#00f" => 0,0,255
"navy" => 0,0,128
[255,128,0] => 255,128,0
{"r":10,"g":20,"b":30} => 10,20,30
Invalid colour: not-a-colour
