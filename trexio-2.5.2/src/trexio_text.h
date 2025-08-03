/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/



#ifndef TREXIO_TEXT_H
#define TREXIO_TEXT_H

#include "trexio.h"
#include "trexio_private.h"
#include "trexio_s.h"
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>
typedef struct metadata_s {
  int64_t metadata_code_num;
  int64_t metadata_author_num;
  int64_t metadata_unsafe;
  char**  metadata_code;
  char**  metadata_author;
  uint64_t dims_metadata_code[16];
  uint64_t dims_metadata_author[16];
  uint64_t len_metadata_package_version;
  uint64_t len_metadata_description;
  uint32_t rank_metadata_code;
  uint32_t rank_metadata_author;
  uint32_t to_flush;
  bool metadata_code_num_isSet;
  bool metadata_author_num_isSet;
  bool metadata_unsafe_isSet;
  char*    metadata_package_version;
  char*    metadata_description;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} metadata_t;

typedef struct nucleus_s {
  int64_t nucleus_num;
  double nucleus_repulsion;
  double*  nucleus_charge;
  double*  nucleus_coord;
  char**  nucleus_label;
  uint64_t dims_nucleus_charge[16];
  uint64_t dims_nucleus_coord[16];
  uint64_t dims_nucleus_label[16];
  uint64_t len_nucleus_point_group;
  uint32_t rank_nucleus_charge;
  uint32_t rank_nucleus_coord;
  uint32_t rank_nucleus_label;
  uint32_t to_flush;
  bool nucleus_num_isSet;
  bool nucleus_repulsion_isSet;
  char*    nucleus_point_group;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} nucleus_t;

typedef struct cell_s {
  int64_t cell_two_pi;
  double*  cell_a;
  double*  cell_b;
  double*  cell_c;
  double*  cell_g_a;
  double*  cell_g_b;
  double*  cell_g_c;
  uint64_t dims_cell_a[16];
  uint64_t dims_cell_b[16];
  uint64_t dims_cell_c[16];
  uint64_t dims_cell_g_a[16];
  uint64_t dims_cell_g_b[16];
  uint64_t dims_cell_g_c[16];
  uint32_t rank_cell_a;
  uint32_t rank_cell_b;
  uint32_t rank_cell_c;
  uint32_t rank_cell_g_a;
  uint32_t rank_cell_g_b;
  uint32_t rank_cell_g_c;
  uint32_t to_flush;
  bool cell_two_pi_isSet;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} cell_t;

typedef struct pbc_s {
  int64_t pbc_periodic;
  int64_t pbc_k_point_num;
  double pbc_madelung;
  double*  pbc_k_point;
  double*  pbc_k_point_weight;
  uint64_t dims_pbc_k_point[16];
  uint64_t dims_pbc_k_point_weight[16];
  uint32_t rank_pbc_k_point;
  uint32_t rank_pbc_k_point_weight;
  uint32_t to_flush;
  bool pbc_periodic_isSet;
  bool pbc_k_point_num_isSet;
  bool pbc_madelung_isSet;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} pbc_t;

typedef struct electron_s {
  int64_t electron_num;
  int64_t electron_up_num;
  int64_t electron_dn_num;
  uint32_t to_flush;
  bool electron_num_isSet;
  bool electron_up_num_isSet;
  bool electron_dn_num_isSet;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} electron_t;

typedef struct state_s {
  int64_t state_num;
  int64_t state_id;
  double state_energy;
  char**  state_label;
  char**  state_file_name;
  uint64_t dims_state_label[16];
  uint64_t dims_state_file_name[16];
  uint64_t len_state_current_label;
  uint32_t rank_state_label;
  uint32_t rank_state_file_name;
  uint32_t to_flush;
  bool state_num_isSet;
  bool state_id_isSet;
  bool state_energy_isSet;
  char*    state_current_label;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} state_t;

typedef struct basis_s {
  int64_t basis_prim_num;
  int64_t basis_shell_num;
  int64_t basis_nao_grid_num;
  int64_t basis_interp_coeff_cnt;
  double basis_e_cut;
  int64_t*  basis_nucleus_index;
  int64_t*  basis_shell_ang_mom;
  double*  basis_shell_factor;
  int64_t*  basis_r_power;
  int64_t*  basis_nao_grid_start;
  int64_t*  basis_nao_grid_size;
  int64_t*  basis_shell_index;
  double*  basis_exponent;
  double*  basis_exponent_im;
  double*  basis_coefficient;
  double*  basis_coefficient_im;
  double*  basis_oscillation_arg;
  double*  basis_prim_factor;
  double*  basis_nao_grid_radius;
  double*  basis_nao_grid_phi;
  double*  basis_nao_grid_grad;
  double*  basis_nao_grid_lap;
  double*  basis_interpolator_phi;
  double*  basis_interpolator_grad;
  double*  basis_interpolator_lap;
  uint64_t dims_basis_nucleus_index[16];
  uint64_t dims_basis_shell_ang_mom[16];
  uint64_t dims_basis_shell_factor[16];
  uint64_t dims_basis_r_power[16];
  uint64_t dims_basis_nao_grid_start[16];
  uint64_t dims_basis_nao_grid_size[16];
  uint64_t dims_basis_shell_index[16];
  uint64_t dims_basis_exponent[16];
  uint64_t dims_basis_exponent_im[16];
  uint64_t dims_basis_coefficient[16];
  uint64_t dims_basis_coefficient_im[16];
  uint64_t dims_basis_oscillation_arg[16];
  uint64_t dims_basis_prim_factor[16];
  uint64_t dims_basis_nao_grid_radius[16];
  uint64_t dims_basis_nao_grid_phi[16];
  uint64_t dims_basis_nao_grid_grad[16];
  uint64_t dims_basis_nao_grid_lap[16];
  uint64_t dims_basis_interpolator_phi[16];
  uint64_t dims_basis_interpolator_grad[16];
  uint64_t dims_basis_interpolator_lap[16];
  uint64_t len_basis_type;
  uint64_t len_basis_oscillation_kind;
  uint64_t len_basis_interpolator_kind;
  uint32_t rank_basis_nucleus_index;
  uint32_t rank_basis_shell_ang_mom;
  uint32_t rank_basis_shell_factor;
  uint32_t rank_basis_r_power;
  uint32_t rank_basis_nao_grid_start;
  uint32_t rank_basis_nao_grid_size;
  uint32_t rank_basis_shell_index;
  uint32_t rank_basis_exponent;
  uint32_t rank_basis_exponent_im;
  uint32_t rank_basis_coefficient;
  uint32_t rank_basis_coefficient_im;
  uint32_t rank_basis_oscillation_arg;
  uint32_t rank_basis_prim_factor;
  uint32_t rank_basis_nao_grid_radius;
  uint32_t rank_basis_nao_grid_phi;
  uint32_t rank_basis_nao_grid_grad;
  uint32_t rank_basis_nao_grid_lap;
  uint32_t rank_basis_interpolator_phi;
  uint32_t rank_basis_interpolator_grad;
  uint32_t rank_basis_interpolator_lap;
  uint32_t to_flush;
  bool basis_prim_num_isSet;
  bool basis_shell_num_isSet;
  bool basis_nao_grid_num_isSet;
  bool basis_interp_coeff_cnt_isSet;
  bool basis_e_cut_isSet;
  char*    basis_type;
  char*    basis_oscillation_kind;
  char*    basis_interpolator_kind;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} basis_t;

