#!/bin/bash

set -x
set -e 

export H5_LDFLAGS=-L/usr/local/lib
export H5_CFLAGS=-I/usr/local/include

# install emacs for Debian

#apt-get update
#apt install software-properties-common -y
#apt-get install wget -y

#wget -q http://emacs.ganneff.de/apt.key -O- | apt-key add

#add-apt-repository "deb http://emacs.ganneff.de/ stretch main"
#apt-get update
#apt-get install emacs-snapshot -y
#update-alternatives --config emacsclient

# ===============================

# install TREXIO in the container from the GitHub repo clone

#apt-get install git -y

#git clone https://github.com/TREX-CoE/trexio.git
#cd trexio
#git checkout swig-python

#./autogen.sh
#TREXIO_DEVEL=1 ./configure --enable-silent-rules
#make
#make check

# ===============================

# alternatively: build wheel directly from developer-provided .tar.gz of TREXIO (generated with `python setup.py sdist`)
# note: trexio-VERSION.tar.gz has to be in the root directory of the host machine

# process input: first argument is the name of the .tar.gz with the source code of the Python API
if [[ -z "$1" ]]; then
    echo "Please specify the name of the TREXIO source code distribution (with .tar.gz suffix)"
    exit 1
fi

TREXIO_SOURCE=${1}

# remove prefix that ends with "-"
tmp=${TREXIO_SOURCE#*-}
# remove suffix that ends with ".tar.gz"
TR_VERSION=${tmp%.tar.gz*}

echo "TREXIO VERSION:" ${TR_VERSION}

# unzip and enter the folder with TREXIO Python API
gzip -cd /tmp/trexio-${TR_VERSION}.tar.gz | tar xvf -
cd trexio-${TR_VERSION}

# create and activate a virtual environment based on CPython version 3.6
/opt/python/cp36-cp36m/bin/python3 -m venv --clear trexio-manylinux-py36
source trexio-manylinux-py36/bin/activate 
python3 --version

# upgrade pip, otherwise it complains that manylinux wheel is "...not supported wheel on this platform"
pip install --upgrade pip 
# install dependencies needed to build manylinux wheel
pip install --upgrade setuptools wheel auditwheel numpy

# set an environment variable needed to locate numpy header files
source tools/set_NUMPY_INCLUDEDIR.sh

# produce conventional (non-manylinux) wheel
python3 setup.py bdist_wheel

# use auditwheel from PyPA to repair all wheels and make them manylinux-compatible
auditwheel repair dist/trexio-${TR_VERSION}-cp36-cp36m-*.whl

# install the produced manylinux wheel in the virtual environment
python3 -m pip install wheelhouse/trexio-${TR_VERSION}-cp36-cp36m-manylinux*.whl

# run test script
cd test && python3 test_api.py && cd ..

# cleaning
rm -rf -- dist/ build/ trexio.egg-info/

# deactivate the current environment
deactivate

# create and activate a virtual environment based on CPython version 3.7
/opt/python/cp37-cp37m/bin/python3 -m venv --clear trexio-manylinux-py37
source trexio-manylinux-py37/bin/activate 
python3 --version

# upgrade pip, otherwise it complains that manylinux wheel is "...not supported wheel on this platform"
pip install --upgrade pip 
# install dependencies needed to build manylinux wheel
pip install --upgrade setuptools wheel auditwheel numpy

# set an environment variable needed to locate numpy header files
source tools/set_NUMPY_INCLUDEDIR.sh

# produce conventional (non-manylinux) wheel
python3 setup.py bdist_wheel

# use auditwheel from PyPA to repair all wheels and make them manylinux-compatible
auditwheel repair dist/trexio-${TR_VERSION}-cp37-cp37m-*.whl

# install the produced manylinux wheel in the virtual environment
python3 -m pip install wheelhouse/trexio-${TR_VERSION}-cp37-cp37m-manylinux*.whl

# run test script
cd test && python3 test_api.py && cd ..

# cleaning
rm -rf -- dist/ build/ trexio.egg-info/

# deactivate the current environment
deactivate

# create and activate a virtual environment based on CPython version 3.8
# NOTE: starting from CPython 3.8 there is no need to add m in the abi-tag, e.g. use cp38-cp38 instead of cp38-cp38m
/opt/python/cp38-cp38/bin/python3 -m venv --clear trexio-manylinux-py38
source trexio-manylinux-py38/bin/activate 
python3 --version

# upgrade pip, otherwise it complains that manylinux wheel is "...not supported wheel on this platform"
pip install --upgrade pip 
# install dependencies needed to build manylinux wheel
pip3 install --upgrade setuptools wheel auditwheel numpy

# set an environment variable needed to locate numpy header files
source tools/set_NUMPY_INCLUDEDIR.sh

# produce conventional (non-manylinux) wheel
python3 setup.py bdist_wheel

# use auditwheel from PyPA to repair all wheels and make them manylinux-compatible
auditwheel repair dist/trexio-${TR_VERSION}-cp38-cp38-*.whl

# install the produced manylinux wheel in the virtual environment
python3 -m pip install wheelhouse/trexio-${TR_VERSION}-cp38-cp38-manylinux*.whl

# run test script
cd test && python3 test_api.py && cd ..

# cleaning
rm -rf -- dist/ build/ trexio.egg-info/

# deactivate the current environment
deactivate

# create and activate a virtual environment based on CPython version 3.8
/opt/python/cp39-cp39/bin/python3 -m venv --clear trexio-manylinux-py39
source trexio-manylinux-py39/bin/activate 
python3 --version

# upgrade pip, otherwise it complains that manylinux wheel is "...not supported wheel on this platform"
pip install --upgrade pip 
# install dependencies needed to build manylinux wheel
pip3 install --upgrade setuptools wheel auditwheel numpy

# produce conventional (non-manylinux) wheel
python3 setup.py bdist_wheel

# use auditwheel from PyPA to repair all wheels and make them manylinux-compatible
auditwheel repair dist/trexio-${TR_VERSION}-cp39-cp39-*.whl

# install the produced manylinux wheel in the virtual environment
python3 -m pip install wheelhouse/trexio-${TR_VERSION}-cp39-cp39-manylinux*.whl

# run test script
cd test && python3 test_api.py && cd ..

# cleaning
rm -rf -- dist/ build/ trexio.egg-info/

# deactivate the current environment
deactivate

# remove all virtual environments used to produce the wheels
rm -rf -- trexio-manylinux-py39 \
	  trexio-manylinux-py38 \
	  trexio-manylinux-py37 \
	  trexio-manylinux-py36 

