#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TEST_BACKEND  TREXIO_HDF5
#define TREXIO_FILE   "test_determinant.h5"
#define RM_COMMAND    "rm -f " TREXIO_FILE
#define SIZE          100
#define N_CHUNKS      5

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

  int mo_num = 150;

  det_list = (int64_t*) calloc(2*3*SIZE, sizeof(int64_t));

  for(int i=0; i<SIZE; i++){
    det_list[6*i]   = 6*i;
    det_list[6*i+1] = 6*i+1;
    det_list[6*i+2] = 6*i+2;
    det_list[6*i+3] = 6*i+3;
    det_list[6*i+4] = 6*i+4;
    det_list[6*i+5] = 6*i+5;
  }

  // write mo_num which will be used to determine the optimal size of int indices
  if (trexio_has_mo_num(file) == TREXIO_HAS_NOT) {
    rc = trexio_write_mo_num(file, mo_num);
    assert(rc == TREXIO_SUCCESS);
  }

  // write dataset chunks of sparse data in the file (including FAKE statements)
  uint64_t chunk_size = (uint64_t) SIZE/N_CHUNKS;
  uint64_t offset_f = 0UL;
  uint64_t offset_d = 0UL;
  if (offset != 0L) offset_f += offset;

  // write n_chunks times using write_sparse
  for(int i=0; i<N_CHUNKS; ++i){
    rc = trexio_write_determinant_list(file, offset_f, chunk_size, &det_list[6*offset_d]); 
    assert(rc == TREXIO_SUCCESS);
    offset_d += chunk_size;
    offset_f += chunk_size;
  }

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // free the allocated memeory
  free(det_list);

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

 // define arrays to read into
  int64_t* det_list_read;
  uint64_t size_r = 40L;

  det_list_read = (int64_t*) calloc(2*3*size_r,sizeof(int64_t));

  // specify the read parameters, here:
  // 1 chunk of 10 elements using offset of 40 (i.e. lines No. 40--59) into elements of the array starting from 5
  int64_t chunk_read = 10L;
  int64_t offset_file_read = 40L;
  int offset_data_read = 5;
  int64_t read_size_check;
  read_size_check = chunk_read;

  if (offset != 0L) offset_file_read += offset;

  // read one chunk using the aforementioned parameters
  rc = trexio_read_determinant_list(file, offset_file_read, &chunk_read, &det_list_read[6*offset_data_read]);
  assert(rc == TREXIO_SUCCESS);
  assert(chunk_read == read_size_check);
  assert(det_list_read[0] == 0);
  assert(det_list_read[6*offset_data_read] == 6 * (int64_t) (offset_file_read-offset));

  // now attempt to read so that one encounters end of file during reading (i.e. offset_file_read + chunk_read > size_max)
  offset_file_read = 97L;
  offset_data_read = 1;
  int64_t eof_read_size_check = SIZE - offset_file_read; // if offset_file_read=97 => only 3 integrals will be read out of total of 100

  if (offset != 0L) offset_file_read += offset;

  // read one chunk that will reach EOF and return TREXIO_END code
  rc = trexio_read_determinant_list(file, offset_file_read, &chunk_read, &det_list_read[6*offset_data_read]);
  /*
  printf("%s\n", trexio_string_of_error(rc));
  for (int i=0; i<size_r; i++) {
    printf("%lld %lld\n", det_list_read[6*i], det_list_read[6*i+5]); 
  }
  */
  assert(rc == TREXIO_END);
  assert(chunk_read == eof_read_size_check);
  assert(det_list_read[6*size_r-1] == 0);
  assert(det_list_read[6*offset_data_read] == 497); 

  // check the value of determinant_num
  int32_t det_num = 0;
  int32_t size_check = SIZE;
  if (offset != 0L) size_check += offset;

  rc = trexio_read_determinant_num(file, &det_num);
  assert(rc == TREXIO_SUCCESS);
  assert(det_num == size_check);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // free the memory
  free(det_list_read);

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

//  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}
