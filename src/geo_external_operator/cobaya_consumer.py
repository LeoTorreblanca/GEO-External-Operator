from cobaya.likelihood import Likelihood


class GEOHubbleConsumer(Likelihood):
    """
    Minimal Cobaya consumer used to validate the GEO Hubble
    Theory interface.
    """

    def get_requirements(self):
        return {
            "geo_hubble": None,
        }

    def logp(self, **params_values):
        geo = self.provider.get_geo_hubble()

        if abs(
            geo["R"] ** 3 - geo["mu_eff"]
        ) > 1e-12:
            raise RuntimeError(
                "R^3 = mu_eff identity failed"
            )

        expected = (
            geo["P_GEO"]
            * geo["H0_primitive"]
        )

        if abs(
            geo["H0_GEO"] - expected
        ) > 1e-12:
            raise RuntimeError(
                "H0_GEO transformation failed"
            )

        return 0.0
