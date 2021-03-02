/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/



#ifndef _TREXIO_TEXT_H
#define _TREXIO_TEXT_H

#include "trexio.h"
#include "trexio_s.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

typedef struct nucleus_s {
  double*  coord;
  double*  charge;
  uint64_t  num;
} nucleus_t;

typedef struct electron_s {
  uint64_t  alpha_num;
  uint64_t  beta_num;
} electron_t;

typedef struct trexio_text_s {
  trexio_t     parent ;
  char*      nucleus_file_name;
  char*      electron_file_name;
} trexio_text_t;

trexio_exit_code trexio_text_init(trexio_t* file);

trexio_exit_code trexio_text_finalize(trexio_t* file);

trexio_exit_code trexio_text_read_nucleus_num(const trexio_t* file, uint64_t* num);
trexio_exit_code trexio_text_write_nucleus_num(const trexio_t* file, const uint64_t num);

trexio_exit_code trexio_text_read_nucleus_coord(const trexio_t* file, double* coord);
trexio_exit_code trexio_text_write_nucleus_coord(const trexio_t* file, const double* coord);

trexio_exit_code trexio_text_read_nucleus_charge(const trexio_t* file, double* coord);
trexio_exit_code trexio_text_write_nucleus_charge(const trexio_t* file, const double* coord);

#endif
