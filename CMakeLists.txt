cmake_minimum_required(VERSION 3.16)

# =========== SETUP THE PROJECT =============

project(Trexio 
	VERSION 2.0.0 
	DESCRIPTION "TREX I/O library" 
	LANGUAGES C Fortran
	)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ============= CONFIGURE HDF5 ============== 

option(ENABLE_HDF5 "Enable HDF5 support" ON)

if(ENABLE_HDF5)
	find_package(HDF5 REQUIRED COMPONENTS C HL)
  if(HDF5_FOUND)
    message(STATUS "HDF5 version     :: ${HDF5_VERSION}")
    message(STATUS "HDF5 include dir :: ${HDF5_INCLUDE_DIRS}")
    message(STATUS "HDF5 libraries   :: ${HDF5_C_LIBRARIES}")
  else()
    # Download and install HDF5 library using FetchContent
    # ...
  endif()
endif()

# ========= DEFINE TREXIO C LIBRARY ========= 

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

target_include_directories(trexio PRIVATE src)

include_directories(include)

if(ENABLE_HDF5)
	target_include_directories(trexio PRIVATE ${HDF5_C_INCLUDE_DIRS})
	target_link_libraries(trexio PRIVATE ${HDF5_C_HL_LIBRARIES} ${HDF5_C_LIBRARIES})
endif()

# ================= TESTING ================= 

enable_testing()

add_executable(io_all tests/io_all.c)
target_link_libraries(io_all PRIVATE trexio)
add_test(
  NAME io_all
  COMMAND $<TARGET_FILE:io_all>
)

# ============= INSTALL TREXIO ============== 

include(GNUInstallDirs)
install(TARGETS trexio
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

# =========================================== 

