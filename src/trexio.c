/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/

#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "trexio.h"
#include "trexio_s.h"
#include "trexio_text.h"
#include "trexio_hdf5.h"
/*
#include "trexio_json.h"
*/

trexio_t* trexio_open(const char* file_name, const char mode, const back_end_t back_end) {
  
  if (file_name == NULL) return NULL;
  if (file_name[0] == '\0') return NULL;
  
  if (back_end <  0) return NULL;
  if (back_end >= TREXIO_INVALID_BACK_END) return NULL;
  
  if (mode != 'r' && mode != 'w' && mode != 'a') return NULL;

  trexio_t* result = NULL;
  
  /* Allocate data structures */
  switch (back_end) {

  case TREXIO_TEXT:
    result = (trexio_t*) malloc (sizeof(trexio_text_t));
    break;

  case TREXIO_HDF5:
    result = (trexio_t*) malloc (sizeof(trexio_hdf5_t));
    break;
/*
  case TREXIO_JSON:
    result = (trexio_t*) malloc (sizeof(trexio_json_t));
    break;
*/      
  }
  
  assert (result != NULL);    /* TODO: Error handling */


  /* Data for the parent type */

  result->file_name   = (char*) calloc(strlen(file_name)+1,sizeof(char));
  strcpy(result->file_name, file_name);
  result->back_end    = back_end;
  result->mode        = mode;
  int irc = pthread_mutex_init ( &(result->thread_lock), NULL);
  assert (irc == 0);

  trexio_exit_code rc;
  
  /* Back end initialization */
  
  rc = TREXIO_FAILURE;
  
  switch (back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_init(result);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_init(result);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_init(result);
    break;
*/      
  }

  if (rc != TREXIO_SUCCESS) {
    free(result->file_name);
    free(result);
    return NULL;
  }

  /* File locking */
  
  rc = TREXIO_FAILURE;
  
  switch (back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_lock(result);
    break;

  case TREXIO_HDF5:
    rc = TREXIO_SUCCESS;
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_lock(result);
    break;
*/      
  }
  
  if (rc != TREXIO_SUCCESS) {
    free(result->file_name);
    free(result);
    return NULL;
  }
  
  return result;
}

trexio_exit_code trexio_close(trexio_t* file) {

  if (file == NULL) return TREXIO_FAILURE;
  
  trexio_exit_code rc;
  
  /* Terminate the back end */
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_finalize(file);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_finalize(file);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_finalize(file);
    break;
*/      
  default:
    assert (1 == 0);  /* Impossible case */
  }

  if (rc != TREXIO_SUCCESS) {
    free(file->file_name);
    free(file);
    return TREXIO_FAILURE;
  }
  
  /* File unlocking */
  
  rc = TREXIO_FAILURE;
  
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_unlock(file);
    break;

  case TREXIO_HDF5:
    rc = TREXIO_SUCCESS;
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_unlock(file);
    break;
