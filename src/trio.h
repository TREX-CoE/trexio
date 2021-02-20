/* This file was generated from the trio.org org-mode file.
   To generate it, open trio.org in Emacs and execute
   M-x org-babel-tangle
*/



#ifndef _TRIO_H
#define _TRIO_H

#include <stdint.h>

typedef int32_t trio_exit_code;

#define TRIO_SUCCESS ( (trio_exit_code) 0 )
#define TRIO_FAILURE ( (trio_exit_code) 1 )

typedef uint32_t back_end_t;

#define TRIO_HDF5             ( (back_end_t) 0 )
#define TRIO_TEXT             ( (back_end_t) 1 ) 
#define TRIO_JSON             ( (back_end_t) 2 ) 
#define TRIO_INVALID_BACK_END ( (back_end_t) 3 )

typedef struct trio_s trio_t;

trio_t* trio_create(const char* file_name, back_end_t back_end);

trio_exit_code trio_close(trio_t* file);

trio_exit_code trio_read_nucleus_num(trio_t* file, int64_t* num);
trio_exit_code trio_write_nucleus_num(trio_t* file, int64_t num);

trio_exit_code trio_read_nucleus_coord(trio_t* file, double* coord);
trio_exit_code trio_write_nucleus_coord(trio_t* file, double* coord);

trio_exit_code trio_read_nucleus_charge(trio_t* file, double* charge);
trio_exit_code trio_write_nucleus_charge(trio_t* file, double* charge);

#endif
