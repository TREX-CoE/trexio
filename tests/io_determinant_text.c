#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TEST_BACKEND  TREXIO_TEXT
#define TREXIO_FILE   "test_determinant.dir"
#define RM_COMMAND    "rm -rf " TREXIO_FILE
#define SIZE          100
#define N_CHUNKS      5
#define STATE_TEST    2
#define MO_NUM        150

static int test_write_determinant (const char* file_name, const back_end_t backend, const int64_t offset) {

/* Try to write an array of sparse data into the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  // parameters to be written
  int64_t* det_list;
  double*  det_coef;

  int mo_num = MO_NUM;

  // write mo_num which will be used to determine the optimal size of int indices
  if (trexio_has_mo_num(file) == TREXIO_HAS_NOT) {
    rc = trexio_write_mo_num(file, mo_num);
    assert(rc == TREXIO_SUCCESS);
  }

  // get the number of int64 bit fields per determinant
  int int_num;
  rc = trexio_get_int64_num(file, &int_num);
  assert(rc == TREXIO_SUCCESS);
  assert(int_num == (MO_NUM-1)/64 + 1);

  // allocate memory and fill with values to be written
  det_list = (int64_t*) calloc(2 * int_num * SIZE, sizeof(int64_t));
  det_coef = (double*) calloc(SIZE, sizeof(double));

  for(int i=0; i<SIZE; i++){
    det_list[6*i]   = 6*i;
    det_list[6*i+1] = 6*i+1;
    det_list[6*i+2] = 6*i+2;
    det_list[6*i+3] = 6*i+3;
    det_list[6*i+4] = 6*i+4;
    det_list[6*i+5] = 6*i+5;
    det_coef[i]     = 3.14 + (double) i;
  }

  // write dataset chunks of sparse data in the file (including FAKE statements)
  uint64_t chunk_size = (uint64_t) SIZE/N_CHUNKS;
  uint64_t offset_f = 0UL;
  uint64_t offset_d = 0UL;
  if (offset != 0L) offset_f += offset;

  // write n_chunks times using write_sparse
  for(int i=0; i<N_CHUNKS; ++i){

    rc = trexio_write_determinant_list(file, offset_f, chunk_size, &det_list[2*int_num*offset_d]);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_write_determinant_coefficient(file, offset_f, chunk_size, &det_coef[offset_d]);
    assert(rc == TREXIO_SUCCESS);

    // The block below will write the coefficients for STATE_TEST
    rc = trexio_set_state(file, STATE_TEST);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_write_determinant_coefficient(file, offset_f, chunk_size, &det_coef[offset_d]);
    assert(rc == TREXIO_SUCCESS);

    // set state back to the default 0 (ground state)
    rc = trexio_set_state(file, 0);
    assert(rc == TREXIO_SUCCESS);
    // =================================================

    offset_d += chunk_size;
    offset_f += chunk_size;
  }

  // manually check the consistency of the determinant_num and coefficient_size after writing
  int64_t coeff_size = 0L;
  int64_t determinant_num = 0L;

  rc = trexio_read_determinant_num_64(file, &determinant_num);
  assert(rc == TREXIO_SUCCESS);

  rc = trexio_read_determinant_coefficient_size(file, &coeff_size);
  assert(rc == TREXIO_SUCCESS);
  assert(determinant_num == coeff_size);

  rc = trexio_set_state(file, STATE_TEST);
  assert(rc == TREXIO_SUCCESS);

  rc = trexio_read_determinant_coefficient_size(file, &coeff_size);
  assert(rc == TREXIO_SUCCESS);
  assert(determinant_num == coeff_size);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // free the allocated memeory
  free(det_list);
  free(det_coef);

/*================= END OF TEST ==================*/

  return 0;
}

