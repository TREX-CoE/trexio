
# ================= TESTING =================

# Create a list of tests for TEXT back end.
set(Tests_text
  open_text
  io_dset_float_text
  io_dset_str_text
  io_dset_sparse_text
  io_determinant_text
  io_safe_dset_float_text
  io_dset_int_text
  io_num_text
  io_str_text
  delete_group_text
  overwrite_all_text
  pre_close
  utility_functions_text
  delete_operations_text
  comprehensive_io_text
  error_handling_text
  )

if(ENABLE_HDF5)
# Create a list of tests for HDF5 back end.
  set(Tests_hdf5
    open_hdf5
    io_dset_float_hdf5
    io_dset_str_hdf5
    io_dset_sparse_hdf5
    io_determinant_hdf5
    io_safe_dset_float_hdf5
    io_dset_int_hdf5
    io_num_hdf5
    io_str_hdf5
    delete_group_hdf5
    overwrite_all_hdf5
    utility_functions_hdf5
    delete_operations_hdf5
    comprehensive_io_hdf5
    error_handling_hdf5
    )

# Set ${Tests} variable to the complete list of tests.
  set(Tests io_all ${Tests_text} ${Tests_hdf5})
else()
  set(Tests ${Tests_text})
endif()

# Compile each TREXIO test as an executable and add them to CTest using add_test.
foreach(Test ${Tests})
  add_executable(${Test} ${Test}.c)
  target_link_libraries(${Test} PRIVATE trexio)
  add_test(NAME ${Test} COMMAND $<TARGET_FILE:${Test}>)
endforeach()

# Add Fortran test and link it with trexio_f (Fortran module) library.
add_executable(test_f test_f.f90)
target_link_libraries(test_f PRIVATE trexio_f)
if(TREXIO_DEVEL)
  set_source_files_properties(${TREXIO_MOD_FILE}
                              PROPERTIES GENERATED TRUE)
endif()
add_test(NAME test_f COMMAND $<TARGET_FILE:test_f>)
