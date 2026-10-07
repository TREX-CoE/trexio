# Builds the Python extension module and installs the trexio package.
#
# This is a module rather than part of src/CMakeLists.txt because two entry
# points need it: the library's own build, where -DTREXIO_PYTHON=ON adds the
# package to everything else it installs, and python/CMakeLists.txt, which pip
# drives through scikit-build-core and which can build the package against a
# TREXIO that is already installed. Keeping one implementation is the point;
# the two differ only in where the library comes from.
#
# The includer defines:
#
#   TREXIO_ROOT_DIR          the top of the TREXIO source tree
#   TREXIO_SRC_DIR           its src directory
#   TREXIO_PYTHON_BINARY_DIR where generated files are written
#
# and provides the target trexio::trexio, built here or found with
# find_package(trexio). Python3 must already have been found with the
# Interpreter, Development.Module and NumPy components.

if(NOT TARGET trexio::trexio)
  message(FATAL_ERROR "TrexioPythonModule needs the target trexio::trexio")
endif()

set(TREXIO_SWIG_WRAPPER "${TREXIO_SRC_DIR}/pytrexio_wrap.c")
set(TREXIO_SWIG_MODULE "${TREXIO_SRC_DIR}/pytrexio.py")

# Python modules are tied to the interpreter that imports them, so they are
# installed next to the library rather than into the include directory. Ask
# the interpreter where its own scheme puts platform-specific packages, with
# the base blanked out so the answer comes back relative to a prefix: that
# picks up lib versus lib64 and the interpreter's own naming instead of
# assuming them.
#
# Blanking base is what makes this reliable. Deriving the path by taking it
# relative to sys.prefix instead returns local/lib64/... on distributions that
# patch the default scheme to /usr/local, Fedora among them.
execute_process(
  COMMAND "${Python3_EXECUTABLE}" -c
    "import os, sysconfig; scheme = sysconfig.get_preferred_scheme('prefix') if hasattr(sysconfig, 'get_preferred_scheme') else ('nt' if os.name == 'nt' else 'posix_prefix'); print(sysconfig.get_path('platlib', scheme, vars={'base': '', 'platbase': ''}).lstrip('/\\\\'))"
  OUTPUT_VARIABLE TREXIO_PLATLIB
  OUTPUT_STRIP_TRAILING_WHITESPACE
  RESULT_VARIABLE TREXIO_PLATLIB_RESULT
  ERROR_QUIET)

if(NOT TREXIO_PLATLIB_RESULT EQUAL 0 OR TREXIO_PLATLIB STREQUAL "")
  set(TREXIO_PLATLIB
    "${CMAKE_INSTALL_LIBDIR}/python${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}/site-packages")
  message(STATUS "Could not ask Python for its package directory; "
                 "falling back to ${TREXIO_PLATLIB}")
endif()

set(TREXIO_INSTALL_PYTHONDIR "${TREXIO_PLATLIB}" CACHE STRING
  "Installation directory for the Python interface, relative to CMAKE_INSTALL_PREFIX unless absolute")

# The wrapper is shipped in the distribution, so SWIG is only needed when it is
# missing or when it has to be regenerated in developer mode. It is written to
# the build directory rather than next to the sources, so that a CMake build
# never competes with the Autotools one over the same generated files.
if(TREXIO_DEVEL OR NOT EXISTS "${TREXIO_SWIG_WRAPPER}")
  # The wrapper has to be generated for this tree, so SWIG is a hard
  # requirement of this configuration rather than something to discover
  # halfway through the build, which is issue #339.
  find_package(SWIG 4.0)
  if(NOT SWIG_FOUND)
    message(FATAL_ERROR
      "The Python interface is enabled and its SWIG wrapper has to be generated "
      "for this tree, which needs SWIG (>= 4.0). Either install SWIG or "
      "configure with -DTREXIO_PYTHON=OFF.")
  endif()
  set(TREXIO_SWIG_WRAPPER "${TREXIO_PYTHON_BINARY_DIR}/pytrexio_wrap.c")
  set(TREXIO_SWIG_MODULE "${TREXIO_PYTHON_BINARY_DIR}/pytrexio.py")
  add_custom_command(
    OUTPUT "${TREXIO_SWIG_WRAPPER}" "${TREXIO_SWIG_MODULE}"
    COMMAND "${SWIG_EXECUTABLE}" -python
            -I${TREXIO_ROOT_DIR}/include
            -I${TREXIO_SRC_DIR}
            -o "${TREXIO_SWIG_WRAPPER}"
            -outdir "${TREXIO_PYTHON_BINARY_DIR}"
            "${TREXIO_SRC_DIR}/pytrexio.i"
    DEPENDS "${TREXIO_SRC_DIR}/pytrexio.i"
            "${TREXIO_SRC_DIR}/numpy.i"
            ${TREXIO_PUBLIC_HEADERS}
    COMMENT "Generating the Python interface with SWIG"
    VERBATIM)
