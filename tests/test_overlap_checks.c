/* Test for the metric helpers trexio_check_mo_orthonormality and
 * trexio_check_rdm_1e_trace.
 *
 * Builds a one-atom s+p basis (4 mutually orthogonal AOs: s, p_z, p_x, p_y),
 * single primitives. With MO coefficients that analytically normalize each AO
 * (computed here, independently of the routine), the MOs are orthonormal, so
 * the reported deviation must be ~0. Scaling one MO coefficient by f makes
 * exactly one diagonal element f^2, so the deviation must become |f^2 - 1|,
 * which guards against the routine trivially returning zero. The 1-RDM trace
 * must equal the written occupation sum.
 *
 * BSD 3-Clause License, Copyright (c) 2026, Susi Lehtola.
 */

#include <math.h>
#include <stdio.h>

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

/* Write the test file with the s-MO coefficient scaled by `s_scale`.
 * Returns a trexio exit code. */
static trexio_exit_code write_file(const char* fname, double s_scale)
{
  const double coord[3] = {0.0, 0.0, 0.0};
  const double gs = 1.0, gp = 1.3;

  /* Unnormalized single-primitive self-overlaps (all stored factors = 1):
   *   s (z^0):  (pi/2g)^{3/2};   p (z^1): (pi/2g)^{3/2} / (4g). */
  const double Cs = 1.0 / sqrt(pow(M_PI / (2.0 * gs), 1.5));
  const double Cp = 1.0 / sqrt(pow(M_PI / (2.0 * gp), 1.5) / (4.0 * gp));

  trexio_exit_code rc;
  trexio_remove_file(fname);
  trexio_t* file = trexio_open(fname, 'w', TREXIO_TEXT, &rc);
  if (rc != TREXIO_SUCCESS) return rc;

#define W(call) do { rc = (call); if (rc != TREXIO_SUCCESS) { \
  printf("  write failed (%d, %s) at line %d\n", rc, trexio_string_of_error(rc), __LINE__); \
  trexio_close(file); return rc; } } while (0)
  W(trexio_write_nucleus_num(file, 1));
  W(trexio_write_nucleus_coord(file, coord));

  W(trexio_write_basis_type(file, "Gaussian", 9));
  W(trexio_write_basis_shell_num(file, 2));
  W(trexio_write_basis_prim_num(file, 2));
  { const int32_t v[2] = {0, 0};    W(trexio_write_basis_nucleus_index(file, v)); }
  { const int32_t v[2] = {0, 1};    W(trexio_write_basis_shell_ang_mom(file, v)); }
  { const double  v[2] = {1.0,1.0}; W(trexio_write_basis_shell_factor(file, v)); }
  { const int32_t v[2] = {0, 0};    W(trexio_write_basis_r_power(file, v)); }
  { const int32_t v[2] = {0, 1};    W(trexio_write_basis_shell_index(file, v)); }
  { const double  v[2] = {gs, gp};  W(trexio_write_basis_exponent(file, v)); }
  { const double  v[2] = {1.0,1.0}; W(trexio_write_basis_coefficient(file, v)); }
  { const double  v[2] = {1.0,1.0}; W(trexio_write_basis_prim_factor(file, v)); }

  W(trexio_write_ao_cartesian(file, 0));
  W(trexio_write_ao_num(file, 4));
  { const int32_t v[4] = {0, 1, 1, 1};  W(trexio_write_ao_shell(file, v)); }
  { double v[4] = {1.0,1.0,1.0,1.0};    W(trexio_write_ao_normalization(file, v)); }

  W(trexio_write_mo_num(file, 4));
  {
    double C[16] = {0};
    C[0*4 + 0] = Cs * s_scale;  /* mo0 = (scaled) normalized s */
    C[1*4 + 1] = Cp;            /* mo1 = normalized p_z */
    C[2*4 + 2] = Cp;            /* mo2 = normalized p_x */
    C[3*4 + 3] = Cp;            /* mo3 = normalized p_y */
    W(trexio_write_mo_coefficient(file, C));
  }
  {
    double g[16] = {0};
    g[0*4 + 0] = 2.0; g[1*4 + 1] = 2.0;
    W(trexio_write_rdm_1e(file, g));
  }
#undef W
  return trexio_close(file);
}

static trexio_exit_code read_dev(const char* fname, double* dev, double* trace)
{
  trexio_exit_code rc;
  trexio_t* file = trexio_open(fname, 'r', TREXIO_TEXT, &rc);
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_check_mo_orthonormality(file, dev);
  if (rc == TREXIO_SUCCESS) rc = trexio_check_rdm_1e_trace(file, trace);
  trexio_close(file);
  return rc;
}

int main(void)
{
  const char* fa = "test_checks_a.dir";
  const char* fb = "test_checks_b.dir";
  double dev = -1.0, trace = -1.0;

  /* orthonormal MOs -> deviation ~ 0, RDM trace = occupation sum */
  if (write_file(fa, 1.0) != TREXIO_SUCCESS) { printf("FAIL write\n"); return 2; }
  if (read_dev(fa, &dev, &trace) != TREXIO_SUCCESS) { printf("FAIL read\n"); return 2; }
  expect("orthonormal MOs deviation", dev, 0.0, 1e-12);
  expect("rdm 1e trace", trace, 4.0, 1e-12);

  /* scale the s MO by 1.1 -> one diagonal element becomes 1.21 -> dev = 0.21 */
  if (write_file(fb, 1.1) != TREXIO_SUCCESS) { printf("FAIL write2\n"); return 2; }
  if (read_dev(fb, &dev, &trace) != TREXIO_SUCCESS) { printf("FAIL read2\n"); return 2; }
  expect("perturbed MOs deviation", dev, 1.1 * 1.1 - 1.0, 1e-12);

  trexio_remove_file(fa);
  trexio_remove_file(fb);

  if (failures == 0) {
    printf("test_overlap_checks: all checks passed\n");
    return 0;
  }
  printf("test_overlap_checks: %d failures\n", failures);
  return 1;
}
