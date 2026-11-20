#!/usr/bin/env bash
# Run TypePHP on project.yml and assemble generated/ + deps/phpx/ into OUT.
#   scripts/assemble-generated.sh <typephp checkout> <project dir> <out dir> <typephp ref>
# Used by the Dockerfile "generate" stage and by scripts/generate.sh --native.
set -euo pipefail
TP=$1; SRC=$2; OUT=$3; REF=${4:-unknown}
GEN=$(mktemp -d)
( cd "$SRC" && php "$TP/bin/tpc.php" project.yml --dry --build-dir "$GEN" --no-progress --no-color -o pixelforge.so )
mkdir -p "$OUT/generated/include"
# every C++ file TypePHP emitted (extension entry, one per PHP source, init/ helpers such as class constants)
find "$GEN" -name '*.cc' -not -path "$GEN/cache/*" | while read -r f; do
  name=$(basename "$f")
  [ -e "$OUT/generated/$name" ] && { echo "duplicate generated file name: $name" >&2; exit 1; }
  cp "$f" "$OUT/generated/$name"
done
cp "$GEN"/include/*.h "$OUT/generated/include/"
# module name: "pixelforge" instead of TypePHP's "typephp_pixelforge"
for f in "$OUT"/generated/*.cc "$OUT"/generated/include/*.h; do
  sed 's/typephp_pixelforge/pixelforge/g' "$f" > "$f.tmp" && mv "$f.tmp" "$f"
done
# vendored PHPX runtime (Apache-2.0): only what the extension links
P=$TP/vendor/swoole/phpx; D=$OUT/deps/phpx
mkdir -p "$D/src" "$D/thirdparty/mpdecimal/libmpdec" "$D/thirdparty/mpdecimal/libmpdec++" "$D/thirdparty/wren-gc"
cp "$P/LICENSE" "$D/"; cp -R "$P/include" "$D/"
for d in core std typephp; do cp -R "$P/src/$d" "$D/src/"; done
find "$D/src" -name '*_nano.cc' -delete
cp "$P/thirdparty/mpdecimal/COPYRIGHT.txt" "$D/thirdparty/mpdecimal/"
cp "$P"/thirdparty/mpdecimal/libmpdec/*.c "$P"/thirdparty/mpdecimal/libmpdec/*.h "$D/thirdparty/mpdecimal/libmpdec/"
rm -f "$D"/thirdparty/mpdecimal/libmpdec/bench*.c
# the CMake build normally configures this header; 64-bit config
sed 's/@MPD_HEADER_CONFIG@/#define MPD_CONFIG_64 1/' "$P/thirdparty/mpdecimal/libmpdec/mpdecimal.h.in" > "$D/thirdparty/mpdecimal/libmpdec/mpdecimal.h"
cp "$P/thirdparty/mpdecimal/libmpdec++/decimal.cc" "$P/thirdparty/mpdecimal/libmpdec++/decimal.hh" "$D/thirdparty/mpdecimal/libmpdec++/"
cp -R "$P/thirdparty/wren-gc/src" "$P/thirdparty/wren-gc/include" "$D/thirdparty/wren-gc/"
cp "$P"/thirdparty/wren-gc/LICENSE* "$D/thirdparty/wren-gc/" 2>/dev/null || true
php -r 'foreach (json_decode(file_get_contents($argv[1]), true)["packages"] as $p) if ($p["name"] === "swoole/phpx") echo "phpx ", $p["version"], "\n";' "$TP/vendor/composer/installed.json" > "$D/VERSION"
echo "typephp $REF" >> "$D/VERSION"
rm -rf "$GEN"
