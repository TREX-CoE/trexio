#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([trexio],[2.6.1],[https://github.com/TREX-CoE/trexio/issues])

AC_CONFIG_SRCDIR([Makefile.in])
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-config])

AM_INIT_AUTOMAKE([foreign subdir-objects color-tests parallel-tests silent-rules 1.11])
AM_MAINTAINER_MODE()
AM_PROG_AR

LT_PREREQ([2.2])
LT_INIT

# Activate developer mode if a dummy file is present (true when cloning the git repository).
# Otherwise, it is the source distribution and the developer mode should not be activated.
# The marker is looked up in $srcdir so that out-of-source (object directory)
# builds detect it correctly instead of silently dropping to non-developer mode.
TEST_IFEXISTS="$srcdir/.devel"
AS_IF([test -f "$TEST_IFEXISTS"],
        [enable_maintainer_mode="yes"]
)

VERSION_MAJOR=`echo ${PACKAGE_VERSION} | cut -d. -f1`
VERSION_MINOR=`echo ${PACKAGE_VERSION} | cut -d. -f2`
VERSION_PATCH=`echo ${PACKAGE_VERSION} | cut -d. -f3 | cut -d- -f1`
AC_DEFINE_UNQUOTED(VERSION_MAJOR, [$VERSION_MAJOR], [major version])
AC_DEFINE_UNQUOTED(VERSION_MINOR, [$VERSION_MINOR], [minor version])
AC_DEFINE_UNQUOTED(VERSION_PATCH, [$VERSION_PATCH], [patch version])


## Save system information, e.g. user name

UNAME=`echo ${USER}`
AC_DEFINE_UNQUOTED(TREXIO_USER_NAME, ["${UNAME}"], [user name])
AC_SUBST([UNAME])

## -------------------
## Checks for programs
## -------------------

# Fortran API [default: --with-fortran], do not disable in the dev mode
AC_PROG_FC

AC_ARG_WITH(fortran, [AS_HELP_STRING([--without-fortran],[do not test and install the Fortran API])], ok=$withval, ok=yes)
AS_IF([test "$ok" = "yes"],[
  AC_FC_FREEFORM
  AC_FC_SRCEXT([f90])
  AC_PROG_FC_C_O
  AC_FC_LIBRARY_LDFLAGS

  # Specific options required with some compilers
  AS_CASE([$FC],
  [*gfortran*], [FCFLAGS="$FCFLAGS -fPIC"],
  [*flang*], [FCFLAGS="$FCFLAGS -fPIC"],
  [*ifort*], [FCFLAGS="$FCFLAGS -fPIC"],
  [])

])
with_fortran=$ok
AM_CONDITIONAL([HAVE_FORTRAN],[test "$ok" = "yes"])
AS_IF([test "$ok" = "yes"],
      [TREXIO_CMAKE_WITH_FORTRAN=ON], [TREXIO_CMAKE_WITH_FORTRAN=OFF])

# Python API [default: --disable-python]
AC_ARG_ENABLE(python, [AS_HELP_STRING([--enable-python],[build and install the Python API])],
              [enable_python=$enableval], [enable_python=no])

# OCaml API [default: --disable-ocaml]
AC_ARG_ENABLE(ocaml, [AS_HELP_STRING([--enable-ocaml],[build and install the OCaml API])],
              [enable_ocaml=$enableval], [enable_ocaml=no])

# Rust API [default: --disable-rust]
AC_ARG_ENABLE(rust, [AS_HELP_STRING([--enable-rust],[build and test the Rust API])],
              [enable_rust=$enableval], [enable_rust=no])

AC_LANG(C)
AC_PROG_CC

# C99 support
m4_version_prereq([2.70],[], [AC_PROG_CC_C99])
AS_IF([test "$ac_cv_prog_cc_c99" = "no"],
      [AC_MSG_ERROR([The compiler does not support C99])])
AC_PROG_CC_C_O
AM_PROG_CC_C_O



AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_GREP

AS_CASE([$CC],
  [*gcc*], [CFLAGS="$CFLAGS -fPIC"],
  [*clang*], [CFLAGS="$CFLAGS -fPIC"],
  [*icc*], [CFLAGS="$CFLAGS -fPIC"],
  [])

# Check if `cp -r -n` works, otherwise use `cp -r`
AC_CHECK_PROGS(CP_PROG, [cp])

