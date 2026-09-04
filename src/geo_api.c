#include "geo_engine.h"

int geo_compute_full_base(
  struct geo_state *geo,
  double eta,
  double L,
  double mu_eff
) {

  int status;

  /*
   * ============================================================
   * FULL GEO BASE RECONSTRUCTION
   *
   * T
   * ↓
   * A, B, L
   * ↓
   * eta, fc
   * ↓
   * mu_eff
   * ↓
   * R^3 = mu_eff
   * ↓
   * compatibility exposure of R
   * ============================================================
   */

  status =
    geo_init(geo);

  if (status != 0)
    return 1;

  status =
    geo_build_architecture(
      geo,
      eta,
      L
    );

  if (status != 0)
    return 2;

  status =
    geo_set_effective_state(
      geo,
      mu_eff
    );

  if (status != 0)
    return 3;

  status =
    geo_compute_effectiveness(
      geo
    );

  if (status != 0)
    return 4;

  /*
   * Temporary Bridge-v3 compatibility exposure.
   *
   * This does not define R.
   * R has already been obtained from:
   *
   *   R^3 = mu_eff
   */
  status =
    geo_compute_foundation_transfer(
      geo
    );

  if (status != 0)
    return 5;
  /*
   * Bifocal organization of the normalized decomposed state.
   */
  status =
    geo_build_bifocal_geometry(
      geo
    );

  if (status != 0)
    return 6;
  status =
    geo_build_tangent_interface(
      geo
    );

  if (status != 0)
    return 7;

  status =
    geo_build_coupling_geometry(
      geo
    );

  if (status != 0)
    return 8;
  return 0;
}
int geo_compute_full_chain(
  struct geo_state *geo,
  double eta,
  double L,
  double mu_eff
) {

  int status;


  /*
   * ============================================================
   * FULL GEO BASE
   * ============================================================
   *
   * Includes:
   *
   *   initialization
   *   normalized / decomposed architecture
   *   eta / fc
   *   application mu_eff
   *   R^3 = mu_eff
   *   compatibility exposure
   *   bifocal geometry
   *   membrane / tangent / Q
   *   coupling geometry
   */

  status =
    geo_compute_full_base(
      geo,
      eta,
      L,
      mu_eff
    );

  if (status != 0)
    return 1;


  /*
   * ============================================================
   * HARMONIC DUAL ORGANIZATION
   * ============================================================
   */

  status =
    geo_compute_harmonic_dual_state(
      geo
    );

  if (status != 0)
    return 2;


  /*
   * ============================================================
   * CLOSED HARMONIC RING
   * ============================================================
   */

  status =
    geo_build_harmonic_ring(
      geo
    );

  if (status != 0)
    return 3;


  /*
   * ============================================================
   * RESIDUAL MEMORY
   *
   * Current explicit q realization remains candidate-v1.
   * ============================================================
   */

  status =
    geo_build_residual_candidate_v1(
      geo
    );

  if (status != 0)
    return 4;


  /*
   * ============================================================
   * 5D CONSERVATIVE TRANSPORT
   * ============================================================
   */

  status =
    geo_build_M5(
      geo
    );

  if (status != 0)
    return 5;


  /*
   * ============================================================
   * SPECTRAL ORGANIZATION
   * ============================================================
   */

  status =
    geo_compute_spectrum(
      geo
    );

  if (status != 0)
    return 6;


  /*
   * ============================================================
   * OBSERVABLE INTENSITY
   * ============================================================
   */

  status =
    geo_compute_observable(
      geo
    );

  if (status != 0)
    return 7;

  /*
   * ============================================================
   * FORWARD PROJECTION
   * ============================================================
   */

  status =
    geo_project_forward(
      geo
    );

  if (status != 0)
    return 8;


  /*
   * ============================================================
   * RECONSTRUCTION / COMPLETION
   * ============================================================
   */

  status =
    geo_reconstruct_completion(
      geo
    );

  if (status != 0)
    return 9;


  return 0;
  return 0;
}

