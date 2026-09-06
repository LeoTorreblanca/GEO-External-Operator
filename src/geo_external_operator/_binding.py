import ctypes
import sys
from importlib.metadata import files as distribution_files
from pathlib import Path


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


def _library_names():
    if sys.platform.startswith("linux"):
        return ["libgeo_public.so"]

    if sys.platform == "darwin":
        return [
            "libgeo_public.dylib",
            "libgeo_public.so",
        ]

    if sys.platform == "win32":
        return [
            "geo_public.dll",
            "libgeo_public.dll",
        ]

    return [
        "libgeo_public.so",
        "libgeo_public.dylib",
        "geo_public.dll",
        "libgeo_public.dll",
    ]


def _library_candidates():
    candidates = []

    # Normal wheel/non-editable installation: the native library
    # normally lives beside this Python module.
    package_dir = Path(__file__).resolve().parent

    for name in _library_names():
        candidates.append(package_dir / name)

    # Editable scikit-build-core installation: Python sources can remain
    # in src/, while CMake-installed native artifacts live in site-packages.
    try:
        installed_files = distribution_files("geo-external-operator")

        if installed_files is not None:
            for entry in installed_files:
                entry_text = str(entry).replace("\\", "/")

                for name in _library_names():
                    if entry_text.endswith(
                        f"geo_external_operator/{name}"
                    ):
                        candidates.append(
                            Path(entry.locate()).resolve()
                        )
    except Exception:
        pass

    # Preserve order while removing duplicates.
    unique = []

    for candidate in candidates:
        if candidate not in unique:
            unique.append(candidate)

    return unique


def find_library():
    candidates = _library_candidates()

    for candidate in candidates:
        if candidate.is_file():
            return candidate

    expected = "\n".join(
        f"  - {candidate}"
        for candidate in candidates
    )

    raise FileNotFoundError(
        "GEO native library was not found.\n"
        "Expected one of:\n"
        f"{expected}"
    )


def load_library():
    lib = ctypes.CDLL(str(find_library()))

    lib.geo_public_api_version.argtypes = []
    lib.geo_public_api_version.restype = ctypes.c_int

    lib.geo_public_compute.argtypes = [
        ctypes.c_double,
        ctypes.c_double,
        ctypes.c_double,
        ctypes.POINTER(GeoResult),
    ]

    lib.geo_public_compute.restype = ctypes.c_int

    return lib


_LIB = None


def get_library():
    global _LIB

    if _LIB is None:
        _LIB = load_library()

    return _LIB


def api_version():
    return int(
        get_library().geo_public_api_version()
    )


def compute(eta, L, mu_eff):
    result = GeoResult()

    status = get_library().geo_public_compute(
        float(eta),
        float(L),
        float(mu_eff),
        ctypes.byref(result),
    )

    if status != 0:
        raise RuntimeError(
            f"geo_public_compute failed with status {status}"
        )

    return result