AC_MSG_CHECKING([for cp -r -n option])
AC_RUN_IFELSE(
    [AC_LANG_PROGRAM([
#include <unistd.h>
],[
execl("/bin/sh", "sh", "-c", "mkdir tmpdir1 && \
touch tmpdir1/test_file && \
$CP_PROG -r -n tmpdir1 tmpdir2 && \
exec ls tmpdir2/test_file > /dev/null", NULL);
])],
[ rm -rf tmpdir1 tmpdir2
  CP_COMMAND="\"$CP_PROG\", \"-r\", \"-n\""
  AC_MSG_RESULT([yes])],
[ rm -rf tmpdir1 tmpdir2
  CP_COMMAND="\"$CP_PROG\", \"-r\""
  AC_MSG_RESULT([no])],
[ rm -rf tmpdir1 tmpdir2
  CP_COMMAND="\"$CP_PROG\", \"-r\""
  AC_MSG_RESULT([no])]
)
AC_DEFINE_UNQUOTED([CP_COMMAND], [$CP_COMMAND], [Command used for trexio_cp])


## ---------
## Libraries
## ---------

# Checks for basic header files.
AC_CHECK_HEADERS([fcntl.h inttypes.h stdint.h stdbool.h stdlib.h string.h unistd.h sys/types.h sys/wait.h ])


### HDF5
### ----

# Initialize variables
PKG_HDF5=""
HDF5_LIBS=""
HDF5_LDFLAGS=""
HDF5_CFLAGS=""
HDF5_CPPFLAGS=""

AC_ARG_WITH([hdf5],
  AS_HELP_STRING([--with-hdf5=PATH], [Use HDF5 (yes|no|/custom/path)]),
  [],
  [with_hdf5=yes])

AS_IF([test "x$with_hdf5" = "xno"],
  [AC_MSG_NOTICE([HDF5 support disabled by user.])],
  [AS_IF([test "x$with_hdf5" = "xyes"],
    [
      # pkg-config
      PKG_PROG_PKG_CONFIG()

      # Try pkg-config first
      PKG_CHECK_EXISTS([hdf5 >= 1.8],
        [
          PKG_CHECK_MODULES([HDF5], [hdf5 >= 1.8])
          PKG_HDF5="hdf5"
        ],
        [
          # Fallback: Try to find h5cc
          AC_PATH_PROG([H5CC], [h5cc], [not_found])
          AS_IF([test "$H5CC" != "not_found"],
            [
              HDF5_LIBS="-lhdf5"
              AC_REQUIRE([AC_PROG_SED])
              AC_REQUIRE([AC_PROG_AWK])
              AC_REQUIRE([AC_PROG_GREP])
              # Look for "HDF5 Version: X.Y.Z"
              HDF5_VERSION=$(eval $H5CC -showconfig | $GREP 'HDF5 Version:' \
                  | $AWK '{print $[]3}')

              # A ideal situation would be where everything we needed was
              # in the AM_* variables. However most systems are not like this
              # and seem to have the values in the non-AM variables.
              #
              # We try the following to find the flags:
              # (1) Look for "NAME:" tags
              # (2) Look for "H5_NAME:" tags
              # (3) Look for "AM_NAME:" tags
              #
              HDF5_tmp_flags=$(eval $H5CC -showconfig \
                  | $GREP 'FLAGS\|Extra libraries:' \
                  | $AWK -F: '{printf("%s "), $[]2}' )

              dnl Find the installation directory and append include/
              HDF5_tmp_inst=$(eval $H5CC -showconfig \
                  | $GREP 'Installation point:' \
                  | $AWK '{print $[]NF}' )

              dnl Add this to the CPPFLAGS
              HDF5_CPPFLAGS="-I${HDF5_tmp_inst}/include"

              HDF5_SHOW=$(eval $H5CC -show)

              dnl Now sort the flags out based upon their prefixes
              for arg in $HDF5_SHOW $HDF5_tmp_flags ; do
                case "$arg" in
                  -I*) echo $HDF5_CPPFLAGS | $GREP -e "$arg" 2>&1 >/dev/null \
                        || HDF5_CPPFLAGS="$HDF5_CPPFLAGS $arg"
                    ;;
                  -L*) echo $HDF5_LDFLAGS | $GREP -e "$arg" 2>&1 >/dev/null \
                        || HDF5_LDFLAGS="$HDF5_LDFLAGS $arg"
                    ;;
                  -l*) echo $HDF5_LIBS | $GREP -e "$arg" 2>&1 >/dev/null \
                        || HDF5_LIBS="$HDF5_LIBS $arg"
                    ;;
                esac
              done
            ],
            [AC_MSG_ERROR([HDF5 not found: install pkg-config .pc file or h5cc, or use --with-hdf5=PATH])]
          )
        ]
      )
    ],
    [
      # User-provided path
      HDF5_PATH="$with_hdf5"
      HDF5_LDFLAGS="-L$HDF5_PATH/lib"
      HDF5_CPPFLAGS="-I$HDF5_PATH/include"
      HDF5_LIBS="-lhdf5"
    ]
  )

  AC_DEFINE([HAVE_HDF5], 1, [Define to 1 if HDF5 is available])
])
AM_CONDITIONAL([HAVE_HDF5], [test "x$with_hdf5" != "xno"])

