/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/



#ifndef _TREXIO_HDF5_H
#define _TREXIO_HDF5_H

#include "trexio.h"
#include "trexio_private.h"
#include "trexio_s.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

#include "hdf5.h"
#include "hdf5_hl.h" // needed for high-level APIs like H5LT, requires additional linking in Makefile

typedef struct slab_s {
  uint64_t a;
  uint64_t b;
  uint64_t c;
  uint64_t d;
} slab_t;

typedef struct dset_s {
  hid_t dset_id;
  hid_t dspace_id;
  hid_t dtype_id;
  uint64_t* dims;
  uint32_t rank;
  const char* dset_name;
} dset_t;

typedef struct h5nucleus_s {
  uint64_t   num;
  double    *coord;
  double    *charge;
  dset_t*    h5_coord;
  dset_t*    h5_charge;
} h5nucleus_t;

typedef struct h5electron_s {
  uint64_t  alpha_num;
  uint64_t  beta_num;
} h5electron_t;

typedef struct trexio_hdf5_s {
  trexio_t     parent ;
  hid_t      file_id;
  hid_t      nucleus_group;
  hid_t      electron_group;
  //... other groups' id
  const char* file_name;
} trexio_hdf5_t;

trexio_exit_code trexio_hdf5_init(trexio_t* file);

trexio_exit_code trexio_hdf5_finalize(trexio_t* file);

typedef struct one_index_s {
  double value;
  int64_t i;
} one_index_t;

typedef struct two_index_s {
  double value;
  int64_t i;
  int64_t j;
} two_index_t;

typedef struct three_index_s {
  double value;
  int64_t i;
  int64_t j;
  int64_t k;
} three_index_t;

typedef struct four_index_s {
  double value;
  int64_t i;
  int64_t j;
  int64_t k;
  int64_t l;
} four_index_t;

trexio_exit_code trexio_hdf5_read_nucleus_num(const trexio_t* file, uint64_t* num);
trexio_exit_code trexio_hdf5_write_nucleus_num(const trexio_t* file, const uint64_t num);

trexio_exit_code trexio_hdf5_read_nucleus_coord(const trexio_t* file, double* coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_hdf5_write_nucleus_coord(const trexio_t* file, const double* coord, const uint32_t rank, const uint64_t* dims);

#endif
