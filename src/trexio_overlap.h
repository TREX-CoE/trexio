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
 *
 *
 * Pure, dependency-free math kernel: contracted Cartesian shell-pair overlap
 * blocks (the routine is shell-driven and carries no angular-momentum limit),
 * plus the single-primitive overlap and the Cartesian-Gaussian normalization
 * constant. The contraction / TREXIO-data-reading layer is built on top of
 * this and is compiled only when the optional overlap feature is enabled.
 */

#ifndef TREXIO_OVERLAP_H
#define TREXIO_OVERLAP_H

#include "trexio.h"   /* trexio_cart_num / _index / _powers / solid harmonics */

/* Normalization constant N of the primitive Cartesian Gaussian
 *   g(r) = N (x-Ax)^i (y-Ay)^j (z-Az)^k exp(-alpha |r-A|^2),
 * such that <g|g> = 1. */
double trexio_cart_gaussian_norm(double alpha, int i, int j, int k);

/* Overlap of two primitive Cartesian Gaussians (without normalization):
 *   gA = (x-Ax)^la (y-Ay)^ma (z-Az)^na exp(-alpha |r-A|^2)
 *   gB = (x-Bx)^lb (y-By)^mb (z-Bz)^nb exp(-beta  |r-B|^2)
 * A and B are length-3 Cartesian centers. */
double trexio_primitive_overlap_cart(double alpha, const double A[3],
                                     int la, int ma, int na,
                                     double beta, const double B[3],
                                     int lb, int mb, int nb);

/* Contracted overlap block of two Cartesian shells, computed in one pass.
 *
 *   shell A: angular momentum lA, center A, nprimA primitives with exponents
 *            expoA[k] and contraction coefficients coefA[k];
 *   shell B: likewise.
 *
 * The coefficients are used as supplied, so the caller folds in whatever
 * per-primitive factors apply (e.g. TREXIO's prim_factor * coefficient).
 * On return, M holds an (ncartA x ncartB) row-major matrix,
 *   M[a * trexio_cart_num(lB) + b] = < cart_a of A | cart_b of B >,
 * with the Cartesian components in canonical TREXIO order. No shell or
 * per-AO normalization and no spherical transform is applied here.
 * There is no hard limit on lA / lB. */
void trexio_shell_pair_overlap_cart(int lA, const double A[3], int nprimA,
                                    const double* expoA, const double* coefA,
                                    int lB, const double B[3], int nprimB,
                                    const double* expoB, const double* coefB,
                                    double* M);

#endif /* TREXIO_OVERLAP_H */
