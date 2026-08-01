#define TEST_BACKEND  TREXIO_TEXT
#define TREXIO_FILE   "test_state_energy.dir"
#define RM_COMMAND_RESULT system("rm -rf -- " TREXIO_FILE);

#include "io_state_energy.c"
