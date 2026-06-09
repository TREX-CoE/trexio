/* Round-trip test for trexio_compute_ao_overlap.
 *
 * Writes a small spherical-GTO file (s and d on atom 0, s on atom 1, all
 * normalization factors set to 1), reads it back, computes the AO overlap,
 * and checks properties that are analytically known and independent of the
 * routine itself:
 *
 *   - s self-overlap and two-center s-s overlap match the closed form;
 *   - s (l=0) and d (l=2) on the same atom are orthogonal (different l);
 *   - the five d functions on one atom are mutually orthogonal (different m);
 *   - the matrix is symmetric.
 *
 * BSD 3-Clause License, Copyright (c) 2026, Susi Lehtola.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "trexio.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static int failures = 0;

static void expect(const char* what, double got, double want, double tol)
{
  if (fabs(got - want) > tol) {
    printf("FAIL  %s : got %.12e, want %.12e\n", what, got, want);
    ++failures;
  }
}

#define CHECK(rc) do { if ((rc) != TREXIO_SUCCESS) {                 \
  printf("FAIL  trexio call returned %d at line %d\n", (rc), __LINE__); \
  return 2; } } while (0)

int main(void)
{
  const char* fname = "test_overlap.dir";
  trexio_exit_code rc;

  trexio_remove_file(fname);

  /* geometry: atom 0 at origin, atom 1 at z = 1.4 */
  const double coord[6] = {0.0, 0.0, 0.0,  0.0, 0.0, 1.4};
  const double R = 1.4;

  /* exponents */
  const double a0 = 1.0;   /* s on atom 0 */
  const double a1 = 0.8;   /* d on atom 0 */
  const double a2 = 1.2;   /* s on atom 1 */

  trexio_t* file = trexio_open(fname, 'w', TREXIO_TEXT, &rc);
  CHECK(rc);

  CHECK(trexio_write_nucleus_num(file, 2));
  CHECK(trexio_write_nucleus_coord(file, coord));

  CHECK(trexio_write_basis_type(file, "Gaussian", 9));
  CHECK(trexio_write_basis_shell_num(file, 3));
  CHECK(trexio_write_basis_prim_num(file, 3));
  { const int32_t v[3] = {0, 0, 1}; CHECK(trexio_write_basis_nucleus_index(file, v)); }
  { const int32_t v[3] = {0, 2, 0}; CHECK(trexio_write_basis_shell_ang_mom(file, v)); }
  { const double  v[3] = {1.0, 1.0, 1.0}; CHECK(trexio_write_basis_shell_factor(file, v)); }
  { const int32_t v[3] = {0, 0, 0}; CHECK(trexio_write_basis_r_power(file, v)); }
  { const int32_t v[3] = {0, 1, 2}; CHECK(trexio_write_basis_shell_index(file, v)); }
  { const double  v[3] = {a0, a1, a2}; CHECK(trexio_write_basis_exponent(file, v)); }
  { const double  v[3] = {1.0, 1.0, 1.0}; CHECK(trexio_write_basis_coefficient(file, v)); }
  { const double  v[3] = {1.0, 1.0, 1.0}; CHECK(trexio_write_basis_prim_factor(file, v)); }

  CHECK(trexio_write_ao_cartesian(file, 0));
  CHECK(trexio_write_ao_num(file, 7));
  { const int32_t v[7] = {0, 1, 1, 1, 1, 1, 2}; CHECK(trexio_write_ao_shell(file, v)); }
  { double v[7]; for (int i = 0; i < 7; ++i) v[i] = 1.0;
    CHECK(trexio_write_ao_normalization(file, v)); }

  CHECK(trexio_close(file));

  /* read back and compute overlap */
  file = trexio_open(fname, 'r', TREXIO_TEXT, &rc);
  CHECK(rc);

  double S[49];
  rc = trexio_compute_ao_overlap(file, S);
  CHECK(rc);
  CHECK(trexio_close(file));
  trexio_remove_file(fname);

  /* AO layout: 0 = s(atom0); 1..5 = d(atom0); 6 = s(atom1). */
#define AO(i, j) S[(i) * 7 + (j)]

  /* s self-overlaps (factors all 1): (pi/2a)^{3/2} */
  expect("s0 self", AO(0, 0), pow(M_PI / (2.0 * a0), 1.5), 1e-12);
  expect("s1 self", AO(6, 6), pow(M_PI / (2.0 * a2), 1.5), 1e-12);

  /* two-center s-s overlap closed form */
  {
    const double ref = pow(M_PI / (a0 + a2), 1.5)
      * exp(-a0 * a2 / (a0 + a2) * R * R);
    expect("s0-s1 two center", AO(0, 6), ref, 1e-12);
  }

  /* s and d on the same atom are orthogonal (different angular momentum) */
  for (int k = 1; k <= 5; ++k) {
    char lbl[32]; snprintf(lbl, sizeof(lbl), "s0-d[%d] orthogonal", k);
    expect(lbl, AO(0, k), 0.0, 1e-12);
  }

  /* the five d functions on atom 0 are mutually orthogonal (different m) */
  for (int i = 1; i <= 5; ++i)
    for (int j = i + 1; j <= 5; ++j) {
      char lbl[32]; snprintf(lbl, sizeof(lbl), "d[%d]-d[%d] orthogonal", i, j);
      expect(lbl, AO(i, j), 0.0, 1e-12);
    }

  /* d diagonal must be strictly positive */
  for (int k = 1; k <= 5; ++k)
    if (AO(k, k) <= 0.0) { printf("FAIL  d[%d] self <= 0\n", k); ++failures; }

  /* symmetry */
  for (int i = 0; i < 7; ++i)
    for (int j = 0; j < 7; ++j)
      expect("symmetry", AO(i, j), AO(j, i), 1e-14);

  if (failures == 0) {
    printf("test_overlap_roundtrip: all checks passed\n");
    return 0;
  }
  printf("test_overlap_roundtrip: %d failures\n", failures);
  return 1;
}
