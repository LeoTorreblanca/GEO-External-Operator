from geo_external_operator import api_version, compute, find_library


def main():
    eta = 0.6
    latent = 0.0
    mu_eff = 0.81

    result = compute(
        eta=eta,
        L=latent,
        mu_eff=mu_eff,
    )

    print("========================================")
    print(" PYTHON -> LIBGEO")
    print("========================================")
    print("API version =", api_version())
    print("library     =", find_library())
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


if __name__ == "__main__":
    main()
