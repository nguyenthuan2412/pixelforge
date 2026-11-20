#!/usr/bin/env bash
# Print the first fenced code block of language $2 under the README heading $1.
# Used by CI to run the README's install instructions verbatim.
#   scripts/readme-block.sh "### Ubuntu / Debian" bash
set -euo pipefail
awk -v h="$1" -v lang="$2" '
  $0 == h { in_sec = 1; next }
  in_sec && !in_code && /^#{1,3} / { exit }
  in_sec && !in_code && $0 == "```" lang { in_code = 1; next }
  in_code && $0 == "```" { exit }
  in_code { print }
' "$(dirname "$0")/../README.md"
