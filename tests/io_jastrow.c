#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int test_write_jastrow (const char* file_name, const back_end_t backend) {

/* Try to write an array of sparse data into the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

#define nucleus_num  3
#define ee_num 2
#define en_num 3
#define een_num 6

  rc = trexio_write_nucleus_num(file, nucleus_num);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_jastrow_type(file, "CHAMP", 6);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_jastrow_ee_num(file, ee_num);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_jastrow_en_num(file, en_num);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_jastrow_een_num(file, een_num);
  assert (rc == TREXIO_SUCCESS);

  double ee [2] = { 0.5, 2. };
  rc = trexio_write_jastrow_ee(file, ee);
  assert (rc == TREXIO_SUCCESS);

  double en [3] = { 1., 2., 3. };
  rc = trexio_write_jastrow_en(file, en);
  assert (rc == TREXIO_SUCCESS);

  double een [6] = { 11., 12., 13., 14., 15., 16. };
  rc = trexio_write_jastrow_een(file, een);
  assert (rc == TREXIO_SUCCESS);

  int en_nucleus [3] = { 0, 1, 2 };
  rc = trexio_write_jastrow_en_nucleus(file, en_nucleus);
  assert (rc == TREXIO_SUCCESS);

  int een_nucleus [6] = { 0, 0, 1, 1, 2, 2 };
  rc = trexio_write_jastrow_een_nucleus(file, een_nucleus);
  assert (rc == TREXIO_SUCCESS);

  double ee_scaling = 1.0;
  rc = trexio_write_jastrow_ee_scaling(file, ee_scaling);
  assert (rc == TREXIO_SUCCESS);

  double en_scaling[3] = { 0.5, 1.0, 0.5 };
  rc = trexio_write_jastrow_en_scaling(file, en_scaling);
  assert (rc == TREXIO_SUCCESS);

#undef nucleus_num
#undef ee_num
#undef en_num
#undef een_num

  rc = trexio_close(file);
/*================= END OF TEST ==================*/

  return 0;
}

static int test_read_jastrow (const char* file_name, const back_end_t backend) {

/* Try to read one chunk of dataset of sparse data in the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  int nucleus_num = 0;
  rc = trexio_read_nucleus_num(file, &nucleus_num);
  assert (rc == TREXIO_SUCCESS);
  assert (nucleus_num == 3);

  char type[16] = "";
  rc = trexio_read_jastrow_type(file, type, 16);
  assert (rc == TREXIO_SUCCESS);
  assert (strcmp("CHAMP",type) == 0);

  int ee_num = 0;
  rc = trexio_read_jastrow_ee_num(file, &ee_num);
  assert (rc == TREXIO_SUCCESS);
  assert (ee_num == 2);

  int en_num = 0;
  rc = trexio_read_jastrow_en_num(file, &en_num);
  assert (rc == TREXIO_SUCCESS);
  assert (en_num == nucleus_num);

  int een_num = 0;
  rc = trexio_read_jastrow_een_num(file, &een_num);
  assert (rc == TREXIO_SUCCESS);
  assert (een_num == 2*nucleus_num);

  double ee [2] = { 0., 0. };
  rc = trexio_read_jastrow_ee(file, ee);
  assert (rc == TREXIO_SUCCESS);
  assert (ee[0] == 0.5);
  assert (ee[1] == 2.0);

  double en [3] = { 0., 0., 0. };
  rc = trexio_read_jastrow_en(file, en);
  assert (rc == TREXIO_SUCCESS);
  assert (en[0] == 1.0);
  assert (en[1] == 2.0);
  assert (en[2] == 3.0);

  double een [6];
  rc = trexio_read_jastrow_een(file, een);
  assert (rc == TREXIO_SUCCESS);
  assert (een[0] == 11.0);
  assert (een[1] == 12.0);
  assert (een[2] == 13.0);
  assert (een[3] == 14.0);
  assert (een[4] == 15.0);
  assert (een[5] == 16.0);

  int en_nucleus [3] = { 0, 0, 0 };
  rc = trexio_read_jastrow_en_nucleus(file, en_nucleus);
  assert (rc == TREXIO_SUCCESS);
  assert (en_nucleus[0] == 0);
  assert (en_nucleus[1] == 1);
  assert (en_nucleus[2] == 2);

  int een_nucleus [6] = { 0, 0, 0, 0, 0, 0 };
  rc = trexio_read_jastrow_een_nucleus(file, een_nucleus);
  assert (rc == TREXIO_SUCCESS);
  assert (een_nucleus[0] == 0);
  assert (een_nucleus[1] == 0);
  assert (een_nucleus[2] == 1);
  assert (een_nucleus[3] == 1);
  assert (een_nucleus[4] == 2);
  assert (een_nucleus[5] == 2);

  double ee_scaling = 0.0;
  rc = trexio_read_jastrow_ee_scaling(file, &ee_scaling);
  assert (rc == TREXIO_SUCCESS);
  assert (ee_scaling == 1.0);

  double en_scaling[3] = { 0.5, 1.0, 0.5 };
  rc = trexio_read_jastrow_en_scaling(file, en_scaling);
  assert (rc == TREXIO_SUCCESS);
  assert (en_scaling[0] == 0.5);
  assert (en_scaling[1] == 1.0);
  assert (en_scaling[2] == 0.5);

  rc = trexio_close(file);
/*================= END OF TEST ==================*/

  return 0;
}


int main(){

/*============== Test launcher ================*/

  int rc;

  rc = system(RM_COMMAND);
  assert (rc == 0);

  test_write_jastrow (TREXIO_FILE, TEST_BACKEND);
  test_read_jastrow  (TREXIO_FILE, TEST_BACKEND);

  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}
