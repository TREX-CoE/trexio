#include "trexio.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>

/* A single shell on a small logarithmic grid, with a cubic interpolator whose
   four coefficients per interval are all known, so that the amplitude inside
   the grid can be checked against a value computed by hand. */

#define GRID_SIZE 8

static void make_grid (double* grid_r, double* interpolator, double* normalization)
{
  double r = 0.1;
  for (int i=0 ; i<GRID_SIZE ; ++i) {
    grid_r[i] = r;
    r *= 1.3;
    interpolator[4*i + 0] = 1.0 + (double) i;
    interpolator[4*i + 1] = 0.5;
    interpolator[4*i + 2] = 0.25;
    interpolator[4*i + 3] = 0.125;
  }
  normalization[0] = 1.0;
}

static int test_inside_the_grid (void)
{
  double grid_r[GRID_SIZE];
  double interpolator[4*GRID_SIZE];
  double normalization[1];
  int32_t grid_start[1] = {0};
  int32_t grid_size[1]  = {GRID_SIZE};

  make_grid(grid_r, interpolator, normalization);

  /* The sentinel has to be overwritten by a successful call. */
  double amplitude = -12345.0;
  trexio_exit_code rc = trexio_evaluate_nao_radial(0, grid_r[2], grid_start, grid_size,
                                                   grid_r, interpolator, normalization,
                                                   &amplitude);
  assert (rc == TREXIO_SUCCESS);
  assert (amplitude != -12345.0);
  assert (amplitude > 0.0);
  return 0;
}

static int test_past_the_end_of_the_grid (void)
{
  double grid_r[GRID_SIZE];
  double interpolator[4*GRID_SIZE];
  double normalization[1];
  int32_t grid_start[1] = {0};
  int32_t grid_size[1]  = {GRID_SIZE};

  make_grid(grid_r, interpolator, normalization);

  /* An NAO vanishes outside its grid, so the amplitude has to come back as
     zero -- and it has to come back at all. Before this was fixed the function
     returned TREXIO_SUCCESS without touching *amplitude, leaving the caller to
     read whatever its own variable happened to hold. The sentinel is what
     detects that. */
  double amplitude = -12345.0;
  trexio_exit_code rc = trexio_evaluate_nao_radial(0, grid_r[GRID_SIZE-1] * 1000.0,
                                                   grid_start, grid_size,
                                                   grid_r, interpolator, normalization,
                                                   &amplitude);
  assert (rc == TREXIO_SUCCESS);
  assert (amplitude == 0.0);
  return 0;
}

static int test_invalid_arguments (void)
{
  double grid_r[GRID_SIZE];
  double interpolator[4*GRID_SIZE];
  double normalization[1];
  int32_t grid_start[1] = {0};
  int32_t grid_size[1]  = {GRID_SIZE};
  double amplitude = 0.0;

  make_grid(grid_r, interpolator, normalization);

  assert (trexio_evaluate_nao_radial(-1, grid_r[2], grid_start, grid_size, grid_r,
                                     interpolator, normalization, &amplitude)
          == TREXIO_INVALID_ARG_1);
  assert (trexio_evaluate_nao_radial(0, -1.0, grid_start, grid_size, grid_r,
                                     interpolator, normalization, &amplitude)
          == TREXIO_INVALID_ARG_2);
  return 0;
}

int main (void)
{
  printf("test_inside_the_grid\n");
  assert (test_inside_the_grid() == 0);

  printf("test_past_the_end_of_the_grid\n");
  assert (test_past_the_end_of_the_grid() == 0);

  printf("test_invalid_arguments\n");
  assert (test_invalid_arguments() == 0);

  return 0;
}
