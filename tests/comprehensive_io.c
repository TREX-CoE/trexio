#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int test_basic_has_read_write() {
    /* Test basic has/read/write operations that weren't covered in existing tests */
    
    trexio_t* file = NULL;
    trexio_exit_code rc;

    /*================= START OF TEST ==================*/

    // Create file and test various has/read/write operations
    file = trexio_open(TREXIO_FILE, 'w', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Test some additional nucleus operations not covered in existing tests
    rc = trexio_write_nucleus_point_group(file, "C1", 2);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_write_nucleus_repulsion(file, 85.123456);
    assert(rc == TREXIO_SUCCESS);

    // Test some electron operations
    rc = trexio_write_electron_up_num(file, 5);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_write_electron_dn_num(file, 5);
    assert(rc == TREXIO_SUCCESS);

    // Test some state operations
    rc = trexio_write_state_id(file, 0);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_write_state_energy(file, -76.54321);
    assert(rc == TREXIO_SUCCESS);

    char* current_label = "Ground State";
    rc = trexio_write_state_current_label(file, current_label, (int32_t)strlen(current_label));
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    // Read file and verify data
    file = trexio_open(TREXIO_FILE, 'r', TEST_BACKEND, &rc);
    assert(file != NULL);
    assert(rc == TREXIO_SUCCESS);

    // Test has functions
    rc = trexio_has_nucleus_point_group(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_has_nucleus_repulsion(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_has_electron_up_num(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_has_electron_dn_num(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_has_state_id(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_has_state_energy(file);
    assert(rc == TREXIO_SUCCESS);

    rc = trexio_has_state_current_label(file);
    assert(rc == TREXIO_SUCCESS);

    // Test read functions
    char point_group[10];
    rc = trexio_read_nucleus_point_group(file, point_group, 10);
    assert(rc == TREXIO_SUCCESS);
    assert(strcmp(point_group, "C1") == 0);

    double repulsion;
    rc = trexio_read_nucleus_repulsion(file, &repulsion);
    assert(rc == TREXIO_SUCCESS);
    assert(fabs(repulsion - 85.123456) < 1e-12);

    int32_t up_num, dn_num;
    rc = trexio_read_electron_up_num(file, &up_num);
    assert(rc == TREXIO_SUCCESS);
    assert(up_num == 5);

    rc = trexio_read_electron_dn_num(file, &dn_num);
    assert(rc == TREXIO_SUCCESS);
    assert(dn_num == 5);

    int32_t read_state_id;
    double read_energy;
    char read_current_label[100];

    rc = trexio_read_state_id(file, &read_state_id);
    assert(rc == TREXIO_SUCCESS);
    assert(read_state_id == 0);

    rc = trexio_read_state_energy(file, &read_energy);
    assert(rc == TREXIO_SUCCESS);
    assert(fabs(read_energy - (-76.54321)) < 1e-12);

    rc = trexio_read_state_current_label(file, read_current_label, 100);
    assert(rc == TREXIO_SUCCESS);
    assert(strcmp(read_current_label, current_label) == 0);

    rc = trexio_close(file);
    assert(rc == TREXIO_SUCCESS);

    /*================= END OF TEST ==================*/

    return 0;
}

int main(){

    /*================= Test launcher ================*/

    int rc;
    rc = system(RM_COMMAND);

    printf("# Testing additional has/read/write operations...\n");

    printf("## Testing basic operations not covered in existing tests\n");
    rc = test_basic_has_read_write();
    assert (rc == 0);

    // Clean up
    rc = system(RM_COMMAND);

    printf("# All comprehensive I/O tests passed!\n");
    return 0;

}