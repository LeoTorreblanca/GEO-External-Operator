import ctypes
from pathlib import Path

from cobaya.theory import Theory


LIB = (
    Path.home()
    / "GEO_CLASS"
    / "geo_engine_public_v1"
    / "libgeo_public.so"
)


class GeoResult(ctypes.Structure):
    _fields_ = [
        ("eta", ctypes.c_double),
        ("L", ctypes.c_double),
        ("mu_eff", ctypes.c_double),

        ("R", ctypes.c_double),
        ("Phi", ctypes.c_double),
        ("alpha", ctypes.c_double),

        ("projected_observable", ctypes.c_double),
        ("projected_complementary", ctypes.c_double),
        ("projected_latent", ctypes.c_double),

        ("reconstructed_observable", ctypes.c_double),
        ("reconstructed_complementary", ctypes.c_double),
        ("reconstructed_latent", ctypes.c_double),

        ("projection_norm_error", ctypes.c_double),
        ("reconstruction_observable_error", ctypes.c_double),
        ("reconstruction_complementary_error", ctypes.c_double),
        ("reconstruction_latent_error", ctypes.c_double),
    ]


class GEOHubbleTheory(Theory):

    # Hubble-specific application hypothesis.
    # This does NOT define the universal relation mu_eff = eta.
    ETA_HUBBLE = 0.6
    L_HUBBLE = 0.0

    def initialize(self):
        self.lib = ctypes.CDLL(str(LIB))

        self.lib.geo_public_compute.argtypes = [
            ctypes.c_double,
            ctypes.c_double,
            ctypes.c_double,
            ctypes.POINTER(GeoResult),
        ]
        self.lib.geo_public_compute.restype = ctypes.c_int

    def get_requirements(self):
        return {
            "Hubble": {
                "z": [0.0]
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

    def calculate(self, state, want_derived=True, **params_values_dict):

        H = self.provider.get_Hubble(
            [0.0],
            units="km/s/Mpc"
        )

        H0_primitive = float(H[0])

        eta = self.ETA_HUBBLE
        L = self.L_HUBBLE

        # Application-specific Hubble realization:
        # mu_H := eta.
        mu_H = eta

        result = GeoResult()

        status = self.lib.geo_public_compute(
            eta,
            L,
            mu_H,
            ctypes.byref(result),
        )

        if status != 0:
            return False

        P_GEO = 1.0 + result.alpha * (1.0 - result.R)
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
