
#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_write(const char* file_name, const back_end_t backend);
int test_read(const char* file_name, const back_end_t backend);

int main() {

/*============== Main test launcher ================*/

  int rc;

  trexio_info();

  bool have_hdf5 = trexio_has_backend(TREXIO_HDF5);
  if(have_hdf5) {
    rc = system("rm -f -- test_all.h5");
    assert (rc == 0);
    test_write("test_all.h5", TREXIO_HDF5);
    test_read ("test_all.h5", TREXIO_HDF5);
    rc = system("rm -f -- test_all.h5");
    assert (rc == 0);
  }

  rc = system("rm -rf test_all.dir");
  assert (rc == 0);
  test_write("test_all.dir", TREXIO_TEXT);
  test_read ("test_all.dir", TREXIO_TEXT);
  rc = system("rm -rf test_all.dir");
  assert (rc == 0);

  return 0;
}

int test_write(const char* file_name, const back_end_t backend) {

/*======== Test write ===========*/

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

  const char* label[] = {"C" ,
                         "Na",
  	                 "ClH asdasdasdas" ,
        	         "C" ,
                	 "C 666" ,
	                 "C" ,
        	         "H" ,
                	 "Ru",
	                 "H" ,
        	         "H 999asdasd" ,
                	 "H" ,
	                 "H" };

  const char* sym = "B3U with some comments";
/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
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

  // check the force flushing
  rc = trexio_flush(file);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_nucleus_label(file, label, 32);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_write_nucleus_point_group(file, sym, 32);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // reopen file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);

  // check if the written data exists in the file
  rc = trexio_has_nucleus_num(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_nucleus_coord(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_nucleus_label(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_nucleus_point_group(file);
  assert (rc == TREXIO_SUCCESS);

  // should not work: try to overwrite the num variable
  rc = trexio_write_nucleus_num(file,25);
  printf("Test error message: %s\n", trexio_string_of_error(rc));
  assert (rc == TREXIO_ATTR_ALREADY_EXISTS);

  // should not work: try to overwrite the dset
  coord[0] = 666.666;
  rc = trexio_write_nucleus_coord(file,coord);
  assert (rc == TREXIO_DSET_ALREADY_EXISTS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // open file again in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);

  // write some missing blocks (e.g. if forgot last time)
  rc = trexio_write_nucleus_charge(file,charge);
  assert (rc == TREXIO_SUCCESS);

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

  // open existing file on 'read' mode [created by test_write]
  file = trexio_open(file_name, 'r', TREXIO_AUTO, &rc);
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
  free(coord);

  // read nucleus_label
  label = (char**) malloc(num*sizeof(char*));
  for (int i=0; i<num; i++){
    label[i] = (char*) malloc(32*sizeof(char));
  }

  rc = trexio_read_nucleus_label(file, label, 2);
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(label[0], "C")  == 0);
  assert (strcmp(label[1], "Na") == 0);

  for (int i=0; i<num; i++){
    free(label[i]);
  }
  free(label);

  point_group = (char*) malloc(32*sizeof(char));

  rc = trexio_read_nucleus_point_group(file, point_group, 6);
  assert (rc == TREXIO_SUCCESS);

  char * pch;
  pch = strtok(point_group, " ");
  assert (strcmp(pch, "B3U") == 0);
  /* alternative test when 3 symbols are read from the file to point_group */
  /*rc = trexio_read_nucleus_point_group(file, point_group, 3);
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(point_group, "B3U") == 0 );*/
  free(point_group);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // read non-existing file, should fail and return NULL
  const char* file_name2 = "test_nonexisting";
  trexio_t* file2 = NULL;

  file2 = trexio_open(file_name2, 'r', backend, &rc);
  assert (file2 == NULL);

/*================= END OF TEST =====================*/

  return 0;
}
