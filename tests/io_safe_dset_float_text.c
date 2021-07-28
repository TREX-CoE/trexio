#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TEST_BACKEND 	TREXIO_TEXT
#define TREXIO_FILE 	"test_safe_dset_f.dir"
#define RM_COMMAND 	"rm -rf " TREXIO_FILE

static int test_write_dset (const char* file_name, const back_end_t backend) {

/* Try to write a dataset with floating point values into the TREXIO file using safe API */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be written
  int num = 12;
  double coord[36] = {
  0.00000000 ,  1.39250319 ,  0.00000000 ,
 -1.20594314 ,  0.69625160 ,  0.00000000 ,
 -1.20594314 , -0.69625160 ,  0.00000000 ,
  0.00000000 , -1.39250319 ,  0.00000000 ,
  1.20594314 , -0.69625160 ,  0.00000000 ,
  1.20594314 ,  0.69625160 ,  0.00000000 ,
 -2.14171677 ,  1.23652075 ,  0.00000000 ,
 -2.14171677 , -1.23652075 ,  0.00000000 ,
  0.00000000 , -2.47304151 ,  0.00000000 ,
  2.14171677 , -1.23652075 ,  0.00000000 ,
  2.14171677 ,  1.23652075 ,  0.00000000 ,
  0.00000000 ,  2.47304151 ,  0.00000000 ,
  };

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend);
  assert (file != NULL);

  // write numerical attribute in an empty file
  rc = trexio_write_nucleus_num(file, num);
  assert (rc == TREXIO_SUCCESS);
  
  /* write numerical dataset with an unsafe dimension
   * this should return TREXIO_UNSAFE_ARRAY_DIM indicating
   * that access beyong allocated memory is likely to occur */
  uint64_t dim_unsafe = num * 12;
  rc = trexio_write_safe_nucleus_coord(file, coord, dim_unsafe);
  assert (rc == TREXIO_UNSAFE_ARRAY_DIM);

  /* write numerical dataset with a safe dimension
   * this should return TREXIO_SUCCESS */
  uint64_t dim_safe = num * 3;
  rc = trexio_write_safe_nucleus_coord(file, coord, dim_safe);
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

  // open file in 'read' mode
  file = trexio_open(file_name, 'r', backend);
  assert (file != NULL);

  // check that the previously written dataset exists
  rc = trexio_has_nucleus_coord(file);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_read_dset (const char* file_name, const back_end_t backend) {

/* Try to read a dataset with floating point values from the TREXIO file using safe API */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be read
  int num;
  double* coord;

/*================= START OF TEST ==================*/

  // open file in 'read' mode
  file = trexio_open(file_name, 'r', backend);
  assert (file != NULL);

  // read numerical attribute from the file
  rc = trexio_read_nucleus_num(file, &num);
  assert (rc == TREXIO_SUCCESS);
  assert (num == 12);

  // read numerical (floating point) dataset from the file
  coord = (double*) calloc(3*num, sizeof(double));

  /* write numerical dataset with an unsafe dimension
   * this should return TREXIO_UNSAFE_ARRAY_DIM indicating
   * that access beyong allocated memory is likely to occur */
  uint64_t dim_unsafe = num * 12;
  rc = trexio_read_safe_nucleus_coord(file, coord, dim_unsafe);
  assert (rc == TREXIO_UNSAFE_ARRAY_DIM);

  /* write numerical dataset with a safe dimension
   * this should return TREXIO_SUCCESS */
  uint64_t dim_safe = num * 3;
  rc = trexio_read_safe_nucleus_coord(file, coord, dim_safe);
  assert (rc == TREXIO_SUCCESS);

  double x = coord[30] - 2.14171677;
  assert( x*x < 1.e-14 );
  free(coord);

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


