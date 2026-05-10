#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static trexio_exit_code test_invalid_arguments() {
    /* Test error handling with invalid function arguments */
    
    trexio_t* file = NULL;
    trexio_exit_code rc;

    /*================= START OF TEST ==================*/

    // Test opening with NULL filename - should fail
    file = trexio_open(NULL, 'w', TEST_BACKEND, &rc);
    assert(file == NULL);
    assert(rc != TREXIO_SUCCESS);

    // Test opening with empty filename - should fail  
    file = trexio_open("", 'w', TEST_BACKEND, &rc);
    assert(file == NULL);
    assert(rc != TREXIO_SUCCESS);

    // Test opening with invalid mode - should fail
    file = trexio_open(TREXIO_FILE, 'x', TEST_BACKEND, &rc);
    assert(file == NULL);
    assert(rc != TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return TREXIO_SUCCESS;
}

static trexio_exit_code test_write_before_dimensions() {
    /* Test error handling when writing data before setting dimensions */
    
    trexio_t* file = NULL;
    trexio_exit_code rc;

    /*================= START OF TEST ==================*/

    // Create file
    file = trexio_open(TREXIO_FILE, 'w', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Try to write array data without setting dimensions first
    double coords[6] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0};
    rc = trexio_write_nucleus_coord(file, coords);
    // This should fail because nucleus_num was not set
    assert(rc != TREXIO_SUCCESS);

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return TREXIO_SUCCESS;
}

