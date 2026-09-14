# GEO External Operator

## Public executable implementation of the GEO Hidden Geometry operator

**Author:** Leonel Hernán Torreblanca  
**Project:** GEO — Hidden Geometry  
**Role:** General external mathematical operator  
**Status:** Public research software  
**API:** C and Python

---

# 1. Overview

GEO External Operator is a standalone executable implementation of the
mathematical operator chain used by the GEO Hidden Geometry framework.

Its purpose is deliberately narrower than that of a physical application.

The package receives an explicitly declared GEO state,

\[
(\eta,L,\mu_{\mathrm{eff}}),
\]

evaluates the corresponding mathematical transformation, and exposes
the resulting radial, spectral, projected, reconstructed, and numerical
closure quantities through public C and Python interfaces.

The core calculation may be summarized as

\[
(\eta,L,\mu_{\mathrm{eff}})
\longrightarrow
\text{GEO External Operator}
\longrightarrow
(R,\Phi,\alpha,\text{projection},\text{reconstruction}).
\]

The operator is application-independent.

A physical or cosmological project may supply a value of
\(\mu_{\mathrm{eff}}\), but the core engine does not decide what physical
system that value represents.

---

# 2. Relationship to the GEO framework

The mathematical provenance of this project is the GEO Hidden Geometry
framework:

https://github.com/LeoTorreblanca/GEO-hidden-geometry-framework

The root GEO project documents the historical development from the
earlier GDD/GDDv2/SOP investigations to the mature conservative and
projective architecture.

GEO External Operator has a different role.

It provides an executable layer that allows the declared mathematical
relations to be evaluated independently of the original CLASS-based
development environment.

The distinction is:

\[
\text{GEO framework}
\rightarrow
\text{mathematical definitions},
\]

while

\[
\text{GEO External Operator}
\rightarrow
\text{executable realization}.
\]

Successful execution demonstrates implementation consistency.

It does not by itself establish empirical validity of the underlying
physical interpretation.

---

# 3. Core inputs

The public operator receives three principal state inputs:

\[
\boxed{
\eta,\quad L,\quad \mu_{\mathrm{eff}}
}
\]

where:

- \(\eta\) is the GEO structural partition parameter;
- \(L\) is the latent/loss component;
- \(\mu_{\mathrm{eff}}\) is the effective state supplied by an
  application.

For the canonical conservative GEO configuration,

\[
\eta=\frac35=0.6
\]

and frequently

\[
L=0.
\]

However, the API does not require

\[
\mu_{\mathrm{eff}}=\eta.
\]

This distinction is fundamental.

---

# 4. Conservative state

The GEO framework defines the normalized conservative architecture

\[
A+B+L=T,
\]

with

\[
T=1.
\]

For a supplied \(\eta\),

\[
A=\eta
\]

and

\[
B=1-\eta-L.
\]

In the canonical lossless state,

\[
L=0,
\]

so

\[
A+B=1.
\]

At

\[
\eta=\frac35,
\]

the canonical partition is

\[
A=\frac35,
\qquad
B=\frac25.
\]

Numerically,

\[
A=0.6,
\qquad
B=0.4.
\]

---

# 5. Canonical coupling relation

The GEO coupling amplitude is defined by

\[
\boxed{
f_c=\sqrt{\eta}.
}
\]

For the canonical state,

\[
f_c
=
\sqrt{\frac35}
=
0.774596669241483\ldots
\]

The implementation evaluates this quantity from the supplied structural
state.

It is not a Hubble-specific parameter.

---

# 6. General effective-state radial law

The current GEO radial/effective-state relation is

\[
\boxed{
R^3=\mu_{\mathrm{eff}}
}
\]

or equivalently

\[
\boxed{
R=\mu_{\mathrm{eff}}^{1/3}.
}
\]

This is the general radial law implemented by the public operator.

The structural parameter

\[
\eta
\]

and the effective application state

\[
\mu_{\mathrm{eff}}
\]

are distinct quantities.

Therefore,

\[
\boxed{
\mu_{\mathrm{eff}}\neq\eta
}
\]

in general.

A particular application may choose equal numerical values, but such an
identification belongs to that application and is not imposed by the
core engine.

---

# 7. Why the radial distinction matters

Earlier GEO application experiments sometimes used special assignments
between an effective state and the canonical structural node.

The present External Operator does not promote such assignments to
universal identities.

Instead, the API makes the separation explicit:

    eta
    L
    mu_eff

are independent arguments to the public computation interface.

Consequently, one may hold

\[
\eta=0.6
\]

