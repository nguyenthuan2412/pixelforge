<?php
/** Functional tests for the pixelforge extension. Run: php tests/run.php */
use PixelForge\Image;
use PixelForge\PixelForge;
use PixelForge\PixelForgeException;

$F = __DIR__ . '/../fixtures';
$OUT = sys_get_temp_dir() . '/pixelforge-tests';
@mkdir($OUT, 0777, true);
$pass = 0; $fail = 0;
// Any warning / notice / deprecation is a test failure (silent fallbacks must not slip through).
set_error_handler(function (int $no, string $msg, string $file, int $line) {
    throw new ErrorException($msg, 0, $no, $file, $line);
});

function t(string $name, callable $fn): void {
    global $pass, $fail;
    try {
        $fn();
        $pass++;
        echo "  \033[32m✔\033[0m $name\n";
    } catch (Throwable $e) {
        $fail++;
        echo "  \033[31m✘ $name\033[0m\n    " . get_class($e) . ': ' . $e->getMessage() . "\n";
    }
}
function eq($a, $b, string $msg = ''): void {
    if ($a !== $b) throw new Exception(($msg ? "$msg: " : '') . 'expected ' . var_export($b, true) . ', got ' . var_export($a, true));
}
function ok($c, string $msg = 'assertion failed'): void { if (!$c) throw new Exception($msg); }
function dims(string $buf): array { $m = Image::fromBuffer($buf)->metadata(); return [$m['width'], $m['height']]; }

echo "pixelforge · libvips " . PixelForge::versions()['vips'] . " · PHP " . PHP_VERSION . "\n";

t('metadata (header only)', function () use ($F) {
    $m = Image::fromFile("$F/large.jpg")->metadata();
    eq($m['format'], 'jpeg'); eq($m['width'], 6000); eq($m['height'], 4000);
    eq($m['channels'], 3); eq($m['space'], 'srgb'); eq($m['hasAlpha'], false);
    $m = Image::fromFile("$F/alpha.png")->metadata();
    eq($m['format'], 'png'); eq($m['hasAlpha'], true); eq($m['channels'], 4);
});

