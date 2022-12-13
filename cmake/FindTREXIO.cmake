#===========================================

# Try to find TREXIO library;
# If found, it will define the following variables (note the plural form):
#  TREXIO_FOUND - System has libtrexio;
#  TREXIO_INCLUDE_DIRS - The TREXIO include directories;
#  TREXIO_LIBRARIES - The libraries needed to use TREXIO;

# If TREXIO has been installed in a non-standard location, one can set an
# environment variable $TREXIO_DIR in the current shell:
# $ export TREXIO_DIR=<custom_path>
# to indicate the prefix used during the TREXIO installation
# (typically `./configure prefix=<custom_path> ..` or `cmake -DCMAKE_INSTALL_DIR=<custom_path> ..`)

# This file should be located WITHIN your project source tree.
# (e.g. in cmake/FindTREXIO.cmake)
# How to use it in your project CMakeLists.txt:

# This is needed to locate FindTREXIO.cmake file, modify it according to your source tree.
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

# find_package(TREXIO)
# if (TREXIO_FOUND)
#   include_directories(${TREXIO_INCLUDE_DIRS})
#   target_link_libraries(your_target ${TREXIO_LIBRARIES})
# endif()

#===========================================

# This file is distirbuted under the BSD 3-Clause License.
# Copyright (c) 2021, TREX Center of Excellence

#===========================================

message("<FindTREXIO.cmake>")

set(TREXIO_SEARCH_PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw # Fink
	/opt/local # DarwinPorts
	/opt/csw # Blastwave
	/opt
)

find_path(TREXIO_INCLUDE_DIR
	  NAMES trexio.h
	  HINTS $ENV{TREXIO_DIR}
	  PATH_SUFFIXES include/trexio include
	  PATHS ${TREXIO_SEARCH_PATHS}
	  )


# No need to specify platform-specific prefix (e.g. libtrexio on Unix) or
# suffix (e.g. .so on Unix or .dylib on MacOS) in NAMES. CMake takes care of that.
find_library(TREXIO_LIBRARY
             NAMES trexio
	     HINTS $ENV{TREXIO_DIR}
	     PATH_SUFFIXES lib64 lib
	     PATHS ${TREXIO_SEARCH_PATHS}
	     )

message("<FindTREXIO.cmake>")

# Handle the QUIETLY and REQUIRED arguments and set TREXIO_FOUND to TRUE if
# all listed variables are TRUE.
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TREXIO DEFAULT_MSG TREXIO_LIBRARY TREXIO_INCLUDE_DIR )
MARK_AS_ADVANCED(TREXIO_INCLUDE_DIR TREXIO_LIBRARY)

# Mot setting _INCLUDE_DIR and _LIBRARIES is considered a bug,
# see https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Find-Libraries
set(TREXIO_LIBRARIES ${TREXIO_LIBRARY})
set(TREXIO_INCLUDE_DIRS ${TREXIO_INCLUDE_DIR})

