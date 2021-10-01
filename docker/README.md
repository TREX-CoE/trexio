# Docker build

Containerized builds related to TREXIO library.

## Producing manylinux wheels for Python API

Distributing binary wheels for Python packages that rely on C extensions is a non-trivial task.
For more details, see the associated 
[PEP 425](https://www.python.org/dev/peps/pep-0425/) and 
[PEP 600](https://www.python.org/dev/peps/pep-0600/).

This issue is particularly tricky on Linux platforms. However, PyPA provides `Docker` containers
that can be used as an isolated environment to produce binary wheels that are compatible with most Linux distributions.
Such wheels should contain `manylinux` in their platform tag 
(e.g. `...-manylinux_2_24_x86_64.whl` on 64-bit Intel with `glibc >= 2.24`). 
More technical details can be found in the corresponding [GitHub repository](https://github.com/pypa/manylinux).

This section summarizes the steps needed to build `manylinux`-compatible wheels using the aforementioned containers.


### Building the Docker containers

The primary TREXIO back end at the moment is based on the [HDF5](https://portal.hdfgroup.org/display/HDF5/HDF5) library.
Because of this, one has to build new Docker images from the PyPA ones. 
These images will contain the HDF5 library and will be used to produce wheels for the Python API.

To build the Docker images on x86_64 platform, execute the following:

`cd hdf5-on-docker/ && ./build_images.sh`

This should produce several images tagged with `hdf5_1_12_` prefix and `_x86_64` suffix. 
These images inherit from the PyPA manylinux containers.
All available images can be listed using `docker image list` command.


### Building the manylinux wheels

First, make sure that you have the source code distribution 
(e.g. `trexio-0.2.0.tar.gz`) of the Python API in the current directory.
Then run one of the previously produced containers in the interactive mode using the following command:

``docker run --rm -it -e PLAT=manylinux2014_x86_64 -v `pwd`:/tmp hdf5_1_12_on_2014_x86_64 /bin/bash``

where `2014_x86_64` can be replaced with any other available platform suffix (e.g. `2010_x86_64` or `2_24_x86_64`)
The `docker run` command line arguments used here:

  - `-i` (run the docker container in interactive mode)
  - `--rm` (remove the container upon exit)
  - ``-v `pwd`:/tmp`` (mount current directory into the `tmp` directory on the container
  - `-e` (set the environment variables according to the provided list)
  - `hdf5_1_12_on_2014_x86_64` (name of the Docker image to run)
  - `/bin/bash` (which binary the container should execute)

To run the ARM-based container (e.g. with `_aarch64` suffix) on Intel/AMD processor, just add the `--platform linux/arm64` to the
`docker run` arguments. 

Once the Docker container is launched and the corresponding prompt is switched to the container, run the following (example for release 0.2.0):

`cd tmp/ && ./build_manylinux_wheels.sh trexio-0.2.0.tar.gz`

This script creates virtual envirionments for several versions of `CPython` (e.g. 3.7, 3.8, 3.9), 
installs all requirements, 
produces `trexio` wheels with conventional `linux_x86_64` tag and
repairs them to be tagged with `manylinux` using the `auditwheel` tool from PyPA

The produced wheels with the `manylinux` platfrom tag can be found in `trexio-0.2.0/wheelhouse` directory.


### Exporting the wheels

You may want to produce wheels for several versions of `glibc`. 
Prior to running a new docker container, make sure to rename/move the `wheelhouse` directory.
Otherwise, the `build_manylinux_wheels.sh` script will crush.