*/      
  }

  /* Terminate front end */
  
  free(file->file_name);
  file->file_name = NULL;
  
  int irc = pthread_mutex_destroy( &(file->thread_lock) );
  
  free(file);

  if (irc != 0) return TREXIO_ERRNO;
  if (rc != TREXIO_SUCCESS) return TREXIO_FAILURE;
    
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_read_nucleus_charge(trexio_t* file, double* nucleus_charge) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_charge == NULL) return TREXIO_INVALID_ARG_2;
    
  trexio_exit_code rc;
  uint64_t nucleus_num = -1;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;

  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 1;
  uint64_t dims[1] = {nucleus_num}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_nucleus_charge(file, nucleus_charge, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_nucleus_charge(file, nucleus_charge, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_nucleus_charge(file, nucleus_charge);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_read_nucleus_coord(trexio_t* file, double* nucleus_coord) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_coord == NULL) return TREXIO_INVALID_ARG_2;
    
  trexio_exit_code rc;
  uint64_t nucleus_num = -1;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;

  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, 3}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_nucleus_coord(file, nucleus_coord, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_nucleus_coord(file, nucleus_coord, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_nucleus_coord(file, nucleus_coord);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_read_ecp_lmax_plus_1(trexio_t* file, int64_t* ecp_lmax_plus_1) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_lmax_plus_1 == NULL) return TREXIO_INVALID_ARG_2;
    
  trexio_exit_code rc;
  uint64_t nucleus_num = -1;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;

  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 1;
  uint64_t dims[1] = {nucleus_num}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_ecp_lmax_plus_1(file, ecp_lmax_plus_1, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_ecp_lmax_plus_1(file, ecp_lmax_plus_1, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_ecp_lmax_plus_1(file, ecp_lmax_plus_1);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_read_ecp_z_core(trexio_t* file, int64_t* ecp_z_core) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_z_core == NULL) return TREXIO_INVALID_ARG_2;
    
  trexio_exit_code rc;
  uint64_t nucleus_num = -1;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;

  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 1;
  uint64_t dims[1] = {nucleus_num}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_ecp_z_core(file, ecp_z_core, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_ecp_z_core(file, ecp_z_core, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_ecp_z_core(file, ecp_z_core);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_read_ecp_local_n(trexio_t* file, int64_t* ecp_local_n) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_local_n == NULL) return TREXIO_INVALID_ARG_2;
    
  trexio_exit_code rc;
  uint64_t nucleus_num = -1;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;

  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 1;
  uint64_t dims[1] = {nucleus_num}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_ecp_local_n(file, ecp_local_n, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_ecp_local_n(file, ecp_local_n, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_ecp_local_n(file, ecp_local_n);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_read_ecp_local_exponent(trexio_t* file, double* ecp_local_exponent) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_local_exponent == NULL) return TREXIO_INVALID_ARG_2;
    
  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  uint64_t ecp_local_num_n_max = -1;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    rc = trexio_text_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    rc = trexio_hdf5_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    rc = trexio_json_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;

  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, ecp_local_num_n_max}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_ecp_local_exponent(file, ecp_local_exponent, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_ecp_local_exponent(file, ecp_local_exponent, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_ecp_local_exponent(file, ecp_local_exponent);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_read_ecp_local_coef(trexio_t* file, double* ecp_local_coef) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_local_coef == NULL) return TREXIO_INVALID_ARG_2;
    
  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  uint64_t ecp_local_num_n_max = -1;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    rc = trexio_text_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    rc = trexio_hdf5_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    rc = trexio_json_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;

  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, ecp_local_num_n_max}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_ecp_local_coef(file, ecp_local_coef, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_ecp_local_coef(file, ecp_local_coef, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_ecp_local_coef(file, ecp_local_coef);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_read_ecp_local_power(trexio_t* file, int64_t* ecp_local_power) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_local_power == NULL) return TREXIO_INVALID_ARG_2;
    
  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  uint64_t ecp_local_num_n_max = -1;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    rc = trexio_text_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    rc = trexio_hdf5_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    rc = trexio_json_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;

  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, ecp_local_num_n_max}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_ecp_local_power(file, ecp_local_power, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_ecp_local_power(file, ecp_local_power, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_ecp_local_power(file, ecp_local_power);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_read_ecp_non_local_n(trexio_t* file, int64_t* ecp_non_local_n) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_n == NULL) return TREXIO_INVALID_ARG_2;
    
  trexio_exit_code rc;
  uint64_t nucleus_num = -1;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;

  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 1;
  uint64_t dims[1] = {nucleus_num}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_ecp_non_local_n(file, ecp_non_local_n, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_ecp_non_local_n(file, ecp_non_local_n, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_ecp_non_local_n(file, ecp_non_local_n);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_read_ecp_non_local_exponent(trexio_t* file, double* ecp_non_local_exponent) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_exponent == NULL) return TREXIO_INVALID_ARG_2;
    
  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  uint64_t ecp_non_local_num_n_max = -1;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    rc = trexio_text_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    rc = trexio_hdf5_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    rc = trexio_json_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;

  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_non_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, ecp_non_local_num_n_max}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_ecp_non_local_exponent(file, ecp_non_local_exponent, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_ecp_non_local_exponent(file, ecp_non_local_exponent, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_ecp_non_local_exponent(file, ecp_non_local_exponent);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_read_ecp_non_local_coef(trexio_t* file, double* ecp_non_local_coef) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_coef == NULL) return TREXIO_INVALID_ARG_2;
    
  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  uint64_t ecp_non_local_num_n_max = -1;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    rc = trexio_text_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    rc = trexio_hdf5_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    rc = trexio_json_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;

  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_non_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, ecp_non_local_num_n_max}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_ecp_non_local_coef(file, ecp_non_local_coef, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_ecp_non_local_coef(file, ecp_non_local_coef, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_ecp_non_local_coef(file, ecp_non_local_coef);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_read_ecp_non_local_power(trexio_t* file, int64_t* ecp_non_local_power) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_power == NULL) return TREXIO_INVALID_ARG_2;
    
  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  uint64_t ecp_non_local_num_n_max = -1;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    rc = trexio_text_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    rc = trexio_hdf5_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    rc = trexio_json_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;

  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_non_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, ecp_non_local_num_n_max}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_ecp_non_local_power(file, ecp_non_local_power, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_ecp_non_local_power(file, ecp_non_local_power, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_ecp_non_local_power(file, ecp_non_local_power);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_read_nucleus_num(trexio_t* file, int64_t* num) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  uint64_t u_num = 0;
  trexio_exit_code rc = TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &u_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &u_num);
    break;
/*
  case TREXIO_JSON:
    rc =trexio_json_read_nucleus_num(file, &u_num);
    break;
*/      
  }

  if (rc != TREXIO_SUCCESS) return rc;
                              
  /**/ *num = (int64_t) u_num;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_read_ecp_local_num_n_max(trexio_t* file, int64_t* num) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  uint64_t u_num = 0;
  trexio_exit_code rc = TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_ecp_local_num_n_max(file, &u_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_ecp_local_num_n_max(file, &u_num);
    break;
/*
  case TREXIO_JSON:
    rc =trexio_json_read_ecp_local_num_n_max(file, &u_num);
    break;
*/      
  }

  if (rc != TREXIO_SUCCESS) return rc;
                              
  /**/ *num = (int64_t) u_num;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_read_ecp_non_local_num_n_max(trexio_t* file, int64_t* num) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;

  uint64_t u_num = 0;
  trexio_exit_code rc = TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_ecp_non_local_num_n_max(file, &u_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_ecp_non_local_num_n_max(file, &u_num);
    break;
/*
  case TREXIO_JSON:
    rc =trexio_json_read_ecp_non_local_num_n_max(file, &u_num);
    break;
*/      
  }

  if (rc != TREXIO_SUCCESS) return rc;
                              
  /**/ *num = (int64_t) u_num;
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_write_nucleus_charge(trexio_t* file, const double* nucleus_charge) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_charge == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 1;
  uint64_t dims[1] = {nucleus_num}; 
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_nucleus_charge(file, nucleus_charge, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_nucleus_charge(file, nucleus_charge, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_nucleus_charge(file, nucleus_charge);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_write_nucleus_coord(trexio_t* file, const double* nucleus_coord) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (nucleus_coord == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, 3}; 
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_nucleus_coord(file, nucleus_coord, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_nucleus_coord(file, nucleus_coord, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_nucleus_coord(file, nucleus_coord);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_write_ecp_lmax_plus_1(trexio_t* file, const int64_t* ecp_lmax_plus_1) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_lmax_plus_1 == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 1;
  uint64_t dims[1] = {nucleus_num}; 
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_ecp_lmax_plus_1(file, ecp_lmax_plus_1, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_ecp_lmax_plus_1(file, ecp_lmax_plus_1, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_ecp_lmax_plus_1(file, ecp_lmax_plus_1);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_write_ecp_z_core(trexio_t* file, const int64_t* ecp_z_core) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_z_core == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 1;
  uint64_t dims[1] = {nucleus_num}; 
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_ecp_z_core(file, ecp_z_core, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_ecp_z_core(file, ecp_z_core, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_ecp_z_core(file, ecp_z_core);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_write_ecp_local_n(trexio_t* file, const int64_t* ecp_local_n) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_local_n == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 1;
  uint64_t dims[1] = {nucleus_num}; 
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_ecp_local_n(file, ecp_local_n, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_ecp_local_n(file, ecp_local_n, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_ecp_local_n(file, ecp_local_n);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_write_ecp_local_exponent(trexio_t* file, const double* ecp_local_exponent) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_local_exponent == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  uint64_t ecp_local_num_n_max = -1;
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    rc = trexio_text_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    rc = trexio_hdf5_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    rc = trexio_json_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, ecp_local_num_n_max}; 
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_ecp_local_exponent(file, ecp_local_exponent, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_ecp_local_exponent(file, ecp_local_exponent, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_ecp_local_exponent(file, ecp_local_exponent);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_write_ecp_local_coef(trexio_t* file, const double* ecp_local_coef) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_local_coef == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  uint64_t ecp_local_num_n_max = -1;
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    rc = trexio_text_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    rc = trexio_hdf5_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    rc = trexio_json_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, ecp_local_num_n_max}; 
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_ecp_local_coef(file, ecp_local_coef, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_ecp_local_coef(file, ecp_local_coef, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_ecp_local_coef(file, ecp_local_coef);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_write_ecp_local_power(trexio_t* file, const int64_t* ecp_local_power) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_local_power == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  uint64_t ecp_local_num_n_max = -1;
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    rc = trexio_text_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    rc = trexio_hdf5_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    rc = trexio_json_read_ecp_local_num_n_max(file, &ecp_local_num_n_max);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, ecp_local_num_n_max}; 
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_ecp_local_power(file, ecp_local_power, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_ecp_local_power(file, ecp_local_power, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_ecp_local_power(file, ecp_local_power);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_write_ecp_non_local_n(trexio_t* file, const int64_t* ecp_non_local_n) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_n == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 1;
  uint64_t dims[1] = {nucleus_num}; 
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_ecp_non_local_n(file, ecp_non_local_n, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_ecp_non_local_n(file, ecp_non_local_n, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_ecp_non_local_n(file, ecp_non_local_n);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_write_ecp_non_local_exponent(trexio_t* file, const double* ecp_non_local_exponent) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_exponent == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  uint64_t ecp_non_local_num_n_max = -1;
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    rc = trexio_text_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    rc = trexio_hdf5_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    rc = trexio_json_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_non_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, ecp_non_local_num_n_max}; 
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_ecp_non_local_exponent(file, ecp_non_local_exponent, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_ecp_non_local_exponent(file, ecp_non_local_exponent, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_ecp_non_local_exponent(file, ecp_non_local_exponent);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_write_ecp_non_local_coef(trexio_t* file, const double* ecp_non_local_coef) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_coef == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  uint64_t ecp_non_local_num_n_max = -1;
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    rc = trexio_text_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    rc = trexio_hdf5_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    rc = trexio_json_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_non_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, ecp_non_local_num_n_max}; 
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_ecp_non_local_coef(file, ecp_non_local_coef, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_ecp_non_local_coef(file, ecp_non_local_coef, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_ecp_non_local_coef(file, ecp_non_local_coef);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_write_ecp_non_local_power(trexio_t* file, const int64_t* ecp_non_local_power) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (ecp_non_local_power == NULL) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc;
  uint64_t nucleus_num = -1;
  uint64_t ecp_non_local_num_n_max = -1;
  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_read_nucleus_num(file, &nucleus_num);
    rc = trexio_text_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_read_nucleus_num(file, &nucleus_num);
    rc = trexio_hdf5_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_read_nucleus_num(file, &nucleus_num);
    rc = trexio_json_read_ecp_non_local_num_n_max(file, &ecp_non_local_num_n_max);
    break;
*/
  }

  if (rc != TREXIO_SUCCESS) return rc;
  if (nucleus_num <= 0L) return TREXIO_INVALID_NUM;
  if (ecp_non_local_num_n_max <= 0L) return TREXIO_INVALID_NUM;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, ecp_non_local_num_n_max}; 
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_ecp_non_local_power(file, ecp_non_local_power, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_ecp_non_local_power(file, ecp_non_local_power, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_ecp_non_local_power(file, ecp_non_local_power);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
trexio_exit_code trexio_write_nucleus_num(trexio_t* file, const int64_t num) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  <  0   ) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc = TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_write_nucleus_num(file, (uint64_t) num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_write_nucleus_num(file, (uint64_t) num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_write_nucleus_num(file, (uint64_t) num);
    break;
*/      
  }
  if (rc != TREXIO_SUCCESS) return rc;
                              
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_write_ecp_local_num_n_max(trexio_t* file, const int64_t num) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  <  0   ) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc = TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_write_ecp_local_num_n_max(file, (uint64_t) num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_write_ecp_local_num_n_max(file, (uint64_t) num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_write_ecp_local_num_n_max(file, (uint64_t) num);
    break;
*/      
  }
  if (rc != TREXIO_SUCCESS) return rc;
                              
  return TREXIO_SUCCESS;
}
trexio_exit_code trexio_write_ecp_non_local_num_n_max(trexio_t* file, const int64_t num) {
  if (file == NULL) return TREXIO_INVALID_ARG_1;
  if (num  <  0   ) return TREXIO_INVALID_ARG_2;

  trexio_exit_code rc = TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    rc = trexio_text_write_ecp_non_local_num_n_max(file, (uint64_t) num);
    break;

  case TREXIO_HDF5:
    rc = trexio_hdf5_write_ecp_non_local_num_n_max(file, (uint64_t) num);
    break;
/*
  case TREXIO_JSON:
    rc = trexio_json_write_ecp_non_local_num_n_max(file, (uint64_t) num);
    break;
*/      
  }
  if (rc != TREXIO_SUCCESS) return rc;
                              
  return TREXIO_SUCCESS;
}
