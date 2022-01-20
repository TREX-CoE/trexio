cmake_minimum_required(VERSION 3.16)

# =========== SETUP THE PROJECT =============

# Initialize the CMake project.
project(Trexio
	VERSION 2.1.0
	DESCRIPTION "TREX I/O library"
	LANGUAGES C Fortran
	)

# Request the C99 standard.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Optional configure for developer mode to generate source code from org-mode files.
option(TREXIO_DEVEL "TREXIO developer mode (for code generation)." OFF)

if(EXISTS "${CMAKE_SOURCE_DIR}/.git/config")
  set(TREXIO_DEVEL ON)
  find_package(Python3 REQUIRED)
  if(Python3_FOUND)
    if(Python3_VERSION_MINOR LESS 6)
      message(FATAL_ERROR "Required Python3 version :: >= 3.6; Found :: ${Python3_VERSION}")
    else()
      message(STATUS "Python3 version :: ${Python3_VERSION}")
    endif()
  endif()
  find_program(EMACS NAMES emacs REQUIRED)
  if(NOT EMACS-NOTFOUND)
    message(STATUS "EMACS detected :: ${EMACS}")
  else()
    message(FATAL_ERROR "EMACS not found. It is required to produce TREXIO source code from org-mode files.")
  endif()
  configure_file(${CMAKE_SOURCE_DIR}/include/cmake_config.h.in
                 ${CMAKE_SOURCE_DIR}/include/config.h)
endif()

# Set directories to be included at build time.
include_directories(include)

# Add subdirectory with add_library(trexio) specifications.
add_subdirectory(src)

# Add subdirectory with unit tests.
enable_testing()
add_subdirectory(tests)
