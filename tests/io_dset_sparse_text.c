#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TEST_BACKEND 	TREXIO_TEXT
#define TREXIO_FILE 	"test_dset_sparse.dir"
#define RM_COMMAND 	  "rm -rf " TREXIO_FILE
#define SIZE          100
#define N_CHUNKS      5

static int test_write_dset_sparse (const char* file_name, const back_end_t backend) {

/* Try to write an array of sparse data into the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file in 'write' mode
  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  // parameters to be written
  int32_t* index;
  double* value;

  index = calloc(4L*SIZE, sizeof(int32_t));
  value = calloc(SIZE, sizeof(double));

  for(int i=0; i<SIZE; i++){
    index[4*i]   = 4*i;
    index[4*i+1] = 4*i+1;
    index[4*i+2] = 4*i+2;
    index[4*i+3] = 4*i+3;
    value[i]     = 3.14 + (double) i;
  }

  // write dataset chunks of sparse data in the file (including FAKE statements)
  uint64_t chunk_size = (uint64_t) SIZE/N_CHUNKS;
  uint64_t offset_f = 0;

  // write n_chunks times using write_sparse
  for(int i=0; i<N_CHUNKS; ++i){
    rc = trexio_write_mo_2e_int_eri(file, offset_f, chunk_size, &index[4*offset_f], &value[offset_f]);
    assert(rc == TREXIO_SUCCESS);
    offset_f += chunk_size;
  }

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // free the allocated memeory
  free(index);
  free(value);

/*================= END OF TEST ==================*/

  return 0;
}

static int test_has_dset_sparse (const char* file_name, const back_end_t backend) {

/* Try to check the existence of a dataset of sparse data in the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  // first check that mo_2e_int_eri_lr (we only write non-lr component in this unit test)
  rc = trexio_has_mo_2e_int_eri_lr(file);
  assert(rc==TREXIO_HAS_NOT);

  // check that previous call to has_sparse did not create a file/dset
  rc = trexio_has_mo_2e_int_eri_lr(file);
  assert(rc==TREXIO_HAS_NOT);

  // now check that previously written mo_2e_int_eri exists
  rc = trexio_has_mo_2e_int_eri(file);
  assert(rc==TREXIO_SUCCESS);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}

static int test_read_dset_sparse (const char* file_name, const back_end_t backend) {

/* Try to read one chunk of dataset of sparse data in the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

 // define arrays to read into
  int32_t* index_read;
  double* value_read;
  uint64_t size = 20L;

  index_read = (int32_t*) calloc(4L*size,sizeof(int32_t));
  value_read = (double*) calloc(size,sizeof(double));

  // specify the read parameters, here:
  // 1 chunk of 10 elements using offset of 40 (i.e. lines No. 40--59) into elements of the array starting from 5
  uint64_t chunk_read = 10L;
  uint64_t offset_file_read = 40L;
  int offset_data_read = 5;

  // read one chunk using the aforementioned parameters
  rc = trexio_read_mo_2e_int_eri(file, offset_file_read, chunk_read, &index_read[4*offset_data_read], &value_read[offset_data_read]);
  assert(rc == TREXIO_SUCCESS);
  assert(index_read[0] == 0);
  assert(index_read[4*offset_data_read] == offset_file_read*4);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

  // free the memory
  free(index_read);
  free(value_read);

/*================= END OF TEST ==================*/

  return 0;
}

static int test_read_dset_sparse_size (const char* file_name, const back_end_t backend, const int64_t size_check) {

/* Try to read a size of the dataset of sparse data in the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  // define the variable to read into
  int64_t size_written;

  // read one chunk using the aforementioned parameters
  rc = trexio_read_mo_2e_int_eri_size(file, &size_written);
  assert(rc == TREXIO_SUCCESS);
  assert(size_written == size_check);

  // close current session
  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}

int main(){

/*============== Test launcher ================*/

  int rc;
  rc = system(RM_COMMAND);
  assert (rc == 0);

  // check the first write attempt (SIZE elements written in N_CHUNKS chunks)
  test_write_dset_sparse    (TREXIO_FILE, TEST_BACKEND);
  test_has_dset_sparse      (TREXIO_FILE, TEST_BACKEND);
  test_read_dset_sparse     (TREXIO_FILE, TEST_BACKEND);
  test_read_dset_sparse_size(TREXIO_FILE, TEST_BACKEND, (int64_t) SIZE);

  // check the second write attempt (SIZE elements written in N_CHUNKS chunks)
  test_write_dset_sparse    (TREXIO_FILE, TEST_BACKEND);
  test_read_dset_sparse_size(TREXIO_FILE, TEST_BACKEND, (int64_t) SIZE*2);

  rc = system(RM_COMMAND);
  assert (rc == 0);

  return 0;
}
