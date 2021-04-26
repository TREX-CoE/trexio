#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([TREXIO], [0.2], [https://github.com/TREX-CoE/trexio/issues])
AC_CONFIG_SRCDIR([src/trexio_text.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_FC
AC_PROG_INSTALL
AC_PROG_LN_S

# Minimal configure without Automake but with HDF5 (default: with HDF5) [optional]:
# ./configure CFLAGS="-g -fPIC" HDF5_PATH=/usr/lib/x86_64-linux-gnu/hdf5/serial [--with-hdf5]
# Minimal configure without Automake and without HDF5:
# ./configure CFLAGS="-g -fPIC" --without-hdf5 [or --with-hdf5=no]

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

if test "x${hdf5}" = xno; then                   
  AC_MSG_WARN([                                     
    ------------------------------------------      
    Configuring with the HDF5 library is               
    recommended to build efficient TREXIO.             
    ------------------------------------------])    
else
  AC_ARG_VAR(HDF5_PATH, Path to the HDF5 directory)
  if test "x${HDF5_PATH}" = x; then                   
    AC_MSG_ERROR([                                     
    ------------------------------------------      
    The path to HDF5 library is required. 
    Maybe you forgot to pass HDF5_PATH="/your/path" to configure script. 
    Stopping...
    ------------------------------------------])    
  fi

  have_hdf5=no					
  have_hdf5_hl=no					

  # The trick with FLAGS_TMP is necessary to check for HDF5 functions 
  CPPFLAGS_TMP="${CPPFLAGS}"
  LDFLAGS_TMP="${LDFLAGS}"

  CPPFLAGS="-I${HDF5_PATH}/include ${CPPFLAGS_TMP}"
  LDFLAGS="-L${HDF5_PATH} ${LDFLAGS_TMP}"

  AC_CHECK_HEADERS([hdf5_hl.h], [], [have_hdf5_hl=no])	
  AC_CHECK_LIB([hdf5_hl], [H5LTfind_dataset], [], [have_hdf5_hl=no])

  AC_CHECK_HEADERS([hdf5.h], [], [have_hdf5=no])
  AC_CHECK_LIB([hdf5], [H5open], [], [have_hdf5=no])

  #CPPFLAGS="${CPPFLAGS_TMP}"
  #LDFLAGS="${LDFLAGS_TMP}"
fi

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
Compiler: '${CC} ${CPPFLAGS} ${CFLAGS} ${LDFLAGS} ${LIBS}'

Package features:
  Compilation with HDF5: ${hdf5}
  HDF5 located at: ${HDF5_PATH}

Now type 'make @<:@<target>@:>@'
where the optional <target> is:
  all 		- build C and Fortran APIs
  check		- check C and Fortran APIs
  clean 	- clean the produced files
--------------------------------------------------"

