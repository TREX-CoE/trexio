
# TREXIO

[![build](https://github.com/TREX-CoE/trexio/actions/workflows/actions.yml/badge.svg)](https://github.com/TREX-CoE/trexio/actions/workflows/actions.yml)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/TREX-CoE/trexio)

TREX library for efficient I/O.


## Minimal requirements (for users):

- Autotools             (autoconf >= 2.69, automake >= 1.11, libtool >= 2.2)
- C compiler            (gcc/icc/clang)
- Fortran compiler      (gfortran/ifort)
- HDF5 library          (>= 1.8)	[optional, recommended for high performance]


## Installation procedure from the tarball (for users):

1. Download the `trexio-<version>.tar.gz` file
2. `gzip -cd trexio-<version>.tar.gz | tar xvf -`
3. `cd trexio-<version>`
4. `./configure`
5. `make`
6. `make check`
7. `sudo make install`


**Note: on systems with no `sudo` access, one can replace `./configure` with `./configure prefix=${PWD}/_install` in order to execute `make install/uninstall` commands without `sudo` privileges.**


## Additional requirements (for developers):

- python3       (>= 3.6)
- Emacs         (>= 26.0)
- SWIG          (>= 4.0)

## Installation procedure from the GitHub repo clone (for developers):

1. `git clone https://github.com/TREX-CoE/trexio.git`
2. `cd trexio`
3. `./autogen.sh`
4. `./configure`
5. `make`
6. `make check`
7. `sudo make install`

## Compilation without the HDF5 library

By default, the configuration step proceeds to search for the [HDF5 library](https://portal.hdfgroup.org/display/HDF5/HDF5).
This search can be disabled if HDF5 is not present/installable on the user machine.
To compile without HDF5, append `--without-hdf5` option to `configure` script. For example,

`./configure --without-hdf5`

## Linking to your program

The `make install` command takes care of installing the TREXIO shared library on the user machine.
Once installed, add `-ltrexio` to the list of compiler options.

In some cases (e.g. when using custom `prefix` during configuration), the TREXIO library might end up installed in a directory, which is absent in the default `$LIBRARY_PATH`.
In order to link the program against TREXIO, the search paths can be modified as follows:

`export LIBRARY_PATH=$LIBRARY_PATH:<path_to_trexio>/lib`

(same holds for `$LD_LIBRARY_PATH`). The `<path_to_trexio>` has to be replaced by the prefix used during the installation.

If your compilation relies on some build tools (like Autotools or CMake), feel free to use the built-in solutions to locate and link external dependencies automatically.

In Fortran applications, make sure that the `trexio_f.f90` module file is included in the source tree.
You might have to manually copy it into your program source directory.
The `trexio_f.f90` module file can be found in the `include/` directory of the TREXIO source code distribution.

**Note:** there is no need to include `trexio.h` header file during compilation of Fortran programs.
Only the installed library and the Fortran module file are required.


## Naming convention

The primary TREXIO API is composed of the following functions:

- `trexio_open`
- `trexio_write_[group]_[variable]`
- `trexio_read_[group]_[variable]`
- `trexio_has_[group]_[variable]`
- `trexio_close`

where `[group]` and `[variable]` substitutions correspond to the contents of the `trex.json` configuration file
(for more details, see the corresponding [documentation](https://trex-coe.github.io/trexio/trex.html) page).
For example, consider the `coord` variable (array), which belongs to the `nucleus` group. The TREXIO user can write or read it using `trexio_write_nucleus_coord` or `trexio_read_nucleus_coord` functions, respectively.

Note: the `[variable]` names have to be unique only within the corresponding parent `[group]`.
There is no naming conflict when, for example, `num` variable exists both in the `nucleus` group (i.e. the number of nuclei) and in the `mo` group (i.e. the number of molecular orbitals).
These quantities can be accessed using the corresponding `trexio_[has|read|write]_nucleus_num` and `trexio_[has|read|write]_mo_num`, respectively.


## Python API

For more details regarding the installation and usage of the TREXIO Python API,
see [this page](python/README.md).


## Tutorial

TREXIO tutorials in Jupyter notebook format can be found in the
[corresponding GitHub repository](https://github.com/TREX-CoE/trexio-tutorials)
or on [Binder](https://mybinder.org/v2/gh/TREX-CoE/trexio-tutorials/HEAD).

For example, the tutorial covering TREXIO basics using benzene molecule as an example can be viewed and executed online by clicking on this badge:
[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/TREX-CoE/trexio-tutorials/HEAD?filepath=notebooks%2Ftutorial_benzene.ipynb)


## Documentation

[Documentation generated from TREXIO org-mode files.](https://trex-coe.github.io/trexio/)


### Miscellaneous

Note: The code should be compliant with the C99
[CERT C coding standard](https://resources.sei.cmu.edu/downloads/secure-coding/assets/sei-cert-c-coding-standard-2016-v01.pdf).
This can be checked with the `cppcheck` tool.



-----------------
![European flag](https://trex-coe.eu/sites/default/files/inline-images/euflag.jpg)
[TREX: Targeting Real Chemical Accuracy at the Exascale](https://trex-coe.eu) project has received funding from the European Union’s Horizon 2020 - Research and Innovation program - under grant agreement no. 952165. The content of this document does not represent the opinion of the European Union, and the European Union is not responsible for any use that might be made of such content.


