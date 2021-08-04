#!/bin/bash                                                    

set -x
set -e

#source version.py

python3 -m pip install --upgrade setuptools wheel twine
python3 -s setup.py --no-user-cfg build
python3 setup.py sdist bdist_wheel
python3 -m pip install dist/pytrexio-0.1-cp38-cp38-linux_x86_64.whl
#python3 -m twine upload dist/pytrexio-0.1.tar.gz

# NOTE:I get an error: 
#      Binary wheel 'pytrexio-0.1-cp38-cp38-linux_x86_64.whl' has an unsupported platform tag 'linux_x86_64'.
# when uploading the wheel instead of the tar.gz file to testpypi
# This is a well-known issue, see https://stackoverflow.com/questions/59451069/binary-wheel-cant-be-uploaded-on-pypi-using-twine

# TODO: see how SQLite does things since it-s similar to out problem in a way that the have src/ directory with C source and header files and they have master setup.py script to compile and ship it

#python3 -m twine upload --repository testpypi dist/pytrexio-0.1.tar.gz

rm -rf build dist pytrexio.egg-info
