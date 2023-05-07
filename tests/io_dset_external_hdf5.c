#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define TEST_BACKEND 	TREXIO_HDF5
#define TREXIO_FILE 	"test_dset_external.h5"
#define RM_COMMAND 	    "rm -f -- " TREXIO_FILE

#define VECTOR_NAME     "test external vector"
#define MATRIX_NAME     "test external matrix"

static int test_write_dset (const char* file_name, const back_end_t backend) {

/* Try to write a dataset with numerical (int) values into the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be written
  uint32_t rank_v     = 1;
  uint64_t dims_v[1]  = {12};
  int32_t  vector[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

  uint32_t rank_m     = 2;
  uint64_t dims_m[2]  = {3, 4};
  int32_t  matrix[12] = {
      0 , 1  , 2  ,
      3 , 4  , 5  ,
      6 , 7  , 8  ,
      9 , 10 , 11
  };

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);

  // write numerical (int32) vector in an external group of the file
  rc = trexio_write_external_int32_array(file, vector, rank_v, dims_v, VECTOR_NAME);
  assert (rc == TREXIO_SUCCESS);

  // write numerical (int32) matrixin an external group of the file
  rc = trexio_write_external_int32_array(file, matrix, rank_m, dims_m, MATRIX_NAME);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_has_dset (const char* file_name, const back_end_t backend) {

/* Try to check the existence of a dataset in the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);

  // check that the group exists
  rc = trexio_has_external(file);
  assert(rc==TREXIO_SUCCESS);

  // check that the previously written datasets exist
  rc = trexio_has_external_array(file, VECTOR_NAME);
  assert (rc == TREXIO_SUCCESS);

  // check that the previously written datasets exist
  rc = trexio_has_external_array(file, MATRIX_NAME);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_read_dset (const char* file_name, const back_end_t backend) {

/* Try to read a dataset with numericali (int) values from the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be read
  int32_t* vector;

/*================= START OF TEST ==================*/

  // open file in 'read' mode
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);

  // read numerical dataset from the file
  vector = (int32_t*) calloc(12, sizeof(int32_t));
  rc = trexio_read_external_int32_array(file, vector, VECTOR_NAME);
  assert (rc == TREXIO_SUCCESS);
  assert (vector[0]  == 0);
  assert (vector[11] == 11);

  free(vector);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


int main(void) {

/*============== Test launcher ================*/

  int rc;
  rc = system(RM_COMMAND);
  assert (rc == 0);

  test_write_dset (TREXIO_FILE, TEST_BACKEND);
  test_has_dset   (TREXIO_FILE, TEST_BACKEND);
  test_read_dset  (TREXIO_FILE, TEST_BACKEND);

  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}
