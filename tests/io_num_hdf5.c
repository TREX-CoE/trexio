#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int test_write_num (const char* file_name, const back_end_t backend) {

/* Try to write dimensioning attribute (num variable) into the HDF5 file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be written
  int num = 12;

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend);
  assert (file != NULL);


  // write numerical attribute in an empty file
  rc = trexio_write_nucleus_num(file,num);
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
  rc = system("rm -rf test_write_num.h5");
  assert (rc == 0);
  test_write_num("test_write_num.h5", TREXIO_HDF5);
  rc = system("rm -rf test_write_num.h5");
  assert (rc == 0);

  return 0;
}