# Export variables to the Makefiles
AC_SUBST([PKG_HDF5])
AC_SUBST([HDF5_LDFLAGS])
AC_SUBST([HDF5_LIBS])
AC_SUBST([HDF5_CFLAGS])
AC_SUBST([HDF5_CPPFLAGS])

# Append flags to global variables
CPPFLAGS="${HDF5_CPPFLAGS} ${CPPFLAGS}"
CFLAGS="${HDF5_CFLAGS} ${CFLAGS}"
LDFLAGS="${HDF5_LDFLAGS} ${LDFLAGS}"
LIBS="${HDF5_LIBS} ${LIBS}"

# Final link and header check (only if enabled)
AS_IF([test "x$with_hdf5" != "xno"],
  [
    OLD_LIBS="$LIBS"
    AC_CHECK_LIB([hdf5], [H5Fcreate],
      [],
      [AC_MSG_ERROR([HDF5 library (-lhdf5) not found or link failed. Provide --with-hdf5=PATH])]
    )
    AC_CHECK_HEADER([hdf5.h],
      [],
      [AC_MSG_ERROR([hdf5.h not found. Provide --with-hdf5=PATH or check CPPFLAGS])]
    )
    LIBS="$OLD_LIBS"
  ]
)
####

# The block below should only execute if the ax_lib_hdf5.m4 macro failed to find HDF5.
# It is only needed to manually build Python API because setup.py depends on HDF5.

#if test x"$HDF5_LDFLAGS" = "x" || x"$HDF5_CFLAGS" = "x"; then
#  AC_SUBST([HDF5_CFLAGS])
#  AC_SUBST([HDF5_LDFLAGS])
#fi

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_PID_T
AC_C_CONST
AC_C_INLINE

# Checks for library functions.
# AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset mkdir strerror])

if test "x$enable_maintainer_mode" = "xyes"; then
  TREXIO_DEVEL=" -- Maintainer mode"
else
  TREXIO_DEVEL=""
fi


AC_ARG_WITH(efence, [AS_HELP_STRING([--with-efence],[use ElectricFence library])], ok=$withval, ok=no)
if test "$ok" = "yes"; then
        AC_CHECK_LIB([efence], [malloc])
        ARGS="${ARGS} efence"
fi

AC_ARG_ENABLE(malloc-trace, [AS_HELP_STRING([--enable-malloc-trace],[use debug malloc/free])], ok=$enableval, ok=no)
if test "$ok" = "yes"; then
        AC_DEFINE(MALLOC_TRACE,"malloc_trace.dat",[Define to use debugging malloc/free])
        ARGS="${ARGS} malloc-trace"
fi

AC_ARG_ENABLE(prof, [AS_HELP_STRING([--enable-prof],[compile for profiling])], ok=$enableval, ok=no)
if test "$ok" = "yes"; then
        CFLAGS="${CFLAGS} -pg"
        AC_DEFINE(ENABLE_PROF,1,[Define when using the profiler tool])
        ARGS="${ARGS} prof"
fi


AM_CONDITIONAL([TREXIO_DEVEL],[test "x$TREXIO_DEVEL" != x])

