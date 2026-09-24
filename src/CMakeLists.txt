# ========= DEFINE TREXIO C LIBRARY =========

include(GNUInstallDirs)

# Set a list of TREXIO source and header files that are always compiled.
set(TREXIO_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/trexio.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/trexio_text.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/trexio_memory.c"
	)
set(TREXIO_PUBLIC_HEADERS "${PROJECT_SOURCE_DIR}/include/trexio.h")
set(TREXIO_PRIVATE_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/trexio_s.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/trexio_private.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/trexio_text.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/trexio_memory.h"
	)

add_library(trexio)
add_library(trexio::trexio ALIAS trexio)

# Set TREXIO version and include files.
set_target_properties(trexio PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION ${PROJECT_VERSION_MAJOR}
	POSITION_INDEPENDENT_CODE ON
	PUBLIC_HEADER ${TREXIO_PUBLIC_HEADERS}
	# allow linking with DLL (BUILD_SHARED_LIBS=ON) without needing __declspec(dllexport)
	WINDOWS_EXPORT_ALL_SYMBOLS ON
	)

# Require C99 to build TREXIO, and propagate it as a usage requirement to
# anything that links the library (tests and external consumers). This is
# scoped to the target, unlike the global CMAKE_C_STANDARD variable.
target_compile_features(trexio PUBLIC c_std_99)

