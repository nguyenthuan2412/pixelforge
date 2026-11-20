<?php
/**
 * Speed + memory benchmark. Each scenario runs in a fresh process so peak RSS
 * (VmHWM) is measured per task. Usage: php tests/bench.php [iterations]
 */
use PixelForge\Image;

$F = __DIR__ . '/../fixtures';
$N = (int) ($argv[1] ?? 20);

if (($argv[1] ?? '') === '--child') {
    [$name, $n] = [$argv[2], (int) $argv[3]];
    $buf = file_get_contents("$F/large.jpg");
    $base = rss();
    $jobs = [
        'jpeg 6000x4000 -> 800px jpeg (file)' => fn () => Image::fromFile("$F/large.jpg")->resize(800)->jpeg(['quality' => 80])->toBuffer(),
        'jpeg 6000x4000 -> 800px webp (buffer)' => fn () => Image::fromBuffer($buf)->resize(800)->webp(['quality' => 80])->toBuffer(),
        'jpeg -> 320x240 cover + sharpen' => fn () => Image::fromFile("$F/large.jpg")->resize(320, 240)->sharpen()->jpeg()->toBuffer(),
        'jpeg -> avif 800px' => fn () => Image::fromFile("$F/large.jpg")->resize(800)->avif(['effort' => 2])->toBuffer(),
        'full-size jpeg re-encode (no resize)' => fn () => Image::fromFile("$F/large.jpg")->jpeg(['quality' => 80])->toBuffer(),
        'gd: jpeg -> 800px jpeg' => function () use ($F) {
            $src = imagecreatefromjpeg("$F/large.jpg");
            $dst = imagescale($src, 800, -1, IMG_BICUBIC);
            ob_start(); imagejpeg($dst, null, 80); $o = ob_get_clean();
            unset($src, $dst);
            return $o;
        },
        'imagick: jpeg -> 800px jpeg' => function () use ($F) {
            $im = new Imagick("$F/large.jpg");
            $im->resizeImage(800, 0, Imagick::FILTER_LANCZOS, 1);
            $im->setImageCompressionQuality(80);
            $o = $im->getImageBlob(); $im->clear();
            return $o;
        },
    ];
    $job = $jobs[$name];
    $job(); // warm-up
    $t = hrtime(true);
    for ($i = 0; $i < $n; $i++) $job();
    $ms = (hrtime(true) - $t) / 1e6 / $n;
    printf("%-42s %8.1f ms/op %8.1f MB peak RSS\n", $name, $ms, (rss() - 0) / 1024);
    exit;
}

function rss(): int {
    preg_match('/VmHWM:\s+(\d+)/', file_get_contents('/proc/self/status'), $m);
    return (int) $m[1];
}

echo "Benchmark (iterations=$N, " . PHP_VERSION . ", vips " . PixelForge\PixelForge::versions()['vips'] . ", threads " . PixelForge\PixelForge::concurrency() . ")\n";
foreach ([
    'jpeg 6000x4000 -> 800px jpeg (file)', 'jpeg 6000x4000 -> 800px webp (buffer)',
    'jpeg -> 320x240 cover + sharpen', 'jpeg -> avif 800px', 'full-size jpeg re-encode (no resize)',
    'gd: jpeg -> 800px jpeg', 'imagick: jpeg -> 800px jpeg',
] as $name) {
    if (str_starts_with($name, 'gd') && !extension_loaded('gd')) continue;
    if (str_starts_with($name, 'imagick') && !extension_loaded('imagick')) continue;
    $n = str_contains($name, 'gd') || str_contains($name, 'imagick') || str_contains($name, 'full') ? max(1, intdiv($N, 4)) : $N;
    passthru(PHP_BINARY . ' ' . escapeshellarg(__FILE__) . ' --child ' . escapeshellarg($name) . " $n");
}
