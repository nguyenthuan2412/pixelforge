<?php
// pixelforge side of the comparison. Usage: php bench.php <scenario> <iterations>
use PixelForge\Image;

$F = '/app/fixtures';
[$name, $n] = [$argv[1], (int) ($argv[2] ?? 20)];
$buf = file_get_contents("$F/large.jpg");

$jobs = [
    'resize800-jpeg'   => fn () => Image::fromFile("$F/large.jpg")->resize(800)->jpeg(['quality' => 80])->toBuffer(),
    'resize800-webp'   => fn () => Image::fromBuffer($buf)->resize(800)->webp(['quality' => 80])->toBuffer(),
    'cover320-sharpen' => fn () => Image::fromFile("$F/large.jpg")->resize(320, 240)->sharpen()->jpeg()->toBuffer(),
    'resize800-avif'   => fn () => Image::fromFile("$F/large.jpg")->resize(800)->avif(['effort' => 2])->toBuffer(),
    'reencode-full'    => fn () => Image::fromFile("$F/large.jpg")->jpeg(['quality' => 80])->toBuffer(),
    'png-alpha-200'    => fn () => Image::fromFile("$F/alpha.png")->resize(200)->png()->toBuffer(),
    'watermark-1200'   => fn () => Image::fromFile("$F/large.jpg")->resize(1200)->composite([['input' => "$F/overlay.png", 'gravity' => 'southeast']])->jpeg()->toBuffer(),
    'mixed'            => function () use (&$jobs) { $o = ''; foreach (['resize800-jpeg', 'resize800-webp', 'png-alpha-200', 'cover320-sharpen', 'reencode-full'] as $j) $o = $jobs[$j](); return $o; },
    'metadata'         => fn () => (string) Image::fromFile("$F/large.jpg")->metadata()['width'],
];
$job = $jobs[$name];
$out = $job();
$t = hrtime(true);
for ($i = 0; $i < $n; $i++) $out = $job();
$ms = (hrtime(true) - $t) / 1e6 / $n;
preg_match('/VmHWM:\s+(\d+)/', file_get_contents('/proc/self/status'), $m);
usleep(1500000);
preg_match('/VmRSS:\s+(\d+)/', file_get_contents('/proc/self/status'), $r);
echo json_encode(['name' => $name, 'ms' => $ms, 'peakMB' => $m[1] / 1024, 'steadyMB' => $r[1] / 1024, 'bytes' => strlen($out)]), "\n";
