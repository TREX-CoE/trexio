#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Portable cleanup function to replace system() calls */
static inline int trexio_cleanup_test_file(const char* file_path) {
    trexio_exit_code rc;
    
    /* First check if the file/directory exists */
    if (trexio_inquire(file_path) != TREXIO_SUCCESS) {
        return 0; /* File doesn't exist, cleanup successful */
    }
    
    /* Determine if it's a directory or file based on TEXT/HDF5 backend */
#ifdef TEST_BACKEND_TEXT
    rc = trexio_remove_directory_recursive(file_path);
#else
    rc = trexio_remove_file(file_path);
#endif
    
    return (rc == TREXIO_SUCCESS) ? 0 : 1;
}

#ifdef TEST_BACKEND_HDF5
#define TEST_BACKEND  TREXIO_HDF5
#define TREXIO_FILE   TREXIO_FILE_PREFIX ".h5"
#define RM_COMMAND_RESULT  trexio_cleanup_test_file(TREXIO_FILE)
#endif


#ifdef TEST_BACKEND_TEXT 
#define TEST_BACKEND  TREXIO_TEXT
#define TREXIO_FILE   TREXIO_FILE_PREFIX ".dir"
#define RM_COMMAND_RESULT  trexio_cleanup_test_file(TREXIO_FILE)
#endif


