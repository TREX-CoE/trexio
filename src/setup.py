#!/usr/bin/env python

"""
setup.py file for pytrexio
"""

from distutils.core import setup, Extension


pytrexio_module = Extension('_pytrexio',
                           sources=['trexio.c', 'trexio_hdf5.c', 'trexio_text.c', 'pytrexio_wrap.c'],
                           include_dirs=['/usr/include/hdf5/serial'],
                           #runtime_library_dirs=['/usr/lib/x86_64-linux-gnu/hdf5/serial'],
                           libraries=['hdf5', 'hdf5_hl'],
                           extra_compile_args=['-Wno-discarded-qualifiers'],
                           extra_link_args=['-L/usr/lib/x86_64-linux-gnu/hdf5/serial']
                           )

setup (name = 'pytrexio',
       version = '0.1',
       author      = "TREX-CoE",
       description = """Python API of the TREXIO library""",
       ext_modules = [pytrexio_module],
       py_modules = ["pytrexio"],
       url='https://github.com/TREX-CoE/trexio',
       packages=['distutils', 'distutils.command'],
       )
