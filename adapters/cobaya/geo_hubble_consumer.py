from cobaya.likelihood import Likelihood


class GEOHubbleConsumer(Likelihood):

    def get_requirements(self):
        return {
            "geo_hubble": None
        }

    def logp(self, **params_values):

        geo = self.provider.get_geo_hubble()

        print()
        print("====================================================")
        print(" EXTERNAL GEO HUBBLE THEORY CONSUMER")
        print("====================================================")
        print(f"H0 primitive = {geo['H0_primitive']:.15f}")
        print(f"eta          = {geo['eta']:.15f}")
        print(f"mu_eff       = {geo['mu_eff']:.15f}")
        print(f"R            = {geo['R']:.15f}")
        print(f"Phi          = {geo['Phi']:.15f}")
        print(f"alpha        = {geo['alpha']:.15f}")
        print(f"P_GEO        = {geo['P_GEO']:.15f}")
        print(f"H0_GEO       = {geo['H0_GEO']:.15f}")
        print("----------------------------------------------------")

        if abs(geo["R"] ** 3 - geo["mu_eff"]) > 1e-12:
            raise RuntimeError("R^3 = mu_eff identity failed")

        expected = geo["P_GEO"] * geo["H0_primitive"]

        if abs(geo["H0_GEO"] - expected) > 1e-12:
            raise RuntimeError("H0_GEO transformation failed")

        print("GEO THEORY -> EXTERNAL CONSUMER = PASS")
        print("====================================================")
        print()

        return 0.0
