#!/bin/bash

set -x
set -e

export H5_LDFLAGS=-L/usr/local/lib
export H5_CFLAGS=-I/usr/local/include

readonly ROOTDIR=${PWD}

# create the wheelhouse directory
mkdir -p ${ROOTDIR}/wheelhouse

# build wheel directly from developer-provided .tar.gz of TREXIO (generated with `python setup.py sdist`)
# note: trexio-VERSION.tar.gz has to be in the root directory of the host machine and provided as an argument to this script

# process input: first argument is the name of the .tar.gz with the source code of the Python API
if [[ -z "$1" ]]; then
    echo "Please specify the name of the TREXIO source code distribution (with .tar.gz suffix)"
    exit 1
fi

# derive TREXIO version from the file name
TREXIO_SOURCE=${1}
# remove prefix that ends with "-"
tmp=${TREXIO_SOURCE#*-}
# remove suffix that ends with ".tar.gz"
TR_VERSION=${tmp%.tar.gz*}
# print the computed version
echo "TREXIO VERSION:" ${TR_VERSION}

# unzip and enter the folder with TREXIO Python API
gzip -cd ${TREXIO_SOURCE} | tar xvf -
cd trexio-${TR_VERSION}

# the function below build manylinux wheels based on the provided version of python (e.g. build_wheel_for_py 36)
function build_wheel_for_py()
{

   if [[ -z "$1" ]]; then
      echo "Empty string provided instead of the Python version"
      exit 1
   fi

   # derive PYVERSION from the input argument
   PYVERSION=${1}

   # derive manylinux glibc tag from the PLAT env variable provided to docker run
   # this is needed to avoid building wheel for 2010_x86_64 with CPython 3.10
   # because NumPy does not have wheels for it
   MANYLINUX_TAG=${PLAT:9:4}
   if [[ ${PYVERSION} -eq 310 ]] && [[ ${MANYLINUX_TAG} -eq 2010 ]]; then
	echo "Skip build of the wheel for CPython 3.10 on manylinux2010_x86_64"
	return
   fi

   # python versions <= 3.7 required additional "m" in the platform tag, e.g. cp37-cp37m
   if [[ ${PYVERSION} -eq 36 ]] || [[ ${PYVERSION} -eq 37 ]]; then
       PYM="m"
   else
       PYM=""
   fi

   CPYTHON="cp${PYVERSION}-cp${PYVERSION}${PYM}"

   # create and activate a virtual environment based on CPython version ${PYVERSION}
   /opt/python/${CPYTHON}/bin/python3 -m venv --clear trexio-manylinux-py${PYVERSION}
   source trexio-manylinux-py${PYVERSION}/bin/activate
   python3 --version

   # upgrade pip, otherwise it complains that manylinux wheel is "...not supported wheel on this platform"
   pip install --upgrade pip
   # install dependencies needed to build manylinux wheel
   pip install --upgrade setuptools wheel auditwheel
   if [ ${PYVERSION} -eq 36 ] || [ ${PYVERSION} -eq 37 ]; then
       pip install numpy==1.17.3
   elif [ ${PYVERSION} -eq 38 ]; then
       pip install numpy==1.18.3
   elif [ ${PYVERSION} -eq 39 ]; then
       pip install numpy==1.19.3
   else
       pip install numpy==1.21.4
   fi

   # set an environment variable needed to locate numpy header files
   source tools/set_NUMPY_INCLUDEDIR.sh

   # produce conventional (non-manylinux) wheel
   python3 setup.py bdist_wheel

   # use auditwheel from PyPA to repair all wheels and make them manylinux-compatible
   auditwheel repair dist/trexio-${TR_VERSION}-${CPYTHON}-*.whl

   # install the produced manylinux wheel in the virtual environment
   python3 -m pip install wheelhouse/trexio-${TR_VERSION}-${CPYTHON}-manylinux*.whl

   # run test script
   cd test && python3 test_api.py && cd ..

   # cleaning
   rm -rf -- dist/ build/ trexio.egg-info/

   # deactivate the current environment
   deactivate

   # remove the virtual environment
   rm -rf -- trexio-manylinux-py${PYVERSION}

   # move the wheelhouse directory to the ROOTDIR
   mv wheelhouse/trexio-${TR_VERSION}-${CPYTHON}-manylinux*.whl ${ROOTDIR}/wheelhouse/
}


# build wheels for all versions of CPython in this container
for CPYVERSION in 36 37 38 39 310
do
  build_wheel_for_py ${CPYVERSION}
done
