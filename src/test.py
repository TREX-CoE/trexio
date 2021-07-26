import os
import shutil

from pytrexio import *

#=========================================================#
#======== SETUP THE BACK END AND OUTPUT FILE NAME ========#
#=========================================================#

# 0: TREXIO_HDF5 ; 1: TREXIO_TEXT
TEST_TREXIO_BACKEND = TREXIO_TEXT
OUTPUT_FILENAME_TEXT = 'test_py_swig.dir'
OUTPUT_FILENAME_HDF5 = 'test_py_swig.h5'


if TEST_TREXIO_BACKEND == TREXIO_HDF5:
    output_filename = OUTPUT_FILENAME_HDF5
elif TEST_TREXIO_BACKEND == TREXIO_TEXT:
    output_filename = OUTPUT_FILENAME_TEXT
else:
    raise ValueError ('Specify one of the supported back ends as TEST_TREXIO_BACKEND')


try:
    if TEST_TREXIO_BACKEND == TREXIO_HDF5:
        os.remove(output_filename)
    elif TEST_TREXIO_BACKEND == TREXIO_TEXT:
        shutil.rmtree(output_filename)
except:
    print (f'Test file {output_filename} does not exist')

#=========================================================#
#============ WRITE THE DATA IN THE TEST FILE ============#
#=========================================================#

test_file = trexio_open(output_filename, 'w', TEST_TREXIO_BACKEND)

nucleus_num = 12

rc = trexio_write_nucleus_num(test_file, nucleus_num)
assert rc==TREXIO_SUCCESS

charges = doubleArray(nucleus_num)
for i in range(nucleus_num):
    if i < nucleus_num/2:
        charges[i] = 6.
    else:
        charges[i] = 1.

rc = trexio_write_nucleus_charge(test_file, charges)
assert rc==TREXIO_SUCCESS

point_group = 'B3U'

rc = trexio_write_nucleus_point_group(test_file, point_group, 10)
assert rc==TREXIO_SUCCESS

labels = [
        'C',
        'C',
        'C',
        'C',
        'C',
        'C',
        'H',
        'H',
        'H',
        'H',
        'H',
        'H']

rc = trexio_write_nucleus_label(test_file, labels, 10)
assert rc==TREXIO_SUCCESS

rc = trexio_close(test_file)
assert rc==TREXIO_SUCCESS

#==========================================================#
#============ READ THE DATA FROM THE TEST FILE ============#
#==========================================================#

test_file2 = trexio_open(output_filename, 'r', TEST_TREXIO_BACKEND)

result = trexio_read_nucleus_num(test_file2)
assert result[0]==0
assert result[1]==nucleus_num
#print(result)

charges2 = doubleArray(nucleus_num)
for i in range(nucleus_num):
    charges2[i] = -1.

rc = trexio_read_nucleus_charge(test_file2, charges2)
assert rc==TREXIO_SUCCESS
for i in range(nucleus_num):
    assert charges2[i]==charges[i]

# [WIP]: ideally, the list of strings should be returned as below
#rc, label_2d = trexio_read_nucleus_label(test_file2, 10)
# [WIP]: currently only low-level routines (return one long string instead of an array of strings) work
rc, labels_1d = trexio_read_nucleus_label_low(test_file2, 10)
assert rc==TREXIO_SUCCESS

labels_2d = [label for label in labels_1d.split(TREXIO_DELIM) if label]
print(labels_2d)
for i in range(nucleus_num):
    assert labels_2d[i]==labels[i]

rc = trexio_close(test_file2)
assert rc==TREXIO_SUCCESS

#==========================================================#

