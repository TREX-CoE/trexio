# ============= PYTHON SUPPORT ==============

include(GNUInstallDirs)

set(TREXIO_SWIG_MODULE "${PROJECT_SOURCE_DIR}/src/pytrexio.py")

# Python modules are tied to the interpreter that imports them, so they are
# installed next to the library rather than into the include directory. Ask the
# interpreter where its own scheme puts platform-specific packages, with the
# base blanked out so the answer comes back relative to a prefix: that picks up
# lib versus lib64 and the interpreter's own naming instead of assuming them.
#
# Blanking base is what makes this reliable. Deriving the path by taking it
# relative to sys.prefix instead returns local/lib64/... on distributions that
# patch the default scheme to /usr/local, Fedora among them.
execute_process(
  COMMAND
    "${Python3_EXECUTABLE}" -c
    "import os, sysconfig; scheme = sysconfig.get_preferred_scheme('prefix') if hasattr(sysconfig, 'get_preferred_scheme') else ('nt' if os.name == 'nt' else 'posix_prefix'); print(sysconfig.get_path('platlib', scheme, vars={'base': '', 'platbase': ''}).lstrip('/\\\\'))"
  OUTPUT_VARIABLE TREXIO_PLATLIB
  OUTPUT_STRIP_TRAILING_WHITESPACE
  RESULT_VARIABLE TREXIO_PLATLIB_RESULT
  ERROR_QUIET)

if(NOT TREXIO_PLATLIB_RESULT EQUAL 0 OR TREXIO_PLATLIB STREQUAL "")
  set(TREXIO_PLATLIB
      "${CMAKE_INSTALL_LIBDIR}/python${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}/site-packages"
  )
  message(STATUS "Could not ask Python for its package directory; "
                 "falling back to ${TREXIO_PLATLIB}")
endif()

set(TREXIO_INSTALL_PYTHONDIR
    "${TREXIO_PLATLIB}"
    CACHE
      STRING
      "Installation directory for the Python interface, relative to CMAKE_INSTALL_PREFIX unless absolute"
)

# SWIG maps int64_t onto long when SWIGWORDSIZE64 is defined and onto long long
# when it is not, so a wrapper fits only the targets that spell int64_t the same
# way. What decides is that spelling, not how wide long is: int64_t is long on
# LP64 Linux, but long long on ILP32 targets (i686), on LLP64 ones (Windows) and
# also on macOS, which is LP64 yet still spells int64_t long long. Get at it
# with two declarations of one function, which conflict unless the two types are
# the same.
include(CheckCSourceCompiles)
check_c_source_compiles(
  "
#include <stdint.h>
void trexio_check_int64_t(long *);
void trexio_check_int64_t(int64_t *);
int main(void) { return 0; }
"
  TREXIO_INT64_T_IS_LONG)

# A distribution carries one wrapper per spelling, so the one that fits is
# selected here. The define is kept for developer mode, where the wrapper is
# generated below instead.
if(TREXIO_INT64_T_IS_LONG)
  set(TREXIO_SWIG_WORDSIZE_FLAGS "-DSWIGWORDSIZE64")
  set(TREXIO_SWIG_WRAPPER_NAME "pytrexio_wrap_long.c")
else()
  # Unset rather than empty, so that it expands to no argument at all.
  set(TREXIO_SWIG_WORDSIZE_FLAGS)
  set(TREXIO_SWIG_WRAPPER_NAME "pytrexio_wrap_long_long.c")
endif()
set(TREXIO_SWIG_WRAPPER "${PROJECT_SOURCE_DIR}/src/${TREXIO_SWIG_WRAPPER_NAME}")
message(STATUS "Python interface built from ${TREXIO_SWIG_WRAPPER_NAME}")

