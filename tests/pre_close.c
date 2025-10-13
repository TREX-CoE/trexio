#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TEST_BACKEND  TREXIO_TEXT
#define TREXIO_FILE 	"test_pre_close.dir"

/* Portable cleanup function to replace system() calls */
static int trexio_cleanup_test_file_pre_close(const char* file_path) {
    trexio_exit_code rc;
    
    /* First check if the file/directory exists */
    if (trexio_inquire(file_path) != TREXIO_SUCCESS) {
        return 0; /* File doesn't exist, cleanup successful */
    }
    
    rc = trexio_remove_directory_recursive(file_path);
    return (rc == TREXIO_SUCCESS) ? 0 : 1;
}

#define RM_COMMAND_RESULT  trexio_cleanup_test_file_pre_close(TREXIO_FILE)

static int test_pre_close_1 (const char* file_name, const back_end_t backend)
{
/* Check if nelec = nup + ndn */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  // write parameters
  int32_t nup = 4;
  int32_t ndn = 3;
  int32_t nelec = 0;

  rc = trexio_write_electron_up_num(file, nup);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_electron_dn_num(file, ndn);
  assert (rc == TREXIO_SUCCESS);

  // close file
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);


  // re-open file
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_read_electron_num(file, &nelec);
  assert (rc == TREXIO_SUCCESS);
  printf("nup  : %d\n", nup);
  printf("ndn  : %d\n", ndn);
  printf("nelec: %d\n", nelec);
  assert (nelec == nup + ndn);

  // close file
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}

static int test_pre_close_2 (const char* file_name, const back_end_t backend)
{
/* Check if nelec = nup */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  // write parameters
  int32_t nup = 4;
  int32_t nelec = 0;

  rc = trexio_write_electron_up_num(file, nup);
  assert (rc == TREXIO_SUCCESS);

  // close file
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);


  // re-open file
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_read_electron_num(file, &nelec);
  assert (rc == TREXIO_SUCCESS);
  assert (nelec == nup);

  // close file
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


int main()
{
/*============== Test launcher ================*/

  int rc;
  rc = RM_COMMAND_RESULT;
  assert (rc == 0);

  test_pre_close_1 (TREXIO_FILE, TEST_BACKEND);
  rc = RM_COMMAND_RESULT;

  test_pre_close_2 (TREXIO_FILE, TEST_BACKEND);

  rc = RM_COMMAND_RESULT;
  assert (rc == 0);

  return 0;
}
