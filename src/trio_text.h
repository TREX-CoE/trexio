/* This file was generated from the trio.org org-mode file.
   To generate it, open trio.org in Emacs and execute
   M-x org-babel-tangle
*/



#ifndef _TRIO_TEXT_H
#define _TRIO_TEXT_H

#include "trio.h"
#include "trio_s.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

typedef struct nucleus_s {
  double*  coord;
  double*  charge;
  int64_t  num;
} nucleus_t;

typedef struct electron_s {
  int64_t  alpha_num;
  int64_t  beta_num;
} electron_t;

typedef struct trio_text_s {
  trio_t     parent ;
  char*      nucleus_file_name;
  char*      electron_file_name;
} trio_text_t;

trio_exit_code trio_text_init(trio_t* file);

trio_exit_code trio_text_finalize(trio_t* file);

trio_exit_code trio_text_read_nucleus_num(const trio_t* file, int64_t* num);
trio_exit_code trio_text_write_nucleus_num(const trio_t* file, const int64_t num);

trio_exit_code trio_text_read_nucleus_coord(const trio_t* file, double* coord);
trio_exit_code trio_text_write_nucleus_coord(const trio_t* file, const double* coord);

trio_exit_code trio_text_read_nucleus_charge(const trio_t* file, double* coord);
trio_exit_code trio_text_write_nucleus_charge(const trio_t* file, const double* coord);

#endif