int geo_compute_all_candidate_v1(
  struct geo_state *geo,
  double eta
) {

  int status;

  status =
    geo_init(geo);

  if (status != 0)
    return 1;

  status =
    geo_build_core(
      geo,
      eta
    );

  if (status != 0)
    return 2;

  /*
   * ============================================================
   * HISTORICAL CANDIDATE-v1 REDUCTION
   * ============================================================
   *
   * This is NOT the FULL GEO fundamental architecture.
   *
   * The historical candidate-v1 chain explicitly reproduces:
   *
   *   L      = 0
   *   mu_eff = eta
   *
   * therefore:
   *
   *   R = cbrt(mu_eff)
   *     = cbrt(eta)
   *
   * FULL GEO does NOT assume mu_eff = eta.
   * ============================================================
   */

  status =
    geo_set_effective_state(
      geo,
      eta
    );

  if (status != 0)
    return 3;

  status =
    geo_compute_effectiveness(
      geo
    );

  if (status != 0)
    return 4;
status =
    geo_compute_foundation_transfer(
      geo
    );

  if (status != 0)
    return 5;


  /*
   * Explicit geometric organization required by FULL GEO.
   *
   * The historical candidate-v1 values are preserved,
   * but their previously implicit geometric dependencies
   * are now represented explicitly.
   */

  status =
    geo_build_bifocal_geometry(
      geo
    );

  if (status != 0)
    return 6;


  status =
    geo_build_tangent_interface(
      geo
    );

  if (status != 0)
    return 7;


  status =
    geo_build_coupling_geometry(
      geo
    );

  if (status != 0)
    return 8;


  status =
    geo_compute_harmonic_dual_state(
      geo
    );

  if (status != 0)
    return 9;

  status =
    geo_build_harmonic_ring(
      geo
    );

  if (status != 0)
    return 10;

  status =
    geo_build_residual_candidate_v1(
      geo
    );

  if (status != 0)
    return 11;


  status =
    geo_build_M5(
      geo
    );

  if (status != 0)
    return 12;


  status =
    geo_compute_spectrum(
      geo
    );

  if (status != 0)
    return 13;


  status =
    geo_compute_observable(
      geo
    );

  if (status != 0)
    return 14;


  return 0;
}


int geo_validate(
  struct geo_state *geo,
  double tolerance
) {

  const double PHI_REFERENCE =
    1.88961381521168;

  const double ALPHA_REFERENCE =
    0.534463497024;

  if (geo == NULL)
    return 1;

if (
  geo->core_closed == 0
  ||
  geo->effective_state_ready == 0
  ||
  geo->effectiveness_closed == 0
  ||
  geo->foundation_transfer_closed == 0
  ||
  geo->residual_closed == 0
  ||
  geo->ring_closed == 0
  ||
  geo->harmonic_dual_closed == 0
  ||
  geo->transport_closed == 0
  ||
  geo->spectral_closed == 0
  ||
  geo->observable_closed == 0
)
  return 2;

geo->conservation_error =
  fabs(
    geo->A
    +
    geo->B
    +
    geo->L
    -
    geo->T
  );

  geo->phi_reference_error =
    fabs(
      geo->Phi
      -
      PHI_REFERENCE
    );

  geo->alpha_reference_error =
    fabs(
      geo->alpha
      -
      ALPHA_REFERENCE
    );

  if (
    geo->conservation_error
    >
    tolerance
  )
    return 3;
/*
 * GEO v3 harmonic / dual identity audit
 */

if (
geo->theta_harmonic_ring_error
>
tolerance
)
return 4;

if (
geo->harmonic_sum_error
>
tolerance
)
return 5;

if (
geo->dual_balance_identity_error
>
tolerance
)
return 6;

if (
geo->dual_coupling_identity_error
>
tolerance
)
return 7;

  /*
   * Reference values come from the historical closure
   * candidate, so they are diagnostic rather than
   * primitive identities.
   */

  return 0;
}


