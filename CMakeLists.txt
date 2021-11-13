cmake_minimum_required(VERSION 3.16)

project(Trexio 
	VERSION 2.0.0 
	DESCRIPTION "TREX I/O library" 
	LANGUAGES C Fortran
	)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

option(ENABLE_HDF5 "Enable HDF5 support" ON)

if(ENABLE_HDF5)
  find_package(HDF5 REQUIRED)
  if(HDF5_FOUND)
    message(STATUS "HDF5 version     :: ${HDF5_VERSION}")
    message(STATUS "HDF5 include dir :: ${HDF5_INCLUDE_DIRS}")
    message(STATUS "HDF5 libraries   :: ${HDF5_C_LIBRARIES}")
  else()
    # Download and install HDF5 library using FetchContent
    # ...
  endif()
endif()

#IF DO_SHARED
add_library(trexio SHARED
	src/trexio.c
	src/trexio_hdf5.c
	src/trexio_text.c
	)
#ELIF DO_STATIC

#ENDIF

set_target_properties(trexio PROPERTIES 
	VERSION ${PROJECT_VERSION}
	PUBLIC_HEADER include/trexio.h
	)

target_include_directories(trexio PRIVATE 
	include 
	src
	)

if(ENABLE_HDF5)
  target_include_directories(trexio PRIVATE ${HDF5_C_INCLUDE_DIRS})
  target_link_libraries(trexio PRIVATE ${HDF5_C_LIBRARIES})
endif()


include(GNUInstallDirs)
install(TARGETS trexio
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )


