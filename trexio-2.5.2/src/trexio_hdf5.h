/* This file was generated from the org-mode file.
   To generate it, open templator_hdf5.org file in Emacs and execute
   M-x org-babel-tangle
*/

#ifndef TREXIO_HDF5_H
#define TREXIO_HDF5_H

#include "trexio.h"
#include "trexio_private.h"
#include "trexio_s.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif
#
#ifdef HAVE_HDF5
#include "hdf5.h"
typedef struct trexio_hdf5_s {
  trexio_t     parent ;
  hid_t        file_id;
  hid_t        metadata_group;
  hid_t        nucleus_group;
  hid_t        cell_group;
  hid_t        pbc_group;
  hid_t        electron_group;
  hid_t        state_group;
  hid_t        basis_group;
  hid_t        ecp_group;
  hid_t        grid_group;
  hid_t        ao_group;
  hid_t        ao_1e_int_group;
  hid_t        ao_2e_int_group;
  hid_t        mo_group;
  hid_t        mo_1e_int_group;
  hid_t        mo_2e_int_group;
  hid_t        determinant_group;
  hid_t        csf_group;
  hid_t        amplitude_group;
  hid_t        rdm_group;
  hid_t        jastrow_group;
  hid_t        qmc_group;
} trexio_hdf5_t;

trexio_exit_code trexio_hdf5_init(trexio_t* const file);
trexio_exit_code trexio_hdf5_deinit(trexio_t* const file);
trexio_exit_code trexio_hdf5_inquire(const char* file_name);
trexio_exit_code trexio_hdf5_flush(trexio_t* const file);

