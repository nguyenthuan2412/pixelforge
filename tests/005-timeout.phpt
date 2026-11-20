--TEST--
pixelforge: sub-second timeout aborts with a PixelForgeException
--EXTENSIONS--
pixelforge
--FILE--
<?php
use PixelForge\Image;
use PixelForge\PixelForgeException;
$t = microtime(true);
try {
    Image::create(['width' => 6000, 'height' => 4000, 'channels' => 3, 'noise' => ['type' => 'gaussian']])
        ->blur(30)->timeout(['seconds' => 0.05])->png()->toBuffer();
    echo "no timeout\n";
} catch (PixelForgeException $e) {
    echo $e->getMessage(), "\n";
    // under valgrind (run-tests -m sets USE_ZEND_ALLOC=0) everything is ~50x slower
    var_dump(microtime(true) - $t < (getenv('USE_ZEND_ALLOC') === '0' ? 60 : 1.5));
}
// a quick job with a generous timeout is unaffected
echo strlen(Image::create(['width' => 64, 'height' => 64, 'channels' => 3])->timeout(['seconds' => 10])->png()->toBuffer()) > 0 ? "ok\n" : "fail\n";
?>
--EXPECT--
timeout: processing exceeded 0.05s
bool(true)
ok
