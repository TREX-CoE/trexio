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
  local command="(org-babel-tangle-file \"$1\")"
  emacs --batch \
        --load=${TOOLS}/emacs/config_tangle.el \
        --eval "$command" &> /dev/null
}
#        --eval "(require 'org)" \
#        --eval "(org-babel-do-load-languages 'org-babel-load-languages '((python . t)))" \
#        --eval "(setq org-confirm-babel-evaluate nil)" \

# Go to src directory
cd ${SRC}

# We want the script to crash on the 1st error:
set -e

# Create directories for templates
echo "create populated directories"
mkdir -p templates_front/populated
mkdir -p templates_text/populated
mkdir -p templates_hdf5/populated

# It is important to ad '--' to rm because it tells rm that what follows are
# not options. It is safer.

# Cleaning of existing data
echo "remove existing templates"
rm -f -- templates_front/*.{c,h,f90}
rm -f -- templates_text/*.{c,h}
rm -f -- templates_hdf5/*.{c,h}

echo "clean populated directories"
rm -f -- templates_front/populated/*
rm -f -- templates_text/populated/*
rm -f -- templates_hdf5/populated/*

# Produce source files for front end
echo "tangle org files to generate templates"
cd templates_front
tangle templator_front.org
cd ..

# Produce source files for TEXT back end
cd templates_text
tangle templator_text.org
cd ..

# Produce source files for HDF5 back end
cd templates_hdf5
tangle templator_hdf5.org
cd ..

# Populate templates with TREXIO structure according to trex.json file
echo "run generator script to populate templates"
cp ${TOOLS}/generator.py ${TOOLS}/generator_tools.py ${SRC}
python3 generator.py
rm -f -- ${SRC}/generator.py ${SRC}/generator_tools.py
rm -f -r -- ${SRC}/__pycache__/

# Put pieces of source files together
echo "compile populated files in the lib source files "
cd templates_front
source build.sh
cp trexio* ../
cd ..
mv trexio.h trexio_f.f90 ../include

cd templates_text
source build.sh
cp trexio* ../
cd ..

cd templates_hdf5
source build.sh
cp trexio* ../
cd ..

