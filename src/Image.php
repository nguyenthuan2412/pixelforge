<?php

namespace PixelForge;

class PixelForgeException extends \RuntimeException
{
}

/**
 * Fluent, lazy image pipeline (API modelled on Node's sharp).
 *
 *   Image::fromFile('in.jpg')->resize(800, 600)->webp(['quality' => 80])->toFile('out.webp');
 *
 * Nothing is decoded until an output method (toFile/toBuffer/stats) runs.
 */
class Image
{
    public const KEEP_NONE = 0;
    public const KEEP_EXIF = 1;
    public const KEEP_XMP = 2;
    public const KEEP_IPTC = 4;
    public const KEEP_ICC = 8;
    public const KEEP_OTHER = 16;
    public const KEEP_ALL = 31;

    private mixed $h;
    private int $keepFlags = 0;

    private function __construct(mixed $handle)
    {
        $this->h = $handle;
    }

    // ------------------------------------------------------------ inputs

    /**
     * @param array{failOn?:string,limitInputPixels?:int|false,autoOrient?:bool,animated?:bool,pages?:int,
     *              page?:int,density?:float,unlimited?:bool,ignoreIcc?:bool} $options
     */
    public static function fromFile(string $path, array $options = []): Image
    {
        return new Image(\pixelforge_from_file(
            $path,
            (string) ($options['failOn'] ?? 'warning'),
            self::limit($options),
            (bool) ($options['autoOrient'] ?? false),
            self::pages($options),
            (int) ($options['page'] ?? 0),
            (float) ($options['density'] ?? 0),
            (bool) ($options['unlimited'] ?? false),
            (bool) ($options['ignoreIcc'] ?? false)
        ));
    }

    /** Encoded bytes (or raw pixels with ['raw' => ['width','height','channels','depth'?]]). */
    public static function fromBuffer(string $data, array $options = []): Image
    {
        if (isset($options['raw'])) {
            return self::fromRaw($data, $options['raw']);
        }
        return new Image(\pixelforge_from_buffer(
            $data,
            (string) ($options['failOn'] ?? 'warning'),
            self::limit($options),
            (bool) ($options['autoOrient'] ?? false),
            self::pages($options),
            (int) ($options['page'] ?? 0),
            (float) ($options['density'] ?? 0),
            (bool) ($options['unlimited'] ?? false),
            (bool) ($options['ignoreIcc'] ?? false)
        ));
    }

    /** Uncompressed pixel data. @param array{width:int,height:int,channels:int,depth?:string,premultiplied?:bool} $raw */
    public static function fromRaw(string $data, array $raw): Image
    {
        return new Image(\pixelforge_from_raw(
            $data,
            (int) $raw['width'],
            (int) $raw['height'],
            (int) $raw['channels'],
            (string) ($raw['depth'] ?? 'uchar'),
            (bool) ($raw['premultiplied'] ?? false)
        ));
    }

    /**
     * New canvas. @param array{width:int,height:int,channels?:int,background?:mixed,
     *                          noise?:array{type:string,mean?:float,sigma?:float}} $options
     */
    public static function create(array $options): Image
    {
        $c = Color::parse($options['background'] ?? [0, 0, 0, 1]);
        $noise = $options['noise'] ?? [];
        return new Image(\pixelforge_create(
            (int) $options['width'],
            (int) $options['height'],
            (int) ($options['channels'] ?? 4),
            $c[0], $c[1], $c[2], $c[3],
            (string) ($noise['type'] ?? ''),
            (float) ($noise['mean'] ?? 128),
            (float) ($noise['sigma'] ?? 30)
        ));
    }

    /**
     * Render text (Pango markup supported).
     * @param array{text:string,font?:string,fontfile?:string,width?:int,height?:int,align?:string,
     *              justify?:bool,dpi?:int,rgba?:bool,spacing?:int,wrap?:string} $options
     */
    public static function text(array $options): Image
    {
        return new Image(\pixelforge_text(
            (string) $options['text'],
            (string) ($options['font'] ?? ''),
            (string) ($options['fontfile'] ?? ''),
            (int) ($options['width'] ?? 0),
            (int) ($options['height'] ?? 0),
            (string) ($options['align'] ?? 'left'),
            (bool) ($options['justify'] ?? false),
            (int) ($options['dpi'] ?? 0),
            (bool) ($options['rgba'] ?? false),
            (int) ($options['spacing'] ?? 0),
            (string) ($options['wrap'] ?? 'word')
        ));
    }

