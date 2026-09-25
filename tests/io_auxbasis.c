#include "trexio.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static int test_write_auxbasis(const char* file_name, const back_end_t backend) {

/* Try to write independent auxbasis and auxbasis2 data into the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  const int nucleus_num = 2;
  const int auxbasis_shell_num = 3;
  const int auxbasis2_shell_num = 2;
  const int auxbasis_nucleus_index[3] = {0, 1, 0};
  const int auxbasis2_nucleus_index[2] = {1, 1};
  const char* auxbasis_description = "SCF auxiliary basis";
  const char* auxbasis2_description = "MP2 auxiliary basis";
  const int max_str_len = 32;

/*================= START OF TEST ==================*/

  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_nucleus_num(file, nucleus_num);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_auxbasis_shell_num(file, auxbasis_shell_num);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_write_auxbasis_nucleus_index(file, auxbasis_nucleus_index);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_write_auxbasis_description(file, auxbasis_description, max_str_len);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_auxbasis2_shell_num(file, auxbasis2_shell_num);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_write_auxbasis2_nucleus_index(file, auxbasis2_nucleus_index);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_write_auxbasis2_description(file, auxbasis2_description, max_str_len);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}

static int test_has_auxbasis(const char* file_name, const back_end_t backend) {

/* Try to check the existence of auxbasis and auxbasis2 data in the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_has_auxbasis(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_auxbasis_shell_num(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_auxbasis_nucleus_index(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_auxbasis_description(file);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_has_auxbasis2(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_auxbasis2_shell_num(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_auxbasis2_nucleus_index(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_auxbasis2_description(file);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}

static int test_read_auxbasis(const char* file_name, const back_end_t backend) {

/* Try to read back independent auxbasis and auxbasis2 data from the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  int auxbasis_shell_num = 0;
  int auxbasis2_shell_num = 0;
  int auxbasis_nucleus_index[3] = {-1, -1, -1};
  int auxbasis2_nucleus_index[2] = {-1, -1};
  char auxbasis_description[32];
  char auxbasis2_description[32];

/*================= START OF TEST ==================*/

  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_read_auxbasis_shell_num(file, &auxbasis_shell_num);
  assert (rc == TREXIO_SUCCESS);
  assert (auxbasis_shell_num == 3);

  rc = trexio_read_auxbasis_nucleus_index(file, auxbasis_nucleus_index);
  assert (rc == TREXIO_SUCCESS);
  assert (auxbasis_nucleus_index[0] == 0);
  assert (auxbasis_nucleus_index[1] == 1);
  assert (auxbasis_nucleus_index[2] == 0);

  rc = trexio_read_auxbasis_description(file, auxbasis_description, 32);
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(auxbasis_description, "SCF auxiliary basis") == 0);

  rc = trexio_read_auxbasis2_shell_num(file, &auxbasis2_shell_num);
  assert (rc == TREXIO_SUCCESS);
  assert (auxbasis2_shell_num == 2);

  rc = trexio_read_auxbasis2_nucleus_index(file, auxbasis2_nucleus_index);
  assert (rc == TREXIO_SUCCESS);
  assert (auxbasis2_nucleus_index[0] == 1);
  assert (auxbasis2_nucleus_index[1] == 1);

  rc = trexio_read_auxbasis2_description(file, auxbasis2_description, 32);
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(auxbasis2_description, "MP2 auxiliary basis") == 0);

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

  test_write_auxbasis (TREXIO_FILE, TEST_BACKEND);
  test_has_auxbasis   (TREXIO_FILE, TEST_BACKEND);
  test_read_auxbasis  (TREXIO_FILE, TEST_BACKEND);

  rc = RM_COMMAND_RESULT;
  assert (rc == 0);

  return 0;
}
