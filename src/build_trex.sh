#!/bin/bash

if [[ $(basename $PWD) != "src" ]] ; then
  echo "This script should run in the src directory"
  exit -1
fi

# We want the script to crash on the 1st error:
set -e

echo "create populated directories"
mkdir -p templates_front/populated
mkdir -p templates_text/populated
mkdir -p templates_hdf5/populated

# It is important to ad '--' to rm because it tells rm that what follows are
# not options. It is safer.

echo "remove existing templates"
rm -- templates_front/*.{c,h} || true
rm -- templates_text/*.{c,h} || true
rm -- templates_hdf5/*.{c,h} || true

echo "clean populated directories"
rm -- templates_front/populated/* || true
rm -- templates_text/populated/* || true
rm -- templates_hdf5/populated/* || true

echo "tangle org files to generate templates"
cd templates_front
emacs --batch --eval "(require 'org)" --eval '(org-babel-tangle-file "templator_front.org")'
cd ..

cd templates_text
emacs --batch --eval "(require 'org)" --eval '(org-babel-tangle-file "templator_text.org")'
cd ..

cd templates_hdf5
emacs --batch --eval "(require 'org)" --eval '(org-babel-tangle-file "templator_hdf5.org")'
cd ..

echo "run generator script to populate templates"
python3 generator.py

sleep 2

echo "compile populated files in the lib source files "
cd templates_front
source build.sh
cp trexio* ../
cd ..

cd templates_text
source build.sh
cp trexio* ../
cd ..

cd templates_hdf5
source build.sh
cp trexio* ../
cd ..

