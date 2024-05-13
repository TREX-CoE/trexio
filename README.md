# TREXIO

<img src="https://trex-coe.eu/sites/default/files/styles/responsive_no_crop/public/2022-01/TREXIO%20Code.png" width=200>

[![build](https://github.com/TREX-CoE/trexio/actions/workflows/actions.yml/badge.svg)](https://github.com/TREX-CoE/trexio/actions/workflows/actions.yml)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/TREX-CoE/trexio)

TREXIO is an open-source file format and library developed for the storage and
manipulation of data produced by quantum chemistry calculations. It is designed
with the goal of providing a reliable and efficient method of storing and
exchanging wave function parameters and matrix elements. The library consists
of a front-end implemented in the C programming language and two different
back-ends: a text back-end and a binary back-end utilizing the HDF5 library
which enables fast read and write operations. It is compatible with a variety
of platforms and has interfaces for the Fortran, Python, OCaml and Rust
programming languages.

* [TREXIO](#trexio)
   * [Installation](#installation)
      * [Installation using a package manager](#installation-using-a-package-manager)
         * [Conda](#conda)
         * [Spack](#spack)
         * [Guix](#guix)
         * [Debian/Ubuntu](#debianubuntu)
      * [Installation from source](#installation-from-source)
         * [Minimal requirements (for users):](#minimal-requirements-for-users)
         * [Recommended: Installation from the release tarball](#recommended-installation-from-the-release-tarball)
         * [Compilation without the HDF5 library](#compilation-without-the-hdf5-library)
         * [For TREXIO developers: from the GitHub repo clone](#for-trexio-developers-from-the-github-repo-clone)
         * [Using CMake instead of Autotools](#using-cmake-instead-of-autotools)
   * [Using TREXIO](#using-trexio)
      * [Naming convention](#naming-convention)
      * [Tutorial](#tutorial)
      * [Documentation](#documentation)
      * [Linking to your program](#linking-to-your-program)
      * [Distributing TREXIO with your code](#distributing-trexio-with-your-code)
   * [APIs for other languages](#apis-for-other-languages)
      * [Python](#python)
      * [Rust](#rust)
      * [OCaml](#ocaml)
   * [Citation](#citation)
      * [Miscellaneous](#miscellaneous)


## Installation
### Installation using a package manager
#### Conda

[![Anaconda-Server Badge](https://anaconda.org/conda-forge/trexio/badges/version.svg)](https://anaconda.org/conda-forge/trexio)
[![Anaconda-Server Badge](https://anaconda.org/conda-forge/trexio/badges/platforms.svg)](https://anaconda.org/conda-forge/trexio)

The official releases of TREXIO `>2.0.0` are also available via the `conda-forge` channel.
The pre-compiled stable binaries of `trexio` can be installed as follows:

```
conda install -c conda-forge trexio
```

More details can be found in the corresponding [trexio-feedstock](https://github.com/conda-forge/trexio-feedstock).
Note that both parallel (see `mpi_openmpi` prefix) and serial (`nompi`) variants are provided.

#### Spack

The official releases `>=2.0.0` and the development version of TREXIO can be installed using the
[Spack](https://spack.io/) package manager.
The [trexio/package.py](https://github.com/spack/spack/blob/develop/var/spack/repos/builtin/packages/trexio/package.py)
file contains the Spack specifications required to build different variants of `trexio` library.
It can be installed as follows

```
spack install --jobs `getconf _NPROCESSORS_ONLN` trexio
```

#### Guix

The official releases of TREXIO `>=2.0.0` can be installed using the
[GNU Guix](https://guix.gnu.org) functional package manager.
The [trexio.scm](https://github.com/TREX-CoE/trexio/blob/master/tools/trexio.scm)
Schema file contains the manifest specification for the `trexio` package.
It can be installed as follows:

```
guix package --cores=`getconf _NPROCESSORS_ONLN` --install-from-file=trexio.scm
```

#### Debian/Ubuntu

The official release of TREXIO `2.2.0` is available as a Debian (`.deb`) package thanks to the [Debichem Team](https://wiki.debian.org/Debichem).
The source code is hosted [here](https://salsa.debian.org/debichem-team/libtrexio) and
the pre-built binary files are available via the [Debian package registry](https://packages.debian.org/bookworm/libtrexio-dev).

TREXIO is also available on [Ubuntu 23.04 (Lunar Lobster)](https://packages.ubuntu.com/lunar/libtrexio-dev) and newer and can be installed as follows:

```
sudo apt-get update && sudo apt-get install libtrexio-dev
```

### Installation from source
#### Minimal requirements (for users):

- Autotools             (autoconf >= 2.69, automake >= 1.11, libtool >= 2.2) or CMake (>= 3.16)
- C compiler            (gcc/icc/clang)
- Fortran compiler      (gfortran/ifort)
- HDF5 library          (>= 1.8) [optional, recommended for high performance]


#### Recommended: Installation from the release tarball

1. Download the `trexio-<version>.tar.gz` file from the GitHub release page
2. `gzip -cd trexio-<version>.tar.gz | tar xvf -`
3. `cd trexio-<version>`
4. `./configure`
5. ```make -j 4 ```
6. ```make -j 4 check```
7. `sudo make install`

In environments where `sudo` access is unavailable, a common workaround for
executing `make install/uninstall` commands without requiring superuser
privileges involves a modification to the `./configure` command.
This modification typically includes specifying an installation prefix within
the user's home directory to circumvent the need for system-wide installation
permissions. For instance, `./configure prefix=$HOME/.local` can be employed,
where `$HOME/.local` is often recommended for user-space software installations.
However, this is merely a suggestion, and users are free to choose any suitable
directory as their installation prefix, depending on their specific
requirements and system configurations.

Regarding the integration with an MPI (Message Passing Interface) enabled HDF5
library, it's typical to specify the MPI compiler wrapper for the C compiler.
This is done by appending a directive like `CC=mpicc` to the `./configure`
command. However, as TREXIO does not utilize MPI features, it is advisable to
link against a non-MPI (serial) version of the HDF5 library for the sake of
simplicity.

#### Compilation without the HDF5 library

By default, the configuration step proceeds to search for the [HDF5 library](https://portal.hdfgroup.org/display/HDF5/HDF5).
This search can be disabled if HDF5 is not present/installable on the user machine.
To build TREXIO without HDF5 back end, append `--without-hdf5` option to `configure` script or `-DENABLE_HDF5=OFF` option to `cmake`. For example,

- `./configure --without-hdf5`
- `cmake -S. -Bbuild -DENABLE_HDF5=OFF`

#### For TREXIO developers: from the GitHub repo clone

Additional requirements:

- Python3       (>= 3.6)
- Emacs         (>= 26.0)
- SWIG          (>= 4.0)   [required for the Python API]

**Note:** The source code is auto-generated from the Emacs org-mode (`.org`) files following the literate programming approach. This is why the `src` directory is initially empty.

1. `git clone https://github.com/TREX-CoE/trexio.git`
2. `cd trexio`
3. `./autogen.sh`
4. `./configure`
5. ```make -j 4```
6. ```make -j 4 check```
7. `sudo make install`

#### Using CMake instead of Autotools

The aforementioned instructions rely on [Autotools](https://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html) build system.
[CMake](https://cmake.org) users can achieve the same with the following steps (an example of out-of-source build):

1. `cmake -S. -Bbuild`
2. `cd build`
3. ```make -j 4```
4. ```ctest -j 4```
5. `sudo make install`

**Note**: on systems with no `sudo` access, one can add `-DCMAKE_INSTALL_PREFIX=build` as an argument to the `cmake` command so that `make install/uninstall` can be run without `sudo` privileges.

**Note**: when linking against an MPI-enabled HDF5 library one usually has to specify the MPI wrapper for the C compiler by adding, e.g., `-DCMAKE_C_COMPILER=mpicc` to the `cmake` command.

## Using TREXIO
### Naming convention

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


### Tutorial

TREXIO tutorials in Jupyter notebook format can be found in the
[corresponding GitHub repository](https://github.com/TREX-CoE/trexio-tutorials)
or on [Binder](https://mybinder.org/v2/gh/TREX-CoE/trexio-tutorials/HEAD).

For example, the tutorial covering TREXIO basics using benzene molecule as an example can be viewed and executed online by clicking on this badge:
[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/TREX-CoE/trexio-tutorials/HEAD?filepath=notebooks%2Ftutorial_benzene.ipynb)


### Documentation

[Documentation generated from TREXIO org-mode files.](https://trex-coe.github.io/trexio/)


### Linking to your program

The `make install` command takes care of installing the TREXIO shared library on the user machine.
After installation, append `-ltrexio` to the list of compiler  (`$LIBS`) options.

In some cases (e.g. when using custom installation prefix during configuration), the TREXIO library might end up installed in a directory, which is absent in the default `$LD_LIBRARY_PATH`.
In order to link the program against TREXIO, the search path can be modified as follows:

`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<path_to_trexio>/lib`

where the `<path_to_trexio>` has to be replaced by the prefix used during the installation.

If your project relies on CMake build system, feel free to use the
[FindTREXIO.cmake](https://github.com/TREX-CoE/trexio/blob/master/cmake/FindTREXIO.cmake)
module to find and link TREXIO library automatically.

In Fortran applications, make sure that the `trexio_f.f90` module file is included in the source tree.
You might have to manually copy it into your program source directory.
The `trexio_f.f90` module file can be found in the `include/` directory of the TREXIO source code distribution.

**Note:** there is no need to include `trexio.h` header file during compilation of Fortran programs.
Only the installed library and the Fortran module file are required.


### Distributing TREXIO with your code

The TREXIO software is distributed under the 3-clause BSD license, renowned for
its permissiveness. Consequently, it is entirely acceptable for you to
provide the TREXIO release tarball in conjunction with your own code.
Should you opt to include TREXIO with your software, it is recommended to
distribute the release tarball, instead of the content of the git repository.
The release tarballs contain pre-generated source files. This not only
accelerates the compilation process but also significantly reduces dependency
requirements.

## APIs for other languages
### Python

[![PyPI version](https://badge.fury.io/py/trexio.svg)](https://badge.fury.io/py/trexio)

For more details regarding the installation and usage of the TREXIO Python API,
see [this page](python/README.md).

The aforementioned instructions are adapted for users installing from the source code distribution (periodically updated).
In order to install the Python API with the latest changes, follow the developer installation guide and run the following command in the end

```
make python-install
```

**Note: this implies that SWIG is installed and available.**

We rely on the `pytest` package for unit testing. It can be installed via `pip install pytest`. To test the installation, run

```
make python-test
```

We highly recommend to use virtual environments to avoid compatibility issues and to improve reproducibility.


### Rust

The Rust API is available on Crates.io, so you can simply run
```
cargo add trexio
```
to your Rust project.

If you prefer to install the Rust API provided with this repository:
```
cargo add --path /path/to/trexio/rust/trexio
```

### OCaml

The TREXIO OCaml API is available in OPAM:
```
opam install trexio
```

If you prefer to install it from this repository,

```
cd ocaml/trexio
make
opam install .
```

## Citation

The journal article reference describing TREXIO can be cited as follows:

```
@article{10.1063/5.0148161,
    author = {Posenitskiy, Evgeny and Chilkuri, Vijay Gopal and Ammar, Abdallah and Hapka, Michał and Pernal, Katarzyna and Shinde, Ravindra and Landinez Borda, Edgar Josué and Filippi, Claudia and Nakano, Kosuke and Kohulák, Otto and Sorella, Sandro and de Oliveira Castro, Pablo and Jalby, William and Ríos, Pablo López and Alavi, Ali and Scemama, Anthony},
    title = "{TREXIO: A file format and library for quantum chemistry}",
    journal = {The Journal of Chemical Physics},
    volume = {158},
    number = {17},
    year = {2023},
    month = {05},
    issn = {0021-9606},
    doi = {10.1063/5.0148161},
    url = {https://doi.org/10.1063/5.0148161},
    note = {174801},
    eprint = {https://pubs.aip.org/aip/jcp/article-pdf/doi/10.1063/5.0148161/17355866/174801\_1\_5.0148161.pdf},
}
```

Journal paper: [![doi](https://img.shields.io/badge/doi-10.1063/5.0148161-5077AB.svg)](https://doi.org/10.1063/5.0148161)

ArXiv paper: [![arXiv](https://img.shields.io/badge/arXiv-2302.14793-b31b1b.svg)](https://arxiv.org/abs/2302.14793)

### Miscellaneous

The code should be compliant with the C99
[CERT C coding standard](https://resources.sei.cmu.edu/downloads/secure-coding/assets/sei-cert-c-coding-standard-2016-v01.pdf).
This can be checked with the `cppcheck` tool.

If you loaded an HDF5 module and the configure script can't find the HDF5 library,
it is probably because the path to the HDF5 library is missing from your `$LIBRARY_PATH`
variable. It happens that when building the HDF5 modules, the system
administrators only append the path to the libraries to the `$LD_LIBRARY_PATH`
variable, but forget to append it also to `$LIBRARY_PATH`, which is required
for linking. A simple workaround for the user is to do

```
export LIBRARY_PATH=$LD_LIBRARY_PATH
```

before running `configure`, but it is preferable to inform the system administators
of the problem.


-----------------
![European flag](https://trex-coe.eu/sites/default/files/inline-images/euflag.jpg)
[TREX: Targeting Real Chemical Accuracy at the Exascale](https://trex-coe.eu) project has received funding from the European Union’s Horizon 2020 - Research and Innovation program - under grant agreement no. 952165. The content of this document does not represent the opinion of the European Union, and the European Union is not responsible for any use that might be made of such content.
