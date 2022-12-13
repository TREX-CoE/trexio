#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_BACKEND 	TREXIO_TEXT
#define TREXIO_FILE 	"test_str.dir"
#define RM_COMMAND 	"rm -f -- " TREXIO_FILE "/*.txt " TREXIO_FILE "/*.txt.size " TREXIO_FILE "/.lock && rm -fd -- " TREXIO_FILE

static int test_write_str (const char* file_name, const back_end_t backend) {

/* Try to write a string attribute (single variable-length string) into the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be written
  const char* sym = "B3U with some comments";

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);

  // write string attribute in an empty file
  int max_str_len = 32;
  rc = trexio_write_nucleus_point_group(file, sym, max_str_len);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_has_str (const char* file_name, const back_end_t backend) {

/* Try to check the existence of a string attribute in the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);

  // check that the previously written string attribute exists
  rc = trexio_has_nucleus_point_group(file);
  assert (rc == TREXIO_SUCCESS);

  // check that another string attribute does not exist
  rc = trexio_has_mo_type(file);
  assert (rc == TREXIO_HAS_NOT);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_read_str (const char* file_name, const back_end_t backend) {

/* Try to read a string attribute from the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be read
  char* sym;

/*================= START OF TEST ==================*/

  // open file in 'read' mode
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);

  // read string attribute from the file
  int max_str_len = 32;
  sym = (char*) malloc(max_str_len*sizeof(char));

  rc = trexio_read_nucleus_point_group(file, sym, max_str_len);
  assert (rc == TREXIO_SUCCESS);

  char * pch;
  pch = strtok(sym, " ");
  assert (strcmp(pch, "B3U") == 0);
  /* alternative test when 3 symbols are read from the file to sym */
  /*rc = trexio_read_nucleus_point_group(file, sym, 3);
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(sym, "B3U") == 0 );*/
  free(sym);

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

  test_write_str (TREXIO_FILE, TEST_BACKEND);
  test_has_str   (TREXIO_FILE, TEST_BACKEND);
  test_read_str  (TREXIO_FILE, TEST_BACKEND);

  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}
