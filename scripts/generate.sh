#!/usr/bin/env bash
# Regenerate generated/ (C++ emitted by TypePHP from src/*.php) and deps/phpx/ (vendored PHPX runtime).
# Requires Docker. Run after changing src/Image.php or src/pixelforge.stub.php.
set -euo pipefail
cd "$(dirname "$0")/.."
rm -rf generated deps/phpx
docker build --target generated --output type=local,dest=. .
echo "generated/ and deps/phpx/ updated"
