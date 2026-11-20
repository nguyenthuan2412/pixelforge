# syntax=docker/dockerfile:1
# pixelforge: libvips image processing extension for PHP (TypePHP-generated C++, built with phpize).
#
#   docker build -t pixelforge .                                  # sharp's prebuilt libvips (fastest, default)
#   docker build --build-arg VIPS_FLAVOR=source -t pixelforge .   # libvips from source + Debian libs (adds JPEG XL)
#   docker build --build-arg PHP_VARIANT=fpm -t pixelforge:fpm .
#   docker build --build-arg PHP_VERSION=8.4 -t pixelforge:8.4 .
#   docker build --target artifacts -o out .                      # pixelforge.so + libvips
#   docker build --target generated -o . .                        # regenerate generated/ + deps/phpx (scripts/generate.sh)
ARG PHP_VERSION=8.5
ARG DEBIAN=trixie
# cli | fpm (both share the NTS ABI of the build stage)
ARG PHP_VARIANT=cli
# prebuilt | source
ARG VIPS_FLAVOR=prebuilt

# ---------------------------------------------------------------- libvips: sharp's prebuilt bundle
# Same binary Node's sharp 0.35.5 ships: libvips 8.18.7 statically linked with mozjpeg, zlib-ng,
# libpng 1.6.58, libwebp 1.6, libheif 1.23.5 + aom 3.15, highway 1.4, lcms 2.19, cgif, imagequant,
# librsvg, pango/cairo (text), libarchive (zip tiles), libuhdr. Single .so, depends on libc only.
FROM php:${PHP_VERSION}-cli-${DEBIAN} AS vips-prebuilt
ARG TARGETARCH
ARG PIXELFORGE_LIBVIPS=1.3.4
ARG SHA_DEV=s1VIq6p83pWGi1hk7VLdfRiI6DUolGYqbpCNu4zdEIbKjlbdR9zHFpIiY6wQtnbn5jSfu9+E/PSC26tkONer2Q==
ARG SHA_ARM64=Y3dgX/6lE2QhQb+Gxy0WZxfg9MEm/JBjamZpS2IklP7xIQoKN4hzAm7KcMVGtaVDt3neE9OKBC7vAfonA/Lr1A==
ARG SHA_X64=GJ//SSXbnwSDes02umB3nDJLFcQzw8a18V8fyhqr6tV515tOEMdImjjxj1AoafMRz56F3PHgftnj1QEKSU1zkw==
RUN apt-get update && apt-get install -y --no-install-recommends build-essential pkg-config ca-certificates curl \
    && rm -rf /var/lib/apt/lists/*
RUN set -eux; \
    case "${TARGETARCH:-$(dpkg --print-architecture)}" in \
      arm64) plat=linux-arm64; sha="$SHA_ARM64" ;; \
      amd64) plat=linux-x64;  sha="$SHA_X64" ;; \
      *) echo "unsupported arch" >&2; exit 1 ;; \
    esac; \
    fetch() { \
      curl -fsSL "https://registry.npmjs.org/@img/sharp-libvips-$1/-/sharp-libvips-$1-${PIXELFORGE_LIBVIPS}.tgz" -o /tmp/$1.tgz; \
      test "$(openssl dgst -sha512 -binary /tmp/$1.tgz | base64 -w0)" = "$2"; \
      mkdir -p /tmp/$1 && tar xzf /tmp/$1.tgz -C /tmp/$1; \
    }; \
    fetch dev "$SHA_DEV"; fetch "$plat" "$sha"; \
    mkdir -p /opt/vips/lib/pkgconfig; \
    cp -r /tmp/dev/package/include /opt/vips/include; \
    cp -r /tmp/$plat/package/lib/* /opt/vips/lib/; \
    cp /tmp/$plat/package/versions.json /opt/vips/versions.json; \
    so=$(basename /opt/vips/lib/libvips-cpp.so.*); \
    ln -s "$so" /opt/vips/lib/libvips-cpp.so; \
    printf '%s\n' 'prefix=/opt/vips' 'Name: vips-cpp' 'Description: sharp prebuilt libvips' "Version: ${so#libvips-cpp.so.}" \
      'Cflags: -I${prefix}/include -I${prefix}/include/glib-2.0 -I${prefix}/lib/glib-2.0/include' \
      'Libs: -L${prefix}/lib -lvips-cpp' > /opt/vips/lib/pkgconfig/vips-cpp.pc; \
    echo /opt/vips/lib > /etc/ld.so.conf.d/000-vips.conf; ldconfig; \
    rm -rf /tmp/*
ENV PKG_CONFIG_PATH=/opt/vips/lib/pkgconfig

# ---------------------------------------------------------------- libvips: from source (Debian libs)
FROM php:${PHP_VERSION}-cli-${DEBIAN} AS vips-source
ARG VIPS_VERSION=8.18.7
RUN apt-get update && apt-get install -y --no-install-recommends \
      build-essential meson ninja-build pkg-config ca-certificates curl xz-utils \
      libglib2.0-dev libexpat1-dev \
      libjpeg62-turbo-dev libpng-dev libwebp-dev libtiff-dev libcgif-dev \
      libheif-dev libheif-plugin-aomenc libheif-plugin-dav1d libheif-plugin-libde265 libheif-plugin-x265 \
      libjxl-dev librsvg2-dev libexif-dev liblcms2-dev libimagequant-dev libhwy-dev libarchive-dev \
      libpango1.0-dev \
    && rm -rf /var/lib/apt/lists/*
RUN curl -fsSL https://github.com/libvips/libvips/releases/download/v${VIPS_VERSION}/vips-${VIPS_VERSION}.tar.xz \
      | tar xJ -C /tmp \
    && cd /tmp/vips-${VIPS_VERSION} \
    && meson setup build --prefix=/opt/vips --libdir=lib --buildtype=release \
         -Dintrospection=disabled -Dmodules=disabled -Dcplusplus=true \
         -Ddeprecated=false -Dexamples=false -Dpoppler=disabled -Dmagick=disabled \
         -Dopenslide=disabled -Dmatio=disabled -Dcfitsio=disabled -Dnifti=disabled \
         -Dopenexr=disabled -Dfftw=disabled -Dorc=disabled \
    && meson compile -C build && meson install -C build \
    && echo /opt/vips/lib > /etc/ld.so.conf.d/000-vips.conf && ldconfig \
    && rm -rf /tmp/vips-*
ENV PKG_CONFIG_PATH=/opt/vips/lib/pkgconfig

FROM vips-${VIPS_FLAVOR} AS vips

# ---------------------------------------------------------------- TypePHP toolchain (code generation only)
FROM php:8.5-cli-${DEBIAN} AS typephp
ARG TYPEPHP_REF=cddd025baa369b54937a5472ce0d94f467475dae
RUN apt-get update && apt-get install -y --no-install-recommends \
      build-essential cmake git unzip ca-certificates libgmp-dev libmpfr-dev \
    && rm -rf /var/lib/apt/lists/*
COPY --from=composer:2 /usr/bin/composer /usr/bin/composer
RUN git clone https://github.com/swoole/typephp.git /opt/typephp \
    && cd /opt/typephp && git checkout ${TYPEPHP_REF} \
    && composer install --no-dev --no-interaction --prefer-dist \
    && cd vendor/swoole/phpx \
    && cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -Dphp_dir=/usr/local \
    && cmake --build build --parallel "$(nproc)" --target phpx
ENV PATH=/opt/typephp/bin:$PATH

FROM typephp AS generate
COPY project.yml /src/pixelforge/project.yml
COPY src /src/pixelforge/src
RUN set -eux; cd /src/pixelforge; \
    tpc.php project.yml --dry --build-dir /tmp/gen --no-progress --no-color -o pixelforge.so; \
    mkdir -p /out/generated/include; \
    cp /tmp/gen/extension-pixelforge.cc /out/generated/; \
    cp "$(find /tmp/gen/src -name Image.cc)" /out/generated/Image.cc; \
    cp /tmp/gen/include/*.h /out/generated/include/; \
    # module name: "pixelforge" instead of TypePHP's "typephp_pixelforge"
    sed -i 's/typephp_pixelforge/pixelforge/g' /out/generated/*.cc /out/generated/include/*.h; \
    # vendored PHPX runtime (Apache-2.0), only what the extension links
    P=/opt/typephp/vendor/swoole/phpx; D=/out/deps/phpx; \
    mkdir -p $D/src $D/thirdparty/mpdecimal/libmpdec $D/thirdparty/mpdecimal/libmpdec++ $D/thirdparty/wren-gc; \
    cp $P/LICENSE $D/; cp -r $P/include $D/; \
    for d in core std typephp; do cp -r $P/src/$d $D/src/; done; \
    find $D/src -name '*_nano.cc' -delete; \
    cp $P/thirdparty/mpdecimal/COPYRIGHT.txt $D/thirdparty/mpdecimal/; \
    cp $P/thirdparty/mpdecimal/libmpdec/*.c $P/thirdparty/mpdecimal/libmpdec/*.h $D/thirdparty/mpdecimal/libmpdec/; \
    rm -f $D/thirdparty/mpdecimal/libmpdec/bench*.c; \
    sed 's/@MPD_HEADER_CONFIG@/#define MPD_CONFIG_64 1/' $P/thirdparty/mpdecimal/libmpdec/mpdecimal.h.in > $D/thirdparty/mpdecimal/libmpdec/mpdecimal.h; \
    cp $P/thirdparty/mpdecimal/libmpdec++/decimal.cc $P/thirdparty/mpdecimal/libmpdec++/decimal.hh $D/thirdparty/mpdecimal/libmpdec++/; \
    cp -r $P/thirdparty/wren-gc/src $P/thirdparty/wren-gc/include $D/thirdparty/wren-gc/; \
    ls $P/thirdparty/wren-gc; cp $P/thirdparty/wren-gc/LICENSE* $D/thirdparty/wren-gc/ 2>/dev/null || true; \
    php -r 'foreach (json_decode(file_get_contents("/opt/typephp/vendor/composer/installed.json"), true)["packages"] as $p) if ($p["name"] === "swoole/phpx") echo "phpx ", $p["version"], "\n";' > $D/VERSION; \
    echo "typephp ${TYPEPHP_REF}" >> $D/VERSION

FROM scratch AS generated
COPY --from=generate /out/ /

# ---------------------------------------------------------------- build with phpize (exactly what PECL/PIE do)
FROM vips AS build
RUN apt-get update && apt-get install -y --no-install-recommends \
      build-essential autoconf pkg-config libgmp-dev libmpfr-dev \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /src/pixelforge
COPY config.m4 ./
COPY generated generated
COPY deps deps
COPY src src
RUN phpize && ./configure --with-pixelforge-vips=/opt/vips && make -j"$(nproc)" \
    && mkdir -p /out/lib && cp modules/pixelforge.so /out/ \
    && cp -a /opt/vips/lib/. /out/lib/ && rm -rf /out/lib/pkgconfig \
    && LD_LIBRARY_PATH=/out/lib ldd /out/pixelforge.so /out/lib/*.so* 2>/dev/null | awk '/=> \//{print $3}' | grep -v '^/out/' | sort -u \
       | while read -r f; do dpkg -S "$(realpath "$f")" 2>/dev/null || dpkg -S "/usr$(realpath "$f")" 2>/dev/null || true; done \
       | cut -d: -f1 | sort -u > /out/runtime-packages.txt \
    && cat /out/runtime-packages.txt

# ---------------------------------------------------------------- test fixtures
FROM debian:${DEBIAN}-slim AS fixtures
RUN apt-get update && apt-get install -y --no-install-recommends libvips-tools && rm -rf /var/lib/apt/lists/*
# A large 24MP JPEG, a PNG with alpha, a small overlay.
RUN mkdir -p /fixtures && cd /tmp \
    && vips gaussnoise n.v 6000 4000 --mean 128 --sigma 50 \
    && vips gaussblur n.v nb.v 3 \
    && vips bandjoin "nb.v nb.v nb.v" rgb.v \
    && vips copy rgb.v rgb2.v --interpretation srgb \
    && vips cast rgb2.v rgbu.v uchar \
    && vips jpegsave rgbu.v /fixtures/large.jpg --Q 90 \
    && vips extract_area rgbu.v small.v 0 0 800 600 \
    && vips bandjoin_const small.v alpha.v 180 \
    && vips pngsave alpha.v /fixtures/alpha.png \
    && vips extract_area alpha.v ov.v 0 0 120 80 \
    && vips pngsave ov.v /fixtures/overlay.png \
    && rm -f /tmp/*.v && ls -la /fixtures

# ---------------------------------------------------------------- artifacts
FROM scratch AS artifacts
COPY --from=build /out/ /
COPY --from=fixtures /fixtures /fixtures

# ---------------------------------------------------------------- runtime
FROM php:${PHP_VERSION}-${PHP_VARIANT}-${DEBIAN} AS runtime
COPY --from=build /out/runtime-packages.txt /tmp/
RUN apt-get update && apt-get install -y --no-install-recommends \
      $(cat /tmp/runtime-packages.txt) \
      fontconfig-config fonts-dejavu-core \
      $(grep -q libheif /tmp/runtime-packages.txt && echo libheif-plugin-aomenc libheif-plugin-dav1d libheif-plugin-libde265 libheif-plugin-x265) \
    && rm -rf /var/lib/apt/lists/* /tmp/runtime-packages.txt
COPY --from=build /out/lib/ /opt/vips/lib/
COPY --from=build /out/pixelforge.so /tmp/pixelforge.so
RUN echo /opt/vips/lib > /etc/ld.so.conf.d/000-vips.conf && ldconfig \
    && mv /tmp/pixelforge.so "$(php-config --extension-dir)/pixelforge.so" \
    && echo "extension=pixelforge" > "$PHP_INI_DIR/conf.d/50-pixelforge.ini" \
    && php -m | grep -x pixelforge
# glibc malloc + malloc_trim after every output keeps long-lived workers small (PIXELFORGE_TRIM=0 disables).
# For php-fpm with many workers you may set PIXELFORGE_CONCURRENCY=1; by default threads are chosen per pipeline.
WORKDIR /app
COPY --from=fixtures /fixtures /app/fixtures
COPY examples /app/examples
COPY tests /app/tests
