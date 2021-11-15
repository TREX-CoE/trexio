cmake_minimum_required(VERSION 3.16)

# =========== SETUP THE PROJECT =============

project(Trexio 
	VERSION 2.0.0 
	DESCRIPTION "TREX I/O library" 
	LANGUAGES C Fortran
	)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ========= DEFINE TREXIO C LIBRARY ========= 

#IF DO_SHARED
add_library(trexio SHARED
	src/trexio.c
	src/trexio_text.c
	)
#ELIF DO_STATIC

#ENDIF

set_target_properties(trexio PROPERTIES 
	VERSION ${PROJECT_VERSION}
	PUBLIC_HEADER include/trexio.h
	)

target_include_directories(trexio PRIVATE src)
include_directories(include)

# ============= CONFIGURE HDF5 ============== 

option(ENABLE_HDF5 "Enable HDF5 support" ON)

if(ENABLE_HDF5)
  find_package(HDF5 REQUIRED COMPONENTS C HL)

  if(HDF5_FOUND)
    message(STATUS "HDF5 version     :: ${HDF5_VERSION}")
    message(STATUS "HDF5 include dir :: ${HDF5_INCLUDE_DIRS}")
    message(STATUS "HDF5 libraries   :: ${HDF5_C_LIBRARIES}")
  else()
    # Download and install HDF5 library using FetchContent
    # ...
    # For now - raise a FatalError
    message(FATAL_ERROR "HDF5 is enabled not found.")
  endif()

  target_sources(trexio PRIVATE src/trexio_hdf5.c)
  target_compile_definitions(trexio PUBLIC HAVE_HDF5=1)
  target_include_directories(trexio PRIVATE ${HDF5_C_INCLUDE_DIRS})
  target_link_libraries(trexio PRIVATE 
	  ${HDF5_C_HL_LIBRARIES} 
	  ${HDF5_C_LIBRARIES})
endif()

# ================= TESTING ================= 

enable_testing()

# create the lists of tests
set(Tests_text
  open_text
  io_dset_float_text
  io_dset_str_text
  io_safe_dset_float_text
  io_dset_int_text
  io_num_text
  io_str_text
  overwrite_all_text
  )

if(ENABLE_HDF5)
  set(Tests_hdf5
    open_hdf5
    io_dset_float_hdf5
    io_dset_str_hdf5
    io_safe_dset_float_hdf5
    io_dset_int_hdf5
    io_num_hdf5
    io_str_hdf5
    overwrite_all_hdf5
    )
  set(Tests io_all ${Tests_text} ${Tests_hdf5})
else()
  set(Tests ${Tests_text})
endif()

# Add all the ADD_TEST for each test
foreach(test ${Tests})
  add_executable(${test} tests/${test}.c)
  target_link_libraries(${test} PRIVATE trexio)
  add_test(NAME ${test} COMMAND $<TARGET_FILE:${test}>)
endforeach ()

# ============= INSTALL TREXIO ============== 

include(GNUInstallDirs)
install(TARGETS trexio
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

# =========================================== 

