# Cobaya Integration

GEO External Operator provides an optional Cobaya Theory adapter.

The adapter uses the same public GEO engine exposed by the standalone Python API.

## Installation

Cobaya support is optional.

Install it with:

    pip install "geo-external-operator[cobaya]"

For development and testing:

    pip install -e ".[test,cobaya]"

## Theory adapter

The adapter is available as:

    from geo_external_operator.cobaya import GEOHubbleTheory

The adapter obtains the primitive Hubble quantity from a Cobaya provider and applies the GEO Hubble realization.

## Hubble realization

The current Hubble adapter uses:

    eta_H = 0.6

    L_H = 0

and the application-specific hypothesis:

    mu_H = eta_H

This relation applies to this Hubble realization only.

It does not define a universal identity between eta and mu_eff in the general GEO engine.

The radial response is computed by the native engine using:

    R = mu_H^(1/3)

The Hubble projection is then evaluated as:

    P_GEO = 1 + alpha * (1 - R)

and:

    H0_GEO = P_GEO * H0_primitive

## Separation of responsibilities

The cosmological provider supplies the primitive physical quantity.

The GEO adapter supplies the application-specific effective state and calls the public GEO operator.

The native GEO engine performs the geometric computation.

This separation allows the GEO operator to remain independent of a specific local CLASS installation.

## No hard-coded development path

The current packaged adapter does not load a library from a private path such as:

    ~/GEO_CLASS/

Instead, it imports the installed GEO Python package and uses the native library distributed with that package.

## Testing

The Cobaya adapter has an automated test using a controlled provider with:

    H0_primitive = 67.4

The test verifies:

    eta = 0.6

    mu_H = 0.6

    R^3 = mu_H

and:

    H0_GEO = P_GEO * H0_primitive

The test checks software and numerical consistency.

It does not constitute observational validation of the Hubble realization.

## Core package independence

Cobaya is not required to use the core GEO operator.

When Cobaya is absent, the core test suite remains executable and the Cobaya integration test is skipped.

When the Cobaya optional dependency is installed, the complete integration test is executed.
