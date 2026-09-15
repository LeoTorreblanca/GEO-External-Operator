import argparse
import math

from geo_external_operator import api_version, compute, find_library


def line():
    print("=" * 72)


def parse_args():
    parser = argparse.ArgumentParser(
        description=(
            "Run the GEO External Operator and display both the canonical "
            "engine projection and the derived GEO-Hubble projection ratio."
        )
    )

    parser.add_argument(
        "--eta",
        type=float,
        default=0.60,
        help="GEO partition parameter eta (default: 0.60)",
    )

    parser.add_argument(
        "--L",
        type=float,
        default=0.00,
        help="Latent component L (default: 0.00)",
    )

    parser.add_argument(
        "--mu",
        dest="mu_eff",
        type=float,
        default=0.8104,
        help="Effective application state mu_eff (default: 0.8104)",
    )

    return parser.parse_args()


def main():
    args = parse_args()

    result = compute(
        eta=args.eta,
        L=args.L,
        mu_eff=args.mu_eff,
    )

    # ---------------------------------------------------------
    # Core GEO audits
    # ---------------------------------------------------------

    radial_error = abs(result.R**3 - result.mu_eff)

    radial_pass = radial_error < 1.0e-12
    projection_pass = result.projection_norm_error < 1.0e-12

    reconstruction_pass = max(
        result.reconstruction_observable_error,
        result.reconstruction_complementary_error,
        result.reconstruction_latent_error,
    ) < 1.0e-12

    # ---------------------------------------------------------
    # Canonical GEO projection quantities
    #
    # eta = f_c^2
    # f_c = sqrt(eta)
    #
    # The public engine already returns the first projected
    # coordinate:
    #
    # A'_engine = projected_observable
    #
    # For the canonical conservative state eta=0.6, L=0:
    #
    # theta_M = pi/4
    # A'_engine = 1/sqrt(2)
    #
    # GEO-Hubble then defines the application-level ratio
    #
    # P_GEO = f_c / A'_engine
    #
    # which closes analytically to sqrt(6/5).
    # ---------------------------------------------------------

    theta_canonical_rad = math.pi / 4.0
    theta_canonical_deg = math.degrees(theta_canonical_rad)

    fc = math.sqrt(result.eta)

    projected_observable_engine = result.projected_observable

    if abs(projected_observable_engine) < 1.0e-15:
        raise SystemExit(
            "Cannot construct projection ratio: "
            "projected observable is numerically zero."
        )

    projection_ratio_engine = (
        fc / projected_observable_engine
    )

    # Analytic canonical reference for eta = 3/5.
    projection_ratio_closed = math.sqrt(6.0 / 5.0)

    projection_ratio_error = abs(
        projection_ratio_engine - projection_ratio_closed
    )

    canonical_eta = abs(result.eta - 0.60) < 1.0e-15
    canonical_L = abs(result.L) < 1.0e-15

    canonical_projection_ratio_pass = (
        canonical_eta
        and canonical_L
        and projection_ratio_error < 1.0e-12
    )

    # ---------------------------------------------------------
    # Output
    # ---------------------------------------------------------

    line()
    print(" GEO EXTERNAL OPERATOR — PUBLIC ENGINE DEMONSTRATION")
    line()

    print("\n[LIBRARY]")
    print(f"API version                  = {api_version()}")
    print(f"native library               = {find_library()}")

    print("\n[ENGINE INPUT]")
    print(f"eta                          = {result.eta:.15f}")
    print(f"L                            = {result.L:.15f}")
    print(f"mu_eff                       = {result.mu_eff:.15f}")

    print("\n[GEOMETRIC RESPONSE]")
    print(f"R                            = {result.R:.15f}")
    print(f"R^3                          = {result.R**3:.15f}")
    print(f"|R^3 - mu_eff|               = {radial_error:.3e}")

    print("\n[SPECTRAL / EFFECTIVE OUTPUT]")
    print(f"Phi                          = {result.Phi:.15f}")
    print(f"alpha                        = {result.alpha:.15f}")

    print("\n[CANONICAL MEMBRANE]")
    print(f"theta_M [rad]                = {theta_canonical_rad:.15f}")
    print(f"theta_M [deg]                = {theta_canonical_deg:.15f}")
    print(f"f_c = sqrt(eta)              = {fc:.15f}")

    print("\n[CANONICAL PROJECTED STATE — ENGINE]")
    print(
        f"observable A'                = "
        f"{result.projected_observable:.15f}"
    )
    print(
        f"complementary B'             = "
        f"{result.projected_complementary:.15f}"
    )
    print(
        f"latent                       = "
        f"{result.projected_latent:.15f}"
    )

    print("\n[GEO-HUBBLE PROJECTION RATIO — DERIVED FROM ENGINE]")
    print(
        f"A'_engine                    = "
        f"{projected_observable_engine:.15f}"
    )
    print(
        f"P_GEO engine = f_c / A'      = "
        f"{projection_ratio_engine:.15f}"
    )
    print(
        f"P_GEO closed = sqrt(6/5)     = "
        f"{projection_ratio_closed:.15f}"
    )
    print(
        f"|engine - closed|            = "
        f"{projection_ratio_error:.3e}"
    )

    print("\n[RECONSTRUCTED STATE]")
    print(
        f"observable                   = "
        f"{result.reconstructed_observable:.15f}"
    )
    print(
        f"complementary                = "
        f"{result.reconstructed_complementary:.15f}"
    )
    print(
        f"latent                       = "
        f"{result.reconstructed_latent:.15f}"
    )

    print("\n[ENGINE AUDIT]")
    print(
        f"projection norm error        = "
        f"{result.projection_norm_error:.3e}"
    )
    print(
        f"reconstruction obs. error    = "
        f"{result.reconstruction_observable_error:.3e}"
    )
    print(
        f"reconstruction comp. error   = "
        f"{result.reconstruction_complementary_error:.3e}"
    )
    print(
        f"reconstruction latent error  = "
        f"{result.reconstruction_latent_error:.3e}"
    )

    print("\n[VALIDATION]")
    print(
        f"canonical R^3 = mu_eff       = "
        f"{'PASS' if radial_pass else 'FAIL'}"
    )
    print(
        f"projection norm closure      = "
        f"{'PASS' if projection_pass else 'FAIL'}"
    )
    print(
        f"state reconstruction         = "
        f"{'PASS' if reconstruction_pass else 'FAIL'}"
    )

    if canonical_eta and canonical_L:
        print(
            f"GEO-Hubble ratio closure     = "
            f"{'PASS' if canonical_projection_ratio_pass else 'FAIL'}"
        )
    else:
        print(
            "GEO-Hubble ratio closure     = "
            "N/A (canonical eta=0.6, L=0 required)"
        )

    print("\n[INTERPRETATION]")
    print(
        "canonical engine projection  = "
        "orthogonal GEO membrane projection"
    )
    print(
        "GEO-Hubble projection ratio  = "
        "derived application-level ratio f_c / A'"
    )
    print(
        "radial law                    = "
        "R^3 = mu_eff"
    )
    print(
        "radial/projection coupling    = "
        "NONE in this demonstration"
    )

    line()

    core_pass = (
        radial_pass
        and projection_pass
        and reconstruction_pass
    )

    if core_pass:
        print(" GEO PUBLIC ENGINE = PASS")
    else:
        print(" GEO PUBLIC ENGINE = FAIL")
        raise SystemExit(1)

    line()


if __name__ == "__main__":
    main()
