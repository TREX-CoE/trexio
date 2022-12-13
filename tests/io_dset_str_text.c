#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_BACKEND 	TREXIO_TEXT
#define TREXIO_FILE 	"test_dset_s.dir"
#define RM_COMMAND 	"rm -f -- " TREXIO_FILE "/*.txt " TREXIO_FILE "/*.txt.size " TREXIO_FILE "/.lock && rm -fd -- " TREXIO_FILE

static int test_write_dset_str (const char* file_name, const back_end_t backend) {

/* Try to write an array of strings into the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be written
  int num = 12;
  const char* labels[] = {"C"       ,
                          "Na FAKE" ,
                          "C"       ,
                          "C"       ,
                          "C"       ,
                          "C"       ,
                          "H"       ,
                          "H"       ,
                          "H"       ,
                          "H"       ,
                          "H"       ,
                          "H FAKE"  };

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);

  // write numerical attribute in an empty file
  rc = trexio_write_nucleus_num(file, num);
  assert (rc == TREXIO_SUCCESS);

  // write dataset of string in the file (including FAKE statements)
  int max_str_len = 16;
  rc = trexio_write_nucleus_label(file, labels, max_str_len);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_has_dset_str (const char* file_name, const back_end_t backend) {

/* Try to check the existence of a dataset of strings in the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);

  // check that the previously written dataset of strings exists
  rc = trexio_has_nucleus_label(file);
  assert (rc == TREXIO_SUCCESS);

  // check that the dataset of strings does not exist
  rc = trexio_has_mo_symmetry(file);
  assert (rc == TREXIO_HAS_NOT);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_read_dset_str (const char* file_name, const back_end_t backend) {

/* Try to read a dataset with strings from the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be read
  int num;
  char **labels;

/*================= START OF TEST ==================*/

  // open file in 'read' mode
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);

  // read numerical attribute from the file
  rc = trexio_read_nucleus_num(file, &num);
  assert (rc == TREXIO_SUCCESS);
  assert (num == 12);

  // read the arrays of strings truncated to max_str_len=2 symbols
  int max_str_len = 2;

  labels = (char**) malloc(num*sizeof(char*));
  for (int i=0; i<num; i++){
    labels[i] = (char*) malloc((max_str_len+1)*sizeof(char));
  }

  rc = trexio_read_nucleus_label(file, labels, max_str_len);
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(labels[0], "C")  == 0);
  assert (strcmp(labels[1], "Na") == 0);

  for (int i=0; i<num; i++){
    free(labels[i]);
  }
  free(labels);

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

  test_write_dset_str (TREXIO_FILE, TEST_BACKEND);
  test_has_dset_str   (TREXIO_FILE, TEST_BACKEND);
  test_read_dset_str  (TREXIO_FILE, TEST_BACKEND);

  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}