    /**
     * Join several inputs into one image: a grid, or the frames of an animation.
     * @param array<int, Image|string> $inputs
     * @param array{animated?:bool,across?:int,shim?:int,background?:mixed,halign?:string,valign?:string} $options
     */
    public static function join(array $inputs, array $options = []): Image
    {
        $bg = Color::parse($options['background'] ?? [0, 0, 0, 1]);
        $img = new Image(\pixelforge_join_new(
            (bool) ($options['animated'] ?? false),
            (int) ($options['across'] ?? 1),
            (int) ($options['shim'] ?? 0),
            $bg[0], $bg[1], $bg[2], $bg[3],
            (string) ($options['halign'] ?? 'left'),
            (string) ($options['valign'] ?? 'top')
        ));
        foreach ($inputs as $in) {
            \pixelforge_join_add($img->h, self::input($in)->handle());
        }
        return $img;
    }

    private static function input(mixed $in): Image
    {
        if ($in instanceof Image) {
            return $in;
        }
        if (is_array($in)) {
            if (isset($in['create'])) {
                return Image::create($in['create']);
            }
            if (isset($in['text'])) {
                return Image::text($in['text']);
            }
            if (isset($in['raw'])) {
                return Image::fromRaw((string) $in['input'], $in['raw']);
            }
        }
        $s = (string) $in;
        // short strings that exist on disk are paths, everything else is encoded bytes
        if (strlen($s) < 4096 && !str_contains($s, "\0") && is_file($s)) {
            return Image::fromFile($s);
        }
        return Image::fromBuffer($s);
    }

    private static function limit(array $options): int
    {
        $limit = $options['limitInputPixels'] ?? 268402689;
        if ($limit === false) {
            return 0;
        }
        return (int) $limit;
    }

    private static function pages(array $options): int
    {
        if (!empty($options['animated'])) {
            return -1;
        }
        return (int) ($options['pages'] ?? 1);
    }

    /** Independent copy of the pipeline (source is shared, not copied). */
    public function clone(): Image
    {
        $img = new Image(\pixelforge_clone($this->h));
        $img->keepFlags = $this->keepFlags;
        return $img;
    }

    public function handle(): mixed
    {
        return $this->h;
    }

    // ------------------------------------------------------------ geometry

    /**
     * @param array{fit?:string,position?:string,gravity?:string,background?:mixed,
     *              withoutEnlargement?:bool,withoutReduction?:bool,width?:int,height?:int} $options
     */
    public function resize(?int $width = null, ?int $height = null, array $options = []): Image
    {
        $w = $width ?? (int) ($options['width'] ?? 0);
        $h = $height ?? (int) ($options['height'] ?? 0);
        $bg = Color::parse($options['background'] ?? [0, 0, 0, 1]);
        $pos = $options['position'] ?? ($options['gravity'] ?? 'centre');
        \pixelforge_resize(
            $this->h, $w, $h,
            (string) ($options['fit'] ?? 'cover'),
            Gravity::normalise((string) $pos),
            $bg[0], $bg[1], $bg[2], $bg[3],
            (bool) ($options['withoutEnlargement'] ?? false),
            (bool) ($options['withoutReduction'] ?? false),
            (string) ($options['kernel'] ?? 'lanczos3'),
            (bool) ($options['fastShrinkOnLoad'] ?? true)
        );
        return $this;
    }

    /** Crop. @param array{left:int,top:int,width:int,height:int} $region */
    public function extract(array $region): Image
    {
        \pixelforge_extract($this->h, (int) $region['left'], (int) $region['top'], (int) $region['width'], (int) $region['height']);
        return $this;
    }

