#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N_CHUNKS      4

static int test_write_dset_sparse (const char* file_name, const back_end_t backend, const int64_t offset, const int64_t mo_num) {

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
  uint64_t size = mo_num/2;

  index = calloc(4L*size, sizeof(int32_t));
  value = calloc(size, sizeof(double));

  for(int i=0; (uint64_t) i<size; i++){
    index[4*i]   = i;
    index[4*i+1] = i+1;
    index[4*i+2] = i+2;
    index[4*i+3] = i+3;
    value[i]     = 3.14 + (double) i;
  }

  // write mo_num which will be used to determine the optimal size of int indices
  if (trexio_has_mo_num(file) == TREXIO_HAS_NOT) {
    rc = trexio_write_mo_num_64(file, mo_num);
    assert(rc == TREXIO_SUCCESS);
  }

  // write dataset chunks of sparse data in the file (including FAKE statements)
  uint64_t chunk_size = (uint64_t) size/N_CHUNKS;
  chunk_size = chunk_size > 0 ? chunk_size : (uint64_t) size;
  uint64_t n_chunks = size/chunk_size;
  printf("chunk_size = %ld\n", (long) chunk_size);
  printf("n_chunks   = %ld\n", (long) n_chunks);

  uint64_t offset_f = 0UL + offset;
  uint64_t offset_d = 0UL;

  // write n_chunks times using write_sparse
  while(offset_d < size) {
    if (offset_d+chunk_size > size) chunk_size = size-offset_d;
  printf("chunk_size = %ld\n", (long) chunk_size);
    if (chunk_size == 0L) break;
    rc = trexio_write_mo_2e_int_eri(file, offset_f, chunk_size, &index[4*offset_d], &value[offset_d]);
    printf("%5d: %s\n", __LINE__, trexio_string_of_error(rc));
    assert(rc == TREXIO_SUCCESS);
    offset_d += chunk_size;
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

  // check that the group exists
  rc = trexio_has_mo_2e_int(file);
  assert(rc==TREXIO_SUCCESS);

  // check that the group does not exist
  rc = trexio_has_rdm(file);
  assert(rc==TREXIO_HAS_NOT);

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

static int test_read_dset_sparse (const char* file_name, const back_end_t backend, const int64_t offset) {

/* Try to read one chunk of dataset of sparse data in the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

/*================= START OF TEST ==================*/

  // open file
  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);
  assert (rc == TREXIO_SUCCESS);

  int32_t mo_num = 0;
  rc = trexio_read_mo_num(file, &mo_num);
  assert(rc == TREXIO_SUCCESS);
  printf("%5d: mo_num = %d\n", __LINE__, mo_num);
  const int64_t size = mo_num/2;

 // define arrays to read into
  int32_t* index_read;
  double* value_read;
  uint64_t size_r = mo_num;

  index_read = (int32_t*) calloc(4L*size_r,sizeof(int32_t));
  value_read = (double*) calloc(size_r,sizeof(double));

  // specify the read parameters, here:
  // 1 chunk of 10 elements using offset of 40 (i.e. lines No. 40--59) into elements of the array starting from 5
  int64_t chunk_read = size/3;
  chunk_read = chunk_read < 2 ? 2 : chunk_read;
  int64_t offset_file_read = 1;
  int64_t read_size_check;
  read_size_check = chunk_read;

  if (offset != 0L) offset_file_read += offset;

  // read one chunk using the aforementioned parameters
  rc = trexio_read_mo_2e_int_eri(file, offset_file_read, &chunk_read, &index_read[0], &value_read[0]);
  printf("%5d: %s\n", __LINE__, trexio_string_of_error(rc));
/*
  for (int i=0 ; i<chunk_read ; ++i) {
    printf("%d %d | %ld %ld %ld\n", i, index_read[i], (long) offset, (long) offset_file_read, (long) chunk_read);
  }
*/
  //assert(rc == TREXIO_SUCCESS);
  assert(chunk_read == read_size_check);
  assert(index_read[0] == offset_file_read-offset);


  // now attempt to read so that one encounters end of file during reading (i.e. offset_file_read + chunk_read > size_max)
  int64_t size_max;
  rc = trexio_read_mo_2e_int_eri_size(file, &size_max);
  assert(rc == TREXIO_SUCCESS);
  offset_file_read = size_max-chunk_read+1;
  int64_t eof_read_size_check = size_max - offset_file_read; // if offset_file_read=97 => only 3 integrals will be read out of total of 100


  // read one chunk that will reach EOF and return TREXIO_END code
  rc = trexio_read_mo_2e_int_eri(file, offset_file_read, &chunk_read, &index_read[0], &value_read[0]);
  printf("%5d: %s\n", __LINE__, trexio_string_of_error(rc));
  assert(rc == TREXIO_END);
  printf("%d %d  x\n", (int32_t) index_read[0], (int32_t) (4L*offset_file_read));
  printf("%ld  %ld\n", (long) chunk_read, (long) eof_read_size_check);
  assert(chunk_read == eof_read_size_check);
  printf("%d %d\n", index_read[0] , (int32_t) (offset_file_read - offset));
  assert(index_read[0] == (int32_t) offset_file_read - offset);

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
  printf("%5d: %ld %ld\n", __LINE__, (long) size_written, (long) size_check);
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

  int32_t mo_num[8] = {6,12,30,62,252,510,1020,9000};

  for (int i=0 ; i<8 ; ++i) {

    printf("%5d: mo_num = %d\n", __LINE__, mo_num[i]);
    const int64_t size = mo_num[i]/2;
    // check the first write attempt (SIZE elements written in N_CHUNKS chunks)
    test_write_dset_sparse    (TREXIO_FILE, TEST_BACKEND, 0, mo_num[i]);
    test_has_dset_sparse      (TREXIO_FILE, TEST_BACKEND);
    test_read_dset_sparse     (TREXIO_FILE, TEST_BACKEND, 0);
    test_read_dset_sparse_size(TREXIO_FILE, TEST_BACKEND, size);

    // check the second write attempt (SIZE elements written in N_CHUNKS chunks)
    test_write_dset_sparse    (TREXIO_FILE, TEST_BACKEND, size, mo_num[i]);
    test_read_dset_sparse     (TREXIO_FILE, TEST_BACKEND, size);
    test_read_dset_sparse_size(TREXIO_FILE, TEST_BACKEND, 2*size);

    rc = system(RM_COMMAND);
    assert (rc == 0);

  }

  return 0;
}
