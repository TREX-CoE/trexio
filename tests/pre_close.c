#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TEST_BACKEND  TREXIO_TEXT
#define TREXIO_FILE 	"test_pre_close.dir"
#define RM_COMMAND 	"rm -f -- " TREXIO_FILE "/*.txt " TREXIO_FILE "/*.txt.size " TREXIO_FILE "/.lock && rm -fd -- " TREXIO_FILE

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
  rc = system(RM_COMMAND);
  assert (rc == 0);

  test_pre_close_1 (TREXIO_FILE, TEST_BACKEND);
  rc = system(RM_COMMAND);

  test_pre_close_2 (TREXIO_FILE, TEST_BACKEND);

  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}
