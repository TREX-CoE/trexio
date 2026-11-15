#!/usr/bin/env python3
"""
setup.py file for TREXIO Python package
"""


import os, sys
from setuptools import setup, Extension

def parse_setuppy_commands():
    """Skip native dependency checks for source distributions and metadata.

    Metadata generation must work without HDF5, including the egg_info hook
    setuptools runs before building an sdist. Wheel builds check dependencies.
    """
    args = sys.argv[1:]

    return any(command in args for command in ('sdist', 'egg_info', 'dist_info'))

skip_dependency_checks = parse_setuppy_commands()

# this was recommended to solve the problem of the missing numpy header files
try:
    import numpy
except ImportError:
    raise Exception("numpy Python package cannot be imported.")

numpy_includedir = numpy.get_include()

# dirty workaround: get numpy includedir from the environment variable that can be pre-set using set_NUMPY_INCLUDEDIR.sh
#numpy_includedir = os.environ.get("NUMPY_INCLUDEDIR", None)

numpy_isUndefined = numpy_includedir is None or numpy_includedir==""

if numpy_isUndefined and not skip_dependency_checks:
    raise Exception("NUMPY_INCLUDEDIR environment variable is not specified. Please do it manually or execute set_NUMPY_INCLUDEDIR.sh script.")


rootpath = os.path.dirname(os.path.abspath(__file__))
srcpath = os.path.join(rootpath, 'src')
c_files = ['trexio.c', 'trexio_text.c', 'trexio_memory.c']


with open("README.md", "r") as fh:
    long_description = fh.read()

VERSIONFILE = "pytrexio/_version.py"
try:
    exec(open(VERSIONFILE).read())
except:
    raise IOError("Could not open the version file %s." % (VERSIONFILE, ))

version_r = __version__
if not version_r:
    raise RuntimeError("Unable to find a version string in %s." % (VERSIONFILE, ))


# =========================== Start of the HDF5 block =========================== #
# HDF5 is required for extension builds unless the user explicitly opts out
# by setting TREXIO_PYTHON_EXCLUDE_HDF5=1. Metadata and sdists do not
# compile the extension and therefore do not need a local HDF5 installation.

h5_present = False
exclude_hdf5 = os.environ.get("TREXIO_PYTHON_EXCLUDE_HDF5") == "1"
h5_ldflags_withl = os.environ.get("H5_LDFLAGS", None)
h5_cflags_withI  = os.environ.get("H5_CFLAGS", None)

h5_ldflags_isUndefined = h5_ldflags_withl is None or h5_ldflags_withl==""
h5_cflags_isUndefined = h5_cflags_withI is None or h5_cflags_withI==""

if not exclude_hdf5 and not skip_dependency_checks:
    h5_present = not h5_ldflags_isUndefined and not h5_cflags_isUndefined

if not h5_present and not exclude_hdf5 and not skip_dependency_checks:
    try:
        import pkgconfig as pk
        h5_present = pk.exists('hdf5')
        if h5_present:
            h5_cflags_withI = pk.cflags('hdf5')
            h5_ldflags_withl = pk.libs('hdf5')
    except (ImportError, OSError):
        h5_present = False

    if not h5_present:
        raise RuntimeError(
            "HDF5 could not be discovered. Install HDF5 and make it available "
            "to pkg-config, or set both H5_CFLAGS and H5_LDFLAGS, for example:\n"
            'H5_CFLAGS="-I/path/to/hdf5/include" '
            'H5_LDFLAGS="-L/path/to/hdf5/lib" python -m pip install .\n'
            "To explicitly build without HDF5 (text and in-memory back ends), "
            "use: TREXIO_PYTHON_EXCLUDE_HDF5=1 python -m pip install .\n"
            "For PyPI, use: TREXIO_PYTHON_EXCLUDE_HDF5=1 python -m pip install "
            "trexio --no-binary=trexio --no-cache-dir"
        )

if h5_present:
    h5_cflags = h5_cflags_withI.replace("-I","").split(" ")[0]
    h5_ldflags = h5_ldflags_withl.split(" ")[0]
    c_files.append('trexio_hdf5.c')

# ============================ End of the HDF5 block ============================ #

# Define pytrexio extension module based on TREXIO source codes + SWIG-generated wrapper
c_files.append('pytrexio_wrap.c')
compile_args = [
        '-std=c99',
        '-Wno-discarded-qualifiers',
        '-Wno-unused-variable',
        '-Wno-unused-but-set-variable'
        ]
# An Autotools config.h may enable HDF5. Explicit builds without HDF5 must
# ignore it and use the standalone configuration instead.
if not exclude_hdf5 and os.path.isfile(os.path.join(srcpath, "config.h")):
        compile_args.append('-DHAVE_CONFIG_H')
# explicit hack needed when building from sdist tarball
if h5_present:
        compile_args.append('-DHAVE_HDF5')

# define C extension module
if h5_present:
    pytrexio_module = Extension('trexio._pytrexio',
                            sources = [os.path.join(srcpath, code) for code in c_files],
                            include_dirs = [h5_cflags, srcpath, numpy_includedir],
                            libraries = ['hdf5' ],
                            extra_compile_args = compile_args,
                            extra_link_args = [h5_ldflags]
                            )
else:
    pytrexio_module = Extension('trexio._pytrexio',
                            sources = [os.path.join(srcpath, code) for code in c_files],
                            include_dirs = [srcpath, numpy_includedir],
                            extra_compile_args = compile_args
                            )


# Compiler macros change with the backend selection. Separate object directories
# prevent setuptools from reusing objects built for the other selection.
build_base = os.path.join('build', 'no_hdf5' if exclude_hdf5 else 'hdf5')

setup(name             = 'trexio',
      version          = version_r,
      author           = "TREX-CoE",
      author_email     = "posenitskiy@irsamc.ups-tlse.fr",
      description      = """Python API of the TREXIO library""",
      long_description = long_description,
      long_description_content_type = "text/markdown",
      ext_modules      = [pytrexio_module],
      packages         = ['trexio'],
      options          = {'build': {'build_base': build_base}},
      url              = 'https://github.com/TREX-CoE/trexio',
      license          = 'BSD-3-Clause',
      classifiers=[
         "Intended Audience :: Science/Research",
         "Intended Audience :: Developers",
         "Topic :: Scientific/Engineering",
         "Programming Language :: C",
         "Programming Language :: Python",
         "Programming Language :: Python :: 3",
         "Programming Language :: Python :: 3 :: Only",
         "Programming Language :: Python :: Implementation :: CPython",
         "Operating System :: POSIX",
         "Operating System :: Unix",
         "Operating System :: MacOS"
      ],
      python_requires = ">=3.6",
      install_requires = ['numpy>=1.17.3']
      )
