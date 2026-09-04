#ifndef GEO_ENGINE_H
#define GEO_ENGINE_H

#include <math.h>
#include <stdio.h>

#define GEO_DIM 5
#define GEO_COUPLING_PERFECT   0
#define GEO_COUPLING_ELLIPTIC  1
/*
 * GEO Internal Geometric Engine
 *
 * This module is independent of CLASS.
 *
 * Canonical chain:
 *
 * eta
 *  -> A,B
 *  -> fc
 *  -> R
 *  -> residual return q
 *  -> M5(q)
 *  -> spectral radius Phi
 *  -> observable intensity alpha
 */

struct geo_state {

  /*
   * ============================================================
   * FULL GEO — NORMALIZED / CANONICAL ARCHITECTURE
   * ============================================================
   */

  /* Normalized total */
  double T;

  /* Canonical geometric architecture */
  double eta;

  /* Conservative decomposed geometry */
  double A;
  double B;
  double L;

  /* Canonical coupling factor */
  double fc;

  /*
   * ============================================================
   * APPLICATION ADAPTER / EFFECTIVE STATE
   * ============================================================
   *
   * mu_eff is NOT eta.
   *
   * eta belongs to the canonical GEO architecture.
   * mu_eff belongs to the concrete physical/numerical
   * realization using GEO.
   */
  double mu_eff;

  /*
   * Fundamental Law of Geometric Effectiveness
   *
   * R^3 = mu_eff
   * R   = cbrt(mu_eff)
   */
  double R;
  /*
   * ============================================================
   * BIFOCAL GEOMETRY
   * ============================================================
   *
   * GEO organizes the projected geometry around two
   * complementary centers:
   *
   *   observable focus
   *   complementary focus
   *
   * These are structural states of the same normalized object.
   */
  double focus_observable;
  double focus_complementary;

  double bifocal_sum;
  double bifocal_conservation_error;


  /*
   * ============================================================
   * MEMBRANE / TANGENT INTERFACE
   * ============================================================
   *
   * theta_membrane = pi/4 in the symmetric equilibrium state.
   *
   * Admissible local redistribution satisfies:
   *
   *   delta_observable + delta_complementary = 0
   *
   * Q belongs to this tangent / dual projection layer.
   */
  double theta_membrane;

  double tangent_delta_observable;
  double tangent_delta_complementary;

  double tangent_conservation_error;

  /*
   * 2D orthogonal tangent / membrane projection operator.
   *
   * Q^T Q = I
   * det(Q) = +1
   */
  double Q[2][2];

  double Q_orthogonality_error;
  double Q_determinant_error;


  /*
   * ============================================================
   * COUPLING GEOMETRY
   * ============================================================
   *
   * Perfect coupling   -> circle
   * Imperfect coupling -> ellipse
   *
   * No physical application law is imposed here.
   */
  int coupling_regime;

  double coupling_axis_a;
  double coupling_axis_b;
  double coupling_eccentricity;

  double coupling_geometry_error;

 double transfer_efficiency;

  /* Harmonic closure */
  double theta;
  double gap;
  double closure_t;
  /*
   * GEO v3 harmonic / dual state
   *
   * These quantities are additive to the historical ring state.
   * Existing theta, gap and closure_t remain untouched.
   */

  double theta_harmonic;

  double harmonic_observable;
  double harmonic_complementary;

  double harmonic_sum;

  double dual_balance;
  double dual_coupling;

  /* Independent identity audits */
  double theta_harmonic_ring_error;
  double harmonic_sum_error;
  double dual_balance_identity_error;
  double dual_coupling_identity_error;

  int harmonic_dual_closed;

  /* Residual transport */
  double q;

  /* Conservative transfer operator */
  double M5[GEO_DIM][GEO_DIM];

  /* Spectrum */
  double eigenvalues[GEO_DIM];
  double Phi;

  /* Observable intensity */
  double alpha;
 /*
   * ============================================================
   * FORWARD PROJECTION
   * ============================================================
   *
   * The bifocal state is projected through the already-closed
   * tangent / membrane operator Q.
   *
   * Input state:
   *
   *   [ F_O ]
   *   [ F_C ]
   *
   * Projected state:
   *
   *   [ P_O ]
   *   [ P_C ]
   *
   * L remains explicit and is not discarded.
   */
  double projected_observable;
  double projected_complementary;
  double projected_latent;

  double projection_norm_input;
  double projection_norm_output;
  double projection_norm_error;


