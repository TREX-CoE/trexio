import os
import shutil

from pytrexio import *

#=========================================================#
#======== SETUP THE BACK END AND OUTPUT FILE NAME ========#
#=========================================================#

# 0: TREXIO_HDF5 ; 1: TREXIO_TEXT
TEST_TREXIO_BACKEND = 1 
OUTPUT_FILENAME_TEXT = 'test_py_swig.dir'
OUTPUT_FILENAME_HDF5 = 'test_py_swig.h5'


if TEST_TREXIO_BACKEND == 0:
    output_filename = OUTPUT_FILENAME_HDF5
elif TEST_TREXIO_BACKEND == 1:
    output_filename = OUTPUT_FILENAME_TEXT
else:
    raise ValueError ('Specify one of the supported back end as TEST_TREXIO_BACKEND')


try:
    if TEST_TREXIO_BACKEND == 0:
        os.remove(output_filename)
    if TEST_TREXIO_BACKEND == 1:
        shutil.rmtree(output_filename)
except:
    print (f'Test file {OUTPUT_FILENAME} does not exist')

#=========================================================#
#============ WRITE THE DATA IN THE TEST FILE ============#
#=========================================================#

test_file = trexio_open(output_filename, 'w', TEST_TREXIO_BACKEND)

nucleus_num = 12

rc = trexio_write_nucleus_num(test_file, nucleus_num)
assert rc==0

charges = doubleArray(nucleus_num)
for i in range(nucleus_num):
    if i < nucleus_num/2:
        charges[i] = 6.
    else:
        charges[i] = 1.

rc = trexio_write_nucleus_charge(test_file, charges)
assert rc==0

point_group = 'B3U'

rc = trexio_write_nucleus_point_group(test_file, point_group, 10)
assert rc==0

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
assert rc==0

rc = trexio_close(test_file)
assert rc==0

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
assert rc==0
for i in range(nucleus_num):
    assert charges2[i]==charges[i]

labels2 = ['' for i in range(nucleus_num)]
print(labels2)
rc = trexio_read_nucleus_label(test_file2, labels2, 10)
print(labels2)
assert rc==0
for i in range(nucleus_num):
    assert labels2[i]==labels[i]

rc = trexio_close(test_file2)
assert rc==0

#==========================================================#

