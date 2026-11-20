#!/usr/bin/env bash
# Install the prebuilt libvips bundle used by Node's sharp (@img/sharp-libvips) into PREFIX.
# It is a single self-contained shared library (mozjpeg, zlib-ng, libwebp, libheif+aom, highway...).
#
#   sudo scripts/install-libvips.sh /opt/sharp-libvips
#   pie install nguyenthuan2412/pixelforge --with-pixelforge-vips=/opt/sharp-libvips
#   # or: pecl install -D 'with-pixelforge-vips="/opt/sharp-libvips"' pixelforge-X.Y.Z.tgz
set -euo pipefail
PREFIX=${1:-/opt/sharp-libvips}
VERSION=${SHARP_LIBVIPS_VERSION:-1.3.4}
sha_for() {
  case "$1" in
    dev)             echo s1VIq6p83pWGi1hk7VLdfRiI6DUolGYqbpCNu4zdEIbKjlbdR9zHFpIiY6wQtnbn5jSfu9+E/PSC26tkONer2Q== ;;
    linux-arm64)     echo Y3dgX/6lE2QhQb+Gxy0WZxfg9MEm/JBjamZpS2IklP7xIQoKN4hzAm7KcMVGtaVDt3neE9OKBC7vAfonA/Lr1A== ;;
    linux-x64)       echo GJ//SSXbnwSDes02umB3nDJLFcQzw8a18V8fyhqr6tV515tOEMdImjjxj1AoafMRz56F3PHgftnj1QEKSU1zkw== ;;
    linuxmusl-arm64) echo hvulFwtjUcagsis6BBxHwGFwWoNZjgYmULGVrZcyfNbjA8hKILbRxGg15/7w5HDyXHXUos/j6baAWqnCyQ2DWA== ;;
    linuxmusl-x64)   echo 6zXKeE/p39I1AmA3cJG35eyBGNqNddLnUXjhwBnsGjFPWqf5VKkDBEqaEkPDoTEtkxwi2vv8Tcr2mDyP4So7Fg== ;;
    darwin-arm64)    echo 5R89nBYiRdUlSWJxPhO+GVtaXzXSxKnRu/xqMn3KTA3L9EB9Oy/P+Nn2f2vlhPuUdy/Zusb2DarbyTpGCfEDuw== ;;
    darwin-x64)      echo iR2OKH80yi0U+dUplyh3/xdpFvps6YkCwsXenIJxqxR1v9o+xtKTGbS9H7cps+2Vxjc8B1j96p75NmTGjIhtpQ== ;;
  esac
}
os=$(uname -s); arch=$(uname -m)
case "$arch" in x86_64|amd64) arch=x64 ;; aarch64|arm64) arch=arm64 ;; *) echo "unsupported arch $arch" >&2; exit 1 ;; esac
case "$os" in
  Linux)  if ldd --version 2>&1 | grep -qi musl; then plat=linuxmusl-$arch; else plat=linux-$arch; fi ;;
  Darwin) plat=darwin-$arch ;;
  *) echo "unsupported OS $os" >&2; exit 1 ;;
esac
[ "$VERSION" = 1.3.4 ] || { echo "hashes are pinned for 1.3.4" >&2; exit 1; }
tmp=$(mktemp -d); trap 'rm -rf "$tmp"' EXIT
fetch() {
  curl -fsSL "https://registry.npmjs.org/@img/sharp-libvips-$1/-/sharp-libvips-$1-$VERSION.tgz" -o "$tmp/$1.tgz"
  got=$(openssl dgst -sha512 -binary "$tmp/$1.tgz" | openssl base64 -A)
  [ "$got" = "$(sha_for "$1")" ] || { echo "checksum mismatch for $1" >&2; exit 1; }
  mkdir -p "$tmp/$1" && tar xzf "$tmp/$1.tgz" -C "$tmp/$1"
}
fetch dev; fetch "$plat"
mkdir -p "$PREFIX/lib/pkgconfig" "$PREFIX/include"
cp -R "$tmp/dev/package/include/." "$PREFIX/include/"
cp -R "$tmp/$plat/package/lib/." "$PREFIX/lib/"
rm -f "$PREFIX/lib/index.js"
cd "$PREFIX/lib"
if [ "$os" = Darwin ]; then
  so=$(ls libvips-cpp.*.dylib | head -1); ln -sf "$so" libvips-cpp.dylib
  install_name_tool -id "$PREFIX/lib/$so" "$so" 2>/dev/null || true
else
  so=$(ls libvips-cpp.so.* | head -1); ln -sf "$so" libvips-cpp.so
fi
ver=$(echo "$so" | sed -E 's/^libvips-cpp\.(so\.)?([0-9.]+[0-9])(\.dylib)?$/\2/')
cat > "$PREFIX/lib/pkgconfig/vips-cpp.pc" <<PC
prefix=$PREFIX
Name: vips-cpp
Description: libvips prebuilt bundle (@img/sharp-libvips $VERSION, $plat)
Version: $ver
Cflags: -I\${prefix}/include -I\${prefix}/include/glib-2.0 -I\${prefix}/lib/glib-2.0/include
Libs: -L\${prefix}/lib -lvips-cpp
PC
echo "libvips $ver ($plat) installed in $PREFIX"
