#include "geo_engine.h"
#include "geo_public.h"

int geo_public_api_version(void) {
    return GEO_PUBLIC_API_VERSION;
}

int geo_public_compute(
    double eta,
    double L,
    double mu_eff,
    struct geo_result *result
) {
    struct geo_state geo;
    int status;

    if (result == NULL)
        return 100;

    status = geo_compute_full_chain(
        &geo,
        eta,
        L,
        mu_eff
    );

    if (status != 0)
        return status;

    result->eta = geo.eta;
    result->L = geo.L;
    result->mu_eff = geo.mu_eff;

    result->R = geo.R;
    result->Phi = geo.Phi;
    result->alpha = geo.alpha;

    result->projected_observable =
        geo.projected_observable;

    result->projected_complementary =
        geo.projected_complementary;

    result->projected_latent =
        geo.projected_latent;

    result->reconstructed_observable =
        geo.reconstructed_observable;

    result->reconstructed_complementary =
        geo.reconstructed_complementary;

    result->reconstructed_latent =
        geo.reconstructed_latent;

    result->projection_norm_error =
        geo.projection_norm_error;

    result->reconstruction_observable_error =
        geo.reconstruction_observable_error;

    result->reconstruction_complementary_error =
        geo.reconstruction_complementary_error;

    result->reconstruction_latent_error =
        geo.reconstruction_latent_error;

    return 0;
}
