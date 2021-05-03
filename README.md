# TREXIO

TREX library fo efficient I/O.

## Current installation procedure from the tarball (`trexio-<version>.tar.gz`):

1. `gzip -cd trexio-<version>.tar.gz | tar xvf -`
2. `cd trexio-<version>` 
3. `./configure`
4. `make && sudo make install`
5. `make check`

## Current (temporary) installation procedure from the GitHub repo clone:

1. `git clone https://github.com/TREX-CoE/trexio.git`
2. `cd trexio` 
4. `cd tools && ./build_trexio.sh && cd ..`
5. `autoreconf`
6. `automake --add-missing --copy`
7. `./configure`
8. `make && sudo make install`
9. `make check`

**Note: on systems with no `sudo` access, one can replace `./configure` with `./configure prefix=${PWD}` in order to execite `make install/uninstall` commands with `sudo` rights. This will enable the installation in the root directory of the library.**

## Tutorial

**TODO**

## Technical documentation

[Generated from TREXIO org-mode files](https://trex-coe.github.io/trexio/)

### Miscellaneous

Note: The code should be compliant with the C99 [CERT C coding
standard](https://resources.sei.cmu.edu/downloads/secure-coding/assets/sei-cert-c-coding-standard-2016-v01.pdf). This can be checked with the `cppcheck` tool.
