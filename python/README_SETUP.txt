# Additional information related to the installation of the TREXIO Python API

Removing MANIFEST.in leads to issues in the installation. In particular, the .c and .h source files do not get copied 
from the src/ directory into the tar.gz which is produced by setup sdist command. 
These source files are required to build the pytrexio.so extension module, which is needed for the Python API.

Then the following commands do the job of installing trexio in virtual environment:

$ python3 -m pip install --upgrade setuptools wheel twine
$ python3 -s setup.py --no-user-cfg build
$ python3 setup.py sdist bdist_wheel
$ python3 -m pip install dist/trexio-0.1-*.whl --force-reinstall

BUG: when trying to install trexio from tar.gz, trexio appears to be installed 
after user runs [python3 -s setup.py --no-user-cfg build] 
but before [python3 -m pip install dist/{WHEELNAME}.whl]
which leads to pip install saying that trexio is already installed but the test fails saying that _trexio was not found,
indicating that probably first installation did not go well. 
FIX: Use --force-reinstall option with pip install

The installed in virtual environment trexio can be uninstalled using [pip uninstall trexio] 
but only from the root directory where the initially used (to install) setup.py script is located. 
For example, it is most probably the python/ directory of the TREXIO_ROOT folder.

