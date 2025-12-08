
# ============= THREADS SUPPORT ==============

# the two options below add preference for the pthread library over other system-wide threads implementations
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
# find thread library
find_package(Threads REQUIRED)

# ============= STDINT SUPPORT ===============

include(CheckIncludeFile)
check_include_file(stdint.h HAVE_STDINT_H)

# ========= DEFINE TREXIO C LIBRARY =========

# Set a list of TREXIO source and header files that are always compiled.
set(TREXIO_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/trexio.c
	${CMAKE_CURRENT_SOURCE_DIR}/trexio_text.c
	)
set(TREXIO_PUBLIC_HEADERS ${PROJECT_SOURCE_DIR}/include/trexio.h)
set(TREXIO_PRIVATE_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/trexio_s.h
	${CMAKE_CURRENT_SOURCE_DIR}/trexio_private.h
	${CMAKE_CURRENT_SOURCE_DIR}/trexio_text.h
	)

# By default, the shared TREXIO library is built (even without -DBUILD_SHARED_LIBS=ON).
# To change this behaviour, append -DBUILD_STATIC_LIBS=ON to the cmake call.
option(BUILD_SHARED_LIBS "Build the shared library" ON)
option(BUILD_STATIC_LIBS "Build the static library" OFF)

if(BUILD_SHARED_LIBS AND BUILD_STATIC_LIBS)
  set(BUILD_SHARED_LIBS OFF)
endif()

# Conditional SHARED/STATIC build for TREXIO library.
if(BUILD_SHARED_LIBS AND NOT BUILD_STATIC_LIBS)

  message(STATUS "TREXIO :: shared C library will be built")
  add_library(trexio SHARED)

elseif(NOT BUILD_SHARED_LIBS AND BUILD_STATIC_LIBS)

  message(STATUS "TREXIO :: static C library will be built")
  add_library(trexio STATIC)
  # Static TREXIO has to be compiled with -fPIC flag. For Shared it is done by default.
  set_property(TARGET trexio PROPERTY POSITION_INDEPENDENT_CODE ON)

else()
  message(FATAL_ERROR "Building both static and shared TREXIO simultaneously is not supported.")
endif()

# Set TREXIO version and include files.
set_target_properties(trexio PROPERTIES
	VERSION ${PROJECT_VERSION}
	PUBLIC_HEADER ${TREXIO_PUBLIC_HEADERS}
	)

include(standard_math_lib)
target_link_std_math(trexio PRIVATE)

# ============= CONFIGURE HDF5 ==============

# By defaulti, TREXIO is configured with the HDF5 support.
# To change this, append -DENABLE_HDF5=OFF to the cmake call.
option(ENABLE_HDF5 "Enable HDF5 support" ON)

if(ENABLE_HDF5)
  # Try to detect HDF5 installation using built-in FindHDF5.cmake macro, unless the target has been set up previously.
  if (NOT TARGET hdf5::hdf5)
      find_package(HDF5 REQUIRED COMPONENTS C)
  endif ()

  if(HDF5_FOUND)
    message(STATUS "HDF5 version     :: ${HDF5_VERSION}")
    message(STATUS "HDF5 include dir :: ${HDF5_INCLUDE_DIRS}")
  elseif(NOT TARGET hdf5::hdf5)
    # Download and install HDF5 library using FetchContent
    # ...
    # For now - raise a FATAL_ERROR
    message(FATAL_ERROR "HDF5 is enabled but not found.")
  endif()

  # If HDF5 found:
  # - append the trexio_hdf5.c source file with the HDF5 back end to the list TREXIO_SOURCES
  list(APPEND TREXIO_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/trexio_hdf5.c)
  list(APPEND TREXIO_PRIVATE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/trexio_hdf5.h)
  # - define symbol HAVE_HDF5=1 (used to activate HDF5 back end in the preprocessor conditionals)
  target_compile_definitions(trexio PUBLIC "HAVE_HDF5")
  target_link_libraries(trexio PRIVATE hdf5::hdf5)
  if (HDF5_IS_PARALLEL)
      if (NOT TARGET MPI::MPI_C)
          find_package(MPI REQUIRED COMPONENTS C)
      endif ()
      target_link_libraries(trexio PUBLIC MPI::MPI_C)
  endif ()
endif()

# Private headers have to be listed as sources, otherwise they are installed
# with public headers upon make install (when using PRIVATE_HEADER property).
target_sources(trexio PRIVATE ${TREXIO_SOURCES} ${TREXIO_PRIVATE_HEADERS})
target_include_directories(trexio PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

# ============= FORTRAN SUPPORT ==============

include(FortranCInterface)
# Check that C and Fortran compilers can talk to each other.
FortranCInterface_VERIFY()

# Fortran module
set(TREXIO_MOD_FILE ${PROJECT_SOURCE_DIR}/include/trexio_f.f90)
# Export to parent scope so tests directory picks this up.
set(TREXIO_MOD_FILE ${TREXIO_MOD_FILE} PARENT_SCOPE)
# Add TREXIO Fortran module as a library.
add_library(trexio_f SHARED)
target_sources(trexio_f PUBLIC ${TREXIO_MOD_FILE})
target_link_libraries(trexio_f PUBLIC trexio)

# ====== CODE GENERATION FOR DEVEL MODE =====

add_custom_command(
        # note writing trex.json to src tree
        COMMAND bash build_json.sh
        OUTPUT  "${PROJECT_SOURCE_DIR}/trex.json"
        DEPENDS "${PROJECT_SOURCE_DIR}/trex.org"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tools
        COMMENT "Generate trex.json from trex.org")

if(TREXIO_DEVEL)
  set(ORG_FILES
	templates_front/templator_front.org
  	templates_text/templator_text.org
    ${PROJECT_SOURCE_DIR}/trex.org
	)
  if(ENABLE_HDF5)
    list(APPEND ORG_FILES templates_hdf5/templator_hdf5.org)
  endif()

  add_custom_command(OUTPUT
	  ${TREXIO_SOURCES}
	  ${TREXIO_PUBLIC_HEADERS}
	  ${TREXIO_PRIVATE_HEADERS}
	  ${TREXIO_MOD_FILE}
      COMMAND ./build_trexio.sh
      DEPENDS ${ORG_FILES} ${PROJECT_SOURCE_DIR}/include/config.h
              "${PROJECT_SOURCE_DIR}/trex.json"
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tools
      COMMENT "Generating TREXIO source code from org-mode files."
      VERBATIM)

  set_source_files_properties(${TREXIO_SOURCES}
                              ${TREXIO_PUBLIC_HEADERS}
                              ${TREXIO_PRIVATE_HEADERS}
                              ${TREXIO_MOD_FILE}
                              PROPERTIES GENERATED TRUE)

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
    "${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

# ===========================================
