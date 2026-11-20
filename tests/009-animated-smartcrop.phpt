--TEST--
pixelforge: smart crop on animated images uses the first frame's crop window for every frame
--EXTENSIONS--
pixelforge
--FILE--
<?php
use PixelForge\Image;
// three frames with a bright square in a different corner; frame 0 decides the window
$frame = function (int $x, int $y) {
    return Image::create(['width' => 120, 'height' => 90, 'channels' => 3, 'background' => '#202020'])
        ->composite([['input' => Image::create(['width' => 30, 'height' => 30, 'channels' => 3, 'noise' => ['type' => 'gaussian', 'mean' => 200, 'sigma' => 60]]), 'left' => $x, 'top' => $y]]);
};
$anim = Image::join([$frame(85, 55), $frame(5, 5), $frame(5, 55)], ['animated' => true])->webp(['lossless' => true])->toBuffer();   // multi-page, pixel exact
foreach (['attention', 'entropy'] as $mode) {
    $first = Image::fromBuffer($anim)->resize(40, 40, ['position' => $mode])->raw()->toBuffer();       // frame 0 only
    $all = Image::fromBuffer($anim, ['animated' => true])->resize(40, 40, ['position' => $mode]);
    $info = $all->clone()->webp(['lossless' => true])->toBufferWithInfo()['info'];
    $frame0 = substr($all->raw()->toBuffer(), 0, strlen($first));
    echo "$mode: {$info['width']}x{$info['height']} pages={$info['pages']} frame0-matches-single=", $frame0 === $first ? 'yes' : 'no', "\n";
}
// join (sequentially loaded inputs) followed by steps that need random access
$png = Image::create(['width' => 60, 'height' => 40, 'channels' => 3, 'noise' => ['type' => 'gaussian']])->png()->toBuffer();
foreach ([
    'join+entropy'  => fn () => Image::join([Image::fromBuffer($png), Image::fromBuffer($png)], ['animated' => true])->resize(20, 20, ['position' => 'entropy'])->gif()->toBuffer(),
    'join+rotate90' => fn () => Image::join([$png, $png], ['across' => 2])->rotate(90)->png()->toBuffer(),
    'join+flip'     => fn () => Image::join([$png, $png])->flip()->png()->toBuffer(),
    'join+trim'     => fn () => Image::join([$png, $png])->trim()->png()->toBuffer(),
] as $k => $fn) {
    echo $k, ': ', strlen($fn()) > 0 ? "ok\n" : "empty\n";
}
?>
--EXPECT--
attention: 40x40 pages=3 frame0-matches-single=yes
entropy: 40x40 pages=3 frame0-matches-single=yes
join+entropy: ok
join+rotate90: ok
join+flip: ok
join+trim: ok