  /*
   * ============================================================
   * RECONSTRUCTION / COMPLETION
   * ============================================================
   *
   * GEO reconstruction is treated as completion of the
   * projected state using the complementary information.
   *
   * Since Q is orthogonal, the complete projected pair can be
   * mapped back with Q^T.
   *
   * This is NOT interpreted as reconstruction from the
   * observable component alone.
   */
  double reconstructed_observable;
  double reconstructed_complementary;
  double reconstructed_latent;

  double reconstruction_observable_error;
  double reconstruction_complementary_error;
  double reconstruction_latent_error;

  /* Audit information */
  double conservation_error;
  double phi_reference_error;
  double alpha_reference_error;

  int core_closed;
  /* Application adapter / effectiveness state */
  int effective_state_ready;
  int effectiveness_closed;
  int bifocal_closed;
  int tangent_closed;
  int coupling_closed;
  int ring_closed;

/*
  * Legacy compatibility flag.
  * Kept temporarily while Bridge v3 still references
  * geo_compute_foundation_transfer().
  */
  int foundation_transfer_closed;
  int residual_closed;
  int transport_closed;
  int spectral_closed;
  int observable_closed;
int projection_closed;
int reconstruction_closed;
};


/* Initialize state */
int geo_init(
  struct geo_state *geo
);


/*
 * ============================================================
 * FULL GEO ARCHITECTURE
 * ============================================================
 *
 * T = 1
 *
 * A = eta
 * B = T - A - L
 *
 * A + B + L = T
 *
 * fc = sqrt(eta)
 *
 * L = 0 reproduces the canonical two-sector realization:
 *
 * A + B = 1
 */
int geo_build_architecture(
  struct geo_state *geo,
  double eta,
  double L
);


/*
 * Historical two-sector compatibility wrapper.
 *
 * Equivalent to:
 *
 *   geo_build_architecture(
 *     geo,
 *     eta,
 *     0.0
 *   );
 *
 * Kept temporarily for regression tests and the reduced
 * Bridge-v3 chain.
 */
int geo_build_core(
  struct geo_state *geo,
  double eta
);

/*
 * ============================================================
 * APPLICATION ADAPTER / EFFECTIVE STATE
 * ============================================================
 *
 * mu_eff is supplied by the concrete GEO realization.
 * It is independent from eta.
 */
int geo_set_effective_state(
  struct geo_state *geo,
  double mu_eff
);


/*
 * ============================================================
 * FUNDAMENTAL LAW OF GEOMETRIC EFFECTIVENESS
 *
 * R^3 = mu_eff
 * R   = cbrt(mu_eff)
 * ============================================================
 */
int geo_compute_effectiveness(
  struct geo_state *geo
);

/*
 * ============================================================
 * BIFOCAL GEOMETRY
 * ============================================================
 *
 * The normalized decomposed GEO state is represented by two
 * complementary geometric centers:
 *
 *   F_O = A
 *   F_C = B
 *
 * while L remains the latent / residual contribution.
 *
 * Therefore:
 *
 *   F_O + F_C + L = T
 *
 * This stage requires the application effectiveness state to
 * have been closed first, preserving the FULL GEO pipeline:
 *
 * architecture
 *   -> effective state
 *   -> effectiveness law
 *   -> bifocal geometry
 */
int geo_build_bifocal_geometry(
  struct geo_state *geo
);
/*
 * ============================================================
 * MEMBRANE / TANGENT INTERFACE
 * ============================================================
 *
 * Symmetric equilibrium:
 *
 *   theta_membrane = pi/4
 *
 * Local conservative redistribution:
 *
 *   delta_observable + delta_complementary = 0
 *
 * Tangent projection / rotation operator:
 *
 *   Q(theta) =
 *
 *   [  cos(theta)   sin(theta) ]
 *   [ -sin(theta)   cos(theta) ]
 *
 * with:
 *
 *   Q^T Q = I
 *   det(Q) = +1
 */
int geo_build_tangent_interface(
  struct geo_state *geo
);
/*
 * ============================================================
 * COUPLING GEOMETRY
 * ============================================================
 *
 * GEO coupling geometry:
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
 *
 * e is the coupling-eccentricity proxy.
 *
 * No application-specific semi-axis realization is imposed
 * at this architectural stage.
 */
int geo_build_coupling_geometry(
  struct geo_state *geo
);

/*
 * Legacy Bridge-v3 compatibility exposure.
 *
 * FULL GEO fundamental law:
 *
 *   R^3 = mu_eff
 *   R   = cbrt(mu_eff)
 *
 * transfer_efficiency is retained temporarily only as the
 * CLASS-facing compatibility exposure of R.
 *
 * It is NOT a canonical GEO primitive and it must NOT be
 * interpreted as a universal perturbation multiplier.
 */

