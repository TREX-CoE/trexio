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


static int test_pre_close_3 (const char* file_name, const back_end_t backend)
{
/* Test that writing both ao.cartesian and ao.cartesian_shell fails with TREXIO_AMBIGUOUS_CARTESIAN */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file in 'w' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert(file != NULL);
  assert(rc == TREXIO_SUCCESS);

  // Minimal basis setup required to write ao.cartesian_shell (needs basis.shell_num)
  int32_t shell_num = 2;
  rc = trexio_write_basis_shell_num(file, shell_num);
  assert(rc == TREXIO_SUCCESS);

  // ao.num is typically the dimensioning attribute — write it so the ao group is valid
  int32_t ao_num = 6;
  rc = trexio_write_ao_num(file, ao_num);
  assert(rc == TREXIO_SUCCESS);

  // Write ao.cartesian (sets all shells to cartesian)
  int32_t cartesian_value = 1;
  rc = trexio_write_ao_cartesian(file, cartesian_value);
  assert(rc == TREXIO_SUCCESS);

  // Write ao.cartesian_shell per shell (shells: [0, 0] means all spherical, but having both flags is invalid)
  int32_t shell_flags[2] = {0, 1};
  rc = trexio_write_ao_cartesian_shell(file, shell_flags);
  assert(rc == TREXIO_SUCCESS);

  // Close file — should fail with TREXIO_AMBIGUOUS_CARTESIAN
  rc = trexio_close(file);
  assert(rc == TREXIO_AMBIGUOUS_CARTESIAN);
  printf("Correctly detected ambiguous cartesian/cartesian_shell at close.\n");

/*================= END OF TEST ==================*/

  return 0;
}


static int test_cartesian_valid_writes (const char* file_name, const back_end_t backend)
{
/* Test that writing exactly one of ao.cartesian or ao.cartesian_shell succeeds */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*--- Only ao.cartesian (should succeed) ---*/

  // Cleanup from test_pre_close_3 if directory still exists
  int cleanup_rc;
  do { cleanup_rc = trexio_cleanup_test_file_pre_close(file_name); } while (cleanup_rc == 0 && trexio_inquire(file_name) == TREXIO_SUCCESS);

  file = trexio_open(file_name, 'w', backend, &rc);
  assert(file != NULL);
  assert(rc == TREXIO_SUCCESS);

  int32_t shell_num = 2;
  rc = trexio_write_basis_shell_num(file, shell_num);
  assert(rc == TREXIO_SUCCESS);

  int32_t ao_num = 6;
  rc = trexio_write_ao_num(file, ao_num);
  assert(rc == TREXIO_SUCCESS);

  // Write only ao.cartesian (no cartesian_shell)
  int32_t cartesian_value = 0;
  rc = trexio_write_ao_cartesian(file, cartesian_value);
  assert(rc == TREXIO_SUCCESS);

  rc = trexio_close(file);
  assert(rc == TREXIO_SUCCESS);

/*--- Reopen and verify ---*/

  file = trexio_open(file_name, 'r', backend, &rc);
  assert(file != NULL);
  assert(rc == TREXIO_SUCCESS);

  trexio_exit_code cartesian_exists = trexio_has_ao_cartesian(file);
  assert(cartesian_exists == TREXIO_SUCCESS);

  int read_val = -1;
  rc = trexio_read_ao_cartesian(file, &read_val);
  assert(rc == TREXIO_SUCCESS);
  assert(read_val == 0);

  trexio_exit_code shell_exists = trexio_has_ao_cartesian_shell(file);
  assert(shell_exists == TREXIO_HAS_NOT); // should NOT have cartesian_shell

  rc = trexio_close(file);
  assert(rc == TREXIO_SUCCESS);

/*--- Now test with a fresh file using ao.cartesian_shell (should also succeed) ---*/

  do { cleanup_rc = trexio_cleanup_test_file_pre_close(file_name); } while (cleanup_rc == 0 && trexio_inquire(file_name) == TREXIO_SUCCESS);

  file = trexio_open(file_name, 'w', backend, &rc);
  assert(file != NULL);
  assert(rc == TREXIO_SUCCESS);

  shell_num = 2;
  rc = trexio_write_basis_shell_num(file, shell_num);
  assert(rc == TREXIO_SUCCESS);

  ao_num = 6;
  rc = trexio_write_ao_num(file, ao_num);
  assert(rc == TREXIO_SUCCESS);

  // Write only ao.cartesian_shell (no cartesian)
  int32_t shell_flags[2] = {0, 1};
  rc = trexio_write_ao_cartesian_shell(file, shell_flags);
  assert(rc == TREXIO_SUCCESS);

  rc = trexio_close(file);
  assert(rc == TREXIO_SUCCESS);

/*--- Reopen and verify ---*/

  file = trexio_open(file_name, 'r', backend, &rc);
  assert(file != NULL);
  assert(rc == TREXIO_SUCCESS);

  trexio_exit_code shell_exists2 = trexio_has_ao_cartesian_shell(file);
  assert(shell_exists2 == TREXIO_SUCCESS);

  int32_t shell_read[2];
  rc = trexio_read_ao_cartesian_shell(file, shell_read);
  assert(rc == TREXIO_SUCCESS);
  assert(shell_read[0] == 0);
  assert(shell_read[1] == 1);

  trexio_exit_code cartesian_exists2 = trexio_has_ao_cartesian(file);
  assert(cartesian_exists2 == TREXIO_HAS_NOT);

  rc = trexio_close(file);
  assert(rc == TREXIO_SUCCESS);

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

  test_pre_close_3 (TREXIO_FILE, TEST_BACKEND);
  rc = RM_COMMAND_RESULT;

  test_cartesian_valid_writes (TREXIO_FILE, TEST_BACKEND);
  rc = RM_COMMAND_RESULT;

  assert (rc == 0);

  return 0;
}
