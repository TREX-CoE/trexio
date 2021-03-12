/* [[file:trexio_text.org::*File prefixes][File prefixes:3]] */
/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/



#ifndef _TREXIO_TEXT_H
#define _TREXIO_TEXT_H

#include "trexio.h"
#include "trexio_private.h"
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
/* File prefixes:3 ends here */

/* Structs for blocks */

/* [[file:trexio_text.org::*Structs for blocks][Structs for blocks:1]] */
typedef struct nucleus_s {
  FILE*    file;
  double*  coord;
  double*  charge;
  uint64_t num;
  uint64_t dims_charge[16];
  uint64_t dims_coord[16];
  uint32_t rank_charge;
  uint32_t rank_coord;
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
/* Structs for blocks:1 ends here */

/* Structs for the text back end */
    

/* [[file:trexio_text.org::*Structs for the text back end][Structs for the text back end:1]] */
typedef struct trexio_text_s {
  trexio_t   parent ;
  int        lock_file;

  nucleus_t*  nucleus;
  electron_t* electron;
  rdm_t*      rdm;
} trexio_text_t;
/* Structs for the text back end:1 ends here */

/* Init/deinit functions */


/* [[file:trexio_text.org::*Init/deinit functions][Init/deinit functions:1]] */
trexio_exit_code trexio_text_init(trexio_t* file);
/* Init/deinit functions:1 ends here */

/* [[file:trexio_text.org::*Init/deinit functions][Init/deinit functions:3]] */
trexio_exit_code trexio_text_lock(trexio_t* file);
/* Init/deinit functions:3 ends here */

/* [[file:trexio_text.org::*Init/deinit functions][Init/deinit functions:5]] */
trexio_exit_code trexio_text_finalize(trexio_t* file);
/* Init/deinit functions:5 ends here */

/* [[file:trexio_text.org::*Init/deinit functions][Init/deinit functions:7]] */
trexio_exit_code trexio_text_unlock(trexio_t* file);
/* Init/deinit functions:7 ends here */

/* Read the struct */


/* [[file:trexio_text.org::*Read the struct][Read the struct:1]] */
nucleus_t* trexio_text_read_nucleus(trexio_text_t* file);
/* Read the struct:1 ends here */

/* Flush the struct */


/* [[file:trexio_text.org::*Flush the struct][Flush the struct:1]] */
trexio_exit_code trexio_text_flush_nucleus(const trexio_text_t* file);
/* Flush the struct:1 ends here */

/* Free memory */

/*      Memory is allocated when reading. The following function frees memory. */
    

/* [[file:trexio_text.org::*Free memory][Free memory:1]] */
trexio_exit_code trexio_text_free_nucleus(trexio_text_t* file);
/* Free memory:1 ends here */

/* Read/Write the num attribute */


/* [[file:trexio_text.org::*Read/Write the num attribute][Read/Write the num attribute:1]] */
trexio_exit_code trexio_text_read_nucleus_num(const trexio_t* file, uint64_t* num);
trexio_exit_code trexio_text_write_nucleus_num(const trexio_t* file, const uint64_t num);
/* Read/Write the num attribute:1 ends here */

/* Read/Write the coord attribute */

/*      The ~coord~ array is assumed allocated with the appropriate size. */
    

/* [[file:trexio_text.org::*Read/Write the coord attribute][Read/Write the coord attribute:1]] */
trexio_exit_code trexio_text_read_nucleus_coord(const trexio_t* file, double* coord, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_nucleus_coord(const trexio_t* file, const double* coord, const uint32_t rank, const uint64_t* dims);
/* Read/Write the coord attribute:1 ends here */

/* Read/Write the charge attribute */

/*      The ~charge~ array is assumed allocated with the appropriate size. */
    

/* [[file:trexio_text.org::*Read/Write the charge attribute][Read/Write the charge attribute:1]] */
trexio_exit_code trexio_text_read_nucleus_charge(const trexio_t* file, double* charge, const uint32_t rank, const uint64_t* dims);
trexio_exit_code trexio_text_write_nucleus_charge(const trexio_t* file, const double* charge, const uint32_t rank, const uint64_t* dims);
/* Read/Write the charge attribute:1 ends here */

/* Read the complete struct */


/* [[file:trexio_text.org::*Read the complete struct][Read the complete struct:1]] */
rdm_t* trexio_text_read_rdm(trexio_text_t* file);
/* Read the complete struct:1 ends here */

/* Flush the complete struct */


/* [[file:trexio_text.org::*Flush the complete struct][Flush the complete struct:1]] */
trexio_exit_code trexio_text_flush_rdm(const trexio_text_t* file);
/* Flush the complete struct:1 ends here */

/* Free memory */

/*      Memory is allocated when reading. The followig function frees memory. */
    

/* [[file:trexio_text.org::*Free memory][Free memory:1]] */
trexio_exit_code trexio_text_free_rdm(trexio_text_t* file);
/* Free memory:1 ends here */

/* Read/Write the one_e attribute */

/*      The ~one_e~ array is assumed allocated with the appropriate size. */
    

/* [[file:trexio_text.org::*Read/Write the one_e attribute][Read/Write the one_e attribute:1]] */
trexio_exit_code trexio_text_read_rdm_one_e(const trexio_t* file, double* one_e, const uint64_t dim_one_e);
trexio_exit_code trexio_text_write_rdm_one_e(const trexio_t* file, const double* one_e, const uint64_t dim_one_e);
/* Read/Write the one_e attribute:1 ends here */

/* Read/Write the two_e attribute */

/*      ~two_e~ is a sparse data structure, which can be too large to fit */
/*      in memory. So we provide functions to read and write it by */
/*      chunks. */
/*      In the text back end, the easiest way to do it is to create a */
/*      file for each sparse float structure. */
    

/* [[file:trexio_text.org::*Read/Write the two_e attribute][Read/Write the two_e attribute:1]] */
trexio_exit_code trexio_text_buffered_read_rdm_two_e(const trexio_t* file, const uint64_t offset, const uint64_t size, int64_t* index, double* value);
trexio_exit_code trexio_text_buffered_write_rdm_two_e(const trexio_t* file, const uint64_t offset, const uint64_t size, const int64_t* index, const double* value);
/* Read/Write the two_e attribute:1 ends here */

/* File suffixes                                                     :noxport: */


/* [[file:trexio_text.org::*File suffixes][File suffixes:1]] */
#endif
/* File suffixes:1 ends here */
