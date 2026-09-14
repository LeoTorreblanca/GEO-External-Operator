#!/usr/bin/env bash

set -euo pipefail

cd "$(dirname "$0")"

echo "============================================================"
echo " GEO EXTERNAL OPERATOR — CORE REPRODUCTION"
echo "============================================================"

echo
echo "[1/4] Building public GEO library"
make clean
make

echo
echo "[2/4] Checking public native API"
nm -D --defined-only libgeo_public.so | grep ' geo_public'

echo
echo "[3/4] Running core regression suite"
python -m pytest -q

echo
echo "[4/4] Running public engine demonstration"
python examples/full_engine_demo.py \
  --eta 0.60 \
  --L 0.00 \
  --mu 0.8104

echo
echo "============================================================"
echo " GEO EXTERNAL OPERATOR — CORE REPRODUCTION = PASS"
echo "============================================================"

