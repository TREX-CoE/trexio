

#===========================================

# This file should be located WITHIN your project source tree.
# (e.g. in cmake/FindTREXIO.cmake file)

# usage in CMakeLists.txt 
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")
#find_package(TREXIO)
#include_directories("${TREXIO_INCLUDE_DIR}")
#target_link_libraries(your_target ${TREXIO_LIBRARY})

#===========================================

# If already in cache, be silent
if (TREXIO_INCLUDE_DIR AND TREXIO_LIBRARY)
  set(TREXIO_FIND_QUIETLY TRUE)
endif()

set(TREXIO_FOUND OFF)
set(TREXIO_LIBRARY)

set(TREXIO_NAMES "libtrexio.so")
#set(TREXIO_NAMES "libtrexio.so" "libtrexio.dylib" "libtrexio.la")

find_path(TREXIO_INCLUDE_DIR 
	  NAMES trexio.h 
	  HINTS /usr/include
	        /usr/local/include
		$ENV{HOME}/include)

find_library(TREXIO_LIBRARY
             NAMES ${TREXIO_NAMES}
             PATHS /usr/lib
                   /usr/local/lib
		   $ENV{HOME}/lib
             NO_DEFAULT_PATH)


# Handle the QUIETLY and REQUIRED arguments and set TREXIO_FOUND to TRUE if
# all listed variables are TRUE.
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TREXIO DEFAULT_MSG TREXIO_LIBRARY TREXIO_INCLUDE_DIR )
MARK_AS_ADVANCED(TREXIO_INCLUDE_DIR TREXIO_LIBRARY)
