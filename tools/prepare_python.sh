#!/bin/bash

# Check that script is executed from tools directory
if [[ $(basename $PWD) != "tools" ]] ; then
  echo "This script should run in the tools directory"
  exit -1
fi

TREXIO_ROOT=$(dirname "${PWD}../")

#   First define readonly global variables.
readonly SRC=${TREXIO_ROOT}/src
readonly INCLUDIR=${TREXIO_ROOT}/include
readonly TOOLS=${TREXIO_ROOT}/tools
readonly PYDIR=${TREXIO_ROOT}/python

# We want the script to crash on the 1st error:
set -e

# Create src directory in the python folder if not yet done
mkdir -p ${PYDIR}/src

# Copy all the source code and header files in the corresponding python directory
cp ${SRC}/*.py ${PYDIR}
cp ${SRC}/*.c ${PYDIR}/src
cp ${SRC}/*.h ${PYDIR}/src
cp ${INCLUDIR}/trexio.h ${PYDIR}/src 

# Copy additional info
cp ${TREXIO_ROOT}/AUTHORS ${TREXIO_ROOT}/LICENSE ${TREXIO_ROOT}/README.md ${PYDIR}

