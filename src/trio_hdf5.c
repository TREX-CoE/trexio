/* This file was generated from the trio.org org-mode file.
   To generate it, open trio.org in Emacs and execute
   M-x org-babel-tangle
*/



#include "trio_hdf5.h"

trio_exit_code trio_hdf5_init(trio_t* file) {

  trio_hdf5_t* f = (trio_hdf5_t*) file;

  /* If file doesn't exist, create it */
  int f_ishere = 0;
  struct stat st;
  
  if (stat(file->file_name, &st) == 0) {
    printf("%s \n","HDF5 file already exists");
   // RDWR OR RDONLY ???
    f->file_id = H5Fopen(file->file_name, H5F_ACC_RDWR, H5P_DEFAULT);
    f_ishere = 1;
  } else {
    f->file_id = H5Fcreate(file->file_name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    f_ishere = 0;
  }  

  /* Create groups in the hdf5 file */
  const char* nucleus_group_name = "nucleus";
  //const char* electron_group_name = "electron";
 
  if (f_ishere == 0){
    f->nucleus_group = H5Gcreate(f->file_id, nucleus_group_name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    //f->electron_group = H5Gcreate(f->file_id, electron_group_name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
  } else { 
    f->nucleus_group = H5Gopen(f->file_id, nucleus_group_name, H5P_DEFAULT);
    //f->electron_group = H5Gopen(f->file_id, electron_group_name, H5P_DEFAULT);   
  }
  /* not sure if assert statement here makes sence 
     H5Gcreate will raise its own H5 error if somethings is wrong*/
  assert (f->nucleus_group > 0L);
  //assert (f->electron_group > 0L);

  return TRIO_SUCCESS;
}

trio_exit_code trio_hdf5_finalize(trio_t* file) {

  trio_hdf5_t* f = (trio_hdf5_t*) file;

  H5Gclose(f->nucleus_group);
  f->nucleus_group = 0;

/*
  H5Gclose(f->electron_group);
  f->electron_group = 0; 
*/
  return TRIO_SUCCESS;
}

h5nucleus_t* trio_hdf5_read_nucleus(const trio_hdf5_t* file) {
  
  /* Allocate the data structure */
  h5nucleus_t* nucleus = (h5nucleus_t*) malloc(sizeof(h5nucleus_t));
  assert (nucleus != NULL);

  nucleus->num    = 0;
  nucleus->coord  = NULL;
  nucleus->charge = NULL;
  nucleus->h5_coord  = NULL;
  nucleus->h5_charge = NULL;

  /* Try to open the file. If HDF5 cannot open, return */ 
  if (file->file_id < 0) return nucleus;

  herr_t status;  
  /* Read the nucleus_num attribute of nucleus group */
  const char *num_name = "nucleus_num";
  hid_t num_id;
  num_id = H5Aopen(file->nucleus_group, num_name, H5P_DEFAULT);
  assert (num_id > 0);

  status = H5Aread(num_id, H5T_NATIVE_ULLONG, &(nucleus->num));
  assert (status >= 0);

  /* Allocate and read nucleus_charge array */
  nucleus->charge = (double*) calloc(nucleus->num, sizeof(double));
  assert (nucleus->charge != NULL);

  /*
   * High-level H5LT API. No need to deal with dataspaces and datatypes
   */
  /*  
  status = H5LTread_dataset_double(file->nucleus_group, 
                                "nucleus_charge", 
				nucleus->charge)
  */
  /*
   * Low-level implementation. Involves dealing with all HDF5 handles and dimensions
   */
  nucleus->h5_charge = (dset_t*) malloc(sizeof(dset_t));
  assert (nucleus->h5_charge != NULL);

  nucleus->h5_charge->dset_id = H5Dopen(file->nucleus_group, 
                                        "nucleus_charge", 
                                        H5P_DEFAULT);
  assert (nucleus->h5_charge->dset_id > 0);
  /*
   * Get dataspace, datatype and dimensions
   * dspace and dtype handles created below have to be closed when not used
   */    
  nucleus->h5_charge->dspace_id = H5Dget_space(nucleus->h5_charge->dset_id);
  assert (nucleus->h5_charge->dspace_id > 0);
  
  nucleus->h5_charge->dtype_id = H5Dget_type(nucleus->h5_charge->dset_id);
  assert (nucleus->h5_charge->dtype_id > 0);
  
  int rrank;
  const int rank = 1;
  hsize_t dims[1] = {0};
  rrank = H5Sget_simple_extent_dims(nucleus->h5_charge->dspace_id, 
                                    dims, NULL);
  assert (rrank == rank);
  for (int i=0; i<rank; i++){
    assert (dims[i] > 0);
  }

  status = H5Dread(nucleus->h5_charge->dset_id, nucleus->h5_charge->dtype_id,
               H5S_ALL, H5S_ALL, H5P_DEFAULT,
	       nucleus->charge);
  assert (status >= 0);

  /* Allocate and read nucleus_coord array */
  nucleus->coord = (double*) calloc(3 * nucleus->num, sizeof(double));
  assert (nucleus->coord != NULL);

  status = H5LTread_dataset_double(file->nucleus_group, 
                                    "nucleus_coord", 
				    nucleus->coord);
  assert (status >= 0);
  /* Print arrays */
  /*
  for (size_t i=0 ; i<nucleus->num ; i++) {
    printf("%lf \n", nucleus->charge[i]);
  }
  
  for (size_t i=0 ; i<3*nucleus->num ; i++) {
      printf("%lf \n", nucleus->coord[i]);
  }
   */
  H5Aclose(num_id);
  H5Sclose(nucleus->h5_charge->dspace_id);
  H5Tclose(nucleus->h5_charge->dtype_id);
  H5Dclose(nucleus->h5_charge->dset_id);
  H5Fclose(file->file_id);

  return nucleus;
}


trio_exit_code trio_hdf5_write_nucleus(const trio_hdf5_t* file, h5nucleus_t* nucleus) {
  assert (nucleus != NULL);

  assert (file != NULL);

  // TODO
  return TRIO_FAILURE;
}

trio_exit_code trio_hdf5_free_nucleus(h5nucleus_t* nucleus) {
  
  if (nucleus == NULL) return TRIO_FAILURE;
  
  if (nucleus->coord != NULL) free (nucleus->coord);
  nucleus->coord = NULL;
  
  if (nucleus->charge != NULL) free (nucleus->charge);
  nucleus->charge = NULL;
  
  if (nucleus->h5_coord != NULL) free (nucleus->h5_coord);
  nucleus->h5_coord = NULL;
  
  if (nucleus->h5_charge != NULL) free (nucleus->h5_charge);
  nucleus->h5_charge = NULL;

  free (nucleus);

  return TRIO_SUCCESS;
}

trio_exit_code trio_hdf5_read_nucleus_coord(const trio_t* file, double* coord) {

  assert (file != NULL);
  h5nucleus_t* nucleus = trio_hdf5_read_nucleus((trio_hdf5_t*) file);
  
  if (nucleus == NULL) return TRIO_FAILURE;

  assert (coord != NULL);
  
  for (size_t i=0 ; i<3*nucleus->num ; i++) {
    coord[i] = nucleus->coord[i];
  }

  trio_hdf5_free_nucleus(nucleus);
  return TRIO_SUCCESS;
}

 
trio_exit_code trio_hdf5_write_nucleus_coord(const trio_t* file, const double* coord) {
  assert (file != NULL);
  assert (coord != NULL);
  // TODO
  return TRIO_FAILURE;
}
