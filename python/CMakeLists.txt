# A project of its own for the Python package, so that pip can build it through
# scikit-build-core.
#
# Two things follow from that, and both are the point of this file. The wheel
# carries the metadata a wheel carries -- the .dist-info directory that records
# the version and the dependencies, and that makes the package visible to
# `pip list`, `pip uninstall` and importlib.metadata. Installing the package
# with `cmake --install` produces an importable directory and none of that.
#
# And the package can be built against a TREXIO that is already installed,
# rather than compiling a second copy of the library into the extension module.
# A distribution that packages the library and the Python bindings separately
# wants exactly that: it builds the wheel the ordinary way, and the extension
# links the libtrexio it has already packaged.
cmake_minimum_required(VERSION 3.19)

project(TrexioPython LANGUAGES C)

# Python first, because Python3_add_library needs it.
find_package(Python3 3.6 REQUIRED COMPONENTS Interpreter Development.Module NumPy)

# Three ways to get the library, in order of preference: already a target
# (someone added this directory to a larger build), installed (what a
# distribution wants), or the sources next door (what a wheel built from an sdist
# has to do). CMAKE_DISABLE_FIND_PACKAGE_trexio=ON forces the last one, which is
# how the wheels published to PyPI are built: they cannot depend on a library
# being installed on the machine that imports them.
set(TREXIO_ROOT_DIR "${PROJECT_SOURCE_DIR}/..")

if(NOT TARGET trexio::trexio)
  find_package(trexio CONFIG)
  if(trexio_FOUND)
    message(STATUS "Building the Python package against the installed TREXIO "
                   "${trexio_VERSION}")
  else()
    message(STATUS "No installed TREXIO found: building the bundled sources")
    # The library is built, but neither its tests nor its own Python support,
    # which would be this file again.
    set(TREXIO_PYTHON OFF CACHE BOOL "" FORCE)
    set(TREXIO_FORTRAN OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
    add_subdirectory("${TREXIO_ROOT_DIR}" _deps/trexio-build)
  endif()
endif()

list(APPEND CMAKE_MODULE_PATH "${TREXIO_ROOT_DIR}/cmake")

set(TREXIO_SRC_DIR "${TREXIO_ROOT_DIR}/src")
set(TREXIO_PYTHON_BINARY_DIR "${PROJECT_BINARY_DIR}")

# scikit-build-core installs into the wheel root, so the package goes directly
# there rather than under a platlib path computed for a prefix.
set(TREXIO_INSTALL_PYTHONDIR "." CACHE STRING
  "Installation directory for the Python package")

include(TrexioPythonModule)