    /** @param int|array{top?:int,bottom?:int,left?:int,right?:int,extendWith?:string,background?:mixed} $extend */
    public function extend(int|array $extend): Image
    {
        if (is_int($extend)) {
            $extend = ['top' => $extend, 'bottom' => $extend, 'left' => $extend, 'right' => $extend];
        }
        $bg = Color::parse($extend['background'] ?? [0, 0, 0, 1]);
        \pixelforge_extend(
            $this->h,
            (int) ($extend['top'] ?? 0), (int) ($extend['bottom'] ?? 0),
            (int) ($extend['left'] ?? 0), (int) ($extend['right'] ?? 0),
            (string) ($extend['extendWith'] ?? 'background'),
            $bg[0], $bg[1], $bg[2], $bg[3]
        );
        return $this;
    }

    /** @param array{threshold?:float,background?:mixed,lineArt?:bool} $options */
    public function trim(array $options = []): Image
    {
        $useBg = isset($options['background']);
        $bg = Color::parse($options['background'] ?? [0, 0, 0, 1]);
        \pixelforge_trim($this->h, (float) ($options['threshold'] ?? 10), $useBg, $bg[0], $bg[1], $bg[2], (bool) ($options['lineArt'] ?? false));
        return $this;
    }

    /** rotate() with no angle = auto-orient from EXIF (like sharp). */
    public function rotate(?float $angle = null, array $options = []): Image
    {
        if ($angle === null) {
            return $this->autoOrient();
        }
        $bg = Color::parse($options['background'] ?? [0, 0, 0, 1]);
        \pixelforge_rotate($this->h, $angle, $bg[0], $bg[1], $bg[2], $bg[3]);
        return $this;
    }

    public function autoOrient(): Image
    {
        \pixelforge_auto_orient($this->h);
        return $this;
    }

    public function flip(): Image
    {
        \pixelforge_flip($this->h);
        return $this;
    }

    public function flop(): Image
    {
        \pixelforge_flop($this->h);
        return $this;
    }

    /** @param array{0:float,1:float,2:float,3:float} $matrix 2x2 matrix [a,b,c,d] */
    public function affine(array $matrix, array $options = []): Image
    {
        $bg = Color::parse($options['background'] ?? [0, 0, 0, 1]);
        \pixelforge_affine(
            $this->h,
            (float) $matrix[0], (float) $matrix[1], (float) $matrix[2], (float) $matrix[3],
            $bg[0], $bg[1], $bg[2], $bg[3],
            (string) ($options['interpolator'] ?? 'bicubic'),
            (float) ($options['idx'] ?? 0), (float) ($options['idy'] ?? 0),
            (float) ($options['odx'] ?? 0), (float) ($options['ody'] ?? 0)
        );
        return $this;
    }

    // ------------------------------------------------------------ operations

    /** @param array{sigma?:float,m1?:float,m2?:float,x1?:float,y2?:float,y3?:float} $options */
    public function sharpen(array $options = []): Image
    {
        \pixelforge_sharpen(
            $this->h,
            (float) ($options['sigma'] ?? 0),
            (float) ($options['m1'] ?? 1.0),
            (float) ($options['m2'] ?? 2.0),
            (float) ($options['x1'] ?? 2.0),
            (float) ($options['y2'] ?? 10.0),
            (float) ($options['y3'] ?? 20.0)
        );
        return $this;
    }

    public function median(int $size = 3): Image
    {
        \pixelforge_median($this->h, $size);
        return $this;
    }

    /** @param float|array{sigma:float,precision?:string,minAmplitude?:float} $sigma */
    public function blur(float|array $sigma = 0.0): Image
    {
        $o = is_array($sigma) ? $sigma : ['sigma' => $sigma];
        \pixelforge_blur($this->h, (float) ($o['sigma'] ?? 0), (string) ($o['precision'] ?? 'integer'), (float) ($o['minAmplitude'] ?? 0.2));
        return $this;
    }

    public function flatten(array $options = []): Image
    {
        $bg = Color::parse($options['background'] ?? [0, 0, 0, 1]);
        \pixelforge_flatten($this->h, $bg[0], $bg[1], $bg[2]);
        return $this;
    }

    public function unflatten(): Image
    {
        \pixelforge_unflatten($this->h);
        return $this;
    }

