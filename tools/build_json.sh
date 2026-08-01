#!/bin/bash
set -e

# Check that script is executed from tools directory
if [[ $(basename $PWD) != "tools" ]] ; then
  echo "This script should run in the tools directory"
  exit -1
fi

TREXIO_ROOT=$(dirname "${PWD}../")

#   First define readonly global variables.
readonly SRC=${TREXIO_ROOT}/src
readonly TOOLS=${TREXIO_ROOT}/tools

# Function to produce TREXIO source files from org-mode files
function tangle()
{
  emacs --batch "$1" \
        --load=${TOOLS}/emacs/config_tangle.el \
        --eval "(progn
              (require 'ob)
              (require 'ob-python)
              (org-babel-execute-buffer)
              (org-babel-tangle))" &> /dev/null
}

# Create trex.json file
cd ${TREXIO_ROOT}
tangle trex.org
touch trex.json

