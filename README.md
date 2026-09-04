# GEO External Operator

External deterministic operator and solver-independent integration layer for the GEO Hidden Geometry Framework.

## Overview

This repository provides a public C interface and a Cobaya integration path for applying the GEO operator externally to quantities supplied by an independent cosmological solver.

The demonstrated integration uses upstream CLASS v3.3.4 through its standard `classy` interface. GEO is not compiled into CLASS and this integration path does not require modifications to CLASS source code.

## Public interface

The public C API is exposed through:

- `geo_public_api_version`
- `geo_public_compute`

Build the shared library with:

    make

This produces:

    libgeo_public.so

## Canonical effectiveness relation

The GEO effectiveness law implemented by the public operator is:

    R^3 = mu_eff
    R   = mu_eff^(1/3)

where `mu_eff` is an application-dependent effective state.

The framework does not impose the universal identity:

    mu_eff = eta

The Hubble example included in this repository uses the specific realization:

    mu_H := eta = 0.6

as an application-level assumption.

## Cobaya / CLASS integration

The external chain is:

    CLASS
      -> standard Cobaya Hubble provider
      -> GEOHubbleTheory
      -> libgeo_public.so
      -> GEO derived quantities

The tested component order is:

    classy
    -> geo_hubble_theory.GEOHubbleTheory
    -> geo_hubble_consumer.GEOHubbleConsumer

## Clean upstream CLASS provenance

The validation environment used:

    CLASS tag:    v3.3.4
    CLASS commit: e85808324f51fc694d12e3ed7439552a3c3f9540
    Python:       3.12.3
    NumPy:        1.26.4
    SciPy:        1.13.1
    Cobaya:       3.6.2
    classy:       3.3.4.0

The CLASS source tree used for the clean validation was produced from the tracked-clean upstream repository with `git archive`.

See:

    provenance/CLASS_UPSTREAM.txt

## Three-point regression

The clean external regression produced:

    H0 primitive = 66.0
    H0_GEO       = 71.522848664464732

    H0 primitive = 67.4
    H0_GEO       = 73.039999999771553

    H0 primitive = 69.0
    H0_GEO       = 74.773887240122221

All three evaluations completed with:

    GEO THEORY -> EXTERNAL CONSUMER = PASS

This regression demonstrates dynamic software behavior. In particular, the output is not hard-coded to a single Hubble value.

## Scientific status

This repository demonstrates software modularity, reproducibility and external solver integration.

It does not, by itself, constitute independent observational validation of the GEO framework.

The Hubble mapping shown here is an application-specific realization.

Parts of the current spectral/residual closure remain associated with the historical `candidate-v1` implementation and should be interpreted accordingly.

## Reproduction

Activate an environment containing compatible CLASS/classy and Cobaya, then run:

    ./run_reproduction.sh

## Repository structure

    include/                 Public and internal C headers
    src/                     GEO engine and public facade
    adapters/cobaya/         Cobaya Theory and consumer
    examples/class_hubble/   Three deterministic Hubble examples
    tests/                   External C/Python tests
    provenance/              Upstream CLASS and environment records

## License

MIT License.

## Author

Leonel Hernán Torreblanca
