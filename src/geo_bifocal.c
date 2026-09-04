#include "geo_engine.h"


int geo_build_bifocal_geometry(
  struct geo_state *geo
) {

  if (geo == NULL)
    return 1;

  /*
   * Bifocal organization belongs downstream of the
   * fundamental effectiveness law.
   */
  if (geo->effectiveness_closed == 0)
    return 2;

  /*
   * ============================================================
   * GEO BIFOCAL GEOMETRY
   * ============================================================
   *
   * The decomposed normalized geometry is organized around
   * two complementary centers:
   *
   *   F_O = observable focus
   *   F_C = complementary focus
   *
   * In the normalized decomposition:
   *
   *   F_O = A
   *   F_C = B
   *
   * L remains explicit as latent / residual content.
   *
   * Hence:
   *
   *   F_O + F_C + L = T
   * ============================================================
   */

  geo->focus_observable =
    geo->A;

  geo->focus_complementary =
    geo->B;

  geo->bifocal_sum =
    geo->focus_observable
    +
    geo->focus_complementary;

  geo->bifocal_conservation_error =
    fabs(
      geo->focus_observable
      +
      geo->focus_complementary
      +
      geo->L
      -
      geo->T
    );

  geo->bifocal_closed = 1;

  return 0;
}
