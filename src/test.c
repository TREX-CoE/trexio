#include "trio.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int test_read();
int test_write();

int test_h5read();

int main() {
  test_h5read();
  test_write();
  test_read();
  return 0 ;
}


int test_h5read() {
  const char* file_name = "test.h5";

  trio_t* file = NULL;
  trio_exit_code rc;

  uint64_t num;
  //double* charge;
  double* coord;

  file = trio_create(file_name, TRIO_HDF5);

  /*rc = trio_read_nucleus_num(file,&num);
  assert (num == 12);

  charge = (double*) calloc(num, sizeof(double));
  rc = trio_read_nucleus_charge(file,charge);
  assert(charge[10] == 1.);*/
  num = 4;

  coord = (double*) calloc(3*num, sizeof(double));
  rc = trio_read_nucleus_coord(file,coord);
  
  for (size_t i=0; i<3*num; i++){
	  printf("%lf \n", coord[i]);
  }

  double x = coord[0] - 2.14171677;
  assert( x*x < 1000.);

  if (rc == TRIO_SUCCESS) {
    printf("SUCCESS\n");
  } else {
    printf("FAILURE\n");
  }

  trio_close(file);

  return 0;
}


int test_write() {
  const char* file_name = "trio_test";

  trio_t* file = NULL;
  trio_exit_code rc;


  uint64_t num = 12;

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

  file = trio_create(file_name, TRIO_TEXT);

  rc = trio_write_nucleus_num(file,num);
  rc = trio_write_nucleus_charge(file,charge);
  rc = trio_write_nucleus_coord(file,coord);

  if (rc == TRIO_SUCCESS) {
    printf("SUCCESS\n");
  } else {
    printf("FAILURE\n");
  }

  trio_close(file);

  return 0;
}

int test_read() {
  const char* file_name = "trio_test";

  trio_t* file = NULL;
  trio_exit_code rc;

  uint64_t num;
  double* charge;
  double* coord;

  file = trio_create(file_name, TRIO_TEXT);

  rc = trio_read_nucleus_num(file,&num);
  assert (num == 12);

  charge = (double*) calloc(num, sizeof(double));
  rc = trio_read_nucleus_charge(file,charge);
  assert(charge[10] == 1.);

  coord = (double*) calloc(3*num, sizeof(double));
  rc = trio_read_nucleus_coord(file,coord);
  double x = coord[30] - 2.14171677;
  assert( x*x < 1.e-12);

  if (rc == TRIO_SUCCESS) {
    printf("SUCCESS\n");
  } else {
    printf("FAILURE\n");
  }

  trio_close(file);

  return 0;
}

