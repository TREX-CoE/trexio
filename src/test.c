#include "trexio.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int test_read();
int test_write();

int test_h5read();
int test_h5write();

int main() {

  test_h5write();
  test_h5read();

  test_write();
  test_read();
  return 0 ;
}


int test_h5write() {
  const char* file_name = "test_write.h5";

  trexio_t* file = NULL;
  trexio_exit_code rc;

  rc = TREXIO_SUCCESS;

  int64_t num = 12;

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

  file = trexio_open(file_name, 'w', TREXIO_HDF5);
  assert (file != NULL);

  // works: try writing info in an empty file
  rc = trexio_write_nucleus_num(file,num);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_write_nucleus_coord(file,coord);
  assert (rc == TREXIO_SUCCESS);

  // should not work: try to rewrite the nucleus_num
  rc = trexio_write_nucleus_num(file,25);
  assert (rc != TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  file = trexio_open(file_name, 'a', TREXIO_HDF5);
  assert (file != NULL);
  
  // works: try to read the nucleus_num from existing file
  rc = trexio_read_nucleus_num(file,&num);
  assert (rc == TREXIO_SUCCESS);
  assert (num == 12);

  // works: try to rewrite the nucleus_coord
  coord[0] = 666.666;
  rc = trexio_write_nucleus_coord(file,coord);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  return 0;
}

int test_h5read() {
  const char* file_name = "test_write.h5";

  trexio_t* file = NULL;
  trexio_exit_code rc;

  int64_t num;
  double* coord;

  file = trexio_open(file_name, 'r', TREXIO_HDF5);
  assert (file != NULL);

  rc = trexio_read_nucleus_num(file,&num);
  assert (rc == TREXIO_SUCCESS);
  assert (num == 12);

  coord = (double*) calloc(3*num, sizeof(double));
  rc = trexio_read_nucleus_coord(file,coord);
  assert (rc == TREXIO_SUCCESS);

  /*for (size_t i=0; i<3*num; i++){
	  printf("%lf \n", coord[i]);
  }*/

  double x = coord[30] - 2.14171677;
  assert( x*x < 1.e-12);

  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  free(coord);

  return 0;
}


int test_write() {
  const char* file_name = "trexio_test";

  trexio_t* file = NULL;
  trexio_exit_code rc;


  int64_t num = 12;

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

  file = trexio_open(file_name, 'w', TREXIO_TEXT);
  assert (file != NULL);

  rc = trexio_write_nucleus_num(file,num);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_nucleus_charge(file,charge);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_nucleus_coord(file,coord);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  return 0;
}

int test_read() {
  const char* file_name = "trexio_test";

  trexio_t* file = NULL;
  trexio_exit_code rc;

  int64_t num;
  double* charge;
  double* coord;

  file = trexio_open(file_name, 'r', TREXIO_TEXT);
  assert (file != NULL);

  rc = trexio_read_nucleus_num(file,&num);
  assert (rc == TREXIO_SUCCESS);
  assert (num == 12);

  charge = (double*) calloc(num, sizeof(double));
  rc = trexio_read_nucleus_charge(file,charge);
  assert (rc == TREXIO_SUCCESS);
  assert(charge[10] == 1.);

  coord = (double*) calloc(3*num, sizeof(double));
  rc = trexio_read_nucleus_coord(file,coord);
  assert (rc == TREXIO_SUCCESS);

  double x = coord[30] - 2.14171677;
  assert( x*x < 1.e-12);

  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  free(charge);
  free(coord);

  return 0;
}

