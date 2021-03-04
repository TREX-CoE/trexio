/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/



#ifndef _TREXIO_TEXT_H
#define _TREXIO_TEXT_H

#include "trexio.h"
#include "trexio_s.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

typedef struct nucleus_s {
  FILE*    file;
  uint64_t dim_coord;
  uint64_t dim_charge;
  double*  coord;
  double*  charge;
  uint64_t num;
  int      to_flush;
} nucleus_t;

typedef struct electron_s {
  FILE*    file;
  uint64_t  alpha_num;
  uint64_t  beta_num;
  int       to_flush;
} electron_t;

typedef struct rdm_s {
  FILE*    file;
  uint64_t dim_one_e;
  double*  one_e;
  char*    two_e_file_name;
  int      to_flush;
} rdm_t;

typedef struct trexio_text_s {
  trexio_t   parent ;
  int        lock_file;

  nucleus_t*  nucleus;
  electron_t* electron;
  rdm_t*      rdm;
} trexio_text_t;

trexio_exit_code trexio_text_init(trexio_t* file);

trexio_exit_code trexio_text_lock(trexio_t* file);

trexio_exit_code trexio_text_finalize(trexio_t* file);

trexio_exit_code trexio_text_unlock(trexio_t* file);

nucleus_t* trexio_text_read_nucleus(trexio_text_t* file);

trexio_exit_code trexio_text_flush_nucleus(const trexio_text_t* file);

trexio_exit_code trexio_text_free_nucleus(trexio_text_t* file);

trexio_exit_code trexio_text_read_nucleus_num(const trexio_t* file, uint64_t* num);
trexio_exit_code trexio_text_write_nucleus_num(const trexio_t* file, const uint64_t num);

trexio_exit_code trexio_text_read_nucleus_coord(const trexio_t* file, double* coord, const uint64_t dim_coord);
trexio_exit_code trexio_text_write_nucleus_coord(const trexio_t* file, const double* coord, const uint64_t dim_coord);

trexio_exit_code trexio_text_read_nucleus_charge(const trexio_t* file, double* charge, const uint64_t dim_charge);
trexio_exit_code trexio_text_write_nucleus_charge(const trexio_t* file, const double* charge, const uint64_t dim_charge);

rdm_t* trexio_text_read_rdm(trexio_text_t* file);

trexio_exit_code trexio_text_flush_rdm(const trexio_text_t* file);

trexio_exit_code trexio_text_free_rdm(trexio_text_t* file);

trexio_exit_code trexio_text_read_rdm_one_e(const trexio_t* file, double* one_e, const uint64_t dim_one_e);
trexio_exit_code trexio_text_write_rdm_one_e(const trexio_t* file, const double* one_e, const uint64_t dim_one_e);

trexio_exit_code trexio_text_buffered_read_rdm_two_e(const trexio_t* file, const uint64_t offset, const uint64_t size, int64_t* index, double* value);
trexio_exit_code trexio_text_buffered_write_rdm_two_e(const trexio_t* file, const uint64_t offset, const uint64_t size, const int64_t* index, const double* value);

#endif