typedef struct ecp_s {
  int64_t ecp_num;
  int64_t*  ecp_max_ang_mom_plus_1;
  int64_t*  ecp_z_core;
  int64_t*  ecp_ang_mom;
  int64_t*  ecp_nucleus_index;
  double*  ecp_exponent;
  double*  ecp_coefficient;
  int64_t*  ecp_power;
  uint64_t dims_ecp_max_ang_mom_plus_1[16];
  uint64_t dims_ecp_z_core[16];
  uint64_t dims_ecp_ang_mom[16];
  uint64_t dims_ecp_nucleus_index[16];
  uint64_t dims_ecp_exponent[16];
  uint64_t dims_ecp_coefficient[16];
  uint64_t dims_ecp_power[16];
  uint32_t rank_ecp_max_ang_mom_plus_1;
  uint32_t rank_ecp_z_core;
  uint32_t rank_ecp_ang_mom;
  uint32_t rank_ecp_nucleus_index;
  uint32_t rank_ecp_exponent;
  uint32_t rank_ecp_coefficient;
  uint32_t rank_ecp_power;
  uint32_t to_flush;
  bool ecp_num_isSet;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} ecp_t;

typedef struct grid_s {
  double grid_rad_precision;
  int64_t grid_num;
  int64_t grid_max_ang_num;
  int64_t grid_min_ang_num;
  int64_t grid_ang_num;
  int64_t grid_rad_num;
  double*  grid_coord;
  double*  grid_weight;
  double*  grid_ang_coord;
  double*  grid_ang_weight;
  double*  grid_rad_coord;
  double*  grid_rad_weight;
  uint64_t dims_grid_coord[16];
  uint64_t dims_grid_weight[16];
  uint64_t dims_grid_ang_coord[16];
  uint64_t dims_grid_ang_weight[16];
  uint64_t dims_grid_rad_coord[16];
  uint64_t dims_grid_rad_weight[16];
  uint64_t len_grid_description;
  uint32_t rank_grid_coord;
  uint32_t rank_grid_weight;
  uint32_t rank_grid_ang_coord;
  uint32_t rank_grid_ang_weight;
  uint32_t rank_grid_rad_coord;
  uint32_t rank_grid_rad_weight;
  uint32_t to_flush;
  bool grid_rad_precision_isSet;
  bool grid_num_isSet;
  bool grid_max_ang_num_isSet;
  bool grid_min_ang_num_isSet;
  bool grid_ang_num_isSet;
  bool grid_rad_num_isSet;
  char*    grid_description;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} grid_t;

typedef struct ao_s {
  int64_t ao_cartesian;
  int64_t ao_num;
  int64_t*  ao_shell;
  double*  ao_normalization;
  uint64_t dims_ao_shell[16];
  uint64_t dims_ao_normalization[16];
  uint32_t rank_ao_shell;
  uint32_t rank_ao_normalization;
  uint32_t to_flush;
  bool ao_cartesian_isSet;
  bool ao_num_isSet;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} ao_t;

typedef struct ao_1e_int_s {
  double*  ao_1e_int_overlap;
  double*  ao_1e_int_kinetic;
  double*  ao_1e_int_potential_n_e;
  double*  ao_1e_int_ecp;
  double*  ao_1e_int_core_hamiltonian;
  double*  ao_1e_int_overlap_im;
  double*  ao_1e_int_kinetic_im;
  double*  ao_1e_int_potential_n_e_im;
  double*  ao_1e_int_ecp_im;
  double*  ao_1e_int_core_hamiltonian_im;
  uint64_t dims_ao_1e_int_overlap[16];
  uint64_t dims_ao_1e_int_kinetic[16];
  uint64_t dims_ao_1e_int_potential_n_e[16];
  uint64_t dims_ao_1e_int_ecp[16];
  uint64_t dims_ao_1e_int_core_hamiltonian[16];
  uint64_t dims_ao_1e_int_overlap_im[16];
  uint64_t dims_ao_1e_int_kinetic_im[16];
  uint64_t dims_ao_1e_int_potential_n_e_im[16];
  uint64_t dims_ao_1e_int_ecp_im[16];
  uint64_t dims_ao_1e_int_core_hamiltonian_im[16];
  uint32_t rank_ao_1e_int_overlap;
  uint32_t rank_ao_1e_int_kinetic;
  uint32_t rank_ao_1e_int_potential_n_e;
  uint32_t rank_ao_1e_int_ecp;
  uint32_t rank_ao_1e_int_core_hamiltonian;
  uint32_t rank_ao_1e_int_overlap_im;
  uint32_t rank_ao_1e_int_kinetic_im;
  uint32_t rank_ao_1e_int_potential_n_e_im;
  uint32_t rank_ao_1e_int_ecp_im;
  uint32_t rank_ao_1e_int_core_hamiltonian_im;
  uint32_t to_flush;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} ao_1e_int_t;

typedef struct ao_2e_int_s {
  int64_t ao_2e_int_eri_cholesky_num;
  int64_t ao_2e_int_eri_lr_cholesky_num;
  uint32_t to_flush;
  bool ao_2e_int_eri_cholesky_num_isSet;
  bool ao_2e_int_eri_lr_cholesky_num_isSet;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} ao_2e_int_t;

typedef struct mo_s {
  int64_t mo_num;
  double*  mo_coefficient;
  double*  mo_coefficient_im;
  double*  mo_occupation;
  double*  mo_energy;
  int64_t*  mo_spin;
  int64_t*  mo_k_point;
  char**  mo_class;
  char**  mo_symmetry;
  uint64_t dims_mo_coefficient[16];
  uint64_t dims_mo_coefficient_im[16];
  uint64_t dims_mo_occupation[16];
  uint64_t dims_mo_energy[16];
  uint64_t dims_mo_spin[16];
  uint64_t dims_mo_k_point[16];
  uint64_t dims_mo_class[16];
  uint64_t dims_mo_symmetry[16];
  uint64_t len_mo_type;
  uint32_t rank_mo_coefficient;
  uint32_t rank_mo_coefficient_im;
  uint32_t rank_mo_occupation;
  uint32_t rank_mo_energy;
  uint32_t rank_mo_spin;
  uint32_t rank_mo_k_point;
  uint32_t rank_mo_class;
  uint32_t rank_mo_symmetry;
  uint32_t to_flush;
  bool mo_num_isSet;
  char*    mo_type;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} mo_t;

typedef struct mo_1e_int_s {
  double*  mo_1e_int_overlap;
  double*  mo_1e_int_kinetic;
  double*  mo_1e_int_potential_n_e;
  double*  mo_1e_int_ecp;
  double*  mo_1e_int_core_hamiltonian;
  double*  mo_1e_int_overlap_im;
  double*  mo_1e_int_kinetic_im;
  double*  mo_1e_int_potential_n_e_im;
  double*  mo_1e_int_ecp_im;
  double*  mo_1e_int_core_hamiltonian_im;
  uint64_t dims_mo_1e_int_overlap[16];
  uint64_t dims_mo_1e_int_kinetic[16];
  uint64_t dims_mo_1e_int_potential_n_e[16];
  uint64_t dims_mo_1e_int_ecp[16];
  uint64_t dims_mo_1e_int_core_hamiltonian[16];
  uint64_t dims_mo_1e_int_overlap_im[16];
  uint64_t dims_mo_1e_int_kinetic_im[16];
  uint64_t dims_mo_1e_int_potential_n_e_im[16];
  uint64_t dims_mo_1e_int_ecp_im[16];
  uint64_t dims_mo_1e_int_core_hamiltonian_im[16];
  uint32_t rank_mo_1e_int_overlap;
  uint32_t rank_mo_1e_int_kinetic;
  uint32_t rank_mo_1e_int_potential_n_e;
  uint32_t rank_mo_1e_int_ecp;
  uint32_t rank_mo_1e_int_core_hamiltonian;
  uint32_t rank_mo_1e_int_overlap_im;
  uint32_t rank_mo_1e_int_kinetic_im;
  uint32_t rank_mo_1e_int_potential_n_e_im;
  uint32_t rank_mo_1e_int_ecp_im;
  uint32_t rank_mo_1e_int_core_hamiltonian_im;
  uint32_t to_flush;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} mo_1e_int_t;

