#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_BACKEND 	TREXIO_HDF5
#define TREXIO_FILE 	"test.h5"
#define RM_COMMAND 	"rm -rf " TREXIO_FILE

static int test_write (const char* file_name, const back_end_t backend) {

/* Try to write a full set of data (num+dset_num+str+dset_str) related to benzene molecule into the TREXIO file */

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
  const char* sym = "D6h";
  const char* labels[] = {"C" ,
                          "C" ,
                          "C" ,
                          "C" ,
                          "C" ,
                          "C" ,
                          "H" ,
                          "H" ,
                          "H" ,
                          "H" ,
                          "H" ,
                          "H" };

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend);
  assert (file != NULL);

  // write the data
  rc = trexio_write_nucleus_num(file, num);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_nucleus_coord(file, coord);
  assert (rc == TREXIO_SUCCESS);
  
  rc = trexio_write_nucleus_point_group(file, sym, 4);
  assert (rc == TREXIO_SUCCESS);
  
  rc = trexio_write_nucleus_label(file, labels, 2);
  assert (rc == TREXIO_SUCCESS);
  
  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_overwrite (const char* file_name, const back_end_t backend) {

/* Try to overwrite the data that already exists in the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be written
  int num = 24;
  double coord[3] = {
  0.00000000 ,  666.666,  0.00000000 ,
  };
  const char* sym = "Unknown";
  const char* labels[] = {"Ru" ,
                          "U"  ,
                          "Cl" ,
                          "Na" ,
                          "H" };

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend);
  assert (file != NULL);

  // check that the previously written data cannot be overwritten
  rc = trexio_write_nucleus_num(file, num);
  assert (rc == TREXIO_ATTR_ALREADY_EXISTS);

  rc = trexio_write_nucleus_coord(file, coord);
  assert (rc == TREXIO_DSET_ALREADY_EXISTS);
  
  rc = trexio_write_nucleus_point_group(file, sym, 16);
  assert (rc == TREXIO_ATTR_ALREADY_EXISTS);
  
  rc = trexio_write_nucleus_label(file, labels, 4);
  assert (rc == TREXIO_DSET_ALREADY_EXISTS);

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

  test_write     (TREXIO_FILE, TEST_BACKEND);
  test_overwrite (TREXIO_FILE, TEST_BACKEND);

  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}


