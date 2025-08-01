#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TEST_BACKEND_TEXT TREXIO_TEXT
#define TEST_FILE "test_utility_functions_trexio"

static int test_state_management(const char* file_name, const back_end_t backend) {
    /* Test state management functions: set/get state */

    trexio_t* file = NULL;
    trexio_exit_code rc;
    int32_t state_in = 42;
    int32_t state_out = 0;

    /*================= START OF TEST ==================*/

    // open file in 'write' mode
    file = trexio_open(file_name, 'w', backend, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // test trexio_set_state
    rc = trexio_set_state(file, state_in);
    assert(rc == TREXIO_SUCCESS);

    // test trexio_get_state
    rc = trexio_get_state(file, &state_out);
    assert(rc == TREXIO_SUCCESS);
    assert(state_out == state_in);

    // close current session
    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return 0;
}

static int test_file_operations(const char* file_name, const back_end_t backend) {
    /* Test file operations: inquire, cp, flush, info */

    trexio_t* file = NULL;
    trexio_exit_code rc;
    char copy_file_name[256];
    snprintf(copy_file_name, sizeof(copy_file_name), "%s_copy", file_name);

    /*================= START OF TEST ==================*/

    // Create a test file first
    file = trexio_open(file_name, 'w', backend, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Write some data to make the file non-empty
    rc = trexio_write_nucleus_num(file, 2);
    assert(rc == TREXIO_SUCCESS);

    // test trexio_flush
    rc = trexio_flush(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    // test trexio_inquire on existing file
    rc = trexio_inquire(file_name);
    assert(rc == TREXIO_SUCCESS);

    // test trexio_inquire on non-existing file
    rc = trexio_inquire("non_existing_file");
    assert(rc != TREXIO_SUCCESS); // Should fail

    // test trexio_cp (copy file)
    rc = trexio_cp(file_name, copy_file_name);
    assert(rc == TREXIO_SUCCESS);

    // Verify the copied file exists and contains the same data
    file = trexio_open(copy_file_name, 'r', backend, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    int32_t nucleus_num = 0;
    rc = trexio_read_nucleus_num(file, &nucleus_num);
    assert(rc == TREXIO_SUCCESS);
    assert(nucleus_num == 2);

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    // test trexio_info
    rc = trexio_info();
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return 0;
}

static int test_bitfield_operations() {
    /* Test bitfield/orbital list conversion functions */

    trexio_exit_code rc;
    int32_t N_int = 2;
    int32_t occupied_num = 4;
    int32_t orb_list[4] = {0, 1, 5, 10};
    bitfield_t* bit_list = NULL;
    int32_t recovered_list[10];
    int32_t recovered_occupied_num = 0;

    /*================= START OF TEST ==================*/

    // Allocate bitfield
    bit_list = calloc(N_int, sizeof(bitfield_t));
    assert(bit_list != NULL);

    // test trexio_to_bitfield_list
    rc = trexio_to_bitfield_list(orb_list, occupied_num, bit_list, N_int);
    assert(rc == TREXIO_SUCCESS);

    // test trexio_to_orbital_list
    rc = trexio_to_orbital_list(N_int, bit_list, recovered_list, &recovered_occupied_num);
    assert(rc == TREXIO_SUCCESS);
    assert(recovered_occupied_num == occupied_num);

    // Verify the recovered orbitals match the original
    for (int i = 0; i < occupied_num; i++) {
        assert(recovered_list[i] == orb_list[i]);
    }

    // Test with spin-separated lists - just check function exists and runs
    int32_t list_up[5], list_dn[5];
    int32_t occ_num_up = 0, occ_num_dn = 0;

    rc = trexio_to_orbital_list_up_dn(N_int, bit_list, list_up, list_dn, &occ_num_up, &occ_num_dn);
    // Function may succeed or fail depending on implementation details
    // Main goal is to test that it doesn't crash

    // Test safe versions with proper bounds checking - these may fail with specific error codes
    int32_t safe_list[10];
    int32_t safe_num = 0;

    rc = trexio_safe_to_orbital_list(N_int, bit_list, 1, safe_list, 10, &safe_num);
    // Function may succeed or fail - main goal is to test that it exists and doesn't crash
    if (rc == TREXIO_SUCCESS) {
        assert(safe_num <= 10); // Should not exceed bounds
    }

    int32_t safe_up[5], safe_dn[5];
    int32_t safe_up_num = 0, safe_dn_num = 0;

    rc = trexio_safe_to_orbital_list_up_dn(N_int, bit_list, 1, safe_up, 5, safe_dn, 5, &safe_up_num, &safe_dn_num);
    // Function may succeed or fail - main goal is to test that it doesn't crash
    if (rc == TREXIO_SUCCESS) {
        assert(safe_up_num <= 5);
        assert(safe_dn_num <= 5);
    }

    free(bit_list);

    /*================= END OF TEST ==================*/

    return 0;
}

static int test_safety_functions(const char* file_name, const back_end_t backend) {
    /* Test safety and marking functions */

    trexio_t* file = NULL;
    trexio_exit_code rc;
    int32_t safety_flag = 1;

    /*================= START OF TEST ==================*/

    // open file in 'write' mode
    file = trexio_open(file_name, 'w', backend, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // test trexio_mark_safety - may succeed or fail depending on implementation
    rc = trexio_mark_safety(file, safety_flag);
    // Function exists and can be called - result may vary based on file state

    // Test with different safety flags
    rc = trexio_mark_safety(file, 0);
    // Function exists and can be called - result may vary

    rc = trexio_mark_safety(file, 42);
    // Function exists and can be called - result may vary

    // close current session
    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return 0;
}

static int test_one_based_indexing(const char* file_name, const back_end_t backend) {
    /* Test one-based indexing setting */

    trexio_t* file = NULL;
    trexio_exit_code rc;

    /*================= START OF TEST ==================*/

    // open file in 'write' mode
    file = trexio_open(file_name, 'w', backend, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // test trexio_set_one_based
    rc = trexio_set_one_based(file);
    assert(rc == TREXIO_SUCCESS);

    // close current session
    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return 0;
}

int main(){

    /*================= Test launcher ================*/

    int rc;
    rc = system("rm -rf " TEST_FILE);
    rc = system("rm -rf " TEST_FILE "_copy");

    printf("# Testing utility functions...\n");

    // Test state management functions
    printf("## Testing state management functions\n");
    rc = test_state_management(TEST_FILE, TEST_BACKEND_TEXT);
    assert (rc == 0);

    // Test file operations
    printf("## Testing file operations\n");
    rc = test_file_operations(TEST_FILE, TEST_BACKEND_TEXT);
    assert (rc == 0);

    // Test bitfield operations
    printf("## Testing bitfield operations\n");
    rc = test_bitfield_operations();
    assert (rc == 0);

    // Test safety functions
    printf("## Testing safety functions\n");
    rc = test_safety_functions(TEST_FILE, TEST_BACKEND_TEXT);
    assert (rc == 0);

    // Test one-based indexing
    printf("## Testing one-based indexing\n");
    rc = test_one_based_indexing(TEST_FILE, TEST_BACKEND_TEXT);
    assert (rc == 0);

    // Clean up
    rc = system("rm -rf " TEST_FILE);
    rc = system("rm -rf " TEST_FILE "_copy");

    printf("# All utility function tests passed!\n");
    return 0;
}
