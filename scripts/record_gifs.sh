#!/usr/bin/env bash
# Generate docs/rubik.gif and docs/hyper.gif from a fresh scramble[+]solve pass.
#
# Requirements: a built ./build/rubik binary and ffmpeg on PATH.
#
# The binary writes raw PPM frames into a temp dir (see record_view in
# main.cpp); ffmpeg downsamples + builds an optimized palette per GIF so the
# output stays under ~3 MB at 720px.

set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN="$ROOT/build/rubik"
DOCS="$ROOT/docs"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

if [[ ! -x "$BIN" ]]; then
    echo "binary not found at $BIN — run cmake --build build first" >&2
    exit 1
fi

if ! command -v ffmpeg >/dev/null 2>&1; then
    echo "ffmpeg required (brew install ffmpeg / apt install ffmpeg)" >&2
    exit 1
fi

mkdir -p "$DOCS"

# Per-view tuning so hyper.gif (long expand+solve+reassemble pass) stays
# under ~5 MB while rubik.gif keeps full quality.
for view in rubik hyper; do
    case $view in
        rubik) gif_fps=20; gif_width=720; speed=1.0 ;;
        hyper) gif_fps=15; gif_width=560; speed=2.0 ;;
    esac

    out="$TMP/$view"
    mkdir -p "$out"
    echo "[+] recording $view..."
    "$BIN" --record-view "$view" "$out"

    palette="$TMP/$view-palette.png"
    filter="setpts=PTS/${speed},fps=${gif_fps},scale=${gif_width}:-1:flags=lanczos"

    ffmpeg -y -loglevel error -framerate 30 -i "$out/frame_%05d.ppm" \
        -vf "${filter},palettegen=stats_mode=diff" "$palette"
    ffmpeg -y -loglevel error -framerate 30 -i "$out/frame_%05d.ppm" -i "$palette" \
        -lavfi "${filter} [x]; [x][1:v] paletteuse=dither=bayer:bayer_scale=4" \
        "$DOCS/$view.gif"

    size=$(du -h "$DOCS/$view.gif" | cut -f1)
    echo "[OK] wrote $DOCS/$view.gif ($size)"
done
