/* This file was generated from the org-mode file.
   To generate it, open templator_hdf5.org file in Emacs and execute
   M-x org-babel-tangle
*/

#include "trexio_hdf5.h"
#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif
#
#ifdef HAVE_HDF5
#define METADATA_GROUP_NAME          "metadata"
#define NUCLEUS_GROUP_NAME          "nucleus"
#define CELL_GROUP_NAME          "cell"
#define PBC_GROUP_NAME          "pbc"
#define ELECTRON_GROUP_NAME          "electron"
#define STATE_GROUP_NAME          "state"
#define BASIS_GROUP_NAME          "basis"
#define ECP_GROUP_NAME          "ecp"
#define GRID_GROUP_NAME          "grid"
#define AO_GROUP_NAME          "ao"
#define AO_1E_INT_GROUP_NAME          "ao_1e_int"
#define AO_2E_INT_GROUP_NAME          "ao_2e_int"
#define MO_GROUP_NAME          "mo"
#define MO_1E_INT_GROUP_NAME          "mo_1e_int"
#define MO_2E_INT_GROUP_NAME          "mo_2e_int"
#define DETERMINANT_GROUP_NAME          "determinant"
#define CSF_GROUP_NAME          "csf"
#define AMPLITUDE_GROUP_NAME          "amplitude"
#define RDM_GROUP_NAME          "rdm"
#define JASTROW_GROUP_NAME          "jastrow"
#define QMC_GROUP_NAME          "qmc"
#define METADATA_CODE_NUM_NAME            "metadata_code_num"
#define METADATA_AUTHOR_NUM_NAME            "metadata_author_num"
#define METADATA_UNSAFE_NAME            "metadata_unsafe"
#define NUCLEUS_NUM_NAME            "nucleus_num"
#define NUCLEUS_REPULSION_NAME            "nucleus_repulsion"
#define CELL_TWO_PI_NAME            "cell_two_pi"
#define PBC_PERIODIC_NAME            "pbc_periodic"
#define PBC_K_POINT_NUM_NAME            "pbc_k_point_num"
#define PBC_MADELUNG_NAME            "pbc_madelung"
#define ELECTRON_NUM_NAME            "electron_num"
#define ELECTRON_UP_NUM_NAME            "electron_up_num"
#define ELECTRON_DN_NUM_NAME            "electron_dn_num"
#define STATE_NUM_NAME            "state_num"
#define STATE_ID_NAME            "state_id"
#define STATE_ENERGY_NAME            "state_energy"
#define BASIS_PRIM_NUM_NAME            "basis_prim_num"
#define BASIS_SHELL_NUM_NAME            "basis_shell_num"
#define BASIS_NAO_GRID_NUM_NAME            "basis_nao_grid_num"
#define BASIS_INTERP_COEFF_CNT_NAME            "basis_interp_coeff_cnt"
#define BASIS_E_CUT_NAME            "basis_e_cut"
#define ECP_NUM_NAME            "ecp_num"
#define GRID_RAD_PRECISION_NAME            "grid_rad_precision"
#define GRID_NUM_NAME            "grid_num"
#define GRID_MAX_ANG_NUM_NAME            "grid_max_ang_num"
#define GRID_MIN_ANG_NUM_NAME            "grid_min_ang_num"
#define GRID_ANG_NUM_NAME            "grid_ang_num"
#define GRID_RAD_NUM_NAME            "grid_rad_num"
#define AO_CARTESIAN_NAME            "ao_cartesian"
#define AO_NUM_NAME            "ao_num"
#define AO_2E_INT_ERI_CHOLESKY_NUM_NAME            "ao_2e_int_eri_cholesky_num"
#define AO_2E_INT_ERI_LR_CHOLESKY_NUM_NAME            "ao_2e_int_eri_lr_cholesky_num"
#define MO_NUM_NAME            "mo_num"
#define MO_2E_INT_ERI_CHOLESKY_NUM_NAME            "mo_2e_int_eri_cholesky_num"
#define MO_2E_INT_ERI_LR_CHOLESKY_NUM_NAME            "mo_2e_int_eri_lr_cholesky_num"
#define DETERMINANT_NUM_NAME            "determinant_num"
#define CSF_NUM_NAME            "csf_num"
#define RDM_2E_CHOLESKY_NUM_NAME            "rdm_2e_cholesky_num"
#define RDM_2E_UPUP_CHOLESKY_NUM_NAME            "rdm_2e_upup_cholesky_num"
#define RDM_2E_DNDN_CHOLESKY_NUM_NAME            "rdm_2e_dndn_cholesky_num"
#define RDM_2E_UPDN_CHOLESKY_NUM_NAME            "rdm_2e_updn_cholesky_num"
#define JASTROW_EN_NUM_NAME            "jastrow_en_num"
#define JASTROW_EE_NUM_NAME            "jastrow_ee_num"
#define JASTROW_EEN_NUM_NAME            "jastrow_een_num"
#define JASTROW_EE_SCALING_NAME            "jastrow_ee_scaling"
#define QMC_NUM_NAME            "qmc_num"
#define NUCLEUS_CHARGE_NAME           "nucleus_charge"
#define NUCLEUS_COORD_NAME           "nucleus_coord"
#define CELL_A_NAME           "cell_a"
#define CELL_B_NAME           "cell_b"
#define CELL_C_NAME           "cell_c"
#define CELL_G_A_NAME           "cell_g_a"
#define CELL_G_B_NAME           "cell_g_b"
#define CELL_G_C_NAME           "cell_g_c"
#define PBC_K_POINT_NAME           "pbc_k_point"
#define PBC_K_POINT_WEIGHT_NAME           "pbc_k_point_weight"
#define BASIS_NUCLEUS_INDEX_NAME           "basis_nucleus_index"
#define BASIS_SHELL_ANG_MOM_NAME           "basis_shell_ang_mom"
#define BASIS_SHELL_FACTOR_NAME           "basis_shell_factor"
#define BASIS_R_POWER_NAME           "basis_r_power"
#define BASIS_NAO_GRID_START_NAME           "basis_nao_grid_start"
#define BASIS_NAO_GRID_SIZE_NAME           "basis_nao_grid_size"
#define BASIS_SHELL_INDEX_NAME           "basis_shell_index"
#define BASIS_EXPONENT_NAME           "basis_exponent"
#define BASIS_EXPONENT_IM_NAME           "basis_exponent_im"
#define BASIS_COEFFICIENT_NAME           "basis_coefficient"
#define BASIS_COEFFICIENT_IM_NAME           "basis_coefficient_im"
#define BASIS_OSCILLATION_ARG_NAME           "basis_oscillation_arg"
#define BASIS_PRIM_FACTOR_NAME           "basis_prim_factor"
#define BASIS_NAO_GRID_RADIUS_NAME           "basis_nao_grid_radius"
#define BASIS_NAO_GRID_PHI_NAME           "basis_nao_grid_phi"
#define BASIS_NAO_GRID_GRAD_NAME           "basis_nao_grid_grad"
#define BASIS_NAO_GRID_LAP_NAME           "basis_nao_grid_lap"
#define BASIS_INTERPOLATOR_PHI_NAME           "basis_interpolator_phi"
#define BASIS_INTERPOLATOR_GRAD_NAME           "basis_interpolator_grad"
#define BASIS_INTERPOLATOR_LAP_NAME           "basis_interpolator_lap"
#define ECP_MAX_ANG_MOM_PLUS_1_NAME           "ecp_max_ang_mom_plus_1"
#define ECP_Z_CORE_NAME           "ecp_z_core"
#define ECP_ANG_MOM_NAME           "ecp_ang_mom"
#define ECP_NUCLEUS_INDEX_NAME           "ecp_nucleus_index"
#define ECP_EXPONENT_NAME           "ecp_exponent"
#define ECP_COEFFICIENT_NAME           "ecp_coefficient"
#define ECP_POWER_NAME           "ecp_power"
#define GRID_COORD_NAME           "grid_coord"
#define GRID_WEIGHT_NAME           "grid_weight"
#define GRID_ANG_COORD_NAME           "grid_ang_coord"
#define GRID_ANG_WEIGHT_NAME           "grid_ang_weight"
#define GRID_RAD_COORD_NAME           "grid_rad_coord"
#define GRID_RAD_WEIGHT_NAME           "grid_rad_weight"
#define AO_SHELL_NAME           "ao_shell"
#define AO_NORMALIZATION_NAME           "ao_normalization"
#define AO_1E_INT_OVERLAP_NAME           "ao_1e_int_overlap"
#define AO_1E_INT_KINETIC_NAME           "ao_1e_int_kinetic"
#define AO_1E_INT_POTENTIAL_N_E_NAME           "ao_1e_int_potential_n_e"
#define AO_1E_INT_ECP_NAME           "ao_1e_int_ecp"
#define AO_1E_INT_CORE_HAMILTONIAN_NAME           "ao_1e_int_core_hamiltonian"
#define AO_1E_INT_OVERLAP_IM_NAME           "ao_1e_int_overlap_im"
#define AO_1E_INT_KINETIC_IM_NAME           "ao_1e_int_kinetic_im"
#define AO_1E_INT_POTENTIAL_N_E_IM_NAME           "ao_1e_int_potential_n_e_im"
#define AO_1E_INT_ECP_IM_NAME           "ao_1e_int_ecp_im"
#define AO_1E_INT_CORE_HAMILTONIAN_IM_NAME           "ao_1e_int_core_hamiltonian_im"
#define MO_COEFFICIENT_NAME           "mo_coefficient"
#define MO_COEFFICIENT_IM_NAME           "mo_coefficient_im"
#define MO_OCCUPATION_NAME           "mo_occupation"
#define MO_ENERGY_NAME           "mo_energy"
#define MO_SPIN_NAME           "mo_spin"
#define MO_K_POINT_NAME           "mo_k_point"
#define MO_1E_INT_OVERLAP_NAME           "mo_1e_int_overlap"
#define MO_1E_INT_KINETIC_NAME           "mo_1e_int_kinetic"
#define MO_1E_INT_POTENTIAL_N_E_NAME           "mo_1e_int_potential_n_e"
#define MO_1E_INT_ECP_NAME           "mo_1e_int_ecp"
#define MO_1E_INT_CORE_HAMILTONIAN_NAME           "mo_1e_int_core_hamiltonian"
#define MO_1E_INT_OVERLAP_IM_NAME           "mo_1e_int_overlap_im"
#define MO_1E_INT_KINETIC_IM_NAME           "mo_1e_int_kinetic_im"
#define MO_1E_INT_POTENTIAL_N_E_IM_NAME           "mo_1e_int_potential_n_e_im"
#define MO_1E_INT_ECP_IM_NAME           "mo_1e_int_ecp_im"
#define MO_1E_INT_CORE_HAMILTONIAN_IM_NAME           "mo_1e_int_core_hamiltonian_im"
#define RDM_1E_NAME           "rdm_1e"
#define RDM_1E_UP_NAME           "rdm_1e_up"
#define RDM_1E_DN_NAME           "rdm_1e_dn"
#define RDM_1E_TRANSITION_NAME           "rdm_1e_transition"
#define JASTROW_EN_NAME           "jastrow_en"
#define JASTROW_EE_NAME           "jastrow_ee"
#define JASTROW_EEN_NAME           "jastrow_een"
#define JASTROW_EN_NUCLEUS_NAME           "jastrow_en_nucleus"
#define JASTROW_EEN_NUCLEUS_NAME           "jastrow_een_nucleus"
#define JASTROW_EN_SCALING_NAME           "jastrow_en_scaling"
#define QMC_POINT_NAME           "qmc_point"
#define QMC_PSI_NAME           "qmc_psi"
#define QMC_E_LOC_NAME           "qmc_e_loc"
#define METADATA_CODE_NAME           "metadata_code"
#define METADATA_AUTHOR_NAME           "metadata_author"
#define NUCLEUS_LABEL_NAME           "nucleus_label"
#define STATE_LABEL_NAME           "state_label"
#define STATE_FILE_NAME_NAME           "state_file_name"
#define MO_CLASS_NAME           "mo_class"
#define MO_SYMMETRY_NAME           "mo_symmetry"
#define AO_2E_INT_ERI_NAME           "ao_2e_int_eri"
#define AO_2E_INT_ERI_LR_NAME           "ao_2e_int_eri_lr"
#define AO_2E_INT_ERI_CHOLESKY_NAME           "ao_2e_int_eri_cholesky"
#define AO_2E_INT_ERI_LR_CHOLESKY_NAME           "ao_2e_int_eri_lr_cholesky"
#define MO_2E_INT_ERI_NAME           "mo_2e_int_eri"
#define MO_2E_INT_ERI_LR_NAME           "mo_2e_int_eri_lr"
#define MO_2E_INT_ERI_CHOLESKY_NAME           "mo_2e_int_eri_cholesky"
#define MO_2E_INT_ERI_LR_CHOLESKY_NAME           "mo_2e_int_eri_lr_cholesky"
#define CSF_DET_COEFFICIENT_NAME           "csf_det_coefficient"
#define AMPLITUDE_SINGLE_NAME           "amplitude_single"
#define AMPLITUDE_SINGLE_EXP_NAME           "amplitude_single_exp"
#define AMPLITUDE_DOUBLE_NAME           "amplitude_double"
#define AMPLITUDE_DOUBLE_EXP_NAME           "amplitude_double_exp"
#define AMPLITUDE_TRIPLE_NAME           "amplitude_triple"
#define AMPLITUDE_TRIPLE_EXP_NAME           "amplitude_triple_exp"
#define AMPLITUDE_QUADRUPLE_NAME           "amplitude_quadruple"
#define AMPLITUDE_QUADRUPLE_EXP_NAME           "amplitude_quadruple_exp"
#define RDM_2E_NAME           "rdm_2e"
#define RDM_2E_UPUP_NAME           "rdm_2e_upup"
#define RDM_2E_DNDN_NAME           "rdm_2e_dndn"
#define RDM_2E_UPDN_NAME           "rdm_2e_updn"
#define RDM_2E_TRANSITION_NAME           "rdm_2e_transition"
#define RDM_2E_CHOLESKY_NAME           "rdm_2e_cholesky"
#define RDM_2E_UPUP_CHOLESKY_NAME           "rdm_2e_upup_cholesky"
#define RDM_2E_DNDN_CHOLESKY_NAME           "rdm_2e_dndn_cholesky"
#define RDM_2E_UPDN_CHOLESKY_NAME           "rdm_2e_updn_cholesky"
#define DETERMINANT_COEFFICIENT_NAME           "determinant_coefficient"
#define CSF_COEFFICIENT_NAME           "csf_coefficient"
#define METADATA_PACKAGE_VERSION_NAME            "metadata_package_version"
#define METADATA_DESCRIPTION_NAME            "metadata_description"
#define NUCLEUS_POINT_GROUP_NAME            "nucleus_point_group"
#define STATE_CURRENT_LABEL_NAME            "state_current_label"
#define BASIS_TYPE_NAME            "basis_type"
#define BASIS_OSCILLATION_KIND_NAME            "basis_oscillation_kind"
#define BASIS_INTERPOLATOR_KIND_NAME            "basis_interpolator_kind"
#define GRID_DESCRIPTION_NAME            "grid_description"
#define MO_TYPE_NAME            "mo_type"
#define JASTROW_TYPE_NAME            "jastrow_type"

