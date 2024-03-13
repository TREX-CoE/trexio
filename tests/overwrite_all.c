#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  file = trexio_open(file_name, 'w', backend, &rc);
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


static int test_overwrite_unsafe (const char* file_name, const back_end_t backend) {

/* Try to overwrite the data that already exists in the TREXIO file which is open in UNSAFE mode*/

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be written
  int num = 5;
  double coord[15] = {
  0.00000000 ,  666.666    ,  0.00000000 ,
 -1.20594314 ,  0.69625160 ,  0.00000000 ,
 -1.20594314 , -0.69625160 ,  0.00000000 ,
  0.00000000 , -1.39250319 ,  0.00000000 ,
  1.20594314 , -0.69625160 ,  0.00000000
  };
  const char* sym = "Unknown";
  const char* labels[] = {"Ru" ,
                          "U"  ,
                          "Cl" ,
                          "Na" ,
                          "H" };

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'u', backend, &rc);
  assert (file != NULL);

  // check that the previously written data cannot be overwritten
  rc = trexio_write_nucleus_num(file, num);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_nucleus_coord(file, coord);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_nucleus_point_group(file, sym, 16);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_nucleus_label(file, labels, 4);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_overwrite_safe (const char* file_name, const back_end_t backend) {

/* Try to overwrite the data that already exists in the TREXIO file which is open in SAFE mode*/

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
  file = trexio_open(file_name, 'w', backend, &rc);
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


int test_read(const char* file_name, const back_end_t backend) {

/*========= Test read ===========*/

  trexio_t* file = NULL;
  trexio_exit_code rc;

  int num;
  double* coord;
  char** label;
  char* point_group;

/*================= START OF TEST ==================*/

  // open existing file on 'read' mode
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);

  // read nucleus_num
  rc = trexio_read_nucleus_num(file,&num);
  assert (rc == TREXIO_SUCCESS);
  assert (num == 5);

  // read nucleus_coord
  coord = (double*) calloc(3*num, sizeof(double));
  rc = trexio_read_nucleus_coord(file,coord);
  assert (rc == TREXIO_SUCCESS);

  double x = coord[1] - 666.666;
  assert( x*x < 1.e-14);
  free(coord);

  // read nucleus_label
  label = (char**) malloc(num*sizeof(char*));
  for (int i=0; i<num; i++){
    label[i] = (char*) malloc(32*sizeof(char));
  }

  rc = trexio_read_nucleus_label(file, label, 2);
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(label[0], "Ru")  == 0);
  assert (strcmp(label[3], "Na") == 0);

  for (int i=0; i<num; i++){
    free(label[i]);
  }
  free(label);

  point_group = (char*) malloc(32*sizeof(char));

  rc = trexio_read_nucleus_point_group(file, point_group, 10);
  assert (rc == TREXIO_SUCCESS);

  char * pch;
  pch = strtok(point_group, " ");
  assert (strcmp(pch, "Unknown") == 0);
  /* alternative test when 3 symbols are read from the file to point_group */
  /*rc = trexio_read_nucleus_point_group(file, point_group, 3);
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(point_group, "B3U") == 0 );*/
  free(point_group);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST =====================*/

  return 0;
}


int main(void) {

/*============== Test launcher ================*/

  int rc;
  rc = system(RM_COMMAND);
  assert (rc == 0);

  test_write            (TREXIO_FILE, TEST_BACKEND);
  test_overwrite_safe   (TREXIO_FILE, TEST_BACKEND);
  test_overwrite_unsafe (TREXIO_FILE, TEST_BACKEND);
  test_read             (TREXIO_FILE, TEST_BACKEND);

  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}