t('resize cover (shrink-on-load)', function () use ($F, $OUT) {
    $i = Image::fromFile("$F/large.jpg")->resize(800, 800)->toFile("$OUT/cover.jpg");
    eq([$i['width'], $i['height']], [800, 800]); eq($i['format'], 'jpeg'); ok($i['size'] > 0);
});
t('resize width only keeps aspect', function () use ($F) {
    eq(dims(Image::fromFile("$F/large.jpg")->resize(300)->jpeg()->toBuffer()), [300, 200]);
});
t('resize height only', function () use ($F) {
    eq(dims(Image::fromFile("$F/large.jpg")->resize(null, 100)->png()->toBuffer()), [150, 100]);
});
t('resize inside', function () use ($F) {
    eq(dims(Image::fromFile("$F/large.jpg")->resize(500, 500, ['fit' => 'inside'])->toBuffer()), [500, 333]);
});
t('resize outside', function () use ($F) {
    eq(dims(Image::fromFile("$F/large.jpg")->resize(500, 500, ['fit' => 'outside'])->toBuffer()), [750, 500]);
});
t('resize fill', function () use ($F) {
    eq(dims(Image::fromFile("$F/large.jpg")->resize(320, 100, ['fit' => 'fill'])->toBuffer()), [320, 100]);
});
t('resize contain + background', function () use ($F) {
    $r = Image::fromFile("$F/large.jpg")->resize(400, 400, ['fit' => 'contain', 'background' => '#ff000080'])->png()->toBufferWithInfo();
    eq([$r['info']['width'], $r['info']['height'], $r['info']['channels']], [400, 400, 4]);
});
t('resize cover with gravity north + attention', function () use ($F) {
    eq(dims(Image::fromFile("$F/large.jpg")->resize(200, 300, ['position' => 'top'])->toBuffer()), [200, 300]);
    eq(dims(Image::fromFile("$F/large.jpg")->resize(200, 300, ['position' => 'attention'])->toBuffer()), [200, 300]);
});
t('withoutEnlargement', function () use ($F) {
    eq(dims(Image::fromFile("$F/alpha.png")->resize(2000, null, ['withoutEnlargement' => true])->toBuffer()), [800, 600]);
});
t('resize from buffer', function () use ($F) {
    $buf = file_get_contents("$F/large.jpg");
    eq(dims(Image::fromBuffer($buf)->resize(640)->webp()->toBuffer()), [640, 427]);
});
t('extract / extend / trim', function () use ($F) {
    eq(dims(Image::fromFile("$F/alpha.png")->extract(['left' => 10, 'top' => 20, 'width' => 100, 'height' => 50])->toBuffer()), [100, 50]);
    eq(dims(Image::fromFile("$F/alpha.png")->extend(10)->toBuffer()), [820, 620]);
    eq(dims(Image::fromFile("$F/alpha.png")->extend(['left' => 5, 'extendWith' => 'mirror'])->toBuffer()), [805, 600]);
    $padded = Image::fromFile("$F/overlay.png")->flatten()->extend(['top' => 30, 'bottom' => 30, 'left' => 30, 'right' => 30, 'background' => 'white'])->png()->toBuffer();
    eq(dims(Image::fromBuffer($padded)->trim()->png()->toBuffer()), [120, 80]);
});
t('rotate / flip / flop / autoOrient / affine', function () use ($F) {
    eq(dims(Image::fromFile("$F/alpha.png")->rotate(90)->toBuffer()), [600, 800]);
    eq(dims(Image::fromFile("$F/alpha.png")->rotate(180)->flip()->flop()->toBuffer()), [800, 600]);
    $r = Image::fromFile("$F/overlay.png")->rotate(45, ['background' => 'transparent'])->toBufferWithInfo();
    ok($r['info']['width'] > 120);
    eq(dims(Image::fromFile("$F/large.jpg")->rotate()->resize(100)->toBuffer()), [100, 67]);
    eq(dims(Image::fromFile("$F/overlay.png")->affine([2, 0, 0, 2])->toBuffer()), [240, 160]);
});
t('filters: sharpen, blur, median, gamma, negate, normalise, clahe, threshold, linear, modulate, tint', function () use ($F) {
    $base = fn () => Image::fromFile("$F/alpha.png")->resize(200);
    foreach ([
        fn ($i) => $i->sharpen(), fn ($i) => $i->sharpen(['sigma' => 1.5]),
        fn ($i) => $i->blur(), fn ($i) => $i->blur(3), fn ($i) => $i->median(5),
        fn ($i) => $i->gamma(2.2), fn ($i) => $i->negate(['alpha' => false]),
        fn ($i) => $i->normalise(), fn ($i) => $i->clahe(['width' => 16, 'height' => 16]),
        fn ($i) => $i->threshold(100), fn ($i) => $i->linear(1.2, -10),
        fn ($i) => $i->linear([1, 0.5, 1.2], [0, 10, 0]),
        fn ($i) => $i->modulate(['brightness' => 1.2, 'saturation' => 0.5, 'hue' => 90]),
        fn ($i) => $i->tint('#3366ff'), fn ($i) => $i->greyscale(),
        fn ($i) => $i->convolve(['width' => 3, 'height' => 3, 'kernel' => [-1, 0, 1, -2, 0, 2, -1, 0, 1]]),
        fn ($i) => $i->recomb([[0.393, 0.769, 0.189], [0.349, 0.686, 0.168], [0.272, 0.534, 0.131]]),
        fn ($i) => $i->unflatten(),
    ] as $k => $op) {
        $buf = $op($base())->png()->toBuffer();
        ok(strlen($buf) > 100, "op #$k produced empty output");
    }
});
t('channels: removeAlpha / ensureAlpha / extractChannel / flatten', function () use ($F) {
    eq(Image::fromFile("$F/alpha.png")->removeAlpha()->toBufferWithInfo()['info']['channels'], 3);
    eq(Image::fromFile("$F/large.jpg")->resize(10)->ensureAlpha(0.5)->png()->toBufferWithInfo()['info']['channels'], 4);
    eq(Image::fromFile("$F/alpha.png")->extractChannel('green')->toBufferWithInfo()['info']['channels'], 1);
    eq(Image::fromFile("$F/alpha.png")->flatten(['background' => '#ffffff'])->toBufferWithInfo()['info']['channels'], 3);
});
t('composite (gravity, position, tile, blend)', function () use ($F) {
    $ov = Image::fromFile("$F/overlay.png");
    $r = Image::fromFile("$F/large.jpg")->resize(600)->composite([
        ['input' => $ov, 'gravity' => 'southeast'],
        ['input' => "$F/overlay.png", 'left' => 10, 'top' => 10, 'blend' => 'multiply'],
        ['input' => file_get_contents("$F/overlay.png"), 'tile' => true, 'blend' => 'soft-light'],
        ['input' => ['buffer' => file_get_contents("$F/overlay.png")], 'gravity' => 'north'],
    ])->jpeg()->toBufferWithInfo();
    eq([$r['info']['width'], $r['info']['height']], [600, 400]);
});
t('create canvas', function () {
    $r = Image::create(['width' => 64, 'height' => 32, 'channels' => 4, 'background' => '#00ff0080'])->png()->toBufferWithInfo();
    eq([$r['info']['width'], $r['info']['height'], $r['info']['channels']], [64, 32, 4]);
    $s = Image::fromBuffer($r['data'])->stats();
    eq((int) round($s['channels'][1]['mean']), 255); eq($s['isOpaque'], false);
});
t('output formats', function () use ($F, $OUT) {
    $fmts = PixelForge::format();
    foreach (['jpeg', 'png', 'webp', 'gif', 'tiff', 'avif', 'heif', 'jxl'] as $f) {
        if (!$fmts[$f]['output']) { echo "    (skip $f: not available in this libvips)\n"; continue; }
        $img = Image::fromFile("$F/alpha.png")->resize(160)->toFormat($f, ['quality' => 60, 'effort' => 1]);
        $info = $img->toFile("$OUT/out.$f");
        eq($info['width'], 160, $f); ok(filesize("$OUT/out.$f") > 0, $f);
        $m = Image::fromFile("$OUT/out.$f")->metadata();
        eq($m['format'], $f === 'avif' ? 'heif' : $f, "$f detected format");
        if ($f === 'avif') eq($m['compression'], 'av1');
    }
    $raw = Image::fromFile("$F/overlay.png")->raw()->toBuffer();
    eq(strlen($raw), 120 * 80 * 4);
});
t('format options: progressive jpeg, palette png, lossless webp, 4:4:4', function () use ($F) {
    $j = Image::fromFile("$F/alpha.png")->jpeg(['quality' => 90, 'progressive' => true, 'chromaSubsampling' => '4:4:4', 'mozjpeg' => true])->toBuffer();
    eq(Image::fromBuffer($j)->metadata()['isProgressive'], true);
    $p = Image::fromFile("$F/alpha.png")->png(['palette' => true, 'colours' => 16])->toBuffer();
    $full = Image::fromFile("$F/alpha.png")->png()->toBuffer();
    ok(strlen($p) < strlen($full), 'palette png should be smaller');
    ok(strlen(Image::fromFile("$F/overlay.png")->webp(['lossless' => true])->toBuffer()) > 0);
});
t('toBuffer defaults to input format', function () use ($F) {
    eq(Image::fromBuffer(Image::fromFile("$F/overlay.png")->toBuffer())->metadata()['format'], 'png');
});
t('metadata strip / keep', function () use ($F) {
    $src = Image::fromFile("$F/large.jpg")->resize(100)->keepMetadata()->jpeg()->toBuffer();
    ok(strlen($src) > 0);
});
t('clone pipelines are independent', function () use ($F) {
    $base = Image::fromFile("$F/large.jpg")->resize(400);
    $a = $base->clone()->resize(100)->toBufferWithInfo();
    $b = $base->clone()->toBufferWithInfo();
    eq($a['info']['width'], 100); eq($b['info']['width'], 400);
});
t('errors throw PixelForgeException', function () use ($F) {
    try { Image::fromFile('/nope.jpg')->toBuffer(); throw new Exception('no exception'); } catch (PixelForgeException $e) { ok(str_contains($e->getMessage(), 'nope')); }
    try { Image::fromBuffer('not an image')->metadata(); throw new Exception('no exception'); } catch (PixelForgeException $e) {}
    try { Image::fromFile("$F/large.jpg", ['limitInputPixels' => 1000])->resize(10)->toBuffer(); throw new Exception('no exception'); } catch (PixelForgeException $e) { ok(str_contains($e->getMessage(), 'pixel limit')); }
    try { Image::fromFile("$F/alpha.png")->extract(['left' => 0, 'top' => 0, 'width' => 9000, 'height' => 1])->toBuffer(); throw new Exception('no exception'); } catch (PixelForgeException $e) {}
});
t('animated: join frames -> gif -> load all pages -> resize -> webp', function () use ($F, $OUT) {
    $frames = [];
    foreach (['#ff0000', '#00ff00', '#0000ff', '#ffff00'] as $c) {
        $frames[] = Image::create(['width' => 200, 'height' => 150, 'channels' => 3, 'background' => $c]);
    }
    $gif = Image::join($frames, ['animated' => true])->gif(['loop' => 0, 'delay' => [100, 200, 300, 400]])->toBuffer();
    $m = Image::fromBuffer($gif)->metadata();
    eq($m['format'], 'gif'); eq($m['height'], 150, 'first page only by default');
    $m = Image::fromBuffer($gif, ['animated' => true])->metadata();
    eq([$m['width'], $m['height'], $m['pages']], [200, 150, 4]); eq($m['delay'], [100, 200, 300, 400]); eq($m['loop'], 0);
    $r = Image::fromBuffer($gif, ['animated' => true])->resize(100, 100)->extend(5)->webp()->toBufferWithInfo();
    eq([$r['info']['width'], $r['info']['height'], $r['info']['pages']], [110, 110, 4]);
    $m = Image::fromBuffer($r['data'], ['animated' => true])->metadata();
    eq([$m['format'], $m['pages'], $m['pageHeight']], ['webp', 4, 110]);
    eq(Image::fromBuffer($gif, ['page' => 2])->stats()['dominant'], ['r' => 8, 'g' => 8, 'b' => 248]);
});
t('join grid', function () use ($F) {
    $r = Image::join(["$F/overlay.png", "$F/overlay.png", "$F/overlay.png"], ['across' => 2, 'shim' => 4])->png()->toBufferWithInfo();
    eq([$r['info']['width'], $r['info']['height']], [244, 164]);
});
t('text input', function () {
    $r = Image::text(['text' => '<span foreground="red">Hello</span> pixelforge', 'dpi' => 150, 'rgba' => true])->png()->toBufferWithInfo();
    ok($r['info']['width'] > 50 && $r['info']['height'] > 10); eq($r['info']['channels'], 4);
});
t('raw input/output roundtrip + noise', function () {
    $raw = Image::create(['width' => 64, 'height' => 48, 'channels' => 3, 'noise' => ['type' => 'gaussian', 'mean' => 128, 'sigma' => 30]])->raw()->toBuffer();
    eq(strlen($raw), 64 * 48 * 3);
    $r = Image::fromBuffer($raw, ['raw' => ['width' => 64, 'height' => 48, 'channels' => 3]])->png()->toBuffer();
    eq(Image::fromBuffer($r)->raw()->toBuffer(), $raw);
    $s = Image::fromRaw($raw, ['width' => 64, 'height' => 48, 'channels' => 3])->stats();
    ok(abs($s['channels'][0]['mean'] - 128) < 5); ok($s['entropy'] > 4); ok($s['sharpness'] > 1);
});
t('joinChannel / bandbool / boolean / dilate / erode', function () use ($F) {
    $base = Image::fromFile("$F/alpha.png")->removeAlpha()->resize(100);
    eq($base->clone()->joinChannel(Image::create(['width' => 100, 'height' => 75, 'channels' => 1, 'background' => '#808080']))->png()->toBufferWithInfo()['info']['channels'], 4);
    eq($base->clone()->bandbool('and')->toBufferWithInfo()['info']['channels'], 1);
    ok(strlen($base->clone()->boolean(Image::fromFile("$F/alpha.png")->removeAlpha()->resize(100), 'eor')->png()->toBuffer()) > 0);
    ok(strlen($base->clone()->threshold(128)->dilate(2)->erode(1)->png()->toBuffer()) > 0);
});
t('resize kernels + fastShrinkOnLoad=false', function () use ($F) {
    foreach (['nearest', 'linear', 'cubic', 'mitchell', 'lanczos2', 'lanczos3', 'mks2013', 'mks2021'] as $k) {
        eq(dims(Image::fromFile("$F/large.jpg")->resize(300, null, ['kernel' => $k])->toBuffer()), [300, 200], $k);
    }
    eq(dims(Image::fromFile("$F/large.jpg")->resize(300, null, ['fastShrinkOnLoad' => false])->toBuffer()), [300, 200]);
});
t('tile: deep zoom zip (buffer) and directory (file)', function () use ($F, $OUT) {
    $zip = Image::fromFile("$F/large.jpg")->resize(1024)->tile(['size' => 256])->toBuffer();
    eq(substr($zip, 0, 2), 'PK');
    $info = Image::fromFile("$F/large.jpg")->resize(1024)->tile(['size' => 256, 'layout' => 'google'])->toFile("$OUT/tiles");
    ok(is_dir("$OUT/tiles/0") && is_file("$OUT/tiles/0/0/0.jpg"));
});
t('withIccProfile / withExif', function () use ($F) {
    $b = Image::fromFile("$F/overlay.png")->withIccProfile('p3')->jpeg()->toBuffer();
    eq(Image::fromBuffer($b)->metadata()['hasProfile'], true);
    $b = Image::fromFile("$F/overlay.png")->withExif(['IFD0' => ['Copyright' => 'pixelforge test', 'Artist' => 'me']])->jpeg()->toBuffer();
    $m = Image::fromBuffer($b)->metadata();
    ok(isset($m['exif']) && str_contains($m['exif'], 'pixelforge test'));
});
t('timeout aborts', function () use ($F) {
    try {
        // ~1-3 s of work on any machine; the 50 ms deadline must cut it short
        $t = microtime(true);
        Image::fromFile("$F/large.jpg")->blur(30)->timeout(['seconds' => 0.05])->png(['compressionLevel' => 9])->toBuffer();
        throw new Exception('no timeout');
    } catch (PixelForgeException $e) {
        ok(str_contains($e->getMessage(), 'timeout'), $e->getMessage());
        ok(microtime(true) - $t < 1.0, 'timeout fired late: ' . round(microtime(true) - $t, 2) . 's');
    }
});
t('metadata extras', function () use ($F) {
    $m = Image::fromFile("$F/large.jpg")->metadata();
    eq($m['chromaSubsampling'], '4:4:4'); eq($m['autoOrient'], ['width' => 6000, 'height' => 4000]);
    $s = Image::fromFile("$F/overlay.png")->stats();
    ok(isset($s['dominant']['r'], $s['entropy'], $s['sharpness']));
});
t('API sweep: every public method with documented options', function () use ($F, $OUT) {
    $src = fn () => Image::fromFile("$F/alpha.png")->resize(120);
    $calls = [
        'resize fits' => fn () => array_map(fn ($fit) => $src()->resize(60, 40, ['fit' => $fit])->png()->toBuffer(), ['cover', 'contain', 'fill', 'inside', 'outside']),
        'resize gravities' => fn () => array_map(fn ($g) => $src()->resize(50, 20, ['position' => $g])->png()->toBuffer(),
            ['centre', 'center', 'north', 'northeast', 'east', 'southeast', 'south', 'southwest', 'west', 'northwest',
             'top', 'right top', 'right', 'right bottom', 'bottom', 'left bottom', 'left', 'left top', 'entropy', 'attention']),
        'resize width/height in options' => fn () => $src()->resize(null, null, ['width' => 30, 'height' => 30])->png()->toBuffer(),
        'resize withoutReduction' => fn () => $src()->resize(10, null, ['withoutReduction' => true])->png()->toBuffer(),
        'extend background colour' => fn () => $src()->extend(['top' => 2, 'bottom' => 2, 'left' => 2, 'right' => 2, 'background' => 'navy'])->png()->toBuffer(),
        'extend copy/repeat' => fn () => [$src()->extend(['left' => 3, 'extendWith' => 'copy'])->png()->toBuffer(), $src()->extend(['left' => 3, 'extendWith' => 'repeat'])->png()->toBuffer()],
        'trim options' => fn () => $src()->trim(['threshold' => 20, 'background' => 'white', 'lineArt' => true])->png()->toBuffer(),
        'rotate arbitrary + background' => fn () => $src()->rotate(30, ['background' => 'red'])->png()->toBuffer(),
        'rotate negative / 360+' => fn () => [$src()->rotate(-90)->png()->toBuffer(), $src()->rotate(450)->png()->toBuffer()],
        'affine options' => fn () => $src()->affine([1, 0.2, 0, 1], ['background' => 'white', 'interpolator' => 'nohalo', 'idx' => 1, 'odx' => 2])->png()->toBuffer(),
        'sharpen full options' => fn () => $src()->sharpen(['sigma' => 1, 'm1' => 0.5, 'm2' => 3, 'x1' => 2, 'y2' => 10, 'y3' => 20])->png()->toBuffer(),
        'blur options array' => fn () => $src()->blur(['sigma' => 2, 'precision' => 'approximate', 'minAmplitude' => 0.1])->png()->toBuffer(),
        'gamma in/out' => fn () => $src()->gamma(2.2, 3.0)->png()->toBuffer(),
        'normalise / normalize' => fn () => [$src()->normalise(['lower' => 2, 'upper' => 98])->png()->toBuffer(), $src()->normalize()->png()->toBuffer()],
        'threshold rgb' => fn () => $src()->threshold(100, ['greyscale' => false])->png()->toBuffer(),
        'modulate lightness' => fn () => $src()->modulate(['lightness' => 20])->png()->toBuffer(),
        'tint named / array' => fn () => [$src()->tint('orange')->png()->toBuffer(), $src()->tint([10, 200, 30])->png()->toBuffer()],
        'grayscale alias / toColorspace' => fn () => [$src()->grayscale()->png()->toBuffer(), $src()->toColorspace('b-w')->png()->toBuffer()],
        'colourspaces' => fn () => array_map(fn ($c) => $src()->toColourspace($c)->tiff()->toBuffer(), ['srgb', 'b-w', 'rgb16', 'grey16', 'lab', 'cmyk', 'xyz', 'hsv']),
        'extractChannel all names' => fn () => array_map(fn ($c) => $src()->extractChannel($c)->png()->toBuffer(), ['red', 'green', 'blue', 'alpha', 0, 3]),
        'composite create/text inputs' => fn () => $src()->composite([
            ['input' => ['create' => ['width' => 10, 'height' => 10, 'channels' => 4, 'background' => 'red']], 'gravity' => 'northwest'],
            ['input' => ['text' => ['text' => 'hi', 'rgba' => true]], 'left' => 5, 'top' => 5, 'premultiplied' => false],
        ])->png()->toBuffer(),
        'composite blend modes' => fn () => array_map(fn ($b) => $src()->composite([['input' => "$F/overlay.png", 'blend' => $b]])->png()->toBuffer(),
            ['over', 'multiply', 'screen', 'overlay', 'darken', 'lighten', 'colour-dodge', 'colour-burn', 'hard-light', 'soft-light', 'difference', 'exclusion', 'dest-over', 'xor', 'add', 'saturate']),
        'jpeg options' => fn () => $src()->flatten()->jpeg(['quality' => 50, 'progressive' => true, 'chromaSubsampling' => '4:4:4', 'mozjpeg' => true, 'optimiseCoding' => false])->toBuffer(),
        'png options' => fn () => $src()->png(['compressionLevel' => 9, 'progressive' => true, 'adaptiveFiltering' => true, 'palette' => true, 'quality' => 60, 'effort' => 1, 'colours' => 8, 'dither' => 0.5])->toBuffer(),
        'webp options' => fn () => [$src()->webp(['quality' => 50, 'alphaQuality' => 50, 'smartSubsample' => true, 'effort' => 0, 'minSize' => true, 'mixed' => true])->toBuffer(), $src()->webp(['nearLossless' => true])->toBuffer(), $src()->webp(['nearLossless' => 40])->toBuffer()],
        'avif/heif options' => fn () => [$src()->avif(['quality' => 40, 'effort' => 0, 'chromaSubsampling' => '4:2:0', 'lossless' => false])->toBuffer(), $src()->heif(['compression' => 'av1', 'effort' => 0])->toBuffer()],
        'gif options' => fn () => $src()->gif(['colours' => 16, 'effort' => 1, 'dither' => 0, 'interFrameMaxError' => 5, 'interPaletteMaxError' => 5, 'reuse' => true, 'loop' => 2, 'progressive' => true])->toBuffer(),
        'tiff options' => fn () => array_map(fn ($c) => $src()->tiff(['compression' => $c, 'predictor' => 'horizontal', 'tile' => true, 'tileWidth' => 64, 'tileHeight' => 64])->toBuffer(), ['none', 'jpeg', 'deflate', 'lzw', 'packbits', 'webp']),
        'tiff zstd (optional in libtiff)' => function () use ($src) {
            try { $src()->tiff(['compression' => 'zstd', 'predictor' => 'horizontal'])->toBuffer(); }
            catch (PixelForgeException $e) { if (!str_contains($e->getMessage(), 'not configured')) throw $e; }
        },
        'tiff pyramid' => fn () => $src()->tiff(['pyramid' => true, 'compression' => 'deflate'])->toBuffer(),
        'toFormat aliases' => fn () => [$src()->toFormat('jpg')->toBuffer(), $src()->toFormat('tif')->toBuffer()],
        'toBuffer(format) override' => fn () => $src()->toBuffer('webp'),
        'toFile infers format from extension' => fn () => array_map(fn ($e) => $src()->toFile("$OUT/sweep.$e"), ['jpg', 'jpeg', 'png', 'webp', 'gif', 'tif', 'tiff', 'avif', 'heic']),
        'keep flags' => fn () => [$src()->keepExif()->keepIccProfile()->keepXmp()->jpeg()->toBuffer(), $src()->withMetadata()->png()->toBuffer()],
        'withIccProfile builtins' => fn () => array_map(fn ($p) => $src()->withIccProfile($p)->jpeg()->toBuffer(), ['srgb', 'p3', 'cmyk']),
        'withExifMerge' => fn () => $src()->withExifMerge(['IFD0' => ['Software' => 'pixelforge']])->jpeg()->toBuffer(),
        'tile layouts' => fn () => array_map(fn ($l) => Image::fromFile("$F/alpha.png")->tile(['size' => 128, 'layout' => $l, 'overlap' => 1])->toBuffer(), ['dz', 'zoomify', 'google', 'iiif', 'iiif3']),
        'fromBuffer options' => fn () => Image::fromBuffer(file_get_contents("$F/large.jpg"), ['failOn' => 'none', 'limitInputPixels' => false, 'autoOrient' => true, 'ignoreIcc' => true])->resize(10)->toBuffer(),
        'fromFile pages/page' => fn () => Image::fromFile("$F/alpha.png", ['pages' => 1, 'page' => 0, 'density' => 150, 'unlimited' => true])->toBuffer(),
        'create 1/2/3/4 channels' => fn () => array_map(fn ($c) => Image::create(['width' => 8, 'height' => 8, 'channels' => $c, 'background' => 'gray'])->png()->toBuffer(), [1, 2, 3, 4]),
        'text options' => fn () => Image::text(['text' => 'pixelforge pixelforge', 'font' => 'sans 12', 'width' => 60, 'align' => 'center', 'justify' => true, 'spacing' => 2, 'wrap' => 'word-char'])->png()->toBuffer(),
        'join options' => fn () => Image::join(["$F/overlay.png", "$F/overlay.png"], ['across' => 2, 'shim' => 3, 'background' => 'red', 'halign' => 'center', 'valign' => 'bottom'])->png()->toBuffer(),
        'static helpers' => fn () => [PixelForge::versions(), PixelForge::format(), PixelForge::memory(), PixelForge::concurrency()],
    ];
    $failed = [];
    foreach ($calls as $name => $fn) {
        try { $fn(); } catch (Throwable $e) { $failed[] = "$name: " . get_class($e) . ' ' . $e->getMessage(); }
    }
    ok(!$failed, implode("\n    ", $failed));
});
t('invalid input is rejected with a clear exception (no silent fallback)', function () use ($F) {
    $cases = [
        'bad colour'        => [InvalidArgumentException::class, fn () => Image::create(['width' => 4, 'height' => 4, 'background' => 'rdd'])],
        'bad hex'           => [InvalidArgumentException::class, fn () => Image::create(['width' => 4, 'height' => 4, 'background' => '#zzzzzz'])],
        'bad channel name'  => [InvalidArgumentException::class, fn () => Image::fromFile("$F/alpha.png")->extractChannel('purple')],
        'bad fit'           => [PixelForgeException::class, fn () => Image::fromFile("$F/alpha.png")->resize(10, 10, ['fit' => 'stretch'])],
        'bad format'        => [PixelForgeException::class, fn () => Image::fromFile("$F/alpha.png")->toFormat('bmp')],
        'bad file ext'      => [PixelForgeException::class, fn () => Image::fromFile("$F/alpha.png")->toFile('/tmp/x.bmp')],
        'bad colourspace'   => [PixelForgeException::class, fn () => Image::fromFile("$F/alpha.png")->toColourspace('rainbow')],
        'bad blend'         => [PixelForgeException::class, fn () => Image::fromFile("$F/alpha.png")->composite([['input' => "$F/overlay.png", 'blend' => 'nope']])],
        'bad boolean op'    => [PixelForgeException::class, fn () => Image::fromFile("$F/alpha.png")->bandbool('nand')],
        'bad tile layout'   => [PixelForgeException::class, fn () => Image::fromFile("$F/alpha.png")->tile(['layout' => 'nope'])->toBuffer()],
        'convolve mismatch' => [PixelForgeException::class, fn () => Image::fromFile("$F/alpha.png")->convolve(['width' => 3, 'height' => 3, 'kernel' => [1, 2]])],
        'recomb not square' => [PixelForgeException::class, fn () => Image::fromFile("$F/alpha.png")->recomb([[1, 2]])],
        'channel range'     => [PixelForgeException::class, fn () => Image::fromFile("$F/alpha.png")->extractChannel(9)->toBuffer()],
        'create size'       => [PixelForgeException::class, fn () => Image::create(['width' => 0, 'height' => 4])],
        'create channels'   => [PixelForgeException::class, fn () => Image::create(['width' => 4, 'height' => 4, 'channels' => 7])],
        'raw too small'     => [PixelForgeException::class, fn () => Image::fromRaw('abc', ['width' => 10, 'height' => 10, 'channels' => 3])->toBuffer()],
        'empty buffer'      => [PixelForgeException::class, fn () => Image::fromBuffer('')],
        'animated size'     => [PixelForgeException::class, fn () => Image::join([Image::create(['width' => 4, 'height' => 4]), Image::create(['width' => 5, 'height' => 4])], ['animated' => true])->toBuffer()],
        'unwritable path'   => [PixelForgeException::class, fn () => Image::fromFile("$F/alpha.png")->toFile('/nonexistent-dir/x.png')],
    ];
    $problems = [];
    foreach ($cases as $name => [$expected, $fn]) {
        try { $fn(); $problems[] = "$name: no exception"; }
        catch (Throwable $e) { if (!$e instanceof $expected) $problems[] = "$name: got " . get_class($e) . ' (' . $e->getMessage() . ')'; }
    }
    ok(!$problems, implode("\n    ", $problems));
});
t('global config', function () {
    PixelForge::concurrency(2); eq(PixelForge::concurrency(), 2);
    PixelForge::cache(0, 0, 0);
    ok(isset(PixelForge::memory()['high']));
});

echo "\n$pass passed, $fail failed\n";
exit($fail ? 1 : 0);