    public function gamma(float $gamma = 2.2, ?float $gammaOut = null): Image
    {
        \pixelforge_gamma($this->h, $gamma, $gammaOut ?? $gamma);
        return $this;
    }

    public function negate(array $options = []): Image
    {
        \pixelforge_negate($this->h, (bool) ($options['alpha'] ?? true));
        return $this;
    }

    public function normalise(array $options = []): Image
    {
        \pixelforge_normalise($this->h, (float) ($options['lower'] ?? 1), (float) ($options['upper'] ?? 99));
        return $this;
    }

    public function normalize(array $options = []): Image
    {
        return $this->normalise($options);
    }

    /** @param array{width:int,height:int,maxSlope?:int} $options */
    public function clahe(array $options): Image
    {
        \pixelforge_clahe($this->h, (int) $options['width'], (int) $options['height'], (int) ($options['maxSlope'] ?? 3));
        return $this;
    }

    public function threshold(int $threshold = 128, array $options = []): Image
    {
        $grey = (bool) ($options['greyscale'] ?? ($options['grayscale'] ?? true));
        \pixelforge_threshold($this->h, $threshold, $grey);
        return $this;
    }

    /** @param float|float[] $a @param float|float[] $b */
    public function linear(float|array $a = 1.0, float|array $b = 0.0): Image
    {
        \pixelforge_linear($this->h, self::csv($a), self::csv($b));
        return $this;
    }

    /** @param array{brightness?:float,saturation?:float,hue?:float,lightness?:float} $options */
    public function modulate(array $options): Image
    {
        \pixelforge_modulate(
            $this->h,
            (float) ($options['brightness'] ?? 1),
            (float) ($options['saturation'] ?? 1),
            (float) ($options['hue'] ?? 0),
            (float) ($options['lightness'] ?? 0)
        );
        return $this;
    }

    public function tint(mixed $color): Image
    {
        $c = Color::parse($color);
        \pixelforge_tint($this->h, $c[0], $c[1], $c[2]);
        return $this;
    }

    public function greyscale(bool $grey = true): Image
    {
        if ($grey) {
            \pixelforge_colourspace($this->h, 'b-w');
        }
        return $this;
    }

    public function grayscale(bool $grey = true): Image
    {
        return $this->greyscale($grey);
    }

    public function toColourspace(string $space): Image
    {
        \pixelforge_colourspace($this->h, $space);
        return $this;
    }

    public function toColorspace(string $space): Image
    {
        return $this->toColourspace($space);
    }

    public function removeAlpha(): Image
    {
        \pixelforge_remove_alpha($this->h);
        return $this;
    }

    public function ensureAlpha(float $alpha = 1.0): Image
    {
        \pixelforge_ensure_alpha($this->h, $alpha);
        return $this;
    }

    public function extractChannel(int|string $channel): Image
    {
        if (is_string($channel)) {
            $map = ['red' => 0, 'green' => 1, 'blue' => 2, 'alpha' => 3];
            if (!isset($map[$channel])) {
                throw new \InvalidArgumentException('Invalid channel: ' . $channel);
            }
            $channel = $map[$channel];
        }
        \pixelforge_extract_channel($this->h, $channel);
        return $this;
    }

    /** Append channels from another image (Image, path or bytes). */
    public function joinChannel(mixed $images): Image
    {
        $list = is_array($images) && !isset($images['create']) && !isset($images['text']) ? $images : [$images];
        foreach ($list as $img) {
            \pixelforge_join_channel($this->h, self::input($img)->handle());
        }
        return $this;
    }

    /** Reduce all channels to one with a bitwise op: and | or | eor. */
    public function bandbool(string $op): Image
    {
        \pixelforge_bandbool($this->h, $op);
        return $this;
    }

    /** Bitwise op with another image: and | or | eor. */
    public function boolean(mixed $operand, string $op): Image
    {
        \pixelforge_boolean($this->h, self::input($operand)->handle(), $op);
        return $this;
    }

    public function dilate(int $width = 1): Image
    {
        \pixelforge_dilate($this->h, $width);
        return $this;
    }

