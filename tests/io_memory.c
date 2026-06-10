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
#include <math.h>
#include "trexio.h"

/* Exact float comparison trips -Werror=float-equal; compare within a tol. */
static int dclose(const double a, const double b) { return fabs(a - b) < 1e-12; }

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
  EXPECT(dclose(charge_r[0], 1.0) && dclose(charge_r[1], 8.0) && dclose(charge_r[2], 1.0));

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

  /* ---- sparse data: a few two-electron integrals (4-index) ---- */
  CHECK_RC(trexio_write_mo_num(f, 4));
  {
    const int32_t idx[3*4] = { 0,0,0,0,  1,0,1,0,  2,1,3,2 };
    const double  val[3]   = { 1.5, -0.25, 0.75 };
    CHECK_RC(trexio_write_mo_2e_int_eri(f, 0, 3, idx, val));

    int64_t nmax = 0;
    CHECK_RC(trexio_read_mo_2e_int_eri_size(f, &nmax));
    EXPECT(nmax == 3);

    int32_t idx_r[3*4] = {0};
    double  val_r[3]   = {0};
    int64_t read_size  = 3;
    rc = trexio_read_mo_2e_int_eri(f, 0, &read_size, idx_r, val_r);
    EXPECT(rc == TREXIO_SUCCESS || rc == TREXIO_END);
    EXPECT(read_size == 3);
    EXPECT(idx_r[0]==0 && idx_r[4]==1 && idx_r[8]==2 && idx_r[11]==2);
    EXPECT(dclose(val_r[0], 1.5) && dclose(val_r[1], -0.25) && dclose(val_r[2], 0.75));
    EXPECT(trexio_has_mo_2e_int_eri(f) == TREXIO_SUCCESS);
  }

  /* ---- determinant list (int64 bit fields) + coefficients (buffered) ---- */
  CHECK_RC(trexio_write_electron_up_num(f, 2));
  CHECK_RC(trexio_write_electron_dn_num(f, 2));
  {
    /* mo_num=4 -> 1 int64 per spin -> 2 int64 per determinant.
       Each spin bit-field must have 2 set bits (up_num = dn_num = 2). */
    const int64_t dets[2*2] = { 0x3, 0x3,   0x5, 0x6 };
    CHECK_RC(trexio_write_determinant_list(f, 0, 2, dets));
    const double coef[2] = { 0.99, -0.14 };
    CHECK_RC(trexio_write_determinant_coefficient(f, 0, 2, coef));

    int32_t ndet = 0;
    CHECK_RC(trexio_read_determinant_num(f, &ndet));
    EXPECT(ndet == 2);

    int64_t dets_r[2*2] = {0};
    int64_t nread = 2;
    rc = trexio_read_determinant_list(f, 0, &nread, dets_r);
    EXPECT(rc == TREXIO_SUCCESS || rc == TREXIO_END);
    EXPECT(dets_r[0]==0x3 && dets_r[1]==0x3 && dets_r[2]==0x5 && dets_r[3]==0x6);

    double coef_r[2] = {0};
    int64_t ncoef = 2;
    rc = trexio_read_determinant_coefficient(f, 0, &ncoef, coef_r);
    EXPECT(rc == TREXIO_SUCCESS || rc == TREXIO_END);
    EXPECT(dclose(coef_r[0], 0.99) && dclose(coef_r[1], -0.14));
  }

  CHECK_RC(trexio_close(f));

  if (failures == 0) {
    printf("io_memory: all checks passed\n");
    return 0;
  }
  printf("io_memory: %d failures\n", failures);
  return 1;
}
