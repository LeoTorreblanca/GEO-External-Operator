#include "geo_engine.h"


int geo_build_residual_candidate_v1(
  struct geo_state *geo
) {

  double B5;
  double correction;
  double rho_hol;


  if (geo == NULL)
    return 1;

  /*
   * Residual memory belongs downstream of the
   * closed harmonic ring.
   */
  if (geo->ring_closed == 0)
    return 2;


  /*
   * ============================================================
   * GEO RESIDUAL MEMORY
   *
   * Historical candidate-v1 realization.
   *
   * IMPORTANT:
   *
   * The architecture is now FULL GEO, but this explicit q
   * closure remains labelled candidate-v1 until a more primitive
   * derivation replaces it.
   * ============================================================
   */


  /*
   * Conservative / effectiveness gap.
   *
   * Historical realization:
   *
   *   gap = 1 - R
   */

  geo->gap =
    1.0
    -
    geo->R;


  /*
   * First residual recurrence:
   *
   *   B5 = B^5
   */

  B5 =
    pow(
      geo->B,
      5.0
    );


  /*
   * Ring closure correction:
   *
   *   correction = 1 - B^5/4
   */

  correction =
    1.0
    -
    B5 / 4.0;


  /*
   * Closure transport parameter:
   *
   *   t =
   *
   *   theta_ring
   *   +
   *   (gap / 100)
   *   *
   *   correction
   */

  geo->closure_t =
    geo->theta
    +
    (geo->gap / 100.0)
    *
    correction;


  /*
   * Holonomy spectral radius:
   *
   *   rho_hol = exp(t)
   */

  rho_hol =
    exp(
      geo->closure_t
    );


  /*
   * Residual return:
   *
   *   q =
   *
   *   B^5
   *   *
   *   [rho_hol - 1]
   */

  geo->q =
    B5
    *
    (
      rho_hol
      -
      1.0
    );


  geo->residual_closed = 1;

  return 0;
}