    public function erode(int $width = 1): Image
    {
        \pixelforge_erode($this->h, $width);
        return $this;
    }

    /** @param array{width:int,height:int,kernel:float[],scale?:float,offset?:float} $kernel */
    public function convolve(array $kernel): Image
    {
        \pixelforge_convolve(
            $this->h,
            (int) $kernel['width'],
            (int) $kernel['height'],
            self::csv($kernel['kernel']),
            (float) ($kernel['scale'] ?? 0),
            (float) ($kernel['offset'] ?? 0)
        );
        return $this;
    }

    /** @param float[][] $matrix 3x3 or 4x4 */
    public function recomb(array $matrix): Image
    {
        $flat = [];
        foreach ($matrix as $row) {
            foreach ($row as $v) {
                $flat[] = (float) $v;
            }
        }
        \pixelforge_recomb($this->h, self::csv($flat));
        return $this;
    }

    /**
     * Overlay one or more images.
     * @param array<int, array{input:mixed,gravity?:string,left?:int,top?:int,blend?:string,tile?:bool,premultiplied?:bool}> $layers
     *        `input`: Image, file path, encoded bytes, ['create' => [...]], ['text' => [...]].
     */
    public function composite(array $layers): Image
    {
        foreach ($layers as $layer) {
            $input = self::input($layer['input']);
            $hasPos = isset($layer['left']) && isset($layer['top']);
            \pixelforge_composite(
                $this->h,
                $input->handle(),
                Gravity::normalise((string) ($layer['gravity'] ?? 'centre')),
                $hasPos ? (int) $layer['left'] : -2147483648,
                $hasPos ? (int) $layer['top'] : -2147483648,
                (string) ($layer['blend'] ?? 'over'),
                (bool) ($layer['tile'] ?? false),
                (bool) ($layer['premultiplied'] ?? false)
            );
        }
        return $this;
    }

    // ------------------------------------------------------------ output format

    public function jpeg(array $o = []): Image
    {
        return $this->output('jpeg', $o);
    }

    public function png(array $o = []): Image
    {
        return $this->output('png', $o);
    }

    public function webp(array $o = []): Image
    {
        return $this->output('webp', $o);
    }

    public function avif(array $o = []): Image
    {
        return $this->output('avif', $o);
    }

    public function heif(array $o = []): Image
    {
        return $this->output('heif', $o);
    }

    public function gif(array $o = []): Image
    {
        return $this->output('gif', $o);
    }

    public function tiff(array $o = []): Image
    {
        return $this->output('tiff', $o);
    }

    public function jxl(array $o = []): Image
    {
        return $this->output('jxl', $o);
    }

    public function raw(): Image
    {
        return $this->output('raw', []);
    }

    public function toFormat(string $format, array $o = []): Image
    {
        return $this->output($format, $o);
    }

    private function output(string $format, array $o): Image
    {
        \pixelforge_output(
            $this->h,
            $format,
            (int) ($o['quality'] ?? -1),
            (bool) ($o['lossless'] ?? false),
            (int) ($o['effort'] ?? -1),
            (bool) ($o['progressive'] ?? ($o['interlace'] ?? false)),
            (string) ($o['chromaSubsampling'] ?? ''),
            (bool) ($o['mozjpeg'] ?? false),
            (int) ($o['compressionLevel'] ?? 6),
            (bool) ($o['palette'] ?? (isset($o['colours']) || isset($o['colors']))),
            (int) ($o['colours'] ?? ($o['colors'] ?? 256)),
            (float) ($o['dither'] ?? 1.0),
            (bool) ($o['adaptiveFiltering'] ?? false),
            isset($o['nearLossless']) ? ($o['nearLossless'] === true ? 60 : (int) $o['nearLossless']) : -1,
            (bool) ($o['smartSubsample'] ?? false),
            (int) ($o['alphaQuality'] ?? 100),
            (int) ($o['bitdepth'] ?? 8),
            (string) ($o['compression'] ?? ''),
            (string) ($o['predictor'] ?? ''),
            (bool) ($o['tile'] ?? false),
            (int) ($o['tileWidth'] ?? 256),
            (int) ($o['tileHeight'] ?? 256),
            (bool) ($o['pyramid'] ?? false),
            (int) ($o['loop'] ?? -1),
            self::csv($o['delay'] ?? []),
            (bool) ($o['minSize'] ?? false),
            (bool) ($o['mixed'] ?? false),
            (float) ($o['interFrameMaxError'] ?? 0),
            (float) ($o['interPaletteMaxError'] ?? 3),
            (bool) ($o['reuse'] ?? false),
            (bool) ($o['optimiseCoding'] ?? ($o['optimizeCoding'] ?? true))
        );
        return $this;
    }

