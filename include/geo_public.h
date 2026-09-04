#ifndef GEO_PUBLIC_H
#define GEO_PUBLIC_H

#ifdef __cplusplus
extern "C" {
#endif

#define GEO_PUBLIC_API_VERSION 1

struct geo_result {
    double eta;
    double L;
    double mu_eff;

    double R;
    double Phi;
    double alpha;

    double projected_observable;
    double projected_complementary;
    double projected_latent;

    double reconstructed_observable;
    double reconstructed_complementary;
    double reconstructed_latent;

    double projection_norm_error;
    double reconstruction_observable_error;
    double reconstruction_complementary_error;
    double reconstruction_latent_error;
};

int geo_public_compute(
    double eta,
    double L,
    double mu_eff,
    struct geo_result *result
);

int geo_public_api_version(void);

#ifdef __cplusplus
}
#endif

#endif
