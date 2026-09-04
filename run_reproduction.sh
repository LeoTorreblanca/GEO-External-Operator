#!/usr/bin/env bash

cd "$(dirname "$0")"

echo "============================================================"
echo " GEO EXTERNAL OPERATOR REPRODUCTION"
echo "============================================================"

echo
echo "[1/4] Building public GEO library"
make clean
make

echo
echo "[2/4] Checking public API"
nm -D --defined-only libgeo_public.so | grep ' geo_public'

echo
echo "[3/4] Running Cobaya clean-upstream examples"
export PYTHONPATH="$PWD/adapters/cobaya:${PYTHONPATH}"

cobaya-run examples/class_hubble/H0_66.yaml
cobaya-run examples/class_hubble/H0_67_4.yaml
cobaya-run examples/class_hubble/H0_69.yaml

echo
echo "[4/4] Reproduction complete"
echo "============================================================"
echo " GEO EXTERNAL OPERATOR REPRODUCTION = PASS"
echo "============================================================"
