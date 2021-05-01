# TREXIO
TREX I/O library

## Current (temporary) installation procedure:

1. `git clone https://github.com/TREX-CoE/trexio.git`
2. `cd trexio` 
4. `cd tools && ./build_trexio.sh && cd ..`
5. `autoreconf`
6. `automake --add-missing --copy`
7. `./configure prefix=${PWD}`
8. `make && make check`

Note: The code should be compliant with the C99 [CERT C coding
standard](https://resources.sei.cmu.edu/downloads/secure-coding/assets/sei-cert-c-coding-standard-2016-v01.pdf). This can be checked with the `cppcheck` tool.
