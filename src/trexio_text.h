/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/



#ifndef _TREXIO_TEXT_H
#define _TREXIO_TEXT_H

#include "trexio.h"
#include "trexio_private.h"
#include "trexio_s.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
typedef struct nucleus_s {
  FILE*    file;
  double*  nucleus_charge;
  double*  nucleus_coord;
  uint64_t nucleus_num;
  uint64_t dims_nucleus_charge[16];
  uint64_t dims_nucleus_coord[16];
  uint32_t rank_nucleus_charge;
  uint32_t rank_nucleus_coord;
  int      to_flush;
} nucleus_t;
typedef struct ecp_s {
  FILE*    file;
  int64_t*  ecp_lmax_plus_1;
  int64_t*  ecp_z_core;
  int64_t*  ecp_local_n;
  double*  ecp_local_exponent;
  double*  ecp_local_coef;
  int64_t*  ecp_local_power;
  int64_t*  ecp_non_local_n;
  double*  ecp_non_local_exponent;
  double*  ecp_non_local_coef;
  int64_t*  ecp_non_local_power;
  uint64_t ecp_local_num_n_max;
  uint64_t ecp_non_local_num_n_max;
  uint64_t dims_ecp_lmax_plus_1[16];
  uint64_t dims_ecp_z_core[16];
  uint64_t dims_ecp_local_n[16];
  uint64_t dims_ecp_local_exponent[16];
  uint64_t dims_ecp_local_coef[16];
  uint64_t dims_ecp_local_power[16];
  uint64_t dims_ecp_non_local_n[16];
  uint64_t dims_ecp_non_local_exponent[16];
  uint64_t dims_ecp_non_local_coef[16];
  uint64_t dims_ecp_non_local_power[16];
  uint32_t rank_ecp_lmax_plus_1;
  uint32_t rank_ecp_z_core;
  uint32_t rank_ecp_local_n;
  uint32_t rank_ecp_local_exponent;
  uint32_t rank_ecp_local_coef;
  uint32_t rank_ecp_local_power;
  uint32_t rank_ecp_non_local_n;
  uint32_t rank_ecp_non_local_exponent;
  uint32_t rank_ecp_non_local_coef;
  uint32_t rank_ecp_non_local_power;
  int      to_flush;
} ecp_t;
typedef struct rdm_s {
  FILE*    file;
  uint64_t dim_one_e;
  double*  one_e;
  char*    two_e_file_name;
  int      to_flush;
} rdm_t;

typedef struct trexio_text_s {
  trexio_t   parent ;
  int        lock_file;
  nucleus_t* nucleus;
  ecp_t* ecp;
  rdm_t*      rdm;
} trexio_text_t;
trexio_exit_code trexio_text_init(trexio_t* file);

trexio_exit_code trexio_text_lock(trexio_t* file);

trexio_exit_code trexio_text_finalize(trexio_t* file);

trexio_exit_code trexio_text_unlock(trexio_t* file);
trexio_exit_code trexio_text_free_nucleus(trexio_text_t* file);
trexio_exit_code trexio_text_free_ecp(trexio_text_t* file);
nucleus_t* trexio_text_read_nucleus(trexio_text_t* file);
ecp_t* trexio_text_read_ecp(trexio_text_t* file);
trexio_exit_code trexio_text_flush_nucleus(const trexio_text_t* file);
trexio_exit_code trexio_text_flush_ecp(const trexio_text_t* file);
trexio_exit_code trexio_text_read_nucleus_num(const trexio_t* file, uint64_t* num);
trexio_exit_code trexio_text_write_nucleus_num(const trexio_t* file, const uint64_t num);
trexio_exit_code trexio_text_read_ecp_local_num_n_max(const trexio_t* file, uint64_t* num);
trexio_exit_code trexio_text_write_ecp_local_num_n_max(const trexio_t* file, const uint64_t num);
trexio_exit_code trexio_text_read_ecp_non_local_num_n_max(const trexio_t* file, uint64_t* num);
trexio_exit_code trexio_text_write_ecp_non_local_num_n_max(const trexio_t* file, const uint64_t num);
trexio_exit_code trexio_text_read_nucleus_charge(const trexio_t* file, double* nucleus_charge, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_nucleus_charge(const trexio_t* file, const double* nucleus_charge, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_read_nucleus_coord(const trexio_t* file, double* nucleus_coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_nucleus_coord(const trexio_t* file, const double* nucleus_coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_read_ecp_lmax_plus_1(const trexio_t* file, int64_t* ecp_lmax_plus_1, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_lmax_plus_1(const trexio_t* file, const int64_t* ecp_lmax_plus_1, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_read_ecp_z_core(const trexio_t* file, int64_t* ecp_z_core, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_z_core(const trexio_t* file, const int64_t* ecp_z_core, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_read_ecp_local_n(const trexio_t* file, int64_t* ecp_local_n, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_local_n(const trexio_t* file, const int64_t* ecp_local_n, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_read_ecp_local_exponent(const trexio_t* file, double* ecp_local_exponent, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_local_exponent(const trexio_t* file, const double* ecp_local_exponent, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_read_ecp_local_coef(const trexio_t* file, double* ecp_local_coef, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_local_coef(const trexio_t* file, const double* ecp_local_coef, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_read_ecp_local_power(const trexio_t* file, int64_t* ecp_local_power, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_local_power(const trexio_t* file, const int64_t* ecp_local_power, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_read_ecp_non_local_n(const trexio_t* file, int64_t* ecp_non_local_n, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_non_local_n(const trexio_t* file, const int64_t* ecp_non_local_n, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_read_ecp_non_local_exponent(const trexio_t* file, double* ecp_non_local_exponent, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_non_local_exponent(const trexio_t* file, const double* ecp_non_local_exponent, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_read_ecp_non_local_coef(const trexio_t* file, double* ecp_non_local_coef, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_non_local_coef(const trexio_t* file, const double* ecp_non_local_coef, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_read_ecp_non_local_power(const trexio_t* file, int64_t* ecp_non_local_power, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_non_local_power(const trexio_t* file, const int64_t* ecp_non_local_power, const uint32_t rank, const uint64_t* dims);
rdm_t* trexio_text_read_rdm(trexio_text_t* file);

trexio_exit_code trexio_text_flush_rdm(const trexio_text_t* file);

trexio_exit_code trexio_text_free_rdm(trexio_text_t* file);

trexio_exit_code trexio_text_read_rdm_one_e(const trexio_t* file, double* one_e, const uint64_t dim_one_e);
trexio_exit_code trexio_text_write_rdm_one_e(const trexio_t* file, const double* one_e, const uint64_t dim_one_e);

trexio_exit_code trexio_text_buffered_read_rdm_two_e(const trexio_t* file, const uint64_t offset, const uint64_t size, int64_t* index, double* value);
trexio_exit_code trexio_text_buffered_write_rdm_two_e(const trexio_t* file, const uint64_t offset, const uint64_t size, const int64_t* index, const double* value);
#endif