static int test_has_determinant(const char* file_name, const back_end_t backend) {

/* Try to check the existence of a dataset of sparse data in the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  // now check that previously written determinant_list exists
  rc = trexio_has_determinant_list(file);
  assert(rc==TREXIO_SUCCESS);

  // now check that previously written determinant_coefficient exists
  rc = trexio_has_determinant_coefficient(file);
  assert(rc==TREXIO_SUCCESS);

  // also check for STATE_TEST
  rc = trexio_set_state(file, STATE_TEST);
  assert(rc == TREXIO_SUCCESS);

  rc = trexio_has_determinant_coefficient(file);
  assert(rc==TREXIO_SUCCESS);

  rc = trexio_set_state(file, 0);
  assert(rc == TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}

static int test_read_determinant (const char* file_name, const back_end_t backend, const int64_t offset) {

/* Try to read one chunk of dataset of sparse data in the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  // compute how many integer bit fields is needed per determinant (for a given spin)
  int64_t mo_num;
  rc = trexio_read_mo_num_64(file, &mo_num);
  assert (rc == TREXIO_SUCCESS);
  assert (mo_num == MO_NUM);

  int int_num;
  rc = trexio_get_int64_num(file, &int_num);
  assert (rc == TREXIO_SUCCESS);
  assert (int_num == (MO_NUM - 1)/64 + 1);

  // define arrays to read into
  int64_t* det_list_read;
  double*  det_coef_read;
  double*  det_coef_s2_read;
  double check_diff;
  uint64_t size_r = 40L;

  det_list_read = (int64_t*) calloc(2*int_num*size_r,sizeof(int64_t));
  det_coef_read = (double*)  calloc(size_r,sizeof(double));
  det_coef_s2_read = (double*)  calloc(size_r,sizeof(double));

  // specify the read parameters, here:
  // 1 chunk of 10 elements using offset of 40 (i.e. lines No. 40--59) into elements of the array starting from 5
  int64_t chunk_read = 10L;
  int64_t offset_file_read = 40L;
  int offset_data_read = 5;
  int64_t read_size_check;
  read_size_check = chunk_read;

  if (offset != 0L) offset_file_read += offset;

  // read one chunk using the aforementioned parameters
  rc = trexio_read_determinant_list(file, offset_file_read, &chunk_read, &det_list_read[2*int_num*offset_data_read]);
  assert(rc == TREXIO_SUCCESS);
  assert(chunk_read == read_size_check);
  assert(det_list_read[0] == 0);
  assert(det_list_read[2*int_num*offset_data_read] == 2 * int_num * (int64_t) (offset_file_read-offset));

  rc = trexio_read_determinant_coefficient(file, offset_file_read, &chunk_read, &det_coef_read[offset_data_read]);
  assert(rc == TREXIO_SUCCESS);
  assert(chunk_read == read_size_check);

  check_diff = det_coef_read[0] - 0.;
  assert(check_diff*check_diff < 1e-14);

  check_diff = det_coef_read[offset_data_read] - (3.14 + (double) (offset_file_read-offset));
  //printf("%lf %lf\n", check_diff, det_coef_read[offset_data_read]);
  assert(check_diff*check_diff < 1e-14);

  // read one chuk of coefficients for a different state
  rc = trexio_set_state(file, STATE_TEST);
  assert(rc == TREXIO_SUCCESS);

  rc = trexio_read_determinant_coefficient(file, offset_file_read, &chunk_read, &det_coef_s2_read[offset_data_read]);
  assert(rc == TREXIO_SUCCESS);
  assert(chunk_read == read_size_check);

  check_diff = det_coef_s2_read[0] - 0.;
  assert(check_diff*check_diff < 1e-14);

  rc = trexio_set_state(file, 0);
  assert(rc == TREXIO_SUCCESS);

  // now attempt to read so that one encounters end of file during reading (i.e. offset_file_read + chunk_read > size_max)
  offset_file_read = 97L;
  offset_data_read = 1;
  int64_t eof_read_size_check = SIZE - offset_file_read; // if offset_file_read=97 => only 3 integrals will be read out of total of 100

  if (offset != 0L) offset_file_read += offset;

  chunk_read = read_size_check;
  // read one chunk that will reach EOF and return TREXIO_END code
  rc = trexio_read_determinant_list(file, offset_file_read, &chunk_read, &det_list_read[2*int_num*offset_data_read]);
  /*
  printf("%s\n", trexio_string_of_error(rc));
  for (int i=0; i<size_r; i++) {
    printf("%lld %lld\n", det_list_read[6*i], det_list_read[6*i+5]);
  }
  */
  assert(rc == TREXIO_END);
  assert(chunk_read == eof_read_size_check);
  assert(det_list_read[2*int_num*size_r-1] == 0);
  assert(det_list_read[2*int_num*offset_data_read] == 2 * int_num * (int64_t) (offset_file_read-offset));

  chunk_read = read_size_check;
  rc = trexio_read_determinant_coefficient(file, offset_file_read, &chunk_read, &det_coef_read[offset_data_read]);
  /*
  printf("%s\n", trexio_string_of_error(rc));
  for (int i=0; i<size_r; i++) {
    printf("%lf\n", det_coef_read[i]);
  }
  */
  assert(rc == TREXIO_END);
  assert(chunk_read == eof_read_size_check);

  check_diff= det_coef_read[size_r-1] - 0.;
  //printf("%lf %lf\n", check_diff, det_coef_read[size_r-1]);
  assert(check_diff*check_diff < 1e-14);

  // check the value of determinant_num
  int32_t det_num = 0;
  int32_t size_check = SIZE;
  if (offset != 0L) size_check += offset;

  rc = trexio_read_determinant_num(file, &det_num);
  assert(rc == TREXIO_SUCCESS);
  assert(det_num == size_check);


  // check conversion of determinants into orbital lists
  int64_t  size_list = TREXIO_NORB_PER_INT * int_num;
  int32_t* orb_list_up = (int32_t*) calloc(size_list, sizeof(int32_t));
  int32_t* orb_list_dn = (int32_t*) calloc(size_list, sizeof(int32_t));
  int32_t  occ_num_up, occ_num_dn;

  rc = trexio_to_orbital_list_up_dn (int_num, &det_list_read[2*int_num*5], orb_list_up, orb_list_dn, &occ_num_up, &occ_num_dn);
  assert (rc == TREXIO_SUCCESS);
  assert (occ_num_up == 14);
  assert (occ_num_dn == 17);
  /* // DEBUG printing
  printf("occ_num_up : %d ; occ_num_dn : %d \n", occ_num_up, occ_num_dn);
  for (int i=0; i<occ_num_up; i++) {
     printf("%d ", orb_list_up[i]);
  }
  printf("| ");
  for (int i=0; i<occ_num_dn; i++) {
     printf("%d ", orb_list_dn[i]);
  }
  printf("\n");
  */

  // check conversion of one orbital list into the bitfield determinant representation
  int64_t* det_list_check = (int64_t*) calloc(int_num, sizeof(int64_t));

  rc = trexio_to_bitfield_list (orb_list_up, occ_num_up, det_list_check, int_num);
  assert (rc == TREXIO_SUCCESS);
  for (int i=0; i<int_num; i++) {
    assert (det_list_check[i] == det_list_read[2*int_num*5+i]);
  }

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // free the memory
  free(det_list_read);
  free(det_coef_read);
  free(det_coef_s2_read);
  free(det_list_check);
  free(orb_list_up);
  free(orb_list_dn);

/*================= END OF TEST ==================*/

  return 0;
}


int main(){

/*============== Test launcher ================*/

  int rc;
  rc = system(RM_COMMAND);
  assert (rc == 0);

  // check the first write attempt (SIZE elements written in N_CHUNKS chunks)
  test_write_determinant (TREXIO_FILE, TEST_BACKEND, 0);
  test_has_determinant   (TREXIO_FILE, TEST_BACKEND);
  test_read_determinant  (TREXIO_FILE, TEST_BACKEND, 0);

  // check the second write attempt (SIZE elements written in N_CHUNKS chunks)
  test_write_determinant (TREXIO_FILE, TEST_BACKEND, SIZE);
  test_read_determinant  (TREXIO_FILE, TEST_BACKEND, SIZE);

  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}