trexio_exit_code
trexio_hdf5_flush(trexio_t* const file)
{

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  herr_t rc = H5Fflush(f->file_id, H5F_SCOPE_GLOBAL);
  if (rc < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_inquire(const char* file_name)
{
  /* H5Fis_hdf5 determines whether file is in HDF5 format */
  htri_t rc = H5Fis_hdf5(file_name);
  if (rc > 0 ) {
    return TREXIO_SUCCESS;    //exists and HDF5
  } else if (rc == 0) {
    return TREXIO_FILE_ERROR; //exists but not HDF5
  } else {
    return TREXIO_FAILURE;    //does not exist or function fails
  }
}

trexio_exit_code
trexio_hdf5_init (trexio_t* const file)
{

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* If file doesn't exist, create it */
  int f_exists = 0;
  struct stat st;

  if (stat(file->file_name, &st) == 0) f_exists = 1;

  if (f_exists == 1) {

    switch (file->mode) {
    case 'r':
      // reading the existing file -> open as RDONLY
      f->file_id = H5Fopen(file->file_name, H5F_ACC_RDONLY, H5P_DEFAULT);
      break;
    case 'u':
    case 'w':
      // writing the existing file -> open as RDWRITE
      f->file_id = H5Fopen(file->file_name, H5F_ACC_RDWR, H5P_DEFAULT);
      break;
    }

  } else {

    switch (file->mode) {
    case 'r':
      // reading non-existing file -> error
      return TREXIO_FAILURE;
    case 'u':
    case 'w':
      // writing non-existing file -> create it
      f->file_id = H5Fcreate(file->file_name, H5F_ACC_EXCL, H5P_DEFAULT, H5P_DEFAULT);
      break;
    }

  }

  /* Create or open groups in the hdf5 file assuming that they exist if file exists */
  switch (file->mode) {
    case 'r':
      if (H5Lexists(f->file_id, METADATA_GROUP_NAME, H5P_DEFAULT) > 0) f->metadata_group = H5Gopen(f->file_id, METADATA_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, NUCLEUS_GROUP_NAME, H5P_DEFAULT) > 0) f->nucleus_group = H5Gopen(f->file_id, NUCLEUS_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, CELL_GROUP_NAME, H5P_DEFAULT) > 0) f->cell_group = H5Gopen(f->file_id, CELL_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, PBC_GROUP_NAME, H5P_DEFAULT) > 0) f->pbc_group = H5Gopen(f->file_id, PBC_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, ELECTRON_GROUP_NAME, H5P_DEFAULT) > 0) f->electron_group = H5Gopen(f->file_id, ELECTRON_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, STATE_GROUP_NAME, H5P_DEFAULT) > 0) f->state_group = H5Gopen(f->file_id, STATE_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, BASIS_GROUP_NAME, H5P_DEFAULT) > 0) f->basis_group = H5Gopen(f->file_id, BASIS_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, ECP_GROUP_NAME, H5P_DEFAULT) > 0) f->ecp_group = H5Gopen(f->file_id, ECP_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, GRID_GROUP_NAME, H5P_DEFAULT) > 0) f->grid_group = H5Gopen(f->file_id, GRID_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, AO_GROUP_NAME, H5P_DEFAULT) > 0) f->ao_group = H5Gopen(f->file_id, AO_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, AO_1E_INT_GROUP_NAME, H5P_DEFAULT) > 0) f->ao_1e_int_group = H5Gopen(f->file_id, AO_1E_INT_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, AO_2E_INT_GROUP_NAME, H5P_DEFAULT) > 0) f->ao_2e_int_group = H5Gopen(f->file_id, AO_2E_INT_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, MO_GROUP_NAME, H5P_DEFAULT) > 0) f->mo_group = H5Gopen(f->file_id, MO_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, MO_1E_INT_GROUP_NAME, H5P_DEFAULT) > 0) f->mo_1e_int_group = H5Gopen(f->file_id, MO_1E_INT_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, MO_2E_INT_GROUP_NAME, H5P_DEFAULT) > 0) f->mo_2e_int_group = H5Gopen(f->file_id, MO_2E_INT_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, DETERMINANT_GROUP_NAME, H5P_DEFAULT) > 0) f->determinant_group = H5Gopen(f->file_id, DETERMINANT_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, CSF_GROUP_NAME, H5P_DEFAULT) > 0) f->csf_group = H5Gopen(f->file_id, CSF_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, AMPLITUDE_GROUP_NAME, H5P_DEFAULT) > 0) f->amplitude_group = H5Gopen(f->file_id, AMPLITUDE_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, RDM_GROUP_NAME, H5P_DEFAULT) > 0) f->rdm_group = H5Gopen(f->file_id, RDM_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, JASTROW_GROUP_NAME, H5P_DEFAULT) > 0) f->jastrow_group = H5Gopen(f->file_id, JASTROW_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, QMC_GROUP_NAME, H5P_DEFAULT) > 0) f->qmc_group = H5Gopen(f->file_id, QMC_GROUP_NAME, H5P_DEFAULT);
      if (H5Lexists(f->file_id, METADATA_GROUP_NAME, H5P_DEFAULT) == 0) f->metadata_group = (hid_t) 0;
      if (H5Lexists(f->file_id, NUCLEUS_GROUP_NAME, H5P_DEFAULT) == 0) f->nucleus_group = (hid_t) 0;
      if (H5Lexists(f->file_id, CELL_GROUP_NAME, H5P_DEFAULT) == 0) f->cell_group = (hid_t) 0;
      if (H5Lexists(f->file_id, PBC_GROUP_NAME, H5P_DEFAULT) == 0) f->pbc_group = (hid_t) 0;
      if (H5Lexists(f->file_id, ELECTRON_GROUP_NAME, H5P_DEFAULT) == 0) f->electron_group = (hid_t) 0;
      if (H5Lexists(f->file_id, STATE_GROUP_NAME, H5P_DEFAULT) == 0) f->state_group = (hid_t) 0;
      if (H5Lexists(f->file_id, BASIS_GROUP_NAME, H5P_DEFAULT) == 0) f->basis_group = (hid_t) 0;
      if (H5Lexists(f->file_id, ECP_GROUP_NAME, H5P_DEFAULT) == 0) f->ecp_group = (hid_t) 0;
      if (H5Lexists(f->file_id, GRID_GROUP_NAME, H5P_DEFAULT) == 0) f->grid_group = (hid_t) 0;
      if (H5Lexists(f->file_id, AO_GROUP_NAME, H5P_DEFAULT) == 0) f->ao_group = (hid_t) 0;
      if (H5Lexists(f->file_id, AO_1E_INT_GROUP_NAME, H5P_DEFAULT) == 0) f->ao_1e_int_group = (hid_t) 0;
      if (H5Lexists(f->file_id, AO_2E_INT_GROUP_NAME, H5P_DEFAULT) == 0) f->ao_2e_int_group = (hid_t) 0;
      if (H5Lexists(f->file_id, MO_GROUP_NAME, H5P_DEFAULT) == 0) f->mo_group = (hid_t) 0;
      if (H5Lexists(f->file_id, MO_1E_INT_GROUP_NAME, H5P_DEFAULT) == 0) f->mo_1e_int_group = (hid_t) 0;
      if (H5Lexists(f->file_id, MO_2E_INT_GROUP_NAME, H5P_DEFAULT) == 0) f->mo_2e_int_group = (hid_t) 0;
      if (H5Lexists(f->file_id, DETERMINANT_GROUP_NAME, H5P_DEFAULT) == 0) f->determinant_group = (hid_t) 0;
      if (H5Lexists(f->file_id, CSF_GROUP_NAME, H5P_DEFAULT) == 0) f->csf_group = (hid_t) 0;
      if (H5Lexists(f->file_id, AMPLITUDE_GROUP_NAME, H5P_DEFAULT) == 0) f->amplitude_group = (hid_t) 0;
      if (H5Lexists(f->file_id, RDM_GROUP_NAME, H5P_DEFAULT) == 0) f->rdm_group = (hid_t) 0;
      if (H5Lexists(f->file_id, JASTROW_GROUP_NAME, H5P_DEFAULT) == 0) f->jastrow_group = (hid_t) 0;
      if (H5Lexists(f->file_id, QMC_GROUP_NAME, H5P_DEFAULT) == 0) f->qmc_group = (hid_t) 0;
      break;
    case 'u':
    case 'w':
      if (f_exists == 1) {
        if (H5Lexists(f->file_id, METADATA_GROUP_NAME, H5P_DEFAULT) >  0) f->metadata_group = H5Gopen(f->file_id, METADATA_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, NUCLEUS_GROUP_NAME, H5P_DEFAULT) >  0) f->nucleus_group = H5Gopen(f->file_id, NUCLEUS_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, CELL_GROUP_NAME, H5P_DEFAULT) >  0) f->cell_group = H5Gopen(f->file_id, CELL_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, PBC_GROUP_NAME, H5P_DEFAULT) >  0) f->pbc_group = H5Gopen(f->file_id, PBC_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, ELECTRON_GROUP_NAME, H5P_DEFAULT) >  0) f->electron_group = H5Gopen(f->file_id, ELECTRON_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, STATE_GROUP_NAME, H5P_DEFAULT) >  0) f->state_group = H5Gopen(f->file_id, STATE_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, BASIS_GROUP_NAME, H5P_DEFAULT) >  0) f->basis_group = H5Gopen(f->file_id, BASIS_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, ECP_GROUP_NAME, H5P_DEFAULT) >  0) f->ecp_group = H5Gopen(f->file_id, ECP_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, GRID_GROUP_NAME, H5P_DEFAULT) >  0) f->grid_group = H5Gopen(f->file_id, GRID_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, AO_GROUP_NAME, H5P_DEFAULT) >  0) f->ao_group = H5Gopen(f->file_id, AO_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, AO_1E_INT_GROUP_NAME, H5P_DEFAULT) >  0) f->ao_1e_int_group = H5Gopen(f->file_id, AO_1E_INT_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, AO_2E_INT_GROUP_NAME, H5P_DEFAULT) >  0) f->ao_2e_int_group = H5Gopen(f->file_id, AO_2E_INT_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, MO_GROUP_NAME, H5P_DEFAULT) >  0) f->mo_group = H5Gopen(f->file_id, MO_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, MO_1E_INT_GROUP_NAME, H5P_DEFAULT) >  0) f->mo_1e_int_group = H5Gopen(f->file_id, MO_1E_INT_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, MO_2E_INT_GROUP_NAME, H5P_DEFAULT) >  0) f->mo_2e_int_group = H5Gopen(f->file_id, MO_2E_INT_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, DETERMINANT_GROUP_NAME, H5P_DEFAULT) >  0) f->determinant_group = H5Gopen(f->file_id, DETERMINANT_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, CSF_GROUP_NAME, H5P_DEFAULT) >  0) f->csf_group = H5Gopen(f->file_id, CSF_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, AMPLITUDE_GROUP_NAME, H5P_DEFAULT) >  0) f->amplitude_group = H5Gopen(f->file_id, AMPLITUDE_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, RDM_GROUP_NAME, H5P_DEFAULT) >  0) f->rdm_group = H5Gopen(f->file_id, RDM_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, JASTROW_GROUP_NAME, H5P_DEFAULT) >  0) f->jastrow_group = H5Gopen(f->file_id, JASTROW_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, QMC_GROUP_NAME, H5P_DEFAULT) >  0) f->qmc_group = H5Gopen(f->file_id, QMC_GROUP_NAME, H5P_DEFAULT);
        if (H5Lexists(f->file_id, METADATA_GROUP_NAME, H5P_DEFAULT) == 0) f->metadata_group = H5Gcreate(f->file_id, METADATA_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, NUCLEUS_GROUP_NAME, H5P_DEFAULT) == 0) f->nucleus_group = H5Gcreate(f->file_id, NUCLEUS_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, CELL_GROUP_NAME, H5P_DEFAULT) == 0) f->cell_group = H5Gcreate(f->file_id, CELL_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, PBC_GROUP_NAME, H5P_DEFAULT) == 0) f->pbc_group = H5Gcreate(f->file_id, PBC_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, ELECTRON_GROUP_NAME, H5P_DEFAULT) == 0) f->electron_group = H5Gcreate(f->file_id, ELECTRON_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, STATE_GROUP_NAME, H5P_DEFAULT) == 0) f->state_group = H5Gcreate(f->file_id, STATE_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, BASIS_GROUP_NAME, H5P_DEFAULT) == 0) f->basis_group = H5Gcreate(f->file_id, BASIS_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, ECP_GROUP_NAME, H5P_DEFAULT) == 0) f->ecp_group = H5Gcreate(f->file_id, ECP_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, GRID_GROUP_NAME, H5P_DEFAULT) == 0) f->grid_group = H5Gcreate(f->file_id, GRID_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, AO_GROUP_NAME, H5P_DEFAULT) == 0) f->ao_group = H5Gcreate(f->file_id, AO_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, AO_1E_INT_GROUP_NAME, H5P_DEFAULT) == 0) f->ao_1e_int_group = H5Gcreate(f->file_id, AO_1E_INT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, AO_2E_INT_GROUP_NAME, H5P_DEFAULT) == 0) f->ao_2e_int_group = H5Gcreate(f->file_id, AO_2E_INT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, MO_GROUP_NAME, H5P_DEFAULT) == 0) f->mo_group = H5Gcreate(f->file_id, MO_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, MO_1E_INT_GROUP_NAME, H5P_DEFAULT) == 0) f->mo_1e_int_group = H5Gcreate(f->file_id, MO_1E_INT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, MO_2E_INT_GROUP_NAME, H5P_DEFAULT) == 0) f->mo_2e_int_group = H5Gcreate(f->file_id, MO_2E_INT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, DETERMINANT_GROUP_NAME, H5P_DEFAULT) == 0) f->determinant_group = H5Gcreate(f->file_id, DETERMINANT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, CSF_GROUP_NAME, H5P_DEFAULT) == 0) f->csf_group = H5Gcreate(f->file_id, CSF_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, AMPLITUDE_GROUP_NAME, H5P_DEFAULT) == 0) f->amplitude_group = H5Gcreate(f->file_id, AMPLITUDE_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, RDM_GROUP_NAME, H5P_DEFAULT) == 0) f->rdm_group = H5Gcreate(f->file_id, RDM_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, JASTROW_GROUP_NAME, H5P_DEFAULT) == 0) f->jastrow_group = H5Gcreate(f->file_id, JASTROW_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        if (H5Lexists(f->file_id, QMC_GROUP_NAME, H5P_DEFAULT) == 0) f->qmc_group = H5Gcreate(f->file_id, QMC_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
      } else {
        f->metadata_group = H5Gcreate(f->file_id, METADATA_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->nucleus_group = H5Gcreate(f->file_id, NUCLEUS_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->cell_group = H5Gcreate(f->file_id, CELL_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->pbc_group = H5Gcreate(f->file_id, PBC_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->electron_group = H5Gcreate(f->file_id, ELECTRON_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->state_group = H5Gcreate(f->file_id, STATE_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->basis_group = H5Gcreate(f->file_id, BASIS_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->ecp_group = H5Gcreate(f->file_id, ECP_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->grid_group = H5Gcreate(f->file_id, GRID_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->ao_group = H5Gcreate(f->file_id, AO_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->ao_1e_int_group = H5Gcreate(f->file_id, AO_1E_INT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->ao_2e_int_group = H5Gcreate(f->file_id, AO_2E_INT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->mo_group = H5Gcreate(f->file_id, MO_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->mo_1e_int_group = H5Gcreate(f->file_id, MO_1E_INT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->mo_2e_int_group = H5Gcreate(f->file_id, MO_2E_INT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->determinant_group = H5Gcreate(f->file_id, DETERMINANT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->csf_group = H5Gcreate(f->file_id, CSF_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->amplitude_group = H5Gcreate(f->file_id, AMPLITUDE_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->rdm_group = H5Gcreate(f->file_id, RDM_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->jastrow_group = H5Gcreate(f->file_id, JASTROW_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        f->qmc_group = H5Gcreate(f->file_id, QMC_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
      }
      break;
  }
  if (f->metadata_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->nucleus_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->cell_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->pbc_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->electron_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->state_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->basis_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->ecp_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->grid_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->ao_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->ao_1e_int_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->ao_2e_int_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->mo_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->mo_1e_int_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->mo_2e_int_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->determinant_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->csf_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->amplitude_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->rdm_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->jastrow_group < (hid_t) 0) return TREXIO_INVALID_ID;
  if (f->qmc_group < (hid_t) 0) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_deinit (trexio_t* const file)
{

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  if (f->metadata_group != (hid_t) 0) H5Gclose(f->metadata_group);
  if (f->nucleus_group != (hid_t) 0) H5Gclose(f->nucleus_group);
  if (f->cell_group != (hid_t) 0) H5Gclose(f->cell_group);
  if (f->pbc_group != (hid_t) 0) H5Gclose(f->pbc_group);
  if (f->electron_group != (hid_t) 0) H5Gclose(f->electron_group);
  if (f->state_group != (hid_t) 0) H5Gclose(f->state_group);
  if (f->basis_group != (hid_t) 0) H5Gclose(f->basis_group);
  if (f->ecp_group != (hid_t) 0) H5Gclose(f->ecp_group);
  if (f->grid_group != (hid_t) 0) H5Gclose(f->grid_group);
  if (f->ao_group != (hid_t) 0) H5Gclose(f->ao_group);
  if (f->ao_1e_int_group != (hid_t) 0) H5Gclose(f->ao_1e_int_group);
  if (f->ao_2e_int_group != (hid_t) 0) H5Gclose(f->ao_2e_int_group);
  if (f->mo_group != (hid_t) 0) H5Gclose(f->mo_group);
  if (f->mo_1e_int_group != (hid_t) 0) H5Gclose(f->mo_1e_int_group);
  if (f->mo_2e_int_group != (hid_t) 0) H5Gclose(f->mo_2e_int_group);
  if (f->determinant_group != (hid_t) 0) H5Gclose(f->determinant_group);
  if (f->csf_group != (hid_t) 0) H5Gclose(f->csf_group);
  if (f->amplitude_group != (hid_t) 0) H5Gclose(f->amplitude_group);
  if (f->rdm_group != (hid_t) 0) H5Gclose(f->rdm_group);
  if (f->jastrow_group != (hid_t) 0) H5Gclose(f->jastrow_group);
  if (f->qmc_group != (hid_t) 0) H5Gclose(f->qmc_group);
  f->metadata_group = 0;
  f->nucleus_group = 0;
  f->cell_group = 0;
  f->pbc_group = 0;
  f->electron_group = 0;
  f->state_group = 0;
  f->basis_group = 0;
  f->ecp_group = 0;
  f->grid_group = 0;
  f->ao_group = 0;
  f->ao_1e_int_group = 0;
  f->ao_2e_int_group = 0;
  f->mo_group = 0;
  f->mo_1e_int_group = 0;
  f->mo_2e_int_group = 0;
  f->determinant_group = 0;
  f->csf_group = 0;
  f->amplitude_group = 0;
  f->rdm_group = 0;
  f->jastrow_group = 0;
  f->qmc_group = 0;

  H5Fclose(f->file_id);
  f->file_id = 0;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_has_metadata_code_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->metadata_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->metadata_group, METADATA_CODE_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_metadata_author_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->metadata_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->metadata_group, METADATA_AUTHOR_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_metadata_unsafe (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->metadata_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->metadata_group, METADATA_UNSAFE_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_nucleus_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->nucleus_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->nucleus_group, NUCLEUS_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_nucleus_repulsion (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->nucleus_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->nucleus_group, NUCLEUS_REPULSION_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_cell_two_pi (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->cell_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->cell_group, CELL_TWO_PI_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_pbc_periodic (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->pbc_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->pbc_group, PBC_PERIODIC_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_pbc_k_point_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->pbc_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->pbc_group, PBC_K_POINT_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_pbc_madelung (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->pbc_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->pbc_group, PBC_MADELUNG_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_electron_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->electron_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->electron_group, ELECTRON_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_electron_up_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->electron_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->electron_group, ELECTRON_UP_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_electron_dn_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->electron_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->electron_group, ELECTRON_DN_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_state_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->state_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->state_group, STATE_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_state_id (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->state_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->state_group, STATE_ID_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_state_energy (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->state_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->state_group, STATE_ENERGY_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_prim_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->basis_group, BASIS_PRIM_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_shell_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->basis_group, BASIS_SHELL_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_nao_grid_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->basis_group, BASIS_NAO_GRID_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_interp_coeff_cnt (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->basis_group, BASIS_INTERP_COEFF_CNT_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_e_cut (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->basis_group, BASIS_E_CUT_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_ecp_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->ecp_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->ecp_group, ECP_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_rad_precision (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->grid_group, GRID_RAD_PRECISION_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->grid_group, GRID_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_max_ang_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->grid_group, GRID_MAX_ANG_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_min_ang_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->grid_group, GRID_MIN_ANG_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_ang_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->grid_group, GRID_ANG_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_rad_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->grid_group, GRID_RAD_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_cartesian (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->ao_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->ao_group, AO_CARTESIAN_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->ao_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->ao_group, AO_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_2e_int_eri_cholesky_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->ao_2e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->ao_2e_int_group, AO_2E_INT_ERI_CHOLESKY_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_2e_int_eri_lr_cholesky_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->ao_2e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->ao_2e_int_group, AO_2E_INT_ERI_LR_CHOLESKY_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->mo_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->mo_group, MO_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_2e_int_eri_cholesky_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->mo_2e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->mo_2e_int_group, MO_2E_INT_ERI_CHOLESKY_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_2e_int_eri_lr_cholesky_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->mo_2e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->mo_2e_int_group, MO_2E_INT_ERI_LR_CHOLESKY_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_determinant_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->determinant_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->determinant_group, DETERMINANT_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_csf_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->csf_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->csf_group, CSF_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e_cholesky_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->rdm_group, RDM_2E_CHOLESKY_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e_upup_cholesky_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->rdm_group, RDM_2E_UPUP_CHOLESKY_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e_dndn_cholesky_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->rdm_group, RDM_2E_DNDN_CHOLESKY_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e_updn_cholesky_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->rdm_group, RDM_2E_UPDN_CHOLESKY_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_jastrow_en_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->jastrow_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->jastrow_group, JASTROW_EN_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_jastrow_ee_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->jastrow_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->jastrow_group, JASTROW_EE_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_jastrow_een_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->jastrow_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->jastrow_group, JASTROW_EEN_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_jastrow_ee_scaling (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->jastrow_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->jastrow_group, JASTROW_EE_SCALING_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_qmc_num (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->qmc_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->qmc_group, QMC_NUM_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_metadata_package_version (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->metadata_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->metadata_group, METADATA_PACKAGE_VERSION_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_metadata_description (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->metadata_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->metadata_group, METADATA_DESCRIPTION_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_nucleus_point_group (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->nucleus_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->nucleus_group, NUCLEUS_POINT_GROUP_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_state_current_label (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->state_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->state_group, STATE_CURRENT_LABEL_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_type (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->basis_group, BASIS_TYPE_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_oscillation_kind (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->basis_group, BASIS_OSCILLATION_KIND_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_interpolator_kind (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->basis_group, BASIS_INTERPOLATOR_KIND_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_description (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->grid_group, GRID_DESCRIPTION_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_type (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->mo_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->mo_group, MO_TYPE_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code
trexio_hdf5_has_jastrow_type (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  if (f->jastrow_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t status = H5Aexists(f->jastrow_group, JASTROW_TYPE_NAME);
  /* H5Aexists returns positive value if attribute exists, 0 if does not, negative if error */
  if (status > 0){
    return TREXIO_SUCCESS;
  } else if (status == 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_FAILURE;
  }

}

trexio_exit_code trexio_hdf5_has_determinant_coefficient(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->determinant_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  const char dset_name[] = "determinant_coefficient";

  htri_t exists = H5Lexists(f->determinant_group, dset_name, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code trexio_hdf5_has_csf_coefficient(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->csf_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  const char dset_name[] = "csf_coefficient";

  htri_t exists = H5Lexists(f->csf_group, dset_name, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }
}

trexio_exit_code
trexio_hdf5_has_nucleus_charge (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->nucleus_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->nucleus_group, NUCLEUS_CHARGE_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_nucleus_coord (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->nucleus_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->nucleus_group, NUCLEUS_COORD_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_cell_a (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->cell_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->cell_group, CELL_A_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_cell_b (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->cell_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->cell_group, CELL_B_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_cell_c (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->cell_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->cell_group, CELL_C_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_cell_g_a (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->cell_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->cell_group, CELL_G_A_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_cell_g_b (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->cell_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->cell_group, CELL_G_B_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_cell_g_c (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->cell_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->cell_group, CELL_G_C_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_pbc_k_point (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->pbc_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->pbc_group, PBC_K_POINT_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_pbc_k_point_weight (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->pbc_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->pbc_group, PBC_K_POINT_WEIGHT_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_nucleus_index (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_NUCLEUS_INDEX_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_shell_ang_mom (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_SHELL_ANG_MOM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_shell_factor (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_SHELL_FACTOR_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_r_power (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_R_POWER_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_nao_grid_start (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_NAO_GRID_START_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_nao_grid_size (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_NAO_GRID_SIZE_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_shell_index (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_SHELL_INDEX_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_exponent (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_EXPONENT_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_exponent_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_EXPONENT_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_coefficient (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_COEFFICIENT_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_coefficient_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_COEFFICIENT_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_oscillation_arg (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_OSCILLATION_ARG_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_prim_factor (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_PRIM_FACTOR_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_nao_grid_radius (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_NAO_GRID_RADIUS_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_nao_grid_phi (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_NAO_GRID_PHI_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_nao_grid_grad (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_NAO_GRID_GRAD_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_nao_grid_lap (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_NAO_GRID_LAP_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_interpolator_phi (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_INTERPOLATOR_PHI_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_interpolator_grad (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_INTERPOLATOR_GRAD_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_basis_interpolator_lap (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->basis_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->basis_group, BASIS_INTERPOLATOR_LAP_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ecp_max_ang_mom_plus_1 (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ecp_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ecp_group, ECP_MAX_ANG_MOM_PLUS_1_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ecp_z_core (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ecp_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ecp_group, ECP_Z_CORE_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ecp_ang_mom (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ecp_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ecp_group, ECP_ANG_MOM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ecp_nucleus_index (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ecp_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ecp_group, ECP_NUCLEUS_INDEX_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ecp_exponent (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ecp_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ecp_group, ECP_EXPONENT_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ecp_coefficient (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ecp_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ecp_group, ECP_COEFFICIENT_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ecp_power (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ecp_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ecp_group, ECP_POWER_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_coord (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->grid_group, GRID_COORD_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_weight (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->grid_group, GRID_WEIGHT_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_ang_coord (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->grid_group, GRID_ANG_COORD_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_ang_weight (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->grid_group, GRID_ANG_WEIGHT_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_rad_coord (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->grid_group, GRID_RAD_COORD_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_grid_rad_weight (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->grid_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->grid_group, GRID_RAD_WEIGHT_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_shell (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_group, AO_SHELL_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_normalization (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_group, AO_NORMALIZATION_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_1e_int_overlap (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_1e_int_group, AO_1E_INT_OVERLAP_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_1e_int_kinetic (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_1e_int_group, AO_1E_INT_KINETIC_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_1e_int_potential_n_e (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_1e_int_group, AO_1E_INT_POTENTIAL_N_E_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_1e_int_ecp (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_1e_int_group, AO_1E_INT_ECP_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_1e_int_core_hamiltonian (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_1e_int_group, AO_1E_INT_CORE_HAMILTONIAN_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_1e_int_overlap_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_1e_int_group, AO_1E_INT_OVERLAP_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_1e_int_kinetic_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_1e_int_group, AO_1E_INT_KINETIC_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_1e_int_potential_n_e_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_1e_int_group, AO_1E_INT_POTENTIAL_N_E_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_1e_int_ecp_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_1e_int_group, AO_1E_INT_ECP_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_1e_int_core_hamiltonian_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_1e_int_group, AO_1E_INT_CORE_HAMILTONIAN_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_coefficient (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_group, MO_COEFFICIENT_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_coefficient_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_group, MO_COEFFICIENT_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_occupation (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_group, MO_OCCUPATION_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_energy (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_group, MO_ENERGY_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_spin (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_group, MO_SPIN_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_k_point (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_group, MO_K_POINT_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_1e_int_overlap (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_1e_int_group, MO_1E_INT_OVERLAP_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_1e_int_kinetic (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_1e_int_group, MO_1E_INT_KINETIC_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_1e_int_potential_n_e (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_1e_int_group, MO_1E_INT_POTENTIAL_N_E_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_1e_int_ecp (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_1e_int_group, MO_1E_INT_ECP_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_1e_int_core_hamiltonian (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_1e_int_group, MO_1E_INT_CORE_HAMILTONIAN_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_1e_int_overlap_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_1e_int_group, MO_1E_INT_OVERLAP_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_1e_int_kinetic_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_1e_int_group, MO_1E_INT_KINETIC_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_1e_int_potential_n_e_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_1e_int_group, MO_1E_INT_POTENTIAL_N_E_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_1e_int_ecp_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_1e_int_group, MO_1E_INT_ECP_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_1e_int_core_hamiltonian_im (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_1e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_1e_int_group, MO_1E_INT_CORE_HAMILTONIAN_IM_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_1e (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_1E_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_1e_up (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_1E_UP_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_1e_dn (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_1E_DN_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_1e_transition (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_1E_TRANSITION_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_jastrow_en (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->jastrow_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->jastrow_group, JASTROW_EN_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_jastrow_ee (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->jastrow_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->jastrow_group, JASTROW_EE_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_jastrow_een (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->jastrow_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->jastrow_group, JASTROW_EEN_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_jastrow_en_nucleus (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->jastrow_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->jastrow_group, JASTROW_EN_NUCLEUS_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_jastrow_een_nucleus (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->jastrow_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->jastrow_group, JASTROW_EEN_NUCLEUS_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_jastrow_en_scaling (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->jastrow_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->jastrow_group, JASTROW_EN_SCALING_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_qmc_point (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->qmc_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->qmc_group, QMC_POINT_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_qmc_psi (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->qmc_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->qmc_group, QMC_PSI_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_qmc_e_loc (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->qmc_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->qmc_group, QMC_E_LOC_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_2e_int_eri (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_2e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_2e_int_group, AO_2E_INT_ERI_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_2e_int_eri_lr (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_2e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_2e_int_group, AO_2E_INT_ERI_LR_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_2e_int_eri_cholesky (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_2e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_2e_int_group, AO_2E_INT_ERI_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_2e_int_eri_lr_cholesky (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->ao_2e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->ao_2e_int_group, AO_2E_INT_ERI_LR_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_2e_int_eri (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_2e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_2e_int_group, MO_2E_INT_ERI_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_2e_int_eri_lr (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_2e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_2e_int_group, MO_2E_INT_ERI_LR_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_2e_int_eri_cholesky (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_2e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_2e_int_group, MO_2E_INT_ERI_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_2e_int_eri_lr_cholesky (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_2e_int_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_2e_int_group, MO_2E_INT_ERI_LR_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_csf_det_coefficient (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->csf_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->csf_group, CSF_DET_COEFFICIENT_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_amplitude_single (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->amplitude_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->amplitude_group, AMPLITUDE_SINGLE_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_amplitude_single_exp (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->amplitude_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->amplitude_group, AMPLITUDE_SINGLE_EXP_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_amplitude_double (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->amplitude_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->amplitude_group, AMPLITUDE_DOUBLE_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_amplitude_double_exp (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->amplitude_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->amplitude_group, AMPLITUDE_DOUBLE_EXP_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_amplitude_triple (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->amplitude_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->amplitude_group, AMPLITUDE_TRIPLE_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_amplitude_triple_exp (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->amplitude_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->amplitude_group, AMPLITUDE_TRIPLE_EXP_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_amplitude_quadruple (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->amplitude_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->amplitude_group, AMPLITUDE_QUADRUPLE_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_amplitude_quadruple_exp (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->amplitude_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->amplitude_group, AMPLITUDE_QUADRUPLE_EXP_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_2E_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e_upup (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_2E_UPUP_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e_dndn (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_2E_DNDN_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e_updn (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_2E_UPDN_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e_transition (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_2E_TRANSITION_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e_cholesky (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_2E_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e_upup_cholesky (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_2E_UPUP_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e_dndn_cholesky (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_2E_DNDN_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm_2e_updn_cholesky (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->rdm_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->rdm_group, RDM_2E_UPDN_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_metadata_code (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->metadata_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->metadata_group, METADATA_CODE_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_metadata_author (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->metadata_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->metadata_group, METADATA_AUTHOR_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_nucleus_label (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->nucleus_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->nucleus_group, NUCLEUS_LABEL_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_state_label (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->state_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->state_group, STATE_LABEL_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_state_file_name (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->state_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->state_group, STATE_FILE_NAME_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_class (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_group, MO_CLASS_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_symmetry (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->mo_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->mo_group, MO_SYMMETRY_NAME, H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }

}

trexio_exit_code
trexio_hdf5_has_metadata (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->metadata_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_nucleus (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->nucleus_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_cell (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->cell_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_pbc (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->pbc_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_electron (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->electron_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_state (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->state_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_basis (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->basis_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_ecp (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->ecp_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_grid (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->grid_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_ao (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->ao_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_1e_int (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->ao_1e_int_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_ao_2e_int (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->ao_2e_int_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_mo (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->mo_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_1e_int (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->mo_1e_int_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_mo_2e_int (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->mo_2e_int_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_determinant (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->determinant_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_csf (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->csf_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_amplitude (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->amplitude_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_rdm (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->rdm_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_jastrow (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->jastrow_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_has_qmc (trexio_t* const file)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  struct H5G_info_t group_info;

  /* H5Gget_info return info about the HDF5 group as a group_info struct */
  herr_t status = H5Gget_info(f->qmc_group, &group_info);
  if (status < 0) return TREXIO_FAILURE;

  /* If nlinks==0 --> the group is empty, i.e. non-existent */
  if (group_info.nlinks == (hsize_t) 0) {
    return TREXIO_HAS_NOT;
  } else {
    return TREXIO_SUCCESS;
  }

}

trexio_exit_code
trexio_hdf5_read_metadata_code_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->metadata_group, METADATA_CODE_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the metadata_code_num attribute of metadata group */
  const hid_t num_id = H5Aopen(f->metadata_group, METADATA_CODE_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_metadata_author_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->metadata_group, METADATA_AUTHOR_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the metadata_author_num attribute of metadata group */
  const hid_t num_id = H5Aopen(f->metadata_group, METADATA_AUTHOR_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_metadata_unsafe (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->metadata_group, METADATA_UNSAFE_NAME) == 0) return TREXIO_FAILURE;

  /* Read the metadata_unsafe attribute of metadata group */
  const hid_t num_id = H5Aopen(f->metadata_group, METADATA_UNSAFE_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_nucleus_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->nucleus_group, NUCLEUS_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the nucleus_num attribute of nucleus group */
  const hid_t num_id = H5Aopen(f->nucleus_group, NUCLEUS_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_nucleus_repulsion (trexio_t* const file, double* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->nucleus_group, NUCLEUS_REPULSION_NAME) == 0) return TREXIO_FAILURE;

  /* Read the nucleus_repulsion attribute of nucleus group */
  const hid_t num_id = H5Aopen(f->nucleus_group, NUCLEUS_REPULSION_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_DOUBLE, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_cell_two_pi (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->cell_group, CELL_TWO_PI_NAME) == 0) return TREXIO_FAILURE;

  /* Read the cell_two_pi attribute of cell group */
  const hid_t num_id = H5Aopen(f->cell_group, CELL_TWO_PI_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_pbc_periodic (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->pbc_group, PBC_PERIODIC_NAME) == 0) return TREXIO_FAILURE;

  /* Read the pbc_periodic attribute of pbc group */
  const hid_t num_id = H5Aopen(f->pbc_group, PBC_PERIODIC_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_pbc_k_point_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->pbc_group, PBC_K_POINT_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the pbc_k_point_num attribute of pbc group */
  const hid_t num_id = H5Aopen(f->pbc_group, PBC_K_POINT_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_pbc_madelung (trexio_t* const file, double* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->pbc_group, PBC_MADELUNG_NAME) == 0) return TREXIO_FAILURE;

  /* Read the pbc_madelung attribute of pbc group */
  const hid_t num_id = H5Aopen(f->pbc_group, PBC_MADELUNG_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_DOUBLE, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_electron_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->electron_group, ELECTRON_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the electron_num attribute of electron group */
  const hid_t num_id = H5Aopen(f->electron_group, ELECTRON_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_electron_up_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->electron_group, ELECTRON_UP_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the electron_up_num attribute of electron group */
  const hid_t num_id = H5Aopen(f->electron_group, ELECTRON_UP_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_electron_dn_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->electron_group, ELECTRON_DN_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the electron_dn_num attribute of electron group */
  const hid_t num_id = H5Aopen(f->electron_group, ELECTRON_DN_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_state_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->state_group, STATE_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the state_num attribute of state group */
  const hid_t num_id = H5Aopen(f->state_group, STATE_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_state_id (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->state_group, STATE_ID_NAME) == 0) return TREXIO_FAILURE;

  /* Read the state_id attribute of state group */
  const hid_t num_id = H5Aopen(f->state_group, STATE_ID_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_state_energy (trexio_t* const file, double* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->state_group, STATE_ENERGY_NAME) == 0) return TREXIO_FAILURE;

  /* Read the state_energy attribute of state group */
  const hid_t num_id = H5Aopen(f->state_group, STATE_ENERGY_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_DOUBLE, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_basis_prim_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->basis_group, BASIS_PRIM_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the basis_prim_num attribute of basis group */
  const hid_t num_id = H5Aopen(f->basis_group, BASIS_PRIM_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_basis_shell_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->basis_group, BASIS_SHELL_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the basis_shell_num attribute of basis group */
  const hid_t num_id = H5Aopen(f->basis_group, BASIS_SHELL_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_basis_nao_grid_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->basis_group, BASIS_NAO_GRID_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the basis_nao_grid_num attribute of basis group */
  const hid_t num_id = H5Aopen(f->basis_group, BASIS_NAO_GRID_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_basis_interp_coeff_cnt (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->basis_group, BASIS_INTERP_COEFF_CNT_NAME) == 0) return TREXIO_FAILURE;

  /* Read the basis_interp_coeff_cnt attribute of basis group */
  const hid_t num_id = H5Aopen(f->basis_group, BASIS_INTERP_COEFF_CNT_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_basis_e_cut (trexio_t* const file, double* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->basis_group, BASIS_E_CUT_NAME) == 0) return TREXIO_FAILURE;

  /* Read the basis_e_cut attribute of basis group */
  const hid_t num_id = H5Aopen(f->basis_group, BASIS_E_CUT_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_DOUBLE, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_ecp_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->ecp_group, ECP_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the ecp_num attribute of ecp group */
  const hid_t num_id = H5Aopen(f->ecp_group, ECP_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_grid_rad_precision (trexio_t* const file, double* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->grid_group, GRID_RAD_PRECISION_NAME) == 0) return TREXIO_FAILURE;

  /* Read the grid_rad_precision attribute of grid group */
  const hid_t num_id = H5Aopen(f->grid_group, GRID_RAD_PRECISION_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_DOUBLE, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_grid_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->grid_group, GRID_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the grid_num attribute of grid group */
  const hid_t num_id = H5Aopen(f->grid_group, GRID_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_grid_max_ang_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->grid_group, GRID_MAX_ANG_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the grid_max_ang_num attribute of grid group */
  const hid_t num_id = H5Aopen(f->grid_group, GRID_MAX_ANG_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_grid_min_ang_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->grid_group, GRID_MIN_ANG_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the grid_min_ang_num attribute of grid group */
  const hid_t num_id = H5Aopen(f->grid_group, GRID_MIN_ANG_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_grid_ang_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->grid_group, GRID_ANG_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the grid_ang_num attribute of grid group */
  const hid_t num_id = H5Aopen(f->grid_group, GRID_ANG_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_grid_rad_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->grid_group, GRID_RAD_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the grid_rad_num attribute of grid group */
  const hid_t num_id = H5Aopen(f->grid_group, GRID_RAD_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_ao_cartesian (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->ao_group, AO_CARTESIAN_NAME) == 0) return TREXIO_FAILURE;

  /* Read the ao_cartesian attribute of ao group */
  const hid_t num_id = H5Aopen(f->ao_group, AO_CARTESIAN_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_ao_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->ao_group, AO_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the ao_num attribute of ao group */
  const hid_t num_id = H5Aopen(f->ao_group, AO_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_ao_2e_int_eri_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->ao_2e_int_group, AO_2E_INT_ERI_CHOLESKY_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the ao_2e_int_eri_cholesky_num attribute of ao_2e_int group */
  const hid_t num_id = H5Aopen(f->ao_2e_int_group, AO_2E_INT_ERI_CHOLESKY_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_ao_2e_int_eri_lr_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->ao_2e_int_group, AO_2E_INT_ERI_LR_CHOLESKY_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the ao_2e_int_eri_lr_cholesky_num attribute of ao_2e_int group */
  const hid_t num_id = H5Aopen(f->ao_2e_int_group, AO_2E_INT_ERI_LR_CHOLESKY_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_mo_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->mo_group, MO_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the mo_num attribute of mo group */
  const hid_t num_id = H5Aopen(f->mo_group, MO_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_mo_2e_int_eri_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->mo_2e_int_group, MO_2E_INT_ERI_CHOLESKY_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the mo_2e_int_eri_cholesky_num attribute of mo_2e_int group */
  const hid_t num_id = H5Aopen(f->mo_2e_int_group, MO_2E_INT_ERI_CHOLESKY_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_mo_2e_int_eri_lr_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->mo_2e_int_group, MO_2E_INT_ERI_LR_CHOLESKY_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the mo_2e_int_eri_lr_cholesky_num attribute of mo_2e_int group */
  const hid_t num_id = H5Aopen(f->mo_2e_int_group, MO_2E_INT_ERI_LR_CHOLESKY_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_determinant_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->determinant_group, DETERMINANT_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the determinant_num attribute of determinant group */
  const hid_t num_id = H5Aopen(f->determinant_group, DETERMINANT_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_csf_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->csf_group, CSF_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the csf_num attribute of csf group */
  const hid_t num_id = H5Aopen(f->csf_group, CSF_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_rdm_2e_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->rdm_group, RDM_2E_CHOLESKY_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the rdm_2e_cholesky_num attribute of rdm group */
  const hid_t num_id = H5Aopen(f->rdm_group, RDM_2E_CHOLESKY_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_rdm_2e_upup_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->rdm_group, RDM_2E_UPUP_CHOLESKY_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the rdm_2e_upup_cholesky_num attribute of rdm group */
  const hid_t num_id = H5Aopen(f->rdm_group, RDM_2E_UPUP_CHOLESKY_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_rdm_2e_dndn_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->rdm_group, RDM_2E_DNDN_CHOLESKY_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the rdm_2e_dndn_cholesky_num attribute of rdm group */
  const hid_t num_id = H5Aopen(f->rdm_group, RDM_2E_DNDN_CHOLESKY_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_rdm_2e_updn_cholesky_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->rdm_group, RDM_2E_UPDN_CHOLESKY_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the rdm_2e_updn_cholesky_num attribute of rdm group */
  const hid_t num_id = H5Aopen(f->rdm_group, RDM_2E_UPDN_CHOLESKY_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_jastrow_en_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->jastrow_group, JASTROW_EN_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the jastrow_en_num attribute of jastrow group */
  const hid_t num_id = H5Aopen(f->jastrow_group, JASTROW_EN_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_jastrow_ee_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->jastrow_group, JASTROW_EE_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the jastrow_ee_num attribute of jastrow group */
  const hid_t num_id = H5Aopen(f->jastrow_group, JASTROW_EE_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_jastrow_een_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->jastrow_group, JASTROW_EEN_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the jastrow_een_num attribute of jastrow group */
  const hid_t num_id = H5Aopen(f->jastrow_group, JASTROW_EEN_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_jastrow_ee_scaling (trexio_t* const file, double* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->jastrow_group, JASTROW_EE_SCALING_NAME) == 0) return TREXIO_FAILURE;

  /* Read the jastrow_ee_scaling attribute of jastrow group */
  const hid_t num_id = H5Aopen(f->jastrow_group, JASTROW_EE_SCALING_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_DOUBLE, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_qmc_num (trexio_t* const file, int64_t* const num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->qmc_group, QMC_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the qmc_num attribute of qmc group */
  const hid_t num_id = H5Aopen(f->qmc_group, QMC_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  const herr_t status = H5Aread(num_id, H5T_NATIVE_INT64, num);

  H5Aclose(num_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_metadata_package_version (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_3;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the string attribute is missing in the file */
  if (H5Aexists(f->metadata_group, METADATA_PACKAGE_VERSION_NAME) == 0) return TREXIO_HAS_NOT;

  /* Read the metadata_package_version attribute of metadata group */
  const hid_t str_id = H5Aopen(f->metadata_group, METADATA_PACKAGE_VERSION_NAME, H5P_DEFAULT);
  if (str_id <= 0) return TREXIO_INVALID_ID;

  const hid_t ftype_id = H5Aget_type(str_id);
  if (ftype_id <= 0) return TREXIO_INVALID_ID;
  uint64_t sdim = H5Tget_size(ftype_id);
  sdim++;                         /* Make room for null terminator */

  const hid_t mem_id = H5Tcopy(H5T_C_S1);
  if (mem_id <= 0) return TREXIO_INVALID_ID;

  herr_t status;
  status = (max_str_len+1) > sdim ? H5Tset_size(mem_id, sdim) : H5Tset_size(mem_id, max_str_len+1) ;
  if (status < 0) return TREXIO_FAILURE;

  status = H5Aread(str_id, mem_id, str);
  if (status < 0) return TREXIO_FAILURE;

  H5Aclose(str_id);
  H5Tclose(mem_id);
  H5Tclose(ftype_id);

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_metadata_description (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_3;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the string attribute is missing in the file */
  if (H5Aexists(f->metadata_group, METADATA_DESCRIPTION_NAME) == 0) return TREXIO_HAS_NOT;

  /* Read the metadata_description attribute of metadata group */
  const hid_t str_id = H5Aopen(f->metadata_group, METADATA_DESCRIPTION_NAME, H5P_DEFAULT);
  if (str_id <= 0) return TREXIO_INVALID_ID;

  const hid_t ftype_id = H5Aget_type(str_id);
  if (ftype_id <= 0) return TREXIO_INVALID_ID;
  uint64_t sdim = H5Tget_size(ftype_id);
  sdim++;                         /* Make room for null terminator */

  const hid_t mem_id = H5Tcopy(H5T_C_S1);
  if (mem_id <= 0) return TREXIO_INVALID_ID;

  herr_t status;
  status = (max_str_len+1) > sdim ? H5Tset_size(mem_id, sdim) : H5Tset_size(mem_id, max_str_len+1) ;
  if (status < 0) return TREXIO_FAILURE;

  status = H5Aread(str_id, mem_id, str);
  if (status < 0) return TREXIO_FAILURE;

  H5Aclose(str_id);
  H5Tclose(mem_id);
  H5Tclose(ftype_id);

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_nucleus_point_group (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_3;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the string attribute is missing in the file */
  if (H5Aexists(f->nucleus_group, NUCLEUS_POINT_GROUP_NAME) == 0) return TREXIO_HAS_NOT;

  /* Read the nucleus_point_group attribute of nucleus group */
  const hid_t str_id = H5Aopen(f->nucleus_group, NUCLEUS_POINT_GROUP_NAME, H5P_DEFAULT);
  if (str_id <= 0) return TREXIO_INVALID_ID;

  const hid_t ftype_id = H5Aget_type(str_id);
  if (ftype_id <= 0) return TREXIO_INVALID_ID;
  uint64_t sdim = H5Tget_size(ftype_id);
  sdim++;                         /* Make room for null terminator */

  const hid_t mem_id = H5Tcopy(H5T_C_S1);
  if (mem_id <= 0) return TREXIO_INVALID_ID;

  herr_t status;
  status = (max_str_len+1) > sdim ? H5Tset_size(mem_id, sdim) : H5Tset_size(mem_id, max_str_len+1) ;
  if (status < 0) return TREXIO_FAILURE;

  status = H5Aread(str_id, mem_id, str);
  if (status < 0) return TREXIO_FAILURE;

  H5Aclose(str_id);
  H5Tclose(mem_id);
  H5Tclose(ftype_id);

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_state_current_label (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_3;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the string attribute is missing in the file */
  if (H5Aexists(f->state_group, STATE_CURRENT_LABEL_NAME) == 0) return TREXIO_HAS_NOT;

  /* Read the state_current_label attribute of state group */
  const hid_t str_id = H5Aopen(f->state_group, STATE_CURRENT_LABEL_NAME, H5P_DEFAULT);
  if (str_id <= 0) return TREXIO_INVALID_ID;

  const hid_t ftype_id = H5Aget_type(str_id);
  if (ftype_id <= 0) return TREXIO_INVALID_ID;
  uint64_t sdim = H5Tget_size(ftype_id);
  sdim++;                         /* Make room for null terminator */

  const hid_t mem_id = H5Tcopy(H5T_C_S1);
  if (mem_id <= 0) return TREXIO_INVALID_ID;

  herr_t status;
  status = (max_str_len+1) > sdim ? H5Tset_size(mem_id, sdim) : H5Tset_size(mem_id, max_str_len+1) ;
  if (status < 0) return TREXIO_FAILURE;

  status = H5Aread(str_id, mem_id, str);
  if (status < 0) return TREXIO_FAILURE;

  H5Aclose(str_id);
  H5Tclose(mem_id);
  H5Tclose(ftype_id);

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_basis_type (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_3;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the string attribute is missing in the file */
  if (H5Aexists(f->basis_group, BASIS_TYPE_NAME) == 0) return TREXIO_HAS_NOT;

  /* Read the basis_type attribute of basis group */
  const hid_t str_id = H5Aopen(f->basis_group, BASIS_TYPE_NAME, H5P_DEFAULT);
  if (str_id <= 0) return TREXIO_INVALID_ID;

  const hid_t ftype_id = H5Aget_type(str_id);
  if (ftype_id <= 0) return TREXIO_INVALID_ID;
  uint64_t sdim = H5Tget_size(ftype_id);
  sdim++;                         /* Make room for null terminator */

  const hid_t mem_id = H5Tcopy(H5T_C_S1);
  if (mem_id <= 0) return TREXIO_INVALID_ID;

  herr_t status;
  status = (max_str_len+1) > sdim ? H5Tset_size(mem_id, sdim) : H5Tset_size(mem_id, max_str_len+1) ;
  if (status < 0) return TREXIO_FAILURE;

  status = H5Aread(str_id, mem_id, str);
  if (status < 0) return TREXIO_FAILURE;

  H5Aclose(str_id);
  H5Tclose(mem_id);
  H5Tclose(ftype_id);

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_basis_oscillation_kind (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_3;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the string attribute is missing in the file */
  if (H5Aexists(f->basis_group, BASIS_OSCILLATION_KIND_NAME) == 0) return TREXIO_HAS_NOT;

  /* Read the basis_oscillation_kind attribute of basis group */
  const hid_t str_id = H5Aopen(f->basis_group, BASIS_OSCILLATION_KIND_NAME, H5P_DEFAULT);
  if (str_id <= 0) return TREXIO_INVALID_ID;

  const hid_t ftype_id = H5Aget_type(str_id);
  if (ftype_id <= 0) return TREXIO_INVALID_ID;
  uint64_t sdim = H5Tget_size(ftype_id);
  sdim++;                         /* Make room for null terminator */

  const hid_t mem_id = H5Tcopy(H5T_C_S1);
  if (mem_id <= 0) return TREXIO_INVALID_ID;

  herr_t status;
  status = (max_str_len+1) > sdim ? H5Tset_size(mem_id, sdim) : H5Tset_size(mem_id, max_str_len+1) ;
  if (status < 0) return TREXIO_FAILURE;

  status = H5Aread(str_id, mem_id, str);
  if (status < 0) return TREXIO_FAILURE;

  H5Aclose(str_id);
  H5Tclose(mem_id);
  H5Tclose(ftype_id);

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_basis_interpolator_kind (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_3;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the string attribute is missing in the file */
  if (H5Aexists(f->basis_group, BASIS_INTERPOLATOR_KIND_NAME) == 0) return TREXIO_HAS_NOT;

  /* Read the basis_interpolator_kind attribute of basis group */
  const hid_t str_id = H5Aopen(f->basis_group, BASIS_INTERPOLATOR_KIND_NAME, H5P_DEFAULT);
  if (str_id <= 0) return TREXIO_INVALID_ID;

  const hid_t ftype_id = H5Aget_type(str_id);
  if (ftype_id <= 0) return TREXIO_INVALID_ID;
  uint64_t sdim = H5Tget_size(ftype_id);
  sdim++;                         /* Make room for null terminator */

  const hid_t mem_id = H5Tcopy(H5T_C_S1);
  if (mem_id <= 0) return TREXIO_INVALID_ID;

  herr_t status;
  status = (max_str_len+1) > sdim ? H5Tset_size(mem_id, sdim) : H5Tset_size(mem_id, max_str_len+1) ;
  if (status < 0) return TREXIO_FAILURE;

  status = H5Aread(str_id, mem_id, str);
  if (status < 0) return TREXIO_FAILURE;

  H5Aclose(str_id);
  H5Tclose(mem_id);
  H5Tclose(ftype_id);

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_grid_description (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_3;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the string attribute is missing in the file */
  if (H5Aexists(f->grid_group, GRID_DESCRIPTION_NAME) == 0) return TREXIO_HAS_NOT;

  /* Read the grid_description attribute of grid group */
  const hid_t str_id = H5Aopen(f->grid_group, GRID_DESCRIPTION_NAME, H5P_DEFAULT);
  if (str_id <= 0) return TREXIO_INVALID_ID;

  const hid_t ftype_id = H5Aget_type(str_id);
  if (ftype_id <= 0) return TREXIO_INVALID_ID;
  uint64_t sdim = H5Tget_size(ftype_id);
  sdim++;                         /* Make room for null terminator */

  const hid_t mem_id = H5Tcopy(H5T_C_S1);
  if (mem_id <= 0) return TREXIO_INVALID_ID;

  herr_t status;
  status = (max_str_len+1) > sdim ? H5Tset_size(mem_id, sdim) : H5Tset_size(mem_id, max_str_len+1) ;
  if (status < 0) return TREXIO_FAILURE;

  status = H5Aread(str_id, mem_id, str);
  if (status < 0) return TREXIO_FAILURE;

  H5Aclose(str_id);
  H5Tclose(mem_id);
  H5Tclose(ftype_id);

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_mo_type (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_3;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the string attribute is missing in the file */
  if (H5Aexists(f->mo_group, MO_TYPE_NAME) == 0) return TREXIO_HAS_NOT;

  /* Read the mo_type attribute of mo group */
  const hid_t str_id = H5Aopen(f->mo_group, MO_TYPE_NAME, H5P_DEFAULT);
  if (str_id <= 0) return TREXIO_INVALID_ID;

  const hid_t ftype_id = H5Aget_type(str_id);
  if (ftype_id <= 0) return TREXIO_INVALID_ID;
  uint64_t sdim = H5Tget_size(ftype_id);
  sdim++;                         /* Make room for null terminator */

  const hid_t mem_id = H5Tcopy(H5T_C_S1);
  if (mem_id <= 0) return TREXIO_INVALID_ID;

  herr_t status;
  status = (max_str_len+1) > sdim ? H5Tset_size(mem_id, sdim) : H5Tset_size(mem_id, max_str_len+1) ;
  if (status < 0) return TREXIO_FAILURE;

  status = H5Aread(str_id, mem_id, str);
  if (status < 0) return TREXIO_FAILURE;

  H5Aclose(str_id);
  H5Tclose(mem_id);
  H5Tclose(ftype_id);

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_read_jastrow_type (trexio_t* const file, char* const str, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_3;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;
  /* Quit if the string attribute is missing in the file */
  if (H5Aexists(f->jastrow_group, JASTROW_TYPE_NAME) == 0) return TREXIO_HAS_NOT;

  /* Read the jastrow_type attribute of jastrow group */
  const hid_t str_id = H5Aopen(f->jastrow_group, JASTROW_TYPE_NAME, H5P_DEFAULT);
  if (str_id <= 0) return TREXIO_INVALID_ID;

  const hid_t ftype_id = H5Aget_type(str_id);
  if (ftype_id <= 0) return TREXIO_INVALID_ID;
  uint64_t sdim = H5Tget_size(ftype_id);
  sdim++;                         /* Make room for null terminator */

  const hid_t mem_id = H5Tcopy(H5T_C_S1);
  if (mem_id <= 0) return TREXIO_INVALID_ID;

  herr_t status;
  status = (max_str_len+1) > sdim ? H5Tset_size(mem_id, sdim) : H5Tset_size(mem_id, max_str_len+1) ;
  if (status < 0) return TREXIO_FAILURE;

  status = H5Aread(str_id, mem_id, str);
  if (status < 0) return TREXIO_FAILURE;

  H5Aclose(str_id);
  H5Tclose(mem_id);
  H5Tclose(ftype_id);

  return TREXIO_SUCCESS;

}

trexio_exit_code trexio_hdf5_read_determinant_coefficient(trexio_t* const file,
                                               const int64_t offset_file,
                                               const uint32_t rank,
                                               const uint64_t* dims,
                                               int64_t* const eof_read_size,
                                               double* const dset)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (rank != 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (dset == NULL) return TREXIO_INVALID_ARG_6;

  const char dset_name[] = "determinant_coefficient";

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hsize_t offset[1] = {(hsize_t) offset_file};
  hsize_t count[1]  = {(hsize_t) dims[0]};

  /* Attempt to read values (if EOF -> eof_read_size is modified with the number of elements read and return code is TREXIO_END)
     0 argument below is requires to skip internal treatment specific to sparse indices (i.e. their de-compression).*/
  return trexio_hdf5_open_read_dset_sparse(f->determinant_group, dset_name, 1, offset, count, eof_read_size, 0, dset);
}

trexio_exit_code trexio_hdf5_read_csf_coefficient(trexio_t* const file,
                                               const int64_t offset_file,
                                               const uint32_t rank,
                                               const uint64_t* dims,
                                               int64_t* const eof_read_size,
                                               double* const dset)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (rank != 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (dset == NULL) return TREXIO_INVALID_ARG_6;

  const char dset_name[] = "csf_coefficient";

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hsize_t offset[1] = {(hsize_t) offset_file};
  hsize_t count[1]  = {(hsize_t) dims[0]};

  /* Attempt to read values (if EOF -> eof_read_size is modified with the number of elements read and return code is TREXIO_END)
     0 argument below is requires to skip internal treatment specific to sparse indices (i.e. their de-compression).*/
  return trexio_hdf5_open_read_dset_sparse(f->csf_group, dset_name, 1, offset, count, eof_read_size, 0, dset);
}

trexio_exit_code
trexio_hdf5_read_nucleus_charge (trexio_t* const file, double* const nucleus_charge, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_charge == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->nucleus_group, NUCLEUS_CHARGE_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          nucleus_charge);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_nucleus_coord (trexio_t* const file, double* const nucleus_coord, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_coord == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->nucleus_group, NUCLEUS_COORD_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          nucleus_coord);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_cell_a (trexio_t* const file, double* const cell_a, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_a == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->cell_group, CELL_A_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          cell_a);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_cell_b (trexio_t* const file, double* const cell_b, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_b == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->cell_group, CELL_B_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          cell_b);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_cell_c (trexio_t* const file, double* const cell_c, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_c == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->cell_group, CELL_C_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          cell_c);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_cell_g_a (trexio_t* const file, double* const cell_g_a, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_g_a == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->cell_group, CELL_G_A_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          cell_g_a);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_cell_g_b (trexio_t* const file, double* const cell_g_b, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_g_b == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->cell_group, CELL_G_B_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          cell_g_b);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_cell_g_c (trexio_t* const file, double* const cell_g_c, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_g_c == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->cell_group, CELL_G_C_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          cell_g_c);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_pbc_k_point (trexio_t* const file, double* const pbc_k_point, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (pbc_k_point == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->pbc_group, PBC_K_POINT_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          pbc_k_point);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_pbc_k_point_weight (trexio_t* const file, double* const pbc_k_point_weight, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (pbc_k_point_weight == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->pbc_group, PBC_K_POINT_WEIGHT_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          pbc_k_point_weight);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_nucleus_index (trexio_t* const file, int64_t* const basis_nucleus_index, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nucleus_index == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_NUCLEUS_INDEX_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_nucleus_index);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_shell_ang_mom (trexio_t* const file, int64_t* const basis_shell_ang_mom, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_shell_ang_mom == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_SHELL_ANG_MOM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_shell_ang_mom);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_shell_factor (trexio_t* const file, double* const basis_shell_factor, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_shell_factor == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_SHELL_FACTOR_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_shell_factor);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_r_power (trexio_t* const file, int64_t* const basis_r_power, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_r_power == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_R_POWER_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_r_power);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_nao_grid_start (trexio_t* const file, int64_t* const basis_nao_grid_start, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_start == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_NAO_GRID_START_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_nao_grid_start);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_nao_grid_size (trexio_t* const file, int64_t* const basis_nao_grid_size, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_size == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_NAO_GRID_SIZE_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_nao_grid_size);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_shell_index (trexio_t* const file, int64_t* const basis_shell_index, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_shell_index == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_SHELL_INDEX_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_shell_index);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_exponent (trexio_t* const file, double* const basis_exponent, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_exponent == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_EXPONENT_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_exponent);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_exponent_im (trexio_t* const file, double* const basis_exponent_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_exponent_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_EXPONENT_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_exponent_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_coefficient (trexio_t* const file, double* const basis_coefficient, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_coefficient == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_COEFFICIENT_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_coefficient);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_coefficient_im (trexio_t* const file, double* const basis_coefficient_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_coefficient_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_COEFFICIENT_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_coefficient_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_oscillation_arg (trexio_t* const file, double* const basis_oscillation_arg, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_oscillation_arg == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_OSCILLATION_ARG_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_oscillation_arg);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_prim_factor (trexio_t* const file, double* const basis_prim_factor, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_prim_factor == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_PRIM_FACTOR_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_prim_factor);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_nao_grid_radius (trexio_t* const file, double* const basis_nao_grid_radius, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_radius == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_NAO_GRID_RADIUS_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_nao_grid_radius);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_nao_grid_phi (trexio_t* const file, double* const basis_nao_grid_phi, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_phi == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_NAO_GRID_PHI_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_nao_grid_phi);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_nao_grid_grad (trexio_t* const file, double* const basis_nao_grid_grad, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_grad == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_NAO_GRID_GRAD_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_nao_grid_grad);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_nao_grid_lap (trexio_t* const file, double* const basis_nao_grid_lap, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_lap == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_NAO_GRID_LAP_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_nao_grid_lap);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_interpolator_phi (trexio_t* const file, double* const basis_interpolator_phi, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_interpolator_phi == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_INTERPOLATOR_PHI_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_interpolator_phi);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_interpolator_grad (trexio_t* const file, double* const basis_interpolator_grad, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_interpolator_grad == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_INTERPOLATOR_GRAD_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_interpolator_grad);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_basis_interpolator_lap (trexio_t* const file, double* const basis_interpolator_lap, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_interpolator_lap == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->basis_group, BASIS_INTERPOLATOR_LAP_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          basis_interpolator_lap);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ecp_max_ang_mom_plus_1 (trexio_t* const file, int64_t* const ecp_max_ang_mom_plus_1, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_max_ang_mom_plus_1 == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_MAX_ANG_MOM_PLUS_1_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ecp_max_ang_mom_plus_1);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ecp_z_core (trexio_t* const file, int64_t* const ecp_z_core, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_z_core == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_Z_CORE_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ecp_z_core);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ecp_ang_mom (trexio_t* const file, int64_t* const ecp_ang_mom, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_ang_mom == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_ANG_MOM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ecp_ang_mom);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ecp_nucleus_index (trexio_t* const file, int64_t* const ecp_nucleus_index, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_nucleus_index == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_NUCLEUS_INDEX_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ecp_nucleus_index);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ecp_exponent (trexio_t* const file, double* const ecp_exponent, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_exponent == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_EXPONENT_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ecp_exponent);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ecp_coefficient (trexio_t* const file, double* const ecp_coefficient, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_coefficient == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_COEFFICIENT_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ecp_coefficient);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ecp_power (trexio_t* const file, int64_t* const ecp_power, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_power == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_POWER_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ecp_power);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_grid_coord (trexio_t* const file, double* const grid_coord, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_coord == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->grid_group, GRID_COORD_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          grid_coord);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_grid_weight (trexio_t* const file, double* const grid_weight, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_weight == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->grid_group, GRID_WEIGHT_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          grid_weight);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_grid_ang_coord (trexio_t* const file, double* const grid_ang_coord, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_ang_coord == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->grid_group, GRID_ANG_COORD_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          grid_ang_coord);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_grid_ang_weight (trexio_t* const file, double* const grid_ang_weight, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_ang_weight == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->grid_group, GRID_ANG_WEIGHT_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          grid_ang_weight);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_grid_rad_coord (trexio_t* const file, double* const grid_rad_coord, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_rad_coord == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->grid_group, GRID_RAD_COORD_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          grid_rad_coord);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_grid_rad_weight (trexio_t* const file, double* const grid_rad_weight, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_rad_weight == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->grid_group, GRID_RAD_WEIGHT_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          grid_rad_weight);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_shell (trexio_t* const file, int64_t* const ao_shell, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_shell == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ao_group, AO_SHELL_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ao_shell);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_normalization (trexio_t* const file, double* const ao_normalization, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_normalization == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ao_group, AO_NORMALIZATION_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ao_normalization);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_1e_int_overlap (trexio_t* const file, double* const ao_1e_int_overlap, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_overlap == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ao_1e_int_group, AO_1E_INT_OVERLAP_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ao_1e_int_overlap);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_1e_int_kinetic (trexio_t* const file, double* const ao_1e_int_kinetic, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_kinetic == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ao_1e_int_group, AO_1E_INT_KINETIC_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ao_1e_int_kinetic);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_1e_int_potential_n_e (trexio_t* const file, double* const ao_1e_int_potential_n_e, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_potential_n_e == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ao_1e_int_group, AO_1E_INT_POTENTIAL_N_E_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ao_1e_int_potential_n_e);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_1e_int_ecp (trexio_t* const file, double* const ao_1e_int_ecp, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_ecp == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ao_1e_int_group, AO_1E_INT_ECP_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ao_1e_int_ecp);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_1e_int_core_hamiltonian (trexio_t* const file, double* const ao_1e_int_core_hamiltonian, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_core_hamiltonian == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ao_1e_int_group, AO_1E_INT_CORE_HAMILTONIAN_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ao_1e_int_core_hamiltonian);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_1e_int_overlap_im (trexio_t* const file, double* const ao_1e_int_overlap_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_overlap_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ao_1e_int_group, AO_1E_INT_OVERLAP_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ao_1e_int_overlap_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_1e_int_kinetic_im (trexio_t* const file, double* const ao_1e_int_kinetic_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_kinetic_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ao_1e_int_group, AO_1E_INT_KINETIC_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ao_1e_int_kinetic_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_1e_int_potential_n_e_im (trexio_t* const file, double* const ao_1e_int_potential_n_e_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_potential_n_e_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ao_1e_int_group, AO_1E_INT_POTENTIAL_N_E_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ao_1e_int_potential_n_e_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_1e_int_ecp_im (trexio_t* const file, double* const ao_1e_int_ecp_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_ecp_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ao_1e_int_group, AO_1E_INT_ECP_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ao_1e_int_ecp_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_1e_int_core_hamiltonian_im (trexio_t* const file, double* const ao_1e_int_core_hamiltonian_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_core_hamiltonian_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->ao_1e_int_group, AO_1E_INT_CORE_HAMILTONIAN_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          ao_1e_int_core_hamiltonian_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_coefficient (trexio_t* const file, double* const mo_coefficient, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_coefficient == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_group, MO_COEFFICIENT_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_coefficient);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_coefficient_im (trexio_t* const file, double* const mo_coefficient_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_coefficient_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_group, MO_COEFFICIENT_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_coefficient_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_occupation (trexio_t* const file, double* const mo_occupation, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_occupation == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_group, MO_OCCUPATION_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_occupation);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_energy (trexio_t* const file, double* const mo_energy, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_energy == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_group, MO_ENERGY_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_energy);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_spin (trexio_t* const file, int64_t* const mo_spin, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_spin == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_group, MO_SPIN_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_spin);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_k_point (trexio_t* const file, int64_t* const mo_k_point, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_k_point == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_group, MO_K_POINT_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_k_point);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_1e_int_overlap (trexio_t* const file, double* const mo_1e_int_overlap, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_overlap == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_1e_int_group, MO_1E_INT_OVERLAP_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_1e_int_overlap);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_1e_int_kinetic (trexio_t* const file, double* const mo_1e_int_kinetic, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_kinetic == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_1e_int_group, MO_1E_INT_KINETIC_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_1e_int_kinetic);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_1e_int_potential_n_e (trexio_t* const file, double* const mo_1e_int_potential_n_e, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_potential_n_e == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_1e_int_group, MO_1E_INT_POTENTIAL_N_E_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_1e_int_potential_n_e);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_1e_int_ecp (trexio_t* const file, double* const mo_1e_int_ecp, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_ecp == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_1e_int_group, MO_1E_INT_ECP_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_1e_int_ecp);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_1e_int_core_hamiltonian (trexio_t* const file, double* const mo_1e_int_core_hamiltonian, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_core_hamiltonian == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_1e_int_group, MO_1E_INT_CORE_HAMILTONIAN_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_1e_int_core_hamiltonian);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_1e_int_overlap_im (trexio_t* const file, double* const mo_1e_int_overlap_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_overlap_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_1e_int_group, MO_1E_INT_OVERLAP_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_1e_int_overlap_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_1e_int_kinetic_im (trexio_t* const file, double* const mo_1e_int_kinetic_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_kinetic_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_1e_int_group, MO_1E_INT_KINETIC_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_1e_int_kinetic_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_1e_int_potential_n_e_im (trexio_t* const file, double* const mo_1e_int_potential_n_e_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_potential_n_e_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_1e_int_group, MO_1E_INT_POTENTIAL_N_E_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_1e_int_potential_n_e_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_1e_int_ecp_im (trexio_t* const file, double* const mo_1e_int_ecp_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_ecp_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_1e_int_group, MO_1E_INT_ECP_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_1e_int_ecp_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_1e_int_core_hamiltonian_im (trexio_t* const file, double* const mo_1e_int_core_hamiltonian_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_core_hamiltonian_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_1e_int_group, MO_1E_INT_CORE_HAMILTONIAN_IM_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          mo_1e_int_core_hamiltonian_im);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_1e (trexio_t* const file, double* const rdm_1e, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (rdm_1e == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->rdm_group, RDM_1E_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          rdm_1e);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_1e_up (trexio_t* const file, double* const rdm_1e_up, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (rdm_1e_up == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->rdm_group, RDM_1E_UP_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          rdm_1e_up);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_1e_dn (trexio_t* const file, double* const rdm_1e_dn, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (rdm_1e_dn == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->rdm_group, RDM_1E_DN_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          rdm_1e_dn);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_1e_transition (trexio_t* const file, double* const rdm_1e_transition, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (rdm_1e_transition == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->rdm_group, RDM_1E_TRANSITION_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          rdm_1e_transition);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_jastrow_en (trexio_t* const file, double* const jastrow_en, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_en == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->jastrow_group, JASTROW_EN_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          jastrow_en);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_jastrow_ee (trexio_t* const file, double* const jastrow_ee, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_ee == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->jastrow_group, JASTROW_EE_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          jastrow_ee);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_jastrow_een (trexio_t* const file, double* const jastrow_een, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_een == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->jastrow_group, JASTROW_EEN_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          jastrow_een);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_jastrow_en_nucleus (trexio_t* const file, int64_t* const jastrow_en_nucleus, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_en_nucleus == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->jastrow_group, JASTROW_EN_NUCLEUS_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          jastrow_en_nucleus);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_jastrow_een_nucleus (trexio_t* const file, int64_t* const jastrow_een_nucleus, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_een_nucleus == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->jastrow_group, JASTROW_EEN_NUCLEUS_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_INT64,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          jastrow_een_nucleus);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_jastrow_en_scaling (trexio_t* const file, double* const jastrow_en_scaling, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_en_scaling == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->jastrow_group, JASTROW_EN_SCALING_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          jastrow_en_scaling);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_qmc_point (trexio_t* const file, double* const qmc_point, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (qmc_point == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->qmc_group, QMC_POINT_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          qmc_point);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_qmc_psi (trexio_t* const file, double* const qmc_psi, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (qmc_psi == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->qmc_group, QMC_PSI_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          qmc_psi);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_qmc_e_loc (trexio_t* const file, double* const qmc_e_loc, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (qmc_e_loc == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->qmc_group, QMC_E_LOC_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) return TREXIO_FAILURE;

  // get the dataspace of the dataset
  hid_t dspace_id = H5Dget_space(dset_id);
  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(dspace_id, ddims, NULL);
  // check that dimensions are consistent
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Sclose(dspace_id);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ARG_3;
  }

  for (uint32_t i=0; i<rank; ++i){
    if (ddims[i] != dims[i]) {
      FREE(ddims);
      H5Sclose(dspace_id);
      H5Dclose(dset_id);
      return TREXIO_INVALID_ARG_4;
    }
  }

  FREE(ddims);

  /* Read dataset */
  herr_t status = H5Dread(dset_id,
                          H5T_NATIVE_DOUBLE,
                          H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                          qmc_e_loc);

  H5Sclose(dspace_id);
  H5Dclose(dset_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_2e_int_eri (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AO_2E_INT_ERI_NAME "_indices", 256);
  strncpy(dset_value_name, AO_2E_INT_ERI_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
  hsize_t count_i[1] = {(hsize_t) size * 4};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->ao_2e_int_group, dset_index_name, 4, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->ao_2e_int_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_ao_2e_int_eri_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->ao_2e_int_group, AO_2E_INT_ERI_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_2e_int_eri_lr (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AO_2E_INT_ERI_LR_NAME "_indices", 256);
  strncpy(dset_value_name, AO_2E_INT_ERI_LR_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
  hsize_t count_i[1] = {(hsize_t) size * 4};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->ao_2e_int_group, dset_index_name, 4, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->ao_2e_int_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_ao_2e_int_eri_lr_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->ao_2e_int_group, AO_2E_INT_ERI_LR_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_2e_int_eri_cholesky (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AO_2E_INT_ERI_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, AO_2E_INT_ERI_CHOLESKY_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
  hsize_t count_i[1] = {(hsize_t) size * 3};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->ao_2e_int_group, dset_index_name, 3, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->ao_2e_int_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_ao_2e_int_eri_cholesky_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->ao_2e_int_group, AO_2E_INT_ERI_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_ao_2e_int_eri_lr_cholesky (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AO_2E_INT_ERI_LR_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, AO_2E_INT_ERI_LR_CHOLESKY_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
  hsize_t count_i[1] = {(hsize_t) size * 3};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->ao_2e_int_group, dset_index_name, 3, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->ao_2e_int_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_ao_2e_int_eri_lr_cholesky_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->ao_2e_int_group, AO_2E_INT_ERI_LR_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_2e_int_eri (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, MO_2E_INT_ERI_NAME "_indices", 256);
  strncpy(dset_value_name, MO_2E_INT_ERI_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
  hsize_t count_i[1] = {(hsize_t) size * 4};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->mo_2e_int_group, dset_index_name, 4, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->mo_2e_int_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_mo_2e_int_eri_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->mo_2e_int_group, MO_2E_INT_ERI_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_2e_int_eri_lr (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, MO_2E_INT_ERI_LR_NAME "_indices", 256);
  strncpy(dset_value_name, MO_2E_INT_ERI_LR_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
  hsize_t count_i[1] = {(hsize_t) size * 4};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->mo_2e_int_group, dset_index_name, 4, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->mo_2e_int_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_mo_2e_int_eri_lr_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->mo_2e_int_group, MO_2E_INT_ERI_LR_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_2e_int_eri_cholesky (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, MO_2E_INT_ERI_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, MO_2E_INT_ERI_CHOLESKY_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
  hsize_t count_i[1] = {(hsize_t) size * 3};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->mo_2e_int_group, dset_index_name, 3, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->mo_2e_int_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_mo_2e_int_eri_cholesky_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->mo_2e_int_group, MO_2E_INT_ERI_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_2e_int_eri_lr_cholesky (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, MO_2E_INT_ERI_LR_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, MO_2E_INT_ERI_LR_CHOLESKY_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
  hsize_t count_i[1] = {(hsize_t) size * 3};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->mo_2e_int_group, dset_index_name, 3, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->mo_2e_int_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_mo_2e_int_eri_lr_cholesky_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->mo_2e_int_group, MO_2E_INT_ERI_LR_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_csf_det_coefficient (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, CSF_DET_COEFFICIENT_NAME "_indices", 256);
  strncpy(dset_value_name, CSF_DET_COEFFICIENT_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 2};
  hsize_t count_i[1] = {(hsize_t) size * 2};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->csf_group, dset_index_name, 2, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->csf_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_csf_det_coefficient_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->csf_group, CSF_DET_COEFFICIENT_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_amplitude_single (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_SINGLE_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_SINGLE_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 2};
  hsize_t count_i[1] = {(hsize_t) size * 2};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_index_name, 2, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_amplitude_single_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->amplitude_group, AMPLITUDE_SINGLE_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_amplitude_single_exp (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_SINGLE_EXP_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_SINGLE_EXP_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 2};
  hsize_t count_i[1] = {(hsize_t) size * 2};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_index_name, 2, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_amplitude_single_exp_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->amplitude_group, AMPLITUDE_SINGLE_EXP_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_amplitude_double (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_DOUBLE_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_DOUBLE_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
  hsize_t count_i[1] = {(hsize_t) size * 4};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_index_name, 4, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_amplitude_double_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->amplitude_group, AMPLITUDE_DOUBLE_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_amplitude_double_exp (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_DOUBLE_EXP_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_DOUBLE_EXP_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
  hsize_t count_i[1] = {(hsize_t) size * 4};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_index_name, 4, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_amplitude_double_exp_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->amplitude_group, AMPLITUDE_DOUBLE_EXP_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_amplitude_triple (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_TRIPLE_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_TRIPLE_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 6};
  hsize_t count_i[1] = {(hsize_t) size * 6};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_index_name, 6, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_amplitude_triple_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->amplitude_group, AMPLITUDE_TRIPLE_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_amplitude_triple_exp (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_TRIPLE_EXP_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_TRIPLE_EXP_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 6};
  hsize_t count_i[1] = {(hsize_t) size * 6};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_index_name, 6, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_amplitude_triple_exp_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->amplitude_group, AMPLITUDE_TRIPLE_EXP_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_amplitude_quadruple (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_QUADRUPLE_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_QUADRUPLE_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 8};
  hsize_t count_i[1] = {(hsize_t) size * 8};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_index_name, 8, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_amplitude_quadruple_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->amplitude_group, AMPLITUDE_QUADRUPLE_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_amplitude_quadruple_exp (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_QUADRUPLE_EXP_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_QUADRUPLE_EXP_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 8};
  hsize_t count_i[1] = {(hsize_t) size * 8};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_index_name, 8, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->amplitude_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_amplitude_quadruple_exp_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->amplitude_group, AMPLITUDE_QUADRUPLE_EXP_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
  hsize_t count_i[1] = {(hsize_t) size * 4};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_index_name, 4, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->rdm_group, RDM_2E_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_upup (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_UPUP_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_UPUP_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
  hsize_t count_i[1] = {(hsize_t) size * 4};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_index_name, 4, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_upup_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->rdm_group, RDM_2E_UPUP_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_dndn (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_DNDN_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_DNDN_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
  hsize_t count_i[1] = {(hsize_t) size * 4};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_index_name, 4, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_dndn_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->rdm_group, RDM_2E_DNDN_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_updn (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_UPDN_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_UPDN_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
  hsize_t count_i[1] = {(hsize_t) size * 4};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_index_name, 4, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_updn_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->rdm_group, RDM_2E_UPDN_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_transition (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_TRANSITION_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_TRANSITION_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 6};
  hsize_t count_i[1] = {(hsize_t) size * 6};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_index_name, 6, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_transition_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->rdm_group, RDM_2E_TRANSITION_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_cholesky (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_CHOLESKY_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
  hsize_t count_i[1] = {(hsize_t) size * 3};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_index_name, 3, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_cholesky_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->rdm_group, RDM_2E_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_upup_cholesky (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_UPUP_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_UPUP_CHOLESKY_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
  hsize_t count_i[1] = {(hsize_t) size * 3};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_index_name, 3, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_upup_cholesky_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->rdm_group, RDM_2E_UPUP_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_dndn_cholesky (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_DNDN_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_DNDN_CHOLESKY_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
  hsize_t count_i[1] = {(hsize_t) size * 3};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_index_name, 3, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_dndn_cholesky_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->rdm_group, RDM_2E_DNDN_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_updn_cholesky (trexio_t* const file,
                               const int64_t offset_file,
                               const int64_t size,
                               const int64_t size_max,
                               int64_t* const eof_read_size,
                               int32_t* const index_read,
                               double* const value_read)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (index_read == NULL) return TREXIO_INVALID_ARG_6;
  if (value_read == NULL) return TREXIO_INVALID_ARG_7;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_UPDN_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_UPDN_CHOLESKY_NAME "_values", 256);

  hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
  hsize_t count_i[1] = {(hsize_t) size * 3};

  hsize_t offset_v[1] = {(hsize_t) offset_file};
  hsize_t count_v[1] = {(hsize_t) size};

  int is_index = 1, is_value = 0;
  trexio_exit_code rc_read;

  // attempt to read indices
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_index_name, 3, offset_i, count_i, NULL, is_index, index_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;
  // attempt to read values
  // when EOF is encountered - the count_v[0] is modified and contains the number of elements being read
  rc_read = trexio_hdf5_open_read_dset_sparse(f->rdm_group, dset_value_name, 1, offset_v, count_v, eof_read_size, is_value, value_read);
  if (rc_read != TREXIO_SUCCESS && rc_read != TREXIO_END) return rc_read;

  return rc_read;
}

trexio_exit_code
trexio_hdf5_read_rdm_2e_updn_cholesky_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->rdm_group, RDM_2E_UPDN_CHOLESKY_NAME "_values", H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_metadata_code (trexio_t* const file, char* const metadata_code, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (metadata_code  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_5;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  herr_t status;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->metadata_group, METADATA_CODE_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) {
    H5Dclose(dset_id);
    return TREXIO_ALLOCATION_FAILED;
  }

  hid_t dspace = H5Dget_space(dset_id);
  if (dset_id <= 0) {
    FREE(ddims);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // get the rank of the dataset in a file
  int rrank = H5Sget_simple_extent_dims(dspace, ddims, NULL);
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_INVALID_ARG_3;
  }

  for (int i=0; i<rrank; i++) {
    if (ddims[i] != dims[i]) {
      H5Dclose(dset_id);
      H5Sclose(dspace);
      FREE(ddims);
      return TREXIO_INVALID_ARG_4;
    }
  }
  FREE(ddims);

  hid_t memtype = H5Tcopy (H5T_C_S1);
  status = H5Tset_size(memtype, H5T_VARIABLE);
  if (status < 0 || memtype <= 0) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_FAILURE;
  }

  char** rdata = CALLOC(dims[0], char*);
  if (rdata == NULL) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_ALLOCATION_FAILED;
  }

  status = H5Dread(dset_id, memtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, rdata);
  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  // copy contents of temporary rdata buffer into the group_dset otherwise they are lost
  // after calling H5Treclaim or H5Dvlen_reclaim functions
  strcpy(metadata_code, "");
  for (uint64_t i=0; i<dims[0]; i++) {
    strncat(metadata_code, rdata[i], max_str_len);
    strcat(metadata_code, TREXIO_DELIM);
  }

  // H5Dvlen_reclaim is deprecated and replaced by H5Treclaim in HDF5 v.1.12.0
  #if (H5_VERS_MAJOR <= 1 && H5_VERS_MINOR < 12)
    status = H5Dvlen_reclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #else
    status = H5Treclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #endif

  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  FREE(rdata);
  H5Dclose(dset_id);
  H5Sclose(dspace);
  H5Tclose(memtype);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_metadata_author (trexio_t* const file, char* const metadata_author, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (metadata_author  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_5;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  herr_t status;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->metadata_group, METADATA_AUTHOR_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) {
    H5Dclose(dset_id);
    return TREXIO_ALLOCATION_FAILED;
  }

  hid_t dspace = H5Dget_space(dset_id);
  if (dset_id <= 0) {
    FREE(ddims);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // get the rank of the dataset in a file
  int rrank = H5Sget_simple_extent_dims(dspace, ddims, NULL);
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_INVALID_ARG_3;
  }

  for (int i=0; i<rrank; i++) {
    if (ddims[i] != dims[i]) {
      H5Dclose(dset_id);
      H5Sclose(dspace);
      FREE(ddims);
      return TREXIO_INVALID_ARG_4;
    }
  }
  FREE(ddims);

  hid_t memtype = H5Tcopy (H5T_C_S1);
  status = H5Tset_size(memtype, H5T_VARIABLE);
  if (status < 0 || memtype <= 0) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_FAILURE;
  }

  char** rdata = CALLOC(dims[0], char*);
  if (rdata == NULL) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_ALLOCATION_FAILED;
  }

  status = H5Dread(dset_id, memtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, rdata);
  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  // copy contents of temporary rdata buffer into the group_dset otherwise they are lost
  // after calling H5Treclaim or H5Dvlen_reclaim functions
  strcpy(metadata_author, "");
  for (uint64_t i=0; i<dims[0]; i++) {
    strncat(metadata_author, rdata[i], max_str_len);
    strcat(metadata_author, TREXIO_DELIM);
  }

  // H5Dvlen_reclaim is deprecated and replaced by H5Treclaim in HDF5 v.1.12.0
  #if (H5_VERS_MAJOR <= 1 && H5_VERS_MINOR < 12)
    status = H5Dvlen_reclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #else
    status = H5Treclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #endif

  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  FREE(rdata);
  H5Dclose(dset_id);
  H5Sclose(dspace);
  H5Tclose(memtype);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_nucleus_label (trexio_t* const file, char* const nucleus_label, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_label  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_5;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  herr_t status;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->nucleus_group, NUCLEUS_LABEL_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) {
    H5Dclose(dset_id);
    return TREXIO_ALLOCATION_FAILED;
  }

  hid_t dspace = H5Dget_space(dset_id);
  if (dset_id <= 0) {
    FREE(ddims);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // get the rank of the dataset in a file
  int rrank = H5Sget_simple_extent_dims(dspace, ddims, NULL);
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_INVALID_ARG_3;
  }

  for (int i=0; i<rrank; i++) {
    if (ddims[i] != dims[i]) {
      H5Dclose(dset_id);
      H5Sclose(dspace);
      FREE(ddims);
      return TREXIO_INVALID_ARG_4;
    }
  }
  FREE(ddims);

  hid_t memtype = H5Tcopy (H5T_C_S1);
  status = H5Tset_size(memtype, H5T_VARIABLE);
  if (status < 0 || memtype <= 0) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_FAILURE;
  }

  char** rdata = CALLOC(dims[0], char*);
  if (rdata == NULL) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_ALLOCATION_FAILED;
  }

  status = H5Dread(dset_id, memtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, rdata);
  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  // copy contents of temporary rdata buffer into the group_dset otherwise they are lost
  // after calling H5Treclaim or H5Dvlen_reclaim functions
  strcpy(nucleus_label, "");
  for (uint64_t i=0; i<dims[0]; i++) {
    strncat(nucleus_label, rdata[i], max_str_len);
    strcat(nucleus_label, TREXIO_DELIM);
  }

  // H5Dvlen_reclaim is deprecated and replaced by H5Treclaim in HDF5 v.1.12.0
  #if (H5_VERS_MAJOR <= 1 && H5_VERS_MINOR < 12)
    status = H5Dvlen_reclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #else
    status = H5Treclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #endif

  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  FREE(rdata);
  H5Dclose(dset_id);
  H5Sclose(dspace);
  H5Tclose(memtype);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_state_label (trexio_t* const file, char* const state_label, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (state_label  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_5;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  herr_t status;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->state_group, STATE_LABEL_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) {
    H5Dclose(dset_id);
    return TREXIO_ALLOCATION_FAILED;
  }

  hid_t dspace = H5Dget_space(dset_id);
  if (dset_id <= 0) {
    FREE(ddims);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // get the rank of the dataset in a file
  int rrank = H5Sget_simple_extent_dims(dspace, ddims, NULL);
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_INVALID_ARG_3;
  }

  for (int i=0; i<rrank; i++) {
    if (ddims[i] != dims[i]) {
      H5Dclose(dset_id);
      H5Sclose(dspace);
      FREE(ddims);
      return TREXIO_INVALID_ARG_4;
    }
  }
  FREE(ddims);

  hid_t memtype = H5Tcopy (H5T_C_S1);
  status = H5Tset_size(memtype, H5T_VARIABLE);
  if (status < 0 || memtype <= 0) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_FAILURE;
  }

  char** rdata = CALLOC(dims[0], char*);
  if (rdata == NULL) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_ALLOCATION_FAILED;
  }

  status = H5Dread(dset_id, memtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, rdata);
  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  // copy contents of temporary rdata buffer into the group_dset otherwise they are lost
  // after calling H5Treclaim or H5Dvlen_reclaim functions
  strcpy(state_label, "");
  for (uint64_t i=0; i<dims[0]; i++) {
    strncat(state_label, rdata[i], max_str_len);
    strcat(state_label, TREXIO_DELIM);
  }

  // H5Dvlen_reclaim is deprecated and replaced by H5Treclaim in HDF5 v.1.12.0
  #if (H5_VERS_MAJOR <= 1 && H5_VERS_MINOR < 12)
    status = H5Dvlen_reclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #else
    status = H5Treclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #endif

  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  FREE(rdata);
  H5Dclose(dset_id);
  H5Sclose(dspace);
  H5Tclose(memtype);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_state_file_name (trexio_t* const file, char* const state_file_name, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (state_file_name  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_5;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  herr_t status;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->state_group, STATE_FILE_NAME_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) {
    H5Dclose(dset_id);
    return TREXIO_ALLOCATION_FAILED;
  }

  hid_t dspace = H5Dget_space(dset_id);
  if (dset_id <= 0) {
    FREE(ddims);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // get the rank of the dataset in a file
  int rrank = H5Sget_simple_extent_dims(dspace, ddims, NULL);
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_INVALID_ARG_3;
  }

  for (int i=0; i<rrank; i++) {
    if (ddims[i] != dims[i]) {
      H5Dclose(dset_id);
      H5Sclose(dspace);
      FREE(ddims);
      return TREXIO_INVALID_ARG_4;
    }
  }
  FREE(ddims);

  hid_t memtype = H5Tcopy (H5T_C_S1);
  status = H5Tset_size(memtype, H5T_VARIABLE);
  if (status < 0 || memtype <= 0) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_FAILURE;
  }

  char** rdata = CALLOC(dims[0], char*);
  if (rdata == NULL) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_ALLOCATION_FAILED;
  }

  status = H5Dread(dset_id, memtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, rdata);
  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  // copy contents of temporary rdata buffer into the group_dset otherwise they are lost
  // after calling H5Treclaim or H5Dvlen_reclaim functions
  strcpy(state_file_name, "");
  for (uint64_t i=0; i<dims[0]; i++) {
    strncat(state_file_name, rdata[i], max_str_len);
    strcat(state_file_name, TREXIO_DELIM);
  }

  // H5Dvlen_reclaim is deprecated and replaced by H5Treclaim in HDF5 v.1.12.0
  #if (H5_VERS_MAJOR <= 1 && H5_VERS_MINOR < 12)
    status = H5Dvlen_reclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #else
    status = H5Treclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #endif

  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  FREE(rdata);
  H5Dclose(dset_id);
  H5Sclose(dspace);
  H5Tclose(memtype);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_class (trexio_t* const file, char* const mo_class, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_class  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_5;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  herr_t status;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_group, MO_CLASS_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) {
    H5Dclose(dset_id);
    return TREXIO_ALLOCATION_FAILED;
  }

  hid_t dspace = H5Dget_space(dset_id);
  if (dset_id <= 0) {
    FREE(ddims);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // get the rank of the dataset in a file
  int rrank = H5Sget_simple_extent_dims(dspace, ddims, NULL);
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_INVALID_ARG_3;
  }

  for (int i=0; i<rrank; i++) {
    if (ddims[i] != dims[i]) {
      H5Dclose(dset_id);
      H5Sclose(dspace);
      FREE(ddims);
      return TREXIO_INVALID_ARG_4;
    }
  }
  FREE(ddims);

  hid_t memtype = H5Tcopy (H5T_C_S1);
  status = H5Tset_size(memtype, H5T_VARIABLE);
  if (status < 0 || memtype <= 0) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_FAILURE;
  }

  char** rdata = CALLOC(dims[0], char*);
  if (rdata == NULL) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_ALLOCATION_FAILED;
  }

  status = H5Dread(dset_id, memtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, rdata);
  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  // copy contents of temporary rdata buffer into the group_dset otherwise they are lost
  // after calling H5Treclaim or H5Dvlen_reclaim functions
  strcpy(mo_class, "");
  for (uint64_t i=0; i<dims[0]; i++) {
    strncat(mo_class, rdata[i], max_str_len);
    strcat(mo_class, TREXIO_DELIM);
  }

  // H5Dvlen_reclaim is deprecated and replaced by H5Treclaim in HDF5 v.1.12.0
  #if (H5_VERS_MAJOR <= 1 && H5_VERS_MINOR < 12)
    status = H5Dvlen_reclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #else
    status = H5Treclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #endif

  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  FREE(rdata);
  H5Dclose(dset_id);
  H5Sclose(dspace);
  H5Tclose(memtype);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_mo_symmetry (trexio_t* const file, char* const mo_symmetry, const uint32_t rank, const uint64_t* dims, const uint32_t max_str_len)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_symmetry  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (max_str_len < 1) return TREXIO_INVALID_ARG_5;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  herr_t status;

  // open the dataset to get its dimensions
  hid_t dset_id = H5Dopen(f->mo_group, MO_SYMMETRY_NAME, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // allocate space for the dimensions to be read
  hsize_t* ddims = CALLOC( (int) rank, hsize_t);
  if (ddims == NULL) {
    H5Dclose(dset_id);
    return TREXIO_ALLOCATION_FAILED;
  }

  hid_t dspace = H5Dget_space(dset_id);
  if (dset_id <= 0) {
    FREE(ddims);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // get the rank of the dataset in a file
  int rrank = H5Sget_simple_extent_dims(dspace, ddims, NULL);
  if (rrank != (int) rank) {
    FREE(ddims);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_INVALID_ARG_3;
  }

  for (int i=0; i<rrank; i++) {
    if (ddims[i] != dims[i]) {
      H5Dclose(dset_id);
      H5Sclose(dspace);
      FREE(ddims);
      return TREXIO_INVALID_ARG_4;
    }
  }
  FREE(ddims);

  hid_t memtype = H5Tcopy (H5T_C_S1);
  status = H5Tset_size(memtype, H5T_VARIABLE);
  if (status < 0 || memtype <= 0) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    return TREXIO_FAILURE;
  }

  char** rdata = CALLOC(dims[0], char*);
  if (rdata == NULL) {
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_ALLOCATION_FAILED;
  }

  status = H5Dread(dset_id, memtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, rdata);
  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  // copy contents of temporary rdata buffer into the group_dset otherwise they are lost
  // after calling H5Treclaim or H5Dvlen_reclaim functions
  strcpy(mo_symmetry, "");
  for (uint64_t i=0; i<dims[0]; i++) {
    strncat(mo_symmetry, rdata[i], max_str_len);
    strcat(mo_symmetry, TREXIO_DELIM);
  }

  // H5Dvlen_reclaim is deprecated and replaced by H5Treclaim in HDF5 v.1.12.0
  #if (H5_VERS_MAJOR <= 1 && H5_VERS_MINOR < 12)
    status = H5Dvlen_reclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #else
    status = H5Treclaim(memtype, dspace, H5P_DEFAULT, rdata);
  #endif

  if (status < 0) {
    FREE(rdata);
    H5Dclose(dset_id);
    H5Sclose(dspace);
    H5Tclose(memtype);
    return TREXIO_FAILURE;
  }

  FREE(rdata);
  H5Dclose(dset_id);
  H5Sclose(dspace);
  H5Tclose(memtype);

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_metadata_code_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_metadata_code_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->metadata_group, METADATA_CODE_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->metadata_group,
                                 METADATA_CODE_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_metadata_author_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_metadata_author_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->metadata_group, METADATA_AUTHOR_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->metadata_group,
                                 METADATA_AUTHOR_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_metadata_unsafe (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_metadata_unsafe(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->metadata_group, METADATA_UNSAFE_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->metadata_group,
                                 METADATA_UNSAFE_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_nucleus_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_nucleus_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->nucleus_group, NUCLEUS_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->nucleus_group,
                                 NUCLEUS_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_nucleus_repulsion (trexio_t* const file, const double num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_nucleus_repulsion(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->nucleus_group, NUCLEUS_REPULSION_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_DOUBLE);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->nucleus_group,
                                 NUCLEUS_REPULSION_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_cell_two_pi (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_cell_two_pi(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->cell_group, CELL_TWO_PI_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->cell_group,
                                 CELL_TWO_PI_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_pbc_periodic (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_pbc_periodic(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->pbc_group, PBC_PERIODIC_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->pbc_group,
                                 PBC_PERIODIC_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_pbc_k_point_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_pbc_k_point_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->pbc_group, PBC_K_POINT_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->pbc_group,
                                 PBC_K_POINT_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_pbc_madelung (trexio_t* const file, const double num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_pbc_madelung(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->pbc_group, PBC_MADELUNG_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_DOUBLE);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->pbc_group,
                                 PBC_MADELUNG_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_electron_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_electron_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->electron_group, ELECTRON_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->electron_group,
                                 ELECTRON_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_electron_up_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_electron_up_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->electron_group, ELECTRON_UP_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->electron_group,
                                 ELECTRON_UP_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_electron_dn_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_electron_dn_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->electron_group, ELECTRON_DN_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->electron_group,
                                 ELECTRON_DN_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_state_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_state_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->state_group, STATE_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->state_group,
                                 STATE_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_state_id (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_state_id(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->state_group, STATE_ID_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->state_group,
                                 STATE_ID_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_state_energy (trexio_t* const file, const double num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_state_energy(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->state_group, STATE_ENERGY_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_DOUBLE);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->state_group,
                                 STATE_ENERGY_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_basis_prim_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_basis_prim_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->basis_group, BASIS_PRIM_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->basis_group,
                                 BASIS_PRIM_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_basis_shell_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_basis_shell_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->basis_group, BASIS_SHELL_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->basis_group,
                                 BASIS_SHELL_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_basis_nao_grid_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_basis_nao_grid_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->basis_group, BASIS_NAO_GRID_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->basis_group,
                                 BASIS_NAO_GRID_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_basis_interp_coeff_cnt (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_basis_interp_coeff_cnt(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->basis_group, BASIS_INTERP_COEFF_CNT_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->basis_group,
                                 BASIS_INTERP_COEFF_CNT_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_basis_e_cut (trexio_t* const file, const double num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_basis_e_cut(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->basis_group, BASIS_E_CUT_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_DOUBLE);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->basis_group,
                                 BASIS_E_CUT_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_ecp_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_ecp_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->ecp_group, ECP_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->ecp_group,
                                 ECP_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_grid_rad_precision (trexio_t* const file, const double num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_grid_rad_precision(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->grid_group, GRID_RAD_PRECISION_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_DOUBLE);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->grid_group,
                                 GRID_RAD_PRECISION_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_grid_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_grid_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->grid_group, GRID_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->grid_group,
                                 GRID_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_grid_max_ang_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_grid_max_ang_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->grid_group, GRID_MAX_ANG_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->grid_group,
                                 GRID_MAX_ANG_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_grid_min_ang_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_grid_min_ang_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->grid_group, GRID_MIN_ANG_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->grid_group,
                                 GRID_MIN_ANG_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_grid_ang_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_grid_ang_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->grid_group, GRID_ANG_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->grid_group,
                                 GRID_ANG_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_grid_rad_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_grid_rad_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->grid_group, GRID_RAD_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->grid_group,
                                 GRID_RAD_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_ao_cartesian (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_ao_cartesian(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->ao_group, AO_CARTESIAN_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->ao_group,
                                 AO_CARTESIAN_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_ao_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_ao_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->ao_group, AO_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->ao_group,
                                 AO_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_ao_2e_int_eri_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_ao_2e_int_eri_cholesky_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->ao_2e_int_group, AO_2E_INT_ERI_CHOLESKY_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->ao_2e_int_group,
                                 AO_2E_INT_ERI_CHOLESKY_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_ao_2e_int_eri_lr_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_ao_2e_int_eri_lr_cholesky_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->ao_2e_int_group, AO_2E_INT_ERI_LR_CHOLESKY_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->ao_2e_int_group,
                                 AO_2E_INT_ERI_LR_CHOLESKY_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_mo_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_mo_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->mo_group, MO_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->mo_group,
                                 MO_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_mo_2e_int_eri_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_mo_2e_int_eri_cholesky_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->mo_2e_int_group, MO_2E_INT_ERI_CHOLESKY_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->mo_2e_int_group,
                                 MO_2E_INT_ERI_CHOLESKY_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_mo_2e_int_eri_lr_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_mo_2e_int_eri_lr_cholesky_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->mo_2e_int_group, MO_2E_INT_ERI_LR_CHOLESKY_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->mo_2e_int_group,
                                 MO_2E_INT_ERI_LR_CHOLESKY_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_determinant_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_determinant_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->determinant_group, DETERMINANT_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->determinant_group,
                                 DETERMINANT_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_csf_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_csf_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->csf_group, CSF_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->csf_group,
                                 CSF_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_rdm_2e_cholesky_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->rdm_group, RDM_2E_CHOLESKY_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->rdm_group,
                                 RDM_2E_CHOLESKY_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e_upup_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_rdm_2e_upup_cholesky_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->rdm_group, RDM_2E_UPUP_CHOLESKY_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->rdm_group,
                                 RDM_2E_UPUP_CHOLESKY_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e_dndn_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_rdm_2e_dndn_cholesky_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->rdm_group, RDM_2E_DNDN_CHOLESKY_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->rdm_group,
                                 RDM_2E_DNDN_CHOLESKY_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e_updn_cholesky_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_rdm_2e_updn_cholesky_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->rdm_group, RDM_2E_UPDN_CHOLESKY_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->rdm_group,
                                 RDM_2E_UPDN_CHOLESKY_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_jastrow_en_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_jastrow_en_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->jastrow_group, JASTROW_EN_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->jastrow_group,
                                 JASTROW_EN_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_jastrow_ee_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_jastrow_ee_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->jastrow_group, JASTROW_EE_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->jastrow_group,
                                 JASTROW_EE_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_jastrow_een_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_jastrow_een_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->jastrow_group, JASTROW_EEN_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->jastrow_group,
                                 JASTROW_EEN_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_jastrow_ee_scaling (trexio_t* const file, const double num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_jastrow_ee_scaling(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->jastrow_group, JASTROW_EE_SCALING_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_DOUBLE);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->jastrow_group,
                                 JASTROW_EE_SCALING_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_qmc_num (trexio_t* const file, const int64_t num)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num < 0) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_qmc_num(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->qmc_group, QMC_NUM_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the dataspace */
  const hid_t dtype_id = H5Tcopy(H5T_NATIVE_INT64);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) {
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const hid_t num_id = H5Acreate(f->qmc_group,
                                 QMC_NUM_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);
  if (num_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  const herr_t status = H5Awrite(num_id, dtype_id, &num);

  H5Sclose(dspace_id);
  H5Aclose(num_id);
  H5Tclose(dtype_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_metadata_package_version (trexio_t* const file, const char* str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_metadata_package_version(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->metadata_group, METADATA_PACKAGE_VERSION_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the datatype for variable length string */
  const hid_t dtype_id = H5Tcopy(H5T_C_S1);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  size_t str_attr_len = strlen(str) + 1;

  herr_t status;
  status = H5Tset_size(dtype_id, str_attr_len);
  if (status < 0) return TREXIO_FAILURE;

  status = H5Tset_strpad(dtype_id, H5T_STR_NULLTERM);
  if (status < 0) return TREXIO_FAILURE;

  /* Setup the dataspace */
  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  /* Create the metadata_package_version attribute of metadata group */
  const hid_t str_id = H5Acreate(f->metadata_group,
                                 METADATA_PACKAGE_VERSION_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);

  if (str_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  status = H5Awrite(str_id, dtype_id, str);

  H5Aclose(str_id);
  H5Sclose(dspace_id);
  H5Tclose(dtype_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_metadata_description (trexio_t* const file, const char* str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_metadata_description(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->metadata_group, METADATA_DESCRIPTION_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the datatype for variable length string */
  const hid_t dtype_id = H5Tcopy(H5T_C_S1);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  size_t str_attr_len = strlen(str) + 1;

  herr_t status;
  status = H5Tset_size(dtype_id, str_attr_len);
  if (status < 0) return TREXIO_FAILURE;

  status = H5Tset_strpad(dtype_id, H5T_STR_NULLTERM);
  if (status < 0) return TREXIO_FAILURE;

  /* Setup the dataspace */
  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  /* Create the metadata_description attribute of metadata group */
  const hid_t str_id = H5Acreate(f->metadata_group,
                                 METADATA_DESCRIPTION_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);

  if (str_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  status = H5Awrite(str_id, dtype_id, str);

  H5Aclose(str_id);
  H5Sclose(dspace_id);
  H5Tclose(dtype_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_nucleus_point_group (trexio_t* const file, const char* str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_nucleus_point_group(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->nucleus_group, NUCLEUS_POINT_GROUP_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the datatype for variable length string */
  const hid_t dtype_id = H5Tcopy(H5T_C_S1);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  size_t str_attr_len = strlen(str) + 1;

  herr_t status;
  status = H5Tset_size(dtype_id, str_attr_len);
  if (status < 0) return TREXIO_FAILURE;

  status = H5Tset_strpad(dtype_id, H5T_STR_NULLTERM);
  if (status < 0) return TREXIO_FAILURE;

  /* Setup the dataspace */
  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  /* Create the nucleus_point_group attribute of nucleus group */
  const hid_t str_id = H5Acreate(f->nucleus_group,
                                 NUCLEUS_POINT_GROUP_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);

  if (str_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  status = H5Awrite(str_id, dtype_id, str);

  H5Aclose(str_id);
  H5Sclose(dspace_id);
  H5Tclose(dtype_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_state_current_label (trexio_t* const file, const char* str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_state_current_label(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->state_group, STATE_CURRENT_LABEL_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the datatype for variable length string */
  const hid_t dtype_id = H5Tcopy(H5T_C_S1);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  size_t str_attr_len = strlen(str) + 1;

  herr_t status;
  status = H5Tset_size(dtype_id, str_attr_len);
  if (status < 0) return TREXIO_FAILURE;

  status = H5Tset_strpad(dtype_id, H5T_STR_NULLTERM);
  if (status < 0) return TREXIO_FAILURE;

  /* Setup the dataspace */
  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  /* Create the state_current_label attribute of state group */
  const hid_t str_id = H5Acreate(f->state_group,
                                 STATE_CURRENT_LABEL_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);

  if (str_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  status = H5Awrite(str_id, dtype_id, str);

  H5Aclose(str_id);
  H5Sclose(dspace_id);
  H5Tclose(dtype_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_basis_type (trexio_t* const file, const char* str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_basis_type(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->basis_group, BASIS_TYPE_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the datatype for variable length string */
  const hid_t dtype_id = H5Tcopy(H5T_C_S1);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  size_t str_attr_len = strlen(str) + 1;

  herr_t status;
  status = H5Tset_size(dtype_id, str_attr_len);
  if (status < 0) return TREXIO_FAILURE;

  status = H5Tset_strpad(dtype_id, H5T_STR_NULLTERM);
  if (status < 0) return TREXIO_FAILURE;

  /* Setup the dataspace */
  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  /* Create the basis_type attribute of basis group */
  const hid_t str_id = H5Acreate(f->basis_group,
                                 BASIS_TYPE_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);

  if (str_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  status = H5Awrite(str_id, dtype_id, str);

  H5Aclose(str_id);
  H5Sclose(dspace_id);
  H5Tclose(dtype_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_basis_oscillation_kind (trexio_t* const file, const char* str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_basis_oscillation_kind(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->basis_group, BASIS_OSCILLATION_KIND_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the datatype for variable length string */
  const hid_t dtype_id = H5Tcopy(H5T_C_S1);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  size_t str_attr_len = strlen(str) + 1;

  herr_t status;
  status = H5Tset_size(dtype_id, str_attr_len);
  if (status < 0) return TREXIO_FAILURE;

  status = H5Tset_strpad(dtype_id, H5T_STR_NULLTERM);
  if (status < 0) return TREXIO_FAILURE;

  /* Setup the dataspace */
  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  /* Create the basis_oscillation_kind attribute of basis group */
  const hid_t str_id = H5Acreate(f->basis_group,
                                 BASIS_OSCILLATION_KIND_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);

  if (str_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  status = H5Awrite(str_id, dtype_id, str);

  H5Aclose(str_id);
  H5Sclose(dspace_id);
  H5Tclose(dtype_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_basis_interpolator_kind (trexio_t* const file, const char* str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_basis_interpolator_kind(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->basis_group, BASIS_INTERPOLATOR_KIND_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the datatype for variable length string */
  const hid_t dtype_id = H5Tcopy(H5T_C_S1);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  size_t str_attr_len = strlen(str) + 1;

  herr_t status;
  status = H5Tset_size(dtype_id, str_attr_len);
  if (status < 0) return TREXIO_FAILURE;

  status = H5Tset_strpad(dtype_id, H5T_STR_NULLTERM);
  if (status < 0) return TREXIO_FAILURE;

  /* Setup the dataspace */
  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  /* Create the basis_interpolator_kind attribute of basis group */
  const hid_t str_id = H5Acreate(f->basis_group,
                                 BASIS_INTERPOLATOR_KIND_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);

  if (str_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  status = H5Awrite(str_id, dtype_id, str);

  H5Aclose(str_id);
  H5Sclose(dspace_id);
  H5Tclose(dtype_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_grid_description (trexio_t* const file, const char* str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_grid_description(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->grid_group, GRID_DESCRIPTION_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the datatype for variable length string */
  const hid_t dtype_id = H5Tcopy(H5T_C_S1);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  size_t str_attr_len = strlen(str) + 1;

  herr_t status;
  status = H5Tset_size(dtype_id, str_attr_len);
  if (status < 0) return TREXIO_FAILURE;

  status = H5Tset_strpad(dtype_id, H5T_STR_NULLTERM);
  if (status < 0) return TREXIO_FAILURE;

  /* Setup the dataspace */
  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  /* Create the grid_description attribute of grid group */
  const hid_t str_id = H5Acreate(f->grid_group,
                                 GRID_DESCRIPTION_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);

  if (str_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  status = H5Awrite(str_id, dtype_id, str);

  H5Aclose(str_id);
  H5Sclose(dspace_id);
  H5Tclose(dtype_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_mo_type (trexio_t* const file, const char* str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_mo_type(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->mo_group, MO_TYPE_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the datatype for variable length string */
  const hid_t dtype_id = H5Tcopy(H5T_C_S1);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  size_t str_attr_len = strlen(str) + 1;

  herr_t status;
  status = H5Tset_size(dtype_id, str_attr_len);
  if (status < 0) return TREXIO_FAILURE;

  status = H5Tset_strpad(dtype_id, H5T_STR_NULLTERM);
  if (status < 0) return TREXIO_FAILURE;

  /* Setup the dataspace */
  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  /* Create the mo_type attribute of mo group */
  const hid_t str_id = H5Acreate(f->mo_group,
                                 MO_TYPE_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);

  if (str_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  status = H5Awrite(str_id, dtype_id, str);

  H5Aclose(str_id);
  H5Sclose(dspace_id);
  H5Tclose(dtype_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_jastrow_type (trexio_t* const file, const char* str)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (str  == NULL) return TREXIO_INVALID_ARG_2;

  trexio_hdf5_t* const f = (trexio_hdf5_t*) file;

  /* Delete the attribute if it exists and if the file is open in UNSAFE mode */
  if (trexio_hdf5_has_jastrow_type(file) == TREXIO_SUCCESS && file->mode == 'u') {
    herr_t status_del = H5Adelete(f->jastrow_group, JASTROW_TYPE_NAME);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  /* Setup the datatype for variable length string */
  const hid_t dtype_id = H5Tcopy(H5T_C_S1);
  if (dtype_id <= 0) return TREXIO_INVALID_ID;

  size_t str_attr_len = strlen(str) + 1;

  herr_t status;
  status = H5Tset_size(dtype_id, str_attr_len);
  if (status < 0) return TREXIO_FAILURE;

  status = H5Tset_strpad(dtype_id, H5T_STR_NULLTERM);
  if (status < 0) return TREXIO_FAILURE;

  /* Setup the dataspace */
  const hid_t dspace_id = H5Screate(H5S_SCALAR);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  /* Create the jastrow_type attribute of jastrow group */
  const hid_t str_id = H5Acreate(f->jastrow_group,
                                 JASTROW_TYPE_NAME,
                                 dtype_id, dspace_id,
                                 H5P_DEFAULT, H5P_DEFAULT);

  if (str_id <= 0) {
    H5Sclose(dspace_id);
    H5Tclose(dtype_id);
    return TREXIO_INVALID_ID;
  }

  status = H5Awrite(str_id, dtype_id, str);

  H5Aclose(str_id);
  H5Sclose(dspace_id);
  H5Tclose(dtype_id);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_hdf5_write_determinant_coefficient(trexio_t* const file,
                                                const int64_t offset_file,
		                                const uint32_t rank,
                                                const uint64_t* dims,
                                                const double* dset)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (rank != 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (dset == NULL) return TREXIO_INVALID_ARG_5;

  const char dset_name[] = "determinant_coefficient";

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t dtype = H5T_NATIVE_DOUBLE;

  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_dims[1] = {(hsize_t) dims[0]};

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_determinant_coefficient(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->determinant_group, dset_name, dtype, chunk_dims, dset);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_data[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->determinant_group, dset_name, dtype, chunk_dims, offset_data, dset);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_determinant_coefficient_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const char dset_name[] = "determinant_coefficient";

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->determinant_group, dset_name, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_hdf5_write_csf_coefficient(trexio_t* const file,
                                                const int64_t offset_file,
		                                const uint32_t rank,
                                                const uint64_t* dims,
                                                const double* dset)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (rank != 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (dset == NULL) return TREXIO_INVALID_ARG_5;

  const char dset_name[] = "csf_coefficient";

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t dtype = H5T_NATIVE_DOUBLE;

  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_dims[1] = {(hsize_t) dims[0]};

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_csf_coefficient(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->csf_group, dset_name, dtype, chunk_dims, dset);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_data[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->csf_group, dset_name, dtype, chunk_dims, offset_data, dset);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_read_csf_coefficient_size (trexio_t* const file, int64_t* const size_max)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (size_max == NULL) return TREXIO_INVALID_ARG_2;

  const char dset_name[] = "csf_coefficient";

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  hid_t dset_id = H5Dopen(f->csf_group, dset_name, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  H5Sget_simple_extent_dims(fspace_id, ddims, NULL);

  H5Dclose(dset_id);
  H5Sclose(fspace_id);

  *size_max = (int64_t) ddims[0];

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_nucleus_charge (trexio_t* const file, const double* nucleus_charge, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_charge == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_nucleus_charge(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->nucleus_group, NUCLEUS_CHARGE_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->nucleus_group,
                             NUCLEUS_CHARGE_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           nucleus_charge);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_nucleus_coord (trexio_t* const file, const double* nucleus_coord, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_coord == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_nucleus_coord(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->nucleus_group, NUCLEUS_COORD_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->nucleus_group,
                             NUCLEUS_COORD_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           nucleus_coord);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_cell_a (trexio_t* const file, const double* cell_a, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_a == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_cell_a(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->cell_group, CELL_A_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->cell_group,
                             CELL_A_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           cell_a);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_cell_b (trexio_t* const file, const double* cell_b, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_b == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_cell_b(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->cell_group, CELL_B_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->cell_group,
                             CELL_B_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           cell_b);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_cell_c (trexio_t* const file, const double* cell_c, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_c == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_cell_c(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->cell_group, CELL_C_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->cell_group,
                             CELL_C_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           cell_c);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_cell_g_a (trexio_t* const file, const double* cell_g_a, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_g_a == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_cell_g_a(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->cell_group, CELL_G_A_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->cell_group,
                             CELL_G_A_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           cell_g_a);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_cell_g_b (trexio_t* const file, const double* cell_g_b, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_g_b == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_cell_g_b(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->cell_group, CELL_G_B_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->cell_group,
                             CELL_G_B_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           cell_g_b);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_cell_g_c (trexio_t* const file, const double* cell_g_c, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (cell_g_c == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_cell_g_c(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->cell_group, CELL_G_C_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->cell_group,
                             CELL_G_C_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           cell_g_c);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_pbc_k_point (trexio_t* const file, const double* pbc_k_point, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (pbc_k_point == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_pbc_k_point(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->pbc_group, PBC_K_POINT_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->pbc_group,
                             PBC_K_POINT_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           pbc_k_point);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_pbc_k_point_weight (trexio_t* const file, const double* pbc_k_point_weight, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (pbc_k_point_weight == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_pbc_k_point_weight(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->pbc_group, PBC_K_POINT_WEIGHT_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->pbc_group,
                             PBC_K_POINT_WEIGHT_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           pbc_k_point_weight);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_nucleus_index (trexio_t* const file, const int64_t* basis_nucleus_index, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nucleus_index == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_nucleus_index(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_NUCLEUS_INDEX_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_NUCLEUS_INDEX_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_nucleus_index);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_shell_ang_mom (trexio_t* const file, const int64_t* basis_shell_ang_mom, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_shell_ang_mom == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_shell_ang_mom(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_SHELL_ANG_MOM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_SHELL_ANG_MOM_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_shell_ang_mom);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_shell_factor (trexio_t* const file, const double* basis_shell_factor, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_shell_factor == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_shell_factor(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_SHELL_FACTOR_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_SHELL_FACTOR_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_shell_factor);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_r_power (trexio_t* const file, const int64_t* basis_r_power, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_r_power == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_r_power(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_R_POWER_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_R_POWER_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_r_power);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_nao_grid_start (trexio_t* const file, const int64_t* basis_nao_grid_start, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_start == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_nao_grid_start(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_NAO_GRID_START_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_NAO_GRID_START_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_nao_grid_start);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_nao_grid_size (trexio_t* const file, const int64_t* basis_nao_grid_size, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_size == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_nao_grid_size(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_NAO_GRID_SIZE_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_NAO_GRID_SIZE_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_nao_grid_size);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_shell_index (trexio_t* const file, const int64_t* basis_shell_index, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_shell_index == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_shell_index(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_SHELL_INDEX_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_SHELL_INDEX_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_shell_index);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_exponent (trexio_t* const file, const double* basis_exponent, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_exponent == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_exponent(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_EXPONENT_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_EXPONENT_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_exponent);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_exponent_im (trexio_t* const file, const double* basis_exponent_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_exponent_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_exponent_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_EXPONENT_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_EXPONENT_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_exponent_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_coefficient (trexio_t* const file, const double* basis_coefficient, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_coefficient == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_coefficient(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_COEFFICIENT_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_COEFFICIENT_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_coefficient);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_coefficient_im (trexio_t* const file, const double* basis_coefficient_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_coefficient_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_coefficient_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_COEFFICIENT_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_COEFFICIENT_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_coefficient_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_oscillation_arg (trexio_t* const file, const double* basis_oscillation_arg, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_oscillation_arg == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_oscillation_arg(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_OSCILLATION_ARG_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_OSCILLATION_ARG_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_oscillation_arg);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_prim_factor (trexio_t* const file, const double* basis_prim_factor, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_prim_factor == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_prim_factor(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_PRIM_FACTOR_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_PRIM_FACTOR_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_prim_factor);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_nao_grid_radius (trexio_t* const file, const double* basis_nao_grid_radius, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_radius == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_nao_grid_radius(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_NAO_GRID_RADIUS_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_NAO_GRID_RADIUS_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_nao_grid_radius);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_nao_grid_phi (trexio_t* const file, const double* basis_nao_grid_phi, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_phi == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_nao_grid_phi(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_NAO_GRID_PHI_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_NAO_GRID_PHI_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_nao_grid_phi);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_nao_grid_grad (trexio_t* const file, const double* basis_nao_grid_grad, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_grad == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_nao_grid_grad(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_NAO_GRID_GRAD_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_NAO_GRID_GRAD_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_nao_grid_grad);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_nao_grid_lap (trexio_t* const file, const double* basis_nao_grid_lap, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_nao_grid_lap == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_nao_grid_lap(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_NAO_GRID_LAP_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_NAO_GRID_LAP_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_nao_grid_lap);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_interpolator_phi (trexio_t* const file, const double* basis_interpolator_phi, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_interpolator_phi == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_interpolator_phi(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_INTERPOLATOR_PHI_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_INTERPOLATOR_PHI_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_interpolator_phi);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_interpolator_grad (trexio_t* const file, const double* basis_interpolator_grad, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_interpolator_grad == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_interpolator_grad(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_INTERPOLATOR_GRAD_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_INTERPOLATOR_GRAD_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_interpolator_grad);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_basis_interpolator_lap (trexio_t* const file, const double* basis_interpolator_lap, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (basis_interpolator_lap == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_basis_interpolator_lap(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->basis_group, BASIS_INTERPOLATOR_LAP_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->basis_group,
                             BASIS_INTERPOLATOR_LAP_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           basis_interpolator_lap);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ecp_max_ang_mom_plus_1 (trexio_t* const file, const int64_t* ecp_max_ang_mom_plus_1, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_max_ang_mom_plus_1 == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ecp_max_ang_mom_plus_1(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ecp_group, ECP_MAX_ANG_MOM_PLUS_1_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ecp_group,
                             ECP_MAX_ANG_MOM_PLUS_1_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ecp_max_ang_mom_plus_1);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ecp_z_core (trexio_t* const file, const int64_t* ecp_z_core, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_z_core == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ecp_z_core(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ecp_group, ECP_Z_CORE_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ecp_group,
                             ECP_Z_CORE_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ecp_z_core);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ecp_ang_mom (trexio_t* const file, const int64_t* ecp_ang_mom, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_ang_mom == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ecp_ang_mom(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ecp_group, ECP_ANG_MOM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ecp_group,
                             ECP_ANG_MOM_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ecp_ang_mom);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ecp_nucleus_index (trexio_t* const file, const int64_t* ecp_nucleus_index, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_nucleus_index == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ecp_nucleus_index(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ecp_group, ECP_NUCLEUS_INDEX_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ecp_group,
                             ECP_NUCLEUS_INDEX_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ecp_nucleus_index);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ecp_exponent (trexio_t* const file, const double* ecp_exponent, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_exponent == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ecp_exponent(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ecp_group, ECP_EXPONENT_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ecp_group,
                             ECP_EXPONENT_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ecp_exponent);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ecp_coefficient (trexio_t* const file, const double* ecp_coefficient, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_coefficient == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ecp_coefficient(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ecp_group, ECP_COEFFICIENT_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ecp_group,
                             ECP_COEFFICIENT_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ecp_coefficient);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ecp_power (trexio_t* const file, const int64_t* ecp_power, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_power == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ecp_power(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ecp_group, ECP_POWER_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ecp_group,
                             ECP_POWER_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ecp_power);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_grid_coord (trexio_t* const file, const double* grid_coord, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_coord == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_grid_coord(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->grid_group, GRID_COORD_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->grid_group,
                             GRID_COORD_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           grid_coord);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_grid_weight (trexio_t* const file, const double* grid_weight, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_weight == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_grid_weight(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->grid_group, GRID_WEIGHT_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->grid_group,
                             GRID_WEIGHT_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           grid_weight);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_grid_ang_coord (trexio_t* const file, const double* grid_ang_coord, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_ang_coord == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_grid_ang_coord(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->grid_group, GRID_ANG_COORD_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->grid_group,
                             GRID_ANG_COORD_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           grid_ang_coord);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_grid_ang_weight (trexio_t* const file, const double* grid_ang_weight, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_ang_weight == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_grid_ang_weight(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->grid_group, GRID_ANG_WEIGHT_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->grid_group,
                             GRID_ANG_WEIGHT_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           grid_ang_weight);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_grid_rad_coord (trexio_t* const file, const double* grid_rad_coord, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_rad_coord == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_grid_rad_coord(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->grid_group, GRID_RAD_COORD_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->grid_group,
                             GRID_RAD_COORD_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           grid_rad_coord);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_grid_rad_weight (trexio_t* const file, const double* grid_rad_weight, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (grid_rad_weight == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_grid_rad_weight(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->grid_group, GRID_RAD_WEIGHT_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->grid_group,
                             GRID_RAD_WEIGHT_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           grid_rad_weight);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_shell (trexio_t* const file, const int64_t* ao_shell, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_shell == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ao_shell(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ao_group, AO_SHELL_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ao_group,
                             AO_SHELL_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ao_shell);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_normalization (trexio_t* const file, const double* ao_normalization, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_normalization == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ao_normalization(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ao_group, AO_NORMALIZATION_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ao_group,
                             AO_NORMALIZATION_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ao_normalization);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_1e_int_overlap (trexio_t* const file, const double* ao_1e_int_overlap, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_overlap == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ao_1e_int_overlap(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ao_1e_int_group, AO_1E_INT_OVERLAP_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ao_1e_int_group,
                             AO_1E_INT_OVERLAP_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ao_1e_int_overlap);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_1e_int_kinetic (trexio_t* const file, const double* ao_1e_int_kinetic, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_kinetic == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ao_1e_int_kinetic(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ao_1e_int_group, AO_1E_INT_KINETIC_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ao_1e_int_group,
                             AO_1E_INT_KINETIC_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ao_1e_int_kinetic);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_1e_int_potential_n_e (trexio_t* const file, const double* ao_1e_int_potential_n_e, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_potential_n_e == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ao_1e_int_potential_n_e(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ao_1e_int_group, AO_1E_INT_POTENTIAL_N_E_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ao_1e_int_group,
                             AO_1E_INT_POTENTIAL_N_E_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ao_1e_int_potential_n_e);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_1e_int_ecp (trexio_t* const file, const double* ao_1e_int_ecp, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_ecp == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ao_1e_int_ecp(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ao_1e_int_group, AO_1E_INT_ECP_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ao_1e_int_group,
                             AO_1E_INT_ECP_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ao_1e_int_ecp);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_1e_int_core_hamiltonian (trexio_t* const file, const double* ao_1e_int_core_hamiltonian, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_core_hamiltonian == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ao_1e_int_core_hamiltonian(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ao_1e_int_group, AO_1E_INT_CORE_HAMILTONIAN_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ao_1e_int_group,
                             AO_1E_INT_CORE_HAMILTONIAN_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ao_1e_int_core_hamiltonian);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_1e_int_overlap_im (trexio_t* const file, const double* ao_1e_int_overlap_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_overlap_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ao_1e_int_overlap_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ao_1e_int_group, AO_1E_INT_OVERLAP_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ao_1e_int_group,
                             AO_1E_INT_OVERLAP_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ao_1e_int_overlap_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_1e_int_kinetic_im (trexio_t* const file, const double* ao_1e_int_kinetic_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_kinetic_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ao_1e_int_kinetic_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ao_1e_int_group, AO_1E_INT_KINETIC_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ao_1e_int_group,
                             AO_1E_INT_KINETIC_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ao_1e_int_kinetic_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_1e_int_potential_n_e_im (trexio_t* const file, const double* ao_1e_int_potential_n_e_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_potential_n_e_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ao_1e_int_potential_n_e_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ao_1e_int_group, AO_1E_INT_POTENTIAL_N_E_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ao_1e_int_group,
                             AO_1E_INT_POTENTIAL_N_E_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ao_1e_int_potential_n_e_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_1e_int_ecp_im (trexio_t* const file, const double* ao_1e_int_ecp_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_ecp_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ao_1e_int_ecp_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ao_1e_int_group, AO_1E_INT_ECP_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ao_1e_int_group,
                             AO_1E_INT_ECP_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ao_1e_int_ecp_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_1e_int_core_hamiltonian_im (trexio_t* const file, const double* ao_1e_int_core_hamiltonian_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (ao_1e_int_core_hamiltonian_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_ao_1e_int_core_hamiltonian_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->ao_1e_int_group, AO_1E_INT_CORE_HAMILTONIAN_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->ao_1e_int_group,
                             AO_1E_INT_CORE_HAMILTONIAN_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           ao_1e_int_core_hamiltonian_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_coefficient (trexio_t* const file, const double* mo_coefficient, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_coefficient == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_coefficient(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_group, MO_COEFFICIENT_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_group,
                             MO_COEFFICIENT_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_coefficient);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_coefficient_im (trexio_t* const file, const double* mo_coefficient_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_coefficient_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_coefficient_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_group, MO_COEFFICIENT_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_group,
                             MO_COEFFICIENT_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_coefficient_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_occupation (trexio_t* const file, const double* mo_occupation, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_occupation == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_occupation(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_group, MO_OCCUPATION_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_group,
                             MO_OCCUPATION_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_occupation);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_energy (trexio_t* const file, const double* mo_energy, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_energy == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_energy(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_group, MO_ENERGY_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_group,
                             MO_ENERGY_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_energy);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_spin (trexio_t* const file, const int64_t* mo_spin, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_spin == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_spin(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_group, MO_SPIN_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_group,
                             MO_SPIN_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_spin);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_k_point (trexio_t* const file, const int64_t* mo_k_point, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_k_point == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_k_point(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_group, MO_K_POINT_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_group,
                             MO_K_POINT_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_k_point);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_1e_int_overlap (trexio_t* const file, const double* mo_1e_int_overlap, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_overlap == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_1e_int_overlap(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_1e_int_group, MO_1E_INT_OVERLAP_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_1e_int_group,
                             MO_1E_INT_OVERLAP_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_1e_int_overlap);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_1e_int_kinetic (trexio_t* const file, const double* mo_1e_int_kinetic, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_kinetic == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_1e_int_kinetic(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_1e_int_group, MO_1E_INT_KINETIC_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_1e_int_group,
                             MO_1E_INT_KINETIC_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_1e_int_kinetic);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_1e_int_potential_n_e (trexio_t* const file, const double* mo_1e_int_potential_n_e, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_potential_n_e == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_1e_int_potential_n_e(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_1e_int_group, MO_1E_INT_POTENTIAL_N_E_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_1e_int_group,
                             MO_1E_INT_POTENTIAL_N_E_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_1e_int_potential_n_e);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_1e_int_ecp (trexio_t* const file, const double* mo_1e_int_ecp, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_ecp == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_1e_int_ecp(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_1e_int_group, MO_1E_INT_ECP_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_1e_int_group,
                             MO_1E_INT_ECP_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_1e_int_ecp);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_1e_int_core_hamiltonian (trexio_t* const file, const double* mo_1e_int_core_hamiltonian, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_core_hamiltonian == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_1e_int_core_hamiltonian(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_1e_int_group, MO_1E_INT_CORE_HAMILTONIAN_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_1e_int_group,
                             MO_1E_INT_CORE_HAMILTONIAN_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_1e_int_core_hamiltonian);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_1e_int_overlap_im (trexio_t* const file, const double* mo_1e_int_overlap_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_overlap_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_1e_int_overlap_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_1e_int_group, MO_1E_INT_OVERLAP_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_1e_int_group,
                             MO_1E_INT_OVERLAP_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_1e_int_overlap_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_1e_int_kinetic_im (trexio_t* const file, const double* mo_1e_int_kinetic_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_kinetic_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_1e_int_kinetic_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_1e_int_group, MO_1E_INT_KINETIC_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_1e_int_group,
                             MO_1E_INT_KINETIC_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_1e_int_kinetic_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_1e_int_potential_n_e_im (trexio_t* const file, const double* mo_1e_int_potential_n_e_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_potential_n_e_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_1e_int_potential_n_e_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_1e_int_group, MO_1E_INT_POTENTIAL_N_E_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_1e_int_group,
                             MO_1E_INT_POTENTIAL_N_E_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_1e_int_potential_n_e_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_1e_int_ecp_im (trexio_t* const file, const double* mo_1e_int_ecp_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_ecp_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_1e_int_ecp_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_1e_int_group, MO_1E_INT_ECP_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_1e_int_group,
                             MO_1E_INT_ECP_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_1e_int_ecp_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_1e_int_core_hamiltonian_im (trexio_t* const file, const double* mo_1e_int_core_hamiltonian_im, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_1e_int_core_hamiltonian_im == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_mo_1e_int_core_hamiltonian_im(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->mo_1e_int_group, MO_1E_INT_CORE_HAMILTONIAN_IM_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->mo_1e_int_group,
                             MO_1E_INT_CORE_HAMILTONIAN_IM_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           mo_1e_int_core_hamiltonian_im);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_rdm_1e (trexio_t* const file, const double* rdm_1e, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (rdm_1e == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_rdm_1e(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->rdm_group, RDM_1E_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->rdm_group,
                             RDM_1E_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           rdm_1e);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_rdm_1e_up (trexio_t* const file, const double* rdm_1e_up, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (rdm_1e_up == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_rdm_1e_up(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->rdm_group, RDM_1E_UP_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->rdm_group,
                             RDM_1E_UP_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           rdm_1e_up);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_rdm_1e_dn (trexio_t* const file, const double* rdm_1e_dn, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (rdm_1e_dn == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_rdm_1e_dn(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->rdm_group, RDM_1E_DN_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->rdm_group,
                             RDM_1E_DN_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           rdm_1e_dn);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_rdm_1e_transition (trexio_t* const file, const double* rdm_1e_transition, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (rdm_1e_transition == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_rdm_1e_transition(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->rdm_group, RDM_1E_TRANSITION_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->rdm_group,
                             RDM_1E_TRANSITION_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           rdm_1e_transition);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_jastrow_en (trexio_t* const file, const double* jastrow_en, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_en == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_jastrow_en(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->jastrow_group, JASTROW_EN_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->jastrow_group,
                             JASTROW_EN_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           jastrow_en);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_jastrow_ee (trexio_t* const file, const double* jastrow_ee, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_ee == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_jastrow_ee(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->jastrow_group, JASTROW_EE_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->jastrow_group,
                             JASTROW_EE_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           jastrow_ee);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_jastrow_een (trexio_t* const file, const double* jastrow_een, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_een == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_jastrow_een(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->jastrow_group, JASTROW_EEN_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->jastrow_group,
                             JASTROW_EEN_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           jastrow_een);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_jastrow_en_nucleus (trexio_t* const file, const int64_t* jastrow_en_nucleus, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_en_nucleus == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_jastrow_en_nucleus(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->jastrow_group, JASTROW_EN_NUCLEUS_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->jastrow_group,
                             JASTROW_EN_NUCLEUS_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           jastrow_en_nucleus);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_jastrow_een_nucleus (trexio_t* const file, const int64_t* jastrow_een_nucleus, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_een_nucleus == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_jastrow_een_nucleus(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->jastrow_group, JASTROW_EEN_NUCLEUS_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->jastrow_group,
                             JASTROW_EEN_NUCLEUS_NAME,
                             H5T_NATIVE_INT64,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_INT64,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           jastrow_een_nucleus);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_jastrow_en_scaling (trexio_t* const file, const double* jastrow_en_scaling, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (jastrow_en_scaling == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_jastrow_en_scaling(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->jastrow_group, JASTROW_EN_SCALING_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->jastrow_group,
                             JASTROW_EN_SCALING_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           jastrow_en_scaling);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_qmc_point (trexio_t* const file, const double* qmc_point, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (qmc_point == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_qmc_point(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->qmc_group, QMC_POINT_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->qmc_group,
                             QMC_POINT_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           qmc_point);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_qmc_psi (trexio_t* const file, const double* qmc_psi, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (qmc_psi == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_qmc_psi(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->qmc_group, QMC_PSI_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->qmc_group,
                             QMC_PSI_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           qmc_psi);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_qmc_e_loc (trexio_t* const file, const double* qmc_e_loc, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (qmc_e_loc == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-native h5repack utility after deleting/overwriting big datasets.
  */
  
  if ((trexio_hdf5_has_qmc_e_loc(file) == TREXIO_SUCCESS) && (file->mode == 'u')) {
    herr_t status_del = H5Ldelete(f->qmc_group, QMC_E_LOC_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  hid_t dspace_id = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace_id <= 0) return TREXIO_INVALID_ID;

  hid_t dset_id = H5Dcreate (f->qmc_group,
                             QMC_E_LOC_NAME,
                             H5T_NATIVE_DOUBLE,
                             dspace_id,
                             H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) {
    H5Sclose(dspace_id);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Dwrite(dset_id,
                           H5T_NATIVE_DOUBLE,
                           H5S_ALL,
                           dspace_id,
                           H5P_DEFAULT,
                           qmc_e_loc);
  H5Dclose(dset_id);
  H5Sclose(dspace_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_ao_2e_int_eri (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 4;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AO_2E_INT_ERI_NAME "_indices", 256);
  strncpy(dset_value_name, AO_2E_INT_ERI_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_ao_2e_int_eri(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->ao_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->ao_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->ao_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->ao_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_ao_2e_int_eri_lr (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 4;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AO_2E_INT_ERI_LR_NAME "_indices", 256);
  strncpy(dset_value_name, AO_2E_INT_ERI_LR_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_ao_2e_int_eri_lr(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->ao_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->ao_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->ao_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->ao_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_ao_2e_int_eri_cholesky (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 3;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AO_2E_INT_ERI_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, AO_2E_INT_ERI_CHOLESKY_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_ao_2e_int_eri_cholesky(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->ao_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->ao_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->ao_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->ao_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_ao_2e_int_eri_lr_cholesky (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 3;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AO_2E_INT_ERI_LR_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, AO_2E_INT_ERI_LR_CHOLESKY_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_ao_2e_int_eri_lr_cholesky(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->ao_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->ao_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->ao_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->ao_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_mo_2e_int_eri (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 4;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, MO_2E_INT_ERI_NAME "_indices", 256);
  strncpy(dset_value_name, MO_2E_INT_ERI_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_mo_2e_int_eri(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->mo_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->mo_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->mo_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->mo_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_mo_2e_int_eri_lr (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 4;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, MO_2E_INT_ERI_LR_NAME "_indices", 256);
  strncpy(dset_value_name, MO_2E_INT_ERI_LR_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_mo_2e_int_eri_lr(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->mo_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->mo_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->mo_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->mo_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_mo_2e_int_eri_cholesky (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 3;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, MO_2E_INT_ERI_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, MO_2E_INT_ERI_CHOLESKY_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_mo_2e_int_eri_cholesky(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->mo_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->mo_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->mo_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->mo_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_mo_2e_int_eri_lr_cholesky (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 3;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, MO_2E_INT_ERI_LR_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, MO_2E_INT_ERI_LR_CHOLESKY_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_mo_2e_int_eri_lr_cholesky(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->mo_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->mo_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->mo_2e_int_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->mo_2e_int_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_csf_det_coefficient (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 2;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, CSF_DET_COEFFICIENT_NAME "_indices", 256);
  strncpy(dset_value_name, CSF_DET_COEFFICIENT_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_csf_det_coefficient(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->csf_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->csf_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 2};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->csf_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->csf_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_amplitude_single (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 2;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_SINGLE_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_SINGLE_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_amplitude_single(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 2};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_amplitude_single_exp (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 2;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_SINGLE_EXP_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_SINGLE_EXP_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_amplitude_single_exp(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 2};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_amplitude_double (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 4;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_DOUBLE_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_DOUBLE_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_amplitude_double(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_amplitude_double_exp (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 4;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_DOUBLE_EXP_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_DOUBLE_EXP_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_amplitude_double_exp(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_amplitude_triple (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 6;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_TRIPLE_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_TRIPLE_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_amplitude_triple(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 6};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_amplitude_triple_exp (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 6;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_TRIPLE_EXP_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_TRIPLE_EXP_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_amplitude_triple_exp(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 6};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_amplitude_quadruple (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 8;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_QUADRUPLE_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_QUADRUPLE_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_amplitude_quadruple(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 8};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_amplitude_quadruple_exp (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 8;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, AMPLITUDE_QUADRUPLE_EXP_NAME "_indices", 256);
  strncpy(dset_value_name, AMPLITUDE_QUADRUPLE_EXP_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_amplitude_quadruple_exp(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 8};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->amplitude_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 4;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_rdm_2e(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e_upup (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 4;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_UPUP_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_UPUP_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_rdm_2e_upup(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e_dndn (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 4;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_DNDN_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_DNDN_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_rdm_2e_dndn(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e_updn (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 4;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_UPDN_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_UPDN_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_rdm_2e_updn(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 4};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e_transition (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 6;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_TRANSITION_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_TRANSITION_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_rdm_2e_transition(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 6};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e_cholesky (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 3;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_CHOLESKY_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_rdm_2e_cholesky(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e_upup_cholesky (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 3;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_UPUP_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_UPUP_CHOLESKY_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_rdm_2e_upup_cholesky(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e_dndn_cholesky (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 3;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_DNDN_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_DNDN_CHOLESKY_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_rdm_2e_dndn_cholesky(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_rdm_2e_updn_cholesky (trexio_t* const file,
                                const int64_t offset_file,
                                const int64_t size,
                                const int64_t size_max,
                                const int32_t* index_sparse,
                                const double* value_sparse)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (size < 0) return TREXIO_INVALID_ARG_3;
  if (size_max < 0) return TREXIO_INVALID_ARG_4;
  if (index_sparse == NULL) return TREXIO_INVALID_ARG_5;
  if (value_sparse == NULL) return TREXIO_INVALID_ARG_6;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t index_dtype;
  const void* index_p = NULL;
  void* index_p_non_const = NULL;
  uint64_t size_ranked = (uint64_t) size * 3;
  /* Determine the optimal type for storing indices depending on the size_max (usually mo_num or ao_num) */
  if (size_max < UINT8_MAX) {
    uint8_t* index = CALLOC(size_ranked, uint8_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint8_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT8;
  } else if (size_max < UINT16_MAX) {
    uint16_t* index = CALLOC(size_ranked, uint16_t);
    if (index == NULL) return TREXIO_ALLOCATION_FAILED;
    for (uint64_t i=0; i<size_ranked; ++i){
      index[i] = (uint16_t) index_sparse[i];
    }
    index_p = index;
    index_p_non_const = index;
    index_dtype = H5T_NATIVE_UINT16;
  } else {
    index_p = index_sparse;
    index_dtype = H5T_NATIVE_INT32;
  }

  /* Store float values in double precision */
  hid_t value_dtype = H5T_NATIVE_DOUBLE;
  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_i_dims[1] = {size_ranked};
  const hsize_t chunk_v_dims[1] = {size};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_index_name[256];
  char dset_value_name[256];
  /* Build the names of the datasets */
  strncpy(dset_index_name, RDM_2E_UPDN_CHOLESKY_NAME "_indices", 256);
  strncpy(dset_value_name, RDM_2E_UPDN_CHOLESKY_NAME "_values", 256);

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if (trexio_hdf5_has_rdm_2e_updn_cholesky(file) == TREXIO_HAS_NOT) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_i[1] = {(hsize_t) offset_file * 3};
    hsize_t offset_v[1] = {(hsize_t) offset_file};

  /* Create chunked dataset with index_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_index_name, index_dtype, chunk_i_dims, offset_i, index_p);
    if (index_p != index_sparse) FREE(index_p_non_const);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  /* Create chunked dataset with value_dtype datatype and write values into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->rdm_group, dset_value_name, value_dtype, chunk_v_dims, offset_v, value_sparse);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_write_metadata_code (trexio_t* const file, const char** metadata_code, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (metadata_code  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-provided h5repack utility after deleting/overwriting big datasets.
  */
  if ( (trexio_hdf5_has_metadata_code(file) == TREXIO_SUCCESS) && (file->mode == 'u') ) {
    herr_t status_del = H5Ldelete(f->metadata_group, METADATA_CODE_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  herr_t status;
  hid_t dset_id;

  /* we are going to write variable-length strings */
  hid_t memtype = H5Tcopy (H5T_C_S1);
  if (memtype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (memtype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  hid_t dspace = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace <= 0) return TREXIO_INVALID_ID;

  /* code to create dataset */
  hid_t filetype = H5Tcopy (H5T_FORTRAN_S1);
  if (filetype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (filetype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  dset_id = H5Dcreate (f->metadata_group, METADATA_CODE_NAME, filetype, dspace,
                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  status = H5Dwrite (dset_id, memtype,
                     H5S_ALL, H5S_ALL, H5P_DEFAULT,
                     metadata_code);

  H5Dclose (dset_id);
  H5Sclose (dspace);
  H5Tclose (filetype);
  H5Tclose (memtype);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_metadata_author (trexio_t* const file, const char** metadata_author, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (metadata_author  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-provided h5repack utility after deleting/overwriting big datasets.
  */
  if ( (trexio_hdf5_has_metadata_author(file) == TREXIO_SUCCESS) && (file->mode == 'u') ) {
    herr_t status_del = H5Ldelete(f->metadata_group, METADATA_AUTHOR_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  herr_t status;
  hid_t dset_id;

  /* we are going to write variable-length strings */
  hid_t memtype = H5Tcopy (H5T_C_S1);
  if (memtype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (memtype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  hid_t dspace = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace <= 0) return TREXIO_INVALID_ID;

  /* code to create dataset */
  hid_t filetype = H5Tcopy (H5T_FORTRAN_S1);
  if (filetype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (filetype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  dset_id = H5Dcreate (f->metadata_group, METADATA_AUTHOR_NAME, filetype, dspace,
                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  status = H5Dwrite (dset_id, memtype,
                     H5S_ALL, H5S_ALL, H5P_DEFAULT,
                     metadata_author);

  H5Dclose (dset_id);
  H5Sclose (dspace);
  H5Tclose (filetype);
  H5Tclose (memtype);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_nucleus_label (trexio_t* const file, const char** nucleus_label, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_label  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-provided h5repack utility after deleting/overwriting big datasets.
  */
  if ( (trexio_hdf5_has_nucleus_label(file) == TREXIO_SUCCESS) && (file->mode == 'u') ) {
    herr_t status_del = H5Ldelete(f->nucleus_group, NUCLEUS_LABEL_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  herr_t status;
  hid_t dset_id;

  /* we are going to write variable-length strings */
  hid_t memtype = H5Tcopy (H5T_C_S1);
  if (memtype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (memtype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  hid_t dspace = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace <= 0) return TREXIO_INVALID_ID;

  /* code to create dataset */
  hid_t filetype = H5Tcopy (H5T_FORTRAN_S1);
  if (filetype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (filetype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  dset_id = H5Dcreate (f->nucleus_group, NUCLEUS_LABEL_NAME, filetype, dspace,
                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  status = H5Dwrite (dset_id, memtype,
                     H5S_ALL, H5S_ALL, H5P_DEFAULT,
                     nucleus_label);

  H5Dclose (dset_id);
  H5Sclose (dspace);
  H5Tclose (filetype);
  H5Tclose (memtype);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_state_label (trexio_t* const file, const char** state_label, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (state_label  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-provided h5repack utility after deleting/overwriting big datasets.
  */
  if ( (trexio_hdf5_has_state_label(file) == TREXIO_SUCCESS) && (file->mode == 'u') ) {
    herr_t status_del = H5Ldelete(f->state_group, STATE_LABEL_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  herr_t status;
  hid_t dset_id;

  /* we are going to write variable-length strings */
  hid_t memtype = H5Tcopy (H5T_C_S1);
  if (memtype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (memtype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  hid_t dspace = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace <= 0) return TREXIO_INVALID_ID;

  /* code to create dataset */
  hid_t filetype = H5Tcopy (H5T_FORTRAN_S1);
  if (filetype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (filetype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  dset_id = H5Dcreate (f->state_group, STATE_LABEL_NAME, filetype, dspace,
                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  status = H5Dwrite (dset_id, memtype,
                     H5S_ALL, H5S_ALL, H5P_DEFAULT,
                     state_label);

  H5Dclose (dset_id);
  H5Sclose (dspace);
  H5Tclose (filetype);
  H5Tclose (memtype);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_state_file_name (trexio_t* const file, const char** state_file_name, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (state_file_name  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-provided h5repack utility after deleting/overwriting big datasets.
  */
  if ( (trexio_hdf5_has_state_file_name(file) == TREXIO_SUCCESS) && (file->mode == 'u') ) {
    herr_t status_del = H5Ldelete(f->state_group, STATE_FILE_NAME_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  herr_t status;
  hid_t dset_id;

  /* we are going to write variable-length strings */
  hid_t memtype = H5Tcopy (H5T_C_S1);
  if (memtype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (memtype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  hid_t dspace = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace <= 0) return TREXIO_INVALID_ID;

  /* code to create dataset */
  hid_t filetype = H5Tcopy (H5T_FORTRAN_S1);
  if (filetype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (filetype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  dset_id = H5Dcreate (f->state_group, STATE_FILE_NAME_NAME, filetype, dspace,
                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  status = H5Dwrite (dset_id, memtype,
                     H5S_ALL, H5S_ALL, H5P_DEFAULT,
                     state_file_name);

  H5Dclose (dset_id);
  H5Sclose (dspace);
  H5Tclose (filetype);
  H5Tclose (memtype);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_class (trexio_t* const file, const char** mo_class, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_class  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-provided h5repack utility after deleting/overwriting big datasets.
  */
  if ( (trexio_hdf5_has_mo_class(file) == TREXIO_SUCCESS) && (file->mode == 'u') ) {
    herr_t status_del = H5Ldelete(f->mo_group, MO_CLASS_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  herr_t status;
  hid_t dset_id;

  /* we are going to write variable-length strings */
  hid_t memtype = H5Tcopy (H5T_C_S1);
  if (memtype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (memtype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  hid_t dspace = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace <= 0) return TREXIO_INVALID_ID;

  /* code to create dataset */
  hid_t filetype = H5Tcopy (H5T_FORTRAN_S1);
  if (filetype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (filetype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  dset_id = H5Dcreate (f->mo_group, MO_CLASS_NAME, filetype, dspace,
                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  status = H5Dwrite (dset_id, memtype,
                     H5S_ALL, H5S_ALL, H5P_DEFAULT,
                     mo_class);

  H5Dclose (dset_id);
  H5Sclose (dspace);
  H5Tclose (filetype);
  H5Tclose (memtype);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_write_mo_symmetry (trexio_t* const file, const char** mo_symmetry, const uint32_t rank, const uint64_t* dims)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (mo_symmetry  == NULL) return TREXIO_INVALID_ARG_2;
  if (rank < 1) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  /*
     Try to delete an existing dataset by unlinking it from the group (UNSAFE mode).
     NOTE: In principle, HDF5 should see the deallocated (unused) file space and free it,
     thus reducing the size of the HDF5 file. In practic, this is not always the case.

     Consider using HDF5-provided h5repack utility after deleting/overwriting big datasets.
  */
  if ( (trexio_hdf5_has_mo_symmetry(file) == TREXIO_SUCCESS) && (file->mode == 'u') ) {
    herr_t status_del = H5Ldelete(f->mo_group, MO_SYMMETRY_NAME, H5P_DEFAULT);
    if (status_del < 0) return TREXIO_FAILURE;
  }

  herr_t status;
  hid_t dset_id;

  /* we are going to write variable-length strings */
  hid_t memtype = H5Tcopy (H5T_C_S1);
  if (memtype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (memtype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  hid_t dspace = H5Screate_simple( (int) rank, (const hsize_t*) dims, NULL);
  if (dspace <= 0) return TREXIO_INVALID_ID;

  /* code to create dataset */
  hid_t filetype = H5Tcopy (H5T_FORTRAN_S1);
  if (filetype <= 0) return TREXIO_INVALID_ID;

  status = H5Tset_size (filetype, H5T_VARIABLE);
  if (status < 0) return TREXIO_FAILURE;

  dset_id = H5Dcreate (f->mo_group, MO_SYMMETRY_NAME, filetype, dspace,
                       H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  status = H5Dwrite (dset_id, memtype,
                     H5S_ALL, H5S_ALL, H5P_DEFAULT,
                     mo_symmetry);

  H5Dclose (dset_id);
  H5Sclose (dspace);
  H5Tclose (filetype);
  H5Tclose (memtype);

  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;

}

trexio_exit_code
trexio_hdf5_delete_metadata (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->metadata_group);
  f->metadata_group = 0;
  herr_t status = H5Ldelete(f->file_id, METADATA_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->metadata_group = H5Gcreate(f->file_id, METADATA_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->metadata_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_nucleus (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->nucleus_group);
  f->nucleus_group = 0;
  herr_t status = H5Ldelete(f->file_id, NUCLEUS_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->nucleus_group = H5Gcreate(f->file_id, NUCLEUS_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->nucleus_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_cell (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->cell_group);
  f->cell_group = 0;
  herr_t status = H5Ldelete(f->file_id, CELL_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->cell_group = H5Gcreate(f->file_id, CELL_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->cell_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_pbc (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->pbc_group);
  f->pbc_group = 0;
  herr_t status = H5Ldelete(f->file_id, PBC_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->pbc_group = H5Gcreate(f->file_id, PBC_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->pbc_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_electron (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->electron_group);
  f->electron_group = 0;
  herr_t status = H5Ldelete(f->file_id, ELECTRON_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->electron_group = H5Gcreate(f->file_id, ELECTRON_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->electron_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_state (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->state_group);
  f->state_group = 0;
  herr_t status = H5Ldelete(f->file_id, STATE_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->state_group = H5Gcreate(f->file_id, STATE_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->state_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_basis (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->basis_group);
  f->basis_group = 0;
  herr_t status = H5Ldelete(f->file_id, BASIS_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->basis_group = H5Gcreate(f->file_id, BASIS_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->basis_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_ecp (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->ecp_group);
  f->ecp_group = 0;
  herr_t status = H5Ldelete(f->file_id, ECP_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->ecp_group = H5Gcreate(f->file_id, ECP_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->ecp_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_grid (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->grid_group);
  f->grid_group = 0;
  herr_t status = H5Ldelete(f->file_id, GRID_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->grid_group = H5Gcreate(f->file_id, GRID_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->grid_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_ao (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->ao_group);
  f->ao_group = 0;
  herr_t status = H5Ldelete(f->file_id, AO_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->ao_group = H5Gcreate(f->file_id, AO_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->ao_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_ao_1e_int (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->ao_1e_int_group);
  f->ao_1e_int_group = 0;
  herr_t status = H5Ldelete(f->file_id, AO_1E_INT_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->ao_1e_int_group = H5Gcreate(f->file_id, AO_1E_INT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->ao_1e_int_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_ao_2e_int (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->ao_2e_int_group);
  f->ao_2e_int_group = 0;
  herr_t status = H5Ldelete(f->file_id, AO_2E_INT_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->ao_2e_int_group = H5Gcreate(f->file_id, AO_2E_INT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->ao_2e_int_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_mo (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->mo_group);
  f->mo_group = 0;
  herr_t status = H5Ldelete(f->file_id, MO_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->mo_group = H5Gcreate(f->file_id, MO_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->mo_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_mo_1e_int (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->mo_1e_int_group);
  f->mo_1e_int_group = 0;
  herr_t status = H5Ldelete(f->file_id, MO_1E_INT_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->mo_1e_int_group = H5Gcreate(f->file_id, MO_1E_INT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->mo_1e_int_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_mo_2e_int (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->mo_2e_int_group);
  f->mo_2e_int_group = 0;
  herr_t status = H5Ldelete(f->file_id, MO_2E_INT_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->mo_2e_int_group = H5Gcreate(f->file_id, MO_2E_INT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->mo_2e_int_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_determinant (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->determinant_group);
  f->determinant_group = 0;
  herr_t status = H5Ldelete(f->file_id, DETERMINANT_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->determinant_group = H5Gcreate(f->file_id, DETERMINANT_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->determinant_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_csf (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->csf_group);
  f->csf_group = 0;
  herr_t status = H5Ldelete(f->file_id, CSF_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->csf_group = H5Gcreate(f->file_id, CSF_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->csf_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_amplitude (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->amplitude_group);
  f->amplitude_group = 0;
  herr_t status = H5Ldelete(f->file_id, AMPLITUDE_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->amplitude_group = H5Gcreate(f->file_id, AMPLITUDE_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->amplitude_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_rdm (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->rdm_group);
  f->rdm_group = 0;
  herr_t status = H5Ldelete(f->file_id, RDM_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->rdm_group = H5Gcreate(f->file_id, RDM_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->rdm_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_jastrow (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->jastrow_group);
  f->jastrow_group = 0;
  herr_t status = H5Ldelete(f->file_id, JASTROW_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->jastrow_group = H5Gcreate(f->file_id, JASTROW_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->jastrow_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code
trexio_hdf5_delete_qmc (trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  // delete the link to the existing group: this should free the associated space
  H5Gclose(f->qmc_group);
  f->qmc_group = 0;
  herr_t status = H5Ldelete(f->file_id, QMC_GROUP_NAME, H5P_DEFAULT);
  if (status < 0) return TREXIO_FAILURE;

  // re-create the group (with the new link ?)
  f->qmc_group = H5Gcreate(f->file_id, QMC_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  if (f->qmc_group <= 0L) return TREXIO_INVALID_ID;

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_hdf5_has_determinant_list(trexio_t* const file)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  if (f->determinant_group == (hsize_t) 0) return TREXIO_HAS_NOT;

  htri_t exists = H5Lexists(f->determinant_group, "determinant_list", H5P_DEFAULT);
  if (exists > 0) {
    return TREXIO_SUCCESS;
  } else if (exists < 0) {
    return TREXIO_FAILURE;
  } else {
    return TREXIO_HAS_NOT;
  }
}
trexio_exit_code trexio_hdf5_read_determinant_list(trexio_t* const file,
                                                   const int64_t offset_file,
                                                   const uint32_t rank,
                                                   const uint64_t* dims,
                                                   int64_t* const eof_read_size,
                                                   int64_t* const list)
{
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (rank < 2) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (eof_read_size == NULL) return TREXIO_INVALID_ARG_5;
  if (list == NULL) return TREXIO_INVALID_ARG_6;

  const trexio_hdf5_t* f = (const trexio_hdf5_t*) file;

  char dset_det_name[256] = "determinant_list";

  hsize_t offset[1] = {(hsize_t) offset_file * dims[1]};
  hsize_t count[1]  = {(hsize_t) dims[0] * dims[1]};

  /* Attempt to read determinants (if EOF -> eof_read_size is modified with the number of elements read and return code is TREXIO_END)
     0 argument below is requires to skip internal treatment specific to sparse indices (i.e. their de-compression).*/
  return trexio_hdf5_open_read_dset_sparse(f->determinant_group, dset_det_name, (uint32_t) dims[1], offset, count, eof_read_size, 0, list);
}
trexio_exit_code trexio_hdf5_write_determinant_list(trexio_t* const file,
                                                    const int64_t offset_file,
		                                    const uint32_t rank,
                                                    const uint64_t* dims,
                                                    const int64_t* list)
{

  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (offset_file < 0) return TREXIO_INVALID_ARG_2;
  if (rank < 2) return TREXIO_INVALID_ARG_3;
  if (dims == NULL) return TREXIO_INVALID_ARG_4;
  if (list == NULL) return TREXIO_INVALID_ARG_5;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  hid_t det_dtype = H5T_NATIVE_INT64;
  uint64_t size_ranked = dims[1]*dims[0];

  /* Arrays of chunk dims that will be used for chunking the dataset */
  const hsize_t chunk_dims[1] = {size_ranked};

  /* Indices and values are stored as 2 independent datasets in the HDF5 file */
  char dset_det_name[256] = "determinant_list";

  trexio_exit_code rc_write = TREXIO_FAILURE;
  /* NOTE: chunk size is set upon creation of the HDF5 dataset and cannot be changed ! */
  if ( trexio_hdf5_has_determinant_list(file) == TREXIO_HAS_NOT ) {
  /* If the file does not exist -> create it and write */

  /* Create chunked dataset with det_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_create_write_dset_sparse(f->determinant_group, dset_det_name, det_dtype, chunk_dims, list);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  } else {
  /* If the file exists -> open it and write */
    hsize_t offset_data[1] = {(hsize_t) offset_file * dims[1]};

  /* Create chunked dataset with det_dtype datatype and write indices into it */
    rc_write = trexio_hdf5_open_write_dset_sparse(f->determinant_group, dset_det_name, det_dtype, chunk_dims, offset_data, list);
    if (rc_write != TREXIO_SUCCESS) return rc_write;

  }

  return TREXIO_SUCCESS;
}
trexio_exit_code
trexio_hdf5_create_write_dset_sparse (const hid_t group_id,
                                      const char* dset_name,
                                      const hid_t dtype_id,
                                      const hsize_t* chunk_dims,
                                      const void* data_sparse)
{
  assert (chunk_dims != NULL);
  assert (data_sparse != NULL);
  assert (dset_name != NULL);
  const int h5_rank = 1;
  const hsize_t maxdims[1] = {H5S_UNLIMITED};

  hid_t dspace = H5Screate_simple(h5_rank, chunk_dims, maxdims);
  if (dspace < 0) return TREXIO_INVALID_ID;

  hid_t prop = H5Pcreate(H5P_DATASET_CREATE);
  if (prop < 0) {
    H5Sclose(dspace);
    return TREXIO_INVALID_ID;
  }

  herr_t status = H5Pset_chunk(prop, h5_rank, chunk_dims);
  if (status < 0) {
    H5Sclose(dspace);
    H5Pclose(prop);
    return TREXIO_INVALID_ID;
  }

  hid_t dset_id = H5Dcreate(group_id,
                            dset_name,
                            dtype_id,
                            dspace,
                            H5P_DEFAULT,
                            prop,
                            H5P_DEFAULT);
  if (dset_id < 0) {
    H5Sclose(dspace);
    H5Pclose(prop);
    return TREXIO_INVALID_ID;
  }

  status = H5Dwrite(dset_id,
                    dtype_id,
                    H5S_ALL, H5S_ALL, H5P_DEFAULT,
                    data_sparse);
  H5Sclose(dspace);
  H5Pclose(prop);
  H5Dclose(dset_id);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}


trexio_exit_code
trexio_hdf5_open_write_dset_sparse (const hid_t group_id,
                                    const char* dset_name,
                                    const hid_t dtype_id,
                                    const hsize_t* chunk_dims,
                                    const hsize_t* offset_file,
                                    const void* data_sparse)
{
  const int h5_rank = 1;

  hid_t dset_id = H5Dopen(group_id, dset_name, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  hid_t fspace = H5Dget_space(dset_id);
  if (fspace < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // allocate space for the dimensions to be read
  hsize_t ddims[1] = {0};

  // get the rank and dimensions of the dataset
  int rrank = H5Sget_simple_extent_dims(fspace, ddims, NULL);
  if (rrank != h5_rank) {
    H5Sclose(fspace);
    H5Dclose(dset_id);
    return TREXIO_FAILURE;
  }

  ddims[0] += chunk_dims[0];

  // extend the dset size
  herr_t status  = H5Dset_extent(dset_id, ddims);
  if (status < 0) {
    H5Sclose(fspace);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // close and reopen the file dataspace to take into account the extension
  H5Sclose(fspace);
  fspace = H5Dget_space(dset_id);
  if (fspace < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // select hyperslab to be written using chunk_dims and offset values
  status = H5Sselect_hyperslab(fspace, H5S_SELECT_SET, offset_file, NULL, chunk_dims, NULL);
  if (status < 0) {
    H5Sclose(fspace);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  // create memory dataspace to write from
  hid_t dspace = H5Screate_simple(h5_rank, chunk_dims, NULL);
  if (dspace < 0) {
    H5Sclose(fspace);
    H5Sclose(dspace);
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  status = H5Dwrite(dset_id,
                    dtype_id,
                    dspace, fspace, H5P_DEFAULT,
                    data_sparse);
  H5Dclose(dset_id);
  H5Sclose(dspace);
  H5Sclose(fspace);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}


trexio_exit_code
trexio_hdf5_open_read_dset_sparse (const hid_t group_id,
                                   const char* dset_name,
                                   const uint32_t dset_rank,
                                   const hsize_t* offset_file,
                                   hsize_t* const size_read,
                                   int64_t* const eof_read_size,
                                   const int is_index,
                                   void* const data_sparse
                                   )
{
  const int h5_rank = 1;
  if (dset_rank == 0) return TREXIO_INVALID_ARG_3;

  // get the dataset handle
  hid_t dset_id = H5Dopen(group_id, dset_name, H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID;

  // get the dataspace of the dataset
  hid_t fspace_id = H5Dget_space(dset_id);
  if (fspace_id < 0) {
    H5Dclose(dset_id);
    return TREXIO_INVALID_ID;
  }

  /* get dims of the dset stored in the file to check whether reading with user-provided chunk size
     will reach end of the dataset (i.e. EOF in TEXT back end)
   */
  hsize_t ddims[1] = {0};
  int rrank = H5Sget_simple_extent_dims(fspace_id, ddims, NULL);
  if (rrank != h5_rank) {
    H5Sclose(fspace_id);
    H5Dclose(dset_id);
    return TREXIO_FAILURE;
  }

  hsize_t max_offset = offset_file[0] + size_read[0];

  int is_EOF = 0;
  // if max_offset exceed current dim of the dset => EOF
  if (max_offset > ddims[0]) {
    is_EOF = 1;
    // lower the value of count to reduce the number of elements which will be read
    size_read[0] -= (max_offset - ddims[0]);
    // modified the value of eof_read_size passed by address
    if (eof_read_size != NULL) *eof_read_size = size_read[0]/dset_rank;
  }

  // special case when reading int indices
  uint64_t size_ranked = (uint64_t) size_read[0];
  void* index_p = NULL;
  // read the datatype from the dataset and compare with the pre-defined values
  hid_t dtype = H5Dget_type(dset_id);
  if (is_index == 1) {
    if (H5Tequal(dtype, H5T_NATIVE_UINT8) > 0) {
      uint8_t* index = CALLOC(size_ranked, uint8_t);
      if (index == NULL) return TREXIO_ALLOCATION_FAILED;
      index_p = index;
    } else if (H5Tequal(dtype, H5T_NATIVE_UINT16) > 0) {
      uint16_t* index = CALLOC(size_ranked, uint16_t);
      if (index == NULL) return TREXIO_ALLOCATION_FAILED;
      index_p = index;
    }
  }

  herr_t status = H5Sselect_hyperslab(fspace_id, H5S_SELECT_SET, offset_file, NULL, size_read, NULL);
  if (status < 0) {
    H5Sclose(fspace_id);
    H5Dclose(dset_id);
    if (index_p != NULL) FREE(index_p);
    return TREXIO_INVALID_ID;
  }

  hid_t memspace_id = H5Screate_simple(h5_rank, size_read, NULL);
  if (memspace_id < 0) {
    H5Sclose(fspace_id);
    H5Dclose(dset_id);
    if (index_p != NULL) FREE(index_p);
    return TREXIO_INVALID_ID;
  }

  if (is_index == 1) {
    if (index_p != NULL) {
      status = H5Dread(dset_id,
                       dtype,
                       memspace_id, fspace_id, H5P_DEFAULT,
                       index_p);
    } else {
      status = H5Dread(dset_id,
                       dtype,
                       memspace_id, fspace_id, H5P_DEFAULT,
                       data_sparse);
    }
  } else {
    status = H5Dread(dset_id,
                     dtype,
                     memspace_id, fspace_id, H5P_DEFAULT,
                     data_sparse);
  }

  H5Sclose(fspace_id);
  H5Sclose(memspace_id);
  H5Dclose(dset_id);
  if (status < 0) {
    if (index_p != NULL) FREE(index_p);
    return TREXIO_FAILURE;
  }

  if (is_index == 1) {
    if (H5Tequal(dtype, H5T_NATIVE_UINT8) > 0) {
      uint8_t* index = (uint8_t*) index_p;
      for (uint64_t i=0; i<size_ranked; ++i){
        ((int32_t*)data_sparse)[i] = (int32_t) index[i];
      }
      FREE(index_p);
    } else if (H5Tequal(dtype, H5T_NATIVE_UINT16) > 0) {
      uint16_t* index = (uint16_t*) index_p;
      for (uint64_t i=0; i<size_ranked; ++i){
        ((int32_t*)data_sparse)[i] = (int32_t) index[i];
      }
      FREE(index_p);
    }
  }

  if (is_EOF == 1) return TREXIO_END;

  return TREXIO_SUCCESS;
}
#endif
