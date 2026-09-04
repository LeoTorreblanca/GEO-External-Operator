#include <stdio.h>
#include "geo_engine.h"

int main(void) {

    struct geo_state geo;
    int status;

    const double eta = 0.6;
    const double L = 0.0;
    const double mu_eff = 0.81;

    status = geo_compute_full_chain(
        &geo,
        eta,
        L,
        mu_eff
    );

    if (status != 0) {
        printf("ERROR geo_compute_full_chain: %d\n", status);
        return 1;
    }

    printf("========================================\n");
    printf(" EXTERNAL LIBGEO TEST\n");
    printf("========================================\n");

    printf("eta      = %.15f\n", geo.eta);
    printf("mu_eff   = %.15f\n", geo.mu_eff);
    printf("R        = %.15f\n", geo.R);
    printf("R^3      = %.15f\n", geo.R * geo.R * geo.R);

    printf("Phi      = %.15f\n", geo.Phi);
    printf("alpha    = %.15f\n", geo.alpha);

    printf("P_O      = %.15f\n", geo.projected_observable);
    printf("P_C      = %.15f\n", geo.projected_complementary);

    printf("F_O rec  = %.15f\n", geo.reconstructed_observable);
    printf("F_C rec  = %.15f\n", geo.reconstructed_complementary);

    status = geo_validate(
        &geo,
        1e-12
    );

    if (status != 0) {
        printf("geo_validate = FAIL (%d)\n", status);
        return 2;
    }

    printf("----------------------------------------\n");
    printf("EXTERNAL LIBGEO = PASS\n");
    printf("========================================\n");

    return 0;
}
