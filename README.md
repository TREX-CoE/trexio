
# TREXIO

[![build](https://github.com/TREX-CoE/trexio/actions/workflows/actions.yml/badge.svg)](https://github.com/TREX-CoE/trexio/actions/workflows/actions.yml)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/TREX-CoE/trexio)

TREX library for efficient I/O.


## Minimal requirements (for users):

- Autotools             (autoconf >= 2.69, automake >= 1.11, libtool >= 2.2)
- C compiler            (gcc/icc/clang)
- Fortran compiler      (gfortran/ifort)
- HDF5 library          (>= 1.8)


## Installation procedure from the tarball (for users):

1. Download the `trexio-<version>.tar.gz` file
2. `gzip -cd trexio-<version>.tar.gz | tar xvf -`
3. `cd trexio-<version>`
4. `./configure --enable-silent-rules`
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
4. `TREXIO_DEVEL=1 ./configure --enable-maintainer-mode`
5. `make`
6. `make check`
7. `sudo make install`


## Naming convention

The primary TREXIO API is composed of the following functions:

- `trexio_open`
- `trexio_write_[group]_[variable]`
- `trexio_read_[group]_[variable]`
- `trexio_has_[group]_[variable]`
- `trexio_close`

where `[group]` and `[variable]` substitutions correspond to the contents of the `trex.json` configuration file (for more details, see the corresponding [documentation](https://trex-coe.github.io/trexio/trex.html) page).
For example, consider the `coord` variable (array), which belongs to the `nucleus` group. The TREXIO user can write or read it using `trexio_write_nucleus_coord` or `trexio_read_nucleus_coord` functions, respectively.

Note: the `[variable]` names have to be unique only within the corresponding parent `[group]`. 
There is no naming conflict when, for example, `num` variable exists both in the `nucleus` group (i.e. the number of nuclei) and in the `mo` group (i.e. the number of molecular orbitals). 
These quantities can be accessed using the corresponding `trexio_[has|read|write]_nucleus_num` and `trexio_[has|read|write]_mo_num`, respectively.


## Python API

For more details regarding the installation and usage of the TREXIO Python API, see [this page](python/README.md).


## Tutorial

**TODO**


## Technical documentation

[Documentation generated from TREXIO org-mode files.](https://trex-coe.github.io/trexio/)


### Miscellaneous

Note: The code should be compliant with the C99 [CERT C coding
standard](https://resources.sei.cmu.edu/downloads/secure-coding/assets/sei-cert-c-coding-standard-2016-v01.pdf). This can be checked with the `cppcheck` tool.



-----------------
![European flag](https://trex-coe.eu/sites/default/files/inline-images/euflag.jpg)
[TREX: Targeting Real Chemical Accuracy at the Exascale](https://trex-coe.eu) project has received funding from the European Union’s Horizon 2020 - Research and Innovation program - under grant agreement no. 952165. The content of this document does not represent the opinion of the European Union, and the European Union is not responsible for any use that might be made of such content.


