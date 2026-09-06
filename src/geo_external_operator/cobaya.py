from cobaya.theory import Theory

from ._binding import compute


class GEOHubbleTheory(Theory):
    """
    Cobaya Theory adapter for the GEO Hubble application.

    The Hubble realization uses the application-specific hypothesis

        mu_H := eta

    This does not define a universal identity between eta and mu_eff.
    """

    ETA_HUBBLE = 0.6
    L_HUBBLE = 0.0

    def get_requirements(self):
        return {
            "Hubble": {
                "z": [0.0],
            }
        }

    def get_can_provide(self):
        return ["geo_hubble"]

    def get_can_provide_params(self):
        return [
            "H0_primitive_geo",
            "H0_GEO",
            "R_GEO",
            "Phi_GEO",
            "alpha_GEO",
            "P_GEO",
        ]

    def calculate(
        self,
        state,
        want_derived=True,
        **params_values_dict,
    ):
        H = self.provider.get_Hubble(
            [0.0],
            units="km/s/Mpc",
        )

        H0_primitive = float(H[0])

        eta = self.ETA_HUBBLE
        L = self.L_HUBBLE

        # Application-specific Hubble realization only.
        mu_H = eta

        result = compute(
            eta=eta,
            L=L,
            mu_eff=mu_H,
        )

        P_GEO = 1.0 + result.alpha * (
            1.0 - result.R
        )

        H0_GEO = P_GEO * H0_primitive

        geo_hubble = {
            "H0_primitive": H0_primitive,
            "eta": eta,
            "L": L,
            "mu_eff": mu_H,
            "R": result.R,
            "Phi": result.Phi,
            "alpha": result.alpha,
            "P_GEO": P_GEO,
            "H0_GEO": H0_GEO,
        }

        state["geo_hubble"] = geo_hubble

        if want_derived:
            state["derived"] = {
                "H0_primitive_geo": H0_primitive,
                "H0_GEO": H0_GEO,
                "R_GEO": result.R,
                "Phi_GEO": result.Phi,
                "alpha_GEO": result.alpha,
                "P_GEO": P_GEO,
            }

        return True

    def get_geo_hubble(self):
        return self.current_state["geo_hubble"]
