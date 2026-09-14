import argparse

from geo_external_operator import api_version, compute, find_library


def line():
    print("=" * 68)


def parse_args():
    parser = argparse.ArgumentParser(
        description="Run the GEO External Operator with a user-defined state."
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
        default=0.81,
        help="Effective application state mu_eff (default: 0.81)",
    )

    return parser.parse_args()


def main():
    args = parse_args()

    result = compute(
        eta=args.eta,
        L=args.L,
        mu_eff=args.mu_eff,
    )

    radial_error = abs(result.R**3 - result.mu_eff)

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

    print("\n[PROJECTED STATE]")
    print(
        f"observable                   = "
        f"{result.projected_observable:.15f}"
    )
    print(
        f"complementary                = "
        f"{result.projected_complementary:.15f}"
    )
    print(
        f"latent                       = "
        f"{result.projected_latent:.15f}"
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

    radial_pass = radial_error < 1.0e-12
    projection_pass = result.projection_norm_error < 1.0e-12
    reconstruction_pass = max(
        result.reconstruction_observable_error,
        result.reconstruction_complementary_error,
        result.reconstruction_latent_error,
    ) < 1.0e-12

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

    line()

    if radial_pass and projection_pass and reconstruction_pass:
        print(" GEO PUBLIC ENGINE = PASS")
    else:
        print(" GEO PUBLIC ENGINE = FAIL")
        raise SystemExit(1)

    line()


if __name__ == "__main__":
    main()
