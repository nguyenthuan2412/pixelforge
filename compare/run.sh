#!/usr/bin/env bash
# Runs every scenario on Node sharp and pixelforge, alternating, ROUNDS times; prints medians.
set -euo pipefail
cd "$(dirname "$0")"
CPUS=${CPUS:-4}; N=${N:-20}; ROUNDS=${ROUNDS:-3}
docker build -q -f node.Dockerfile -t sharp-node-bench . >/dev/null
SCEN=(metadata resize800-jpeg resize800-webp cover320-sharpen resize800-avif png-alpha-200 watermark-1200 reencode-full mixed)
RES=$(mktemp)
for r in $(seq "$ROUNDS"); do
  for s in "${SCEN[@]}"; do
    n=$N; [[ $s == reencode-full || $s == mixed ]] && n=$((N/4))
    docker run --rm --cpus="$CPUS" ${NODE_ENV_ARGS:-} sharp-node-bench node bench.mjs "$s" "$n" | sed 's/^/node /' >>"$RES"
    docker run --rm --cpus="$CPUS" ${PHP_ENV_ARGS:-} -v "$PWD/bench.php:/b.php:ro" ${PHP_IMAGE:-pixelforge} php /b.php "$s" "$n" | sed 's/^/php /' >>"$RES"
  done
done
base_node=$(docker run --rm sharp-node-bench node -e "import('sharp').then(()=>console.log(process.resourceUsage().maxRSS/1024))")
base_php=$(docker run --rm ${PHP_IMAGE:-pixelforge} php -r 'PixelForge\PixelForge::versions(); preg_match("/VmHWM:\s+(\d+)/",file_get_contents("/proc/self/status"),$m); echo $m[1]/1024;')
vn=$(docker run --rm sharp-node-bench node -e "import('sharp').then(s=>console.log(s.default.versions.vips))")
python3 - "$RES" "$base_node" "$base_php" "$vn" "$CPUS" <<'PY'
import json, sys, statistics as st
res, bn, bp, vn, cpus = sys.argv[1], float(sys.argv[2]), float(sys.argv[3]), sys.argv[4], sys.argv[5]
d = {}
for line in open(res):
    who, js = line.split(' ', 1); j = json.loads(js)
    d.setdefault(j['name'], {}).setdefault(who, []).append(j)
print(f"cpus={cpus}  node sharp: libvips {vn}, idle RSS {bn:.0f} MB | pixelforge, idle RSS {bp:.0f} MB\n")
print(f"{'scenario':18} {'node ms':>9} {'php ms':>9} {'speed':>7}   {'node pk':>8} {'php pk':>8}   {'node +MB':>8} {'php +MB':>8}   {'node st':>8} {'php st':>8}   {'node B':>8} {'php B':>8}")
for name, w in d.items():
    m = {k: st.median(x['ms'] for x in v) for k, v in w.items()}
    p = {k: st.median(x['peakMB'] for x in v) for k, v in w.items()}
    b = {k: v[-1]['bytes'] for k, v in w.items()}
    sd = {k: st.median(x.get('steadyMB', 0) for x in v) for k, v in w.items()}
    ratio = m['node'] / m['php']
    print(f"{name:18} {m['node']:9.1f} {m['php']:9.1f} {ratio:6.2f}x   {p['node']:8.1f} {p['php']:8.1f}   {p['node']-bn:8.1f} {p['php']-bp:8.1f}   {sd['node']:8.1f} {sd['php']:8.1f}   {b['node']:8} {b['php']:8}")
print("\nspeed = node_ms / php_ms (>1 = pixelforge faster). pk = peak RSS, +MB = peak minus idle runtime RSS, st = RSS 1.5s after the work finished.")
PY
