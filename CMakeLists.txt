cmake_minimum_required(VERSION 3.19)

# =========== SETUP THE PROJECT =============

# Initialize the CMake project. Fortran is enabled conditionally below so that
# the C library can be built without a Fortran compiler (mirrors the autotools
# --without-fortran option).
project(trexio
	VERSION 2.6.1
	DESCRIPTION "TREX I/O library"
	HOMEPAGE_URL "https://trex-coe.github.io/trexio/"
	LANGUAGES C
	)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_TESTING "Whether to perform tests for TREXIO" ON)

option(TREXIO_FORTRAN "Build and test the TREXIO Fortran interface" ON)

# A project that adds TREXIO through add_subdirectory() or FetchContent links
# the trexio_f target, so the Fortran library has to be installed along with the
# rest of that project; installing the trexio_f.f90 source instead would leave
# the installed consumer with a dangling dependency. A standalone build defaults
# to the source, which is what the Autotools build installs as well.
if(NOT TREXIO_FORTRAN OR CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(_trexio_install_fortran_library_default OFF)
else()
  set(_trexio_install_fortran_library_default ON)
endif()
option(TREXIO_INSTALL_FORTRAN_LIBRARY
  "Install the compiled Fortran interface (libtrexio_f and the trexio module file) instead of the trexio_f.f90 source"
  ${_trexio_install_fortran_library_default})
option(TREXIO_USE_HDF5 "Enable HDF5 support" ON)
option(TREXIO_BUILD_DOCS "Build and install documentation" OFF)

# Optional configure for developer mode to generate source code from org-mode files.
option(TREXIO_DEVEL "TREXIO developer mode (for code generation)." OFF)

if(TREXIO_FORTRAN)
  enable_language(Fortran)
elseif(TREXIO_INSTALL_FORTRAN_LIBRARY)
  message(FATAL_ERROR
    "TREXIO_INSTALL_FORTRAN_LIBRARY requires the Fortran interface; "
    "reconfigure with -DTREXIO_FORTRAN=ON.")
endif()

include(GNUInstallDirs)

# Fortran module files are specific to the compiler and even to its version, so
# they cannot be shared the way C headers are. Distributions therefore keep them
# in a separate directory (e.g. ${CMAKE_INSTALL_LIBDIR}/gfortran/modules), which
# packagers can select here.
set(TREXIO_INSTALL_MODULEDIR "${CMAKE_INSTALL_INCLUDEDIR}" CACHE STRING
  "Installation directory for the Fortran module file, relative to CMAKE_INSTALL_PREFIX unless absolute")

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

# ============= DOCUMENTATION =============

if(TREXIO_DEVEL AND TREXIO_BUILD_DOCS)
  file(GLOB_RECURSE TREXIO_DOC_SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/docs/*.org"
    "${PROJECT_SOURCE_DIR}/src/*.org"
  )
  list(APPEND TREXIO_DOC_SOURCES
    "${PROJECT_SOURCE_DIR}/trex.org"
    "${PROJECT_SOURCE_DIR}/docs/theme.setup"
    "${PROJECT_SOURCE_DIR}/tools/emacs/config_doc.el"
    "${PROJECT_SOURCE_DIR}/tools/emacs/config_tangle.el"
    "${PROJECT_SOURCE_DIR}/tools/build_doc.sh"
  )
  set(TREXIO_DOC_STAMP
    "${PROJECT_BINARY_DIR}/trexio-doc.stamp"
  )
  add_custom_command(
    OUTPUT "${TREXIO_DOC_STAMP}"
    COMMAND bash "${PROJECT_SOURCE_DIR}/tools/build_doc.sh"
    COMMAND "${CMAKE_COMMAND}" -E touch "${TREXIO_DOC_STAMP}"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tools"
    DEPENDS ${TREXIO_DOC_SOURCES}
    COMMENT "Generating HTML documentation from Org files"
    VERBATIM
  )
  add_custom_target(trexio_docs ALL
    DEPENDS "${TREXIO_DOC_STAMP}"
  )
endif()

# ============= BUILD TARGETS =============

# Add subdirectory with add_library(trexio) specifications.
add_subdirectory(src)

# Add subdirectory with unit tests.
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
