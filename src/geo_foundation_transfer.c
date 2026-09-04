#include "geo_engine.h"


int geo_set_effective_state(
  struct geo_state *geo,
  double mu_eff
) {

  if (geo == NULL)
    return 1;

  if (geo->core_closed == 0)
    return 2;

  /*
   * GEO effective input is normalized and positive.
   *
   * It belongs to the concrete application realization
   * and must NOT be inferred from eta.
   */
  if (mu_eff <= 0.0 || mu_eff > 1.0)
    return 3;

  geo->mu_eff =
    mu_eff;

  geo->effective_state_ready = 1;

  return 0;
}


int geo_compute_effectiveness(
  struct geo_state *geo
) {

  if (geo == NULL)
    return 1;

  if (geo->core_closed == 0)
    return 2;

  if (geo->effective_state_ready == 0)
    return 3;

  /*
   * ============================================================
   * GEO FUNDAMENTAL LAW OF GEOMETRIC EFFECTIVENESS
   *
   * Application effective state:
   *
   *   mu_eff
   *
   * Fundamental response:
   *
   *   R^3 = mu_eff
   *
   * therefore
   *
   *   R = cbrt(mu_eff)
   *
   * eta and mu_eff are independent levels of the GEO pipeline.
   * No identity mu_eff = eta is assumed here.
   * ============================================================
   */

  geo->R =
    cbrt(
      geo->mu_eff
    );

  geo->effectiveness_closed = 1;

  return 0;
}


/*
 * ============================================================
 * LEGACY BRIDGE-v3 COMPATIBILITY WRAPPER
 * ============================================================
 *
 * Historically this routine exposed the reconstructed GEO
 * transfer state to the CLASS-facing bridge.
 *
 * In FULL GEO the fundamental law is already computed by
 * geo_compute_effectiveness().
 *
 * transfer_efficiency is retained temporarily as a compatibility
 * field only. It is NOT a primitive GEO operator and must not be
 * used to rescale primitive CLASS perturbations.
 * ============================================================
 */

int geo_compute_foundation_transfer(
  struct geo_state *geo
) {

  if (geo == NULL)
    return 1;

  if (geo->effectiveness_closed == 0)
    return 2;

  geo->transfer_efficiency =
    geo->R;

  geo->foundation_transfer_closed = 1;

  return 0;
}
