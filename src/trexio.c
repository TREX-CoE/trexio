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

trexio_exit_code trexio_read_nucleus_coord(trexio_t* file, double* coord) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (coord == NULL) return TREXIO_INVALID_ARG_2;

  int64_t nucleus_num = -1;
  trexio_exit_code rc = trexio_read_nucleus_num(file, &nucleus_num);
  if (rc != TREXIO_SUCCESS) return rc;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, 3}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_nucleus_coord(file, coord, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_nucleus_coord(file, coord, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_nucleus_coord(file, coord);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}

trexio_exit_code trexio_write_nucleus_coord(trexio_t* file, const double* coord) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (coord == NULL) return TREXIO_INVALID_ARG_2;

  int64_t nucleus_num = -1;
  trexio_exit_code rc = trexio_read_nucleus_num(file, &nucleus_num);
  if (rc != TREXIO_SUCCESS) return rc;

  uint32_t rank = 2;
  uint64_t dims[2] = {nucleus_num, 3};
 
  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_nucleus_coord(file, coord, rank, dims);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_nucleus_coord(file, coord, rank, dims);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_nucleus_coord(file, coord);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}

trexio_exit_code trexio_read_nucleus_charge(trexio_t* file, double* charge) {
  if (file   == NULL) return TREXIO_INVALID_ARG_1;
  if (charge == NULL) return TREXIO_INVALID_ARG_2;

  int64_t nucleus_num = -1;
  trexio_exit_code rc = trexio_read_nucleus_num(file, &nucleus_num);
  if (rc != TREXIO_SUCCESS) return rc;

  uint32_t rank = 1;
  uint64_t dims[1] = {nucleus_num}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_nucleus_charge(file, charge, rank, dims);
    break;
/*
  case TREXIO_HDF5:
    return trexio_hdf5_read_nucleus_charge(file, charge);
    break;

  case TREXIO_JSON:
    return trexio_json_read_nucleus_charge(file, charge);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}

trexio_exit_code trexio_write_nucleus_charge(trexio_t* file, const double* charge) {
  if (file   == NULL) return TREXIO_INVALID_ARG_1;
  if (charge == NULL) return TREXIO_INVALID_ARG_2;

  int64_t nucleus_num = -1;
  trexio_exit_code rc = trexio_read_nucleus_num(file, &nucleus_num);
  if (rc != TREXIO_SUCCESS) return rc;

  uint32_t rank = 1;
  uint64_t dims[1] = {nucleus_num}; 

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_nucleus_charge(file, charge, rank, dims);
    break;
/*
  case TREXIO_HDF5:
    return trexio_hdf5_write_nucleus_charge(file, charge);
    break;

  case TREXIO_JSON:
    return trexio_json_write_nucleus_charge(file, charge);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}

trexio_exit_code trexio_read_rdm_one_e(trexio_t* file, double* one_e) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (one_e == NULL) return TREXIO_INVALID_ARG_2;

  int64_t dim_one_e = -1;
  trexio_exit_code rc = trexio_read_nucleus_num(file, &dim_one_e); /* This dimension is wrong. Should be mo_num */
  if (rc != TREXIO_SUCCESS) return rc;
  if (dim_one_e < 0) return TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_rdm_one_e(file, one_e, (uint64_t) dim_one_e);
    break;
/*
  case TREXIO_HDF5:
    return trexio_hdf5_read_rdm_one_e(file, one_e);
    break;

  case TREXIO_JSON:
    return trexio_json_read_rdm_one_e(file, one_e);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}

trexio_exit_code trexio_write_rdm_one_e(trexio_t* file, const double* one_e) {
  if (file  == NULL) return TREXIO_INVALID_ARG_1;
  if (one_e == NULL) return TREXIO_INVALID_ARG_2;

  int64_t nucleus_num = -1;
  trexio_exit_code rc = trexio_read_nucleus_num(file, &nucleus_num);
  if (rc != TREXIO_SUCCESS) return rc;

  int64_t dim_one_e = nucleus_num * nucleus_num; /* This dimension is wrong. Should be mo_num */
  if (dim_one_e < 0) return TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_rdm_one_e(file, one_e, (uint64_t) dim_one_e);
    break;
/*
  case TREXIO_HDF5:
    return trexio_hdf5_write_rdm_one_e(file, one_e);
    break;

  case TREXIO_JSON:
    return trexio_json_write_rdm_one_e(file, one_e);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}

trexio_exit_code trexio_buffered_read_rdm_two_e(trexio_t* file, const int64_t offset, const int64_t size, int64_t* index, double* value) {
  if (file   == NULL) return TREXIO_INVALID_ARG_1;
  if (offset <= 0   ) return TREXIO_INVALID_ARG_2;
  if (size   <= 0   ) return TREXIO_INVALID_ARG_3;
  if (index  == NULL) return TREXIO_INVALID_ARG_4;
  if (value  == NULL) return TREXIO_INVALID_ARG_5;

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_buffered_read_rdm_two_e(file, (uint64_t) offset, (uint64_t) size, index, value);
    break;
/*
  case TREXIO_HDF5:
    return trexio_hdf5_buffered_read_rdm_two_e(file, size);
    break;

  case TREXIO_JSON:
    return trexio_json_buffered_read_rdm_two_e(file, size);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}

trexio_exit_code trexio_buffered_write_rdm_two_e(trexio_t* file, const int64_t offset, const int64_t size, const int64_t* index, const double* value) {
  if (file   == NULL) return TREXIO_INVALID_ARG_1;
  if (offset <= 0   ) return TREXIO_INVALID_ARG_2;
  if (size   <= 0   ) return TREXIO_INVALID_ARG_3;
  if (index  == NULL) return TREXIO_INVALID_ARG_4;
  if (value  == NULL) return TREXIO_INVALID_ARG_5;

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_buffered_write_rdm_two_e(file, (uint64_t) offset, (uint64_t) size, index, value);
    break;
/*
  case TREXIO_HDF5:
    return trexio_hdf5_buffered_write_rdm_two_e(file, size);
    break;

  case TREXIO_JSON:
    return trexio_json_buffered_write_rdm_two_e(file, size);
    break;
*/
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}
