#include "geo_engine.h"


int geo_project_forward(
  struct geo_state *geo
) {

  double FO;
  double FC;


  if (geo == NULL)
    return 1;

  /*
   * Projection belongs downstream of the complete organized
   * internal GEO state.
   */
  if (geo->observable_closed == 0)
    return 2;

  if (geo->tangent_closed == 0)
    return 3;


  FO =
    geo->focus_observable;

  FC =
    geo->focus_complementary;


  /*
   * ============================================================
   * GEO FORWARD PROJECTION
   *
   *           [ FO ]
   *   P = Q * [    ]
   *           [ FC ]
   *
   * Q is the tangent / membrane orthogonal operator already
   * constructed by the geometric layer.
   * ============================================================
   */

  geo->projected_observable =
    geo->Q[0][0] * FO
    +
    geo->Q[0][1] * FC;


  geo->projected_complementary =
    geo->Q[1][0] * FO
    +
    geo->Q[1][1] * FC;


  /*
   * Latent / residual content remains explicit.
   *
   * Projection does not silently destroy L.
   */
  geo->projected_latent =
    geo->L;


  /*
   * Orthogonal projection norm audit.
   */

  geo->projection_norm_input =
    FO * FO
    +
    FC * FC;


  geo->projection_norm_output =
    geo->projected_observable
    *
    geo->projected_observable
    +
    geo->projected_complementary
    *
    geo->projected_complementary;


  geo->projection_norm_error =
    fabs(
      geo->projection_norm_output
      -
      geo->projection_norm_input
    );


  geo->projection_closed = 1;

  return 0;
}
