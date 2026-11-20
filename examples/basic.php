<?php
use PixelForge\Image;
use PixelForge\PixelForge;

$in = $argv[1] ?? __DIR__ . '/../fixtures/large.jpg';
$out = sys_get_temp_dir();

print_r(Image::fromFile($in)->metadata());

// Thumbnail: auto-orient + shrink-on-load + crop to fill 300x300, WebP
Image::fromFile($in)->rotate()->resize(300, 300, ['fit' => 'cover', 'position' => 'attention'])
    ->webp(['quality' => 80])->toFile("$out/thumb.webp");

// Responsive variants from a single in-memory buffer (source bytes are not copied)
$buf = file_get_contents($in);
foreach ([320, 640, 1280] as $w) {
    $info = Image::fromBuffer($buf)->resize($w)->avif(['quality' => 50])->toFile("$out/img-$w.avif");
    echo "$w => {$info['width']}x{$info['height']} {$info['size']} bytes\n";
}

// Watermark
Image::fromFile($in)->resize(1200)
    ->composite([['input' => __DIR__ . '/../fixtures/overlay.png', 'gravity' => 'southeast']])
    ->jpeg(['quality' => 82, 'progressive' => true, 'mozjpeg' => true])
    ->toFile("$out/watermarked.jpg");

print_r(PixelForge::memory());
