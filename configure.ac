#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([TREXIO], [0.2], [https://github.com/TREX-CoE/trexio/issues])
AC_CONFIG_SRCDIR([src/trexio_text.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
_DEBUG_START_
AC_CHECK_PROG(H5CC_EXISTS, h5cc, TRUE, FALSE)
_DEBUG_END_

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lhdf5':
AC_CHECK_LIB([hdf5], [H5_OPEN])
# FIXME: Replace `main' with a function in `-lhdf5_hl':
AC_CHECK_LIB([hdf5_hl], [H5LT_FIND_DATASET])
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])
# FIXME: Replace `main' with a function in `-lz':
AC_CHECK_LIB([z], [main])
# search for pthread
AC_SEARCH_LIBS([pthread_create], [pthread])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdint.h stdlib.h string.h unistd.h])
AC_CHECK_HEADERS([pthread.h])
# Checks for HDF5-related header files
AC_CHECK_HEADERS([hdf5.h hdf5_hl.h])

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