if test "x${TREXIO_DEVEL}" != "x"; then

  AC_PROG_AWK

  AX_PKG_SWIG(4.0.0, [], AC_MSG_WARN([SWIG is required to build Python API.]) )

  # On Windows, swig -swiglib prints two directories, and AX_PKG_SWIG passes all
  # of its output through, so SWIG_LIB ends up holding a newline and breaks the
  # Makefile it is substituted into. Keep the last line, which is the directory
  # that actually exists.
  SWIG_LIB=`printf '%s\n' "$SWIG_LIB" | tail -n 1`
  # The macro below performs Python benchmarks, but overlapping with AM_PATH_PYTHON
  #AX_SWIG_PYTHON

  AC_CHECK_PROGS([EMACS],[emacs26 emacs],[no])
  if test x${EMACS} = "xno" ; then
    AC_MSG_ERROR([
    --------------------------------------
    Error: Emacs is required for org-mode.
    --------------------------------------
    ])
  fi

  AC_CHECK_PROGS([HAS_CPPCHECK],[cppcheck],[no])
  if test x${HAS_CPPCHECK} != xno ; then
        HAS_CPPCHECK=1
  fi

  GIT_HASH=`git log | head -1 | cut -d ' ' -f 2 | tee ${srcdir}/.git_hash`

else

  GIT_HASH=`cat ${srcdir}/.git_hash`

fi
AC_DEFINE_UNQUOTED(GIT_HASH, ["${GIT_HASH}"], [Git SHA1 Hash])

## Python API
## ----------

# A Python interpreter is needed both to build the Python API and, in maintainer
# mode, to run the source code generator.
trexio_swig_regen=no
SWIG_WORDSIZE_FLAGS=""

AS_IF([test "x$enable_python" = "xyes" || test "x${TREXIO_DEVEL}" != "x"],
      [AM_PATH_PYTHON([3.6],[],[:])])