# Both wrappers are shipped in the distribution, so SWIG is only needed when the
# one that fits is missing, or in developer mode. It is then written to the
# build directory rather than next to the sources, so that a CMake build never
# competes with the Autotools one over the same generated files. It keeps the
# name of the variant it is, so that a build directory reused for a target with
# the other spelling does not pick up the wrong one.
if(TREXIO_DEVEL OR NOT EXISTS "${TREXIO_SWIG_WRAPPER}")
  find_program(SWIG_EXECUTABLE NAMES swig REQUIRED)
  set(TREXIO_SWIG_WRAPPER
      "${CMAKE_CURRENT_BINARY_DIR}/${TREXIO_SWIG_WRAPPER_NAME}")
  set(TREXIO_SWIG_MODULE "${CMAKE_CURRENT_BINARY_DIR}/pytrexio.py")
  add_custom_command(
    OUTPUT "${TREXIO_SWIG_WRAPPER}" "${TREXIO_SWIG_MODULE}"
    COMMAND
      "${SWIG_EXECUTABLE}" -python ${TREXIO_SWIG_WORDSIZE_FLAGS}
      -I${PROJECT_SOURCE_DIR}/include -I${PROJECT_SOURCE_DIR}/src -o
      "${TREXIO_SWIG_WRAPPER}" -outdir "${CMAKE_CURRENT_BINARY_DIR}"
      "${PROJECT_SOURCE_DIR}/src/pytrexio.i"
    DEPENDS "${PROJECT_SOURCE_DIR}/src/pytrexio.i"
            "${PROJECT_SOURCE_DIR}/src/numpy.i"
            "${PROJECT_SOURCE_DIR}/include/trexio.h"
    COMMENT "Generating the Python interface with SWIG"
    VERBATIM)
endif()

# No SOABI suffix, so that both build systems produce the same _pytrexio.so.
python3_add_library(_pytrexio MODULE "${TREXIO_SWIG_WRAPPER}")
target_link_libraries(_pytrexio PRIVATE trexio::trexio Python3::NumPy)
# The wrapper includes trexio_s.h, a private header, which it no longer sits
# next to once it is generated into the build tree.
target_include_directories(_pytrexio PRIVATE "${PROJECT_SOURCE_DIR}/src")

# Assemble an importable copy of the package in the build tree, so that the
# tests exercise what was just built instead of an installed copy.
set(TREXIO_PYTHON_TEST_PKG
    "${PROJECT_BINARY_DIR}/python-test-package"
    CACHE INTERNAL "Staged Python package used by the test suite")
set_target_properties(_pytrexio PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                                           "${TREXIO_PYTHON_TEST_PKG}/trexio")
add_custom_command(
  TARGET _pytrexio
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E make_directory
          "${TREXIO_PYTHON_TEST_PKG}/trexio"
  COMMAND
    "${CMAKE_COMMAND}" -E copy_if_different
    "${PROJECT_SOURCE_DIR}/src/trexio.py"
    "${TREXIO_PYTHON_TEST_PKG}/trexio/__init__.py"
  COMMAND
    "${CMAKE_COMMAND}" -E copy_if_different "${TREXIO_SWIG_MODULE}"
    "${CMAKE_CURRENT_SOURCE_DIR}/pytrexio/_version.py"
    "${TREXIO_PYTHON_TEST_PKG}/trexio/"
  COMMENT "Staging the Python package for the test suite"
  VERBATIM)

# Let the installed module find libtrexio inside the same prefix, so that
# importing it does not depend on LD_LIBRARY_PATH. The path is computed rather
# than hardcoded, so that it still holds when TREXIO_INSTALL_PYTHONDIR is
# pointed somewhere else.
if(NOT IS_ABSOLUTE "${TREXIO_INSTALL_PYTHONDIR}" AND NOT IS_ABSOLUTE
                                                     "${CMAKE_INSTALL_LIBDIR}")
  file(RELATIVE_PATH _trexio_module_to_libdir
       "${CMAKE_INSTALL_PREFIX}/${TREXIO_INSTALL_PYTHONDIR}/trexio"
       "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
  if(APPLE)
    set_target_properties(
      _pytrexio PROPERTIES INSTALL_RPATH
                           "@loader_path/${_trexio_module_to_libdir}")
  else()
    set_target_properties(
      _pytrexio PROPERTIES INSTALL_RPATH "$ORIGIN/${_trexio_module_to_libdir}")
  endif()
endif()

# Everything lands in one importable package, with the generated API as its
# __init__.py, so that `import trexio` pulls in a single directory.
install(TARGETS _pytrexio
        LIBRARY DESTINATION "${TREXIO_INSTALL_PYTHONDIR}/trexio")
install(
  FILES "${PROJECT_SOURCE_DIR}/src/trexio.py"
  DESTINATION "${TREXIO_INSTALL_PYTHONDIR}/trexio"
  RENAME __init__.py)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/pytrexio/_version.py"
              "${TREXIO_SWIG_MODULE}"
        DESTINATION "${TREXIO_INSTALL_PYTHONDIR}/trexio")
