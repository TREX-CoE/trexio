#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_delete_functions(const char* file_name, const back_end_t backend) {
    /* Test that all delete functions exist and can be called without crashing */

    trexio_t* file = NULL;
    trexio_exit_code rc;

    /*================= START OF TEST ==================*/

    // Create a file with some basic data
    file = trexio_open(file_name, 'w', backend, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Write some basic data to create groups to delete
    rc = trexio_write_nucleus_num(file, 2);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_nucleus(file);
    assert(rc == TREXIO_SAFE_MODE);

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    // Create a file with some basic data
    file = trexio_open(file_name, 'u', backend, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Write some basic data to create groups to delete
    rc = trexio_write_electron_num(file, 10);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_write_basis_shell_num(file, 4);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_write_mo_num(file, 8);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_flush(file);

    rc = trexio_delete_nucleus(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_electron(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_state(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_basis(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_ecp(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_grid(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_ao(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_ao_1e_int(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_ao_2e_int(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_mo(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_mo_1e_int(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_mo_2e_int(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_determinant(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_csf(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_amplitude(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_rdm(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_jastrow(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_qmc(file);
    assert(rc == TREXIO_SUCCESS);

    // Test deleting non-existent groups (should not crash)
    rc = trexio_delete_nucleus(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_delete_electron(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return 0;
}

int main(){

    /*================= Test launcher ================*/

    int rc;
    rc = system(RM_COMMAND);

    printf("# Testing delete functions...\n");

    // Test that delete functions exist and can be called
    printf("## Testing all delete functions exist and are callable\n");
    rc = test_delete_functions(TREXIO_FILE, TEST_BACKEND);
    assert (rc == 0);

    // Clean up
    rc = system(RM_COMMAND);

    printf("# All delete function tests passed!\n");
    return 0;

}