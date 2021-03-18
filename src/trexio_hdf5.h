/* This file was generated from the org-mode file.
   To generate it, open templator_hdf5.org file in Emacs and execute
   M-x org-babel-tangle
*/

#ifndef _TREXIO_HDF5_H
#define _TREXIO_HDF5_H

#include "trexio.h"
#include "trexio_s.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

#include "hdf5.h"
#include "hdf5_hl.h" // needed for high-level APIs like H5LT, requires additional linking in Makefile
typedef struct trexio_hdf5_s {
  trexio_t     parent ;
  hid_t      file_id;
  hid_t      nucleus_group;
  hid_t      ecp_group;
  const char* file_name;
} trexio_hdf5_t;

trexio_exit_code trexio_hdf5_init(trexio_t* file);
trexio_exit_code trexio_hdf5_finalize(trexio_t* file);
trexio_exit_code trexio_hdf5_read_nucleus_num (const trexio_t* file, uint64_t* num);
trexio_exit_code trexio_hdf5_write_nucleus_num (const trexio_t* file, const uint64_t num);
trexio_exit_code trexio_hdf5_read_ecp_local_num_n_max (const trexio_t* file, uint64_t* num);
trexio_exit_code trexio_hdf5_write_ecp_local_num_n_max (const trexio_t* file, const uint64_t num);
trexio_exit_code trexio_hdf5_read_ecp_non_local_num_n_max (const trexio_t* file, uint64_t* num);
trexio_exit_code trexio_hdf5_write_ecp_non_local_num_n_max (const trexio_t* file, const uint64_t num);
trexio_exit_code trexio_hdf5_read_nucleus_charge(const trexio_t* file, double* nucleus_charge, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_nucleus_charge(const trexio_t* file, const double* nucleus_charge, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_read_nucleus_coord(const trexio_t* file, double* nucleus_coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_nucleus_coord(const trexio_t* file, const double* nucleus_coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_read_ecp_lmax_plus_1(const trexio_t* file, int64_t* ecp_lmax_plus_1, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_lmax_plus_1(const trexio_t* file, const int64_t* ecp_lmax_plus_1, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_read_ecp_z_core(const trexio_t* file, int64_t* ecp_z_core, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_z_core(const trexio_t* file, const int64_t* ecp_z_core, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_read_ecp_local_n(const trexio_t* file, int64_t* ecp_local_n, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_local_n(const trexio_t* file, const int64_t* ecp_local_n, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_read_ecp_local_exponent(const trexio_t* file, double* ecp_local_exponent, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_local_exponent(const trexio_t* file, const double* ecp_local_exponent, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_read_ecp_local_coef(const trexio_t* file, double* ecp_local_coef, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_local_coef(const trexio_t* file, const double* ecp_local_coef, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_read_ecp_local_power(const trexio_t* file, int64_t* ecp_local_power, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_local_power(const trexio_t* file, const int64_t* ecp_local_power, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_read_ecp_non_local_n(const trexio_t* file, int64_t* ecp_non_local_n, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_non_local_n(const trexio_t* file, const int64_t* ecp_non_local_n, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_read_ecp_non_local_exponent(const trexio_t* file, double* ecp_non_local_exponent, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_non_local_exponent(const trexio_t* file, const double* ecp_non_local_exponent, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_read_ecp_non_local_coef(const trexio_t* file, double* ecp_non_local_coef, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_non_local_coef(const trexio_t* file, const double* ecp_non_local_coef, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_read_ecp_non_local_power(const trexio_t* file, int64_t* ecp_non_local_power, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_non_local_power(const trexio_t* file, const int64_t* ecp_non_local_power, const uint32_t rank, const uint64_t* dims);
#endif
