/* Unit test for the Cartesian <-> real solid harmonic transform.
 *
 * Checks the routine against the signed table in the TREXIO format
 * specification (trex.org "ao" group, documented in issue #244):
 * +m cosine / -m sine, Condon-Shortley folded out, Racah normalization.
 *
 * BSD 3-Clause License, Copyright (c) 2010-2026, Susi Lehtola.
 */

#include <math.h>
#include <stdio.h>

#include "trexio.h"

static int failures = 0;

/* Assert that S_l^m has coefficient `val` on monomial x^nx y^ny z^nz. */
static void chk(int l, int m, int nx, int ny, int nz, double val)
{
  double c[64];
  trexio_solid_harmonic_coeff(l, m, c);
  const double got = c[trexio_cart_index(nx, ny, nz)];
  if (fabs(got - val) > 1e-12) {
    printf("FAIL  S(l=%d,m=%+d) coeff of x^%d y^%d z^%d : got %.12f, want %.12f\n",
           l, m, nx, ny, nz, got, val);
    ++failures;
  }
}

/* Assert S_l^m has no other nonzero coefficients beyond `n` listed ones. */
static void chk_nnz(int l, int m, int n)
{
  double c[64];
  trexio_solid_harmonic_coeff(l, m, c);
  int cnt = 0;
  for (int k = 0; k < trexio_cart_num(l); ++k)
    if (fabs(c[k]) > 1e-12) ++cnt;
  if (cnt != n) {
    printf("FAIL  S(l=%d,m=%+d) has %d nonzero terms, want %d\n", l, m, cnt, n);
    ++failures;
  }
}

int main(void)
{
  const double s3 = sqrt(3.0), s6 = sqrt(6.0), s10 = sqrt(10.0);
  const double s15 = sqrt(15.0), s35 = sqrt(35.0);

  /* Storage order: 0, +1, -1, +2, -2, ... */
  if (trexio_sphe_m(0) !=  0) { printf("FAIL order j=0\n"); ++failures; }
  if (trexio_sphe_m(1) != +1) { printf("FAIL order j=1\n"); ++failures; }
  if (trexio_sphe_m(2) != -1) { printf("FAIL order j=2\n"); ++failures; }
  if (trexio_sphe_m(3) != +2) { printf("FAIL order j=3\n"); ++failures; }
  if (trexio_sphe_m(4) != -2) { printf("FAIL order j=4\n"); ++failures; }

  /* l = 0 */
  chk(0, 0, 0, 0, 0, 1.0); chk_nnz(0, 0, 1);

  /* l = 1 : z, x, y  (the p_z, p_x, p_y anchor) */
  chk(1,  0, 0, 0, 1, 1.0); chk_nnz(1,  0, 1);
  chk(1, +1, 1, 0, 0, 1.0); chk_nnz(1, +1, 1);
  chk(1, -1, 0, 1, 0, 1.0); chk_nnz(1, -1, 1);

  /* l = 2 */
  chk(2,  0, 0, 0, 2,  1.0);   chk(2, 0, 2, 0, 0, -0.5); chk(2, 0, 0, 2, 0, -0.5);
  chk_nnz(2, 0, 3);
  chk(2, +1, 1, 0, 1,  s3);    chk_nnz(2, +1, 1);
  chk(2, -1, 0, 1, 1,  s3);    chk_nnz(2, -1, 1);
  chk(2, +2, 2, 0, 0,  s3/2);  chk(2, +2, 0, 2, 0, -s3/2); chk_nnz(2, +2, 2);
  chk(2, -2, 1, 1, 0,  s3);    chk_nnz(2, -2, 1);

  /* l = 3 */
  chk(3,  0, 0, 0, 3,  1.0);   chk(3, 0, 2, 0, 1, -1.5); chk(3, 0, 0, 2, 1, -1.5);
  chk(3, +1, 1, 0, 2,  s6);    chk(3, +1, 3, 0, 0, -s6/4); chk(3, +1, 1, 2, 0, -s6/4);
  chk(3, -1, 0, 1, 2,  s6);    chk(3, -1, 2, 1, 0, -s6/4); chk(3, -1, 0, 3, 0, -s6/4);
  chk(3, +2, 2, 0, 1,  s15/2); chk(3, +2, 0, 2, 1, -s15/2); chk_nnz(3, +2, 2);
  chk(3, -2, 1, 1, 1,  s15);   chk_nnz(3, -2, 1);
  chk(3, +3, 3, 0, 0,  s10/4); chk(3, +3, 1, 2, 0, -3*s10/4); chk_nnz(3, +3, 2);
  chk(3, -3, 2, 1, 0,  3*s10/4); chk(3, -3, 0, 3, 0, -s10/4); chk_nnz(3, -3, 2);

  /* l = 4 (selected leading / highest-m terms) */
  chk(4,  0, 0, 0, 4,  1.0);
  chk(4, +4, 4, 0, 0,  s35/8); chk(4, +4, 2, 2, 0, -6*s35/8); chk(4, +4, 0, 4, 0, s35/8);
  chk(4, -4, 3, 1, 0,  s35/2); chk(4, -4, 1, 3, 0, -s35/2);   chk_nnz(4, -4, 2);
  /* S(4,+1) = (sqrt10/4) xz(7z^2-3r^2) = (sqrt10/4)(4 xz^3 - 3 x^3 z - 3 xy^2 z) */
  chk(4, +1, 1, 0, 3,  s10);   chk(4, +1, 3, 0, 1, -3*s10/4); chk(4, +1, 1, 2, 1, -3*s10/4);
  chk_nnz(4, +1, 3);

  if (failures == 0) {
    printf("test_solid_harmonics: all checks passed\n");
    return 0;
  }
  printf("test_solid_harmonics: %d failures\n", failures);
  return 1;
}