fixed while changing

\[
\mu_{\mathrm{eff}}.
\]

The corresponding radial quantity

\[
R=\mu_{\mathrm{eff}}^{1/3}
\]

changes accordingly.

This behavior is an intentional property of the current public engine.

---

# 8. Canonical projection

The operator contains the canonical GEO projective layer.

For the conservative observable/complementary pair,

\[
\mathbf v=
\begin{pmatrix}
A\\
B
\end{pmatrix},
\]

the canonical orthogonal transformation is associated with

\[
\theta=\frac{\pi}{4}.
\]

It can be written

\[
\boxed{
Q=
\frac1{\sqrt2}
\begin{pmatrix}
1&1\\
-1&1
\end{pmatrix}.
}
\]

The projected pair is

\[
\mathbf v'=Q\mathbf v.
\]

Thus

\[
A'
=
\frac{A+B}{\sqrt2},
\]

and

\[
B'
=
\frac{B-A}{\sqrt2}
\]

for the canonical orientation.

For the lossless state,

\[
A+B=1,
\]

which gives

\[
\boxed{
A'=\frac1{\sqrt2}.
}
\]

At the canonical state

\[
A=0.6,
\qquad
B=0.4,
\]

the engine returns approximately

\[
A'=0.7071067811865475
\]

and

\[
B'=-0.1414213562373095.
\]

---

# 9. Orthogonality and norm preservation

The canonical operator satisfies

\[
Q^TQ=I.
\]

Therefore the complete projected state preserves the Euclidean norm.

The public API exposes a numerical diagnostic,

    projection_norm_error

which makes this closure directly testable.

Residual errors at approximately machine precision are expected because
the implementation uses floating-point arithmetic.

---

# 10. Reconstruction

Because the canonical projection is orthogonal,

\[
Q^{-1}=Q^T.
\]

The complete projected pair can therefore be mapped back to the original
state.

The public API exposes reconstructed quantities for:

- the observable component;
- the complementary component;
- the latent component.

It also exposes the corresponding numerical reconstruction errors.

This verifies the forward/inverse consistency of the implemented
transformation.

The implementation does not claim that one projected coordinate by
itself contains enough information to reconstruct the full original
state.

---

# 11. Spectral and effective outputs

The External Operator also evaluates the declared GEO transport
realization used by the engine.

Among the exposed quantities are

\[
\Phi
\]

and

\[
\alpha.
\]

The spectral quantity is associated with the declared transport
operator through

\[
\boxed{
\Phi=\rho(M_5),
}
\]

where

\[
\rho(M_5)=\max_i|\lambda_i|.
\]

A corresponding coefficient is evaluated as

\[
\boxed{
\alpha=\frac{\Phi B}{\sqrt2}.
}
\]

These quantities are deterministic outputs of the declared operator
state.

They are not observational parameters inferred by this package.

---

# 12. Public Python API

The principal Python interface is

    from geo_external_operator import compute

A calculation is performed as

    result = compute(
        eta=0.6,
        L=0.0,
        mu_eff=0.81,
    )

The result exposes fields including:

    eta
    L
    mu_eff
    R
    Phi
    alpha

as well as:

    projected_observable
    projected_complementary
    projected_latent

and:

    reconstructed_observable
    reconstructed_complementary
    reconstructed_latent

with numerical diagnostics including:

    projection_norm_error
    reconstruction_observable_error
    reconstruction_complementary_error
    reconstruction_latent_error

The exact public result structure is documented in `docs/python_api.md`.

---

# 13. Public C API

The project also exposes a native C interface.

Principal public entry points include:

    geo_public_api_version

and

    geo_public_compute

The corresponding headers and source implementation are contained under

    include/
    src/

The public shared library can be built through the project build system.

The C interface and Python binding evaluate the same underlying
mathematical operator.

---

# 14. Public engine demonstration

The principal standalone example is

    examples/full_engine_demo.py

It accepts explicit command-line state values.

For example:

    python examples/full_engine_demo.py \
      --eta 0.60 \
      --L 0.00 \
      --mu 0.81

The demonstration reports:

- API version;
- native library location;
- input state;
- radial response;
- radial closure error;
- \(\Phi\);
- \(\alpha\);
- projected state;
- reconstructed state;
- projection norm error;
- reconstruction errors;
- overall validation status.

The demo explicitly checks

\[
\left|R^3-\mu_{\mathrm{eff}}\right|
\]

and requires the radial identity to close within the declared numerical
tolerance.

It also checks projection and reconstruction closure.

---

# 15. Example of radial-state independence

