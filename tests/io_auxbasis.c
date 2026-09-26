#include "trexio.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static const char expected_auxbasis_description[] = "SCF auxiliary basis";
static const char expected_auxbasis2_description[] = "MP2 auxiliary basis";

static int test_write_auxbasis(const char* file_name, const back_end_t backend) {

/* Try to write independent auxbasis and auxbasis2 data into the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  const int32_t nucleus_num = 2;
  const int32_t auxbasis_shell_num = 3;
  const int32_t auxbasis2_shell_num = 2;
  const int32_t auxbasis_nucleus_index[3] = {0, 1, 0};
  const int32_t auxbasis2_nucleus_index[2] = {1, 1};

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
  rc = trexio_write_auxbasis_description(file, expected_auxbasis_description,
                                         sizeof(expected_auxbasis_description));
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_auxbasis2_shell_num(file, auxbasis2_shell_num);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_write_auxbasis2_nucleus_index(file, auxbasis2_nucleus_index);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_write_auxbasis2_description(file, expected_auxbasis2_description,
                                          sizeof(expected_auxbasis2_description));
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

  int32_t auxbasis_shell_num = 0;
  int32_t auxbasis2_shell_num = 0;
  const int32_t expected_auxbasis_nucleus_index[3] = {0, 1, 0};
  const int32_t expected_auxbasis2_nucleus_index[2] = {1, 1};
  int32_t auxbasis_nucleus_index[3] = {-1, -1, -1};
  int32_t auxbasis2_nucleus_index[2] = {-1, -1};
  char auxbasis_description[sizeof(expected_auxbasis_description)];
  char auxbasis2_description[sizeof(expected_auxbasis2_description)];
  char auxbasis_description_short[sizeof("SCF")];
  char auxbasis2_description_short[sizeof("MP2")];

/*================= START OF TEST ==================*/

  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_read_auxbasis_shell_num(file, &auxbasis_shell_num);
  assert (rc == TREXIO_SUCCESS);
  assert (auxbasis_shell_num == 3);

  rc = trexio_read_auxbasis_nucleus_index(file, auxbasis_nucleus_index);
  assert (rc == TREXIO_SUCCESS);
  assert (memcmp(auxbasis_nucleus_index, expected_auxbasis_nucleus_index,
                 sizeof(expected_auxbasis_nucleus_index)) == 0);

  rc = trexio_read_auxbasis_description(file, auxbasis_description,
                                        sizeof(auxbasis_description));
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(auxbasis_description, expected_auxbasis_description) == 0);
  rc = trexio_read_auxbasis_description(file, auxbasis_description_short,
                                        sizeof(auxbasis_description_short));
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(auxbasis_description_short, "SCF") == 0);

  rc = trexio_read_auxbasis2_shell_num(file, &auxbasis2_shell_num);
  assert (rc == TREXIO_SUCCESS);
  assert (auxbasis2_shell_num == 2);

  rc = trexio_read_auxbasis2_nucleus_index(file, auxbasis2_nucleus_index);
  assert (rc == TREXIO_SUCCESS);
  assert (memcmp(auxbasis2_nucleus_index, expected_auxbasis2_nucleus_index,
                 sizeof(expected_auxbasis2_nucleus_index)) == 0);

  rc = trexio_read_auxbasis2_description(file, auxbasis2_description,
                                         sizeof(auxbasis2_description));
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(auxbasis2_description, expected_auxbasis2_description) == 0);
  rc = trexio_read_auxbasis2_description(file, auxbasis2_description_short,
                                         sizeof(auxbasis2_description_short));
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp(auxbasis2_description_short, "MP2") == 0);

  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}

static int test_write_auxbasis2_only(const char* file_name, const back_end_t backend) {

/* Try to write only auxbasis2 data into the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  const int32_t nucleus_num = 2;
  const int32_t auxbasis2_shell_num = 2;
  const int32_t auxbasis2_nucleus_index[2] = {1, 1};

/*================= START OF TEST ==================*/

  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_nucleus_num(file, nucleus_num);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_auxbasis2_shell_num(file, auxbasis2_shell_num);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_write_auxbasis2_nucleus_index(file, auxbasis2_nucleus_index);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}

static int test_has_auxbasis2_isolation(const char* file_name, const back_end_t backend) {

/* Try to check that auxbasis stays absent when only auxbasis2 is written */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_has_auxbasis(file);
  assert (rc == TREXIO_HAS_NOT);
  rc = trexio_has_auxbasis_shell_num(file);
  assert (rc == TREXIO_HAS_NOT);
  rc = trexio_has_auxbasis_nucleus_index(file);
  assert (rc == TREXIO_HAS_NOT);

  rc = trexio_has_auxbasis2(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_auxbasis2_shell_num(file);
  assert (rc == TREXIO_SUCCESS);
  rc = trexio_has_auxbasis2_nucleus_index(file);
  assert (rc == TREXIO_SUCCESS);

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

  test_write_auxbasis2_only    (TREXIO_FILE, TEST_BACKEND);
  test_has_auxbasis2_isolation (TREXIO_FILE, TEST_BACKEND);

  rc = RM_COMMAND_RESULT;
  assert (rc == 0);

  return 0;
}
