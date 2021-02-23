/* This file was generated from the trio.org org-mode file.
   To generate it, open trio.org in Emacs and execute
   M-x org-babel-tangle
*/



#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "trio.h"
#include "trio_s.h"
#include "trio_text.h"
#include "trio_hdf5.h"
/*
#include "trio_json.h"
*/

trio_t* trio_create(const char* file_name, back_end_t back_end) {

  /* Check that file name is not NULL or empty */
  assert (file_name != NULL);
  assert (file_name[0] != '\0');
  
  /* Check that back_end is valid */
  assert (back_end < TRIO_INVALID_BACK_END);
  
  trio_t* result = NULL;
  
  switch (back_end) {

  case TRIO_TEXT:
    result = (trio_t*) malloc (sizeof(trio_text_t));
    break;

  case TRIO_HDF5:
    result = (trio_t*) malloc (sizeof(trio_hdf5_t));
    break;
/*
  case TRIO_JSON:
    result = (trio_t*) malloc (sizeof(trio_json_t));
    break;
*/      
  default:
    assert (1 == 0);  /* Impossible case */
  }
  
  /* TODO: Error handling */
  assert (result != NULL);

  result->file_name   = (char*) calloc(strlen(file_name)+1,sizeof(char));
  strcpy(result->file_name, file_name);
  result->back_end    = back_end;
  result->mode        = 'w';  /* Upon creation, mode=write */
  int irc = pthread_mutex_init ( &(result->thread_lock), NULL);
  assert (irc == 0);

  trio_exit_code rc = TRIO_FAILURE;
  
  switch (back_end) {

  case TRIO_TEXT:
    rc = trio_text_init(result);
    break;

  case TRIO_HDF5:
    rc = trio_hdf5_init(result);
    break;
/*
  case TRIO_JSON:
    rc = trio_json_init(result);
    break;
*/      
  default:
    assert (1 == 0);  /* Impossible case */
  }
  assert (rc == TRIO_SUCCESS);
  
  return result;
}

trio_exit_code trio_close(trio_t* file) {

  assert (file != NULL);
  
  trio_exit_code rc;
  
  switch (file->back_end) {

  case TRIO_TEXT:
    rc = trio_text_finalize(file);
    break;

  case TRIO_HDF5:
    rc = trio_hdf5_finalize(file);
    break;
/*
  case TRIO_JSON:
    rc = trio_json_finalize(file);
    break;
*/      
  default:
    assert (1 == 0);  /* Impossible case */
  }

  if (rc != TRIO_SUCCESS) {
    return TRIO_FAILURE;
  }
  
  free(file->file_name);
  file->file_name = NULL;
  
  int irc = pthread_mutex_destroy( &(file->thread_lock) );
  assert (irc == 0);

  free(file);
  
  return TRIO_SUCCESS;
}

trio_exit_code trio_read_nucleus_num(trio_t* file, uint64_t* num) {
  if (file == NULL) return TRIO_FAILURE;

  switch (file->back_end) {

  case TRIO_TEXT:
    return trio_text_read_nucleus_num(file, num);
    break;
/*
  case TRIO_HDF5:
    return trio_hdf5_read_nucleus_num(file, num);
    break;

  case TRIO_JSON:
    return trio_json_read_nucleus_num(file, num);
    break;
*/      
  default:
    return TRIO_FAILURE;  /* Impossible case */
  }
}

trio_exit_code trio_write_nucleus_num(trio_t* file, uint64_t num) {
  if (file == NULL) return TRIO_FAILURE;

  switch (file->back_end) {

  case TRIO_TEXT:
    return trio_text_write_nucleus_num(file, num);
    break;
/*
  case TRIO_HDF5:
    return trio_hdf5_write_nucleus_num(file, num);
    break;

  case TRIO_JSON:
    return trio_json_write_nucleus_num(file, num);
    break;
*/      
  default:
    return TRIO_FAILURE;  /* Impossible case */
  }
}

trio_exit_code trio_read_nucleus_coord(trio_t* file, double* coord) {
  if (file == NULL) return TRIO_FAILURE;

  switch (file->back_end) {

  case TRIO_TEXT:
    return trio_text_read_nucleus_coord(file, coord);
    break;

  case TRIO_HDF5:
    return trio_hdf5_read_nucleus_coord(file, coord);
    break;
/*
  case TRIO_JSON:
    return trio_json_read_nucleus_coord(file, coord);
    break;
*/
  default:
    return TRIO_FAILURE;  /* Impossible case */
  }
}

trio_exit_code trio_write_nucleus_coord(trio_t* file, double* coord) {
  if (file == NULL) return TRIO_FAILURE;

  switch (file->back_end) {

  case TRIO_TEXT:
    return trio_text_write_nucleus_coord(file, coord);
    break;
/*
  case TRIO_HDF5:
    return trio_hdf5_write_nucleus_coord(file, coord);
    break;

  case TRIO_JSON:
    return trio_json_write_nucleus_coord(file, coord);
    break;
*/
  default:
    return TRIO_FAILURE;  /* Impossible case */
  }
}

trio_exit_code trio_read_nucleus_charge(trio_t* file, double* charge) {
  if (file == NULL) return TRIO_FAILURE;

  switch (file->back_end) {

  case TRIO_TEXT:
    return trio_text_read_nucleus_charge(file, charge);
    break;
/*
  case TRIO_HDF5:
    return trio_hdf5_read_nucleus_charge(file, charge);
    break;

  case TRIO_JSON:
    return trio_json_read_nucleus_charge(file, charge);
    break;
*/
  default:
    return TRIO_FAILURE;  /* Impossible case */
  }
}

trio_exit_code trio_write_nucleus_charge(trio_t* file, double* charge) {
  if (file == NULL) return TRIO_FAILURE;

  switch (file->back_end) {

  case TRIO_TEXT:
    return trio_text_write_nucleus_charge(file, charge);
    break;
/*
  case TRIO_HDF5:
    return trio_hdf5_write_nucleus_charge(file, charge);
    break;

  case TRIO_JSON:
    return trio_json_write_nucleus_charge(file, charge);
    break;
*/
  default:
    return TRIO_FAILURE;  /* Impossible case */
  }
}
