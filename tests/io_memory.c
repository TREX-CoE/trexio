/* Test for the in-memory (RAM) back end.
 *
 * Opens an in-memory file, writes data of each supported category
 * (dimension, numerical dataset, string attribute, string dataset), reads it
 * back from the SAME handle, and checks the values and the has_* queries.
 * This exercises the same-process, disk-free exchange path.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trexio.h"

static int failures = 0;
#define CHECK_RC(rc) do { if ((rc) != TREXIO_SUCCESS) {                  \
  printf("FAIL  line %d: rc=%d (%s)\n", __LINE__, (rc),                  \
         trexio_string_of_error(rc)); ++failures; } } while (0)
#define EXPECT(cond) do { if (!(cond)) {                                 \
  printf("FAIL  line %d: %s\n", __LINE__, #cond); ++failures; } } while (0)

int main(void)
{
  trexio_exit_code rc;

  trexio_t* f = trexio_open("io_memory_dummy", 'w', TREXIO_MEMORY, &rc);
  if (rc != TREXIO_SUCCESS) {
    printf("FAIL open: %d (%s)\n", rc, trexio_string_of_error(rc));
    return 1;
  }

  /* dimension / numerical attribute */
  CHECK_RC(trexio_write_nucleus_num(f, 3));

  /* numerical dataset (float) */
  const double charge[3] = {1.0, 8.0, 1.0};
  CHECK_RC(trexio_write_nucleus_charge(f, charge));

  /* string attribute */
  CHECK_RC(trexio_write_nucleus_point_group(f, "C2v", 4));

  /* string dataset */
  const char* labels[3] = {"H", "O", "H"};
  CHECK_RC(trexio_write_nucleus_label(f, labels, 4));

  /* has_* queries on present data */
  EXPECT(trexio_has_nucleus_num(f)         == TREXIO_SUCCESS);
  EXPECT(trexio_has_nucleus_charge(f)      == TREXIO_SUCCESS);
  EXPECT(trexio_has_nucleus_point_group(f) == TREXIO_SUCCESS);
  EXPECT(trexio_has_nucleus_label(f)       == TREXIO_SUCCESS);
  /* something not written */
  EXPECT(trexio_has_nucleus_coord(f)       == TREXIO_HAS_NOT);

  /* read everything back from the same handle */
  int32_t num = 0;
  CHECK_RC(trexio_read_nucleus_num(f, &num));
  EXPECT(num == 3);

  double charge_r[3] = {0};
  CHECK_RC(trexio_read_nucleus_charge(f, charge_r));
  EXPECT(charge_r[0] == 1.0 && charge_r[1] == 8.0 && charge_r[2] == 1.0);

  char pg[16];
  CHECK_RC(trexio_read_nucleus_point_group(f, pg, 16));
  EXPECT(strcmp(pg, "C2v") == 0);

  char* labels_r[3];
  for (int i = 0; i < 3; ++i) labels_r[i] = calloc(8, sizeof(char));
  CHECK_RC(trexio_read_nucleus_label(f, labels_r, 8));
  EXPECT(strcmp(labels_r[0], "H") == 0);
  EXPECT(strcmp(labels_r[1], "O") == 0);
  EXPECT(strcmp(labels_r[2], "H") == 0);
  for (int i = 0; i < 3; ++i) free(labels_r[i]);

  CHECK_RC(trexio_close(f));

  if (failures == 0) {
    printf("io_memory: all checks passed\n");
    return 0;
  }
  printf("io_memory: %d failures\n", failures);
  return 1;
}
