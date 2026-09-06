# Quick Start

GEO External Operator exposes the native GEO engine through a small Python API.

## Basic computation

    import geo_external_operator as geo

    result = geo.compute(
        eta=0.6,
        L=0.0,
        mu_eff=0.81,
    )

    print("eta =", result.eta)
    print("mu_eff =", result.mu_eff)
    print("R =", result.R)
    print("R^3 =", result.R ** 3)

In this example:

    eta = 0.6
    mu_eff = 0.81

The quantities eta and mu_eff are deliberately different.

The canonical radial relation implemented by the engine is:

    R = mu_eff^(1/3)

and therefore:

    R^3 = mu_eff

The parameter eta describes the GEO partition, while mu_eff is the
application-dependent effective state.

The public engine does not assume a universal identity between eta and mu_eff.

## Projection and reconstruction

The result also exposes numerical diagnostics for the projection and
reconstruction stages:

    print("projection error =", result.projection_norm_error)

    print(
        "reconstruction observable error =",
        result.reconstruction_observable_error,
    )

    print(
        "reconstruction complementary error =",
        result.reconstruction_complementary_error,
    )

For a successful computation these errors should be close to machine precision.

## Locate the native library

The native C library is installed as part of the Python package:

    print(geo.find_library())

No hard-coded GEO development path is required.
