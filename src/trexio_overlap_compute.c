/* GTO overlap validation helper: reads the basis/ao groups of a TREXIO file
 * and assembles the AO overlap matrix, shell-pair by shell-pair. Built
 * unconditionally as part of the library (libm is already required).
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2026, Susi Lehtola
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the conditions of the BSD
 * 3-Clause License (see COPYING) are met. THIS SOFTWARE IS PROVIDED "AS IS"
 * WITHOUT WARRANTY OF ANY KIND.
 */

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "trexio.h"
#include "trexio_overlap.h"

/* Number of AOs contributed by a shell of angular momentum l. */
static int shell_ao_num(const int l, const int cartesian)
{
  return cartesian ? trexio_cart_num(l) : trexio_sphe_num(l);
}

trexio_exit_code trexio_compute_ao_overlap(trexio_t* const file,
                                           const int64_t overlap_size,
                                           double* const overlap)
{
  if (file == NULL)    return TREXIO_INVALID_ARG_1;
  if (overlap == NULL) return TREXIO_INVALID_ARG_3;

  trexio_exit_code rc;

  /* --- basis must be Gaussian ------------------------------------------- */
  char btype[32];
  rc = trexio_read_basis_type(file, btype, (int32_t) sizeof(btype));
  if (rc != TREXIO_SUCCESS) return rc;
  if (strcmp(btype, "Gaussian") != 0) return TREXIO_NOT_IMPLEMENTED;

  /* The kernel assumes plain real Gaussians. Complex exponents/coefficients
   * and oscillating primitives change the integrand, so refuse them rather
   * than silently returning a wrong matrix. */
  if (trexio_has_basis_exponent_im   (file) == TREXIO_SUCCESS ||
      trexio_has_basis_coefficient_im(file) == TREXIO_SUCCESS ||
      trexio_has_basis_oscillation_arg (file) == TREXIO_SUCCESS ||
      trexio_has_basis_oscillation_kind(file) == TREXIO_SUCCESS)
    return TREXIO_NOT_IMPLEMENTED;

  /* --- dimensions ------------------------------------------------------- */
  int32_t nucleus_num = 0, shell_num = 0, prim_num = 0, ao_num = 0, cartesian = 0;
  if ((rc = trexio_read_nucleus_num (file, &nucleus_num)) != TREXIO_SUCCESS) return rc;
  if ((rc = trexio_read_basis_shell_num(file, &shell_num)) != TREXIO_SUCCESS) return rc;
  if ((rc = trexio_read_basis_prim_num (file, &prim_num )) != TREXIO_SUCCESS) return rc;
  if ((rc = trexio_read_ao_num         (file, &ao_num    )) != TREXIO_SUCCESS) return rc;
  if ((rc = trexio_read_ao_cartesian   (file, &cartesian )) != TREXIO_SUCCESS) return rc;

  /* The output matrix is ao_num x ao_num. */
  if (overlap_size < (int64_t) ao_num * (int64_t) ao_num) return TREXIO_INVALID_ARG_2;

  /* --- allocate all buffers (single cleanup path) ---------------------- */
  double*  coord    = malloc(sizeof(double)  * 3 * (size_t) nucleus_num);
  int32_t* nuc_idx  = malloc(sizeof(int32_t)     * (size_t) shell_num);
  int32_t* ang_mom  = malloc(sizeof(int32_t)     * (size_t) shell_num);
  double*  sh_fac   = malloc(sizeof(double)      * (size_t) shell_num);
  int32_t* r_power  = malloc(sizeof(int32_t)     * (size_t) shell_num);
  int32_t* sh_idx   = malloc(sizeof(int32_t)     * (size_t) prim_num);
  double*  expo     = malloc(sizeof(double)      * (size_t) prim_num);
  double*  coef     = malloc(sizeof(double)      * (size_t) prim_num);
  double*  pfac     = malloc(sizeof(double)      * (size_t) prim_num);
  double*  ao_norm  = malloc(sizeof(double)      * (size_t) ao_num);
  int32_t* ao_shell = malloc(sizeof(int32_t)     * (size_t) ao_num);

  int32_t* prim_off = malloc(sizeof(int32_t)     * (size_t) (shell_num + 1));
  int32_t* cursor   = malloc(sizeof(int32_t)     * (size_t) shell_num);
  int32_t* ao_off   = malloc(sizeof(int32_t)     * (size_t) shell_num);
  double*  pexpo    = malloc(sizeof(double)      * (size_t) prim_num);
  double*  pcoef    = malloc(sizeof(double)      * (size_t) prim_num);

  rc = TREXIO_ALLOCATION_FAILED;
  if (!coord || !nuc_idx || !ang_mom || !sh_fac || !r_power || !sh_idx ||
      !expo || !coef || !pfac || !ao_norm || !ao_shell || !prim_off || !cursor ||
      !ao_off || !pexpo || !pcoef) goto cleanup;

  /* --- read mandatory groups -------------------------------------------- */
  if ((rc = trexio_read_nucleus_coord        (file, coord  )) != TREXIO_SUCCESS) goto cleanup;
  if ((rc = trexio_read_basis_nucleus_index  (file, nuc_idx)) != TREXIO_SUCCESS) goto cleanup;
  if ((rc = trexio_read_basis_shell_ang_mom  (file, ang_mom)) != TREXIO_SUCCESS) goto cleanup;
  if ((rc = trexio_read_basis_shell_index    (file, sh_idx )) != TREXIO_SUCCESS) goto cleanup;
  if ((rc = trexio_read_basis_exponent       (file, expo   )) != TREXIO_SUCCESS) goto cleanup;
  if ((rc = trexio_read_basis_coefficient    (file, coef   )) != TREXIO_SUCCESS) goto cleanup;
  if ((rc = trexio_read_ao_shell             (file, ao_shell)) != TREXIO_SUCCESS) goto cleanup;

  /* --- optional normalization factors (default to identity if absent) ---- */
  if (trexio_has_basis_shell_factor(file) == TREXIO_SUCCESS) {
    if ((rc = trexio_read_basis_shell_factor(file, sh_fac)) != TREXIO_SUCCESS) goto cleanup;
  } else {
    for (int32_t s = 0; s < shell_num; ++s) sh_fac[s] = 1.0;
  }
  if (trexio_has_basis_prim_factor(file) == TREXIO_SUCCESS) {
    if ((rc = trexio_read_basis_prim_factor(file, pfac)) != TREXIO_SUCCESS) goto cleanup;
  } else {
    for (int32_t k = 0; k < prim_num; ++k) pfac[k] = 1.0;
  }
  if (trexio_has_ao_normalization(file) == TREXIO_SUCCESS) {
    if ((rc = trexio_read_ao_normalization(file, ao_norm)) != TREXIO_SUCCESS) goto cleanup;
  } else {
    for (int32_t i = 0; i < ao_num; ++i) ao_norm[i] = 1.0;
  }
  /* r_power (n_s): optional, defaults to 0 (ordinary GTOs). */
  if (trexio_has_basis_r_power(file) == TREXIO_SUCCESS) {
    if ((rc = trexio_read_basis_r_power(file, r_power)) != TREXIO_SUCCESS) goto cleanup;
  } else {
    for (int32_t s = 0; s < shell_num; ++s) r_power[s] = 0;
  }

  /* r_power != 0 (e.g. Cartesian-as-spherical shells) is not supported. */
  for (int32_t s = 0; s < shell_num; ++s)
    if (r_power[s] != 0) { rc = TREXIO_NOT_IMPLEMENTED; goto cleanup; }

  /* --- validate file-supplied indices before using them ----------------- */
  /* A corrupted file must not be able to drive an out-of-bounds access. */
  for (int32_t s = 0; s < shell_num; ++s) {
    if (nuc_idx[s] < 0 || nuc_idx[s] >= nucleus_num) { rc = TREXIO_FAILURE; goto cleanup; }
    if (ang_mom[s] < 0)                              { rc = TREXIO_FAILURE; goto cleanup; }
  }
  for (int32_t k = 0; k < prim_num; ++k)
    if (sh_idx[k] < 0 || sh_idx[k] >= shell_num)     { rc = TREXIO_FAILURE; goto cleanup; }

  /* --- group primitives by shell and fold prim_factor into coefficient -- */
  for (int32_t s = 0; s <= shell_num; ++s) prim_off[s] = 0;
  for (int32_t k = 0; k < prim_num; ++k) prim_off[sh_idx[k] + 1]++;
  for (int32_t s = 0; s < shell_num; ++s) prim_off[s + 1] += prim_off[s];
  for (int32_t s = 0; s < shell_num; ++s) cursor[s] = prim_off[s];
  for (int32_t k = 0; k < prim_num; ++k) {
    const int32_t pos = cursor[sh_idx[k]]++;
    pexpo[pos] = expo[k];
    pcoef[pos] = pfac[k] * coef[k];
  }

  /* --- AO offset of each shell, validated against ao.shell -------------- */
  {
    int32_t off = 0;
    for (int32_t s = 0; s < shell_num; ++s) {
      ao_off[s] = off;
      const int n = shell_ao_num(ang_mom[s], cartesian);
      /* The AOs of a shell must be stored consecutively and in shell order. */
      for (int j = 0; j < n; ++j)
        if (off + j >= ao_num || ao_shell[off + j] != s) {
          rc = TREXIO_FAILURE; goto cleanup;
        }
      off += n;
    }
    if (off != ao_num) { rc = TREXIO_FAILURE; goto cleanup; } /* inconsistent file */
  }

  for (int32_t i = 0; i < ao_num * ao_num; ++i) overlap[i] = 0.0;

  /* --- shell-pair loop -------------------------------------------------- */
  for (int32_t sA = 0; sA < shell_num; ++sA) {
    const int lA = ang_mom[sA];
    const int ncA = trexio_cart_num(lA);
    const int nAOa = shell_ao_num(lA, cartesian);
    const double* RA = &coord[3 * nuc_idx[sA]];

    for (int32_t sB = 0; sB <= sA; ++sB) {
      const int lB = ang_mom[sB];
      const int ncB = trexio_cart_num(lB);
      const int nAOb = shell_ao_num(lB, cartesian);
      const double* RB = &coord[3 * nuc_idx[sB]];

      /* contracted Cartesian block */
      double* M = malloc(sizeof(double) * (size_t) (ncA * ncB));
      double* blk = malloc(sizeof(double) * (size_t) (nAOa * nAOb));
      if (!M || !blk) { free(M); free(blk); rc = TREXIO_ALLOCATION_FAILED; goto cleanup; }

      trexio_shell_pair_overlap_cart(
        lA, RA, prim_off[sA + 1] - prim_off[sA], &pexpo[prim_off[sA]], &pcoef[prim_off[sA]],
        lB, RB, prim_off[sB + 1] - prim_off[sB], &pexpo[prim_off[sB]], &pcoef[prim_off[sB]],
        M);

      const double sfac = sh_fac[sA] * sh_fac[sB];
      for (int i = 0; i < ncA * ncB; ++i) M[i] *= sfac;

      if (cartesian) {
        for (int i = 0; i < nAOa * nAOb; ++i) blk[i] = M[i];
      } else {
        /* blk = TA * M * TB^T, with TA/TB the cart->solid transforms */
        double* TA = malloc(sizeof(double) * (size_t) (nAOa * ncA));
        double* TB = malloc(sizeof(double) * (size_t) (nAOb * ncB));
        if (!TA || !TB) { free(TA); free(TB); free(M); free(blk);
                          rc = TREXIO_ALLOCATION_FAILED; goto cleanup; }
        rc = trexio_solid_harmonic_transmat(lA, (int64_t) nAOa * ncA, TA);
        if (rc != TREXIO_SUCCESS) { free(TA); free(TB); free(M); free(blk); goto cleanup; }
        rc = trexio_solid_harmonic_transmat(lB, (int64_t) nAOb * ncB, TB);
        if (rc != TREXIO_SUCCESS) { free(TA); free(TB); free(M); free(blk); goto cleanup; }
        for (int ia = 0; ia < nAOa; ++ia) {
          for (int jb = 0; jb < nAOb; ++jb) {
            double acc = 0.0;
            for (int a = 0; a < ncA; ++a) {
              const double ta = TA[ia * ncA + a];
              if (ta == 0.0) continue;
              for (int b = 0; b < ncB; ++b)
                acc += ta * M[a * ncB + b] * TB[jb * ncB + b];
            }
            blk[ia * nAOb + jb] = acc;
          }
        }
        free(TA); free(TB);
      }

      /* per-AO normalization and scatter into both triangles */
      for (int ia = 0; ia < nAOa; ++ia) {
        const int32_t I = ao_off[sA] + ia;
        for (int jb = 0; jb < nAOb; ++jb) {
          const int32_t J = ao_off[sB] + jb;
          const double v = blk[ia * nAOb + jb] * ao_norm[I] * ao_norm[J];
          overlap[I * ao_num + J] = v;
          overlap[J * ao_num + I] = v;
        }
      }

      free(M); free(blk);
    }
  }

  rc = TREXIO_SUCCESS;

cleanup:
  free(coord);  free(nuc_idx); free(ang_mom); free(sh_fac); free(r_power);
  free(sh_idx); free(expo);    free(coef);    free(pfac);   free(ao_norm);
  free(ao_shell);
  free(prim_off); free(cursor); free(ao_off); free(pexpo);  free(pcoef);
  return rc;
}