AS_IF([test "x$enable_python" = "xyes"], [

  AS_IF([test "x$PYTHON" = "x" || test "x$PYTHON" = "x:"],
        [AC_MSG_ERROR([--enable-python requires a Python 3 interpreter.])])

  # Python imports an extension module by the suffixes its own machinery lists,
  # which is not what the platform calls a shared library: .so here, .pyd on
  # Windows, where Libtool builds a .dll. The generic suffix is the last one, and
  # the plain name keeps this in step with the CMake build, which asks FindPython
  # for the same thing and adds no ABI tag either.
  PYTHON_EXT_SUFFIX=`$PYTHON -c "import importlib.machinery as m; print(m.EXTENSION_SUFFIXES[[-1]])" 2>/dev/null`
  AS_IF([test "x$PYTHON_EXT_SUFFIX" = "x"], [PYTHON_EXT_SUFFIX=.so])
  AC_MSG_CHECKING([the suffix of Python extension modules])
  AC_MSG_RESULT([$PYTHON_EXT_SUFFIX])

  # The extension module is compiled here rather than by setup.py, so the Python
  # and NumPy headers have to be available.
  PYTHON_INCLUDE=`$PYTHON -c "import sysconfig; print(sysconfig.get_path('include'))" 2>/dev/null`
  NUMPY_INCLUDE=`$PYTHON -c "import numpy; print(numpy.get_include())" 2>/dev/null`
  PYTHON_CPPFLAGS="-I$PYTHON_INCLUDE"
  NUMPY_CPPFLAGS="-I$NUMPY_INCLUDE"

  OLD_CPPFLAGS="$CPPFLAGS"
  CPPFLAGS="$CPPFLAGS $PYTHON_CPPFLAGS"
  AC_CHECK_HEADER([Python.h],[],
    [AC_MSG_ERROR([Python.h not found. Install the Python development files (python3-devel or python3-dev).])])
  CPPFLAGS="$CPPFLAGS $NUMPY_CPPFLAGS"
  AC_CHECK_HEADER([numpy/arrayobject.h],[],
    [AC_MSG_ERROR([The NumPy headers were not found. Install numpy for $PYTHON.])],
    [#include <Python.h>])
  CPPFLAGS="$OLD_CPPFLAGS"

  # The SWIG wrapper is shipped in the distribution; SWIG itself is only needed
  # in maintainer mode, where the wrapper is regenerated from pytrexio.i.
  AS_IF([test "x${TREXIO_DEVEL}" = "x" && test ! -f "$srcdir/src/pytrexio_wrap.c"],
        [AC_MSG_ERROR([src/pytrexio_wrap.c is missing from this distribution.])])

  # SWIGWORDSIZE64 makes SWIG map int64_t onto long, and without it onto long
  # long, so the define has to follow the target rather than be hardcoded. What
  # decides is how int64_t is spelled, not how wide long is: it is long on LP64
  # Linux, but long long on ILP32 targets (i686), on LLP64 ones (Windows) and
  # also on macOS, which is LP64 yet still spells int64_t long long. Get at it
  # with two declarations of one function, which conflict unless the two types
  # are the same.
  AC_CACHE_CHECK([whether int64_t is long], [trexio_cv_int64_t_is_long],
    [AC_COMPILE_IFELSE(
      [AC_LANG_PROGRAM([[#include <stdint.h>
void trexio_check_int64_t(long *);
void trexio_check_int64_t(int64_t *);]], [])],
      [trexio_cv_int64_t_is_long=yes],
      [trexio_cv_int64_t_is_long=no])])
  AS_IF([test "x$trexio_cv_int64_t_is_long" = "xyes"],
        [SWIG_WORDSIZE_FLAGS="-DSWIGWORDSIZE64"],
        [SWIG_WORDSIZE_FLAGS=""])

  # A generated wrapper records which of the two it was made for, because SWIG
  # emits its 32-bit guard only when SWIGWORDSIZE64 was defined. A shipped wrapper
  # that does not match this target is at best miscompiled and at worst rejected
  # outright, so regenerate it into the build directory and leave the distributed
  # copy alone.
  AC_MSG_CHECKING([whether the SWIG wrapper matches the type of int64_t])
  AS_IF([test -f "$srcdir/src/pytrexio_wrap.c"],
    [AS_IF([grep SWIG_NO_WORDSIZE64_CHECK "$srcdir/src/pytrexio_wrap.c" >/dev/null 2>&1],
           [trexio_wrapper_int64_t_is_long=yes], [trexio_wrapper_int64_t_is_long=no])
     AS_IF([test "x$trexio_wrapper_int64_t_is_long" = "x$trexio_cv_int64_t_is_long"],
           [AC_MSG_RESULT([yes])],
           [AC_MSG_RESULT([no, it will be regenerated])
            trexio_swig_regen=yes])],
    [AC_MSG_RESULT([no wrapper present, it is generated from pytrexio.i])])

  AS_IF([test "x$trexio_swig_regen" = "xyes"],
    [AC_CHECK_PROGS([SWIG],[swig],[no])
     AS_IF([test "x$SWIG" = "xno"],
       [AC_MSG_ERROR([
    ------------------------------------------------------------------
    The Python API has to be regenerated for this target: the wrapper
    that comes with the distribution maps int64_t onto a different
    type than this target uses. Install SWIG (>= 4.0), or configure
    with --disable-python.
    ------------------------------------------------------------------])])])
])

AC_SUBST([PYTHON_CPPFLAGS])
AC_SUBST([NUMPY_CPPFLAGS])
AC_SUBST([SWIG_WORDSIZE_FLAGS])
AC_SUBST([PYTHON_EXT_SUFFIX])

# The OCaml binding is built by dune, which finds the library with pkg-config: in
# a build tree that is the uninstalled trexio.pc generated below. Its stubs are
# generated from trex.json by a Python script, so Python is needed as well.
AS_IF([test "x$enable_ocaml" = "xyes"], [
  AC_CHECK_PROGS([DUNE],[dune],[no])
  AS_IF([test "x$DUNE" = "xno"],
        [AC_MSG_ERROR([--enable-ocaml requires dune (the OCaml build system).])])
  AS_IF([test "x$PKG_CONFIG" = "x"],
        [AC_MSG_ERROR([--enable-ocaml requires pkg-config, which dune uses to
locate the library.])])
  AS_IF([test "x$PYTHON" = "x" || test "x$PYTHON" = "x:"],
        [AC_MSG_ERROR([--enable-ocaml requires a Python 3 interpreter to generate
the OCaml stubs from trex.json.])])
])

# The Rust binding is built by cargo. There is nothing to install: a crate is
# consumed from source, so this only builds it and runs its tests.
AS_IF([test "x$enable_rust" = "xyes"], [
  AC_CHECK_PROGS([CARGO],[cargo],[no])
  AS_IF([test "x$CARGO" = "xno"],
        [AC_MSG_ERROR([--enable-rust requires cargo (the Rust build system).])])
])
AM_CONDITIONAL([HAVE_PYTHON],[test "x$enable_python" = "xyes"])
AM_CONDITIONAL([HAVE_OCAML],[test "x$enable_ocaml" = "xyes"])
AM_CONDITIONAL([HAVE_RUST],[test "x$enable_rust" = "xyes"])
AM_CONDITIONAL([REGENERATE_SWIG],[test "x$trexio_swig_regen" = "xyes"])

## Libm
## ----

AC_SEARCH_LIBS([sqrt], [m], [], AC_MSG_ERROR([The libm library is required]))
AC_CHECK_HEADERS([math.h])

### pthread
### -------

AC_SEARCH_LIBS([pthread_create], [pthread], [], AC_MSG_ERROR([The pthread library is required]))
AC_CHECK_HEADERS([pthread.h])

# Debug flags

AC_ARG_ENABLE(debug, [AS_HELP_STRING([--enable-debug],[enable gcc and gfortran debug flags])], ok=$enableval, ok=no)
if test "$ok" = "yes"; then
  CFLAGS="${CFLAGS} -Wall -Wextra -Wpedantic -Werror -Wshadow -Wformat -Wfloat-equal -Wconversion -Wcast-align -Wnull-dereference -Wstrict-aliasing -Winline -Wmissing-prototypes -Wunreachable-code -fstack-protector-strong -fdiagnostics-show-option -Wfloat-conversion -Wcast-qual -fno-inline -fno-omit-frame-pointer -Wno-sign-conversion -Wno-cast-qual -Wno-float-conversion" # -Wno-unused-variable"
  FCFLAGS="${FCFLAGS} -g -fcheck=all -Waliasing -Wampersand -Wconversion -Wsurprising -Wintrinsics-std -Wno-tabs -Wintrinsic-shadow -Wline-truncation -Wreal-q-constant -Wuninitialized  -fbacktrace -ffpe-trap=zero,overflow -finit-real=nan"
fi


AC_ARG_ENABLE(sanitizer, [AS_HELP_STRING([--enable-sanitizer],[enable sanitizer debug flags])], ok=$enableval, ok=no)
if test "$ok" = "yes"; then
  CFLAGS="${CFLAGS} -fsanitize=address -fsanitize=undefined -fsanitize=leak -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=bounds -fsanitize=bounds-strict"
  FCFLAGS="${FCFLAGS} -fsanitize=address -fsanitize=undefined -fsanitize=leak -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=bounds -fsanitize=bounds-strict"
fi


# Values interpolated into the CMake package configuration file, which the
# Autotools build installs so that find_package(trexio) works for consumers of
# an Autotools installation too.
AS_IF([test "x$with_hdf5" != "xno"],
      [TREXIO_CMAKE_WITH_HDF5=ON], [TREXIO_CMAKE_WITH_HDF5=OFF])
AC_SUBST([TREXIO_CMAKE_WITH_HDF5])
AC_SUBST([TREXIO_CMAKE_WITH_FORTRAN])

AC_CONFIG_FILES([Makefile
                 pkgconfig/trexio.pc
                 pkgconfig/uninstalled/trexio.pc:pkgconfig/trexio-uninstalled.pc.in
                 cmake/trexio-config.cmake:cmake/autotools-trexio-config.cmake.in
                 cmake/trexio-config-version.cmake:cmake/autotools-trexio-config-version.cmake.in])
AC_OUTPUT

AS_ECHO([ \
"-------------------------------------------------

${PACKAGE_NAME} Version ${PACKAGE_VERSION} ${GIT_HASH} ${TREXIO_DEVEL}

Prefix ........:  ${prefix}
CC ............:  ${CC}
CPPFLAGS ......:  ${CPPFLAGS}
CFLAGS ........:  ${CFLAGS}
FC ............:  ${FC}
FCFLAGS .......:  ${FCFLAGS}
LDFLAGS .......:  ${LDFLAGS}
LIBS ..........:  ${LIBS}

Package features:
  Compilation with HDF5 ..:  ${with_hdf5}
  HDF5 version ...........:  ${HDF5_VERSION}
  Fortran API ............:  ${with_fortran}
  Python API .............:  ${enable_python}
  OCaml API ..............:  ${enable_ocaml}
  Rust API ...............:  ${enable_rust}

Now type 'make @<:@<target>@:>@'
where the optional <target> is:
  all           - build C library and the enabled bindings
  check         - run unit tests
  install       - install the library
--------------------------------------------------"])
