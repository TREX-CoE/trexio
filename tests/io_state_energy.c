#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int test_write_state_energy (const char* file_name, const back_end_t backend) {

/* Try to write state energy (float attribute) including negative values */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be written
  int state_num = 1;  // Need to set the dimensioning variable first
  double positive_energy = 100.5;
  double negative_energy = -123.456789;
  double zero_energy = 0.0;
  double very_negative_energy = -987.654321;

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);

  // write state_num first to create the state group
  rc = trexio_write_state_num(file, state_num);
  assert (rc == TREXIO_SUCCESS);

  // write positive state energy
  rc = trexio_write_state_energy(file, positive_energy);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // reopen file in 'update' mode to test overwriting with negative value
  file = trexio_open(file_name, 'u', backend, &rc);
  assert (file != NULL);

  // write negative state energy (this is the main test - negative energies should be valid)
  rc = trexio_write_state_energy(file, negative_energy);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // reopen file in 'update' mode to test overwriting with zero value
  file = trexio_open(file_name, 'u', backend, &rc);
  assert (file != NULL);

  // write zero state energy (zero should also be valid for energy)
  rc = trexio_write_state_energy(file, zero_energy);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // reopen file in 'update' mode to test with a very negative value
  file = trexio_open(file_name, 'u', backend, &rc);
  assert (file != NULL);

  // write very negative state energy - this should also succeed
  rc = trexio_write_state_energy(file, very_negative_energy);
  assert (rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_read_state_energy (const char* file_name, const back_end_t backend) {

/* Try to read state energy from the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  // parameters to be read
  double energy_read;
  double expected_energy = -987.654321;  // Last value written in test_write_state_energy
  double tolerance = 1.e-14;

/*================= START OF TEST ==================*/

  // open file in 'read' mode
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);

  // check that state_energy exists
  rc = trexio_has_state_energy(file);
  assert (rc == TREXIO_SUCCESS);

  // read state energy from the file
  rc = trexio_read_state_energy(file, &energy_read);
  assert (rc == TREXIO_SUCCESS);
  
  // verify the value is correct (should be the very negative value from last write)
  assert (fabs(energy_read - expected_energy) < tolerance);

  // close current session
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

  test_write_state_energy (TREXIO_FILE, TEST_BACKEND);
  test_read_state_energy   (TREXIO_FILE, TEST_BACKEND);
  
  rc = RM_COMMAND_RESULT;
  assert (rc == 0);

  return 0;
}
