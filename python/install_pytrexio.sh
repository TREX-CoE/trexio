#!/bin/bash

set -x
set -e

# the parser below is needed when ./configure outputs several HDF5-related flags, which are then provided as input arguments to this script
for arg in "$@"
do
    if [[ $arg == "-L"* ]] && [[ $arg == *"hdf5"* ]]; then
        H5_LDFLAGS_LOCAL=$arg
    elif [[ $arg == "-I"* ]] && [[ $arg == *"hdf5"* ]]; then
        H5_CFLAGS_LOCAL=$arg
    fi
done

# check that both variables are set
if [[ -z ${H5_LDFLAGS_LOCAL} ]] || [[ -z ${H5_CFLAGS_LOCAL} ]]; then
    if [[ -z ${H5_LDFLAGS} ]] || [[ -z ${H5_CFLAGS} ]]; then
        which h5cc &> /dev/null
        if [[ $? -eq 0 ]] ; then
              HDF5_tmp_flags=$(h5cc -showconfig \
                  | grep  'FLAGS\|Extra libraries:' \
                  | awk  -F: '{printf("%s "), $2}' )
              echo $HDF5_tmp_flags

              # Find the installation directory and append include/
              HDF5_tmp_inst=$(h5cc -showconfig \
                  | grep  'Installation point:' \
                  | awk  '{print $NF}' )
              echo $HDF5_tmp_inst

              # Add this to the CPPFLAGS
              HDF5_CPPFLAGS="-I${HDF5_tmp_inst}/include"

              HDF5_SHOW=$(h5cc -show)

              # Now sort the flags out based upon their prefixes
              for arg in $HDF5_SHOW $HDF5_tmp_flags ; do
                case "$arg" in
                  -I*) echo $HDF5_CPPFLAGS | grep -e "$arg" 2>&1 >/dev/null \
                        || HDF5_CPPFLAGS="$HDF5_CPPFLAGS $arg"
                    ;;
                  -L*) echo $HDF5_LDFLAGS | grep -e "$arg" 2>&1 >/dev/null \
                        || HDF5_LDFLAGS="$HDF5_LDFLAGS $arg"
                    ;;
                  -l*) echo $HDF5_LIBS | grep -e "$arg" 2>&1 >/dev/null \
                        || HDF5_LIBS="$HDF5_LIBS $arg"
                    ;;
                esac
              done
              export H5_LDFLAGS="$HDF5_LDFLAGS"
              export H5_CFLAGS="$HDF5_CPPFLAGS"
        else
            echo "Paths to the HDF5 installation are not provided. pkgconfig will try to detect them."
        fi
    else
        echo "Using exported H5_LDFLAGS and H5_CFLAGS environment variables."
    fi
else
    export H5_LDFLAGS=${H5_LDFLAGS_LOCAL}
    export H5_CFLAGS=${H5_CFLAGS_LOCAL}
fi

# Install/upgrade packages required for the installation
python3 -m pip install --upgrade setuptools build pip
python3 -m pip install -r requirements.txt
python3 -m pip install pytest

# export NUMPY_INCLUDEDIR environment variable needed for the proper setup
#source tools/set_NUMPY_INCLUDEDIR.sh
#if [[ -z ${NUMPY_INCLUDEDIR} ]] ; then
#    echo "NUMPY_INCLUDEDIR is not set. Check that numpy is installed (e.g. call pip freeze)."
#    exit 1
#fi

# Create build directory and compile extension files (*.c)
# --no-user-cfg disables custom .cfg files of the user machine, so that only setup.cfg is used
#python3 -s setup.py --no-user-cfg build

# Local inplace build of the .so module with SWIG-produced pytrexio_wrap.c (from the SWIG documentation)
#python3 setup.py build_ext --inplace --swig-opts="-modern"

# Create distributions:

# OLD WAY (DEPRECATED BY PYPA)
#   1) sdist produces .tar.gz with all files necessary for manual compilation;
#   2) bdist_whell produces .whl wheel distribution (see https://www.python.org/dev/peps/pep-0425/).
#python3 setup.py sdist bdist_wheel

# NEW WAY (USING BUILD PACKAGE OF PYPA)
python3 -m build --sdist --wheel --outdir dist/

# Install pytrexio in the current environment from the aforementioned wheel
python3 -m pip install dist/trexio-*.whl --force-reinstall

# Run the command below in the root directory to install the package in 'editable' (-e) mode without dependencies (--no-deps)
#python -m pip install -e . --no-deps

# Uninstall pytrexio: this only works from the pytrexio root directory
#python3 -m pip uninstall trexio

# Install twine to upload things on PyPI
#python3 -m pip install --upgrade twine

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