void geo_print(
  const struct geo_state *geo
) {

  int i;
  int j;

  if (geo == NULL)
    return;

  printf("\n");
  printf("========================================\n");
  printf("GEO INTERNAL GEOMETRIC ENGINE\n");
  printf("========================================\n");

  printf("\n");
  printf("Primitive / partition\n");
  printf("----------------------------------------\n");

  printf("T         = %.15f\n", geo->T);
printf("eta       = %.15f\n", geo->eta);

printf("A         = %.15f\n", geo->A);
printf("B         = %.15f\n", geo->B);
printf("L         = %.15f\n", geo->L);

printf(
  "A+B+L     = %.15f\n",
  geo->A + geo->B + geo->L
);

if (fabs(geo->B) > 0.0) {
  printf(
    "A/B       = %.15f\n",
    geo->A / geo->B
  );
}

  printf("\n");
  printf("Canonical operators\n");
  printf("----------------------------------------\n");

  printf("fc        = %.15f\n", geo->fc);
  printf("R         = %.15f\n", geo->R);
printf(
  "transfer  = %.15f\n",
  geo->transfer_efficiency
);

  printf("\n");
  printf("Residual closure candidate v1\n");
  printf("----------------------------------------\n");

  printf("theta     = %.15f\n", geo->theta);
  printf("gap       = %.15f\n", geo->gap);
  printf("t         = %.15f\n", geo->closure_t);
  printf("q         = %.15f\n", geo->q);
printf("\n");
printf("Harmonic / dual state v3\n");
printf("----------------------------------------\n");

printf(
"theta_harmonic       = %.15f\n",
geo->theta_harmonic
);

printf(
"harmonic_observable  = %.15f\n",
geo->harmonic_observable
);

printf(
"harmonic_complement  = %.15f\n",
geo->harmonic_complementary
);

printf(
"harmonic_sum         = %.15f\n",
geo->harmonic_sum
);

printf(
"dual_balance         = %.15f\n",
geo->dual_balance
);

printf(
"dual_coupling        = %.15f\n",
geo->dual_coupling
);

printf("\n");
printf("Harmonic / dual audit\n");
printf("----------------------------------------\n");

printf(
"theta-ring error     = %.15e\n",
geo->theta_harmonic_ring_error
);

printf(
"harmonic sum error   = %.15e\n",
geo->harmonic_sum_error
);

printf(
"dual balance error   = %.15e\n",
geo->dual_balance_identity_error
);

printf(
"dual coupling error  = %.15e\n",
geo->dual_coupling_identity_error
);


  printf("\n");
  printf("M5(q)\n");
  printf("----------------------------------------\n");

  for (i = 0; i < GEO_DIM; i++) {

    for (j = 0; j < GEO_DIM; j++) {

      printf(
        "% .12f ",
        geo->M5[i][j]
      );
    }

    printf("\n");
  }

  printf("\n");
  printf("Eigenvalues\n");
  printf("----------------------------------------\n");

  for (i = 0; i < GEO_DIM; i++) {

    printf(
      "lambda_%d = %.15f\n",
      i + 1,
      geo->eigenvalues[i]
    );
  }

  printf("\n");
  printf("Spectral / observable\n");
  printf("----------------------------------------\n");

  printf("Phi       = %.15f\n", geo->Phi);
  printf("alpha     = %.15f\n", geo->alpha);

  printf("\n");
  printf("Audit\n");
  printf("----------------------------------------\n");

  printf(
    "A+B error     = %.15e\n",
    geo->conservation_error
  );

  printf(
    "Phi ref error = %.15e\n",
    geo->phi_reference_error
  );

  printf(
    "alpha ref err = %.15e\n",
    geo->alpha_reference_error
  );

  printf("\n");
  printf("========================================\n");
}
