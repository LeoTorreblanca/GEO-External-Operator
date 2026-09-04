#include "geo_engine.h"


int geo_build_harmonic_ring(
  struct geo_state *geo
) {

  if (geo == NULL)
    return 1;

  /*
   * The ring belongs downstream of harmonic duality.
   */
  if (geo->harmonic_dual_closed == 0)
    return 2;

  /*
   * ============================================================
   * GEO HARMONIC RING
   * ============================================================
   *
   * The historical field geo->theta is retained for numerical
   * and regression compatibility.
   *
   * In FULL GEO it is no longer independently defined.
   *
   * The closed ring inherits the harmonic phase:
   *
   *   theta_ring = theta_harmonic
   *
   * and therefore, in symmetric equilibrium:
   *
   *   theta_ring = theta_membrane = pi/4
   * ============================================================
   */

  geo->theta =
    geo->theta_harmonic;

  geo->ring_closed = 1;

  return 0;
}