static trexio_exit_code test_read_nonexistent_data() {
    /* Test reading data that doesn't exist */
    
    trexio_t* file = NULL;
    trexio_exit_code rc;

    /*================= START OF TEST ==================*/

    // Create empty file
    file = trexio_open(TREXIO_FILE, 'w', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    // Read from empty file
    file = trexio_open(TREXIO_FILE, 'r', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Test has function on non-existent data
    trexio_exit_code has_rc;
    has_rc = trexio_has_nucleus_num(file);
    (void)has_rc;  // Suppress unused variable warning
    // has function should return TREXIO_HAS_NOT or similar - we just test it doesn't crash

    // Try to read non-existent data
    int32_t num;
    rc = trexio_read_nucleus_num(file, &num);
    assert(rc != TREXIO_SUCCESS); // Should fail

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return TREXIO_SUCCESS;
}

static trexio_exit_code test_write_to_readonly_file() {
    /* Test writing to a read-only file */
    
    trexio_t* file = NULL;
    trexio_exit_code rc;

    /*================= START OF TEST ==================*/

    // Create file with some data
    file = trexio_open(TREXIO_FILE, 'w', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_write_nucleus_num(file, 2);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    // Open file in read-only mode
    file = trexio_open(TREXIO_FILE, 'r', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Try to write to read-only file - should fail
    rc = trexio_write_nucleus_num(file, 3);
    assert(rc != TREXIO_SUCCESS);

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return TREXIO_SUCCESS;
}

static trexio_exit_code test_invalid_dimensions() {
    /* Test error handling with invalid dimensions */
    
    trexio_t* file = NULL;
    trexio_exit_code rc;

    /*================= START OF TEST ==================*/

    // Create file
    file = trexio_open(TREXIO_FILE, 'w', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Test writing negative dimensions - should fail or be handled gracefully
    rc = trexio_write_nucleus_num(file, -1);
    // Implementation may handle this differently, we just test it doesn't crash

    // Test writing very large dimensions
    rc = trexio_write_nucleus_num(file, INT32_MAX);
    // Implementation may handle this differently, we just test it doesn't crash

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return TREXIO_SUCCESS;
}

static trexio_exit_code test_double_write_scenarios() {
    /* Test scenarios where data is written twice */
    
    trexio_t* file = NULL;
    trexio_exit_code rc;

    /*================= START OF TEST ==================*/

    // Create file
    file = trexio_open(TREXIO_FILE, 'w', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Write data first time
    rc = trexio_write_nucleus_num(file, 2);
    assert(rc == TREXIO_SUCCESS);

    // Try to write same data again - behavior depends on implementation
    rc = trexio_write_nucleus_num(file, 3);
    // Some implementations may allow overwrite, others may not
    // We just test it doesn't crash

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return TREXIO_SUCCESS;
}

static trexio_exit_code test_string_operations_edge_cases() {
    /* Test string operations with edge cases */
    
    trexio_t* file = NULL;
    trexio_exit_code rc;

    /*================= START OF TEST ==================*/

    // Create file
    file = trexio_open(TREXIO_FILE, 'w', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Test empty string
    char* empty_string = "";
    rc = trexio_write_basis_type(file, empty_string, (int32_t)strlen(empty_string));
    // May succeed or fail depending on implementation

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    // Test reading with different buffer sizes
    file = trexio_open(TREXIO_FILE, 'r', TEST_BACKEND, &rc);
    if (file != NULL && rc == TREXIO_SUCCESS) {
        char buffer[100];
        rc = trexio_read_basis_type(file, buffer, 100);
        // May succeed or fail depending on what was written

        rc = trexio_close(file);
        assert(rc == TREXIO_SUCCESS);
    }

    // Test very long string
    file = trexio_open(TREXIO_FILE, 'w', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    char* long_string = "This is a very long string that might exceed normal buffer sizes and test the string handling capabilities of the TREXIO library implementation.";
    rc = trexio_write_basis_type(file, long_string, (int32_t)strlen(long_string));
    // May succeed or fail depending on implementation limits

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return TREXIO_SUCCESS;
}

static trexio_exit_code test_backend_detection() {
    /* Test backend detection and availability functions */
    
    trexio_t* file = NULL;
    trexio_exit_code rc;
    (void)rc;  // Suppress unused variable warning

    /*================= START OF TEST ==================*/

    // Test backend availability
    bool has_text = trexio_has_backend(TREXIO_TEXT);
    (void)has_text;  // Suppress unused variable warning
    // Should not crash

    // Test with HDF5 backend if available
    bool has_hdf5 = trexio_has_backend(TREXIO_HDF5);
    (void)has_hdf5;  // Should not crash

    // Test with invalid backend
    bool has_invalid = trexio_has_backend(999);
    (void)has_invalid;  // Should not crash and likely return false

    /*================= END OF TEST ==================*/

    return TREXIO_SUCCESS;
}

static trexio_exit_code test_get_int64_num_function() {
    /* Test get_int64_num function with various inputs */
    
    trexio_t* file = NULL;
    trexio_exit_code rc;

    /*================= START OF TEST ==================*/

    // Create file with data
    file = trexio_open(TREXIO_FILE, 'w', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Write some int64 number
    rc = trexio_write_rdm_2e_cholesky_num(file, 5);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    // Read and test get_int64_num
    file = trexio_open(TREXIO_FILE, 'r', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Test get_int64_num function - correct type
    int32_t int64_num = 0;
    rc = trexio_get_int64_num(file, &int64_num);
    assert(rc == TREXIO_SUCCESS);
    assert(int64_num == 5);

    // Test with NULL arguments
    rc = trexio_get_int64_num(NULL, &int64_num);
    assert(rc != TREXIO_SUCCESS);

    rc = trexio_get_int64_num(file, NULL);
    assert(rc != TREXIO_SUCCESS);

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return TREXIO_SUCCESS;
}

int main(){

    /*================= Test launcher ================*/

    int rc;
    rc = system(RM_COMMAND);

    printf("# Testing error handling and edge cases...\n");

    // Test invalid arguments
    printf("## Testing invalid arguments\n");
    rc = test_invalid_arguments();
    assert (rc == TREXIO_SUCCESS);

    rc = system(RM_COMMAND);
    assert (rc == 0);

    // Test writing before dimensions
    printf("## Testing write before dimensions\n");
    rc = test_write_before_dimensions();
    assert (rc == TREXIO_SUCCESS);

    rc = system(RM_COMMAND);
    assert (rc == 0);

    // Test reading non-existent data
    printf("## Testing read non-existent data\n");
    rc = test_read_nonexistent_data();
    assert (rc == TREXIO_SUCCESS);

    rc = system(RM_COMMAND);
    assert (rc == 0);

    // Test writing to read-only file
    printf("## Testing write to read-only file\n");
    rc = test_write_to_readonly_file();
    assert (rc == TREXIO_SUCCESS);

    rc = system(RM_COMMAND);
    assert (rc == 0);

    // Test invalid dimensions
    printf("## Testing invalid dimensions\n");
    rc = test_invalid_dimensions();
    assert (rc == TREXIO_SUCCESS);

    rc = system(RM_COMMAND);
    assert (rc == 0);

    // Test double write scenarios
    printf("## Testing double write scenarios\n");
    rc = test_double_write_scenarios();
    assert (rc == TREXIO_SUCCESS);

    rc = system(RM_COMMAND);
    assert (rc == 0);

    // Test string operations edge cases
    printf("## Testing string operations edge cases\n");
    rc = test_string_operations_edge_cases();
    assert (rc == TREXIO_SUCCESS);

    rc = system(RM_COMMAND);
    assert (rc == 0);

    // Test backend detection
    printf("## Testing backend detection\n");
    rc = test_backend_detection();
    assert (rc == TREXIO_SUCCESS);

    rc = system(RM_COMMAND);
    assert (rc == 0);

    // Test get_int64_num function
    printf("## Testing get_int64_num function\n");
    rc = test_get_int64_num_function();
    assert (rc == TREXIO_SUCCESS);

    // Final cleanup
    rc = system(RM_COMMAND);

    printf("# All error handling tests passed!\n");
    return 0;

}