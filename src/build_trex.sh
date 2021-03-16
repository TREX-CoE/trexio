#!/bin/bash


rm templates_front/populated/*
rm templates_text/populated/*
rm templates_hdf5/populated/*

python generator.py

sleep 2

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

