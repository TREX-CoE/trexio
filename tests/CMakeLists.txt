
# ================= TESTING =================

# Create a list of tests for TEXT back end.
set(Tests_text
  open_text
  io_auxbasis_text
  io_dset_float_text
  io_dset_str_text
  io_dset_sparse_text
  io_determinant_text
  io_jastrow_text
  io_safe_dset_float_text
  io_dset_int_text
  io_num_text
  io_str_text
  io_state_energy_text
  delete_group_text
  overwrite_all_text
  pre_close
  )

if(TREXIO_USE_HDF5)
  # Create a list of tests for HDF5 back end.
  set(Tests_hdf5
    open_hdf5
    io_auxbasis_hdf5
    io_dset_float_hdf5
    io_dset_str_hdf5
    io_dset_sparse_hdf5
    io_determinant_hdf5
    io_jastrow_hdf5
    io_safe_dset_float_hdf5
    io_dset_int_hdf5
    io_num_hdf5
    io_str_hdf5
    io_state_energy_hdf5
    delete_group_hdf5
    overwrite_all_hdf5
    )

# Set ${Tests} variable to the complete list of tests.
  set(Tests io_all ${Tests_text} ${Tests_hdf5})
else()
  set(Tests ${Tests_text})
endif()

# The in-memory back end is always available.
list(APPEND Tests io_memory)

# Compile each TREXIO test as an executable and add them to CTest using add_test.
foreach(Test ${Tests})
  add_executable(${Test} ${Test}.c)
  target_link_libraries(${Test} PRIVATE trexio::trexio)
  add_test(NAME ${Test} COMMAND $<TARGET_FILE:${Test}>)
endforeach()

# Windows has no RPATH so place the test binaries next to the DLL to avoid all
# aborting with STATUS_DLL_NOT_FOUND (0xC0000135).
if(WIN32 AND BUILD_SHARED_LIBS)
  set_target_properties(${Tests} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "$<TARGET_FILE_DIR:trexio>")
endif()

# Run the Python test suite against the module staged in the build tree. pytest
# is a test-only dependency, so the tests are only registered when it is there.
if(TREXIO_PYTHON)
  execute_process(
    COMMAND "${Python3_EXECUTABLE}" -c "import pytest"
    RESULT_VARIABLE _trexio_have_pytest
    OUTPUT_QUIET ERROR_QUIET)
  if(_trexio_have_pytest EQUAL 0)
    if(TREXIO_USE_HDF5)
      set(_trexio_pytest_flags --all)
    else()
      set(_trexio_pytest_flags "")
    endif()
    add_test(NAME python_api
      COMMAND "${Python3_EXECUTABLE}" -m pytest -v ${_trexio_pytest_flags}
              "${PROJECT_SOURCE_DIR}/python/test/test_api.py"
              "${PROJECT_SOURCE_DIR}/python/test/test_memory.py"
      WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
    set_tests_properties(python_api PROPERTIES
      ENVIRONMENT "PYTHONPATH=${TREXIO_PYTHON_TEST_PKG}")
  else()
    message(STATUS "pytest not found: the Python API tests will not be run")
  endif()
endif()

# Add Fortran test and link it with trexio_f (Fortran module) library.
if(TREXIO_FORTRAN)
  add_executable(test_f test_f.f90)
  target_link_libraries(test_f PRIVATE trexio_f)
  add_test(NAME test_f COMMAND $<TARGET_FILE:test_f>)
  if(WIN32 AND BUILD_SHARED_LIBS)
    set_target_properties(test_f PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "$<TARGET_FILE_DIR:trexio>")
  endif()
endif()
