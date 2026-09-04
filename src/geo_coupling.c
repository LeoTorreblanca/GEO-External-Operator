#include "geo_engine.h"


int geo_build_coupling_geometry(
  struct geo_state *geo
) {

  if (geo == NULL)
    return 1;

  /*
   * Coupling geometry belongs downstream of the
   * membrane / tangent interface.
   */
  if (geo->tangent_closed == 0)
    return 2;

  /*
   * Canonical efficiency domain.
   */
  if (geo->eta <= 0.0 || geo->eta > 1.0)
    return 3;


  /*
   * ============================================================
   * GEO COUPLING GEOMETRY
   *
   * Coupling-eccentricity proxy:
   *
   *   e = sqrt(1 - eta)
   *
   * Perfect coupling:
   *
   *   eta = 1
   *   e   = 0
   *   circle
   *
   * Imperfect / anisotropic coupling:
   *
   *   0 < eta < 1
   *   e > 0
   *   ellipse
   * ============================================================
   */

  geo->coupling_eccentricity =
    sqrt(
      1.0
      -
      geo->eta
    );


  if (
    geo->coupling_eccentricity
    <= 1.0e-15
  ) {

    geo->coupling_regime =
      GEO_COUPLING_PERFECT;
  }

  else {

    geo->coupling_regime =
      GEO_COUPLING_ELLIPTIC;
  }


  /*
   * FULL GEO architecture does not impose explicit ellipse
   * semi-axes at this stage.
   *
   * Physical/application realizations may construct them later.
   */

  geo->coupling_axis_a =
    0.0;

  geo->coupling_axis_b =
    0.0;


  /*
   * Internal identity audit:
   *
   *   e^2 + eta = 1
   */

  geo->coupling_geometry_error =
    fabs(
      geo->coupling_eccentricity
      *
      geo->coupling_eccentricity
      +
      geo->eta
      -
      1.0
    );


  geo->coupling_closed = 1;

  return 0;
}
