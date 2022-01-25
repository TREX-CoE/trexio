#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_BACKEND 	TREXIO_HDF5
#define TREXIO_FILE 	"test_open.h5"
#define TREXIO_VOID 	"non_existing_" TREXIO_FILE
#define RM_COMMAND 	"rm -rf " TREXIO_FILE


static int test_open_w (const char* file_name, const back_end_t backend) {

/* Try to open the TREXIO file in 'write' mode */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_open_r (const char* file_name, const back_end_t backend) {

/* Try to open the TREXIO file in 'read' mode */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_open_auto (const char* file_name) {

/* Try to open the TREXIO file in 'read' mode */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'r', TREXIO_AUTO, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_open_errors (const back_end_t backend) {

/* Try to call trexio_open with bad arguments */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open non-existing file in 'r' (read) mode, should return TREXIO_OPEN_ERROR
  file = trexio_open(TREXIO_VOID, 'r', backend, &rc);
  assert (file == NULL);
  assert (rc == TREXIO_OPEN_ERROR);
  fprintf(stderr, "%s \n", trexio_string_of_error(rc));

  // open file with empty file name, should return TREXIO_INVALID_ARG_1
  file = trexio_open("", 'w', backend, &rc);
  assert (file == NULL);
  assert (rc == TREXIO_INVALID_ARG_1);
  fprintf(stderr, "%s \n", trexio_string_of_error(rc));

  // open existing file in non-supported I/O mode, should return TREXIO_INVALID_ARG_2
  file = trexio_open(TREXIO_FILE, 'k', backend, &rc);
  assert (file == NULL);
  assert (rc == TREXIO_INVALID_ARG_2);
  fprintf(stderr, "%s \n", trexio_string_of_error(rc));

  // open existing file with non-supported back end, should return TREXIO_INVALID_ARG_3
  file = trexio_open(TREXIO_FILE, 'w', 666, &rc);
  assert (file == NULL);
  assert (rc == TREXIO_INVALID_ARG_3);
  fprintf(stderr, "%s \n", trexio_string_of_error(rc));

/*================= END OF TEST ==================*/

  return 0;
}


static int test_inquire (const back_end_t backend) {

/* Try to call trexio_inquire function */

  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // inquire non-existing file
  rc = trexio_inquire(TREXIO_VOID);
  assert (rc == TREXIO_FAILURE);

  // inquire existing file
  rc = trexio_inquire(TREXIO_FILE);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


int main(void) {

/*============== Test launcher ================*/

  int rc;
  rc = system(RM_COMMAND);
  assert (rc == 0);

  test_open_w     (TREXIO_FILE, TEST_BACKEND);
  test_open_r     (TREXIO_FILE, TEST_BACKEND);
  test_open_auto  (TREXIO_FILE);
  test_open_errors(TEST_BACKEND);
  test_inquire    (TEST_BACKEND);

  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}
