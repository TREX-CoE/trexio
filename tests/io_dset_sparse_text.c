#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "trexio.h"
#include <assert.h>

#define FILENAME "test_sparse.dir"


int main(){

  uint64_t offset_f = 0;

  // create the data to write
  uint64_t size = 100;
  int32_t* index;
  double* value;

  index = calloc(4L*size, sizeof(int32_t));
  value = calloc(size, sizeof(double));

  for(int i=0; i<size; i++){
    index[4*i]   = 4*i;
    index[4*i+1] = 4*i+1;
    index[4*i+2] = 4*i+2;
    index[4*i+3] = 4*i+3;
    value[i]     = 3.14 + (double) i;
  }

  int rc_open;
  trexio_t* trexio_file = trexio_open(FILENAME, 'w', TREXIO_TEXT, &rc_open);
  assert(rc_open == TREXIO_SUCCESS);
  assert(trexio_file != NULL);


  // check if the file exists
  int rc;
  rc = trexio_has_mo_2e_int_eri(trexio_file);
  assert(rc==TREXIO_SUCCESS || rc==TREXIO_HAS_NOT);

  if(rc==TREXIO_HAS_NOT){
    printf("FILE DID NOT EXIST AT THE START.\n");
  } else {
    printf("FILE EXIST AT THE START.\n");
  }

  // check that previous call to has_sparse did not create a file
  if (rc==TREXIO_HAS_NOT) {
    rc = trexio_has_mo_2e_int_eri(trexio_file);
    assert(rc==TREXIO_HAS_NOT);
  }

  // define chunks: here they contain 20 elements, i.e. 100/5
  int n_chunks = 5;
  uint64_t chunk_size = size/n_chunks;

  // write 5 chunks using write_sparse
  for(int i=0; i<n_chunks; ++i){
    rc = trexio_write_mo_2e_int_eri(trexio_file, offset_f, chunk_size, &index[4*offset_f], &value[offset_f]);
    assert(rc==TREXIO_SUCCESS);
    offset_f += chunk_size;
  }

  rc = trexio_close(trexio_file);
  assert(rc == TREXIO_SUCCESS);
  // TODO: SHOULD NOT TREXIO_CLOSE SET TO NULL THE TREXIO_T POINTER ???
  //assert(trexio_file == NULL);

  trexio_t* trexio_file_2 = trexio_open(FILENAME, 'r', TREXIO_TEXT, &rc_open);
  assert(rc_open == TREXIO_SUCCESS);
  assert(trexio_file_2 != NULL);

  // define arrays to read into
  int32_t* index_read;
  double* value_read;

  index_read = (int32_t*) calloc(4L*chunk_size,sizeof(int32_t));
  value_read = (double*) calloc(chunk_size,sizeof(double));

  // read 1 chunk of 20 elements using offset of 40( i.e. lines No. 40--59)
  uint64_t offset_f_read = 40L;
  int offset_data_read = 5;
  rc = trexio_read_mo_2e_int_eri(trexio_file_2, offset_f_read, 10L, &index_read[4*offset_data_read], &value_read[offset_data_read]);
  assert(rc==TREXIO_SUCCESS);
  assert(index_read[0]==0 && index_read[4*offset_data_read]==offset_f_read*4);

  // print the data being read
  for(int i=0; i<chunk_size; ++i){
    printf("%d %d %d %d %lf\n",
    index_read[4*i],
    index_read[4*i+1],
    index_read[4*i+2],
    index_read[4*i+3],
    value_read[i]
    );
  }

  // check that the file has been created
  rc = trexio_has_mo_2e_int_eri(trexio_file_2);
  assert(rc==TREXIO_SUCCESS);

  // close the TREXIO file
  rc = trexio_close(trexio_file_2);
  assert(rc == TREXIO_SUCCESS);

  // free the memory
  free(index);
  free(value);
  free(index_read);
  free(value_read);

}