int geo_compute_foundation_transfer(
  struct geo_state *geo
);

/*
 * Residual closure candidate v1.
 *
 * This implements the explicit closure presently used in
 * GEO-FOUNDATIONS/TARS/test_phi_closed.py.
 *
 * It must remain labelled as a candidate realization unless
 * promoted by the mathematical foundations.
 */

/*
 * GEO v3 harmonic / dual state.
 *
 * Reconstructs the complementary harmonic realization
 *
 * H_observable      = cos^2(theta_harmonic)
 * H_complementary   = sin^2(theta_harmonic)
 *
 * harmonic_sum      = H_observable + H_complementary
 * dual_balance      = H_observable - H_complementary
 * dual_coupling     = H_observable * H_complementary
 *
 * and independently audits:
 *
 * dual_balance  = cos(2 theta_harmonic)
 * dual_coupling = 1/4 sin^2(2 theta_harmonic)
 *
 * Existing GEO ring variables are not modified.
 */
int geo_compute_harmonic_dual_state(
    struct geo_state *geo
);
/*
 * ============================================================
 * HARMONIC RING
 * ============================================================
 *
 * Closed conservative organization downstream of the
 * harmonic / dual state.
 *
 * The ring does not generate q.
 * It establishes the closed harmonic organization from
 * which residual memory is subsequently evaluated.
 */
int geo_build_harmonic_ring(
  struct geo_state *geo
);

int geo_build_residual_candidate_v1(
  struct geo_state *geo
);


/* Build canonical M5(q) transport matrix */
int geo_build_M5(
  struct geo_state *geo
);


/* Compute dominant spectral radius */
int geo_compute_spectrum(
  struct geo_state *geo
);


/* Compute alpha = Phi B / sqrt(2) */
int geo_compute_observable(
  struct geo_state *geo
);
/*
 * ============================================================
 * FORWARD PROJECTION
 * ============================================================
 *
 * Project the complete bifocal state through Q.
 *
 * No information is discarded internally:
 *
 *   observable
 *   complementary
 *   latent
 *
 * are retained explicitly.
 */
int geo_project_forward(
  struct geo_state *geo
);


/*
 * ============================================================
 * RECONSTRUCTION / COMPLETION
 * ============================================================
 *
 * Reconstruct the bifocal candidate from the COMPLETE projected
 * state using Q^T, preserving the latent contribution.
 *
 * The routine deliberately requires projection_closed.
 */
int geo_reconstruct_completion(
  struct geo_state *geo
);

/*
 * ============================================================
 * FULL GEO BASE CHAIN
 * ============================================================
 *
 * Explicit architecture/effective-state reconstruction:
 *
 *   normalized total
 *        ↓
 *   decomposed geometry
 *        ↓
 *   canonical architecture
 *        ↓
 *   application effective state
 *        ↓
 *   fundamental effectiveness law
 *
 * Inputs:
 *
 *   eta    = canonical architectural efficiency
 *   L      = latent / residual normalized contribution
 *   mu_eff = application-specific effective input
 *
 * No identity between eta and mu_eff is assumed.
 *
 * This routine closes the FULL GEO base state before the
 * bifocal / membrane / tangent / coupling machinery.
 * ============================================================
 */
int geo_compute_full_base(
  struct geo_state *geo,
  double eta,
  double L,
  double mu_eff
);

/*
 * ============================================================
 * FULL GEO COMPLETE FORWARD INTERNAL CHAIN
 * ============================================================
 *
 * Explicit FULL GEO pipeline:
 *
 *   T
 *   -> A,B,L
 *   -> eta,fc
 *   -> mu_eff
 *   -> R
 *   -> bifocal geometry
 *   -> membrane / tangent / Q
 *   -> coupling geometry
 *   -> harmonic duality
 *   -> harmonic ring
 *   -> residual memory q
 *   -> M5(q)
 *   -> spectral organization Phi
 *   -> observable intensity alpha
 *
 * Unlike geo_compute_all_candidate_v1(), this routine does NOT
 * impose the historical reduction mu_eff := eta.
 */
int geo_compute_full_chain(
  struct geo_state *geo,
  double eta,
  double L,
  double mu_eff
);
/* Complete candidate chain */
int geo_compute_all_candidate_v1(
  struct geo_state *geo,
  double eta
);


/* Validate identities and known reference values */
int geo_validate(
  struct geo_state *geo,
  double tolerance
);


/* Diagnostic print */
void geo_print(
  const struct geo_state *geo
);

#endif
