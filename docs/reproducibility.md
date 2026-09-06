# Reproducibility

GEO External Operator is designed so that the public engine can be built and tested without relying on the author's private development directories.

## Clean installation

Clone the repository:

    git clone https://github.com/LeoTorreblanca/GEO-External-Operator.git

Enter the repository:

    cd GEO-External-Operator

Create an isolated Python environment:

    python3 -m venv .venv

Activate it:

    source .venv/bin/activate

Upgrade pip:

    python -m pip install --upgrade pip

## Core installation and tests

Install the package with the core test dependencies:

    pip install -e ".[test]"

Run:

    pytest -v

Without Cobaya installed, the expected behavior is:

    5 core tests passed
    1 Cobaya integration test skipped

## Complete Cobaya test

Install the optional Cobaya dependencies:

    pip install -e ".[test,cobaya]"

Run:

    pytest -v

The complete current suite contains six tests.

## Wheel distribution

The project can also be built as a standard Python wheel.

Install the build frontend:

    python -m pip install build

Build the distributions:

    python -m build

The resulting wheel contains:

    geo_external_operator/__init__.py
    geo_external_operator/_binding.py
    geo_external_operator/libgeo_public.so
    geo_external_operator/include/geo_public.h
    geo_external_operator/include/geo_engine.h

The wheel can be installed in an independent environment with:

    pip install geo_external_operator-1.1.0-*.whl

The native GEO library is loaded from the installed package.

No private GEO_CLASS path is required.

## Numerical checks

The automated tests currently verify:

    public native API loading

    independence of eta and mu_eff

    R^3 = mu_eff

    projection norm closure

    reconstruction closure

    Cobaya Hubble adapter consistency

Projection and reconstruction closure are expected to be satisfied within floating-point precision.

## Provenance

The repository contains a provenance directory with information about the upstream CLASS environment used during interoperability development.

The GEO engine itself is maintained as an external operator and is not compiled as a modification of the upstream CLASS source tree in this package.

## Interpretation of successful tests

Passing the software test suite demonstrates that the packaged implementation is internally consistent with the tested numerical identities and interfaces.

It does not demonstrate that the GEO framework, or any particular cosmological realization of it, is empirically established.

Physical and observational validation remain separate scientific questions.
