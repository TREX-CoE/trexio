#!/bin/sh

PREFIX=$1
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
cd vendor
tar -zxf trexio-*.tar.gz
cd trexio-*
./configure --prefix=${PREFIX}
$(MAKE) install && \
rm -rf trexio-*/

