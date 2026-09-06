# GEO External Operator

GEO External Operator is a standalone scientific software implementation of the
GEO geometric-response operator.

The software exposes the GEO engine through:

- a native C library;
- a Python interface;
- a Cobaya Theory adapter;
- reproducible tests and examples.

The software is independent of CLASS itself. CLASS or another cosmological
solver may provide primitive physical quantities to an external GEO adapter.

## Scope

This repository provides software implementation and reproducibility material.

It does not claim that the GEO framework is an established physical theory, nor
does successful execution of the software constitute observational validation.

The current implementation should be treated as research software for testing
specific GEO realizations.

## Core relation

The canonical effective radial response is

\[
R = \mu_{\mathrm{eff}}^{1/3}.
\]

The partition parameter \(\eta\) and the application-dependent effective state
\(\mu_{\mathrm{eff}}\) are distinct quantities.

Specific adapters may define an application-dependent relation between them.
For example, the current Hubble demonstration uses the explicit hypothesis

\[
\mu_H := \eta.
\]
