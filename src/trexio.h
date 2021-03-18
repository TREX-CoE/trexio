/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/

#ifndef _TREXIO_H
#define _TREXIO_H

#include <stdint.h>

typedef int32_t trexio_exit_code;

#define TREXIO_FAILURE       ( (trexio_exit_code) -1 )
#define TREXIO_SUCCESS       ( (trexio_exit_code)  0 )
#define TREXIO_INVALID_ARG_1 ( (trexio_exit_code)  1 )
#define TREXIO_INVALID_ARG_2 ( (trexio_exit_code)  2 )
#define TREXIO_INVALID_ARG_3 ( (trexio_exit_code)  3 )
#define TREXIO_INVALID_ARG_4 ( (trexio_exit_code)  4 )
#define TREXIO_INVALID_ARG_5 ( (trexio_exit_code)  5 )
#define TREXIO_END           ( (trexio_exit_code) 10 )
#define TREXIO_READONLY      ( (trexio_exit_code) 11 )
#define TREXIO_ERRNO         ( (trexio_exit_code) 12 )
#define TREXIO_INVALID_ID    ( (trexio_exit_code) 20 )
#define TREXIO_ALLOCATION_FAILED  (  (trexio_exit_code)  21  )
#define TREXIO_INVALID_NUM   ( (trexio_exit_code) 22 )

typedef int32_t back_end_t;

#define TREXIO_HDF5             ( (back_end_t) 0 )
#define TREXIO_TEXT             ( (back_end_t) 1 ) 
#define TREXIO_JSON             ( (back_end_t) 2 ) 
#define TREXIO_INVALID_BACK_END ( (back_end_t) 3 )

typedef struct trexio_s trexio_t;

trexio_t* trexio_open(const char* file_name, const char mode, const back_end_t back_end);

trexio_exit_code trexio_close(trexio_t* file);
trexio_exit_code trexio_read_nucleus_charge(trexio_t* file, double* nucleus_charge);
trexio_exit_code trexio_write_nucleus_charge(trexio_t* file, const double* nucleus_charge);
trexio_exit_code trexio_read_nucleus_coord(trexio_t* file, double* nucleus_coord);
trexio_exit_code trexio_write_nucleus_coord(trexio_t* file, const double* nucleus_coord);
trexio_exit_code trexio_read_ecp_lmax_plus_1(trexio_t* file, int64_t* ecp_lmax_plus_1);
trexio_exit_code trexio_write_ecp_lmax_plus_1(trexio_t* file, const int64_t* ecp_lmax_plus_1);
trexio_exit_code trexio_read_ecp_z_core(trexio_t* file, int64_t* ecp_z_core);
trexio_exit_code trexio_write_ecp_z_core(trexio_t* file, const int64_t* ecp_z_core);
trexio_exit_code trexio_read_ecp_local_n(trexio_t* file, int64_t* ecp_local_n);
trexio_exit_code trexio_write_ecp_local_n(trexio_t* file, const int64_t* ecp_local_n);
trexio_exit_code trexio_read_ecp_local_exponent(trexio_t* file, double* ecp_local_exponent);
trexio_exit_code trexio_write_ecp_local_exponent(trexio_t* file, const double* ecp_local_exponent);
trexio_exit_code trexio_read_ecp_local_coef(trexio_t* file, double* ecp_local_coef);
trexio_exit_code trexio_write_ecp_local_coef(trexio_t* file, const double* ecp_local_coef);
trexio_exit_code trexio_read_ecp_local_power(trexio_t* file, int64_t* ecp_local_power);
trexio_exit_code trexio_write_ecp_local_power(trexio_t* file, const int64_t* ecp_local_power);
trexio_exit_code trexio_read_ecp_non_local_n(trexio_t* file, int64_t* ecp_non_local_n);
trexio_exit_code trexio_write_ecp_non_local_n(trexio_t* file, const int64_t* ecp_non_local_n);
trexio_exit_code trexio_read_ecp_non_local_exponent(trexio_t* file, double* ecp_non_local_exponent);
trexio_exit_code trexio_write_ecp_non_local_exponent(trexio_t* file, const double* ecp_non_local_exponent);
trexio_exit_code trexio_read_ecp_non_local_coef(trexio_t* file, double* ecp_non_local_coef);
trexio_exit_code trexio_write_ecp_non_local_coef(trexio_t* file, const double* ecp_non_local_coef);
trexio_exit_code trexio_read_ecp_non_local_power(trexio_t* file, int64_t* ecp_non_local_power);
trexio_exit_code trexio_write_ecp_non_local_power(trexio_t* file, const int64_t* ecp_non_local_power);
trexio_exit_code trexio_read_nucleus_num(trexio_t* file, int64_t* num);
trexio_exit_code trexio_write_nucleus_num(trexio_t* file, const int64_t num);
trexio_exit_code trexio_read_ecp_local_num_n_max(trexio_t* file, int64_t* num);
trexio_exit_code trexio_write_ecp_local_num_n_max(trexio_t* file, const int64_t num);
trexio_exit_code trexio_read_ecp_non_local_num_n_max(trexio_t* file, int64_t* num);
trexio_exit_code trexio_write_ecp_non_local_num_n_max(trexio_t* file, const int64_t num);
#endif
