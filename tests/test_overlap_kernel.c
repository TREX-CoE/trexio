/* Unit test for the primitive GTO overlap kernel.
 *
 * Validates the kernel math independently of any TREXIO file:
 *   - normalized Cartesian Gaussians have unit self-overlap (s, p, d, f);
 *   - the kernel is symmetric under exchange of the two primitives;
 *   - a two-center s-s overlap matches the closed-form value.
 *
 * BSD 3-Clause License, Copyright (c) 2026, Susi Lehtola.
 */

#include <math.h>
#include <stdio.h>

#include "trexio_overlap.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static int failures = 0;

static void expect(const char* what, double got, double want, double tol)
{
  if (fabs(got - want) > tol) {
    printf("FAIL  %s : got %.12f, want %.12f\n", what, got, want);
    ++failures;
  }
}

/* Self-overlap of a normalized Cartesian Gaussian -- must be 1. */
static double self_overlap(double a, int i, int j, int k)
{
  const double A[3] = {0.3, -0.7, 1.1};
  const double N = trexio_cart_gaussian_norm(a, i, j, k);
  return N * N * trexio_primitive_overlap_cart(a, A, i, j, k, a, A, i, j, k);
}

int main(void)
{
  const double a = 1.3, b = 0.7;

  /* Normalized self-overlaps across angular momenta. */
  expect("norm s (000)",  self_overlap(a, 0, 0, 0), 1.0, 1e-13);
  expect("norm p (100)",  self_overlap(a, 1, 0, 0), 1.0, 1e-13);
  expect("norm p (001)",  self_overlap(b, 0, 0, 1), 1.0, 1e-13);
  expect("norm d (200)",  self_overlap(a, 2, 0, 0), 1.0, 1e-13);
  expect("norm d (110)",  self_overlap(a, 1, 1, 0), 1.0, 1e-13);
  expect("norm f (111)",  self_overlap(b, 1, 1, 1), 1.0, 1e-13);
  expect("norm f (300)",  self_overlap(a, 3, 0, 0), 1.0, 1e-13);

  /* Symmetry under primitive exchange. */
  {
    const double A[3] = {0.0, 0.0, 0.0}, B[3] = {0.5, -0.4, 0.9};
    const double sab = trexio_primitive_overlap_cart(a, A, 1, 0, 0, b, B, 0, 1, 1);
    const double sba = trexio_primitive_overlap_cart(b, B, 0, 1, 1, a, A, 1, 0, 0);
    expect("exchange symmetry", sab, sba, 1e-14);
  }

  /* Two-center s-s overlap closed form:
   *   <gA|gB> = (pi/(a+b))^{3/2} exp(-a b/(a+b) |AB|^2). */
  {
    const double A[3] = {0.0, 0.0, 0.0}, B[3] = {1.0, 0.0, 0.0};
    const double r2 = 1.0;
    const double ref = pow(M_PI / (a + b), 1.5) * exp(-a * b / (a + b) * r2);
    const double got = trexio_primitive_overlap_cart(a, A, 0, 0, 0, b, B, 0, 0, 0);
    expect("s-s two center", got, ref, 1e-14);
  }

  /* Orthogonality of different Cartesian components on the same center:
   *   a p_x and p_y primitive on the same atom have zero overlap. */
  {
    const double A[3] = {0.2, 0.2, 0.2};
    const double s = trexio_primitive_overlap_cart(a, A, 1, 0, 0, a, A, 0, 1, 0);
    expect("px-py orthogonal", s, 0.0, 1e-14);
  }

  /* Shell-pair driver: an s|s block of single primitives must equal the
   * single-primitive overlap. */
  {
    const double A[3] = {0.0, 0.0, 0.0}, B[3] = {0.3, 0.4, 0.0};
    const double eA[1] = {a}, cA[1] = {1.0}, eB[1] = {b}, cB[1] = {1.0};
    double M[1];
    trexio_shell_pair_overlap_cart(0, A, 1, eA, cA, 0, B, 1, eB, cB, M);
    expect("shellpair s|s",
           M[0], trexio_primitive_overlap_cart(a, A, 0, 0, 0, b, B, 0, 0, 0), 1e-14);
  }

  /* Shell-pair driver: a p|p self-block (single primitive, A=B) is diagonal,
   * and each normalized diagonal element is 1; canonical order is x,y,z. */
  {
    const double A[3] = {0.1, -0.2, 0.5};
    const double e[1] = {a}, c[1] = {1.0};
    double M[9];
    trexio_shell_pair_overlap_cart(1, A, 1, e, c, 1, A, 1, e, c, M);
    const double Np = trexio_cart_gaussian_norm(a, 1, 0, 0);   /* same for x,y,z */
    expect("shellpair p|p xx norm", Np * Np * M[0 * 3 + 0], 1.0, 1e-13);
    expect("shellpair p|p yy norm", Np * Np * M[1 * 3 + 1], 1.0, 1e-13);
    expect("shellpair p|p zz norm", Np * Np * M[2 * 3 + 2], 1.0, 1e-13);
    expect("shellpair p|p xy zero", M[0 * 3 + 1], 0.0, 1e-14);
    expect("shellpair p|p xz zero", M[0 * 3 + 2], 0.0, 1e-14);
  }

  if (failures == 0) {
    printf("test_overlap_kernel: all checks passed\n");
    return 0;
  }
  printf("test_overlap_kernel: %d failures\n", failures);
  return 1;
}
