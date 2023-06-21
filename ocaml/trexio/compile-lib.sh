#!/bin/sh

PREFIX=$1
TASK=$2
PKGCONFIG_COMMAND="pkg-config --libs --cflags trexio"

INSTALLED="no"

# Try with system defaults
if cc test.c >/dev/null 2>&1 ; then
  exit
fi

# Try with pkg-config
if eval $PKGCONFIG_COMMAND >/dev/null 2>&1; then
    exit
fi

# Compile C library
set -e
if test "$TASK" = "build" ; then
  tar -zxf trexio-*.tar.gz
  cd trexio-*
  ./configure --prefix=${PREFIX}
  make -j 4
  cd ../
elif test "$TASK" = "install" ; then
  cd trexio-*
  make install
  rm -rf trexio-*/
fi