# The Microsoft UCRT marks the standard C string and I/O functions deprecated
# in favour of its own _s variants. TREXIO calls the standard ones with
# explicit bounds (~1000 call sites), so silence the advisory instead of
# forking the code. This is narrower than /wd4996, which would also hide
# genuine __declspec(deprecated) markers coming from other libraries. The
# MSVC variable is also true for compilers targeting the MSVC ABI, e.g. clang-cl.
if(MSVC)
  target_compile_definitions(trexio PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

include(standard_math_lib)
target_link_std_math(trexio PRIVATE TREXIO_STD_MATH_LIB)
target_link_libraries(trexio PRIVATE Threads::Threads)

# ============= CONFIGURE HDF5 ==============
if(TREXIO_USE_HDF5)
  list(APPEND TREXIO_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/trexio_hdf5.c)
  list(APPEND TREXIO_PRIVATE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/trexio_hdf5.h)
  target_compile_definitions(trexio PRIVATE HAVE_HDF5)
  target_link_libraries(trexio PRIVATE HDF5::HDF5)
  if(TREXIO_HDF5_IS_PARALLEL)
    target_link_libraries(trexio PRIVATE MPI::MPI_C)
  endif()
endif()

# Private headers have to be listed as sources, otherwise they are installed
# with public headers upon make install (when using PRIVATE_HEADER property).
target_sources(trexio PRIVATE ${TREXIO_SOURCES} ${TREXIO_PRIVATE_HEADERS})
target_include_directories(trexio PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

# ============= FORTRAN SUPPORT ==============

if(TREXIO_FORTRAN)
  set(_trexio_fortran_module_dir "${CMAKE_CURRENT_BINARY_DIR}/modules")

  add_library(trexio_f ${TREXIO_MOD_FILE})
  target_link_libraries(trexio_f PUBLIC trexio::trexio)
  target_include_directories(trexio_f INTERFACE
    $<BUILD_INTERFACE:${_trexio_fortran_module_dir}>
  )
  set_target_properties(trexio_f PROPERTIES
    Fortran_MODULE_DIRECTORY "${_trexio_fortran_module_dir}"
  )
endif()

# ============= PYTHON SUPPORT ==============

if(TREXIO_PYTHON)
  set(TREXIO_SWIG_WRAPPER "${CMAKE_CURRENT_SOURCE_DIR}/pytrexio_wrap.c")
  set(TREXIO_SWIG_MODULE "${CMAKE_CURRENT_SOURCE_DIR}/pytrexio.py")

  # Python modules are tied to the interpreter that imports them, so they are
  # installed next to the library rather than into the include directory.
  set(TREXIO_INSTALL_PYTHONDIR
    "${CMAKE_INSTALL_LIBDIR}/python${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}/site-packages"
    CACHE STRING
    "Installation directory for the Python interface, relative to CMAKE_INSTALL_PREFIX unless absolute")

  # The wrapper is shipped in the distribution, so SWIG is only needed when it is
  # missing or when it has to be regenerated in developer mode. It is written to
  # the build directory rather than next to the sources, so that a CMake build
  # never competes with the Autotools one over the same generated files.
  if(TREXIO_DEVEL OR NOT EXISTS "${TREXIO_SWIG_WRAPPER}")
    find_program(SWIG_EXECUTABLE NAMES swig REQUIRED)
    set(TREXIO_SWIG_WRAPPER "${CMAKE_CURRENT_BINARY_DIR}/pytrexio_wrap.c")
    set(TREXIO_SWIG_MODULE "${CMAKE_CURRENT_BINARY_DIR}/pytrexio.py")
    add_custom_command(
      OUTPUT "${TREXIO_SWIG_WRAPPER}" "${TREXIO_SWIG_MODULE}"
      COMMAND "${SWIG_EXECUTABLE}" -python
              -I${PROJECT_SOURCE_DIR}/include
              -I${CMAKE_CURRENT_SOURCE_DIR}
              -o "${TREXIO_SWIG_WRAPPER}"
              -outdir "${CMAKE_CURRENT_BINARY_DIR}"
              "${CMAKE_CURRENT_SOURCE_DIR}/pytrexio.i"
      DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/pytrexio.i"
              "${CMAKE_CURRENT_SOURCE_DIR}/numpy.i"
              ${TREXIO_PUBLIC_HEADERS}
      COMMENT "Generating the Python interface with SWIG"
      VERBATIM)
  endif()

  # No SOABI suffix, so that both build systems produce the same _pytrexio.so.
  Python3_add_library(_pytrexio MODULE "${TREXIO_SWIG_WRAPPER}")
  target_link_libraries(_pytrexio PRIVATE trexio::trexio Python3::NumPy)
  # The wrapper includes trexio_s.h, a private header, which it no longer sits
  # next to once it is generated into the build tree.
  target_include_directories(_pytrexio PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

  # Assemble an importable copy of the package in the build tree, so that the
  # tests exercise what was just built instead of an installed copy.
  set(TREXIO_PYTHON_TEST_PKG "${PROJECT_BINARY_DIR}/python-test-package"
      CACHE INTERNAL "Staged Python package used by the test suite")
  set_target_properties(_pytrexio PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${TREXIO_PYTHON_TEST_PKG}/pytrexio")
  add_custom_command(TARGET _pytrexio POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${TREXIO_PYTHON_TEST_PKG}/pytrexio"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${PROJECT_SOURCE_DIR}/src/trexio.py" "${TREXIO_PYTHON_TEST_PKG}/"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${TREXIO_SWIG_MODULE}"
            "${PROJECT_SOURCE_DIR}/python/pytrexio/__init__.py"
            "${PROJECT_SOURCE_DIR}/python/pytrexio/_version.py"
            "${TREXIO_PYTHON_TEST_PKG}/pytrexio/"
    COMMENT "Staging the Python package for the test suite"
    VERBATIM)

  # Let the installed module find libtrexio inside the same prefix, so that
  # importing it does not depend on LD_LIBRARY_PATH. The path is computed rather
  # than hardcoded, so that it still holds when TREXIO_INSTALL_PYTHONDIR is
  # pointed somewhere else.
  if(NOT IS_ABSOLUTE "${TREXIO_INSTALL_PYTHONDIR}" AND NOT IS_ABSOLUTE "${CMAKE_INSTALL_LIBDIR}")
    file(RELATIVE_PATH _trexio_module_to_libdir
      "${CMAKE_INSTALL_PREFIX}/${TREXIO_INSTALL_PYTHONDIR}/pytrexio"
      "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
    if(APPLE)
      set_target_properties(_pytrexio PROPERTIES
        INSTALL_RPATH "@loader_path/${_trexio_module_to_libdir}")
    else()
      set_target_properties(_pytrexio PROPERTIES
        INSTALL_RPATH "$ORIGIN/${_trexio_module_to_libdir}")
    endif()
  endif()

  install(TARGETS _pytrexio
    LIBRARY DESTINATION "${TREXIO_INSTALL_PYTHONDIR}/pytrexio"
  )
  install(FILES "${PROJECT_SOURCE_DIR}/src/trexio.py"
    DESTINATION "${TREXIO_INSTALL_PYTHONDIR}"
  )
  install(FILES
      "${PROJECT_SOURCE_DIR}/python/pytrexio/__init__.py"
      "${PROJECT_SOURCE_DIR}/python/pytrexio/_version.py"
      "${TREXIO_SWIG_MODULE}"
    DESTINATION "${TREXIO_INSTALL_PYTHONDIR}/pytrexio"
  )
endif()

# ====== CODE GENERATION FOR DEVEL MODE =====

if(TREXIO_DEVEL)
  add_custom_command(
        # note writing trex.json to src tree
        COMMAND bash build_json.sh
        OUTPUT  "${PROJECT_SOURCE_DIR}/trex.json"
        DEPENDS "${PROJECT_SOURCE_DIR}/trex.org"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tools
        COMMENT "Generate trex.json from trex.org")

  set(ORG_FILES
      templates_front/templator_front.org
      templates_text/templator_text.org
      ${PROJECT_SOURCE_DIR}/trex.org
  )
  if(TREXIO_USE_HDF5)
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

# ============= INSTALL TREXIO =============

install(TARGETS trexio
  EXPORT trexio-targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if(TREXIO_FORTRAN)
  install(FILES ${TREXIO_MOD_FILE} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()

set(_trexio_install_cmakedir "${CMAKE_INSTALL_LIBDIR}/cmake/trexio")

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/trexio-config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/trexio-config.cmake"
  INSTALL_DESTINATION "${_trexio_install_cmakedir}"
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/trexio-config-version.cmake"
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY SameMajorVersion
)

install(EXPORT trexio-targets
  FILE trexio-targets.cmake
  NAMESPACE trexio::
  DESTINATION "${_trexio_install_cmakedir}"
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/trexio-config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/trexio-config-version.cmake"
  DESTINATION "${_trexio_install_cmakedir}"
)

set(TREXIO_PC_REQUIRES_PRIVATE "")
set(TREXIO_PC_LIBS_PRIVATE "${CMAKE_THREAD_LIBS_INIT}")

if(TREXIO_USE_HDF5)
  find_package(PkgConfig QUIET)
  if(PkgConfig_FOUND)
    pkg_check_modules(_TREXIO_HDF5_PC QUIET hdf5)
  endif()
  if(_TREXIO_HDF5_PC_FOUND)
    set(TREXIO_PC_REQUIRES_PRIVATE "hdf5")
  else()
    # No hdf5.pc on this system (e.g. Fedora, or Debian's hdf5-serial):
    # embed the actual link flags instead of Requiring a missing module.
    foreach(_lib_hdf5 IN LISTS HDF5_C_LIBRARIES)
      string(APPEND TREXIO_PC_LIBS_PRIVATE " ${_lib_hdf5}")
    endforeach()
    if(TREXIO_HDF5_IS_PARALLEL)
      foreach(_lib_mpi IN LISTS MPI_C_LIBRARIES)
        string(APPEND TREXIO_PC_LIBS_PRIVATE " ${_lib_mpi}")
      endforeach()
    endif()
  endif()
endif()

if(TREXIO_STD_MATH_LIB)
  string(APPEND TREXIO_PC_LIBS_PRIVATE " -l${TREXIO_STD_MATH_LIB}")
endif()
string(STRIP "${TREXIO_PC_LIBS_PRIVATE}" TREXIO_PC_LIBS_PRIVATE)

# Keep relative GNUInstallDirs relocatable, while also supporting package
# managers that pass absolute installation directories.
if(IS_ABSOLUTE "${CMAKE_INSTALL_LIBDIR}")
  set(TREXIO_PC_LIBDIR "${CMAKE_INSTALL_LIBDIR}")
else()
  set(TREXIO_PC_LIBDIR "\${prefix}/${CMAKE_INSTALL_LIBDIR}")
endif()
if(IS_ABSOLUTE "${CMAKE_INSTALL_INCLUDEDIR}")
  set(TREXIO_PC_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}")
else()
  set(TREXIO_PC_INCLUDEDIR "\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}")
endif()

configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/trexio.pc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/trexio.pc"
  @ONLY
)

install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/trexio.pc"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
)

# Install documentation
if(TREXIO_BUILD_DOCS)
  install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/docs/"
    DESTINATION "${CMAKE_INSTALL_DOCDIR}"
    FILES_MATCHING
      PATTERN "*.html"
      PATTERN "*.css"
      PATTERN "*.png"
      PATTERN "org-html-themes" EXCLUDE
  )
endif()

# Uninstall target, copied from CMake FAQ:
# https://gitlab.kitware.com/cmake/community/wikis/FAQ#can-i-do-make-uninstall-with-cmake
if(NOT TARGET uninstall)
  configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    @ONLY)
  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
endif()