typedef struct mo_2e_int_s {
  int64_t mo_2e_int_eri_cholesky_num;
  int64_t mo_2e_int_eri_lr_cholesky_num;
  uint32_t to_flush;
  bool mo_2e_int_eri_cholesky_num_isSet;
  bool mo_2e_int_eri_lr_cholesky_num_isSet;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} mo_2e_int_t;

typedef struct determinant_s {
  int64_t determinant_num;
  uint32_t to_flush;
  bool determinant_num_isSet;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} determinant_t;

typedef struct csf_s {
  int64_t csf_num;
  uint32_t to_flush;
  bool csf_num_isSet;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} csf_t;

typedef struct amplitude_s {
  uint32_t to_flush;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} amplitude_t;

typedef struct rdm_s {
  int64_t rdm_2e_cholesky_num;
  int64_t rdm_2e_upup_cholesky_num;
  int64_t rdm_2e_dndn_cholesky_num;
  int64_t rdm_2e_updn_cholesky_num;
  double*  rdm_1e;
  double*  rdm_1e_up;
  double*  rdm_1e_dn;
  double*  rdm_1e_transition;
  uint64_t dims_rdm_1e[16];
  uint64_t dims_rdm_1e_up[16];
  uint64_t dims_rdm_1e_dn[16];
  uint64_t dims_rdm_1e_transition[16];
  uint32_t rank_rdm_1e;
  uint32_t rank_rdm_1e_up;
  uint32_t rank_rdm_1e_dn;
  uint32_t rank_rdm_1e_transition;
  uint32_t to_flush;
  bool rdm_2e_cholesky_num_isSet;
  bool rdm_2e_upup_cholesky_num_isSet;
  bool rdm_2e_dndn_cholesky_num_isSet;
  bool rdm_2e_updn_cholesky_num_isSet;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} rdm_t;

typedef struct jastrow_s {
  int64_t jastrow_en_num;
  int64_t jastrow_ee_num;
  int64_t jastrow_een_num;
  double jastrow_ee_scaling;
  double*  jastrow_en;
  double*  jastrow_ee;
  double*  jastrow_een;
  int64_t*  jastrow_en_nucleus;
  int64_t*  jastrow_een_nucleus;
  double*  jastrow_en_scaling;
  uint64_t dims_jastrow_en[16];
  uint64_t dims_jastrow_ee[16];
  uint64_t dims_jastrow_een[16];
  uint64_t dims_jastrow_en_nucleus[16];
  uint64_t dims_jastrow_een_nucleus[16];
  uint64_t dims_jastrow_en_scaling[16];
  uint64_t len_jastrow_type;
  uint32_t rank_jastrow_en;
  uint32_t rank_jastrow_ee;
  uint32_t rank_jastrow_een;
  uint32_t rank_jastrow_en_nucleus;
  uint32_t rank_jastrow_een_nucleus;
  uint32_t rank_jastrow_en_scaling;
  uint32_t to_flush;
  bool jastrow_en_num_isSet;
  bool jastrow_ee_num_isSet;
  bool jastrow_een_num_isSet;
  bool jastrow_ee_scaling_isSet;
  char*    jastrow_type;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} jastrow_t;

typedef struct qmc_s {
  int64_t qmc_num;
  double*  qmc_point;
  double*  qmc_psi;
  double*  qmc_e_loc;
  uint64_t dims_qmc_point[16];
  uint64_t dims_qmc_psi[16];
  uint64_t dims_qmc_e_loc[16];
  uint32_t rank_qmc_point;
  uint32_t rank_qmc_psi;
  uint32_t rank_qmc_e_loc;
  uint32_t to_flush;
  bool qmc_num_isSet;
  char     file_name[TREXIO_MAX_FILENAME_LENGTH];
} qmc_t;

typedef struct trexio_text_s {
  trexio_t   parent ;
  metadata_t* metadata;
  nucleus_t* nucleus;
  cell_t* cell;
  pbc_t* pbc;
  electron_t* electron;
  state_t* state;
  basis_t* basis;
  ecp_t* ecp;
  grid_t* grid;
  ao_t* ao;
  ao_1e_int_t* ao_1e_int;
  ao_2e_int_t* ao_2e_int;
  mo_t* mo;
  mo_1e_int_t* mo_1e_int;
  mo_2e_int_t* mo_2e_int;
  determinant_t* determinant;
  csf_t* csf;
  amplitude_t* amplitude;
  rdm_t* rdm;
  jastrow_t* jastrow;
  qmc_t* qmc;
  int        lock_file;
} trexio_text_t;

trexio_exit_code trexio_text_init(trexio_t* const file);
trexio_exit_code trexio_text_inquire(const char* file_name);
trexio_exit_code trexio_text_deinit(trexio_t* const file);
trexio_exit_code trexio_text_lock(trexio_t* const file);
trexio_exit_code trexio_text_unlock(trexio_t* const file);
trexio_exit_code trexio_text_flush(trexio_t* const file);
bool trexio_text_file_exists(const char* file_name);
trexio_exit_code trexio_text_has_determinant_list(trexio_t* const file);
trexio_exit_code trexio_text_read_determinant_list(trexio_t* const file, const int64_t offset_file, const uint32_t rank, const uint64_t* dims, int64_t* const eof_read_size, int64_t* const list);
trexio_exit_code trexio_text_write_determinant_list(trexio_t* const file, const int64_t offset_file, const uint32_t rank, const uint64_t* dims, const int64_t* list);
trexio_exit_code trexio_text_has_metadata(trexio_t* const file);

trexio_exit_code trexio_text_has_nucleus(trexio_t* const file);

trexio_exit_code trexio_text_has_cell(trexio_t* const file);

trexio_exit_code trexio_text_has_pbc(trexio_t* const file);

trexio_exit_code trexio_text_has_electron(trexio_t* const file);

trexio_exit_code trexio_text_has_state(trexio_t* const file);

trexio_exit_code trexio_text_has_basis(trexio_t* const file);

trexio_exit_code trexio_text_has_ecp(trexio_t* const file);

trexio_exit_code trexio_text_has_grid(trexio_t* const file);

trexio_exit_code trexio_text_has_ao(trexio_t* const file);

trexio_exit_code trexio_text_has_ao_1e_int(trexio_t* const file);

trexio_exit_code trexio_text_has_ao_2e_int(trexio_t* const file);

trexio_exit_code trexio_text_has_mo(trexio_t* const file);

trexio_exit_code trexio_text_has_mo_1e_int(trexio_t* const file);

trexio_exit_code trexio_text_has_mo_2e_int(trexio_t* const file);

trexio_exit_code trexio_text_has_determinant(trexio_t* const file);

