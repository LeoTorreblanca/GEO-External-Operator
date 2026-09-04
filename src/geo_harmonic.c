#include "geo_engine.h"

int geo_compute_harmonic_dual_state(
struct geo_state *geo
) {

double c;
double s;

double balance_identity;
double coupling_identity;

if (geo == NULL)
return 1;

/*
 * ============================================================
 * FULL GEO HARMONIC DEPENDENCY
 * ============================================================
 *
 * Harmonic duality belongs downstream of:
 *
 *   bifocal geometry
 *   membrane / tangent interface
 *   coupling geometry
 *
 * and upstream of residual memory.
 *
 * Therefore the coupling state must already be closed.
 * ============================================================
 */

if (geo->coupling_closed == 0)
  return 2;

/*
 * The harmonic phase is inherited from the membrane /
 * tangent equilibrium state.
 *
 * It is not reconstructed independently.
 */
geo->theta_harmonic =
  geo->theta_membrane;


/*
 * Harmonic phase must coincide with the membrane /
 * tangent phase from which it is derived.
 */
geo->theta_harmonic_ring_error =
  fabs(
    geo->theta_harmonic
    -
    geo->theta_membrane
  );


/*
 * ============================================================
 * Complementary harmonic sectors
 *
 * observable:
 *
 * H_obs = cos^2(theta)
 *
 * complementary:
 *
 * H_comp = sin^2(theta)
 * ============================================================
 */

c =
cos(
geo->theta_harmonic
);

s =
sin(
geo->theta_harmonic
);


geo->harmonic_observable =
c * c;

geo->harmonic_complementary =
s * s;


/*
 * ============================================================
 * Conservative harmonic sum
 *
 * H_obs + H_comp = 1
 * ============================================================
 */

geo->harmonic_sum =
geo->harmonic_observable
+
geo->harmonic_complementary;


geo->harmonic_sum_error =
fabs(
geo->harmonic_sum
-
1.0
);


/*
 * ============================================================
 * Signed dual balance
 *
 * H_obs - H_comp
 *
 * independently equivalent to:
 *
 * cos(2 theta)
 * ============================================================
 */

geo->dual_balance =
geo->harmonic_observable
-
geo->harmonic_complementary;


balance_identity =
cos(
2.0
*
geo->theta_harmonic
);


geo->dual_balance_identity_error =
fabs(
geo->dual_balance
-
balance_identity
);


/*
 * ============================================================
 * Dual coupling
 *
 * H_obs * H_comp
 *
 * independently equivalent to:
 *
 * 1/4 sin^2(2 theta)
 * ============================================================
 */

geo->dual_coupling =
geo->harmonic_observable
*
geo->harmonic_complementary;


coupling_identity =
0.25
*
sin(
2.0
*
geo->theta_harmonic
)
*
sin(
2.0
*
geo->theta_harmonic
);


geo->dual_coupling_identity_error =
fabs(
geo->dual_coupling
-
coupling_identity
);


/*
 * Do not modify:
 *
 * geo->theta
 * geo->gap
 * geo->closure_t
 * geo->q
 * geo->R
 * geo->Phi
 * geo->alpha
 *
 * v3 is additive.
 */

geo->harmonic_dual_closed = 1;

return 0;
}
