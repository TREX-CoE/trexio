#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([trexio],[2.5.2],[https://github.com/TREX-CoE/trexio/issues])

AC_CONFIG_SRCDIR([Makefile.in])
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-config])

AM_INIT_AUTOMAKE([subdir-objects color-tests parallel-tests silent-rules 1.11])
AM_MAINTAINER_MODE()
AM_PROG_AR

LT_PREREQ([2.2])
LT_INIT

# Activate developer mode if a dummy file is present (true when cloning the git repository).
# Otherwise, it is the source distribution and the developer mode should not be activated.
TEST_IFEXISTS=".devel"
AS_IF([test -f $TEST_IFEXISTS],
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
AM_CONDITIONAL([HAVE_FORTRAN],[test "$ok" = "yes"])

AC_LANG(C)
AC_PROG_CC

# C99 support
m4_version_prereq([2.70],[], [AC_PROG_CC_C99])
AS_IF([test "$ac_cv_prog_cc_c99" = "no"],
      [AC_MSG_ERROR([The compiler does not support C99])])
AC_PROG_CC_C_O
AM_PROG_CC_C_O


# pkg-config
PKG_PROG_PKG_CONFIG()

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
  TREXIO_DEVEL=" -- Developer mode"
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
  AM_PATH_PYTHON([3.0])

  AX_PKG_SWIG(4.0.0, [], AC_MSG_WARN([SWIG is required to build Python API.]) )
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


AC_CONFIG_FILES([Makefile
                 pkgconfig/trexio.pc])
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

Now type 'make @<:@<target>@:>@'
where the optional <target> is:
  all           - build C library and Fortran binding
  check         - run unit tests
  install       - install the library
--------------------------------------------------"])