trexio_exit_code trexio_text_has_csf(trexio_t* const file);

trexio_exit_code trexio_text_has_amplitude(trexio_t* const file);

trexio_exit_code trexio_text_has_rdm(trexio_t* const file);

trexio_exit_code trexio_text_has_jastrow(trexio_t* const file);

trexio_exit_code trexio_text_has_qmc(trexio_t* const file);

trexio_exit_code trexio_text_free_metadata(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_metadata (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, metadata_t* metadata);

trexio_exit_code trexio_text_free_nucleus(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_nucleus (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, nucleus_t* nucleus);

trexio_exit_code trexio_text_free_cell(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_cell (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, cell_t* cell);

trexio_exit_code trexio_text_free_pbc(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_pbc (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, pbc_t* pbc);

trexio_exit_code trexio_text_free_electron(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_electron (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, electron_t* electron);

trexio_exit_code trexio_text_free_state(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_state (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, state_t* state);

trexio_exit_code trexio_text_free_basis(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_basis (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, basis_t* basis);

trexio_exit_code trexio_text_free_ecp(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_ecp (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, ecp_t* ecp);

trexio_exit_code trexio_text_free_grid(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_grid (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, grid_t* grid);

trexio_exit_code trexio_text_free_ao(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_ao (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, ao_t* ao);

trexio_exit_code trexio_text_free_ao_1e_int(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_ao_1e_int (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, ao_1e_int_t* ao_1e_int);

trexio_exit_code trexio_text_free_ao_2e_int(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_ao_2e_int (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, ao_2e_int_t* ao_2e_int);

trexio_exit_code trexio_text_free_mo(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_mo (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, mo_t* mo);

trexio_exit_code trexio_text_free_mo_1e_int(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_mo_1e_int (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, mo_1e_int_t* mo_1e_int);

trexio_exit_code trexio_text_free_mo_2e_int(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_mo_2e_int (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, mo_2e_int_t* mo_2e_int);

trexio_exit_code trexio_text_free_determinant(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_determinant (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, determinant_t* determinant);

trexio_exit_code trexio_text_free_csf(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_csf (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, csf_t* csf);

trexio_exit_code trexio_text_free_amplitude(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_amplitude (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, amplitude_t* amplitude);

trexio_exit_code trexio_text_free_rdm(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_rdm (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, rdm_t* rdm);

trexio_exit_code trexio_text_free_jastrow(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_jastrow (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, jastrow_t* jastrow);

trexio_exit_code trexio_text_free_qmc(trexio_text_t* const file);

trexio_exit_code trexio_text_free_read_qmc (char* buffer, FILE* txt_file, trexio_text_t* trexio_file, qmc_t* qmc);

metadata_t* trexio_text_read_metadata(trexio_text_t* const file);

nucleus_t* trexio_text_read_nucleus(trexio_text_t* const file);

cell_t* trexio_text_read_cell(trexio_text_t* const file);

pbc_t* trexio_text_read_pbc(trexio_text_t* const file);

electron_t* trexio_text_read_electron(trexio_text_t* const file);

state_t* trexio_text_read_state(trexio_text_t* const file);

basis_t* trexio_text_read_basis(trexio_text_t* const file);

ecp_t* trexio_text_read_ecp(trexio_text_t* const file);

grid_t* trexio_text_read_grid(trexio_text_t* const file);

ao_t* trexio_text_read_ao(trexio_text_t* const file);

ao_1e_int_t* trexio_text_read_ao_1e_int(trexio_text_t* const file);

ao_2e_int_t* trexio_text_read_ao_2e_int(trexio_text_t* const file);

mo_t* trexio_text_read_mo(trexio_text_t* const file);

mo_1e_int_t* trexio_text_read_mo_1e_int(trexio_text_t* const file);

mo_2e_int_t* trexio_text_read_mo_2e_int(trexio_text_t* const file);

determinant_t* trexio_text_read_determinant(trexio_text_t* const file);

csf_t* trexio_text_read_csf(trexio_text_t* const file);

amplitude_t* trexio_text_read_amplitude(trexio_text_t* const file);

rdm_t* trexio_text_read_rdm(trexio_text_t* const file);

jastrow_t* trexio_text_read_jastrow(trexio_text_t* const file);

qmc_t* trexio_text_read_qmc(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_metadata(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_nucleus(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_cell(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_pbc(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_electron(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_state(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_basis(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_ecp(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_grid(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_ao(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_ao_1e_int(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_ao_2e_int(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_mo(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_mo_1e_int(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_mo_2e_int(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_determinant(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_csf(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_amplitude(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_rdm(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_jastrow(trexio_text_t* const file);

trexio_exit_code trexio_text_flush_qmc(trexio_text_t* const file);

trexio_exit_code trexio_text_delete_metadata (trexio_t* const file);

trexio_exit_code trexio_text_delete_nucleus (trexio_t* const file);

trexio_exit_code trexio_text_delete_cell (trexio_t* const file);

trexio_exit_code trexio_text_delete_pbc (trexio_t* const file);

trexio_exit_code trexio_text_delete_electron (trexio_t* const file);

trexio_exit_code trexio_text_delete_state (trexio_t* const file);

trexio_exit_code trexio_text_delete_basis (trexio_t* const file);

trexio_exit_code trexio_text_delete_ecp (trexio_t* const file);

trexio_exit_code trexio_text_delete_grid (trexio_t* const file);

trexio_exit_code trexio_text_delete_ao (trexio_t* const file);

trexio_exit_code trexio_text_delete_ao_1e_int (trexio_t* const file);

trexio_exit_code trexio_text_delete_ao_2e_int (trexio_t* const file);

trexio_exit_code trexio_text_delete_mo (trexio_t* const file);

trexio_exit_code trexio_text_delete_mo_1e_int (trexio_t* const file);

trexio_exit_code trexio_text_delete_mo_2e_int (trexio_t* const file);

trexio_exit_code trexio_text_delete_determinant (trexio_t* const file);

trexio_exit_code trexio_text_delete_csf (trexio_t* const file);

trexio_exit_code trexio_text_delete_amplitude (trexio_t* const file);

trexio_exit_code trexio_text_delete_rdm (trexio_t* const file);

trexio_exit_code trexio_text_delete_jastrow (trexio_t* const file);

trexio_exit_code trexio_text_delete_qmc (trexio_t* const file);

trexio_exit_code trexio_text_has_nucleus_charge (trexio_t* const file);
trexio_exit_code trexio_text_read_nucleus_charge (trexio_t* const file, double* const nucleus_charge, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_nucleus_charge(trexio_t* const file, const double* nucleus_charge, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_nucleus_coord (trexio_t* const file);
trexio_exit_code trexio_text_read_nucleus_coord (trexio_t* const file, double* const nucleus_coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_nucleus_coord(trexio_t* const file, const double* nucleus_coord, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_cell_a (trexio_t* const file);
trexio_exit_code trexio_text_read_cell_a (trexio_t* const file, double* const cell_a, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_cell_a(trexio_t* const file, const double* cell_a, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_cell_b (trexio_t* const file);
trexio_exit_code trexio_text_read_cell_b (trexio_t* const file, double* const cell_b, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_cell_b(trexio_t* const file, const double* cell_b, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_cell_c (trexio_t* const file);
trexio_exit_code trexio_text_read_cell_c (trexio_t* const file, double* const cell_c, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_cell_c(trexio_t* const file, const double* cell_c, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_cell_g_a (trexio_t* const file);
trexio_exit_code trexio_text_read_cell_g_a (trexio_t* const file, double* const cell_g_a, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_cell_g_a(trexio_t* const file, const double* cell_g_a, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_cell_g_b (trexio_t* const file);
trexio_exit_code trexio_text_read_cell_g_b (trexio_t* const file, double* const cell_g_b, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_cell_g_b(trexio_t* const file, const double* cell_g_b, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_cell_g_c (trexio_t* const file);
trexio_exit_code trexio_text_read_cell_g_c (trexio_t* const file, double* const cell_g_c, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_cell_g_c(trexio_t* const file, const double* cell_g_c, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_pbc_k_point (trexio_t* const file);
trexio_exit_code trexio_text_read_pbc_k_point (trexio_t* const file, double* const pbc_k_point, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_pbc_k_point(trexio_t* const file, const double* pbc_k_point, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_pbc_k_point_weight (trexio_t* const file);
trexio_exit_code trexio_text_read_pbc_k_point_weight (trexio_t* const file, double* const pbc_k_point_weight, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_pbc_k_point_weight(trexio_t* const file, const double* pbc_k_point_weight, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_nucleus_index (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_nucleus_index (trexio_t* const file, int64_t* const basis_nucleus_index, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_nucleus_index(trexio_t* const file, const int64_t* basis_nucleus_index, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_shell_ang_mom (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_shell_ang_mom (trexio_t* const file, int64_t* const basis_shell_ang_mom, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_shell_ang_mom(trexio_t* const file, const int64_t* basis_shell_ang_mom, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_shell_factor (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_shell_factor (trexio_t* const file, double* const basis_shell_factor, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_shell_factor(trexio_t* const file, const double* basis_shell_factor, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_r_power (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_r_power (trexio_t* const file, int64_t* const basis_r_power, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_r_power(trexio_t* const file, const int64_t* basis_r_power, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_nao_grid_start (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_nao_grid_start (trexio_t* const file, int64_t* const basis_nao_grid_start, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_nao_grid_start(trexio_t* const file, const int64_t* basis_nao_grid_start, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_nao_grid_size (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_nao_grid_size (trexio_t* const file, int64_t* const basis_nao_grid_size, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_nao_grid_size(trexio_t* const file, const int64_t* basis_nao_grid_size, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_shell_index (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_shell_index (trexio_t* const file, int64_t* const basis_shell_index, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_shell_index(trexio_t* const file, const int64_t* basis_shell_index, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_exponent (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_exponent (trexio_t* const file, double* const basis_exponent, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_exponent(trexio_t* const file, const double* basis_exponent, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_exponent_im (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_exponent_im (trexio_t* const file, double* const basis_exponent_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_exponent_im(trexio_t* const file, const double* basis_exponent_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_coefficient (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_coefficient (trexio_t* const file, double* const basis_coefficient, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_coefficient(trexio_t* const file, const double* basis_coefficient, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_coefficient_im (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_coefficient_im (trexio_t* const file, double* const basis_coefficient_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_coefficient_im(trexio_t* const file, const double* basis_coefficient_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_oscillation_arg (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_oscillation_arg (trexio_t* const file, double* const basis_oscillation_arg, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_oscillation_arg(trexio_t* const file, const double* basis_oscillation_arg, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_prim_factor (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_prim_factor (trexio_t* const file, double* const basis_prim_factor, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_prim_factor(trexio_t* const file, const double* basis_prim_factor, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_nao_grid_radius (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_nao_grid_radius (trexio_t* const file, double* const basis_nao_grid_radius, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_nao_grid_radius(trexio_t* const file, const double* basis_nao_grid_radius, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_nao_grid_phi (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_nao_grid_phi (trexio_t* const file, double* const basis_nao_grid_phi, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_nao_grid_phi(trexio_t* const file, const double* basis_nao_grid_phi, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_nao_grid_grad (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_nao_grid_grad (trexio_t* const file, double* const basis_nao_grid_grad, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_nao_grid_grad(trexio_t* const file, const double* basis_nao_grid_grad, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_nao_grid_lap (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_nao_grid_lap (trexio_t* const file, double* const basis_nao_grid_lap, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_nao_grid_lap(trexio_t* const file, const double* basis_nao_grid_lap, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_interpolator_phi (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_interpolator_phi (trexio_t* const file, double* const basis_interpolator_phi, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_interpolator_phi(trexio_t* const file, const double* basis_interpolator_phi, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_interpolator_grad (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_interpolator_grad (trexio_t* const file, double* const basis_interpolator_grad, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_interpolator_grad(trexio_t* const file, const double* basis_interpolator_grad, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_basis_interpolator_lap (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_interpolator_lap (trexio_t* const file, double* const basis_interpolator_lap, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_basis_interpolator_lap(trexio_t* const file, const double* basis_interpolator_lap, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ecp_max_ang_mom_plus_1 (trexio_t* const file);
trexio_exit_code trexio_text_read_ecp_max_ang_mom_plus_1 (trexio_t* const file, int64_t* const ecp_max_ang_mom_plus_1, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_max_ang_mom_plus_1(trexio_t* const file, const int64_t* ecp_max_ang_mom_plus_1, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ecp_z_core (trexio_t* const file);
trexio_exit_code trexio_text_read_ecp_z_core (trexio_t* const file, int64_t* const ecp_z_core, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_z_core(trexio_t* const file, const int64_t* ecp_z_core, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ecp_ang_mom (trexio_t* const file);
trexio_exit_code trexio_text_read_ecp_ang_mom (trexio_t* const file, int64_t* const ecp_ang_mom, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_ang_mom(trexio_t* const file, const int64_t* ecp_ang_mom, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ecp_nucleus_index (trexio_t* const file);
trexio_exit_code trexio_text_read_ecp_nucleus_index (trexio_t* const file, int64_t* const ecp_nucleus_index, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_nucleus_index(trexio_t* const file, const int64_t* ecp_nucleus_index, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ecp_exponent (trexio_t* const file);
trexio_exit_code trexio_text_read_ecp_exponent (trexio_t* const file, double* const ecp_exponent, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_exponent(trexio_t* const file, const double* ecp_exponent, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ecp_coefficient (trexio_t* const file);
trexio_exit_code trexio_text_read_ecp_coefficient (trexio_t* const file, double* const ecp_coefficient, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_coefficient(trexio_t* const file, const double* ecp_coefficient, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ecp_power (trexio_t* const file);
trexio_exit_code trexio_text_read_ecp_power (trexio_t* const file, int64_t* const ecp_power, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ecp_power(trexio_t* const file, const int64_t* ecp_power, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_grid_coord (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_coord (trexio_t* const file, double* const grid_coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_grid_coord(trexio_t* const file, const double* grid_coord, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_grid_weight (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_weight (trexio_t* const file, double* const grid_weight, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_grid_weight(trexio_t* const file, const double* grid_weight, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_grid_ang_coord (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_ang_coord (trexio_t* const file, double* const grid_ang_coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_grid_ang_coord(trexio_t* const file, const double* grid_ang_coord, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_grid_ang_weight (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_ang_weight (trexio_t* const file, double* const grid_ang_weight, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_grid_ang_weight(trexio_t* const file, const double* grid_ang_weight, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_grid_rad_coord (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_rad_coord (trexio_t* const file, double* const grid_rad_coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_grid_rad_coord(trexio_t* const file, const double* grid_rad_coord, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_grid_rad_weight (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_rad_weight (trexio_t* const file, double* const grid_rad_weight, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_grid_rad_weight(trexio_t* const file, const double* grid_rad_weight, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_shell (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_shell (trexio_t* const file, int64_t* const ao_shell, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ao_shell(trexio_t* const file, const int64_t* ao_shell, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_normalization (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_normalization (trexio_t* const file, double* const ao_normalization, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ao_normalization(trexio_t* const file, const double* ao_normalization, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_1e_int_overlap (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_1e_int_overlap (trexio_t* const file, double* const ao_1e_int_overlap, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ao_1e_int_overlap(trexio_t* const file, const double* ao_1e_int_overlap, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_1e_int_kinetic (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_1e_int_kinetic (trexio_t* const file, double* const ao_1e_int_kinetic, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ao_1e_int_kinetic(trexio_t* const file, const double* ao_1e_int_kinetic, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_1e_int_potential_n_e (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_1e_int_potential_n_e (trexio_t* const file, double* const ao_1e_int_potential_n_e, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ao_1e_int_potential_n_e(trexio_t* const file, const double* ao_1e_int_potential_n_e, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_1e_int_ecp (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_1e_int_ecp (trexio_t* const file, double* const ao_1e_int_ecp, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ao_1e_int_ecp(trexio_t* const file, const double* ao_1e_int_ecp, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_1e_int_core_hamiltonian (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_1e_int_core_hamiltonian (trexio_t* const file, double* const ao_1e_int_core_hamiltonian, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ao_1e_int_core_hamiltonian(trexio_t* const file, const double* ao_1e_int_core_hamiltonian, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_1e_int_overlap_im (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_1e_int_overlap_im (trexio_t* const file, double* const ao_1e_int_overlap_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ao_1e_int_overlap_im(trexio_t* const file, const double* ao_1e_int_overlap_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_1e_int_kinetic_im (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_1e_int_kinetic_im (trexio_t* const file, double* const ao_1e_int_kinetic_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ao_1e_int_kinetic_im(trexio_t* const file, const double* ao_1e_int_kinetic_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_1e_int_potential_n_e_im (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_1e_int_potential_n_e_im (trexio_t* const file, double* const ao_1e_int_potential_n_e_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ao_1e_int_potential_n_e_im(trexio_t* const file, const double* ao_1e_int_potential_n_e_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_1e_int_ecp_im (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_1e_int_ecp_im (trexio_t* const file, double* const ao_1e_int_ecp_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ao_1e_int_ecp_im(trexio_t* const file, const double* ao_1e_int_ecp_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_1e_int_core_hamiltonian_im (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_1e_int_core_hamiltonian_im (trexio_t* const file, double* const ao_1e_int_core_hamiltonian_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_ao_1e_int_core_hamiltonian_im(trexio_t* const file, const double* ao_1e_int_core_hamiltonian_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_coefficient (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_coefficient (trexio_t* const file, double* const mo_coefficient, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_coefficient(trexio_t* const file, const double* mo_coefficient, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_coefficient_im (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_coefficient_im (trexio_t* const file, double* const mo_coefficient_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_coefficient_im(trexio_t* const file, const double* mo_coefficient_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_occupation (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_occupation (trexio_t* const file, double* const mo_occupation, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_occupation(trexio_t* const file, const double* mo_occupation, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_energy (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_energy (trexio_t* const file, double* const mo_energy, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_energy(trexio_t* const file, const double* mo_energy, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_spin (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_spin (trexio_t* const file, int64_t* const mo_spin, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_spin(trexio_t* const file, const int64_t* mo_spin, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_k_point (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_k_point (trexio_t* const file, int64_t* const mo_k_point, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_k_point(trexio_t* const file, const int64_t* mo_k_point, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_1e_int_overlap (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_1e_int_overlap (trexio_t* const file, double* const mo_1e_int_overlap, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_1e_int_overlap(trexio_t* const file, const double* mo_1e_int_overlap, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_1e_int_kinetic (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_1e_int_kinetic (trexio_t* const file, double* const mo_1e_int_kinetic, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_1e_int_kinetic(trexio_t* const file, const double* mo_1e_int_kinetic, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_1e_int_potential_n_e (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_1e_int_potential_n_e (trexio_t* const file, double* const mo_1e_int_potential_n_e, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_1e_int_potential_n_e(trexio_t* const file, const double* mo_1e_int_potential_n_e, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_1e_int_ecp (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_1e_int_ecp (trexio_t* const file, double* const mo_1e_int_ecp, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_1e_int_ecp(trexio_t* const file, const double* mo_1e_int_ecp, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_1e_int_core_hamiltonian (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_1e_int_core_hamiltonian (trexio_t* const file, double* const mo_1e_int_core_hamiltonian, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_1e_int_core_hamiltonian(trexio_t* const file, const double* mo_1e_int_core_hamiltonian, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_1e_int_overlap_im (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_1e_int_overlap_im (trexio_t* const file, double* const mo_1e_int_overlap_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_1e_int_overlap_im(trexio_t* const file, const double* mo_1e_int_overlap_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_1e_int_kinetic_im (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_1e_int_kinetic_im (trexio_t* const file, double* const mo_1e_int_kinetic_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_1e_int_kinetic_im(trexio_t* const file, const double* mo_1e_int_kinetic_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_1e_int_potential_n_e_im (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_1e_int_potential_n_e_im (trexio_t* const file, double* const mo_1e_int_potential_n_e_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_1e_int_potential_n_e_im(trexio_t* const file, const double* mo_1e_int_potential_n_e_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_1e_int_ecp_im (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_1e_int_ecp_im (trexio_t* const file, double* const mo_1e_int_ecp_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_1e_int_ecp_im(trexio_t* const file, const double* mo_1e_int_ecp_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_1e_int_core_hamiltonian_im (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_1e_int_core_hamiltonian_im (trexio_t* const file, double* const mo_1e_int_core_hamiltonian_im, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_mo_1e_int_core_hamiltonian_im(trexio_t* const file, const double* mo_1e_int_core_hamiltonian_im, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_rdm_1e (trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_1e (trexio_t* const file, double* const rdm_1e, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_rdm_1e(trexio_t* const file, const double* rdm_1e, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_rdm_1e_up (trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_1e_up (trexio_t* const file, double* const rdm_1e_up, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_rdm_1e_up(trexio_t* const file, const double* rdm_1e_up, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_rdm_1e_dn (trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_1e_dn (trexio_t* const file, double* const rdm_1e_dn, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_rdm_1e_dn(trexio_t* const file, const double* rdm_1e_dn, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_rdm_1e_transition (trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_1e_transition (trexio_t* const file, double* const rdm_1e_transition, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_rdm_1e_transition(trexio_t* const file, const double* rdm_1e_transition, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_jastrow_en (trexio_t* const file);
trexio_exit_code trexio_text_read_jastrow_en (trexio_t* const file, double* const jastrow_en, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_jastrow_en(trexio_t* const file, const double* jastrow_en, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_jastrow_ee (trexio_t* const file);
trexio_exit_code trexio_text_read_jastrow_ee (trexio_t* const file, double* const jastrow_ee, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_jastrow_ee(trexio_t* const file, const double* jastrow_ee, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_jastrow_een (trexio_t* const file);
trexio_exit_code trexio_text_read_jastrow_een (trexio_t* const file, double* const jastrow_een, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_jastrow_een(trexio_t* const file, const double* jastrow_een, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_jastrow_en_nucleus (trexio_t* const file);
trexio_exit_code trexio_text_read_jastrow_en_nucleus (trexio_t* const file, int64_t* const jastrow_en_nucleus, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_jastrow_en_nucleus(trexio_t* const file, const int64_t* jastrow_en_nucleus, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_jastrow_een_nucleus (trexio_t* const file);
trexio_exit_code trexio_text_read_jastrow_een_nucleus (trexio_t* const file, int64_t* const jastrow_een_nucleus, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_jastrow_een_nucleus(trexio_t* const file, const int64_t* jastrow_een_nucleus, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_jastrow_en_scaling (trexio_t* const file);
trexio_exit_code trexio_text_read_jastrow_en_scaling (trexio_t* const file, double* const jastrow_en_scaling, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_jastrow_en_scaling(trexio_t* const file, const double* jastrow_en_scaling, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_qmc_point (trexio_t* const file);
trexio_exit_code trexio_text_read_qmc_point (trexio_t* const file, double* const qmc_point, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_qmc_point(trexio_t* const file, const double* qmc_point, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_qmc_psi (trexio_t* const file);
trexio_exit_code trexio_text_read_qmc_psi (trexio_t* const file, double* const qmc_psi, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_qmc_psi(trexio_t* const file, const double* qmc_psi, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_qmc_e_loc (trexio_t* const file);
trexio_exit_code trexio_text_read_qmc_e_loc (trexio_t* const file, double* const qmc_e_loc, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_qmc_e_loc(trexio_t* const file, const double* qmc_e_loc, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_metadata_code (trexio_t* const file);
trexio_exit_code trexio_text_read_metadata_code (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_metadata_code (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_metadata_author (trexio_t* const file);
trexio_exit_code trexio_text_read_metadata_author (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_metadata_author (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_nucleus_label (trexio_t* const file);
trexio_exit_code trexio_text_read_nucleus_label (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_nucleus_label (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_state_label (trexio_t* const file);
trexio_exit_code trexio_text_read_state_label (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_state_label (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_state_file_name (trexio_t* const file);
trexio_exit_code trexio_text_read_state_file_name (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_state_file_name (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_class (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_class (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_mo_class (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_mo_symmetry (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_symmetry (trexio_t* const file, char* const dset, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_mo_symmetry (trexio_t* const file, const char** dset, const uint32_t rank, const uint64_t* dims);

trexio_exit_code trexio_text_has_ao_2e_int_eri(trexio_t* const file);
trexio_exit_code trexio_text_read_ao_2e_int_eri(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_ao_2e_int_eri(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_ao_2e_int_eri_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_ao_2e_int_eri_lr(trexio_t* const file);
trexio_exit_code trexio_text_read_ao_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_ao_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_ao_2e_int_eri_lr_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_ao_2e_int_eri_cholesky(trexio_t* const file);
trexio_exit_code trexio_text_read_ao_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_ao_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_ao_2e_int_eri_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_ao_2e_int_eri_lr_cholesky(trexio_t* const file);
trexio_exit_code trexio_text_read_ao_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_ao_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_ao_2e_int_eri_lr_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_mo_2e_int_eri(trexio_t* const file);
trexio_exit_code trexio_text_read_mo_2e_int_eri(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_mo_2e_int_eri(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_mo_2e_int_eri_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_mo_2e_int_eri_lr(trexio_t* const file);
trexio_exit_code trexio_text_read_mo_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_mo_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_mo_2e_int_eri_lr_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_mo_2e_int_eri_cholesky(trexio_t* const file);
trexio_exit_code trexio_text_read_mo_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_mo_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_mo_2e_int_eri_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_mo_2e_int_eri_lr_cholesky(trexio_t* const file);
trexio_exit_code trexio_text_read_mo_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_mo_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_mo_2e_int_eri_lr_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_csf_det_coefficient(trexio_t* const file);
trexio_exit_code trexio_text_read_csf_det_coefficient(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_csf_det_coefficient(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_csf_det_coefficient_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_amplitude_single(trexio_t* const file);
trexio_exit_code trexio_text_read_amplitude_single(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_amplitude_single(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_amplitude_single_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_amplitude_single_exp(trexio_t* const file);
trexio_exit_code trexio_text_read_amplitude_single_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_amplitude_single_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_amplitude_single_exp_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_amplitude_double(trexio_t* const file);
trexio_exit_code trexio_text_read_amplitude_double(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_amplitude_double(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_amplitude_double_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_amplitude_double_exp(trexio_t* const file);
trexio_exit_code trexio_text_read_amplitude_double_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_amplitude_double_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_amplitude_double_exp_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_amplitude_triple(trexio_t* const file);
trexio_exit_code trexio_text_read_amplitude_triple(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_amplitude_triple(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_amplitude_triple_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_amplitude_triple_exp(trexio_t* const file);
trexio_exit_code trexio_text_read_amplitude_triple_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_amplitude_triple_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_amplitude_triple_exp_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_amplitude_quadruple(trexio_t* const file);
trexio_exit_code trexio_text_read_amplitude_quadruple(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_amplitude_quadruple(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_amplitude_quadruple_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_amplitude_quadruple_exp(trexio_t* const file);
trexio_exit_code trexio_text_read_amplitude_quadruple_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_amplitude_quadruple_exp(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_amplitude_quadruple_exp_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_rdm_2e(trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_rdm_2e(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_rdm_2e_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_rdm_2e_upup(trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e_upup(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_rdm_2e_upup(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_rdm_2e_upup_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_rdm_2e_dndn(trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e_dndn(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_rdm_2e_dndn(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_rdm_2e_dndn_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_rdm_2e_updn(trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e_updn(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_rdm_2e_updn(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_rdm_2e_updn_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_rdm_2e_transition(trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e_transition(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_rdm_2e_transition(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_rdm_2e_transition_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_rdm_2e_cholesky(trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_rdm_2e_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_rdm_2e_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_rdm_2e_upup_cholesky(trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e_upup_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_rdm_2e_upup_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_rdm_2e_upup_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_rdm_2e_dndn_cholesky(trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e_dndn_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_rdm_2e_dndn_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_rdm_2e_dndn_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_rdm_2e_updn_cholesky(trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e_updn_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, int64_t* const eof_read_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_text_write_rdm_2e_updn_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t size, const int64_t size_max, const int64_t size_start, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_text_read_rdm_2e_updn_cholesky_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_metadata_code_num (trexio_t* const file);
trexio_exit_code trexio_text_read_metadata_code_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_metadata_code_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_metadata_author_num (trexio_t* const file);
trexio_exit_code trexio_text_read_metadata_author_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_metadata_author_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_metadata_unsafe (trexio_t* const file);
trexio_exit_code trexio_text_read_metadata_unsafe (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_metadata_unsafe(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_nucleus_num (trexio_t* const file);
trexio_exit_code trexio_text_read_nucleus_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_nucleus_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_nucleus_repulsion (trexio_t* const file);
trexio_exit_code trexio_text_read_nucleus_repulsion (trexio_t* const file, double* const num);
trexio_exit_code trexio_text_write_nucleus_repulsion(trexio_t* const file, const double num);

trexio_exit_code trexio_text_has_cell_two_pi (trexio_t* const file);
trexio_exit_code trexio_text_read_cell_two_pi (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_cell_two_pi(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_pbc_periodic (trexio_t* const file);
trexio_exit_code trexio_text_read_pbc_periodic (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_pbc_periodic(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_pbc_k_point_num (trexio_t* const file);
trexio_exit_code trexio_text_read_pbc_k_point_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_pbc_k_point_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_pbc_madelung (trexio_t* const file);
trexio_exit_code trexio_text_read_pbc_madelung (trexio_t* const file, double* const num);
trexio_exit_code trexio_text_write_pbc_madelung(trexio_t* const file, const double num);

trexio_exit_code trexio_text_has_electron_num (trexio_t* const file);
trexio_exit_code trexio_text_read_electron_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_electron_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_electron_up_num (trexio_t* const file);
trexio_exit_code trexio_text_read_electron_up_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_electron_up_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_electron_dn_num (trexio_t* const file);
trexio_exit_code trexio_text_read_electron_dn_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_electron_dn_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_state_num (trexio_t* const file);
trexio_exit_code trexio_text_read_state_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_state_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_state_id (trexio_t* const file);
trexio_exit_code trexio_text_read_state_id (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_state_id(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_state_energy (trexio_t* const file);
trexio_exit_code trexio_text_read_state_energy (trexio_t* const file, double* const num);
trexio_exit_code trexio_text_write_state_energy(trexio_t* const file, const double num);

trexio_exit_code trexio_text_has_basis_prim_num (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_prim_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_basis_prim_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_basis_shell_num (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_shell_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_basis_shell_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_basis_nao_grid_num (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_nao_grid_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_basis_nao_grid_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_basis_interp_coeff_cnt (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_interp_coeff_cnt (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_basis_interp_coeff_cnt(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_basis_e_cut (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_e_cut (trexio_t* const file, double* const num);
trexio_exit_code trexio_text_write_basis_e_cut(trexio_t* const file, const double num);

trexio_exit_code trexio_text_has_ecp_num (trexio_t* const file);
trexio_exit_code trexio_text_read_ecp_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_ecp_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_grid_rad_precision (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_rad_precision (trexio_t* const file, double* const num);
trexio_exit_code trexio_text_write_grid_rad_precision(trexio_t* const file, const double num);

trexio_exit_code trexio_text_has_grid_num (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_grid_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_grid_max_ang_num (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_max_ang_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_grid_max_ang_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_grid_min_ang_num (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_min_ang_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_grid_min_ang_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_grid_ang_num (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_ang_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_grid_ang_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_grid_rad_num (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_rad_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_grid_rad_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_ao_cartesian (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_cartesian (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_ao_cartesian(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_ao_num (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_ao_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_ao_2e_int_eri_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_2e_int_eri_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_ao_2e_int_eri_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_ao_2e_int_eri_lr_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_text_read_ao_2e_int_eri_lr_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_ao_2e_int_eri_lr_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_mo_num (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_mo_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_mo_2e_int_eri_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_2e_int_eri_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_mo_2e_int_eri_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_mo_2e_int_eri_lr_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_2e_int_eri_lr_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_mo_2e_int_eri_lr_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_determinant_num (trexio_t* const file);
trexio_exit_code trexio_text_read_determinant_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_determinant_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_csf_num (trexio_t* const file);
trexio_exit_code trexio_text_read_csf_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_csf_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_rdm_2e_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_rdm_2e_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_rdm_2e_upup_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e_upup_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_rdm_2e_upup_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_rdm_2e_dndn_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e_dndn_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_rdm_2e_dndn_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_rdm_2e_updn_cholesky_num (trexio_t* const file);
trexio_exit_code trexio_text_read_rdm_2e_updn_cholesky_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_rdm_2e_updn_cholesky_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_jastrow_en_num (trexio_t* const file);
trexio_exit_code trexio_text_read_jastrow_en_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_jastrow_en_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_jastrow_ee_num (trexio_t* const file);
trexio_exit_code trexio_text_read_jastrow_ee_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_jastrow_ee_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_jastrow_een_num (trexio_t* const file);
trexio_exit_code trexio_text_read_jastrow_een_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_jastrow_een_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_jastrow_ee_scaling (trexio_t* const file);
trexio_exit_code trexio_text_read_jastrow_ee_scaling (trexio_t* const file, double* const num);
trexio_exit_code trexio_text_write_jastrow_ee_scaling(trexio_t* const file, const double num);

trexio_exit_code trexio_text_has_qmc_num (trexio_t* const file);
trexio_exit_code trexio_text_read_qmc_num (trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_text_write_qmc_num(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_text_has_metadata_package_version (trexio_t* const file);
trexio_exit_code trexio_text_read_metadata_package_version (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_metadata_package_version (trexio_t* const file, const char* str);

trexio_exit_code trexio_text_has_metadata_description (trexio_t* const file);
trexio_exit_code trexio_text_read_metadata_description (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_metadata_description (trexio_t* const file, const char* str);

trexio_exit_code trexio_text_has_nucleus_point_group (trexio_t* const file);
trexio_exit_code trexio_text_read_nucleus_point_group (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_nucleus_point_group (trexio_t* const file, const char* str);

trexio_exit_code trexio_text_has_state_current_label (trexio_t* const file);
trexio_exit_code trexio_text_read_state_current_label (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_state_current_label (trexio_t* const file, const char* str);

trexio_exit_code trexio_text_has_basis_type (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_type (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_basis_type (trexio_t* const file, const char* str);

trexio_exit_code trexio_text_has_basis_oscillation_kind (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_oscillation_kind (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_basis_oscillation_kind (trexio_t* const file, const char* str);

trexio_exit_code trexio_text_has_basis_interpolator_kind (trexio_t* const file);
trexio_exit_code trexio_text_read_basis_interpolator_kind (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_basis_interpolator_kind (trexio_t* const file, const char* str);

trexio_exit_code trexio_text_has_grid_description (trexio_t* const file);
trexio_exit_code trexio_text_read_grid_description (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_grid_description (trexio_t* const file, const char* str);

trexio_exit_code trexio_text_has_mo_type (trexio_t* const file);
trexio_exit_code trexio_text_read_mo_type (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_mo_type (trexio_t* const file, const char* str);

trexio_exit_code trexio_text_has_jastrow_type (trexio_t* const file);
trexio_exit_code trexio_text_read_jastrow_type (trexio_t* const file, char* const str, const uint32_t max_str_len);
trexio_exit_code trexio_text_write_jastrow_type (trexio_t* const file, const char* str);

trexio_exit_code trexio_text_has_determinant_coefficient(trexio_t* const file);
trexio_exit_code trexio_text_read_determinant_coefficient(trexio_t* const file, const int64_t offset_file, const uint32_t rank, const uint64_t* dims, int64_t* const eof_read_size, double* const dset);
trexio_exit_code trexio_text_write_determinant_coefficient(trexio_t* const file, const int64_t offset_file, const uint32_t rank, const uint64_t* dims, const double* dset);
trexio_exit_code trexio_text_read_determinant_coefficient_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_text_has_csf_coefficient(trexio_t* const file);
trexio_exit_code trexio_text_read_csf_coefficient(trexio_t* const file, const int64_t offset_file, const uint32_t rank, const uint64_t* dims, int64_t* const eof_read_size, double* const dset);
trexio_exit_code trexio_text_write_csf_coefficient(trexio_t* const file, const int64_t offset_file, const uint32_t rank, const uint64_t* dims, const double* dset);
trexio_exit_code trexio_text_read_csf_coefficient_size(trexio_t* const file, int64_t* const size_max);

#endif
