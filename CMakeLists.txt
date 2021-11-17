cmake_minimum_required(VERSION 3.16)

# =========== SETUP THE PROJECT =============

# Initialize the CMake project.
project(Trexio 
	VERSION 2.0.0 
	DESCRIPTION "TREX I/O library" 
	LANGUAGES C Fortran
	)

# Request the C99 standard.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Optional configure for developer mode to generate source code from org-mode files.
option(TREXIO_DEVEL "TREXIO developer mode (for code generation)." OFF)

if(EXISTS ".git/config")
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
endif()

# By default, the shared TREXIO library is built (even without -DBUILD_SHARED_LIBS=ON).
# To change this behaviour, append -DBUILD_STATIC_LIBS=ON to the cmake call.
option(BUILD_SHARED_LIBS "Build the shared library" ON)
option(BUILD_STATIC_LIBS "Build the static library" OFF)

if(BUILD_SHARED_LIBS AND BUILD_STATIC_LIBS)
  set(BUILD_SHARED_LIBS OFF)
endif()

# ========= DEFINE TREXIO C LIBRARY ========= 

# Set a list of TREXIO source and header files that are always compiled.
set(TREXIO_SOURCES 
	${CMAKE_SOURCE_DIR}/src/trexio.c
	${CMAKE_SOURCE_DIR}/src/trexio_text.c
	)
set(TREXIO_PUBLIC_HEADERS ${CMAKE_SOURCE_DIR}/include/trexio.h)
set(TREXIO_PRIVATE_HEADERS 
	${CMAKE_SOURCE_DIR}/src/trexio_s.h
	${CMAKE_SOURCE_DIR}/src/trexio_private.h
	${CMAKE_SOURCE_DIR}/src/trexio_text.h
	)

# Conditional SHARED/STATIC build for TREXIO library.
if(BUILD_SHARED_LIBS AND NOT BUILD_STATIC_LIBS)

  message(STATUS "TREXIO :: shared C library will be built")
  add_library(trexio SHARED)

elseif(NOT BUILD_SHARED_LIBS AND BUILD_STATIC_LIBS)
  
  message(STATUS "TREXIO :: static C library will be built")
  add_library(trexio STATIC)

else()
  message(FATAL_ERROR "Building both static and shared TREXIO simultaneously is not supported.")
endif()

# Set TREXIO version and include files.
set_target_properties(trexio PROPERTIES 
	VERSION ${PROJECT_VERSION}
	PUBLIC_HEADER ${TREXIO_PUBLIC_HEADERS}
	)

# Set directories to be included at build time.
include_directories(include)

# ============= CONFIGURE HDF5 ============== 

# By defaulti, TREXIO is configured with the HDF5 support.
# To change this, append -DENABLE_HDF5=OFF to the cmake call.
option(ENABLE_HDF5 "Enable HDF5 support" ON)

if(ENABLE_HDF5)
  # Try to detect HDF5 installation using built-in FindHDF5.cmake macro.
  find_package(HDF5 REQUIRED COMPONENTS C HL)

  if(HDF5_FOUND)
    message(STATUS "HDF5 version     :: ${HDF5_VERSION}")
    message(STATUS "HDF5 include dir :: ${HDF5_INCLUDE_DIRS}")
  else()
    # Download and install HDF5 library using FetchContent
    # ...
    # For now - raise a FATAL_ERROR
    message(FATAL_ERROR "HDF5 is enabled but not found.")
  endif()

  # If HDF5 found:
  # - append the trexio_hdf5.c source file with the HDF5 back end to the list TREXIO_SOURCES
  list(APPEND TREXIO_SOURCES ${CMAKE_SOURCE_DIR}/src/trexio_hdf5.c)
  list(APPEND TREXIO_PRIVATE_HEADERS ${CMAKE_SOURCE_DIR}/src/trexio_hdf5.h)
  # - define symbol HAVE_HDF5=1 (used to activate HDF5 back end in the preprocessor conditionals)
  target_compile_definitions(trexio PUBLIC "HAVE_HDF5")
  # - include directories with HDF5 header files
  target_include_directories(trexio PRIVATE ${HDF5_C_INCLUDE_DIRS})
  # - link to HDF5 C libraries
  target_link_libraries(trexio PRIVATE 
	  ${HDF5_C_HL_LIBRARIES} 
	  ${HDF5_C_LIBRARIES})
