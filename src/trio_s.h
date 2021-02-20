/* This file was generated from the trio.org org-mode file.
   To generate it, open trio.org in Emacs and execute
   M-x org-babel-tangle
*/



#ifndef _TRIO_S_H
#define _TRIO_S_H

#include "trio.h"
#include <pthread.h>
#include <assert.h>

struct trio_s {
  char*             file_name;
  pthread_mutex_t   thread_lock;
  back_end_t        back_end;
  char              mode;
  char              padding[7];   /* Ensures the proper alignment of back-ends */
};

#endif
