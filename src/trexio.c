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

trexio_t* trexio_create(const char* file_name, back_end_t back_end) {
  
  /* Check that file name is not NULL or empty */
  assert (file_name != NULL);
  assert (file_name[0] != '\0');
  
  /* Check that back_end is valid */
  assert (back_end < TREXIO_INVALID_BACK_END);
  
  trexio_t* result = NULL;
  
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

  trexio_exit_code rc = TREXIO_FAILURE;
  
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
  default:
    assert (1 == 0);  /* Impossible case */
  }
  assert (rc == TREXIO_SUCCESS);
  
  return result;
}

trexio_exit_code trexio_close(trexio_t* file) {

  assert (file != NULL);
  
  trexio_exit_code rc;
  
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
    return TREXIO_FAILURE;
  }
  
  free(file->file_name);
  file->file_name = NULL;
  
  int irc = pthread_mutex_destroy( &(file->thread_lock) );
  assert (irc == 0);

  free(file);
  
  return TREXIO_SUCCESS;
}

trexio_exit_code trexio_read_nucleus_num(trexio_t* file, uint64_t* num) {
  if (file == NULL) return TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_nucleus_num(file, num);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_nucleus_num(file, num);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_read_nucleus_num(file, num);
    break;
*/      
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}

trexio_exit_code trexio_write_nucleus_num(trexio_t* file, uint64_t num) {
  if (file == NULL) return TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_nucleus_num(file, num);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_nucleus_num(file, num);
    break;
/*
  case TREXIO_JSON:
    return trexio_json_write_nucleus_num(file, num);
    break;
*/      
  default:
    return TREXIO_FAILURE;  /* Impossible case */
  }
}

trexio_exit_code trexio_read_nucleus_coord(trexio_t* file, double* coord) {
  if (file == NULL) return TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_nucleus_coord(file, coord);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_read_nucleus_coord(file, coord);
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

trexio_exit_code trexio_write_nucleus_coord(trexio_t* file, double* coord) {
  if (file == NULL) return TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_nucleus_coord(file, coord);
    break;

  case TREXIO_HDF5:
    return trexio_hdf5_write_nucleus_coord(file, coord);
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
  if (file == NULL) return TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_read_nucleus_charge(file, charge);
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

trexio_exit_code trexio_write_nucleus_charge(trexio_t* file, double* charge) {
  if (file == NULL) return TREXIO_FAILURE;

  switch (file->back_end) {

  case TREXIO_TEXT:
    return trexio_text_write_nucleus_charge(file, charge);
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
