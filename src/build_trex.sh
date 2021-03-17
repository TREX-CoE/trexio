#!/bin/bash

echo "create populated directories"
mkdir -p templates_front/populated
mkdir -p templates_text/populated
mkdir -p templates_hdf5/populated

echo "remove existing templates"
rm templates_front/*.c
rm templates_text/*.c
rm templates_hdf5/*.c
rm templates_front/*.h
rm templates_text/*.h
rm templates_hdf5/*.h

echo "clean populated directories"
rm templates_front/populated/*
rm templates_text/populated/*
rm templates_hdf5/populated/*

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
python generator.py

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

