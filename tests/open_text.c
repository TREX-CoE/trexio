#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_BACKEND 	TREXIO_TEXT
#define TREXIO_FILE 	"test_open.dir"
#define TREXIO_VOID 	"non_existing_" TREXIO_FILE
#define RM_COMMAND 	"rm -rf " TREXIO_FILE


static int test_open_w (const char* file_name, const back_end_t backend) {

/* Try to open the TREXIO file in 'write' mode */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend);
  assert (file != NULL);

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
  file = trexio_open(file_name, 'r', backend);
  assert (file != NULL);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_open_void (const char* file_name, const back_end_t backend) {

/* Try to open the non-existing TREXIO file in 'read' mode */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file in 'read' mode
  file = trexio_open(file_name, 'r', backend);
  assert (file == NULL);

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
  test_open_void  (TREXIO_VOID, TEST_BACKEND);

  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}


