cmake_minimum_required(VERSION 3.19)

# =========== SETUP THE PROJECT =============

# Initialize the CMake project. Fortran is enabled conditionally below so that
# the C library can be built without a Fortran compiler (mirrors the autotools
# --without-fortran option).
project(Trexio
	VERSION 2.6.1
	DESCRIPTION "TREX I/O library"
	HOMEPAGE_URL "https://trex-coe.github.io/trexio/"
	LANGUAGES C
	)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_TESTING "Whether to perform tests for TREXIO" ON)

option(TREXIO_FORTRAN "Build and test the TREXIO Fortran interface" ON)
option(TREXIO_USE_HDF5 "Enable HDF5 support" ON)

# Optional configure for developer mode to generate source code from org-mode files.
option(TREXIO_DEVEL "TREXIO developer mode (for code generation)." OFF)

if(TREXIO_FORTRAN)
  enable_language(Fortran)
endif()

# The C99 requirement is expressed per target on the trexio library (see
# src/CMakeLists.txt) rather than via the global CMAKE_C_STANDARD variable,
# which would otherwise leak into every target of a parent project that adds
# TREXIO through add_subdirectory() or FetchContent.

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# ============= CONFIGURE DEPENDENCIES ==============

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(TREXIO_HDF5_IS_PARALLEL OFF)
if(TREXIO_USE_HDF5)
  find_package(HDF5 REQUIRED COMPONENTS C)
  if(HDF5_IS_PARALLEL)
    set(TREXIO_HDF5_IS_PARALLEL ON)
    find_package(MPI REQUIRED COMPONENTS C)
  endif()
endif()

if(TREXIO_FORTRAN)
  include(FortranCInterface)
  FortranCInterface_VERIFY()
endif()

set(TREXIO_MOD_FILE "${PROJECT_SOURCE_DIR}/include/trexio_f.f90")

if(EXISTS "${PROJECT_SOURCE_DIR}/.devel")
  message(STATUS "Detected ${PROJECT_SOURCE_DIR}/.devel, enabling developer mode")
  set(TREXIO_DEVEL ON)
endif()

if(TREXIO_DEVEL)
  find_package(Python3 3.6 REQUIRED COMPONENTS Interpreter)
  find_program(EMACS_EXECUTABLE NAMES emacs REQUIRED)
  message(STATUS "Emacs executable: ${EMACS_EXECUTABLE}")
  # In case Git is not available, default to "unknown".
  set(GIT_HASH "unknown")
  find_package(Git QUIET)
  if(Git_FOUND)
    execute_process(
      COMMAND "${GIT_EXECUTABLE}" --no-pager show -s --pretty=format:%H -n 1
      OUTPUT_VARIABLE GIT_HASH
      OUTPUT_STRIP_TRAILING_WHITESPACE
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
      ERROR_QUIET)
  endif()
  # get the user name from the ${USER} env variable
  set(TREXIO_USER_NAME "$ENV{USER}")
  # replace placeholders in the templace config.h.in file to produce config.h
  # config.h is needed to insert TREXIO_PACKAGE_VERSION and TREXIO_GIT_HASH into trexio.h
  configure_file(
    "${PROJECT_SOURCE_DIR}/include/cmake_config.h.in"
    "${PROJECT_SOURCE_DIR}/include/config.h"
    @ONLY)
endif()

# Add subdirectory with add_library(trexio) specifications.
add_subdirectory(src)

# Add subdirectory with unit tests.
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
