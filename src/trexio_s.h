/* This file was generated from the trexio.org org-mode file.
   To generate it, open trexio.org in Emacs and execute
   M-x org-babel-tangle
*/



#ifndef _TREXIO_S_H
#define _TREXIO_S_H

#include "trexio.h"
#include <pthread.h>
#include <assert.h>

struct trexio_s {
  char*             file_name;
  pthread_mutex_t   thread_lock;
  back_end_t        back_end;
  char              mode;
  char              padding[7];   /* Ensures the proper alignment of back-ends */
};

#endif
