#!/usr/bin/env python3

import numpy as np
import pytest
import trexio
from benzene_data import *


# this function is copied from the trexio-tools github repository (BSD-3 license):
# https://github.com/TREX-CoE/trexio_tools/blob/master/src/trexio_tools/group_tools/determinant.py
def to_determinant_list(orbital_list: list, int64_num: int) -> list:
    """
    Convert a list of occupied orbitals from the `orbital_list`
    into a list of Slater determinants (in their bit string representation).

    Orbitals in the `orbital_list` should be 0-based, namely the lowest orbital has index 0, not 1.

    int64_num is the number of 64-bit integers needed to represent a Slater determinant bit string.
    It depends on the number of molecular orbitals as follows: int64_num = int((mo_num-1)/64) + 1
    """

    if not isinstance(orbital_list, list):
        raise TypeError(f"orbital_list should be a list, not {type(orbital_list)}")

    det_list = []
    bitfield = 0
    shift    = 0

    # since orbital indices are 0-based but the code below works for 1-based --> increment the input indices by +1
    orb_list_upshifted = [ orb+1 for orb in orbital_list]

    # orbital list has to be sorted in increasing order for the bitfields to be set correctly
    orb_list_sorted = sorted(orb_list_upshifted)

    for orb in orb_list_sorted:

        if orb-shift > 64:
            # this removes the 0 bit from the beginning of the bitfield
            bitfield = bitfield >> 1
            # append a bitfield to the list
            det_list.append(bitfield)
            bitfield = 0

        modulo = int((orb-1)/64)
        shift  = modulo*64
        bitfield |= (1 << (orb-shift))

    # this removes the 0 bit from the beginning of the bitfield
    bitfield = bitfield >> 1
    det_list.append(bitfield)
    #print('Popcounts: ', [bin(d).count('1') for d in det_list)
    #print('Bitfields: ', [bin(d) for d in det_list])

    bitfield_num = len(det_list)
    if bitfield_num > int64_num:
        raise Exception(f'Number of bitfields {bitfield_num} cannot be more than the int64_num {int64_num}.')
    if bitfield_num < int64_num:
        for _ in range(int64_num - bitfield_num):
            print("Appending an empty bitfield.")
            det_list.append(0)

    return det_list


def clean(back_end, filename):
    """Remove test files."""
    if back_end == trexio.TREXIO_HDF5:
        import os
        try:
            os.remove(filename)
            os.remove('unsafe_' + filename)
        except FileNotFoundError:
            pass
    else:
        import shutil
        try:
            shutil.rmtree(filename)
            shutil.rmtree('unsafe_' + filename)
        except FileNotFoundError:
            pass


def test_info():
    """Print the output of the trexio.info function."""
    trexio.info()


def test_void():
    """Check raise of an error upon I/O on non-existing file."""
    with pytest.raises(trexio.Error):
        _ = trexio.File('void.file', 'r', trexio.TREXIO_TEXT)


def test_orbital_list():
    """Convert one determinant into a list of orbitals."""
    orb_list_up, orb_list_dn = trexio.to_orbital_list_up_dn(int64_num, det_test)
    assert orb_list_up[0] == 0
    assert orb_list_dn[0] == 1


def test_bitfield_list():
    """Convert lists of occupied up- and down-spin orbitals into determinants."""
    # convert det_test list into a numpy array for .all() assertion to work
    det_test_np = np.array(det_test, dtype=np.int64)

    det_list_up = trexio.to_bitfield_list(int64_num, orb_up_test)
    assert (det_list_up == det_test_np[:int64_num]).all()
    det_list_dn = trexio.to_bitfield_list(int64_num, orb_dn_test)
    assert (det_list_dn == det_test_np[int64_num:]).all()


