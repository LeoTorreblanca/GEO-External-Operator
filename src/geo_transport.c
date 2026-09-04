#include "geo_engine.h"


int geo_build_M5(
  struct geo_state *geo
) {

  int i;
  int j;

  double O_diag;
  double C_value;
  double S_diag;

  if (geo == NULL)
    return 1;

  if (geo->core_closed == 0)
    return 2;

  if (geo->residual_closed == 0)
    return 3;

  /*
   * Canonical GEO transport realization
   *
   * M5(q) =
   *
   * [ O3    C   ]
   * [ C^T  SB2  ]
   *
   * O3 = (eta/B) I3
   *
   * C  = fc/sqrt(6) * 1_(3x2)
   *
   * SB2 =
   *
   * [ B R   q ]
   * [  q   B R]
   */

  O_diag =
    geo->eta / geo->B;

  C_value =
    geo->fc / sqrt(6.0);

  S_diag =
    geo->B * geo->R;

  /*
   * Clear matrix
   */

  for (i = 0; i < GEO_DIM; i++) {
    for (j = 0; j < GEO_DIM; j++) {
      geo->M5[i][j] = 0.0;
    }
  }

  /*
   * O3 block
   */

  for (i = 0; i < 3; i++) {
    geo->M5[i][i] = O_diag;
  }

  /*
   * Coupling block C and C^T
   */

  for (i = 0; i < 3; i++) {
    for (j = 3; j < 5; j++) {

      geo->M5[i][j] =
        C_value;

      geo->M5[j][i] =
        C_value;
    }
  }

  /*
   * Complementary sector B2
   */

  geo->M5[3][3] = S_diag;
  geo->M5[4][4] = S_diag;

  geo->M5[3][4] = geo->q;
  geo->M5[4][3] = geo->q;

  geo->transport_closed = 1;

  return 0;
}
