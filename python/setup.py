#!/usr/bin/env python

"""
setup.py file for TREXIO Python package
"""

from setuptools import setup, Extension
import os

rootpath = os.path.dirname(os.path.abspath(__file__))
srcpath = os.path.join(rootpath, 'src')
c_files = ['trexio.c', 'trexio_hdf5.c', 'trexio_text.c', 'pytrexio_wrap.c']

with open("README.md", "r") as fh:
    long_description = fh.read()


pytrexio_module = Extension('pytrexio._pytrexio',
                            sources = [os.path.join(srcpath, code) for code in c_files],
                            include_dirs = ['/usr/include/hdf5/serial', srcpath],
                            libraries = ['hdf5', 'hdf5_hl'],
                            extra_compile_args = ['-Wno-discarded-qualifiers'],
                            extra_link_args = ['-L/usr/lib/x86_64-linux-gnu/hdf5/serial']
                            )


setup(name             = 'trexio',
      version          = '0.1',
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
         "Programming Language :: Python :: 3",
         "Programming Language :: C",
         "License :: OSI Approved :: BSD License",
         "Operating System :: POSIX :: Linux"
      ],
      install_requires = ['h5py']
      )
