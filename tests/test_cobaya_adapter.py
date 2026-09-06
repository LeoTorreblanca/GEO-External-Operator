import math

import pytest

pytest.importorskip(
    "cobaya",
    reason="Cobaya integration test requires the 'cobaya' optional dependency",
)

from geo_external_operator.cobaya import GEOHubbleTheory


class DummyProvider:
    def __init__(self, H0):
        self.H0 = H0

    def get_Hubble(self, z, units=None):
        assert list(z) == [0.0]
        assert units == "km/s/Mpc"

        return [self.H0]


def test_hubble_adapter():
    theory = GEOHubbleTheory()

    theory.provider = DummyProvider(67.4)

    state = {}

    ok = theory.calculate(
        state,
        want_derived=True,
    )

    assert ok is True

    result = state["geo_hubble"]

    assert math.isclose(
        result["H0_primitive"],
        67.4,
        abs_tol=1e-12,
    )

    assert math.isclose(
        result["eta"],
        0.6,
        abs_tol=1e-15,
    )

    assert math.isclose(
        result["mu_eff"],
        0.6,
        abs_tol=1e-15,
    )

    assert math.isclose(
        result["R"] ** 3,
        result["mu_eff"],
        abs_tol=1e-12,
    )

    assert math.isclose(
        result["H0_GEO"],
        result["P_GEO"] * result["H0_primitive"],
        abs_tol=1e-12,
    )
