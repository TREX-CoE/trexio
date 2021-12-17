
# ================= TESTING =================

# Create a list of tests for TEXT back end.
set(Tests_text
  open_text
  io_dset_float_text
  io_dset_str_text
  io_dset_sparse_text
  io_safe_dset_float_text
  io_dset_int_text
  io_num_text
  io_str_text
  overwrite_all_text
  )

if(ENABLE_HDF5)
# Create a list of tests for HDF5 back end.
  set(Tests_hdf5
    open_hdf5
    io_dset_float_hdf5
    io_dset_str_hdf5
    io_dset_sparse_hdf5
    io_safe_dset_float_hdf5
    io_dset_int_hdf5
    io_num_hdf5
    io_str_hdf5
    overwrite_all_hdf5
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
add_test(NAME test_f COMMAND $<TARGET_FILE:test_f>)