endif()

# No SOABI suffix, so that both build systems produce the same _pytrexio.so.
Python3_add_library(_pytrexio MODULE "${TREXIO_SWIG_WRAPPER}")
target_link_libraries(_pytrexio PRIVATE trexio::trexio Python3::NumPy)
# The wrapper includes trexio_s.h, a private header, which it no longer sits
# next to once it is generated into the build tree.
target_include_directories(_pytrexio PRIVATE "${TREXIO_SRC_DIR}")

if(BUILD_TESTING)
  # Assemble an importable copy of the package in the build tree, so that the
  # tests exercise what was just built instead of an installed copy.
  set(TREXIO_PYTHON_TEST_PKG "${PROJECT_BINARY_DIR}/python-test-package"
      CACHE INTERNAL "Staged Python package used by the test suite")
  set_target_properties(_pytrexio PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${TREXIO_PYTHON_TEST_PKG}/trexio")
  add_custom_command(TARGET _pytrexio POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${TREXIO_PYTHON_TEST_PKG}/trexio"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${TREXIO_ROOT_DIR}/src/trexio.py"
            "${TREXIO_PYTHON_TEST_PKG}/trexio/__init__.py"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${TREXIO_SWIG_MODULE}"
            "${TREXIO_ROOT_DIR}/python/pytrexio/_version.py"
            "${TREXIO_PYTHON_TEST_PKG}/trexio/"
    COMMENT "Staging the Python package for the test suite"
    VERBATIM)
endif()

# Let the installed module find libtrexio inside the same prefix, so that
# importing it does not depend on LD_LIBRARY_PATH. The path is computed rather
# than hardcoded, so that it still holds when TREXIO_INSTALL_PYTHONDIR is
# pointed somewhere else.
# A wheel is not a prefix: the package sits at its root, the library is either
# inside the extension or already on the loader's path, and a RUNPATH computed
# from a prefix layout would point at a directory that does not exist there.
if(NOT TREXIO_INSTALL_PYTHONDIR STREQUAL "."
   AND NOT IS_ABSOLUTE "${TREXIO_INSTALL_PYTHONDIR}"
   AND NOT IS_ABSOLUTE "${CMAKE_INSTALL_LIBDIR}")
  file(RELATIVE_PATH _trexio_module_to_libdir
    "${CMAKE_INSTALL_PREFIX}/${TREXIO_INSTALL_PYTHONDIR}/trexio"
    "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
  if(APPLE)
    set_target_properties(_pytrexio PROPERTIES
      INSTALL_RPATH "@loader_path/${_trexio_module_to_libdir}")
  else()
    set_target_properties(_pytrexio PROPERTIES
      INSTALL_RPATH "$ORIGIN/${_trexio_module_to_libdir}")
  endif()
endif()

# Everything lands in one importable package, with the generated API as its
# __init__.py, so that `import trexio` pulls in a single directory. The files
# are tagged as a component of their own, so that a wheel build can install
# the Python package without dragging in the library, the headers and the
# pkg-config and CMake package files.
install(TARGETS _pytrexio
  LIBRARY DESTINATION "${TREXIO_INSTALL_PYTHONDIR}/trexio"
          COMPONENT python
)
install(FILES "${TREXIO_ROOT_DIR}/src/trexio.py"
  DESTINATION "${TREXIO_INSTALL_PYTHONDIR}/trexio"
  RENAME __init__.py
  COMPONENT python
)
install(FILES
    "${TREXIO_ROOT_DIR}/python/pytrexio/_version.py"
    "${TREXIO_SWIG_MODULE}"
  DESTINATION "${TREXIO_INSTALL_PYTHONDIR}/trexio"
  COMPONENT python
)
