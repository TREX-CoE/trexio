import os
import shutil
import numpy as np

import trexio as tr

#=========================================================#
#======== SETUP THE BACK END AND OUTPUT FILE NAME ========#
#=========================================================#

# 0: TREXIO_HDF5 ; 1: TREXIO_TEXT
TEST_TREXIO_BACKEND = tr.TREXIO_TEXT
OUTPUT_FILENAME_TEXT = 'test_py_swig.dir'
OUTPUT_FILENAME_HDF5 = 'test_py_swig.h5'


if TEST_TREXIO_BACKEND == tr.TREXIO_HDF5:
    output_filename = OUTPUT_FILENAME_HDF5
elif TEST_TREXIO_BACKEND == tr.TREXIO_TEXT:
    output_filename = OUTPUT_FILENAME_TEXT
else:
    raise ValueError ('Specify one of the supported back ends as TEST_TREXIO_BACKEND')


try:
    if TEST_TREXIO_BACKEND == tr.TREXIO_HDF5:
        os.remove(output_filename)
    elif TEST_TREXIO_BACKEND == tr.TREXIO_TEXT:
        shutil.rmtree(output_filename)
except:
    print ('Nothing to remove.')

#=========================================================#
#============ WRITE THE DATA IN THE TEST FILE ============#
#=========================================================#

test_file = tr.open(output_filename, 'w', TEST_TREXIO_BACKEND)

print(test_file)

nucleus_num = 12

tr.write_nucleus_num(test_file, nucleus_num)

# initialize charge arrays as a list and convert it to numpy array
charges = [6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1.]
charges_np = np.array(charges, dtype=np.float64)

# function call below works with both lists and numpy arrays, dimension needed for memory-safety is derived 
# from the size of the list/array by SWIG using typemaps from numpy.i
rc = tr.write_safe_nucleus_charge(test_file, charges_np)

# initialize arrays of nuclear indices as a list and convert it to numpy array
indices = [i for i in range(nucleus_num)]
# type cast is important here because by default numpy transforms a list of integers into int64 array
indices_np = np.array(indices, dtype=np.int32)

# function call below works with both lists and numpy arrays, dimension needed for memory-safety is derived 
# from the size of the list/array by SWIG using typemacs from numpy.i
tr.write_safe_basis_nucleus_index(test_file, indices_np)

point_group = 'B3U'

tr.write_nucleus_point_group(test_file, point_group)

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

tr.write_nucleus_label(test_file,labels)

tr.close(test_file)

#==========================================================#
#============ READ THE DATA FROM THE TEST FILE ============#
#==========================================================#

test_file2 = tr.open(output_filename, 'r', TEST_TREXIO_BACKEND)

rnum = tr.read_nucleus_num(test_file2)
assert rnum==nucleus_num

# safe call to read_safe array of float values
rcharges_np = tr.read_safe_nucleus_charge(test_file2, nucleus_num)
assert rcharges_np.dtype is np.dtype(np.float64)
np.testing.assert_array_almost_equal(rcharges_np, charges_np, decimal=8)

# unsafe call to read_safe should fail with error message corresponding to TREXIO_UNSAFE_ARRAY_DIM
try:
    rcharges_fail = tr.read_safe_nucleus_charge(test_file2, nucleus_num*5)
except Exception:
    print("Unsafe call to safe API: successful")

# safe call to read_safe array of int values
rindices_np = tr.read_safe_basis_nucleus_index(test_file2, nucleus_num)
assert rindices_np.dtype is np.dtype(np.int32)
for i in range(nucleus_num):
    assert rindices_np[i]==indices_np[i]

rlabels_2d = tr.read_nucleus_label(test_file2)
print(rlabels_2d)
for i in range(nucleus_num):
    assert rlabels_2d[i]==labels[i]

rpoint_group = tr.read_nucleus_point_group(test_file2)
print(rpoint_group)
assert rpoint_group==point_group 

tr.close(test_file2)

try:
    if TEST_TREXIO_BACKEND == tr.TREXIO_HDF5:
        os.remove(output_filename)
    elif TEST_TREXIO_BACKEND == tr.TREXIO_TEXT:
        shutil.rmtree(output_filename)
except:
    print (f'No output file {output_filename} has been produced')

#==========================================================#

