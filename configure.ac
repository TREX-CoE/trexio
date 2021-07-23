#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([trexio], [0.3.0], [https://github.com/TREX-CoE/trexio/issues])
AM_INIT_AUTOMAKE([subdir-objects color-tests parallel-tests silent-rules 1.11])
AM_MAINTAINER_MODE()
LT_PREREQ([2.2])
LT_INIT
AC_CONFIG_SRCDIR([Makefile.in])
AC_CONFIG_HEADERS([include/config.h])
AC_CONFIG_MACRO_DIR([m4])

VERSION_MAJOR=`echo ${PACKAGE_VERSION} | cut -d. -f1`
VERSION_MINOR=`echo ${PACKAGE_VERSION} | cut -d. -f2`
VERSION_PATCH=`echo ${PACKAGE_VERSION} | cut -d. -f3 | cut -d- -f1`
AC_DEFINE_UNQUOTED(TREXIO_VERSION_MAJOR, [$VERSION_MAJOR], [major version])
AC_DEFINE_UNQUOTED(TREXIO_VERSION_MINOR, [$VERSION_MINOR], [minor version])
AC_DEFINE_UNQUOTED(TREXIO_VERSION_PATCH, [$VERSION_PATCH], [patch version])
AC_SUBST([VERSION_MAJOR])
AC_SUBST([VERSION_MINOR])
AC_SUBST([VERSION_PATCH])

## Save system information, e.g. user name

UNAME=`echo ${USER}`
AC_DEFINE_UNQUOTED(TREXIO_USER_NAME, ["${UNAME}"], [user name])
AC_SUBST([UNAME])

## -------------------
## Checks for programs 
## -------------------

AC_LANG(C)
AC_PROG_CC

# C99 support
m4_version_prereq([2.70],[], [AC_PROG_CC_C99])
AS_IF([test "$ac_cv_prog_cc_c99" = "no"],
      [AC_MSG_ERROR([The compiler does not support C99])])
AC_PROG_CC_C_O

# Fortran
AC_PROG_FC
AC_FC_FREEFORM
AC_FC_SRCEXT([f90])
AC_PROG_FC_C_O
AC_FC_LIBRARY_LDFLAGS

# pkg-config
PKG_PROG_PKG_CONFIG()
PKG_CFLAGS=""

AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_LN_S
AC_PROG_GREP


## ---------
## Libraries
## ---------

# Checks for basic header files.
AC_CHECK_HEADERS([fcntl.h inttypes.h stdint.h stdbool.h stdlib.h string.h unistd.h])


### HDF5
### ----

# Configure with HDF5 (default: --with-hdf5 using pkg-config) [optional]:
# ./configure [--with-hdf5 or --with-hdf5=yes]

# Configure with user-provided path to HDF5:
# ./configure --with-hdf5=/usr/lib/x86_64-linux-gnu/hdf5/serial

# Configure without HDF5:
# ./configure --without-hdf5 [or --with-hdf5=no]


PKG_HDF5=""
AX_LIB_HDF5()

if test "x${with_hdf5}" = xno; then
  AC_MSG_WARN([
    ------------------------------------------
    Configuring with the HDF5 library is
    recommended to build efficient TREXIO.
    ------------------------------------------])
fi

CFLAGS="${HDF5_CFLAGS} ${CFLAGS}"
CPPFLAGS="${HDF5_CPPFLAGS} ${CPPFLAGS}"
LDFLAGS="${HDF5_LDFLAGS} ${LDFLAGS}"
LIBS="${HDF5_LIBS} ${LIBS}"

# Check if HDF5 if available with pkg-config

PKG_CHECK_MODULES([HDF5], [hdf5 >= 1.8], [
    PKG_HDF5="hdf5"
    ],[
    PKG_HDF5=""
   ])
    PKG_CFLAGS="${PKG_CFLAGS}"

AC_SUBST([PKG_HDF5])
AC_SUBST([PKG_CFLAGS])


# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset mkdir strerror])

AM_CONDITIONAL([TREXIO_DEVEL],[test "x$TREXIO_DEVEL" != x])

if test "x${TREXIO_DEVEL}" != "x"; then

  TREXIO_DEVEL=" -- Developer mode"
  AC_PROG_AWK
  AM_PATH_PYTHON([3.0])

  AC_CHECK_PROGS([EMACS],[emacs26 emacs],[no])
  if test x${EMACS} == xno ; then
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

fi

## Libm
## ----

AC_SEARCH_LIBS([sqrt], [m], [], AC_MSG_ERROR([The libm library is required]))
AC_CHECK_HEADERS([math.h])

### pthread
### -------

AC_SEARCH_LIBS([pthread_create], [pthread], [], AC_MSG_ERROR([The pthread library is required]))
AC_CHECK_HEADERS([pthread.h])


AC_CONFIG_FILES([Makefile
                 pkgconfig/trexio.pc])
AC_OUTPUT

echo \
"-------------------------------------------------

${PACKAGE_NAME} Version ${PACKAGE_VERSION} ${TREXIO_DEVEL}

Prefix ........:  ${prefix}
CC ............:  ${CC}
CPPFLAGS ......:  ${CPPFLAGS}
CFLAGS ........:  ${CFLAGS}
FC ............:  ${FC}
FCLAGS ........:  ${FCFLAGS}
LDFLAGS .......:  ${LDFLAGS}
LIBS ..........:  ${LIBS}

Package features:
  Compilation with HDF5 ..:  ${with_hdf5}
  HDF5 version ...........:  ${HDF5_VERSION}

Now type 'make @<:@<target>@:>@'
where the optional <target> is:
  all           - build C library and Fortran binding
  check	        - run unit tests
  install       - install the library 
--------------------------------------------------"

