#define TEST_BACKEND  TREXIO_HDF5
#define TREXIO_FILE   "test_state_energy.h5"
#define RM_COMMAND_RESULT system("rm -f -- " TREXIO_FILE);

#include "io_state_energy.c"
