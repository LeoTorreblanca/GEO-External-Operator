#include "geo_engine.h"


int geo_reconstruct_completion(
  struct geo_state *geo
) {

  double PO;
  double PC;


  if (geo == NULL)
    return 1;

  if (geo->projection_closed == 0)
    return 2;


  PO =
    geo->projected_observable;

  PC =
    geo->projected_complementary;


  /*
   * ============================================================
   * GEO RECONSTRUCTION / COMPLETION
   * ============================================================
   *
   * Forward:
   *
   *   P = Q F
   *
   * For the COMPLETE projected pair and orthogonal Q:
   *
   *   F_candidate = Q^T P
   *
   * This does NOT claim that the observable component alone
   * uniquely reconstructs the hidden state.
   *
   * Reconstruction requires the complementary projected content.
   * ============================================================
   */


  geo->reconstructed_observable =
    geo->Q[0][0] * PO
    +
    geo->Q[1][0] * PC;


  geo->reconstructed_complementary =
    geo->Q[0][1] * PO
    +
    geo->Q[1][1] * PC;


  geo->reconstructed_latent =
    geo->projected_latent;


  /*
   * Completion audit against the original bifocal state.
   */

  geo->reconstruction_observable_error =
    fabs(
      geo->reconstructed_observable
      -
      geo->focus_observable
    );


  geo->reconstruction_complementary_error =
    fabs(
      geo->reconstructed_complementary
      -
      geo->focus_complementary
    );


  geo->reconstruction_latent_error =
    fabs(
      geo->reconstructed_latent
      -
      geo->L
    );


  geo->reconstruction_closed = 1;

  return 0;
}
