# The OCaml and Rust interfaces are built by their own tools, dune and cargo, so
# they are driven as custom targets rather than being described to CMake. Both are
# pointed at the library built here instead of one installed on the system.

find_package(Python3 COMPONENTS Interpreter QUIET)

if(TREXIO_OCAML)
  find_program(TREXIO_DUNE dune)
  if(NOT TREXIO_DUNE)
    message(FATAL_ERROR
      "TREXIO_OCAML needs dune, the OCaml build system, which was not found.")
  endif()
  if(NOT Python3_Interpreter_FOUND)
    message(FATAL_ERROR
      "TREXIO_OCAML needs a Python 3 interpreter to generate the OCaml stubs "
      "from trex.json.")
  endif()

  # dune locates the library with pkg-config, so it is given a pkg-config file
  # describing this build tree. It has to be named trexio.pc, because that is the
  # name looked up, and it goes in a directory of its own so that nothing else is
  # found there. file(GENERATE) rather than configure_file(), because the library
  # directory is only known per configuration.
  set(TREXIO_UNINSTALLED_PC_DIR "${PROJECT_BINARY_DIR}/pkgconfig-uninstalled")
  file(GENERATE
    OUTPUT "${TREXIO_UNINSTALLED_PC_DIR}/trexio.pc"
    CONTENT "includedir=${PROJECT_SOURCE_DIR}/include
builtincludedir=${PROJECT_BINARY_DIR}/trexio-generated
libdir=$<TARGET_FILE_DIR:trexio>

Name: trexio
Description: TREX Input/Output library, uninstalled
Version: ${PROJECT_VERSION}
Cflags: -I\${includedir} -I\${builtincludedir}
Libs: -L\${libdir} -ltrexio
")

  # dune keeps its output under ocaml/trexio/_build, so it runs in the source
  # directory; only the generated stubs and that directory are written to.
  add_custom_target(trexio_ocaml ALL
    COMMAND "${CMAKE_COMMAND}" -E env
            "TREXIO_JSON=${PROJECT_SOURCE_DIR}/trex.json"
            "TREXIO_CONFIGURE_AC=${PROJECT_SOURCE_DIR}/configure.ac"
            "${Python3_EXECUTABLE}" read_json.py
    COMMAND "${CMAKE_COMMAND}" -E env
            "PKG_CONFIG_PATH=${TREXIO_UNINSTALLED_PC_DIR}"
            "${TREXIO_DUNE}" build
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/ocaml/trexio"
    COMMENT "Building the OCaml interface with dune"
    VERBATIM)
  add_dependencies(trexio_ocaml trexio)

  # dune does the installing, so it is called from a script run at install time.
  # It reads DESTDIR from the environment by itself, which is why only the prefix
  # is passed; that prefix is the one configured, not one given to
  # `cmake --install --prefix`.
  file(GENERATE
    OUTPUT "${PROJECT_BINARY_DIR}/trexio-ocaml-install.cmake"
    CONTENT "execute_process(
  COMMAND \"${CMAKE_COMMAND}\" -E env \"PKG_CONFIG_PATH=${TREXIO_UNINSTALLED_PC_DIR}\"
          \"${TREXIO_DUNE}\" install --prefix \"${CMAKE_INSTALL_PREFIX}\"
  WORKING_DIRECTORY \"${PROJECT_SOURCE_DIR}/ocaml/trexio\"
  RESULT_VARIABLE result)
if(NOT result EQUAL 0)
  message(FATAL_ERROR \"dune install failed\")
endif()
")
  install(SCRIPT "${PROJECT_BINARY_DIR}/trexio-ocaml-install.cmake")
endif()

if(TREXIO_RUST)
  find_program(TREXIO_CARGO cargo)
  if(NOT TREXIO_CARGO)
    message(FATAL_ERROR
      "TREXIO_RUST needs cargo, the Rust build system, which was not found.")
  endif()

  # build.rs takes the two directories separately, because a build tree is not an
  # installation prefix. Without them it would download a released TREXIO and
  # test that instead of this one. There is nothing to install: a crate is
  # consumed from source.
  set(TREXIO_CARGO_ENV
      "TREXIO_INCLUDE_DIR=${PROJECT_SOURCE_DIR}/include"
      "TREXIO_LIB_DIR=$<TARGET_FILE_DIR:trexio>"
      "TREXIO_SRC=${PROJECT_SOURCE_DIR}")

  add_custom_target(trexio_rust ALL
    COMMAND "${CMAKE_COMMAND}" -E env ${TREXIO_CARGO_ENV}
            "${TREXIO_CARGO}" build
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/rust/trexio"
    COMMENT "Building the Rust interface with cargo"
    VERBATIM)
  add_dependencies(trexio_rust trexio)

  if(BUILD_TESTING)
    add_test(NAME rust_api
      COMMAND "${CMAKE_COMMAND}" -E env ${TREXIO_CARGO_ENV}
              "${TREXIO_CARGO}" test
      WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/rust/trexio")
    # The tests load the library that was just built.
    set_tests_properties(rust_api PROPERTIES
      ENVIRONMENT "LD_LIBRARY_PATH=$<TARGET_FILE_DIR:trexio>")
  endif()
endif()