    /**
     * Deep Zoom / Zoomify / Google / IIIF tile pyramid (toFile('out.dz' | 'out.zip')).
     * @param array{size?:int,overlap?:int,angle?:int,layout?:string,container?:string,depth?:string,
     *              skipBlanks?:int|bool,centre?:bool,basename?:string,id?:string,background?:mixed} $o
     */
    public function tile(array $o = []): Image
    {
        $bg = Color::parse($o['background'] ?? '#ffffff');
        \pixelforge_tile(
            $this->h,
            (int) ($o['size'] ?? 256),
            (int) ($o['overlap'] ?? 0),
            (int) ($o['angle'] ?? 0),
            (string) ($o['layout'] ?? 'dz'),
            (string) ($o['container'] ?? 'fs'),
            (string) ($o['depth'] ?? ''),
            (bool) ($o['skipBlanks'] ?? false),
            (bool) ($o['centre'] ?? ($o['center'] ?? false)),
            (string) ($o['basename'] ?? ''),
            (string) ($o['id'] ?? ''),
            $bg[0], $bg[1], $bg[2], $bg[3]
        );
        return $this;
    }

    /** Abort processing after $seconds (throws PixelForgeException). */
    public function timeout(array $o): Image
    {
        \pixelforge_timeout($this->h, (float) ($o['seconds'] ?? 0));
        return $this;
    }

    // ------------------------------------------------------------ metadata retention

    /** Keep all metadata (EXIF, XMP, IPTC, ICC). Default strips everything, like sharp. */
    public function keepMetadata(): Image
    {
        return $this->keep(self::KEEP_ALL);
    }

    public function withMetadata(): Image
    {
        return $this->keepMetadata();
    }

    public function keepExif(): Image
    {
        return $this->keep($this->keepFlags | self::KEEP_EXIF);
    }

    public function keepIccProfile(): Image
    {
        return $this->keep($this->keepFlags | self::KEEP_ICC);
    }

    /** Convert to and embed an output ICC profile: 'srgb', 'p3', 'cmyk' or a file path. */
    public function withIccProfile(string $profile): Image
    {
        \pixelforge_icc($this->h, $profile);
        return $this;
    }

    /** Replace EXIF. @param array<string, array<string,string>> $exif e.g. ['IFD0' => ['Copyright' => 'me']] */
    public function withExif(array $exif): Image
    {
        \pixelforge_exif($this->h, self::flattenExif($exif), false);
        return $this;
    }

    /** Merge into existing EXIF. */
    public function withExifMerge(array $exif): Image
    {
        \pixelforge_exif($this->h, self::flattenExif($exif), true);
        return $this;
    }

    private static function flattenExif(array $exif): string
    {
        $out = [];
        foreach ($exif as $ifd => $tags) {
            foreach ($tags as $tag => $value) {
                $out[] = $ifd . "\x1f" . $tag . "\x1f" . $value;
            }
        }
        return implode("\x1e", $out);
    }

    public function keepXmp(): Image
    {
        return $this->keep($this->keepFlags | self::KEEP_XMP);
    }

    private function keep(int $flags): Image
    {
        $this->keepFlags = $flags;
        \pixelforge_keep($this->h, $flags);
        return $this;
    }

    // ------------------------------------------------------------ sinks

    /** @return array{format:string,width:int,height:int,channels:int,size:int} */
    public function toFile(string $path): array
    {
        return \pixelforge_to_file($this->h, $path);
    }

    /** Encoded bytes. Format defaults to the configured output format, else the input format. */
    public function toBuffer(?string $format = null): string
    {
        $r = \pixelforge_to_buffer($this->h, $format ?? '');
        return $r['data'];
    }

