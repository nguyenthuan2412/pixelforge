# Node.js + sharp (prebuilt, bundled libvips) with the same fixtures as pixelforge.
FROM node:24-trixie-slim
WORKDIR /bench
RUN npm init -y >/dev/null && npm install --omit=dev sharp@0.35.5
COPY --from=pixelforge /app/fixtures /app/fixtures
COPY bench.mjs /bench/
