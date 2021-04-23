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


# Checks for libraries.
# FIXME: Replace `main' with a function in `-lhdf5':
#AC_CHECK_LIB([hdf5], [H5_OPEN])
# FIXME: Replace `main' with a function in `-lhdf5_hl':
#AC_CHECK_LIB([hdf5_hl], [H5LT_FIND_DATASET])
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])
# FIXME: Replace `main' with a function in `-lz':
AC_CHECK_LIB([z], [main])


AC_ARG_WITH([hdf5],
	    AS_HELP_STRING([--with-hdf5], 
		[Include HDF5 functionality @<:@default: yes@:>@])],
	     [hdf5=${withval}],
	     [hdf5=yes])

AS_IF([test "x$with_hdf5" != "xno"], [
  AC_ARG_VAR(hdf5_path, Path to the HDF5 directory)	\
  AC_CHECK_PROG(HAVE_H5CC, h5cc, TRUE, FALSE)		
])

if test "x${hdf5}" = xyes; then
  have_hdf5=no								
  AC_SEARCH_LIBS([H5_OPEN], [hdf5], [have_hdf5=yes])  	
  if test "x${have_hdf5}" = xyes; then               	
     AC_CHECK_HEADERS([hdf5.h], [], [have_hdf5=no])	
  fi                                                    
  if test "x${have_hdf5}" = xno; then                   
    AC_MSG_WARN([                                     
      ------------------------------------------      
      The HDF5 library and header file                
      required to build efficient TREXIO.             
      ------------------------------------------])    
  fi                                                 
fi


# search for pthread
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

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdint.h stdlib.h string.h unistd.h])

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
Compiler: '${CC} ${CFLAGS} ${CPPFLAGS}'

Package features:
  Async Execution: ${async_exec}

Now type 'make @<:@<target>@:>@'
where the optional <target> is:
  all 		- build
  check		- check
  clean 	- clean 
--------------------------------------------------"

