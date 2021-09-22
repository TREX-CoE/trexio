#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_BACKEND 	TREXIO_HDF5
#define TREXIO_FILE 	"test_dset_i.h5"
#define RM_COMMAND 	"rm -rf " TREXIO_FILE

static int test_write_dset (const char* file_name, const back_end_t backend) {

/* Try to write a dataset with numerical (int) values into the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be written
  int num = 12;
  int nucl_index[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);

  // write numerical attribute in an empty file
  rc = trexio_write_nucleus_num(file, num);
  assert (rc == TREXIO_SUCCESS);
  
  // write numerical (integer) dataset in a file
  rc = trexio_write_basis_nucleus_index(file, nucl_index);
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

  // check that the previously written dataset exists
  rc = trexio_has_basis_nucleus_index(file);
  assert (rc == TREXIO_SUCCESS);

  // check that another dataset does not exist
  rc = trexio_has_mo_coefficient(file);
  assert (rc == TREXIO_HAS_NOT);

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
  int num;
  int* nucl_index;

/*================= START OF TEST ==================*/

  // open file in 'read' mode
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);

  // read numerical attribute from the file
  rc = trexio_read_nucleus_num(file, &num);
  assert (rc == TREXIO_SUCCESS);
  assert (num == 12);

  // read numerical dataset from the file
  nucl_index = (int*) calloc(num, sizeof(int));
  rc = trexio_read_basis_nucleus_index(file, nucl_index);
  assert (rc == TREXIO_SUCCESS);
  assert (nucl_index[num-1] == num-1);

  free(nucl_index);

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


