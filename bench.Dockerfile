# Benchmark image: pixelforge + GD + Imagick for comparison.
#   docker build -t pixelforge . && docker build -f bench.Dockerfile -t pixelforge:bench .
FROM pixelforge
COPY --from=mlocati/php-extension-installer /usr/bin/install-php-extensions /usr/local/bin/
RUN install-php-extensions gd imagick
CMD ["php", "/app/tests/bench.php", "20"]
