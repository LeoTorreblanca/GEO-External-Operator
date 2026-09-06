import ctypes
from pathlib import Path

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

geo = ctypes.CDLL(str(LIB))

geo.geo_public_api_version.argtypes = []
geo.geo_public_api_version.restype = ctypes.c_int

geo.geo_public_compute.argtypes = [
    ctypes.c_double,
    ctypes.c_double,
    ctypes.c_double,
    ctypes.POINTER(GeoResult),
]

geo.geo_public_compute.restype = ctypes.c_int

result = GeoResult()

status = geo.geo_public_compute(
    0.6,
    0.0,
    0.81,
    ctypes.byref(result),
)

print("========================================")
print(" PYTHON -> LIBGEO")
print("========================================")
print("API version =", geo.geo_public_api_version())
print("status      =", status)
print()
print("eta         =", f"{result.eta:.15f}")
print("mu_eff      =", f"{result.mu_eff:.15f}")
print("R           =", f"{result.R:.15f}")
print("R^3         =", f"{result.R**3:.15f}")
print("Phi         =", f"{result.Phi:.15f}")
print("alpha       =", f"{result.alpha:.15f}")
print()
print("P_O         =", f"{result.projected_observable:.15f}")
print("P_C         =", f"{result.projected_complementary:.15f}")
print()
print("F_O rec     =", f"{result.reconstructed_observable:.15f}")
print("F_C rec     =", f"{result.reconstructed_complementary:.15f}")
print()

if status != 0:
    raise SystemExit("PYTHON -> LIBGEO = FAIL")

if abs(result.R**3 - result.mu_eff) > 1e-12:
    raise SystemExit("R^3 = mu_eff = FAIL")

if result.projection_norm_error > 1e-12:
    raise SystemExit("projection norm = FAIL")

if result.reconstruction_observable_error > 1e-12:
    raise SystemExit("observable reconstruction = FAIL")

if result.reconstruction_complementary_error > 1e-12:
    raise SystemExit("complementary reconstruction = FAIL")

print("----------------------------------------")
print("PYTHON -> LIBGEO = PASS")
print("========================================")
