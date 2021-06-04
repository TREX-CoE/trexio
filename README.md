# TREXIO

TREX library fo efficient I/O.


## Minimal requirements (for users):

- Autoconf
- C compiler		(gcc/icc/clang)
- Fortran compiler 	(gfortran/ifort/flang)


## Installation procedure from the tarball (for users):

1. Download the `trexio-<version>.tar.gz` file
2. `gzip -cd trexio-<version>.tar.gz | tar xvf -`
3. `cd trexio-<version>`
4. `./configure`
5. `make`
6. `make check`
7. `sudo make install`


**Note: on systems with no `sudo` rights access, one can replace `./configure` with `./configure prefix=${PWD}` in order to execute `make install/uninstall` commands without `sudo`. This will enable the installation in the root directory of the library.**


## Additional requirements (for developers):

- Automake
- python3 	(>=3.6)
- Emacs		(>=26.0)


## Installation procedure from the GitHub repo clone (for developers):

1. `git clone https://github.com/TREX-CoE/trexio.git`
2. `cd trexio`
3. `./autogen.sh`
4. `./configure`
5. `make`
6. `make check`
7. `sudo make install`


## Tutorial

**TODO**


## Technical documentation

[Documentation generated from TREXIO org-mode files](https://trex-coe.github.io/trexio/)


### Miscellaneous

Note: The code should be compliant with the C99 [CERT C coding
standard](https://resources.sei.cmu.edu/downloads/secure-coding/assets/sei-cert-c-coding-standard-2016-v01.pdf). This can be checked with the `cppcheck` tool.


