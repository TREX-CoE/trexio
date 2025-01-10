#!/bin/bash

set -e

TESTS_C="\
  io_all \
  open_text \
  io_num_text \
  io_dset_float_text \
  io_dset_int_text \
  io_dset_sparse_text \
  io_determinant_text \
  io_jastrow_text \
  io_safe_dset_float_text \
  io_str_text \
  io_dset_str_text \
  delete_group_text \
  overwrite_all_text \
  pre_close \
  open_hdf5 \
  io_num_hdf5 \
  io_dset_float_hdf5 \
  io_dset_int_hdf5 \
  io_dset_sparse_hdf5 \
  io_determinant_hdf5 \
  io_jastrow_hdf5 \
  io_safe_dset_float_hdf5 \
  io_str_hdf5 \
  io_dset_str_hdf5 \
  delete_group_hdf5 \
  overwrite_all_hdf5"

TESTS="$TESTS_C test_f"

for test in $TESTS; do
    echo "$test"
    libtool --mode=execute valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --error-exitcode=666 \
        --errors-for-leak-kinds=all \
        --suppressions=valgrind.supp \
        "./$test"
done
