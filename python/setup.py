#!/usr/bin/env python3
"""
setup.py file for TREXIO Python package
"""


import os
from setuptools import setup, Extension

# this was recommended to solve the problem of the missing numpy header files
# bit it causes `pip install .` to fail with numpy module not found error
#try:
#    import numpy
#except ImportError:
#    raise Exception("numpy Python package cannot be imported.")
#numpy_includedir = numpy.get_include()

# this does not cause aforementioned issue but the includedir points to system-wide numpy and not to venv-wide
#from distutils.sysconfig import get_python_inc
#numpy_includedir = os.path.join(get_python_inc(plat_specific=1), 'numpy')

# dirty workaround: get numpy includedir from the environment variable that can be pre-set using set_NUMPY_INCLUDEDIR.sh
numpy_includedir = os.environ.get("NUMPY_INCLUDEDIR", None)
numpy_isUndefined = numpy_includedir is None or numpy_includedir==""

if numpy_isUndefined:
    raise Exception("NUMPY_INCLUDEDIR environment variable is not specified. Please do it manually or execute set_NUMPY_INCLUDEDIR.sh script.")


rootpath = os.path.dirname(os.path.abspath(__file__))
srcpath = os.path.join(rootpath, 'src')
c_files = ['trexio.c', 'trexio_hdf5.c', 'trexio_text.c', 'pytrexio_wrap.c']


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
# The block below is needed to derive additional flags related to the HDF5 library,
# which is required to build pytrexio extension module during the setup.py execution

h5_ldflags_withl = os.environ.get("H5_LDFLAGS", None)
h5_cflags_withI  = os.environ.get("H5_CFLAGS", None)

h5_ldflags_isUndefined = h5_ldflags_withl is None or h5_ldflags_withl==""
h5_cflags_isUndefined = h5_cflags_withI is None or h5_cflags_withI==""

if h5_ldflags_isUndefined or h5_cflags_isUndefined:

    try:
        import pkgconfig as pk
    except ImportError:
        raise Exception("pkgconfig Python package cannot be imported.")

    try:
        assert pk.exists('hdf5')
    except AssertionError:
        raise Exception("pkg-config could not locate HDF5")

    h5_cflags_withI = pk.cflags('hdf5')
    h5_ldflags_withl = pk.libs('hdf5')

h5_cflags = h5_cflags_withI.replace("-I","").split(" ")[0]
h5_ldflags = h5_ldflags_withl.split(" ")[0]

# ============================ End of the HDF5 block ============================ #

# Define pytrexio extension module based on TREXIO source codes + SWIG-generated wrapper
pytrexio_module = Extension('pytrexio._pytrexio',
                            sources = [os.path.join(srcpath, code) for code in c_files],
                            include_dirs = [h5_cflags, srcpath, numpy_includedir],
                            libraries = ['hdf5', 'hdf5_hl'],
                            extra_compile_args = ['-Wno-discarded-qualifiers'],
                            extra_link_args = [h5_ldflags]
                            )


setup(name             = 'trexio',
      version          = version_r,
      author           = "TREX-CoE",
      author_email     = "posenitskiy@irsamc.ups-tlse.fr",
      description      = """Python API of the TREXIO library""",
      long_description = long_description,
      long_description_content_type = "text/markdown",
      ext_modules      = [pytrexio_module],
      py_modules       = ['trexio'],
      packages         = ['pytrexio'],
      url              = 'https://github.com/TREX-CoE/trexio',
      license          = 'BSD',
      classifiers=[
         "Intended Audience :: Science/Research",
         "Intended Audience :: Developers",
         "Topic :: Scientific/Engineering",
         "Programming Language :: C",
         "Programming Language :: Python",
         "Programming Language :: Python :: 3",
         "Programming Language :: Python :: 3 :: Only",
         "Programming Language :: Python :: Implementation :: CPython",
         "License :: OSI Approved :: BSD License",
         "Operating System :: POSIX",
         "Operating System :: Unix",
         "Operating System :: MacOS"
      ],
      python_requires = ">=3.6",
      install_requires = ['numpy>=1.17.3']
      )

