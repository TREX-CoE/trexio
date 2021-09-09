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
4. Run `pip3 install .` (this installs `trexio` in your environment)
5. Run `cd test && python3 test_api.py` (this executes several tests that verify the installation)

You are ready to go!


### Examples

An interactive Jupyter notebook called `tutorial_benzene.ipynb` is provided in the `examples` directory. 
It demonstrates some basic use cases of the TREXIO library in general and of the Python API in particular.

Jupyter can be installed using `pip install jupyter`. If you are not familiar with it, feel free to consult the [Jupyter documentation](https://jupyter-notebook.readthedocs.io/en/stable/notebook.html).


#### Running the notebook

The example notebook can be launched using the following command:

`jupyter notebook tutorial_benzene.ipynb`


#### Additional steps needed to run a custom virtual environment in Jupyter notebooks

If you have installed `trexio` in a virtual environemnt called, e.g. `myvenv`, but would like to use your system-wide Jupyter installation, this is also possible.
This requires `ipykernel` python package to be installed, which usually comes together with the Jupyter installation. If this is not the case, run `pip install ipykernel`. 
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

