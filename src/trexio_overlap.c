/* GTO overlap-integral kernel for TREXIO (validation helper).
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2026, Susi Lehtola
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DAMAGES ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE.
 */

#include <math.h>

#include "trexio_overlap.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* (2n-1)!! = 1*3*5*...*(2n-1), with (-1)!! = 1. */
static double odd_double_factorial(const int n)
{
  double r = 1.0;
  for (int i = 2 * n - 1; i > 0; i -= 2) r *= (double) i;
  return r;
}

double trexio_cart_gaussian_norm(const double alpha, const int i, const int j, const int k)
{
  /* N^2 = (2 alpha / pi)^{3/2} (4 alpha)^{i+j+k}
   *       / [ (2i-1)!! (2j-1)!! (2k-1)!! ] */
  const double n2 = pow(2.0 * alpha / M_PI, 1.5)
    * pow(4.0 * alpha, (double) (i + j + k))
    / (odd_double_factorial(i) * odd_double_factorial(j) * odd_double_factorial(k));
  return sqrt(n2);
}

/* One-dimensional Obara-Saika overlap table (dimensionless, S00 = 1), filled
 * into the caller-provided S of size (la+1)*(lb+1), row-major S[i*(lb+1)+j].
 * p = alpha + beta; PA = P - Ax, PB = P - Bx, with P the product center.
 * No angular-momentum limit: the caller sizes S to the actual la, lb. */
static void os_overlap_1d(const int la, const int lb,
                          const double PA, const double PB, const double p,
                          double* const S)
{
  const double oo2p = 0.5 / p;
  const int w = lb + 1;

  S[0] = 1.0;
  for (int j = 1; j <= lb; ++j)
    S[j] = PB * S[j - 1] + (j >= 2 ? oo2p * (j - 1) * S[j - 2] : 0.0);

  for (int i = 1; i <= la; ++i) {
    for (int j = 0; j <= lb; ++j) {
      double v = PA * S[(i - 1) * w + j];
      if (i >= 2) v += oo2p * (i - 1) * S[(i - 2) * w + j];
      if (j >= 1) v += oo2p * j * S[(i - 1) * w + (j - 1)];
      S[i * w + j] = v;
    }
  }
}

double trexio_primitive_overlap_cart(const double alpha, const double A[3],
                                     const int la, const int ma, const int na,
                                     const double beta, const double B[3],
                                     const int lb, const int mb, const int nb)
{
  const double p = alpha + beta;
  const double mu = alpha * beta / p;

  double ab2 = 0.0, PA[3], PB[3];
  for (int d = 0; d < 3; ++d) {
    const double diff = A[d] - B[d];
    ab2 += diff * diff;
    const double Pc = (alpha * A[d] + beta * B[d]) / p;
    PA[d] = Pc - A[d];
    PB[d] = Pc - B[d];
  }

  double Sx[(la + 1) * (lb + 1)];
  double Sy[(ma + 1) * (mb + 1)];
  double Sz[(na + 1) * (nb + 1)];
  os_overlap_1d(la, lb, PA[0], PB[0], p, Sx);
  os_overlap_1d(ma, mb, PA[1], PB[1], p, Sy);
  os_overlap_1d(na, nb, PA[2], PB[2], p, Sz);

  return pow(M_PI / p, 1.5) * exp(-mu * ab2)
    * Sx[la * (lb + 1) + lb] * Sy[ma * (mb + 1) + mb] * Sz[na * (nb + 1) + nb];
}

void trexio_shell_pair_overlap_cart(const int lA, const double A[3], const int nprimA,
                                    const double* const expoA, const double* const coefA,
                                    const int lB, const double B[3], const int nprimB,
                                    const double* const expoB, const double* const coefB,
                                    double* const M)
{
  const int ncartA = trexio_cart_num(lA);
  const int ncartB = trexio_cart_num(lB);
  const int wB = lB + 1;

  for (int i = 0; i < ncartA * ncartB; ++i) M[i] = 0.0;

  /* Cartesian power lists in canonical TREXIO order. */
  int pA[ncartA][3], pB[ncartB][3];
  for (int a = 0; a < ncartA; ++a) trexio_cart_powers(lA, a, &pA[a][0], &pA[a][1], &pA[a][2]);
  for (int b = 0; b < ncartB; ++b) trexio_cart_powers(lB, b, &pB[b][0], &pB[b][1], &pB[b][2]);

  double ab2 = 0.0;
  for (int d = 0; d < 3; ++d) { const double diff = A[d] - B[d]; ab2 += diff * diff; }

  for (int kA = 0; kA < nprimA; ++kA) {
    for (int kB = 0; kB < nprimB; ++kB) {
      const double alpha = expoA[kA], beta = expoB[kB];
      const double p = alpha + beta;
      const double mu = alpha * beta / p;

      double PA[3], PB[3];
      for (int d = 0; d < 3; ++d) {
        const double Pc = (alpha * A[d] + beta * B[d]) / p;
        PA[d] = Pc - A[d];
        PB[d] = Pc - B[d];
      }

      /* One 1-D table per Cartesian direction, reused over all components. */
      double Sx[(lA + 1) * wB], Sy[(lA + 1) * wB], Sz[(lA + 1) * wB];
      os_overlap_1d(lA, lB, PA[0], PB[0], p, Sx);
      os_overlap_1d(lA, lB, PA[1], PB[1], p, Sy);
      os_overlap_1d(lA, lB, PA[2], PB[2], p, Sz);

      const double pref = coefA[kA] * coefB[kB]
        * pow(M_PI / p, 1.5) * exp(-mu * ab2);

      for (int a = 0; a < ncartA; ++a) {
        for (int b = 0; b < ncartB; ++b) {
          M[a * ncartB + b] += pref
            * Sx[pA[a][0] * wB + pB[b][0]]
            * Sy[pA[a][1] * wB + pB[b][1]]
            * Sz[pA[a][2] * wB + pB[b][2]];
        }
      }
    }
  }
}
