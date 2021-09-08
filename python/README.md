## TREXIO Python API

TREXIO provides a Python API for interactive calls to the library.
It allows to simplify interfacing between different codes and can 
be used to convert between different input/output file formats.


### Requirements

- python3 	(>= 3.6)
- numpy
- C compiler 	(gcc/icc)


### Installation from PyPI

Run `pip3 install trexio`

**Note:** we highly recommend to use virtual environments to avoid compatibility issues.


### Additional requirements (for installation from source)

- HDF5 library	(>= 1.8)
- pkgconfig	(TODO: CHECK THIS by installing wheels)


### Installation from source

1. Download the latest source code distribution (in `.tar.gz` format) of the TREXIO Python API
2. Unpack and `cd` in the output directory
3. Run `pip3 install -r requirements.txt` (this installs all python dependencies)
4. Run `pip3 install .` (this install `trexio` in your environment)
5. Run `cd test && python3 test_api.py` (this executes several tests that check the installation)

You are ready to go!


### Examples

An interactive Jupyter notebook called `tutorial_benzene.ipynb` can be found in the `examples` directory or on Binder (TODO: link). 
It is provided to demonstrate some basic use cases of the TREXIO library in general and the Python API in particular.


#### Additional requirements to run Jupyter notebooks with TREXIO

Jupyter can be installed using `pip install jupyter`.

If you have installed `trexio` in the virtual environemnt called, e.g. `myvenv`, make sure to also install it as a kernel for (this requires `ipykernel` python package to be installed) by executing the following:

`python3 -m ipykernel install --user --name=myvenv`


#### Running the notebook

The example notebook can be launched using the following command 

`jupyter-notebook tutorial_benzene.ipynb`

Once the notebook is open, make sure that your virtual environment is selected as the current kernel. 
If this is not the case, try the following: 

1. Press the `Kernel` button in the navigation panel
2. In the output list of options select `Change kernel`
3. Find the name of your virtual environment (e.g. `myvenv`) in the list and select it

That's it, you have activated the virtual environment and can now run the cells of the `tutorial_benzene.ipynb` notebook.

To uninstall the kernel named `myvenv` from Jupyter, execute the following:

`jupyter kernelspec uninstall myvenv

