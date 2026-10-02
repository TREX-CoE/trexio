#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


static int test_write_dset_str_edge_len (const char* file_name, const back_end_t backend) {

/* Regression test for https://github.com/TREX-CoE/trexio/issues/277 :
   writing a string dataset whose elements are exactly max_str_len long used to
   overflow the compiled string buffer because the delimiter appended after
   each element was not accounted for in the buffer size. */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // one author name of exactly 34 characters, as in the reproducer from the issue
  const char* authors[] = {"0123456789abcdef" "0123456789abcdef" "01"};
  int author_num = 1;

/*================= START OF TEST ==================*/

  // open file in 'u' (update) mode so it can be reused after test_write_dset_str
  file = trexio_open(file_name, 'u', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_metadata_author_num(file, author_num);
  assert (rc == TREXIO_SUCCESS);

  // max_str_len set exactly to the length of the longest author name (34)
  int max_str_len = (int) strlen(authors[0]) + 1;
  rc = trexio_write_metadata_author(file, authors, max_str_len);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_read_dset_str_edge_len (const char* file_name, const back_end_t backend) {

/* Read back the author name written by test_write_dset_str_edge_len and check
   that it was not corrupted by the buffer overflow. */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  char** authors;
  int author_num = 1;
  int max_str_len = 34;

/*================= START OF TEST ==================*/

  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  authors = (char**) malloc(author_num*sizeof(char*));
  for (int i=0; i<author_num; i++){
    authors[i] = (char*) malloc((max_str_len+1)*sizeof(char));
  }

  rc = trexio_read_metadata_author(file, authors, max_str_len);
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(authors[0], "0123456789abcdef0123456789abcdef01") == 0);

  for (int i=0; i<author_num; i++){
    free(authors[i]);
  }
  free(authors);

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
  assert (rc == TREXIO_SUCCESS);

  // check that the previously written dataset of strings exists
  rc = trexio_has_nucleus_label(file);
  if (rc != TREXIO_SUCCESS) {
     printf("%s\n", trexio_string_of_error(rc));
  }
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
  char** labels;

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
  rc = RM_COMMAND_RESULT;
  assert (rc == 0);

  test_write_dset_str (TREXIO_FILE, TEST_BACKEND);
  test_has_dset_str   (TREXIO_FILE, TEST_BACKEND);
  test_read_dset_str  (TREXIO_FILE, TEST_BACKEND);

  test_write_dset_str_edge_len (TREXIO_FILE, TEST_BACKEND);
  test_read_dset_str_edge_len  (TREXIO_FILE, TEST_BACKEND);

  rc = RM_COMMAND_RESULT;
  assert (rc == 0);

  return 0;
}
