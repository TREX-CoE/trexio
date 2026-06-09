/* Cartesian <-> real solid harmonic transformation for TREXIO.
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2010-2026, Susi Lehtola
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
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Originally written by Susi Lehtola for ERKALE (src/solidharmonics.cpp) and
 * relicensed by the author under the BSD 3-Clause License above for inclusion
 * in TREXIO; stripped of the Armadillo dependency and re-normalized to the
 * TREXIO (Racah) convention. Based on the closed-form Cartesian expansion of
 * the real solid harmonics, see https://en.wikipedia.org/wiki/Solid_harmonics
 */

#include <math.h>
#include <stdlib.h>

#include "trexio.h"

static double tsh_factorial(const int n)
{
  double r = 1.0;
  for (int i = 2; i <= n; ++i) r *= (double) i;
  return r;
}

/* Binomial coefficient C(m,n) as a double (exact for the small arguments
 * used here). Returns 0 for out-of-range n, matching the series bounds. */
static double tsh_binom(const int m, int n)
{
  if (n < 0 || m < 0 || n > m) return 0.0;
  if (n > m - n) n = m - n;
  double r = 1.0;
  for (int k = 0; k < n; ++k) r = r * (double) (m - k) / (double) (k + 1);
  return r;
}

void trexio_solid_harmonic_coeff(const int l, const int mval, double* const coeff)
{
  const int ncart = trexio_cart_num(l);
  for (int i = 0; i < ncart; ++i) coeff[i] = 0.0;

  const int m = abs(mval);

  /* Racah / Schmidt semi-normalization: S_l^m = sqrt(4 pi / (2l+1)) r^l Y_l^m.
   * (ERKALE's unit-sphere Y_l^m carries an extra sqrt((2l+1)/4 pi), dropped
   * here so that S_l^0 has unit coefficient on z^l.) */
  double prefac = pow(2.0, -l);
  if (m != 0)
    prefac *= sqrt(2.0 * tsh_factorial(l - m) / tsh_factorial(l + m));

  for (int k = 0; k <= (l - m) / 2; ++k) {
    double ffac = pow(-1.0, k) * tsh_binom(l, k) * tsh_binom(2 * (l - k), l);
    if (m != 0)
      ffac *= tsh_factorial(l - 2 * k) / tsh_factorial(l - 2 * k - m);
    ffac *= prefac;

    for (int a = 0; a <= k; ++a) {
      const double afac = tsh_binom(k, a) * ffac;
      for (int b = 0; b <= a; ++b) {
        const double fac = tsh_binom(a, b) * afac;

        const int zexp = 2 * b - 2 * k + l - m;
        const int yexp = 2 * (a - b);
        const int xexp = 2 * (k - a);

        if (mval > 0) {
          /* cosine combination: contribution of Re[(x+iy)^m] */
          for (int p = 0; p <= m; ++p) {
            int cosfac;
            switch ((m - p) & 3) {       /* cos((m-p) pi/2) */
            case 0:  cosfac =  1; break;
            case 2:  cosfac = -1; break;
            default: cosfac =  0; break;
            }
            if (cosfac)
              coeff[trexio_cart_index(xexp + p, yexp + m - p, zexp)]
                += cosfac * tsh_binom(m, p) * fac;
          }
        } else if (mval == 0) {
          coeff[trexio_cart_index(xexp, yexp, zexp)] += fac;
        } else {
          /* sine combination: contribution of Im[(x+iy)^m] */
          for (int p = 0; p <= m; ++p) {
            int sinfac;
            switch ((m - p) & 3) {       /* sin((m-p) pi/2) */
            case 1:  sinfac =  1; break;
            case 3:  sinfac = -1; break;
            default: sinfac =  0; break;
            }
            if (sinfac)
              coeff[trexio_cart_index(xexp + p, yexp + m - p, zexp)]
                += sinfac * tsh_binom(m, p) * fac;
          }
        }
      }
    }
  }
}

void trexio_solid_harmonic_transmat(const int l, double* const mat)
{
  const int ncart = trexio_cart_num(l);
  for (int j = 0; j < trexio_sphe_num(l); ++j)
    trexio_solid_harmonic_coeff(l, trexio_sphe_m(j), &mat[j * ncart]);
}