The separation between \(\eta\) and \(\mu_{\mathrm{eff}}\) can be tested
directly.

For example, keep

\[
\eta=0.6
\]

and

\[
L=0
\]

fixed.

Then evaluate different effective states.

For

\[
\mu_{\mathrm{eff}}=0.6,
\]

the radial response is

\[
R
=
0.6^{1/3}
=
0.843432665301749\ldots
\]

whereas for

\[
\mu_{\mathrm{eff}}=0.8104,
\]

the radial response becomes

\[
R
=
0.8104^{1/3}
=
0.932323170115423\ldots
\]

The structural parameter \(\eta\) has not changed.

This demonstrates the software-level separation between the structural
and effective-state layers.

---

# 16. Canonical numerical example

A canonical engine call may use

\[
\eta=0.6,
\]

\[
L=0,
\]

and an independently supplied

\[
\mu_{\mathrm{eff}}.
\]

For

\[
\mu_{\mathrm{eff}}=0.6,
\]

the public operator gives

\[
R=0.843432665301749\ldots
\]

with

\[
R^3-\mu_{\mathrm{eff}}
\]

at floating-point closure.

For the same structural state, the canonical projection returns

\[
A'
\simeq
0.7071067811865475
\]

and

\[
B'
\simeq
-0.1414213562373094.
\]

These values arise from the declared mathematical operator and are not
introduced as fitted observational targets.

---

# 17. Application boundary

GEO External Operator is intentionally application-neutral.

It does not define:

- a preferred Hubble mapping;
- a preferred cosmological observable;
- a preferred gravitational observable;
- a particular dataset;
- an observational likelihood;
- a physical interpretation of every mathematical coordinate.

Instead, an application supplies the relevant effective state and
defines how its physical quantities are mapped into the operator.

The architecture is therefore

\[
\text{physical application}
\rightarrow
\mu_{\mathrm{eff}}
\rightarrow
\text{GEO External Operator}
\rightarrow
\text{mathematical response}.
\]

The physical validity of the first mapping must be tested separately.

---

# 18. GEO-Hubble

The GEO-Hubble project is maintained separately from this core operator.

That project evaluates a specific projective hypothesis using the
canonical GEO architecture and the External Operator as a numerical
reference implementation.

The separation is deliberate.

The External Operator should remain valid as a mathematical engine even
if a particular Hubble application is modified, rejected, or replaced.

Accordingly, Hubble-specific adapter logic is not part of the current
core package.

Historical releases that contained an earlier Hubble adapter remain
available through Git history and tagged versions for provenance.

---

# 19. CLASS and cosmological software

The original GEO research program included extensive work with CLASS.

The External Operator was designed so that the core GEO calculation can
exist outside a modified CLASS source tree.

Scientific software may call the public GEO interfaces and supply
application quantities externally.

This modularity is useful for reproducibility because it separates

\[
\text{external solver}
\]

from

\[
\text{GEO operator}.
\]

CLASS provenance associated with earlier interoperability experiments is
retained under

    provenance/

for historical reproducibility.

Those provenance records do not imply that CLASS or Cobaya is required
by the current core package.

---

# 20. Historical adapter provenance

Earlier public releases included a Hubble-specific Cobaya adapter.

That adapter belonged to an application-specific historical experiment
and is not part of the current core operator API.

The corresponding historical state remains recoverable through the Git
history and historical release tags.

This allows the project to preserve provenance without treating an older
application mapping as a universal mathematical definition.

---

# 21. Tests

The repository contains automated tests for the native and Python
interfaces.

The core validation strategy includes checks of:

- public API availability;
- structural state handling;
- radial-law closure;
- projection;
- projection norm conservation;
- reconstruction;
- numerical precision;
- C/Python consistency.

Application-specific cosmological adapter tests are intentionally
separate from the current core suite.

Run the available test suite with:

    pytest -q

Native tests may additionally be executed through the project build and
test workflow.

---

# 22. Numerical precision

The GEO operator is evaluated in floating-point arithmetic.

Therefore quantities expected analytically to vanish may return small
residual values such as

\[
10^{-16}
\]

or similar machine-scale errors.

Such values should be interpreted according to the declared numerical
tolerances of the tests.

The implementation should not replace mathematical closure with exact
decimal string comparison.

---

# 23. Scientific status

GEO External Operator is research software.

A successful calculation establishes that the declared mathematical
operations can be evaluated consistently by the implementation.

It does not by itself demonstrate that:

