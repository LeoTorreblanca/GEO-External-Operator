# Mathematical Model

GEO External Operator implements the mathematical operator chain of the GEO framework as a standalone computational engine.

The engine separates the geometric partition from the application-dependent effective state.

## Normalized partition

The total normalized state is:

    T = 1

The active, complementary, and latent sectors satisfy:

    A + B + L = 1

with:

    A = eta

and therefore:

    B = 1 - eta - L

For the two-sector case:

    L = 0

so that:

    A + B = 1

The canonical coupling scale is:

    fc = sqrt(eta)

## Effective state

The effective state used by an application is:

    mu_eff

The quantities eta and mu_eff are distinct.

The general GEO engine does not impose:

    mu_eff = eta

An application-specific adapter may define such a relation when that relation is explicitly part of the tested realization.

## Radial response

The canonical radial response is:

    R = mu_eff^(1/3)

Equivalently:

    R^3 = mu_eff

This identity is directly tested by the software test suite.

## Geometric operator chain

The current engine evaluates the GEO state through the following computational stages:

    normalized state
        ->
    partition
        ->
    effective state
        ->
    radial response
        ->
    bifocal geometry
        ->
    tangent geometry
        ->
    coupling geometry
        ->
    harmonic dual
        ->
    harmonic ring
        ->
    residual state
        ->
    five-dimensional transport
        ->
    spectral response
        ->
    projection
        ->
    reconstruction

## Five-dimensional transport

The engine contains a five-dimensional transport representation composed of:

    3 observable dimensions
    +
    2 complementary dimensions

This structure is represented internally by the M5 transport matrix.

The spectral stage extracts the corresponding numerical response used by the later operator stages.

## Projection

The engine performs an orthogonal projection of the geometric state.

The public result exposes both:

    projected_observable
    projected_complementary

as well as the latent contribution when present.

## Reconstruction

Reconstruction uses the complete projected pair.

The implementation does not claim that the observable projected component alone uniquely determines the complementary hidden state.

The public API exposes numerical reconstruction errors so that closure can be tested directly.

## Scope

These equations describe the mathematical and computational implementation provided by this repository.

Application-specific physical interpretations and observational tests are separate from the numerical consistency of the operator itself.