class TestIO:
    """Unit tests for writing/reading different blocks of the TREXIO file."""

    @pytest.fixture(autouse=True)
    def setup(self, backend):
        self.mode      = 'w'
        self.test_file = None
        if backend == 'hdf5':
            self.back_end = trexio.TREXIO_HDF5
            self.filename = 'test_file_py.h5'
        elif backend == 'text':
            self.back_end = trexio.TREXIO_TEXT
            self.filename = 'test_file_py.dir'
        else:
            raise ValueError("Wrong TREXIO back-end supplied to pytest.")


    def test_clean(self):
        """Clean existing files."""
        clean(self.back_end, self.filename)


    #def __del__(self):
    #    """Class destructor."""
    #    if self.test_file:
    #        if self.test_file.isOpen:
    #            self.test_file.close()
    def open(self, filename=None, mode=None, back_end=None):
        """Create a TREXIO file and open it for writing."""
        if not filename:
            filename = self.filename
        else:
            self.filename = filename
        if not mode:
            mode = self.mode
        else:
            self.mode = mode
        if not back_end:
            back_end = self.back_end
        else:
            self.back_end = back_end

        self.test_file = trexio.File(filename, mode, back_end)
        assert self.test_file.exists


    def test_close(self):
        """Close the file."""
        self.open()
        if self.test_file.isOpen:
            self.test_file.close()
        assert not self.test_file.isOpen


    def test_errors(self):
        """Test some exceptions based on trexio.Error class."""
        self.open(filename='unsafe_' + self.filename, mode='w', back_end=self.back_end)
        # try to write a negative number (should raise an error)
        with pytest.raises(trexio.Error):
            trexio.write_nucleus_num(self.test_file, -100)

        trexio.write_nucleus_num(self.test_file, nucleus_num)

        # try to overwrite a number (should raise an error)
        with pytest.raises(trexio.Error):
            trexio.write_nucleus_num(self.test_file, nucleus_num * 2)

        if self.test_file.isOpen:
            self.test_file.close()


    def test_num(self):
        """Write a number."""
        self.open()
        trexio.write_nucleus_num(self.test_file, nucleus_num)
        assert trexio.has_nucleus_num(self.test_file)
        if self.test_file.isOpen:
            self.test_file.close()


    def test_str(self):
        """Write a string."""
        self.open()
        trexio.write_nucleus_point_group(self.test_file, point_group)
        assert trexio.has_nucleus_point_group(self.test_file)
        if self.test_file.isOpen:
            self.test_file.close()


    def test_array_str(self):
        """Write an array of strings."""
        self.open()
        if not trexio.has_nucleus_num(self.test_file):
            self.test_num()
        trexio.write_nucleus_label(self.test_file, nucleus_label)
        assert trexio.has_nucleus_label(self.test_file)
        if self.test_file.isOpen:
            self.test_file.close()


    def test_array_1D(self):
        """Write array of charges."""
        self.open()
        if not trexio.has_nucleus_num(self.test_file):
            self.test_num()
        trexio.write_nucleus_charge(self.test_file, nucleus_charge)
        assert trexio.has_nucleus_charge(self.test_file)
        if self.test_file.isOpen:
            self.test_file.close()


    def test_array_2D(self):
        """Write array of coordinates."""
        self.open()
        if not trexio.has_nucleus_num(self.test_file):
            self.test_num()
        trexio.write_nucleus_coord(self.test_file, nucleus_coord)
        assert trexio.has_nucleus_coord(self.test_file)
        if self.test_file.isOpen:
            self.test_file.close()


    def test_indices(self):
        """Write array of indices."""
        self.open()
        # type cast is important here because by default numpy transforms a list of integers into int64 array
        indices_np = np.array(nucleus_index, dtype=np.int64)
        # first write basis_shell_num because it is needed to check dimensions of basis_nucleus_index
        trexio.write_basis_shell_num(self.test_file, basis_shell_num)
        # now write the indices
        trexio.write_basis_nucleus_index(self.test_file, indices_np)
        assert trexio.has_basis_nucleus_index(self.test_file)
        if self.test_file.isOpen:
            self.test_file.close()


    def test_sparse(self):
        """Write a sparse array."""
        self.open()
        # write ao_num (needed later to write sparse ao_2e_int_eri integrals)
        trexio.write_ao_num(self.test_file, ao_num)
        # one complete write (no chunking)
        offset = 0
        trexio.write_ao_2e_int_eri(self.test_file, offset, num_integrals, indices, values)
        assert trexio.has_ao_2e_int_eri(self.test_file)
        if self.test_file.isOpen:
            self.test_file.close()


    def test_determinant(self):
        """Write CI determinants and coefficients."""
        self.open()
        # write mo_num (needed later to write determinants)
        MO_NUM_TEST = 100
        trexio.write_mo_num(self.test_file, MO_NUM_TEST)
        # get the number of bit-strings per spin component
        INT64_NUM_TEST = int((MO_NUM_TEST-1)/64) + 1
        int_num = trexio.get_int64_num(self.test_file)
        assert int_num == INT64_NUM_TEST
        # write the number of up and down electrons
        trexio.write_electron_up_num(self.test_file, 4)
        trexio.write_electron_dn_num(self.test_file, 3)
        # orbital lists
        orb_list_up = [0,1,2,3]
        orb_list_dn = [0,1,2]

        # data to write
        DET_NUM_TEST = 100
        det_up = to_determinant_list(orb_list_up, INT64_NUM_TEST)
        det_dn = to_determinant_list(orb_list_dn, INT64_NUM_TEST)

        det_list = []
        coeff_list = []
        for i in range(DET_NUM_TEST):
            det_list.append(det_up + det_dn)
            coeff_list.append(3.14 + float(i))

        # write the data for the ground state
        offset = 0
        trexio.write_state_id(self.test_file, 0)
        trexio.write_determinant_list(self.test_file, offset, DET_NUM_TEST, det_list)
        assert trexio.has_determinant_list(self.test_file)
        trexio.write_determinant_coefficient(self.test_file, offset, DET_NUM_TEST, coeff_list)
        assert trexio.has_determinant_coefficient(self.test_file)
        # manually check the consistency between coefficient_size and number of determinants
        assert trexio.read_determinant_coefficient_size(self.test_file) == trexio.read_determinant_num(self.test_file)
        if self.test_file.isOpen:
            self.test_file.close()


    def test_delete_group(self):
        """Delete a group."""
        self.open(filename='unsafe_' + self.filename, mode='u', back_end=self.back_end)

        trexio.write_nucleus_num(self.test_file, nucleus_num)
        trexio.write_nucleus_charge(self.test_file, nucleus_charge)
        trexio.flush(self.test_file)

        assert trexio.has_nucleus_num(self.test_file)
        assert trexio.has_nucleus_charge(self.test_file)
        assert trexio.has_nucleus(self.test_file)

        trexio.delete_nucleus(self.test_file)

        assert not trexio.has_nucleus_num(self.test_file)
        assert not trexio.has_nucleus_charge(self.test_file)
        assert not trexio.has_nucleus(self.test_file)

        if self.test_file.isOpen:
            self.test_file.close()


    def test_has_group(self):
        """Check existense of a group."""
        self.open()
        assert trexio.has_nucleus(self.test_file)
        assert not trexio.has_rdm(self.test_file)
        if self.test_file.isOpen:
            self.test_file.close()


    def test_context_manager(self):
        """Test the with ... as ... context handling."""
        with trexio.File(filename=self.filename, mode='u', back_end=self.back_end) as tfile:
            trexio.write_metadata_description(tfile, 'Test file produced by the Python API')
            assert trexio.has_metadata_description(tfile)
            assert tfile.isOpen
        # the file handle can remain existing but the file itself is closed upon exit from the `with` block
        assert not tfile.isOpen


    def test_read_num(self):
        """Read a number."""
        self.open(mode='r')
        num_r = trexio.read_nucleus_num(self.test_file)
        assert num_r == nucleus_num
        if self.test_file.isOpen:
            self.test_file.close()


    def test_read_array_1D(self):
        """Read an array."""
        self.open(mode='r')
        charges_np_r = trexio.read_nucleus_charge(self.test_file)
        assert charges_np_r.dtype is np.dtype(np.float64)
        assert charges_np_r.size == nucleus_num
        np.testing.assert_array_almost_equal(charges_np_r, np.array(nucleus_charge), decimal=8)
        if self.test_file.isOpen:
            self.test_file.close()


    def test_read_array_2D(self):
        """Read an array."""
        self.open(mode='r')
        # read nuclear coordinates without providing optional argument dim
        coords_np = trexio.read_nucleus_coord(self.test_file)
        assert coords_np.dtype is np.dtype(np.float64)
        assert coords_np.size == nucleus_num * 3
        np.testing.assert_array_almost_equal(coords_np, np.array(nucleus_coord).reshape(nucleus_num,3), decimal=8)
        if self.test_file.isOpen:
            self.test_file.close()


    def test_read_errors(self):
        """Test some reading errors."""
        self.open(mode='r')
        # unsafe call to read_safe should fail with error message corresponding to TREXIO_UNSAFE_ARRAY_DIM
        with pytest.raises(trexio.Error):
            _ = trexio.read_nucleus_charge(self.test_file, dim=nucleus_num/2)
        if self.test_file.isOpen:
            self.test_file.close()


    def test_read_integers(self):
        """Read some integer arrays."""
        self.open(mode='r')

        indices_np_16 = trexio.read_basis_nucleus_index(self.test_file, dtype=np.int16)
        assert indices_np_16.dtype is np.dtype(np.int16)
        assert (indices_np_16 == np.array(nucleus_index)).all()

        indices_np_32 = trexio.read_basis_nucleus_index(self.test_file, dtype=np.int32)
        assert indices_np_32.dtype is np.dtype(np.int32)
        assert (indices_np_32 == np.array(nucleus_index)).all()

        indices_np_64 = trexio.read_basis_nucleus_index(self.test_file)
        assert indices_np_64.dtype is np.dtype(np.int64)
        assert indices_np_64.size == basis_shell_num
        assert (indices_np_64 == np.array(nucleus_index)).all()
        if self.test_file.isOpen:
            self.test_file.close()

    def test_sparse_read(self):
        """Read a sparse array."""
        self.open(mode='r')
        # read sparse arrays on ao_2e_int_eri integrals
        buf_size    = 60
        offset_file = 0
        # read full buf_size (i.e. the one that does not reach EOF)
        indices_sparse_np, value_sparse_np, read_buf_size, eof = trexio.read_ao_2e_int_eri(self.test_file, offset_file, buf_size)
        #print(f'First complete sparse read size: {read_buf_size}')
        assert not eof
        assert read_buf_size == buf_size
        assert indices_sparse_np[0][0] == 0
        assert indices_sparse_np[read_buf_size-1][3] == read_buf_size * 4 - 1

        offset_file += buf_size
        # read incomplete buf_size (i.e. the one that does reach EOF)
        indices_sparse_np, value_sparse_np, read_buf_size, eof = trexio.read_ao_2e_int_eri(self.test_file, offset_file, buf_size)
        #print(f'Second incomplete sparse read size: {read_buf_size}')
        assert eof
        assert read_buf_size == (num_integrals - buf_size)
        assert indices_sparse_np[0][0] == offset_file * 4
        assert indices_sparse_np[read_buf_size-1][3] == (offset_file + read_buf_size) * 4 - 1
        if self.test_file.isOpen:
            self.test_file.close()


    def test_array_str_read(self):
        """Read an array of strings."""
        self.open(mode='r')
        labels_r = trexio.read_nucleus_label(self.test_file)
        assert len(labels_r) == nucleus_num
        assert labels_r == nucleus_label
        if self.test_file.isOpen:
            self.test_file.close()


    def test_str_read(self):
        """Read a string."""
        self.open(mode='r')
        point_group_r = trexio.read_nucleus_point_group(self.test_file)
        assert point_group_r == point_group
        if self.test_file.isOpen:
            self.test_file.close()
