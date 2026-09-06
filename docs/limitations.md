# Limitations

GEO External Operator is research software intended to provide a reproducible implementation of the GEO geometric operator.

The existence of a working software implementation must be distinguished from physical or observational validation of the GEO framework.

## Scientific status

The GEO framework remains under active scientific development.

Successful execution of the engine demonstrates that the implemented mathematical operations can be evaluated consistently by the software.

It does not establish GEO as a confirmed physical theory.

## General operator and physical applications

The general GEO engine accepts:

    eta

    L

    mu_eff

as explicit inputs.

The engine does not impose a universal identity between eta and mu_eff.

Mappings between a physical system and mu_eff belong to the corresponding application and require separate justification.

## Hubble application

The current Hubble adapter uses the application-specific hypothesis:

    mu_H = eta

with:

    eta = 0.6

This relation is specific to that realization.

It must not be interpreted as the general GEO definition of mu_eff.

## Cosmological interoperability

The operator can be used externally with cosmological software such as Cobaya and CLASS.

Software interoperability means that quantities can be exchanged through defined interfaces.

It does not by itself demonstrate that the corresponding GEO realization is physically correct or preferred by observational data.

## Projection and reconstruction

The engine exposes observable and complementary projected components.

Reconstruction uses the complete projected pair.

The implementation does not claim that the observable projected component alone uniquely reconstructs the hidden complementary state.

## Numerical precision

Projection, reconstruction, and radial identities are evaluated using floating-point arithmetic.

Small residual numerical errors near machine precision are therefore expected.

## Application-specific validation

Each physical application of GEO should distinguish between:

    the general mathematical operator

    the application-specific mapping

    the external physical model or data provider

    the observational test

A successful test of one layer should not be presented as validation of all other layers.

## Research scope

This repository focuses on the implementation, packaging, testing, documentation, and reproducibility of the external GEO operator.

Broader claims concerning cosmology, gravity, or other physical applications require separate scientific analysis and evidence.
