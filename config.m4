dnl config.m4 for pixelforge — buildable with phpize (PECL / PIE).
dnl The C++ in generated/ is emitted by TypePHP from src/*.php (scripts/generate.sh);
dnl deps/phpx is the vendored PHPX runtime (Apache-2.0) linked statically.

PHP_ARG_ENABLE([pixelforge],
  [whether to enable pixelforge],
  [AS_HELP_STRING([--disable-pixelforge], [Disable pixelforge image processing])],
  [yes])

PHP_ARG_WITH([pixelforge-vips],
  [for libvips],
  [AS_HELP_STRING([[--with-pixelforge-vips[=DIR]]],
    [Prefix of the libvips (vips-cpp) installation, e.g. the sharp-libvips bundle. Default: pkg-config])],
  [no],
  [no])

if test "$PHP_PIXELFORGE" != "no"; then
  PHP_REQUIRE_CXX()
  PHP_CXX_COMPILE_STDCXX([17], [mandatory], [PIXELFORGE_STDCXX])

  dnl ---------------------------------------------------------------- PHP version
  AC_MSG_CHECKING([for PHP 8.4 or 8.5])
  pf_php_version=`$PHP_CONFIG --vernum`
  if test "$pf_php_version" -lt 80400 || test "$pf_php_version" -ge 80600; then
    AC_MSG_RESULT([no ($pf_php_version)])
    AC_MSG_ERROR([pixelforge requires PHP 8.4 or 8.5])
  fi
  AC_MSG_RESULT([yes ($pf_php_version)])

  dnl ---------------------------------------------------------------- libvips
  if test "$PHP_PIXELFORGE_VIPS" != "no" && test "$PHP_PIXELFORGE_VIPS" != "yes"; then
    export PKG_CONFIG_PATH="$PHP_PIXELFORGE_VIPS/lib/pkgconfig:$PHP_PIXELFORGE_VIPS/lib64/pkgconfig:$PKG_CONFIG_PATH"
  fi
  dnl Homebrew: vips.pc requires keg-only packages (libarchive, expat, libffi, zlib) that pkg-config can't see
  pf_brew=""
  if test "`uname -s`" = "Darwin" && command -v brew >/dev/null 2>&1; then
    pf_brew=`brew --prefix`
    for keg in libarchive expat libffi zlib; do
      if test -d "$pf_brew/opt/$keg/lib/pkgconfig"; then
        export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:$pf_brew/opt/$keg/lib/pkgconfig"
      fi
    done
  fi
  PKG_CHECK_MODULES([VIPS], [vips-cpp >= 8.15],, [
    AC_MSG_ERROR([libvips (vips-cpp >= 8.15) not found. Install libvips-dev / vips, or use --with-pixelforge-vips=DIR])
  ])
  PHP_EVAL_INCLINE([$VIPS_CFLAGS])
  PHP_EVAL_LIBLINE([$VIPS_LIBS], [PIXELFORGE_SHARED_LIBADD])

  dnl Homebrew gmp/mpfr live in $(brew --prefix); add it *after* libvips so an explicit
  dnl --with-pixelforge-vips prefix keeps priority over Homebrew's own vips.
  pf_extra_ldflags=""
  if test -n "$pf_brew"; then
    PHP_ADD_INCLUDE([$pf_brew/include])
    dnl appended (not PHP_ADD_LIBPATH, which prepends) so libvips' -L stays first
    PIXELFORGE_SHARED_LIBADD="$PIXELFORGE_SHARED_LIBADD -L$pf_brew/lib -Wl,-rpath,$pf_brew/lib"
    pf_extra_ldflags="-L$pf_brew/lib"
  fi

  dnl ---------------------------------------------------------------- gmp / mpfr (PHPX runtime)
  PHP_CHECK_LIBRARY([gmp], [__gmpz_init],
    [PHP_ADD_LIBRARY([gmp], [1], [PIXELFORGE_SHARED_LIBADD])],
    [AC_MSG_ERROR([libgmp not found (install libgmp-dev / gmp)])],
    [$pf_extra_ldflags])
  PHP_ADD_LIBRARY([gmpxx], [1], [PIXELFORGE_SHARED_LIBADD])
  PHP_CHECK_LIBRARY([mpfr], [mpfr_init2],
    [PHP_ADD_LIBRARY([mpfr], [1], [PIXELFORGE_SHARED_LIBADD])],
    [AC_MSG_ERROR([libmpfr not found (install libmpfr-dev / mpfr)])],
    [$pf_extra_ldflags -lgmp])

  dnl ---------------------------------------------------------------- sources
  pf_phpx=deps/phpx
  pf_srcdir=PHP_EXT_SRCDIR([pixelforge])
  PHP_ADD_INCLUDE([$pf_srcdir/generated/include])
  PHP_ADD_INCLUDE([$pf_srcdir/$pf_phpx/include])
  PHP_ADD_INCLUDE([$pf_srcdir/$pf_phpx/thirdparty/mpdecimal/libmpdec])
  PHP_ADD_INCLUDE([$pf_srcdir/$pf_phpx/thirdparty/mpdecimal/libmpdec++])
  PHP_ADD_INCLUDE([$pf_srcdir/$pf_phpx/thirdparty/wren-gc/include])

  pf_cxx_sources="generated/extension-pixelforge.cc generated/Image.cc src/pixelforge.cc"
  for f in `cd $pf_srcdir && ls $pf_phpx/src/core/*.cc $pf_phpx/src/std/*.cc $pf_phpx/src/typephp/*.cc | grep -v '_nano\.cc$'`; do
    pf_cxx_sources="$pf_cxx_sources $f"
  done
  pf_cxx_sources="$pf_cxx_sources $pf_phpx/thirdparty/mpdecimal/libmpdec++/decimal.cc"

  pf_c_sources=""
  for f in `cd $pf_srcdir && ls $pf_phpx/thirdparty/mpdecimal/libmpdec/*.c | grep -v bench`; do
    pf_c_sources="$pf_c_sources $f"
  done
  pf_c_sources="$pf_c_sources $pf_phpx/thirdparty/wren-gc/src/wren_gc.c"

  pf_cxxflags="$PIXELFORGE_STDCXX -fvisibility=hidden -fvisibility-inlines-hidden -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1 -DCONFIG_64 -DANSI -DHAVE_UINT128_T -Wno-unused-parameter"
  pf_cflags="-std=c11 -fvisibility=hidden -DCONFIG_64 -DANSI -DHAVE_UINT128_T"

  PHP_NEW_EXTENSION([pixelforge], [$pf_cxx_sources], [$ext_shared],, [$pf_cxxflags], [cxx])
  PHP_ADD_SOURCES_X([PHP_EXT_DIR(pixelforge)], [$pf_c_sources], [$pf_cflags], [shared_objects_pixelforge], [yes])
  PHP_SUBST([PIXELFORGE_SHARED_LIBADD])

  for d in generated src $pf_phpx/src/core $pf_phpx/src/std $pf_phpx/src/typephp \
           $pf_phpx/thirdparty/mpdecimal/libmpdec $pf_phpx/thirdparty/mpdecimal/libmpdec++ $pf_phpx/thirdparty/wren-gc/src; do
    PHP_ADD_BUILD_DIR([$ext_builddir/$d], [1])
  done
fi
