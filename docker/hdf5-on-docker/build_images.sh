#!/bin/bash

set -x
set -e 

# currently cannot build ARM64 images on the AMD64 platform due to the error:
# standard_init_linux.go:219: exec user process caused: exec format error 
#for tag in 2010_x86_64 2014_x86_64 2_24_x86_64 2014_aarch64 2_24_aarch64

# build only x86_64 images
for tag in 2010_x86_64 2014_x86_64 2_24_x86_64
do
    echo "Building image on ${tag} platform"
    docker build -t hdf5_1_12_on_${tag} . -f Dockerfile_${tag}
done

