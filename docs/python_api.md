# Python API

GEO External Operator provides a Python interface to the native C engine.

## Import

Import the package with:

    import geo_external_operator as geo

## Package version

The installed package version is available as:

    print(geo.__version__)

For this development release:

    1.1.0

## Native API version

The native public API version can be queried with:

    print(geo.api_version())

This verifies communication between the Python binding and the compiled C library.

## Compute a GEO state

The main public operation is:

    result = geo.compute(
        eta=0.6,
        L=0.0,
        mu_eff=0.81,
    )

The arguments are:

    eta
        GEO partition parameter.

    L
        Latent contribution.

    mu_eff
        Application-dependent effective state.

The general API treats eta and mu_eff as independent inputs.

## Result

The returned result exposes the public state produced by the native GEO engine.

Core quantities include:

    result.eta
    result.L
    result.mu_eff
    result.R
    result.Phi
    result.alpha

Projection quantities include:

    result.projected_observable
    result.projected_complementary
    result.projected_latent

Reconstruction quantities include:

    result.reconstructed_observable
    result.reconstructed_complementary
    result.reconstructed_latent

Numerical diagnostics include:

    result.projection_norm_error
    result.reconstruction_observable_error
    result.reconstruction_complementary_error
    result.reconstruction_latent_error

## Canonical radial identity

For a computed state:

    result.R ** 3

should reproduce:

    result.mu_eff

within floating-point precision.

## Native library

The location of the compiled native library can be obtained with:

    geo.find_library()

For a normal installed wheel, the library is stored inside the installed Python package.

The public Python interface therefore does not require a hard-coded path to a development copy of the GEO engine.

## C interface

The same engine is also exposed through the public C header:

    geo_public.h

The Python interface is a binding to this public native API rather than an independent reimplementation of the GEO calculations.

## Optional integrations

The core Python package does not require Cobaya.

Cobaya support is installed separately with:

    pip install "geo-external-operator[cobaya]"

The Cobaya adapter consumes the same public GEO engine used by this Python API.
