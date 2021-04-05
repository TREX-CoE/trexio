#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int test_read();
int test_write();
int test_h5read();
int test_h5write();

int main() {

/*============== Main test launcher ================*/

  test_h5write();
  test_h5read();

  test_write();
  test_read();

  printf("Test error message: %s\n", trexio_string_of_error(TREXIO_INVALID_ARG_2));
  return 0 ;
}

int test_h5write() {

/*======== Test write using HDF5 backend ===========*/

  const char* file_name = "test_write.h5";
  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be written
  int num = 12;
  double charge[12] = {6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1.};

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
  file = trexio_open(file_name, 'w', TREXIO_HDF5);
  assert (file != NULL);

  // check that certain data does not exist in the file
  rc = trexio_has_nucleus_num(file);
  assert (rc == TREXIO_HAS_NOT);
  rc = trexio_has_nucleus_coord(file);
  assert (rc == TREXIO_HAS_NOT);

  // write info in an empty file
  rc = trexio_write_nucleus_num(file,num);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_write_nucleus_coord(file,coord);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_write_nucleus_charge(file,charge);
  assert (rc == TREXIO_SUCCESS);

  // check if the written data exists in the file
  rc = trexio_has_nucleus_num(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_nucleus_coord(file);
  assert (rc == TREXIO_SUCCESS);

  // should not work: try to overwrite the nucleus_num
  rc = trexio_write_nucleus_num(file,25);
  assert (rc != TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // open file again in 'append' mode
  file = trexio_open(file_name, 'a', TREXIO_HDF5);
  assert (file != NULL);
  
  // read the nucleus_num from existing file
  rc = trexio_read_nucleus_num(file,&num);
  assert (rc == TREXIO_SUCCESS);
  assert (num == 12);

  // overwrite the nucleus_coord
  coord[0] = 666.666;
  rc = trexio_write_nucleus_coord(file,coord);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}

int test_h5read() {

/*========= Test read using HDF5 backend ===========*/

  const char* file_name = "test_write.h5";
  trexio_t* file = NULL;
  trexio_exit_code rc;

  int num;
  double* coord;

/*================= START OF TEST ==================*/

  // open existing file on 'read' mode [created by test_h5write()]
  file = trexio_open(file_name, 'r', TREXIO_HDF5);
  assert (file != NULL);

  // read nucleus_num
  rc = trexio_read_nucleus_num(file,&num);
  assert (rc == TREXIO_SUCCESS);
  assert (num == 12);

  // read nucleus_coord
  coord = (double*) calloc(3*num, sizeof(double));
  rc = trexio_read_nucleus_coord(file,coord);
  assert (rc == TREXIO_SUCCESS);

  double x = coord[30] - 2.14171677;
  assert( x*x < 1.e-14);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // read non-existing file, should fail and return NULL
  const char* file_name2 = "test_nonexisting.h5";
  trexio_t* file2 = NULL;

  file2 = trexio_open(file_name2, 'r', TREXIO_HDF5);
  assert (file2 == NULL);

  // append non-existing file, should fail and return NULL
  trexio_t* file3 = NULL;

  file3 = trexio_open(file_name2, 'a', TREXIO_HDF5);
  assert (file3 == NULL);

/*================= END OF TEST =====================*/

  free(coord);
  return 0;
}


int test_write() {

/*========= Test write using TEXT backend ===========*/

  const char* file_name = "trexio_test";
  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be written
  int num = 12;
  float charge[12] = {6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1.};
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

  file = trexio_open(file_name, 'w', TREXIO_TEXT);
  assert (file != NULL);

  rc = trexio_has_nucleus_num(file);
  assert (rc == TREXIO_HAS_NOT);
  rc = trexio_has_nucleus_coord(file);
  assert (rc == TREXIO_HAS_NOT);

  rc = trexio_write_nucleus_num(file,num);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_nucleus_charge_32(file,charge);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_nucleus_coord(file,coord);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_has_nucleus_num(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_nucleus_coord(file);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST =====================*/

  return 0;
}

int test_read() {

/*========= Test read using TEXT backend ===========*/
	
  const char* file_name = "trexio_test";
  trexio_t* file = NULL;
  trexio_exit_code rc;

  int num;
  float* charge;
  double* coord;

/*================= START OF TEST ==================*/

  file = trexio_open(file_name, 'r', TREXIO_TEXT);
  assert (file != NULL);

  rc = trexio_read_nucleus_num(file,&num);
  assert (rc == TREXIO_SUCCESS);
  assert (num == 12);

  charge = (float*) calloc(num, sizeof(float));
  rc = trexio_read_nucleus_charge_32(file,charge);
  assert (rc == TREXIO_SUCCESS);
  assert(charge[10] == 1.);

  coord = (double*) calloc(3*num, sizeof(double));
  rc = trexio_read_nucleus_coord(file,coord);
  assert (rc == TREXIO_SUCCESS);

  double x = coord[30] - 2.14171677;
  assert(x*x < 1.e-14);

  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST =====================*/

  free(charge);
  free(coord);
  return 0;
}

