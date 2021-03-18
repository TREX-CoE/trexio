/* This file was generated from the org-mode file.
   To generate it, open templator_hdf5.org file in Emacs and execute
   M-x org-babel-tangle
*/

#include "trexio_hdf5.h"
#define NUCLEUS_GROUP_NAME          "nucleus"
#define ECP_GROUP_NAME          "ecp"
#define NUCLEUS_NUM_NAME            "nucleus_num"
#define ECP_LOCAL_NUM_N_MAX_NAME            "ecp_local_num_n_max"
#define ECP_NON_LOCAL_NUM_N_MAX_NAME            "ecp_non_local_num_n_max"
#define NUCLEUS_CHARGE_NAME   "nucleus_charge"
#define NUCLEUS_COORD_NAME   "nucleus_coord"
#define ECP_LMAX_PLUS_1_NAME   "ecp_lmax_plus_1"
#define ECP_Z_CORE_NAME   "ecp_z_core"
#define ECP_LOCAL_N_NAME   "ecp_local_n"
#define ECP_LOCAL_EXPONENT_NAME   "ecp_local_exponent"
#define ECP_LOCAL_COEF_NAME   "ecp_local_coef"
#define ECP_LOCAL_POWER_NAME   "ecp_local_power"
#define ECP_NON_LOCAL_N_NAME   "ecp_non_local_n"
#define ECP_NON_LOCAL_EXPONENT_NAME   "ecp_non_local_exponent"
#define ECP_NON_LOCAL_COEF_NAME   "ecp_non_local_coef"
#define ECP_NON_LOCAL_POWER_NAME   "ecp_non_local_power"
trexio_exit_code trexio_hdf5_init(trexio_t* file) {

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

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
    case 'a': 
      // appending the existing file -> open as RDWR
      f->file_id = H5Fopen(file->file_name, H5F_ACC_RDWR, H5P_DEFAULT);
      break;
    case 'w': 
      // writing the existing file -> overwrite it (_TRUNC) [_EXCL | H5F_ACC_DEBUG as an alternative]
      f->file_id = H5Fcreate(file->file_name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
      break;
    }  

  } else {

    switch (file->mode) {
    case 'r': 
    case 'a': 
      // reading or appending non-existing file -> error
      return TREXIO_FAILURE;
    case 'w': 
      // writing non-existing file -> create it
      f->file_id = H5Fcreate(file->file_name, H5F_ACC_EXCL, H5P_DEFAULT, H5P_DEFAULT);
      break;
    }  

  }  

  /* Create or open groups in the hdf5 file assuming that they exist if file exists */    
  switch (file->mode) {
    // the switch for 'r'/'a' is reached only if file exists
    case 'r':
    case 'a': 
      f->nucleus_group = H5Gopen(f->file_id, NUCLEUS_GROUP_NAME, H5P_DEFAULT);
      f->ecp_group = H5Gopen(f->file_id, ECP_GROUP_NAME, H5P_DEFAULT);
      //f->electron_group = H5Gopen(f->file_id, ELECTRON_GROUP_NAME, H5P_DEFAULT); 
      break;
    case 'w':
      f->nucleus_group = H5Gcreate(f->file_id, NUCLEUS_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
      f->ecp_group = H5Gcreate(f->file_id, ECP_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
      //f->electron_group = H5Gcreate(f->file_id, ELECTRON_GROUP_NAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
      break;
  }
  assert (f->nucleus_group > 0L);
  assert (f->ecp_group > 0L);
  //assert (f->electron_group > 0L);

  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_hdf5_finalize(trexio_t* file) {

  trexio_hdf5_t* f = (trexio_hdf5_t*) file;

  H5Gclose(f->nucleus_group);
  H5Gclose(f->ecp_group);
  f->nucleus_group = 0;
  f->ecp_group = 0;

/*
  H5Gclose(f->electron_group);
  f->electron_group = 0; 
*/

  H5Fclose(f->file_id);
  f->file_id = 0;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_nucleus_charge(const trexio_t* file, double* nucleus_charge, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (nucleus_charge != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  
  herr_t status;
  int rrank;
  // get the rank of the dataset in a file
  status = H5LTget_dataset_ndims (f->nucleus_group, NUCLEUS_CHARGE_NAME, 
                                  &rrank);

  if (status < 0) return TREXIO_FAILURE;

  if (rrank != (int) rank) return TREXIO_INVALID_ARG_3;

  // open the dataset to get its dimensions  
  hid_t dset_id = H5Dopen(f->nucleus_group, NUCLEUS_CHARGE_NAME,  H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID; 

  // allocate space for the dimensions to be read
  hsize_t* ddims = (hsize_t*) calloc( (int) rank, sizeof(hsize_t));
  if (ddims == NULL) return TREXIO_FAILURE;

  // read dimensions from the existing dataset
  status = H5LDget_dset_dims(dset_id, ddims);

  H5Dclose(dset_id);
  if (status < 0) {
    free(ddims);
    return TREXIO_FAILURE;
  }

  for (uint32_t i=0; i<rank; i++){
     if (ddims[i] != dims[i]) {
       free(ddims);
       return TREXIO_INVALID_ARG_4;
     }
  }
  free(ddims);

  /* High-level H5LT API. No need to deal with dataspaces and datatypes */
  status = H5LTread_dataset_double(f->nucleus_group,
                                    NUCLEUS_CHARGE_NAME,
                                    nucleus_charge);				   
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_nucleus_coord(const trexio_t* file, double* nucleus_coord, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (nucleus_coord != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  
  herr_t status;
  int rrank;
  // get the rank of the dataset in a file
  status = H5LTget_dataset_ndims (f->nucleus_group, NUCLEUS_COORD_NAME, 
                                  &rrank);

  if (status < 0) return TREXIO_FAILURE;

  if (rrank != (int) rank) return TREXIO_INVALID_ARG_3;

  // open the dataset to get its dimensions  
  hid_t dset_id = H5Dopen(f->nucleus_group, NUCLEUS_COORD_NAME,  H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID; 

  // allocate space for the dimensions to be read
  hsize_t* ddims = (hsize_t*) calloc( (int) rank, sizeof(hsize_t));
  if (ddims == NULL) return TREXIO_FAILURE;

  // read dimensions from the existing dataset
  status = H5LDget_dset_dims(dset_id, ddims);

  H5Dclose(dset_id);
  if (status < 0) {
    free(ddims);
    return TREXIO_FAILURE;
  }

  for (uint32_t i=0; i<rank; i++){
     if (ddims[i] != dims[i]) {
       free(ddims);
       return TREXIO_INVALID_ARG_4;
     }
  }
  free(ddims);

  /* High-level H5LT API. No need to deal with dataspaces and datatypes */
  status = H5LTread_dataset_double(f->nucleus_group,
                                    NUCLEUS_COORD_NAME,
                                    nucleus_coord);				   
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_ecp_lmax_plus_1(const trexio_t* file, int64_t* ecp_lmax_plus_1, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_lmax_plus_1 != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  
  herr_t status;
  int rrank;
  // get the rank of the dataset in a file
  status = H5LTget_dataset_ndims (f->ecp_group, ECP_LMAX_PLUS_1_NAME, 
                                  &rrank);

  if (status < 0) return TREXIO_FAILURE;

  if (rrank != (int) rank) return TREXIO_INVALID_ARG_3;

  // open the dataset to get its dimensions  
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_LMAX_PLUS_1_NAME,  H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID; 

  // allocate space for the dimensions to be read
  hsize_t* ddims = (hsize_t*) calloc( (int) rank, sizeof(hsize_t));
  if (ddims == NULL) return TREXIO_FAILURE;

  // read dimensions from the existing dataset
  status = H5LDget_dset_dims(dset_id, ddims);

  H5Dclose(dset_id);
  if (status < 0) {
    free(ddims);
    return TREXIO_FAILURE;
  }

  for (uint32_t i=0; i<rank; i++){
     if (ddims[i] != dims[i]) {
       free(ddims);
       return TREXIO_INVALID_ARG_4;
     }
  }
  free(ddims);

  /* High-level H5LT API. No need to deal with dataspaces and datatypes */
  status = H5LTread_dataset_long(f->ecp_group,
                                    ECP_LMAX_PLUS_1_NAME,
                                    ecp_lmax_plus_1);				   
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_ecp_z_core(const trexio_t* file, int64_t* ecp_z_core, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_z_core != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  
  herr_t status;
  int rrank;
  // get the rank of the dataset in a file
  status = H5LTget_dataset_ndims (f->ecp_group, ECP_Z_CORE_NAME, 
                                  &rrank);

  if (status < 0) return TREXIO_FAILURE;

  if (rrank != (int) rank) return TREXIO_INVALID_ARG_3;

  // open the dataset to get its dimensions  
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_Z_CORE_NAME,  H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID; 

  // allocate space for the dimensions to be read
  hsize_t* ddims = (hsize_t*) calloc( (int) rank, sizeof(hsize_t));
  if (ddims == NULL) return TREXIO_FAILURE;

  // read dimensions from the existing dataset
  status = H5LDget_dset_dims(dset_id, ddims);

  H5Dclose(dset_id);
  if (status < 0) {
    free(ddims);
    return TREXIO_FAILURE;
  }

  for (uint32_t i=0; i<rank; i++){
     if (ddims[i] != dims[i]) {
       free(ddims);
       return TREXIO_INVALID_ARG_4;
     }
  }
  free(ddims);

  /* High-level H5LT API. No need to deal with dataspaces and datatypes */
  status = H5LTread_dataset_long(f->ecp_group,
                                    ECP_Z_CORE_NAME,
                                    ecp_z_core);				   
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_ecp_local_n(const trexio_t* file, int64_t* ecp_local_n, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_local_n != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  
  herr_t status;
  int rrank;
  // get the rank of the dataset in a file
  status = H5LTget_dataset_ndims (f->ecp_group, ECP_LOCAL_N_NAME, 
                                  &rrank);

  if (status < 0) return TREXIO_FAILURE;

  if (rrank != (int) rank) return TREXIO_INVALID_ARG_3;

  // open the dataset to get its dimensions  
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_LOCAL_N_NAME,  H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID; 

  // allocate space for the dimensions to be read
  hsize_t* ddims = (hsize_t*) calloc( (int) rank, sizeof(hsize_t));
  if (ddims == NULL) return TREXIO_FAILURE;

  // read dimensions from the existing dataset
  status = H5LDget_dset_dims(dset_id, ddims);

  H5Dclose(dset_id);
  if (status < 0) {
    free(ddims);
    return TREXIO_FAILURE;
  }

  for (uint32_t i=0; i<rank; i++){
     if (ddims[i] != dims[i]) {
       free(ddims);
       return TREXIO_INVALID_ARG_4;
     }
  }
  free(ddims);

  /* High-level H5LT API. No need to deal with dataspaces and datatypes */
  status = H5LTread_dataset_long(f->ecp_group,
                                    ECP_LOCAL_N_NAME,
                                    ecp_local_n);				   
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_ecp_local_exponent(const trexio_t* file, double* ecp_local_exponent, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_local_exponent != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  
  herr_t status;
  int rrank;
  // get the rank of the dataset in a file
  status = H5LTget_dataset_ndims (f->ecp_group, ECP_LOCAL_EXPONENT_NAME, 
                                  &rrank);

  if (status < 0) return TREXIO_FAILURE;

  if (rrank != (int) rank) return TREXIO_INVALID_ARG_3;

  // open the dataset to get its dimensions  
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_LOCAL_EXPONENT_NAME,  H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID; 

  // allocate space for the dimensions to be read
  hsize_t* ddims = (hsize_t*) calloc( (int) rank, sizeof(hsize_t));
  if (ddims == NULL) return TREXIO_FAILURE;

  // read dimensions from the existing dataset
  status = H5LDget_dset_dims(dset_id, ddims);

  H5Dclose(dset_id);
  if (status < 0) {
    free(ddims);
    return TREXIO_FAILURE;
  }

  for (uint32_t i=0; i<rank; i++){
     if (ddims[i] != dims[i]) {
       free(ddims);
       return TREXIO_INVALID_ARG_4;
     }
  }
  free(ddims);

  /* High-level H5LT API. No need to deal with dataspaces and datatypes */
  status = H5LTread_dataset_double(f->ecp_group,
                                    ECP_LOCAL_EXPONENT_NAME,
                                    ecp_local_exponent);				   
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_ecp_local_coef(const trexio_t* file, double* ecp_local_coef, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_local_coef != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  
  herr_t status;
  int rrank;
  // get the rank of the dataset in a file
  status = H5LTget_dataset_ndims (f->ecp_group, ECP_LOCAL_COEF_NAME, 
                                  &rrank);

  if (status < 0) return TREXIO_FAILURE;

  if (rrank != (int) rank) return TREXIO_INVALID_ARG_3;

  // open the dataset to get its dimensions  
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_LOCAL_COEF_NAME,  H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID; 

  // allocate space for the dimensions to be read
  hsize_t* ddims = (hsize_t*) calloc( (int) rank, sizeof(hsize_t));
  if (ddims == NULL) return TREXIO_FAILURE;

  // read dimensions from the existing dataset
  status = H5LDget_dset_dims(dset_id, ddims);

  H5Dclose(dset_id);
  if (status < 0) {
    free(ddims);
    return TREXIO_FAILURE;
  }

  for (uint32_t i=0; i<rank; i++){
     if (ddims[i] != dims[i]) {
       free(ddims);
       return TREXIO_INVALID_ARG_4;
     }
  }
  free(ddims);

  /* High-level H5LT API. No need to deal with dataspaces and datatypes */
  status = H5LTread_dataset_double(f->ecp_group,
                                    ECP_LOCAL_COEF_NAME,
                                    ecp_local_coef);				   
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_ecp_local_power(const trexio_t* file, int64_t* ecp_local_power, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_local_power != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  
  herr_t status;
  int rrank;
  // get the rank of the dataset in a file
  status = H5LTget_dataset_ndims (f->ecp_group, ECP_LOCAL_POWER_NAME, 
                                  &rrank);

  if (status < 0) return TREXIO_FAILURE;

  if (rrank != (int) rank) return TREXIO_INVALID_ARG_3;

  // open the dataset to get its dimensions  
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_LOCAL_POWER_NAME,  H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID; 

  // allocate space for the dimensions to be read
  hsize_t* ddims = (hsize_t*) calloc( (int) rank, sizeof(hsize_t));
  if (ddims == NULL) return TREXIO_FAILURE;

  // read dimensions from the existing dataset
  status = H5LDget_dset_dims(dset_id, ddims);

  H5Dclose(dset_id);
  if (status < 0) {
    free(ddims);
    return TREXIO_FAILURE;
  }

  for (uint32_t i=0; i<rank; i++){
     if (ddims[i] != dims[i]) {
       free(ddims);
       return TREXIO_INVALID_ARG_4;
     }
  }
  free(ddims);

  /* High-level H5LT API. No need to deal with dataspaces and datatypes */
  status = H5LTread_dataset_long(f->ecp_group,
                                    ECP_LOCAL_POWER_NAME,
                                    ecp_local_power);				   
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_ecp_non_local_n(const trexio_t* file, int64_t* ecp_non_local_n, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_non_local_n != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  
  herr_t status;
  int rrank;
  // get the rank of the dataset in a file
  status = H5LTget_dataset_ndims (f->ecp_group, ECP_NON_LOCAL_N_NAME, 
                                  &rrank);

  if (status < 0) return TREXIO_FAILURE;

  if (rrank != (int) rank) return TREXIO_INVALID_ARG_3;

  // open the dataset to get its dimensions  
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_NON_LOCAL_N_NAME,  H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID; 

  // allocate space for the dimensions to be read
  hsize_t* ddims = (hsize_t*) calloc( (int) rank, sizeof(hsize_t));
  if (ddims == NULL) return TREXIO_FAILURE;

  // read dimensions from the existing dataset
  status = H5LDget_dset_dims(dset_id, ddims);

  H5Dclose(dset_id);
  if (status < 0) {
    free(ddims);
    return TREXIO_FAILURE;
  }

  for (uint32_t i=0; i<rank; i++){
     if (ddims[i] != dims[i]) {
       free(ddims);
       return TREXIO_INVALID_ARG_4;
     }
  }
  free(ddims);

  /* High-level H5LT API. No need to deal with dataspaces and datatypes */
  status = H5LTread_dataset_long(f->ecp_group,
                                    ECP_NON_LOCAL_N_NAME,
                                    ecp_non_local_n);				   
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_ecp_non_local_exponent(const trexio_t* file, double* ecp_non_local_exponent, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_non_local_exponent != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  
  herr_t status;
  int rrank;
  // get the rank of the dataset in a file
  status = H5LTget_dataset_ndims (f->ecp_group, ECP_NON_LOCAL_EXPONENT_NAME, 
                                  &rrank);

  if (status < 0) return TREXIO_FAILURE;

  if (rrank != (int) rank) return TREXIO_INVALID_ARG_3;

  // open the dataset to get its dimensions  
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_NON_LOCAL_EXPONENT_NAME,  H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID; 

  // allocate space for the dimensions to be read
  hsize_t* ddims = (hsize_t*) calloc( (int) rank, sizeof(hsize_t));
  if (ddims == NULL) return TREXIO_FAILURE;

  // read dimensions from the existing dataset
  status = H5LDget_dset_dims(dset_id, ddims);

  H5Dclose(dset_id);
  if (status < 0) {
    free(ddims);
    return TREXIO_FAILURE;
  }

  for (uint32_t i=0; i<rank; i++){
     if (ddims[i] != dims[i]) {
       free(ddims);
       return TREXIO_INVALID_ARG_4;
     }
  }
  free(ddims);

  /* High-level H5LT API. No need to deal with dataspaces and datatypes */
  status = H5LTread_dataset_double(f->ecp_group,
                                    ECP_NON_LOCAL_EXPONENT_NAME,
                                    ecp_non_local_exponent);				   
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_ecp_non_local_coef(const trexio_t* file, double* ecp_non_local_coef, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_non_local_coef != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  
  herr_t status;
  int rrank;
  // get the rank of the dataset in a file
  status = H5LTget_dataset_ndims (f->ecp_group, ECP_NON_LOCAL_COEF_NAME, 
                                  &rrank);

  if (status < 0) return TREXIO_FAILURE;

  if (rrank != (int) rank) return TREXIO_INVALID_ARG_3;

  // open the dataset to get its dimensions  
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_NON_LOCAL_COEF_NAME,  H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID; 

  // allocate space for the dimensions to be read
  hsize_t* ddims = (hsize_t*) calloc( (int) rank, sizeof(hsize_t));
  if (ddims == NULL) return TREXIO_FAILURE;

  // read dimensions from the existing dataset
  status = H5LDget_dset_dims(dset_id, ddims);

  H5Dclose(dset_id);
  if (status < 0) {
    free(ddims);
    return TREXIO_FAILURE;
  }

  for (uint32_t i=0; i<rank; i++){
     if (ddims[i] != dims[i]) {
       free(ddims);
       return TREXIO_INVALID_ARG_4;
     }
  }
  free(ddims);

  /* High-level H5LT API. No need to deal with dataspaces and datatypes */
  status = H5LTread_dataset_double(f->ecp_group,
                                    ECP_NON_LOCAL_COEF_NAME,
                                    ecp_non_local_coef);				   
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_ecp_non_local_power(const trexio_t* file, int64_t* ecp_non_local_power, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_non_local_power != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  
  herr_t status;
  int rrank;
  // get the rank of the dataset in a file
  status = H5LTget_dataset_ndims (f->ecp_group, ECP_NON_LOCAL_POWER_NAME, 
                                  &rrank);

  if (status < 0) return TREXIO_FAILURE;

  if (rrank != (int) rank) return TREXIO_INVALID_ARG_3;

  // open the dataset to get its dimensions  
  hid_t dset_id = H5Dopen(f->ecp_group, ECP_NON_LOCAL_POWER_NAME,  H5P_DEFAULT);
  if (dset_id <= 0) return TREXIO_INVALID_ID; 

  // allocate space for the dimensions to be read
  hsize_t* ddims = (hsize_t*) calloc( (int) rank, sizeof(hsize_t));
  if (ddims == NULL) return TREXIO_FAILURE;

  // read dimensions from the existing dataset
  status = H5LDget_dset_dims(dset_id, ddims);

  H5Dclose(dset_id);
  if (status < 0) {
    free(ddims);
    return TREXIO_FAILURE;
  }

  for (uint32_t i=0; i<rank; i++){
     if (ddims[i] != dims[i]) {
       free(ddims);
       return TREXIO_INVALID_ARG_4;
     }
  }
  free(ddims);

  /* High-level H5LT API. No need to deal with dataspaces and datatypes */
  status = H5LTread_dataset_long(f->ecp_group,
                                    ECP_NON_LOCAL_POWER_NAME,
                                    ecp_non_local_power);				   
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_nucleus_num (const trexio_t* file, uint64_t* num) {

  assert (file != NULL);
  assert (num  != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->nucleus_group, NUCLEUS_NUM_NAME) == 0) return TREXIO_FAILURE;

  /* Read the nucleus_num attribute of nucleus group */
  hid_t num_id = H5Aopen(f->nucleus_group, NUCLEUS_NUM_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  herr_t status = H5Aread(num_id, H5T_NATIVE_ULLONG, num);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_ecp_local_num_n_max (const trexio_t* file, uint64_t* num) {

  assert (file != NULL);
  assert (num  != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->ecp_group, ECP_LOCAL_NUM_N_MAX_NAME) == 0) return TREXIO_FAILURE;

  /* Read the nucleus_num attribute of nucleus group */
  hid_t num_id = H5Aopen(f->ecp_group, ECP_LOCAL_NUM_N_MAX_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  herr_t status = H5Aread(num_id, H5T_NATIVE_ULLONG, num);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_read_ecp_non_local_num_n_max (const trexio_t* file, uint64_t* num) {

  assert (file != NULL);
  assert (num  != NULL);
  
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  /* Quit if the dimensioning attribute is missing in the file */
  if (H5Aexists(f->ecp_group, ECP_NON_LOCAL_NUM_N_MAX_NAME) == 0) return TREXIO_FAILURE;

  /* Read the nucleus_num attribute of nucleus group */
  hid_t num_id = H5Aopen(f->ecp_group, ECP_NON_LOCAL_NUM_N_MAX_NAME, H5P_DEFAULT);
  if (num_id <= 0) return TREXIO_INVALID_ID;

  herr_t status = H5Aread(num_id, H5T_NATIVE_ULLONG, num);
  if (status < 0) return TREXIO_FAILURE;

  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_nucleus_charge(const trexio_t* file, const double* nucleus_charge, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (nucleus_charge != NULL);
    
  trexio_exit_code rc;
  uint64_t nucleus_num;
  // error handling for rc is added by the generator
  rc = trexio_hdf5_read_nucleus_num(file, &(nucleus_num)); 
  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file; 

  herr_t status;
  if ( H5LTfind_dataset(f->nucleus_group, NUCLEUS_CHARGE_NAME) != 1) { 
    
    status = H5LTmake_dataset_double (f->nucleus_group, NUCLEUS_CHARGE_NAME, 
                                      (int) rank, (hsize_t*) dims, nucleus_charge);
    if (status < 0) return TREXIO_FAILURE;

  } else {   

    hid_t dset_id = H5Dopen(f->nucleus_group, NUCLEUS_CHARGE_NAME, H5P_DEFAULT);
    if (dset_id <= 0) return TREXIO_INVALID_ID;
    
    status = H5Dwrite(dset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, nucleus_charge);
    
    H5Dclose(dset_id);
    if (status < 0) return TREXIO_FAILURE;

  }
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_nucleus_coord(const trexio_t* file, const double* nucleus_coord, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (nucleus_coord != NULL);
    
  trexio_exit_code rc;
  uint64_t nucleus_num;
  // error handling for rc is added by the generator
  rc = trexio_hdf5_read_nucleus_num(file, &(nucleus_num)); 
  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file; 

  herr_t status;
  if ( H5LTfind_dataset(f->nucleus_group, NUCLEUS_COORD_NAME) != 1) { 
    
    status = H5LTmake_dataset_double (f->nucleus_group, NUCLEUS_COORD_NAME, 
                                      (int) rank, (hsize_t*) dims, nucleus_coord);
    if (status < 0) return TREXIO_FAILURE;

  } else {   

    hid_t dset_id = H5Dopen(f->nucleus_group, NUCLEUS_COORD_NAME, H5P_DEFAULT);
    if (dset_id <= 0) return TREXIO_INVALID_ID;
    
    status = H5Dwrite(dset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, nucleus_coord);
    
    H5Dclose(dset_id);
    if (status < 0) return TREXIO_FAILURE;

  }
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_ecp_lmax_plus_1(const trexio_t* file, const int64_t* ecp_lmax_plus_1, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_lmax_plus_1 != NULL);
    
  trexio_exit_code rc;
  uint64_t nucleus_num;
  // error handling for rc is added by the generator
  rc = trexio_hdf5_read_nucleus_num(file, &(nucleus_num)); 
  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file; 

  herr_t status;
  if ( H5LTfind_dataset(f->ecp_group, ECP_LMAX_PLUS_1_NAME) != 1) { 
    
    status = H5LTmake_dataset_long (f->ecp_group, ECP_LMAX_PLUS_1_NAME, 
                                      (int) rank, (hsize_t*) dims, ecp_lmax_plus_1);
    if (status < 0) return TREXIO_FAILURE;

  } else {   

    hid_t dset_id = H5Dopen(f->ecp_group, ECP_LMAX_PLUS_1_NAME, H5P_DEFAULT);
    if (dset_id <= 0) return TREXIO_INVALID_ID;
    
    status = H5Dwrite(dset_id, H5T_NATIVE_LONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, ecp_lmax_plus_1);
    
    H5Dclose(dset_id);
    if (status < 0) return TREXIO_FAILURE;

  }
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_ecp_z_core(const trexio_t* file, const int64_t* ecp_z_core, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_z_core != NULL);
    
  trexio_exit_code rc;
  uint64_t nucleus_num;
  // error handling for rc is added by the generator
  rc = trexio_hdf5_read_nucleus_num(file, &(nucleus_num)); 
  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file; 

  herr_t status;
  if ( H5LTfind_dataset(f->ecp_group, ECP_Z_CORE_NAME) != 1) { 
    
    status = H5LTmake_dataset_long (f->ecp_group, ECP_Z_CORE_NAME, 
                                      (int) rank, (hsize_t*) dims, ecp_z_core);
    if (status < 0) return TREXIO_FAILURE;

  } else {   

    hid_t dset_id = H5Dopen(f->ecp_group, ECP_Z_CORE_NAME, H5P_DEFAULT);
    if (dset_id <= 0) return TREXIO_INVALID_ID;
    
    status = H5Dwrite(dset_id, H5T_NATIVE_LONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, ecp_z_core);
    
    H5Dclose(dset_id);
    if (status < 0) return TREXIO_FAILURE;

  }
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_ecp_local_n(const trexio_t* file, const int64_t* ecp_local_n, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_local_n != NULL);
    
  trexio_exit_code rc;
  uint64_t nucleus_num;
  // error handling for rc is added by the generator
  rc = trexio_hdf5_read_nucleus_num(file, &(nucleus_num)); 
  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file; 

  herr_t status;
  if ( H5LTfind_dataset(f->ecp_group, ECP_LOCAL_N_NAME) != 1) { 
    
    status = H5LTmake_dataset_long (f->ecp_group, ECP_LOCAL_N_NAME, 
                                      (int) rank, (hsize_t*) dims, ecp_local_n);
    if (status < 0) return TREXIO_FAILURE;

  } else {   

    hid_t dset_id = H5Dopen(f->ecp_group, ECP_LOCAL_N_NAME, H5P_DEFAULT);
    if (dset_id <= 0) return TREXIO_INVALID_ID;
    
    status = H5Dwrite(dset_id, H5T_NATIVE_LONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, ecp_local_n);
    
    H5Dclose(dset_id);
    if (status < 0) return TREXIO_FAILURE;

  }
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_ecp_local_exponent(const trexio_t* file, const double* ecp_local_exponent, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_local_exponent != NULL);
    
  trexio_exit_code rc;
  uint64_t nucleus_num;
  uint64_t ecp_local_num_n_max;
  // error handling for rc is added by the generator
  rc = trexio_hdf5_read_nucleus_num(file, &(nucleus_num)); 
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_hdf5_read_ecp_local_num_n_max(file, &(ecp_local_num_n_max)); 
  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file; 

  herr_t status;
  if ( H5LTfind_dataset(f->ecp_group, ECP_LOCAL_EXPONENT_NAME) != 1) { 
    
    status = H5LTmake_dataset_double (f->ecp_group, ECP_LOCAL_EXPONENT_NAME, 
                                      (int) rank, (hsize_t*) dims, ecp_local_exponent);
    if (status < 0) return TREXIO_FAILURE;

  } else {   

    hid_t dset_id = H5Dopen(f->ecp_group, ECP_LOCAL_EXPONENT_NAME, H5P_DEFAULT);
    if (dset_id <= 0) return TREXIO_INVALID_ID;
    
    status = H5Dwrite(dset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, ecp_local_exponent);
    
    H5Dclose(dset_id);
    if (status < 0) return TREXIO_FAILURE;

  }
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_ecp_local_coef(const trexio_t* file, const double* ecp_local_coef, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_local_coef != NULL);
    
  trexio_exit_code rc;
  uint64_t nucleus_num;
  uint64_t ecp_local_num_n_max;
  // error handling for rc is added by the generator
  rc = trexio_hdf5_read_nucleus_num(file, &(nucleus_num)); 
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_hdf5_read_ecp_local_num_n_max(file, &(ecp_local_num_n_max)); 
  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file; 

  herr_t status;
  if ( H5LTfind_dataset(f->ecp_group, ECP_LOCAL_COEF_NAME) != 1) { 
    
    status = H5LTmake_dataset_double (f->ecp_group, ECP_LOCAL_COEF_NAME, 
                                      (int) rank, (hsize_t*) dims, ecp_local_coef);
    if (status < 0) return TREXIO_FAILURE;

  } else {   

    hid_t dset_id = H5Dopen(f->ecp_group, ECP_LOCAL_COEF_NAME, H5P_DEFAULT);
    if (dset_id <= 0) return TREXIO_INVALID_ID;
    
    status = H5Dwrite(dset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, ecp_local_coef);
    
    H5Dclose(dset_id);
    if (status < 0) return TREXIO_FAILURE;

  }
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_ecp_local_power(const trexio_t* file, const int64_t* ecp_local_power, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_local_power != NULL);
    
  trexio_exit_code rc;
  uint64_t nucleus_num;
  uint64_t ecp_local_num_n_max;
  // error handling for rc is added by the generator
  rc = trexio_hdf5_read_nucleus_num(file, &(nucleus_num)); 
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_hdf5_read_ecp_local_num_n_max(file, &(ecp_local_num_n_max)); 
  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file; 

  herr_t status;
  if ( H5LTfind_dataset(f->ecp_group, ECP_LOCAL_POWER_NAME) != 1) { 
    
    status = H5LTmake_dataset_long (f->ecp_group, ECP_LOCAL_POWER_NAME, 
                                      (int) rank, (hsize_t*) dims, ecp_local_power);
    if (status < 0) return TREXIO_FAILURE;

  } else {   

    hid_t dset_id = H5Dopen(f->ecp_group, ECP_LOCAL_POWER_NAME, H5P_DEFAULT);
    if (dset_id <= 0) return TREXIO_INVALID_ID;
    
    status = H5Dwrite(dset_id, H5T_NATIVE_LONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, ecp_local_power);
    
    H5Dclose(dset_id);
    if (status < 0) return TREXIO_FAILURE;

  }
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_ecp_non_local_n(const trexio_t* file, const int64_t* ecp_non_local_n, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_non_local_n != NULL);
    
  trexio_exit_code rc;
  uint64_t nucleus_num;
  // error handling for rc is added by the generator
  rc = trexio_hdf5_read_nucleus_num(file, &(nucleus_num)); 
  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file; 

  herr_t status;
  if ( H5LTfind_dataset(f->ecp_group, ECP_NON_LOCAL_N_NAME) != 1) { 
    
    status = H5LTmake_dataset_long (f->ecp_group, ECP_NON_LOCAL_N_NAME, 
                                      (int) rank, (hsize_t*) dims, ecp_non_local_n);
    if (status < 0) return TREXIO_FAILURE;

  } else {   

    hid_t dset_id = H5Dopen(f->ecp_group, ECP_NON_LOCAL_N_NAME, H5P_DEFAULT);
    if (dset_id <= 0) return TREXIO_INVALID_ID;
    
    status = H5Dwrite(dset_id, H5T_NATIVE_LONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, ecp_non_local_n);
    
    H5Dclose(dset_id);
    if (status < 0) return TREXIO_FAILURE;

  }
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_ecp_non_local_exponent(const trexio_t* file, const double* ecp_non_local_exponent, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_non_local_exponent != NULL);
    
  trexio_exit_code rc;
  uint64_t nucleus_num;
  uint64_t ecp_non_local_num_n_max;
  // error handling for rc is added by the generator
  rc = trexio_hdf5_read_nucleus_num(file, &(nucleus_num)); 
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_hdf5_read_ecp_non_local_num_n_max(file, &(ecp_non_local_num_n_max)); 
  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_non_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file; 

  herr_t status;
  if ( H5LTfind_dataset(f->ecp_group, ECP_NON_LOCAL_EXPONENT_NAME) != 1) { 
    
    status = H5LTmake_dataset_double (f->ecp_group, ECP_NON_LOCAL_EXPONENT_NAME, 
                                      (int) rank, (hsize_t*) dims, ecp_non_local_exponent);
    if (status < 0) return TREXIO_FAILURE;

  } else {   

    hid_t dset_id = H5Dopen(f->ecp_group, ECP_NON_LOCAL_EXPONENT_NAME, H5P_DEFAULT);
    if (dset_id <= 0) return TREXIO_INVALID_ID;
    
    status = H5Dwrite(dset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, ecp_non_local_exponent);
    
    H5Dclose(dset_id);
    if (status < 0) return TREXIO_FAILURE;

  }
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_ecp_non_local_coef(const trexio_t* file, const double* ecp_non_local_coef, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_non_local_coef != NULL);
    
  trexio_exit_code rc;
  uint64_t nucleus_num;
  uint64_t ecp_non_local_num_n_max;
  // error handling for rc is added by the generator
  rc = trexio_hdf5_read_nucleus_num(file, &(nucleus_num)); 
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_hdf5_read_ecp_non_local_num_n_max(file, &(ecp_non_local_num_n_max)); 
  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_non_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file; 

  herr_t status;
  if ( H5LTfind_dataset(f->ecp_group, ECP_NON_LOCAL_COEF_NAME) != 1) { 
    
    status = H5LTmake_dataset_double (f->ecp_group, ECP_NON_LOCAL_COEF_NAME, 
                                      (int) rank, (hsize_t*) dims, ecp_non_local_coef);
    if (status < 0) return TREXIO_FAILURE;

  } else {   

    hid_t dset_id = H5Dopen(f->ecp_group, ECP_NON_LOCAL_COEF_NAME, H5P_DEFAULT);
    if (dset_id <= 0) return TREXIO_INVALID_ID;
    
    status = H5Dwrite(dset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, ecp_non_local_coef);
    
    H5Dclose(dset_id);
    if (status < 0) return TREXIO_FAILURE;

  }
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_ecp_non_local_power(const trexio_t* file, const int64_t* ecp_non_local_power, const uint32_t rank, const uint64_t* dims) {

  assert (file != NULL);
  assert (ecp_non_local_power != NULL);
    
  trexio_exit_code rc;
  uint64_t nucleus_num;
  uint64_t ecp_non_local_num_n_max;
  // error handling for rc is added by the generator
  rc = trexio_hdf5_read_nucleus_num(file, &(nucleus_num)); 
  if (rc != TREXIO_SUCCESS) return rc;
  rc = trexio_hdf5_read_ecp_non_local_num_n_max(file, &(ecp_non_local_num_n_max)); 
  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_non_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  trexio_hdf5_t* f = (trexio_hdf5_t*) file; 

  herr_t status;
  if ( H5LTfind_dataset(f->ecp_group, ECP_NON_LOCAL_POWER_NAME) != 1) { 
    
    status = H5LTmake_dataset_long (f->ecp_group, ECP_NON_LOCAL_POWER_NAME, 
                                      (int) rank, (hsize_t*) dims, ecp_non_local_power);
    if (status < 0) return TREXIO_FAILURE;

  } else {   

    hid_t dset_id = H5Dopen(f->ecp_group, ECP_NON_LOCAL_POWER_NAME, H5P_DEFAULT);
    if (dset_id <= 0) return TREXIO_INVALID_ID;
    
    status = H5Dwrite(dset_id, H5T_NATIVE_LONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, ecp_non_local_power);
    
    H5Dclose(dset_id);
    if (status < 0) return TREXIO_FAILURE;

  }
  
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_hdf5_write_nucleus_num (const trexio_t* file, const uint64_t num) {

  assert (file != NULL);
  assert (num > 0L);
 
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  hid_t num_id;
  herr_t status;
  /* Write the dimensioning variables */
  hid_t dtype = H5Tcopy(H5T_NATIVE_ULLONG);

  if (H5Aexists(f->nucleus_group, NUCLEUS_NUM_NAME) == 0) {
   
    hid_t dspace = H5Screate(H5S_SCALAR);

    num_id = H5Acreate(f->nucleus_group, NUCLEUS_NUM_NAME, dtype, dspace,
                     H5P_DEFAULT, H5P_DEFAULT);
    if (num_id <= 0) return TREXIO_INVALID_ID;
  
    status = H5Awrite(num_id, dtype, &(num));
    if (status < 0) return TREXIO_FAILURE;

    H5Sclose(dspace);
    
  } else {

    uint64_t infile_num;
    trexio_exit_code rc = trexio_hdf5_read_nucleus_num(file, &(infile_num));
    if (rc != TREXIO_SUCCESS) return rc;

    if (infile_num != num) {

      if (infile_num != 0) {
        printf("%ld -> %ld %s \n", num, infile_num, 
	       "This variable already exists. Overwriting it is not supported");
        H5Tclose(dtype);
        return TREXIO_FAILURE;

      } else {
    
        num_id = H5Aopen(f->nucleus_group, NUCLEUS_NUM_NAME, H5P_DEFAULT);
        if (num_id <= 0) return TREXIO_INVALID_ID;
       
        status = H5Awrite(num_id, dtype, &(num));
        if (status < 0) return TREXIO_FAILURE;

      }
    }
  }

  H5Aclose(num_id);
  H5Tclose(dtype);
  return TREXIO_SUCCESS;
  
}
trexio_exit_code trexio_hdf5_write_ecp_local_num_n_max (const trexio_t* file, const uint64_t num) {

  assert (file != NULL);
  assert (num > 0L);
 
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  hid_t num_id;
  herr_t status;
  /* Write the dimensioning variables */
  hid_t dtype = H5Tcopy(H5T_NATIVE_ULLONG);

  if (H5Aexists(f->ecp_group, ECP_LOCAL_NUM_N_MAX_NAME) == 0) {
   
    hid_t dspace = H5Screate(H5S_SCALAR);

    num_id = H5Acreate(f->ecp_group, ECP_LOCAL_NUM_N_MAX_NAME, dtype, dspace,
                     H5P_DEFAULT, H5P_DEFAULT);
    if (num_id <= 0) return TREXIO_INVALID_ID;
  
    status = H5Awrite(num_id, dtype, &(num));
    if (status < 0) return TREXIO_FAILURE;

    H5Sclose(dspace);
    
  } else {

    uint64_t infile_num;
    trexio_exit_code rc = trexio_hdf5_read_ecp_local_num_n_max(file, &(infile_num));
    if (rc != TREXIO_SUCCESS) return rc;

    if (infile_num != num) {

      if (infile_num != 0) {
        printf("%ld -> %ld %s \n", num, infile_num, 
	       "This variable already exists. Overwriting it is not supported");
        H5Tclose(dtype);
        return TREXIO_FAILURE;

      } else {
    
        num_id = H5Aopen(f->ecp_group, ECP_LOCAL_NUM_N_MAX_NAME, H5P_DEFAULT);
        if (num_id <= 0) return TREXIO_INVALID_ID;
       
        status = H5Awrite(num_id, dtype, &(num));
        if (status < 0) return TREXIO_FAILURE;

      }
    }
  }

  H5Aclose(num_id);
  H5Tclose(dtype);
  return TREXIO_SUCCESS;
  
}
trexio_exit_code trexio_hdf5_write_ecp_non_local_num_n_max (const trexio_t* file, const uint64_t num) {

  assert (file != NULL);
  assert (num > 0L);
 
  trexio_hdf5_t* f = (trexio_hdf5_t*) file;
  hid_t num_id;
  herr_t status;
  /* Write the dimensioning variables */
  hid_t dtype = H5Tcopy(H5T_NATIVE_ULLONG);

  if (H5Aexists(f->ecp_group, ECP_NON_LOCAL_NUM_N_MAX_NAME) == 0) {
   
    hid_t dspace = H5Screate(H5S_SCALAR);

    num_id = H5Acreate(f->ecp_group, ECP_NON_LOCAL_NUM_N_MAX_NAME, dtype, dspace,
                     H5P_DEFAULT, H5P_DEFAULT);
    if (num_id <= 0) return TREXIO_INVALID_ID;
  
    status = H5Awrite(num_id, dtype, &(num));
    if (status < 0) return TREXIO_FAILURE;

    H5Sclose(dspace);
    
  } else {

    uint64_t infile_num;
    trexio_exit_code rc = trexio_hdf5_read_ecp_non_local_num_n_max(file, &(infile_num));
    if (rc != TREXIO_SUCCESS) return rc;

    if (infile_num != num) {

      if (infile_num != 0) {
        printf("%ld -> %ld %s \n", num, infile_num, 
	       "This variable already exists. Overwriting it is not supported");
        H5Tclose(dtype);
        return TREXIO_FAILURE;

      } else {
    
        num_id = H5Aopen(f->ecp_group, ECP_NON_LOCAL_NUM_N_MAX_NAME, H5P_DEFAULT);
        if (num_id <= 0) return TREXIO_INVALID_ID;
       
        status = H5Awrite(num_id, dtype, &(num));
        if (status < 0) return TREXIO_FAILURE;

      }
    }
  }

  H5Aclose(num_id);
  H5Tclose(dtype);
  return TREXIO_SUCCESS;
  
}
