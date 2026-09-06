import math

import geo_external_operator as geo


def test_api_version():
    assert geo.api_version() >= 1


def test_mu_eff_independent_from_eta():
    result = geo.compute(
        eta=0.6,
        L=0.0,
        mu_eff=0.81,
    )

    assert math.isclose(
        result.eta,
        0.6,
        rel_tol=0.0,
        abs_tol=1e-15,
    )

    assert math.isclose(
        result.mu_eff,
        0.81,
        rel_tol=0.0,
        abs_tol=1e-15,
    )


def test_canonical_radial_law():
    result = geo.compute(
        eta=0.6,
        L=0.0,
        mu_eff=0.81,
    )

    assert math.isclose(
        result.R ** 3,
        result.mu_eff,
        rel_tol=0.0,
        abs_tol=1e-12,
    )


def test_projection_norm_closure():
    result = geo.compute(
        eta=0.6,
        L=0.0,
        mu_eff=0.81,
    )

    assert result.projection_norm_error < 1e-12


def test_reconstruction_closure():
    result = geo.compute(
        eta=0.6,
        L=0.0,
        mu_eff=0.81,
    )

    assert result.reconstruction_observable_error < 1e-12

    assert result.reconstruction_complementary_error < 1e-12

    assert result.reconstruction_latent_error < 1e-12