trexio_exit_code
trexio_check_mo_orthonormality(trexio_t* const file, double* const max_deviation)
{
  if (file == NULL)          return TREXIO_INVALID_ARG_1;
  if (max_deviation == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;

  /* Real MO coefficients only. */
  if (trexio_has_mo_coefficient_im(file) == TREXIO_SUCCESS) return TREXIO_NOT_IMPLEMENTED;

  int32_t ao_num = 0, mo_num = 0;
  if ((rc = trexio_read_ao_num(file, &ao_num)) != TREXIO_SUCCESS) return rc;
  if ((rc = trexio_read_mo_num(file, &mo_num)) != TREXIO_SUCCESS) return rc;

  double* S  = malloc(sizeof(double) * (size_t) ao_num * (size_t) ao_num);
  double* C  = malloc(sizeof(double) * (size_t) mo_num * (size_t) ao_num);
  double* SC = malloc(sizeof(double) * (size_t) ao_num * (size_t) mo_num);

  rc = TREXIO_ALLOCATION_FAILED;
  if (!S || !C || !SC) goto cleanup;

  if ((rc = trexio_compute_ao_overlap(file, (int64_t) ao_num * ao_num, S)) != TREXIO_SUCCESS) goto cleanup;
  if ((rc = trexio_read_mo_coefficient(file, C))  != TREXIO_SUCCESS) goto cleanup;
  /* C is row-major [mo_num, ao_num]: C[i*ao_num + a] = c_{i a}. */

  /* SC[a,j] = sum_b S[a,b] C[j,b]   (ao_num x mo_num) */
  for (int32_t a = 0; a < ao_num; ++a)
    for (int32_t j = 0; j < mo_num; ++j) {
      double acc = 0.0;
      for (int32_t b = 0; b < ao_num; ++b)
        acc += S[(size_t) a * ao_num + b] * C[(size_t) j * ao_num + b];
      SC[(size_t) a * mo_num + j] = acc;
    }

  /* O[i,j] = sum_a C[i,a] SC[a,j]; track max | O - I |. */
  double dev = 0.0;
  for (int32_t i = 0; i < mo_num; ++i)
    for (int32_t j = 0; j < mo_num; ++j) {
      double acc = 0.0;
      for (int32_t a = 0; a < ao_num; ++a)
        acc += C[(size_t) i * ao_num + a] * SC[(size_t) a * mo_num + j];
      const double d = fabs(acc - (i == j ? 1.0 : 0.0));
      if (d > dev) dev = d;
    }
  *max_deviation = dev;
  rc = TREXIO_SUCCESS;

cleanup:
  free(S); free(C); free(SC);
  return rc;
}

trexio_exit_code
trexio_check_rdm_1e_trace(trexio_t* const file, double* const trace)
{
  if (file == NULL)  return TREXIO_INVALID_ARG_1;
  if (trace == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  int32_t mo_num = 0;
  if ((rc = trexio_read_mo_num(file, &mo_num)) != TREXIO_SUCCESS) return rc;

  double* g = malloc(sizeof(double) * (size_t) mo_num * (size_t) mo_num);
  if (g == NULL) return TREXIO_ALLOCATION_FAILED;

  rc = trexio_read_rdm_1e(file, g);
  if (rc == TREXIO_SUCCESS) {
    double tr = 0.0;
    for (int32_t i = 0; i < mo_num; ++i) tr += g[(size_t) i * mo_num + i];
    *trace = tr;
  }

  free(g);
  return rc;
}
