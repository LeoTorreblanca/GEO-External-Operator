#include "geo_engine.h"

#include <float.h>


static void geo_copy_matrix(
  double dst[GEO_DIM][GEO_DIM],
  const double src[GEO_DIM][GEO_DIM]
) {

  int i;
  int j;

  for (i = 0; i < GEO_DIM; i++) {
    for (j = 0; j < GEO_DIM; j++) {
      dst[i][j] = src[i][j];
    }
  }
}


static int geo_jacobi_eigenvalues(
  const double input[GEO_DIM][GEO_DIM],
  double eigenvalues[GEO_DIM]
) {

  double A[GEO_DIM][GEO_DIM];

  const int max_iterations = 10000;
  const double tolerance = 1e-15;

  int iteration;
  int i;
  int j;
  int p;
  int q;

  geo_copy_matrix(
    A,
    input
  );

  for (
    iteration = 0;
    iteration < max_iterations;
    iteration++
  ) {

    double max_offdiag = 0.0;

    p = 0;
    q = 1;

    /*
     * Find largest off-diagonal element
     */

    for (i = 0; i < GEO_DIM; i++) {

      for (j = i + 1; j < GEO_DIM; j++) {

        double value =
          fabs(A[i][j]);

        if (value > max_offdiag) {

          max_offdiag = value;

          p = i;
          q = j;
        }
      }
    }

    /*
     * Matrix is effectively diagonal
     */

    if (max_offdiag < tolerance)
      break;

    {
      double app = A[p][p];
      double aqq = A[q][q];
      double apq = A[p][q];

      double tau;
      double t;
      double c;
      double s;

      if (fabs(apq) < DBL_EPSILON)
        continue;

      tau =
        (aqq - app)
        /
        (2.0 * apq);

      if (tau >= 0.0) {

        t =
          1.0
          /
          (
            tau
            +
            sqrt(1.0 + tau * tau)
          );
      }
      else {

        t =
          -1.0
          /
          (
            -tau
            +
            sqrt(1.0 + tau * tau)
          );
      }

      c =
        1.0
        /
        sqrt(1.0 + t * t);

      s =
        t * c;

      /*
       * Update all non-p/q elements
       */

      for (i = 0; i < GEO_DIM; i++) {

        if (i != p && i != q) {

          double aip = A[i][p];
          double aiq = A[i][q];

          A[i][p] =
            c * aip
            -
            s * aiq;

          A[p][i] =
            A[i][p];

          A[i][q] =
            s * aip
            +
            c * aiq;

          A[q][i] =
            A[i][q];
        }
      }

      /*
       * Rotate diagonal block
       */

      A[p][p] =
        c * c * app
        -
        2.0 * s * c * apq
        +
        s * s * aqq;

      A[q][q] =
        s * s * app
        +
        2.0 * s * c * apq
        +
        c * c * aqq;

      A[p][q] = 0.0;
      A[q][p] = 0.0;
    }
  }

  if (iteration == max_iterations)
    return 1;

  for (i = 0; i < GEO_DIM; i++) {
    eigenvalues[i] = A[i][i];
  }

  return 0;
}


int geo_compute_spectrum(
  struct geo_state *geo
) {

  int status;
  int i;

  double spectral_radius = 0.0;

  if (geo == NULL)
    return 1;

  if (geo->transport_closed == 0)
    return 2;

  status =
    geo_jacobi_eigenvalues(
      geo->M5,
      geo->eigenvalues
    );

  if (status != 0)
    return 3;

  /*
   * Phi = spectral radius rho(M5)
   */

  for (i = 0; i < GEO_DIM; i++) {

    double magnitude =
      fabs(geo->eigenvalues[i]);

    if (magnitude > spectral_radius) {
      spectral_radius = magnitude;
    }
  }

  geo->Phi =
    spectral_radius;

  geo->spectral_closed = 1;

  return 0;
}


int geo_compute_observable(
  struct geo_state *geo
) {

  if (geo == NULL)
    return 1;

  if (geo->spectral_closed == 0)
    return 2;

  /*
   * Canonical observable intensity
   *
   * alpha = Phi B / sqrt(2)
   */

  geo->alpha =
    geo->Phi
    *
    geo->B
    /
    sqrt(2.0);

  geo->observable_closed = 1;

  return 0;
}
