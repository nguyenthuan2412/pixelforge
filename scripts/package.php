<?php
/**
 * Writes package.xml (PECL) for the files a phpize build needs, then you can run `pecl package`.
 *   php scripts/package.php 0.1.0 && pecl package
 */
$root = dirname(__DIR__);
chdir($root);
$version = $argv[1] ?? (preg_match('/^version:\s*(\S+)/m', file_get_contents('project.yml'), $m) ? $m[1] : '0.0.0');
$stability = preg_match('/(alpha|beta|RC)/i', $version, $s) ? strtolower($s[1]) : 'stable';
if ($stability === 'rc' || ($stability === 'stable' && str_starts_with($version, '0.'))) $stability = 'beta';

$files = [];
$add = function (string $path, string $role) use (&$files) { $files[$path] = $role; };
foreach (['config.m4' => 'src', 'LICENSE' => 'doc', 'NOTICE' => 'doc', 'README.md' => 'doc', 'CHANGELOG.md' => 'doc',
          'project.yml' => 'src', 'scripts/install-libvips.sh' => 'doc'] as $f => $r) {
    if (is_file($f)) $add($f, $r);
}
$it = fn (string $dir) => new RecursiveIteratorIterator(new RecursiveDirectoryIterator($dir, FilesystemIterator::SKIP_DOTS));
foreach (['src', 'generated', 'deps'] as $dir) {
    foreach ($it($dir) as $f) $add(str_replace('\\', '/', $f->getPathname()), 'src');
}
foreach (glob('tests/*.phpt') as $f) $add($f, 'test');
ksort($files);

$x = new XMLWriter();
$x->openMemory();
$x->setIndent(true);
$x->setIndentString(' ');
$x->startDocument('1.0', 'UTF-8');
$x->startElement('package');
foreach (['packagerversion' => '1.10.1', 'version' => '2.0', 'xmlns' => 'http://pear.php.net/dtd/package-2.0',
          'xmlns:tasks' => 'http://pear.php.net/dtd/tasks-1.0', 'xmlns:xsi' => 'http://www.w3.org/2001/XMLSchema-instance',
          'xsi:schemaLocation' => 'http://pear.php.net/dtd/tasks-1.0 http://pear.php.net/dtd/tasks-1.0.xsd http://pear.php.net/dtd/package-2.0 http://pear.php.net/dtd/package-2.0.xsd'] as $k => $v) {
    $x->writeAttribute($k, $v);
}
$x->writeElement('name', 'pixelforge');
$x->writeElement('channel', 'pecl.php.net');
$x->writeElement('summary', 'High performance, low memory image processing on libvips with a sharp-like API');
$x->writeElement('description', 'pixelforge is a PHP extension for fast image processing on libvips: resize (with JPEG/WebP shrink-on-load), crop, rotate, composite, filters, colour management, animated GIF/WebP, Deep Zoom tiles, and JPEG/PNG/WebP/AVIF/HEIF/GIF/TIFF output. The fluent API is modelled on Node.js sharp. Requires libvips >= 8.15 (vips-cpp), gmp and mpfr.');
$x->startElement('lead');
$x->writeElement('name', 'nguyenthuan2412');
$x->writeElement('user', 'nguyenthuan2412');
$x->writeElement('email', 'nguyenthuan2412@users.noreply.github.com');
$x->writeElement('active', 'yes');
$x->endElement();
$x->writeElement('date', gmdate('Y-m-d'));
$x->startElement('version');
$x->writeElement('release', $version);
$x->writeElement('api', $version);
$x->endElement();
$x->startElement('stability');
$x->writeElement('release', $stability);
$x->writeElement('api', $stability);
$x->endElement();
$x->startElement('license');
$x->writeAttribute('uri', 'https://www.apache.org/licenses/LICENSE-2.0');
$x->text('Apache-2.0');
$x->endElement();
$x->writeElement('notes', "See https://github.com/nguyenthuan2412/pixelforge/releases/tag/v$version");
$x->startElement('contents');
$x->startElement('dir');
$x->writeAttribute('name', '/');
foreach ($files as $path => $role) {
    $x->startElement('file');
    $x->writeAttribute('name', $path);
    $x->writeAttribute('role', $role);
    $x->endElement();
}
$x->endElement();
$x->endElement();
$x->startElement('dependencies');
$x->startElement('required');
$x->startElement('php');
$x->writeElement('min', '8.4.0');
$x->writeElement('max', '8.5.99');
$x->endElement();
$x->startElement('pearinstaller');
$x->writeElement('min', '1.10.0');
$x->endElement();
$x->endElement();
$x->endElement();
$x->writeElement('providesextension', 'pixelforge');
$x->startElement('extsrcrelease');
$x->startElement('configureoption');
$x->writeAttribute('name', 'with-pixelforge-vips');
$x->writeAttribute('default', 'no');
$x->writeAttribute('prompt', 'libvips prefix (no = use pkg-config)');
$x->endElement();
$x->endElement();
$x->endElement();
$x->endDocument();
file_put_contents('package.xml', $x->outputMemory());
fprintf(STDERR, "package.xml: pixelforge %s (%s), %d files\n", $version, $stability, count($files));
