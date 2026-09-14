# GEO External Operator

GEO External Operator is a standalone scientific software implementation of the
GEO geometric-response operator.

The software exposes the GEO engine through:

- a native C library;
- a Python interface;
- a standalone Python interface;
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
## Application boundary

The GEO External Operator exposes the general mathematical engine.

The structural parameter

\[
\eta
\]

and the effective application state

\[
\mu_{\mathrm{eff}}
\]

are distinct inputs.

The general radial relation is

\[
R^3=\mu_{\mathrm{eff}},
\]

or equivalently

\[
R=\mu_{\mathrm{eff}}^{1/3}.
\]

Physical applications may define their own mapping into
\(\mu_{\mathrm{eff}}\), but those mappings are not part of the core
External Operator API.

Application-specific constructions, including GEO-Hubble, are maintained
in dedicated projects rather than in the core External Operator package.

