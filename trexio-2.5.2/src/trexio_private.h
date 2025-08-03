/* This file was generated from the templator_front.org org-mode file.
   To generate it, open templator_front.org in Emacs and execute
   M-x org-babel-tangle
*/

#ifndef _TREXIO_PRIVATE_H
#define _TREXIO_PRIVATE_H

#include "trexio.h"

#define MALLOC(T) (T*) malloc (sizeof(T))
#define CALLOC(N,T) (T*) calloc ( (N)+1 , sizeof(T) )

#define FREE(X) { free(X) ; (X)=NULL; }

#define TREXIO_MAX_FILENAME_LENGTH 4096

trexio_exit_code trexio_pre_close(trexio_t* file);

/* Popcount and trailz */
#if TREXIO_INT_SIZE == 64

  extern int __builtin_popcountll (unsigned long long x_0);
  #define popcnt(X) __builtin_popcountll((unsigned long long) X)

  extern int __builtin_ctzll (unsigned long long x_0);
  #define trailz(X) __builtin_ctzll((unsigned long long) X)

#elif TREXIO_INT_SIZE == 32

  extern int __builtin_popcountl (unsigned long x_0);
  #define popcnt(X) __builtin_popcountl((unsigned long) X)

  extern int __builtin_ctzl(unsigned long x_0);
  #define trailz(X) __builtin_ctzl((unsigned long) X)

#elif TREXIO_INT_SIZE == 16

  extern int __builtin_popcount (unsigned int x_0);
  #define popcnt(X) __builtin_popcount((unsigned int) X)

  extern int __builtin_ctz (unsigned int x_0);
  #define trailz(X) __builtin_ctz((unsigned int) X)

#else

 #error("Invalid TREXIO_INT_SIZE")

#endif
trexio_exit_code trexio_write_determinant_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_write_determinant_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_write_determinant_num_64(trexio_t* const file, const int64_t num);
#endif
