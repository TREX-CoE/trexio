#!/bin/bash                                                    

set -x
set -e

H5_CFLAGS_LOCAL=$1
H5_LDFLAGS_LOCAL=$2

# This script should update the version of the Python package
#source version.py

# Install/upgrade packages required for the installation
python3 -m pip install --upgrade setuptools wheel twine

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

# Uninstall pytrexio: this only works from the pytrexio root directory (more likely python/ folder) and only after --force-reinstall
#python3 -m pip uninstall trexio

# Test the current release by uploading to TestPyPI sandbox
#python3 -m twine upload --repository testpypi dist/trexio-*.tar.gz

# NOTE:I get an error: 
#      Binary wheel 'trexio-0.1-cp38-cp38-linux_x86_64.whl' has an unsupported platform tag 'linux_x86_64'.
# when uploading the wheel instead of the tar.gz file to testpypi
# This is a well-known issue, see https://stackoverflow.com/questions/59451069/binary-wheel-cant-be-uploaded-on-pypi-using-twine
# Once fixed both .tar.gz and .whl distribution can be uploaded, meaning that dist/trexio-*.tar.gz can be replaced by dist/*
#
# Compatibility tags for Linux have been discussed in PEP-513 https://www.python.org/dev/peps/pep-0513/

# Upload updated version of PyTREXIO to PyPI
#python3 -m twine upload dist/trexio-*.tar.gz

# Cleaning
rm -rf build dist trexio.egg-info

