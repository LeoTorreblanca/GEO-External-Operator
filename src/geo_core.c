#include "geo_engine.h"

#include <string.h>


int geo_init(
  struct geo_state *geo
) {

  if (geo == NULL)
    return 1;

  memset(
    geo,
    0,
    sizeof(struct geo_state)
  );

  return 0;
}


int geo_build_architecture(
  struct geo_state *geo,
  double eta,
  double L
) {

  if (geo == NULL)
    return 1;

  /*
   * The primitive partition requires
   *
   * 0 < eta < 1
   *
   * so that both conservative sectors exist.
   */
  if (eta <= 0.0 || eta >= 1.0)
    return 2;
  /*
   * L is a normalized latent / residual contribution.
   *
   * The decomposed geometry requires:
   *
   *   0 <= L < 1
   *
   * and enough remaining complement to preserve B >= 0.
   */
  if (L < 0.0 || L >= 1.0)
    return 3;

  if ((eta + L) > 1.0)
    return 4;
  /*
   * =========================================================
   * FULL GEO NORMALIZED TOTAL
   *
   * T = 1
   * =========================================================
   */

  geo->T = 1.0;
  geo->eta = eta;

  /*
   * =========================================================
   * GEO CONSERVATIVE PARTITION
   *
   * A = eta
   * B = 1 - eta
   * A + B = 1
   * =========================================================
   */
  geo->A = eta;
  geo->L = L;

  geo->B =
    geo->T
    - geo->A
    - geo->L;
  /*
   * =========================================================
   * CANONICAL COUPLING FACTOR
   *
   * fc = sqrt(eta)
   * =========================================================
   */

  geo->fc = sqrt(eta);



  /*
   * =========================================================
   * BASIC AUDIT
   * =========================================================
   */

geo->conservation_error =
  fabs(
    (geo->A + geo->B + geo->L)
    - geo->T
  );

  geo->core_closed = 1;

  return 0;
}
/*
 * ============================================================
 * HISTORICAL TWO-SECTOR COMPATIBILITY WRAPPER
 * ============================================================
 *
 * The reduced Bridge-v3 realization used L = 0.
 *
 * FULL GEO applications should call
 * geo_build_architecture() explicitly.
 * ============================================================
 */

int geo_build_core(
  struct geo_state *geo,
  double eta
) {

  return geo_build_architecture(
    geo,
    eta,
    0.0
  );
}
