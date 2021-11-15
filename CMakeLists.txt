cmake_minimum_required(VERSION 3.16)

# =========== SETUP THE PROJECT =============

# Initialize the CMake project.
project(Trexio 
	VERSION 2.0.0 
	DESCRIPTION "TREX I/O library" 
	LANGUAGES C Fortran
	)

# Request the C99 standard.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# By default, the shared TREXIO library is built (even without -DBUILD_SHARED_LIBS=ON).
# To change this behaviour, append -DBUILD_STATIC_LIBS=ON to the cmake call.
option(BUILD_SHARED_LIBS "Build the shared library" ON)
option(BUILD_STATIC_LIBS "Build the static library" OFF)

if(BUILD_SHARED_LIBS AND BUILD_STATIC_LIBS)
  set(BUILD_SHARED_LIBS OFF)
endif()

# ========= DEFINE TREXIO C LIBRARY ========= 

# Set a list of TREXIO source files that are always compiled.
set(TREXIO_SOURCES 
	src/trexio.c
	src/trexio_text.c
	)

# Conditional SHARED/STATIC build for TREXIO library.
if(BUILD_SHARED_LIBS AND NOT BUILD_STATIC_LIBS)

  message(STATUS "TREXIO :: shared C library will be built")
  add_library(trexio SHARED ${TREXIO_SOURCES})

elseif(NOT BUILD_SHARED_LIBS AND BUILD_STATIC_LIBS)
  
  message(STATUS "TREXIO :: static C library will be built")
  add_library(trexio STATIC ${TREXIO_SOURCES})

else()
  message(FATAL_ERROR "Building both static and shared TREXIO simultaneously is not supported.")
endif()

# Set TREXIO version and include files.
set_target_properties(trexio PROPERTIES 
	VERSION ${PROJECT_VERSION}
	PUBLIC_HEADER include/trexio.h
	)

# Set directories to be included at build time.
target_include_directories(trexio PRIVATE src)
include_directories(include)

# ============= CONFIGURE HDF5 ============== 

# By default TREXIO is configured with HDF5 support.
# To change this, append -DENABLE-HDF5=OFF to the cmake call.
option(ENABLE_HDF5 "Enable HDF5 support" ON)

if(ENABLE_HDF5)
  # Try to detect HDF5 installation using built-in FindHDF5.cmake macro.
  find_package(HDF5 REQUIRED COMPONENTS C HL)

  if(HDF5_FOUND)
    message(STATUS "HDF5 version     :: ${HDF5_VERSION}")
    message(STATUS "HDF5 include dir :: ${HDF5_INCLUDE_DIRS}")
    message(STATUS "HDF5 libraries   :: ${HDF5_C_LIBRARIES}")
  else()
    # Download and install HDF5 library using FetchContent
    # ...
    # For now - raise a FATAL_ERROR
    message(FATAL_ERROR "HDF5 is enabled but not found.")
  endif()

  # If HDF5 found:
  # - append the trexio_hdf5.c source file with the HDF5 back end
  target_sources(trexio PRIVATE src/trexio_hdf5.c)
  # - define symbol HAVE_HDF5=1 (use to activate HDF5 back end in the preprocessor conditionals)
  target_compile_definitions(trexio PUBLIC HAVE_HDF5=1)
  # - include dirs with HDF5 header files
  target_include_directories(trexio PRIVATE ${HDF5_C_INCLUDE_DIRS})
  # - link to HDF5 C libraries
  target_link_libraries(trexio PRIVATE 
	  ${HDF5_C_HL_LIBRARIES} 
	  ${HDF5_C_LIBRARIES})
endif()

# ================= TESTING ================= 

enable_testing()

# Create a list of tests for TEXT back end.
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
# Create a list of tests for HDF5 back end.
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

# Set ${Tests} variable to the complete list of tests.
  set(Tests io_all ${Tests_text} ${Tests_hdf5})
else()
  set(Tests ${Tests_text})
endif()

# Compile each TREXIO test as an executable and add them to CTest using add_test
foreach(test ${Tests})
  add_executable(${test} tests/${test}.c)
  target_link_libraries(${test} PRIVATE trexio)
  add_test(NAME ${test} COMMAND $<TARGET_FILE:${test}>)
endforeach ()

# ============= INSTALL TREXIO ============== 

include(GNUInstallDirs)
# Use standard GNU directories for installation of TREXIO (e.g. /usr/local/lib|include).
# The installation prefix can be modified using -DCMAKE_INSTALL_PREFIX=<custom/path> option of cmake.
install(TARGETS trexio
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

# =========================================== 

