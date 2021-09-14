import os
import shutil
import numpy as np

from pytrexio.pytrexio import *

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
    raise ValueError ('Specify one of the supported back ends as TEST_TREXIO_BACKEND')


try:
    if TEST_TREXIO_BACKEND == 0:
        os.remove(output_filename)
    elif TEST_TREXIO_BACKEND == 1:
        shutil.rmtree(output_filename)
except:
    print ('Nothing to remove.')

#=========================================================#
#============ WRITE THE DATA IN THE TEST FILE ============#
#=========================================================#

test_file = trexio_open(output_filename, 'w', TEST_TREXIO_BACKEND)

nucleus_num = 12

rc = trexio_write_nucleus_num(test_file, nucleus_num)
assert rc==0

# initialize charge arrays as a list and convert it to numpy array
charges = [6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1.]
charges_np = np.array(charges, dtype=np.float64)

# function call below works with both lists and numpy arrays, dimension needed for memory-safety is derived 
# from the size of the list/array by SWIG using typemaps from numpy.i
rc = trexio_write_safe_nucleus_charge(test_file, charges_np)
assert rc==0

# less Python-ic way to read/write arrays using Array classes (probably more portable to other languages)
#charges = doubleArray(nucleus_num)
#for i in range(nucleus_num):
#    if i < nucleus_num/2:
#        charges[i] = 6.
#    else:
#        charges[i] = 1.
#rc = trexio_write_nucleus_charge(test_file, charges)

# initialize arrays of nuclear indices as a list and convert it to numpy array
indices = [i for i in range(nucleus_num)]
# type cast is important here because by default numpy transforms a list of integers into int64 array
indices_np = np.array(indices, dtype=np.int32)

# function call below works with both lists and numpy arrays, dimension needed for memory-safety is derived 
# from the size of the list/array by SWIG using typemacs from numpy.i
rc = trexio_write_safe_basis_nucleus_index(test_file, indices_np)
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

# safe call to read_safe array of float values
rc, rcharges_np = trexio_read_safe_nucleus_charge(test_file2, nucleus_num)
assert rc==0
assert rcharges_np.dtype is np.dtype(np.float64)
np.testing.assert_array_almost_equal(rcharges_np, charges_np, decimal=8)

# unsafe call to read_safe should not only have return code = TREXIO_UNSAFE_ARRAY_DIM
# TODO: it should not return numpy array filled with garbage
rc, rcharges_fail = trexio_read_safe_nucleus_charge(test_file2, nucleus_num*5)
assert rc==23

# less Python-ic way to read/write arrays using Array classes (probably more portable to other languages)
#charges2 = doubleArray(nucleus_num)
#for i in range(nucleus_num):
#    charges2[i] = -1.
#rc = trexio_read_nucleus_charge(test_file2, charges2)
#assert rc==0
#for i in range(nucleus_num):
#    assert charges2[i]==charges[i]

# safe call to read_safe array of int values
rc, rindices_np = trexio_read_safe_basis_nucleus_index(test_file2, nucleus_num)
assert rc==0
assert rindices_np.dtype is np.dtype(np.int32)
for i in range(nucleus_num):
    assert rindices_np[i]==indices_np[i]

# currently only low-level routines (return one long string instead of an array of strings) work
rc, labels_1d = trexio_read_nucleus_label_low(test_file2, 10)
assert rc==0

labels_2d = [label for label in labels_1d.split(TREXIO_DELIM) if label]
print('Read and parsed nuclear labels:\n', labels_2d)
for i in range(nucleus_num):
    assert labels_2d[i]==labels[i]

rc, rpoint_group = trexio_read_nucleus_point_group(test_file2, 3)
print(f'Read point group: {rpoint_group}')
assert rc==0
assert rpoint_group==point_group

rc = trexio_close(test_file2)
assert rc==0

try:
    if TEST_TREXIO_BACKEND == 0:
        os.remove(output_filename)
    elif TEST_TREXIO_BACKEND == 1:
        shutil.rmtree(output_filename)
except:
    print (f'No output file {output_filename} has been produced')

#==========================================================#

