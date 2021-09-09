## TREXIO Python API

TREXIO provides a Python API, which enables interactive calls to the library.
It facilitates the development of interfaces between different codes and 
can be used to convert data from one input/output file format into another.


### Requirements

- python3 	(>= 3.6)
- numpy
- C compiler 	(gcc/icc)


### Installation from PyPI

Run `pip3 install trexio`

**Note: we highly recommend to use virtual environments to avoid compatibility issues.** 
For more details, see the corresponding part of the [Python documentation](https://docs.python.org/3/library/venv.html#creating-virtual-environments).


### Additional requirements (for installation from source)

- HDF5 library	(>= 1.8)
- pkgconfig	(TODO: CHECK THIS by installing wheels)


### Installation from source

1. Download the latest source code distribution (in `.tar.gz` format) of the TREXIO Python API
2. Unpack and `cd` in the output directory
3. Run `pip3 install -r requirements.txt` (this installs all python dependencies)
4. Export custom environment variables needed for the installation. Steps 1 and 2 can be skipped if HDF5 is properly configured for `pkg-config` (i.e. if executing `pkg-config --libs hdf5` returns a list of options).
   1. `export H5_CFLAGS=-I/path/to/hdf5/include`
   2. `export H5_LDFLAGS=-L/path/to/hdf5/lib`
   3. `source tools/set_NUMPY_INCLUDEDIR.sh`
5. Run `pip3 install .` (this installs `trexio` in your environment)
6. Run `cd test && python3 test_api.py` (this executes several tests that verify the installation)

You are ready to go!


### Examples

An interactive Jupyter notebook called `tutorial_benzene.ipynb` is provided in the `examples` directory. 
It demonstrates some basic use cases of the TREXIO library in general and of the Python API in particular.

Jupyter can be installed using `pip install jupyter`. If you are not familiar with it, feel free to consult the [Jupyter documentation](https://jupyter-notebook.readthedocs.io/en/stable/notebook.html).


#### Running the notebook

The example notebook can be launched using the following command:

`jupyter notebook tutorial_benzene.ipynb`


#### Additional steps needed to run a custom virtual environment in Jupyter notebooks

In some cases, it may happen that the Jupyter kernels in the activated virtual environment (e.g. `myvenv`) still point to the system-wide python binaries and not to the environment ones.
This will result in `ImportError` when importing `trexio` in the notebook cell. In order to avoid this, the `myvenv` has to be installed as an additional kernel.
This requires `ipykernel` python package, which usually comes together with the Jupyter installation. If this is not the case, run `pip install ipykernel`. 
You can install `myvenv` as a kernel by executing the following command:

`python3 -m ipykernel install --user --name=myvenv`

Now you can launch a Jupyter notebook. Once it is open, make sure that your virtual environment is selected as the current kernel. 
If this is not the case, try this:

1. Press the `Kernel` button in the navigation panel
2. In the output list of options select `Change kernel`
3. Find the name of your virtual environment (e.g. `myvenv`) in the list and select it

That's it, you have activated the custom virtual environment called `myvenv` in your notebook.

To uninstall the kernel named `myvenv`, execute the following command:

`jupyter kernelspec uninstall myvenv`