endif()

# Private headers have to be listed as sources, otherwise they are installed
# with public headers upon make install (when using PRIVATE_HEADER property).
target_sources(trexio PRIVATE ${TREXIO_SOURCES} ${TREXIO_PRIVATE_HEADERS})

# ================= TESTING ================= 

enable_testing()

# Create a list of tests for TEXT back end.
set(Tests_text
  open_text
  io_dset_float_text
  io_dset_str_text
  io_safe_dset_float_text
  io_dset_int_text
  io_num_text
  io_str_text
  overwrite_all_text
  )

if(ENABLE_HDF5)
# Create a list of tests for HDF5 back end.
  set(Tests_hdf5
    open_hdf5
    io_dset_float_hdf5
    io_dset_str_hdf5
    io_safe_dset_float_hdf5
    io_dset_int_hdf5
    io_num_hdf5
    io_str_hdf5
    overwrite_all_hdf5
    )

# Set ${Tests} variable to the complete list of tests.
  set(Tests io_all ${Tests_text} ${Tests_hdf5})
else()
  set(Tests ${Tests_text})
endif()

# Compile each TREXIO test as an executable and add them to CTest using add_test.
foreach(test ${Tests})
  add_executable(${test} tests/${test}.c)
  target_link_libraries(${test} PRIVATE trexio)
  add_test(NAME ${test} COMMAND $<TARGET_FILE:${test}>)
endforeach ()

# ============= FORTRAN SUPPORT ==============

include(FortranCInterface)
# Check that C and Fortran compilers can talk to each other.
FortranCInterface_VERIFY()

set(TREXIO_MOD_FILE ${CMAKE_SOURCE_DIR}/include/trexio_f.f90)

# Add TREXIO Fortran module as a library.
add_library(trexio_f SHARED)
target_sources(trexio_f PUBLIC ${TREXIO_MOD_FILE})
target_link_libraries(trexio_f PUBLIC trexio)

# Add Fortran test and link it with the aforementioned library.
add_executable(test_f tests/test_f.f90)
target_link_libraries(test_f PRIVATE trexio_f)
add_test(NAME test_f COMMAND $<TARGET_FILE:test_f>)

# ====== CODE GENERATION FOR DEVEL MODE =====

if(TREXIO_DEVEL)
  set(ORG_FILES
	src/templates_front/templator_front.org
  	src/templates_text/templator_text.org
	trex.org
	)
  if(ENABLE_HDF5)
    list(APPEND ORG_FILES src/templates_hdf5/templator_hdf5.org)
  endif()

  add_custom_command(OUTPUT ${TREXIO_SOURCES}
	  ${TREXIO_PUBLIC_HEADERS}
	  ${TREXIO_PRIVATE_HEADERS}
	  ${TREXIO_MOD_FILE}
      COMMAND ./build_trexio.sh
      DEPENDS ${ORG_FILES}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tools
      COMMENT "Generating TREXIO source code from org-mode files."
      VERBATIM)
endif()

# ============= INSTALL TREXIO ============== 

include(GNUInstallDirs)
# Use standard GNU directories for installation of TREXIO (e.g. /usr/local/lib|include).
# The installation prefix can be modified using -DCMAKE_INSTALL_PREFIX=<custom/path> option of cmake.
install(TARGETS trexio
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)
# Also install trexio_f.f90 file with TREXIO Fortran module.
install(FILES ${TREXIO_MOD_FILE} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Uninstall target, copied from CMake FAQ:
# https://gitlab.kitware.com/cmake/community/wikis/FAQ#can-i-do-make-uninstall-with-cmake
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

# =========================================== 

