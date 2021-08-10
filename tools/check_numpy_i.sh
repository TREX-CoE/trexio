#!/bin/bash

# Check that script is executed from tools directory
if [[ $(basename $PWD) != "tools" ]] ; then
  echo "This script should run in the tools directory"
  exit -1
fi

TREXIO_ROOT=$(dirname "${PWD}../")

#   First define readonly global variables.
readonly SRC=${TREXIO_ROOT}/src
readonly TOOLS=${TREXIO_ROOT}/tools

# We want the script to crash on the 1st error:
set -e

NUMPY_SRC=${SRC}/numpy.i
NUMPY_LATEST=${TOOLS}/numpy.i

# Download the latest numpy.i file from NumPy GitHub
wget https://raw.githubusercontent.com/numpy/numpy/main/tools/swig/numpy.i -O ${NUMPY_LATEST}

# Execute diff to check if the numpy.i file in the src/ directory is updated
if ! diff -q ${NUMPY_LATEST} ${NUMPY_SRC}  &>/dev/null; then
  >&2 echo "numpy.i SWIG interface file in the source tree is outdated; replacing ..."
  mv ${NUMPY_LATEST} ${NUMPY_SRC}
else
  >&2 echo "numpy.i SWIG interface file in the source tree is up-to-date."
  rm ${NUMPY_LATEST}
fi

