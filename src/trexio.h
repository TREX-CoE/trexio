/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/



#ifndef _TREXIO_H
#define _TREXIO_H

#include <stdint.h>

typedef int32_t trexio_exit_code;

#define TREXIO_SUCCESS ( (trexio_exit_code) 0 )
#define TREXIO_FAILURE ( (trexio_exit_code) 1 )

typedef uint32_t back_end_t;

#define TREXIO_HDF5             ( (back_end_t) 0 )
#define TREXIO_TEXT             ( (back_end_t) 1 ) 
#define TREXIO_JSON             ( (back_end_t) 2 ) 
#define TREXIO_INVALID_BACK_END ( (back_end_t) 3 )

typedef struct trexio_s trexio_t;

trexio_t* trexio_create(const char* file_name, back_end_t back_end);

trexio_exit_code trexio_close(trexio_t* file);

trexio_exit_code trexio_read_nucleus_num(trexio_t* file, uint64_t* num);
trexio_exit_code trexio_write_nucleus_num(trexio_t* file, uint64_t num);

trexio_exit_code trexio_read_nucleus_coord(trexio_t* file, double* coord);
trexio_exit_code trexio_write_nucleus_coord(trexio_t* file, double* coord);

trexio_exit_code trexio_read_nucleus_charge(trexio_t* file, double* charge);
trexio_exit_code trexio_write_nucleus_charge(trexio_t* file, double* charge);

#endif