    /** @return array{data:string,info:array} */
    public function toBufferWithInfo(?string $format = null): array
    {
        return \pixelforge_to_buffer($this->h, $format ?? '');
    }

    /** Header-only metadata of the input (does not decode pixels). */
    public function metadata(): array
    {
        return \pixelforge_metadata($this->h);
    }

    /** Per-channel statistics of the processed image. */
    public function stats(): array
    {
        return \pixelforge_stats($this->h);
    }

    // ------------------------------------------------------------ helpers

    private static function csv(mixed $v): string
    {
        if (is_array($v)) {
            $parts = [];
            foreach ($v as $x) {
                $parts[] = (string) (float) $x;
            }
            return implode(',', $parts);
        }
        return (string) (float) $v;
    }
}

final class Gravity
{
    public static function normalise(string $g): string
    {
        $g = strtolower(trim($g));
        $map = [
            'center' => 'centre', 'centre' => 'centre',
            'top' => 'north', 'right top' => 'northeast', 'top right' => 'northeast',
            'right' => 'east', 'right bottom' => 'southeast', 'bottom right' => 'southeast',
            'bottom' => 'south', 'left bottom' => 'southwest', 'bottom left' => 'southwest',
            'left' => 'west', 'left top' => 'northwest', 'top left' => 'northwest',
        ];
        return $map[$g] ?? $g;
    }
}

final class Color
{
    /**
     * Accepts '#rgb', '#rrggbb', '#rrggbbaa', 'transparent', 'white', 'black',
     * [r,g,b] or [r,g,b,alpha 0..1] or ['r'=>..,'g'=>..,'b'=>..,'alpha'=>..].
     * @return float[] r,g,b,a in 0..255
     */
    public static function parse(mixed $c): array
    {
        if (is_array($c)) {
            $r = (float) ($c['r'] ?? ($c[0] ?? 0));
            $g = (float) ($c['g'] ?? ($c[1] ?? 0));
            $b = (float) ($c['b'] ?? ($c[2] ?? 0));
            $a = (float) ($c['alpha'] ?? ($c[3] ?? 1));
            return [$r, $g, $b, $a * 255.0];
        }
        $s = strtolower(trim((string) $c));
        if ($s === 'transparent') {
            return [0.0, 0.0, 0.0, 0.0];
        }
        if ($s === 'white') {
            return [255.0, 255.0, 255.0, 255.0];
        }
        if ($s === 'black') {
            return [0.0, 0.0, 0.0, 255.0];
        }
        if (str_starts_with($s, '#')) {
            $s = substr($s, 1);
        }
        if (strlen($s) === 3 || strlen($s) === 4) {
            $e = '';
            for ($i = 0; $i < strlen($s); $i++) {
                $e .= $s[$i] . $s[$i];
            }
            $s = $e;
        }
        if (strlen($s) !== 6 && strlen($s) !== 8) {
            throw new \InvalidArgumentException('Invalid colour: ' . (string) $c);
        }
        $a = strlen($s) === 8 ? (float) hexdec(substr($s, 6, 2)) : 255.0;
        return [(float) hexdec(substr($s, 0, 2)), (float) hexdec(substr($s, 2, 2)), (float) hexdec(substr($s, 4, 2)), $a];
    }
}

final class PixelForge
{
    /** Number of libvips worker threads per image (0 = number of CPU cores). */
    public static function concurrency(?int $n = null): int
    {
        if ($n !== null) {
            \pixelforge_concurrency($n);
        }
        return \pixelforge_get_concurrency();
    }

    /** libvips operation cache. Disabled by default for the lowest memory footprint. */
    public static function cache(int $memoryMb = 50, int $files = 20, int $items = 100): void
    {
        \pixelforge_cache($memoryMb, $files, $items);
    }

    public static function versions(): array
    {
        return \pixelforge_versions();
    }

    public static function format(): array
    {
        return \pixelforge_formats();
    }

    /** libvips tracked memory counters (bytes). */
    public static function memory(): array
    {
        return \pixelforge_memory();
    }
}
