#!/bin/bash

# We want the script to crash on the 1st error:
set -e

# Check that script is executed from tools directory
if [[ $(basename $PWD) != "tools" ]] ; then
  echo "This script should run in the tools directory"
  exit -1
fi

DO_HDF5=0
if [[ -z ${1} ]] && [[ "${1}" == "--without-hdf5" ]] ; then
  echo "Compiling Python API without the HDF5 back end."
  DO_HDF5=1
else
  echo "Compiling Python API with the HDF5 back end."
fi

TREXIO_ROOT=$(dirname "${PWD}../")

#   First define readonly global variables.
readonly SRC=${TREXIO_ROOT}/src
readonly INCLUDIR=${TREXIO_ROOT}/include
readonly TOOLS=${TREXIO_ROOT}/tools
readonly PYDIR=${TREXIO_ROOT}/python
readonly PYTREXIODIR=${PYDIR}/pytrexio
readonly PYDIR_TREXIO_H=${PYDIR}/src/trexio.h

# Create src and trexio directories in the python folder if not yet done
mkdir -p ${PYDIR}/src
mkdir -p ${PYTREXIODIR}

# Copy all the source code and header files in the corresponding python directory
cp ${SRC}/pytrexio.py ${PYTREXIODIR}/pytrexio.py
cp ${SRC}/trexio.py ${PYDIR}/trexio.py
cp ${SRC}/trexio.c ${SRC}/trexio_s.h ${SRC}/trexio_private.h ${PYDIR}/src
cp ${SRC}/trexio_text.{c,h} ${PYDIR}/src
cp ${SRC}/pytrexio_wrap.c ${PYDIR}/src/pytrexio_wrap.c
cp ${INCLUDIR}/trexio.h ${PYDIR}/src
cp ${INCLUDIR}/config.h ${PYDIR}/src

# fix needed for HAVE_HDF5 symbol so that Python extension can be compiled without config.h
export LINE_NO=$(($(awk '/stdint.h/{print NR}' ${PYDIR_TREXIO_H}) + 1))

if [[ ${DO_HDF5} == 0 ]] ; then
    cp ${SRC}/trexio_hdf5.{c,h} ${PYDIR}/src
fi

# Copy additional info
cp ${TREXIO_ROOT}/AUTHORS ${TREXIO_ROOT}/LICENSE ${PYDIR}
