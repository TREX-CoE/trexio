import os
import shutil
import numpy as np

from pytrexio.pytrexio import *

#=========================================================#
#======== SETUP THE BACK END AND OUTPUT FILE NAME ========#
#=========================================================#

# 0: TREXIO_HDF5 ; 1: TREXIO_TEXT
TEST_TREXIO_BACKEND = 0
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

return_obj = trexio_open(output_filename, 'w', TEST_TREXIO_BACKEND)
assert return_obj is not None
if isinstance(return_obj, int):
    print(trexio_string_of_error(return_obj))
    assert return_obj==0
else:
    rc_open = return_obj[1]
    assert rc_open==0
    test_file = return_obj[0]
    assert test_file is not None

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

basis_num = 24
# initialize arrays of nuclear indices as a list and convert it to numpy array
indices = [i for i in range(basis_num)]
# type cast is important here because by default numpy transforms a list of integers into int64 array
indices_np = np.array(indices, dtype=np.int32)

# first write basis_num because it is needed to check dimensions of basis_nucleus_index in TREXIO >= 2.0.0
rc = trexio_write_basis_shell_num(test_file, basis_num)
assert rc==0

# function call below works with both lists and numpy arrays, dimension needed for memory-safety is derived
# from the size of the list/array by SWIG using typemacs from numpy.i
rc = trexio_write_safe_basis_nucleus_index(test_file, indices_np)
assert rc==0

# test writing of sparse data
rc = trexio_write_mo_num(test_file, 600)
assert rc==0

num_integrals = 100
indices = [i for i in range(num_integrals*4)]
values  = [(3.14 + float(i)) for i in range(num_integrals)]

rc = trexio_write_safe_mo_2e_int_eri(test_file, 0, num_integrals, indices, values)
assert rc==0

# test writing of single string
point_group = 'B3U'

rc = trexio_write_nucleus_point_group(test_file, point_group, 10)
assert rc==0

# test writing of array of strings
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

return_obj = trexio_open(output_filename, 'r', TEST_TREXIO_BACKEND)
assert return_obj is not None
if isinstance(return_obj, int):
    print(trexio_string_of_error(return_obj))
    assert return_obj==0
else:
    rc_open = return_obj[1]
    assert rc_open==0
    test_file2 = return_obj[0]
    assert test_file is not None

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

result = trexio_read_basis_shell_num(test_file2)
assert result[0]==0
assert result[1]==basis_num

# safe call to read_safe array of int values
rc, rindices_np = trexio_read_safe_basis_nucleus_index(test_file2, basis_num)
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

# test reasing sparse quantities
rc, mo_2e_int_size = trexio_read_mo_2e_int_eri_size(test_file2)
assert rc==0
assert mo_2e_int_size==num_integrals

buf_size = 60
offset_file = 0
# read full buf_size (i.e. the one that does not reach EOF)
rc, read_buf_size, indices_sparse_np, value_sparse_np = trexio_read_safe_mo_2e_int_eri(test_file2, offset_file, buf_size, buf_size*4, buf_size)
print(f'First complete sparse read size: {read_buf_size}')
#print(indices_sparse_np)
assert rc==0
assert read_buf_size==buf_size
assert indices_sparse_np[0]==0
assert indices_sparse_np[read_buf_size*4-1]==read_buf_size*4-1
offset_file += buf_size

# read incomplete buf_size (i.e. the one that does reach EOF)
rc, read_buf_size, indices_sparse_np, value_sparse_np = trexio_read_safe_mo_2e_int_eri(test_file2, offset_file, buf_size, buf_size*4, buf_size)
print(f'Second incomplete sparse read size: {read_buf_size}')
# Incomplete read still allocates NumPy array of buf_size=60 elements but only 40 elements read upon encounter of EOF,
# Thus the remaining 20 elements are filled with garbage rather than zeros. Handle this in the front end ?
print(indices_sparse_np)
# trexio_exit_code = 6 correspond to TREXIO_END
assert rc==6
assert read_buf_size==(num_integrals - buf_size)
assert indices_sparse_np[0]==offset_file*4
assert indices_sparse_np[read_buf_size*4-1]==(offset_file+read_buf_size)*4-1


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
