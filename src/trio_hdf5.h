/* This file was generated from the trio.org org-mode file.
   To generate it, open trio.org in Emacs and execute
   M-x org-babel-tangle
*/



#ifndef _TRIO_HDF5_H
#define _TRIO_HDF5_H

#include "trio.h"
#include "trio_s.h"
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

typedef struct trio_hdf5_s {
  trio_t     parent ;
  hid_t      file_id;
  hid_t      nucleus_group;
  hid_t      electron_group;
  //... other groups' id
  const char* file_name;
} trio_hdf5_t;

trio_exit_code trio_hdf5_init(trio_t* file);

trio_exit_code trio_hdf5_finalize(trio_t* file);

trio_exit_code trio_hdf5_read_nucleus_num(const trio_t* file, uint64_t* num);
trio_exit_code trio_hdf5_write_nucleus_num(const trio_t* file, const uint64_t num);

trio_exit_code trio_hdf5_read_nucleus_coord(const trio_t* file, double* coord);
trio_exit_code trio_hdf5_write_nucleus_coord(const trio_t* file, const double* coord);

#endif