trexio_exit_code trexio_hdf5_has_metadata_code_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_metadata_code_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_metadata_code_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_metadata_author_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_metadata_author_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_metadata_author_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_metadata_unsafe (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_metadata_unsafe (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_metadata_unsafe(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_nucleus_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_nucleus_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_nucleus_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_nucleus_repulsion (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_nucleus_repulsion (trexio_t* const file, double* const num);
trexio_exit_code trexio_hdf5_write_nucleus_repulsion(trexio_t* const file, const double num);

trexio_exit_code trexio_hdf5_has_cell_two_pi (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_cell_two_pi (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_cell_two_pi(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_pbc_periodic (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_pbc_periodic (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_pbc_periodic(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_pbc_k_point_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_pbc_k_point_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_pbc_k_point_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_pbc_madelung (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_pbc_madelung (trexio_t* const file, double* const num);
trexio_exit_code trexio_hdf5_write_pbc_madelung(trexio_t* const file, const double num);

trexio_exit_code trexio_hdf5_has_electron_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_electron_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_electron_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_electron_up_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_electron_up_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_electron_up_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_electron_dn_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_electron_dn_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_electron_dn_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_state_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_state_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_state_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_state_id (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_state_id (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_state_id(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_state_energy (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_state_energy (trexio_t* const file, double* const num);
trexio_exit_code trexio_hdf5_write_state_energy(trexio_t* const file, const double num);

trexio_exit_code trexio_hdf5_has_basis_prim_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_prim_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_basis_prim_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_basis_shell_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_shell_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_basis_shell_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_basis_nao_grid_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_nao_grid_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_basis_nao_grid_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_basis_interp_coeff_cnt (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_interp_coeff_cnt (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_basis_interp_coeff_cnt(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_basis_e_cut (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_e_cut (trexio_t* const file, double* const num);
trexio_exit_code trexio_hdf5_write_basis_e_cut(trexio_t* const file, const double num);

trexio_exit_code trexio_hdf5_has_ecp_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ecp_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_ecp_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_grid_rad_precision (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_rad_precision (trexio_t* const file, double* const num);
trexio_exit_code trexio_hdf5_write_grid_rad_precision(trexio_t* const file, const double num);

trexio_exit_code trexio_hdf5_has_grid_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_grid_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_grid_max_ang_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_max_ang_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_grid_max_ang_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_grid_min_ang_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_min_ang_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_grid_min_ang_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_grid_ang_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_ang_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_grid_ang_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_grid_rad_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_rad_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_grid_rad_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_ao_cartesian (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_cartesian (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_ao_cartesian(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_ao_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_ao_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_ao_2e_int_eri_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_2e_int_eri_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_ao_2e_int_eri_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_ao_2e_int_eri_lr_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_2e_int_eri_lr_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_ao_2e_int_eri_lr_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_mo_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_mo_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_mo_2e_int_eri_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_2e_int_eri_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_mo_2e_int_eri_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_mo_2e_int_eri_lr_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_2e_int_eri_lr_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_mo_2e_int_eri_lr_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_determinant_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_determinant_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_determinant_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_csf_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_csf_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_csf_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_rdm_2e_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_rdm_2e_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_rdm_2e_upup_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e_upup_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_rdm_2e_upup_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_rdm_2e_dndn_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e_dndn_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_rdm_2e_dndn_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_rdm_2e_updn_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e_updn_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_rdm_2e_updn_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_jastrow_en_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_jastrow_en_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_jastrow_en_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_jastrow_ee_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_jastrow_ee_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_jastrow_ee_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_jastrow_een_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_jastrow_een_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_jastrow_een_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_jastrow_ee_scaling (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_jastrow_ee_scaling (trexio_t* const file, double* const num);
trexio_exit_code trexio_hdf5_write_jastrow_ee_scaling(trexio_t* const file, const double num);

trexio_exit_code trexio_hdf5_has_qmc_num (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_qmc_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_hdf5_write_qmc_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_hdf5_has_metadata_package_version (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_metadata_package_version (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_metadata_package_version(trexio_t* const file, const char* str);

trexio_exit_code trexio_hdf5_has_metadata_description (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_metadata_description (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_metadata_description(trexio_t* const file, const char* str);

trexio_exit_code trexio_hdf5_has_nucleus_point_group (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_nucleus_point_group (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_nucleus_point_group(trexio_t* const file, const char* str);

trexio_exit_code trexio_hdf5_has_state_current_label (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_state_current_label (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_state_current_label(trexio_t* const file, const char* str);

trexio_exit_code trexio_hdf5_has_basis_type (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_type (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_basis_type(trexio_t* const file, const char* str);

trexio_exit_code trexio_hdf5_has_basis_oscillation_kind (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_oscillation_kind (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_basis_oscillation_kind(trexio_t* const file, const char* str);

trexio_exit_code trexio_hdf5_has_basis_interpolator_kind (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_interpolator_kind (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_basis_interpolator_kind(trexio_t* const file, const char* str);

trexio_exit_code trexio_hdf5_has_grid_description (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_description (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_grid_description(trexio_t* const file, const char* str);

trexio_exit_code trexio_hdf5_has_mo_type (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_type (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_mo_type(trexio_t* const file, const char* str);

trexio_exit_code trexio_hdf5_has_jastrow_type (trexio_t* const file);
trexio_exit_code trexio_hdf5_read_jastrow_type (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_jastrow_type(trexio_t* const file, const char* str);

trexio_exit_code trexio_hdf5_has_determinant_coefficient(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_determinant_coefficient(trexio_t* const file, const int64_t offset_file, const uint32_t rank, const uint64_t* dims, int64_t* const eof_read_size, double* const dset);
trexio_exit_code trexio_hdf5_write_determinant_coefficient(trexio_t* const file, const int64_t offset_file, const uint32_t rank, const uint64_t* dims, const double* dset);
trexio_exit_code trexio_hdf5_read_determinant_coefficient_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_csf_coefficient(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_csf_coefficient(trexio_t* const file, const int64_t offset_file, const uint32_t rank, const uint64_t* dims, int64_t* const eof_read_size, double* const dset);
trexio_exit_code trexio_hdf5_write_csf_coefficient(trexio_t* const file, const int64_t offset_file, const uint32_t rank, const uint64_t* dims, const double* dset);
trexio_exit_code trexio_hdf5_read_csf_coefficient_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_nucleus_charge(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_nucleus_charge(trexio_t* const file, double* const nucleus_charge, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_nucleus_charge(trexio_t* const file, const double* nucleus_charge, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_nucleus_coord(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_nucleus_coord(trexio_t* const file, double* const nucleus_coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_nucleus_coord(trexio_t* const file, const double* nucleus_coord, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_cell_a(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_cell_a(trexio_t* const file, double* const cell_a, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_cell_a(trexio_t* const file, const double* cell_a, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_cell_b(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_cell_b(trexio_t* const file, double* const cell_b, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_cell_b(trexio_t* const file, const double* cell_b, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_cell_c(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_cell_c(trexio_t* const file, double* const cell_c, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_cell_c(trexio_t* const file, const double* cell_c, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_cell_g_a(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_cell_g_a(trexio_t* const file, double* const cell_g_a, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_cell_g_a(trexio_t* const file, const double* cell_g_a, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_cell_g_b(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_cell_g_b(trexio_t* const file, double* const cell_g_b, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_cell_g_b(trexio_t* const file, const double* cell_g_b, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_cell_g_c(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_cell_g_c(trexio_t* const file, double* const cell_g_c, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_cell_g_c(trexio_t* const file, const double* cell_g_c, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_pbc_k_point(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_pbc_k_point(trexio_t* const file, double* const pbc_k_point, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_pbc_k_point(trexio_t* const file, const double* pbc_k_point, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_pbc_k_point_weight(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_pbc_k_point_weight(trexio_t* const file, double* const pbc_k_point_weight, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_pbc_k_point_weight(trexio_t* const file, const double* pbc_k_point_weight, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_nucleus_index(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_nucleus_index(trexio_t* const file, int64_t* const basis_nucleus_index, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_nucleus_index(trexio_t* const file, const int64_t* basis_nucleus_index, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_shell_ang_mom(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_shell_ang_mom(trexio_t* const file, int64_t* const basis_shell_ang_mom, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_shell_ang_mom(trexio_t* const file, const int64_t* basis_shell_ang_mom, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_shell_factor(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_shell_factor(trexio_t* const file, double* const basis_shell_factor, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_shell_factor(trexio_t* const file, const double* basis_shell_factor, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_r_power(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_r_power(trexio_t* const file, int64_t* const basis_r_power, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_r_power(trexio_t* const file, const int64_t* basis_r_power, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_nao_grid_start(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_nao_grid_start(trexio_t* const file, int64_t* const basis_nao_grid_start, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_nao_grid_start(trexio_t* const file, const int64_t* basis_nao_grid_start, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_nao_grid_size(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_nao_grid_size(trexio_t* const file, int64_t* const basis_nao_grid_size, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_nao_grid_size(trexio_t* const file, const int64_t* basis_nao_grid_size, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_shell_index(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_shell_index(trexio_t* const file, int64_t* const basis_shell_index, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_shell_index(trexio_t* const file, const int64_t* basis_shell_index, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_exponent(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_exponent(trexio_t* const file, double* const basis_exponent, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_exponent(trexio_t* const file, const double* basis_exponent, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_exponent_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_exponent_im(trexio_t* const file, double* const basis_exponent_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_exponent_im(trexio_t* const file, const double* basis_exponent_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_coefficient(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_coefficient(trexio_t* const file, double* const basis_coefficient, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_coefficient(trexio_t* const file, const double* basis_coefficient, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_coefficient_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_coefficient_im(trexio_t* const file, double* const basis_coefficient_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_coefficient_im(trexio_t* const file, const double* basis_coefficient_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_oscillation_arg(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_oscillation_arg(trexio_t* const file, double* const basis_oscillation_arg, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_oscillation_arg(trexio_t* const file, const double* basis_oscillation_arg, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_prim_factor(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_prim_factor(trexio_t* const file, double* const basis_prim_factor, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_prim_factor(trexio_t* const file, const double* basis_prim_factor, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_nao_grid_radius(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_nao_grid_radius(trexio_t* const file, double* const basis_nao_grid_radius, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_nao_grid_radius(trexio_t* const file, const double* basis_nao_grid_radius, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_nao_grid_phi(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_nao_grid_phi(trexio_t* const file, double* const basis_nao_grid_phi, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_nao_grid_phi(trexio_t* const file, const double* basis_nao_grid_phi, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_nao_grid_grad(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_nao_grid_grad(trexio_t* const file, double* const basis_nao_grid_grad, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_nao_grid_grad(trexio_t* const file, const double* basis_nao_grid_grad, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_nao_grid_lap(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_nao_grid_lap(trexio_t* const file, double* const basis_nao_grid_lap, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_nao_grid_lap(trexio_t* const file, const double* basis_nao_grid_lap, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_interpolator_phi(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_interpolator_phi(trexio_t* const file, double* const basis_interpolator_phi, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_interpolator_phi(trexio_t* const file, const double* basis_interpolator_phi, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_interpolator_grad(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_interpolator_grad(trexio_t* const file, double* const basis_interpolator_grad, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_interpolator_grad(trexio_t* const file, const double* basis_interpolator_grad, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_basis_interpolator_lap(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_basis_interpolator_lap(trexio_t* const file, double* const basis_interpolator_lap, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_basis_interpolator_lap(trexio_t* const file, const double* basis_interpolator_lap, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ecp_max_ang_mom_plus_1(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ecp_max_ang_mom_plus_1(trexio_t* const file, int64_t* const ecp_max_ang_mom_plus_1, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_max_ang_mom_plus_1(trexio_t* const file, const int64_t* ecp_max_ang_mom_plus_1, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ecp_z_core(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ecp_z_core(trexio_t* const file, int64_t* const ecp_z_core, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_z_core(trexio_t* const file, const int64_t* ecp_z_core, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ecp_ang_mom(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ecp_ang_mom(trexio_t* const file, int64_t* const ecp_ang_mom, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_ang_mom(trexio_t* const file, const int64_t* ecp_ang_mom, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ecp_nucleus_index(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ecp_nucleus_index(trexio_t* const file, int64_t* const ecp_nucleus_index, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_nucleus_index(trexio_t* const file, const int64_t* ecp_nucleus_index, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ecp_exponent(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ecp_exponent(trexio_t* const file, double* const ecp_exponent, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_exponent(trexio_t* const file, const double* ecp_exponent, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ecp_coefficient(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ecp_coefficient(trexio_t* const file, double* const ecp_coefficient, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_coefficient(trexio_t* const file, const double* ecp_coefficient, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ecp_power(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ecp_power(trexio_t* const file, int64_t* const ecp_power, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ecp_power(trexio_t* const file, const int64_t* ecp_power, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_grid_coord(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_coord(trexio_t* const file, double* const grid_coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_grid_coord(trexio_t* const file, const double* grid_coord, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_grid_weight(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_weight(trexio_t* const file, double* const grid_weight, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_grid_weight(trexio_t* const file, const double* grid_weight, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_grid_ang_coord(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_ang_coord(trexio_t* const file, double* const grid_ang_coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_grid_ang_coord(trexio_t* const file, const double* grid_ang_coord, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_grid_ang_weight(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_ang_weight(trexio_t* const file, double* const grid_ang_weight, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_grid_ang_weight(trexio_t* const file, const double* grid_ang_weight, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_grid_rad_coord(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_rad_coord(trexio_t* const file, double* const grid_rad_coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_grid_rad_coord(trexio_t* const file, const double* grid_rad_coord, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_grid_rad_weight(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_grid_rad_weight(trexio_t* const file, double* const grid_rad_weight, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_grid_rad_weight(trexio_t* const file, const double* grid_rad_weight, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_shell(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_shell(trexio_t* const file, int64_t* const ao_shell, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ao_shell(trexio_t* const file, const int64_t* ao_shell, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_normalization(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_normalization(trexio_t* const file, double* const ao_normalization, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ao_normalization(trexio_t* const file, const double* ao_normalization, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_1e_int_overlap(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_1e_int_overlap(trexio_t* const file, double* const ao_1e_int_overlap, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ao_1e_int_overlap(trexio_t* const file, const double* ao_1e_int_overlap, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_1e_int_kinetic(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_1e_int_kinetic(trexio_t* const file, double* const ao_1e_int_kinetic, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ao_1e_int_kinetic(trexio_t* const file, const double* ao_1e_int_kinetic, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_1e_int_potential_n_e(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_1e_int_potential_n_e(trexio_t* const file, double* const ao_1e_int_potential_n_e, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ao_1e_int_potential_n_e(trexio_t* const file, const double* ao_1e_int_potential_n_e, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_1e_int_ecp(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_1e_int_ecp(trexio_t* const file, double* const ao_1e_int_ecp, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ao_1e_int_ecp(trexio_t* const file, const double* ao_1e_int_ecp, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_1e_int_core_hamiltonian(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_1e_int_core_hamiltonian(trexio_t* const file, double* const ao_1e_int_core_hamiltonian, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ao_1e_int_core_hamiltonian(trexio_t* const file, const double* ao_1e_int_core_hamiltonian, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_1e_int_overlap_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_1e_int_overlap_im(trexio_t* const file, double* const ao_1e_int_overlap_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ao_1e_int_overlap_im(trexio_t* const file, const double* ao_1e_int_overlap_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_1e_int_kinetic_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_1e_int_kinetic_im(trexio_t* const file, double* const ao_1e_int_kinetic_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ao_1e_int_kinetic_im(trexio_t* const file, const double* ao_1e_int_kinetic_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_1e_int_potential_n_e_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_1e_int_potential_n_e_im(trexio_t* const file, double* const ao_1e_int_potential_n_e_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ao_1e_int_potential_n_e_im(trexio_t* const file, const double* ao_1e_int_potential_n_e_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_1e_int_ecp_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_1e_int_ecp_im(trexio_t* const file, double* const ao_1e_int_ecp_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ao_1e_int_ecp_im(trexio_t* const file, const double* ao_1e_int_ecp_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_1e_int_core_hamiltonian_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_1e_int_core_hamiltonian_im(trexio_t* const file, double* const ao_1e_int_core_hamiltonian_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_ao_1e_int_core_hamiltonian_im(trexio_t* const file, const double* ao_1e_int_core_hamiltonian_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_coefficient(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_coefficient(trexio_t* const file, double* const mo_coefficient, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_coefficient(trexio_t* const file, const double* mo_coefficient, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_coefficient_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_coefficient_im(trexio_t* const file, double* const mo_coefficient_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_coefficient_im(trexio_t* const file, const double* mo_coefficient_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_occupation(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_occupation(trexio_t* const file, double* const mo_occupation, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_occupation(trexio_t* const file, const double* mo_occupation, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_energy(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_energy(trexio_t* const file, double* const mo_energy, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_energy(trexio_t* const file, const double* mo_energy, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_spin(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_spin(trexio_t* const file, int64_t* const mo_spin, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_spin(trexio_t* const file, const int64_t* mo_spin, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_k_point(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_k_point(trexio_t* const file, int64_t* const mo_k_point, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_k_point(trexio_t* const file, const int64_t* mo_k_point, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_1e_int_overlap(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_1e_int_overlap(trexio_t* const file, double* const mo_1e_int_overlap, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_1e_int_overlap(trexio_t* const file, const double* mo_1e_int_overlap, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_1e_int_kinetic(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_1e_int_kinetic(trexio_t* const file, double* const mo_1e_int_kinetic, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_1e_int_kinetic(trexio_t* const file, const double* mo_1e_int_kinetic, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_1e_int_potential_n_e(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_1e_int_potential_n_e(trexio_t* const file, double* const mo_1e_int_potential_n_e, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_1e_int_potential_n_e(trexio_t* const file, const double* mo_1e_int_potential_n_e, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_1e_int_ecp(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_1e_int_ecp(trexio_t* const file, double* const mo_1e_int_ecp, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_1e_int_ecp(trexio_t* const file, const double* mo_1e_int_ecp, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_1e_int_core_hamiltonian(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_1e_int_core_hamiltonian(trexio_t* const file, double* const mo_1e_int_core_hamiltonian, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_1e_int_core_hamiltonian(trexio_t* const file, const double* mo_1e_int_core_hamiltonian, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_1e_int_overlap_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_1e_int_overlap_im(trexio_t* const file, double* const mo_1e_int_overlap_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_1e_int_overlap_im(trexio_t* const file, const double* mo_1e_int_overlap_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_1e_int_kinetic_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_1e_int_kinetic_im(trexio_t* const file, double* const mo_1e_int_kinetic_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_1e_int_kinetic_im(trexio_t* const file, const double* mo_1e_int_kinetic_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_1e_int_potential_n_e_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_1e_int_potential_n_e_im(trexio_t* const file, double* const mo_1e_int_potential_n_e_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_1e_int_potential_n_e_im(trexio_t* const file, const double* mo_1e_int_potential_n_e_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_1e_int_ecp_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_1e_int_ecp_im(trexio_t* const file, double* const mo_1e_int_ecp_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_1e_int_ecp_im(trexio_t* const file, const double* mo_1e_int_ecp_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_1e_int_core_hamiltonian_im(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_1e_int_core_hamiltonian_im(trexio_t* const file, double* const mo_1e_int_core_hamiltonian_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_mo_1e_int_core_hamiltonian_im(trexio_t* const file, const double* mo_1e_int_core_hamiltonian_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_rdm_1e(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_1e(trexio_t* const file, double* const rdm_1e, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_rdm_1e(trexio_t* const file, const double* rdm_1e, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_rdm_1e_up(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_1e_up(trexio_t* const file, double* const rdm_1e_up, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_rdm_1e_up(trexio_t* const file, const double* rdm_1e_up, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_rdm_1e_dn(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_1e_dn(trexio_t* const file, double* const rdm_1e_dn, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_rdm_1e_dn(trexio_t* const file, const double* rdm_1e_dn, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_rdm_1e_transition(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_1e_transition(trexio_t* const file, double* const rdm_1e_transition, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_rdm_1e_transition(trexio_t* const file, const double* rdm_1e_transition, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_jastrow_en(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_jastrow_en(trexio_t* const file, double* const jastrow_en, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_jastrow_en(trexio_t* const file, const double* jastrow_en, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_jastrow_ee(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_jastrow_ee(trexio_t* const file, double* const jastrow_ee, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_jastrow_ee(trexio_t* const file, const double* jastrow_ee, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_jastrow_een(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_jastrow_een(trexio_t* const file, double* const jastrow_een, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_jastrow_een(trexio_t* const file, const double* jastrow_een, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_jastrow_en_nucleus(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_jastrow_en_nucleus(trexio_t* const file, int64_t* const jastrow_en_nucleus, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_jastrow_en_nucleus(trexio_t* const file, const int64_t* jastrow_en_nucleus, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_jastrow_een_nucleus(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_jastrow_een_nucleus(trexio_t* const file, int64_t* const jastrow_een_nucleus, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_jastrow_een_nucleus(trexio_t* const file, const int64_t* jastrow_een_nucleus, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_jastrow_en_scaling(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_jastrow_en_scaling(trexio_t* const file, double* const jastrow_en_scaling, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_jastrow_en_scaling(trexio_t* const file, const double* jastrow_en_scaling, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_qmc_point(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_qmc_point(trexio_t* const file, double* const qmc_point, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_qmc_point(trexio_t* const file, const double* qmc_point, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_qmc_psi(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_qmc_psi(trexio_t* const file, double* const qmc_psi, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_qmc_psi(trexio_t* const file, const double* qmc_psi, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_qmc_e_loc(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_qmc_e_loc(trexio_t* const file, double* const qmc_e_loc, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_qmc_e_loc(trexio_t* const file, const double* qmc_e_loc, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_ao_2e_int_eri(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_2e_int_eri(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_ao_2e_int_eri(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_ao_2e_int_eri_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_ao_2e_int_eri_lr(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_ao_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_ao_2e_int_eri_lr_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_ao_2e_int_eri_cholesky(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_ao_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_ao_2e_int_eri_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_ao_2e_int_eri_lr_cholesky(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_ao_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_ao_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_ao_2e_int_eri_lr_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_mo_2e_int_eri(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_2e_int_eri(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_mo_2e_int_eri(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_mo_2e_int_eri_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_mo_2e_int_eri_lr(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_mo_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_mo_2e_int_eri_lr_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_mo_2e_int_eri_cholesky(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_mo_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_mo_2e_int_eri_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_mo_2e_int_eri_lr_cholesky(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_mo_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_mo_2e_int_eri_lr_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_csf_det_coefficient(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_csf_det_coefficient(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_csf_det_coefficient(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_csf_det_coefficient_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_amplitude_single(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_amplitude_single(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_amplitude_single(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_amplitude_single_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_amplitude_single_exp(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_amplitude_single_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_amplitude_single_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_amplitude_single_exp_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_amplitude_double(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_amplitude_double(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_amplitude_double(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_amplitude_double_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_amplitude_double_exp(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_amplitude_double_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_amplitude_double_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_amplitude_double_exp_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_amplitude_triple(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_amplitude_triple(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_amplitude_triple(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_amplitude_triple_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_amplitude_triple_exp(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_amplitude_triple_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_amplitude_triple_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_amplitude_triple_exp_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_amplitude_quadruple(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_amplitude_quadruple(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_amplitude_quadruple(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_amplitude_quadruple_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_amplitude_quadruple_exp(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_amplitude_quadruple_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_amplitude_quadruple_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_amplitude_quadruple_exp_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_rdm_2e(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_rdm_2e(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_rdm_2e_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_rdm_2e_upup(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e_upup(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_rdm_2e_upup(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_rdm_2e_upup_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_rdm_2e_dndn(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e_dndn(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_rdm_2e_dndn(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_rdm_2e_dndn_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_rdm_2e_updn(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e_updn(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_rdm_2e_updn(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_rdm_2e_updn_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_rdm_2e_transition(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e_transition(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_rdm_2e_transition(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_rdm_2e_transition_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_rdm_2e_cholesky(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_rdm_2e_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_rdm_2e_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_rdm_2e_upup_cholesky(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e_upup_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_rdm_2e_upup_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_rdm_2e_upup_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_rdm_2e_dndn_cholesky(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e_dndn_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_rdm_2e_dndn_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_rdm_2e_dndn_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_rdm_2e_updn_cholesky(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_rdm_2e_updn_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_hdf5_write_rdm_2e_updn_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_hdf5_read_rdm_2e_updn_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_hdf5_has_metadata_code(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_metadata_code(trexio_t* const file, char* const metadata_code, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_metadata_code(trexio_t* const file, const char** metadata_code, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_metadata_author(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_metadata_author(trexio_t* const file, char* const metadata_author, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_metadata_author(trexio_t* const file, const char** metadata_author, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_nucleus_label(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_nucleus_label(trexio_t* const file, char* const nucleus_label, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_nucleus_label(trexio_t* const file, const char** nucleus_label, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_state_label(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_state_label(trexio_t* const file, char* const state_label, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_state_label(trexio_t* const file, const char** state_label, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_state_file_name(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_state_file_name(trexio_t* const file, char* const state_file_name, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_state_file_name(trexio_t* const file, const char** state_file_name, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_class(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_class(trexio_t* const file, char* const mo_class, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_mo_class(trexio_t* const file, const char** mo_class, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_mo_symmetry(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_mo_symmetry(trexio_t* const file, char* const mo_symmetry, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_hdf5_write_mo_symmetry(trexio_t* const file, const char** mo_symmetry, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_hdf5_has_metadata (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_nucleus (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_cell (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_pbc (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_electron (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_state (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_basis (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_ecp (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_grid (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_ao (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_ao_1e_int (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_ao_2e_int (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_mo (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_mo_1e_int (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_mo_2e_int (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_determinant (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_csf (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_amplitude (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_rdm (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_jastrow (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_qmc (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_metadata (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_nucleus (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_cell (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_pbc (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_electron (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_state (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_basis (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_ecp (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_grid (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_ao (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_ao_1e_int (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_ao_2e_int (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_mo (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_mo_1e_int (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_mo_2e_int (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_determinant (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_csf (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_amplitude (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_rdm (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_jastrow (trexio_t* const file);

trexio_exit_code trexio_hdf5_delete_qmc (trexio_t* const file);

trexio_exit_code trexio_hdf5_has_determinant_list(trexio_t* const file);
trexio_exit_code trexio_hdf5_read_determinant_list(trexio_t* const file, const int64_t offset_file, const uint32_t rank, const uint64_t* dims, int64_t* const eof_read_size, int64_t* const list);
trexio_exit_code trexio_hdf5_write_determinant_list(trexio_t* const file, const int64_t offset_file, const uint32_t rank, const uint64_t* dims, const int64_t* list);
trexio_exit_code trexio_hdf5_create_write_dset_sparse (const hid_t group_id, const char* dset_name, const hid_t dtype_id, const hsize_t* chunk_dims, const void* data_sparse);
trexio_exit_code trexio_hdf5_open_write_dset_sparse (const hid_t group_id, const char* dset_name, const hid_t dtype_id, const hsize_t* chunk_dims, const hsize_t* offset_file, const void* data_sparse);
trexio_exit_code trexio_hdf5_open_read_dset_sparse (const hid_t group_id, const char* dset_name, const uint32_t dset_rank, const hsize_t* offset_file, hsize_t* const size_read, int64_t* const eof_read_size, const int is_index, void* const data_sparse);

#endif
#endif
