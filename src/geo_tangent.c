#include "geo_engine.h"


int geo_build_tangent_interface(
  struct geo_state *geo
) {

  double c;
  double s;

  double qtq00;
  double qtq01;
  double qtq10;
  double qtq11;

  double detQ;


  if (geo == NULL)
    return 1;

  if (geo->bifocal_closed == 0)
    return 2;


  /*
   * ============================================================
   * GEO MEMBRANE / TANGENT INTERFACE
   * ============================================================
   *
   * Symmetric equilibrium:
   *
   *   theta_membrane = pi/4
   *
   * This is the balanced orthogonal interface between the
   * observable and complementary bifocal sectors.
   * ============================================================
   */

  geo->theta_membrane =
    M_PI / 4.0;


  /*
   * Tangent conservative redistribution.
   *
   * We store the neutral equilibrium redistribution here:
   *
   *   delta_O = 0
   *   delta_C = 0
   *
   * which satisfies:
   *
   *   delta_O + delta_C = 0
   *
   * Physical/application departures may populate these values
   * later without changing the tangent conservation law.
   */

  geo->tangent_delta_observable =
    0.0;

  geo->tangent_delta_complementary =
    0.0;

  geo->tangent_conservation_error =
    fabs(
      geo->tangent_delta_observable
      +
      geo->tangent_delta_complementary
    );


  /*
   * ============================================================
   * TANGENT / MEMBRANE ORTHOGONAL OPERATOR Q
   * ============================================================
   */

  c =
    cos(
      geo->theta_membrane
    );

  s =
    sin(
      geo->theta_membrane
    );


  geo->Q[0][0] =  c;
  geo->Q[0][1] =  s;

  geo->Q[1][0] = -s;
  geo->Q[1][1] =  c;


  /*
   * Audit Q^T Q = I.
   */

  qtq00 =
    geo->Q[0][0] * geo->Q[0][0]
    +
    geo->Q[1][0] * geo->Q[1][0];

  qtq01 =
    geo->Q[0][0] * geo->Q[0][1]
    +
    geo->Q[1][0] * geo->Q[1][1];

  qtq10 =
    geo->Q[0][1] * geo->Q[0][0]
    +
    geo->Q[1][1] * geo->Q[1][0];

  qtq11 =
    geo->Q[0][1] * geo->Q[0][1]
    +
    geo->Q[1][1] * geo->Q[1][1];


  geo->Q_orthogonality_error =
    fmax(
      fmax(
        fabs(qtq00 - 1.0),
        fabs(qtq01)
      ),
      fmax(
        fabs(qtq10),
        fabs(qtq11 - 1.0)
      )
    );


  /*
   * Audit det(Q) = +1.
   */

  detQ =
    geo->Q[0][0] * geo->Q[1][1]
    -
    geo->Q[0][1] * geo->Q[1][0];

  geo->Q_determinant_error =
    fabs(
      detQ
      -
      1.0
    );


  geo->tangent_closed = 1;

  return 0;
}
