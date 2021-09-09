#!/bin/bash                                                    

set -x
set -e

H5_CFLAGS_LOCAL=$1
H5_LDFLAGS_LOCAL=$2


# Install/upgrade packages required for the installation
python3 -m pip install --upgrade setuptools wheel twine
python3 -m pip install -r requirements.txt

# Create build directory and compile extension files (*.c)
# --no-user-cfg disables custom .cfg files of the user machine, so that only setup.cfg is used
H5_LDFLAGS=${H5_LDFLAGS_LOCAL} H5_CFLAGS=${H5_CFLAGS_LOCAL} python3 -s setup.py --no-user-cfg build 

# Local inplace build of the .so module with SWIG-produced pytrexio_wrap.c (from the SWIG documentation)
#python3 setup.py build_ext --inplace --swig-opts="-modern"

# Create distributions: 
#   1) sdist produces .tar.gz with all files necessary for manual compilation;
#   2) bdist_whell produces .whl wheel distribution (see https://www.python.org/dev/peps/pep-0425/).
python3 setup.py sdist bdist_wheel

# Install pytrexio in the current environment from the aforementioned wheel
# --force-reinstall is needed here because build-system pre-installs pytrexio in the environment 
#                   but does not install things in the corresponding site-packages directory
python3 -m pip install dist/trexio-*.whl --force-reinstall

# Run the command below in the root directory to install the package in 'editable' (-e) mode without dependencies (--no-deps)
#python -m pip install -e . --no-deps

# Uninstall pytrexio: this only works from the pytrexio root directory
#python3 -m pip uninstall trexio

# Test the current release by uploading to TestPyPI sandbox
#python3 -m twine upload --repository testpypi dist/trexio-*.tar.gz

# Upload updated version of PyTREXIO to PyPI
#python3 -m twine upload dist/trexio-*.tar.gz

# Cleaning
rm -rf build dist trexio.egg-info

# Additional information related to the installation of the TREXIO Python API

#Removing MANIFEST.in leads to issues in the installation. In particular, the .c and .h source files do not get copied 
#from the src/ directory into the tar.gz which is produced by setup sdist command. 
#These source files are required to build the pytrexio.so extension module, which is needed for the Python API.

