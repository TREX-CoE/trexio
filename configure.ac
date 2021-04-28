#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([TREXIO], [0.2], [https://github.com/TREX-CoE/trexio/issues])
AC_CONFIG_SRCDIR([src/trexio_text.h])
AC_CONFIG_HEADERS([config.h])
PKG_PROG_PKG_CONFIG()
# Checks for programs.
AC_PROG_CC
AC_PROG_FC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_CC_C99

# Configure with HDF5 (default: --with-hdf5 using pkg-config) [optional]:
# ./configure [--with-hdf5 or --with-hdf5=yes]
# Configure with user-provided path to HDF5:
# ./configure --with-hdf5=/usr/lib/x86_64-linux-gnu/hdf5/serial
# Configure without HDF5:
# ./configure --without-hdf5 [or --with-hdf5=no]

# Checks for basic libraries.
AC_CHECK_LIB([m], [main])
AC_CHECK_LIB([z], [main])
# Checks for basic header files.
AC_CHECK_HEADERS([fcntl.h stdint.h stdlib.h string.h unistd.h])

# Search for pthread
have_pthreads=no
AC_SEARCH_LIBS([pthread_create], [pthread], [have_pthreads=yes])

if test "x${have_pthreads}" = xyes; then
   AC_CHECK_HEADERS([pthread.h], [], [have_pthreads=no])
fi

if test "x${have_pthreads}" = xno; then
AC_MSG_ERROR([
	------------------------------------------
	The pthread library and header file
	required to build TREXIO. Stopping...
	Check 'config.log' for more information.
	------------------------------------------])
fi

AC_ARG_WITH([hdf5],
	    AS_HELP_STRING([--with-hdf5], 
			   [Include HDF5 functionality @<:@default: yes@:>@])],
	     [hdf5=${withval}],
	     [hdf5=yes])

have_hdf5=no
have_hdf5_hl=no
if test "x${hdf5}" = xno; then                   
  AC_MSG_WARN([                                     
    ------------------------------------------      
    Configuring with the HDF5 library is               
    recommended to build efficient TREXIO.             
    ------------------------------------------])    
elif test "x${hdf5}" = xyes; then

  # Check if HDF5 is already configured (e.g. after calling `module load hdf5-<version>`)
  AC_CHECK_HEADERS([hdf5_hl.h])
  AC_CHECK_LIB([hdf5_hl], [H5LTfind_dataset], [], [have_hdf5_hl=no])

  AC_CHECK_HEADERS([hdf5.h])
  AC_CHECK_LIB([hdf5], [H5open], [], [have_hdf5=no])

  # If HDF5 is not configured, try using pkg-config
  if test "x${have_hdf5}" = xno; then
    PKG_CHECK_MODULES([HDF5], [hdf5 >= 1.8])
    CFLAGS="${HDF5_CFLAGS} ${CFLAGS}"
    LIBS="${HDF5_LIBS} -lhdf5_hl ${LIBS}"
  fi

else

  if test "x${hdf5}" = x; then
    AC_MSG_ERROR([                                     
    ------------------------------------------
    The path to HDF5 library is required.
    Maybe you forgot to pass --with-hdf5="/your/path/" to configure script.
    Stopping...
    ------------------------------------------])    
  fi

  CPPFLAGS="-I${hdf5}/include ${CPPFLAGS}"
  LDFLAGS="-L${hdf5} ${LDFLAGS}"

  AC_CHECK_HEADERS([hdf5_hl.h], [], [have_hdf5_hl=no])	
  AC_CHECK_LIB([hdf5_hl], [H5LTfind_dataset], [], [have_hdf5_hl=no])

  AC_CHECK_HEADERS([hdf5.h], [], [have_hdf5=no])
  AC_CHECK_LIB([hdf5], [H5open], [], [have_hdf5=no])

fi

# add -fPIC if not present in CFLAGS, necessary to compile TREXIO
# TODO: replace with AM_CFLAGS for appropriate targer once Automake is introduced
case "${CFLAGS}" in
    *-fPIC*)
    ;;
    *)
    AC_MSG_WARN([
    ------------------------------------------      
    Adding -fPIC option to CFLAGS.
    This is necessary to build TREXIO.
    ------------------------------------------])
    CFLAGS="${CFLAGS} -fPIC"
    ;;
esac

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset mkdir strerror])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT

echo \
"-------------------------------------------------

${PACKAGE_NAME} Version ${PACKAGE_VERSION}

Prefix: '${prefix}'.

CC:           ${CC}
CPPFLAGS:     ${CPPFLAGS}
CFLAGS:	      ${CFLAGS}
FC:           ${FC}
FFLAGS:	      ${FCFLAGS}
LDFLAGS:      ${LDFLAGS}
LIBS:         ${LIBS}

Package features:
  Compilation with HDF5: ${hdf5}

Now type 'make @<:@<target>@:>@'
where the optional <target> is:
  all           - build C and Fortran APIs
  check	        - check C and Fortran APIs
  clean         - clean the produced files
--------------------------------------------------"