- GEO is a confirmed physical theory;
- GEO replaces General Relativity;
- a specific physical system must realize a GEO state;
- an application mapping is empirically correct;
- a numerical closure is observational evidence.

Mathematical implementation and physical validation are distinct
questions.

---

# 24. Reproducibility principle

The project is organized around a simple reproducibility boundary:

\[
\boxed{
\text{inputs}
\rightarrow
\text{operator}
\rightarrow
\text{outputs}
}
\]

The user should be able to identify:

- what values were supplied;
- which equations were evaluated;
- which quantities were derived;
- which numerical tolerances were used;
- which application assumptions exist outside the core operator.

This separation allows the same mathematical engine to be exercised by
multiple applications without silently changing the underlying
definitions.

---

# 25. Repository structure

Principal project areas include:

    include/
        Public and internal C headers

    src/
        Native GEO engine and Python package

    docs/
        Mathematical model, API, limitations, quickstart,
        and reproducibility documentation

    examples/
        Standalone public engine demonstrations

    tests/
        Native and Python regression tests

    provenance/
        Historical environment and interoperability records

    pyproject.toml
        Python/build metadata

    requirements.txt
        Core Python numerical dependencies

    CITATION.cff
        Citation metadata

    LICENSE
        Software license

---

# 26. Installation

The project can be installed from source using its Python build
configuration.

A typical development installation is

    python -m venv .venv
    source .venv/bin/activate

    pip install --upgrade pip
    pip install -e ".[test]"

The exact compiler/build requirements are documented by the project
configuration and development documentation.

Application-specific cosmological packages are not required by the core
GEO External Operator.

---

# 27. Quick verification

After installation, a minimal verification is:

    python - <<'PY'
    from geo_external_operator import compute

    g = compute(
        eta=0.6,
        L=0.0,
        mu_eff=0.8104,
    )

    print("eta =", g.eta)
    print("mu_eff =", g.mu_eff)
    print("R =", g.R)
    print("R^3 - mu_eff =", g.R**3 - g.mu_eff)
    print("projected observable =", g.projected_observable)
    print("Phi =", g.Phi)
    print("alpha =", g.alpha)
    PY

The expected radial identity is

\[
R^3
\simeq
\mu_{\mathrm{eff}}
\]

to floating-point precision.

---

# 28. Related GEO projects

## GEO Hidden Geometry Framework

Historical and architectural root of the GEO program:

https://github.com/LeoTorreblanca/GEO-hidden-geometry-framework

## GEO-FOUNDATIONS

Formal mathematical development of the mature GEO architecture.

## GEO-Hubble Geometric Projection

Application-specific study of the GEO projective Hubble hypothesis.

The Hubble project is intentionally separate from the External Operator
core so that the mathematical engine and the physical application can
be audited independently.

---

# 29. Versioning and historical compatibility

The GEO research program has evolved through multiple mathematical and
computational stages.

For this reason, users reproducing an older result should identify the
specific version or Git commit associated with that calculation.

Historical interfaces may contain application-specific logic that is not
part of the current core architecture.

Current documentation should be used for present mathematical
definitions.

Historical releases remain useful for provenance and reproducibility.

---

# 30. Citation

Citation metadata are provided in

    CITATION.cff

Author:

**Leonel Hernán Torreblanca**

Project:

**GEO — Hidden Geometry**

When a persistent archive or DOI is associated with a particular
release, cite the archived release corresponding to the version actually
used.

---

# 31. License

This project is distributed under the MIT License.

See:

    LICENSE

---

# 32. Summary

GEO External Operator implements a general executable GEO state

\[
\boxed{
(\eta,L,\mu_{\mathrm{eff}})
}
\]

with structural coupling

\[
\boxed{
f_c=\sqrt{\eta},
}
\]

general radial response

\[
\boxed{
R=\mu_{\mathrm{eff}}^{1/3},
}
\]

canonical orthogonal projection,

\[
\boxed{
Q^TQ=I,
}
\]

forward and inverse reconstruction, spectral evaluation,

\[
\boxed{
\Phi=\rho(M_5),
}
\]

and derived coefficient

\[
\boxed{
\alpha=\frac{\Phi B}{\sqrt2}.
}
\]

The structural parameter

\[
\eta
\]

and the effective application state

\[
\mu_{\mathrm{eff}}
\]

remain distinct.

Physical applications are layered on top of this operator rather than
embedded into its general mathematical definition.

The present repository therefore serves as the public executable bridge

\[
\boxed{
\text{GEO mathematics}
\longrightarrow
\text{reproducible operator}
\longrightarrow
\text{application-specific tests}.
}
\]
