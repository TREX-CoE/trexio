#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef TEST_BACKEND_HDF5
#define TEST_BACKEND  TREXIO_HDF5
#define TREXIO_FILE   TREXIO_FILE_PREFIX ".h5"
#define RM_COMMAND    "rm -f -- " TREXIO_FILE
#endif


#ifdef TEST_BACKEND_TEXT 
#define TEST_BACKEND  TREXIO_TEXT
#define TREXIO_FILE   TREXIO_FILE_PREFIX ".dir"
#define RM_COMMAND    "rm -f -- " TREXIO_FILE "/*.txt " TREXIO_FILE "/*.txt.size " TREXIO_FILE "/.lock && rm -fd -- " TREXIO_FILE
#endif


