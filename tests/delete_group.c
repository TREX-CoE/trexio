#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int test_write_delete_group (const char* file_name, const back_end_t backend) {

/* Try to write a dimensioning attribute (num variable) into the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be written
  int num = 12;
  double coord[36] = {
  0.00000000 ,  1.39250319 ,  0.00000000 ,
 -1.20594314 ,  0.69625160 ,  0.00000000 ,
 -1.20594314 , -0.69625160 ,  0.00000000 ,
  0.00000000 , -1.39250319 ,  0.00000000 ,
  1.20594314 , -0.69625160 ,  0.00000000 ,
  1.20594314 ,  0.69625160 ,  0.00000000 ,
 -2.14171677 ,  1.23652075 ,  0.00000000 ,
 -2.14171677 , -1.23652075 ,  0.00000000 ,
  0.00000000 , -2.47304151 ,  0.00000000 ,
  2.14171677 , -1.23652075 ,  0.00000000 ,
  2.14171677 ,  1.23652075 ,  0.00000000 ,
  0.00000000 ,  2.47304151 ,  0.00000000 ,
  };

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);

  // write numerical attribute in an empty file
  rc = trexio_write_nucleus_num(file, num);
  assert (rc == TREXIO_SUCCESS);

  // write numerical dataset in a file
  rc = trexio_write_nucleus_coord(file, coord);
  assert (rc == TREXIO_SUCCESS);

  // write numerical attribute ao_cartesian as 0
  rc = trexio_write_ao_cartesian(file, 0);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // open file in 'unsafe' mode
  file = trexio_open(file_name, 'u', backend, &rc);
  assert (file != NULL);

  // delete a previously written group
  rc = trexio_delete_nucleus(file);
  assert (rc == TREXIO_SUCCESS);

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

  test_write_delete_group (TREXIO_FILE, TEST_BACKEND);

  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}
