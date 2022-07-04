#!/usr/bin/env python3

import numpy as np
import pytest
import trexio
from benzene_data import *


FILENAME = 'test_file_py.h5'
BACK_END = trexio.TREXIO_HDF5


def clean():
    """Remove test files."""
    import os

    try:
        os.remove(FILENAME)
        os.remove('unsafe_' + FILENAME)
    except FileNotFoundError:
        pass


def test_info():
    """Print the output of the trexio.info function."""
    trexio.info()


def test_void():
    """Check raise of an error upon I/O on non-existing file."""
    with pytest.raises(trexio.Error):
        _ = trexio.File('void.file', 'r', BACK_END)


def test_orbital_list():
    """Convert one determinant into a list of orbitals."""
    orb_list_up, orb_list_dn = trexio.to_orbital_list_up_dn(int64_num, det_test)
    assert orb_list_up[0] == 0
    assert orb_list_dn[0] == 1


class TestIO:
    """Unit tests for writing/reading different blocks of the TREXIO file."""

    filename  = FILENAME
    back_end  = BACK_END
    mode      = 'w'
    test_file = None

    clean()


    def __del__(self):
        if self.test_file:
            if self.test_file.isOpen:
                self.test_file.close()


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


    def test_num(self):
        """Write a number."""
        self.open()
        trexio.write_nucleus_num(self.test_file, nucleus_num)
        assert trexio.has_nucleus_num(self.test_file)


    def test_str(self):
        """Write a string."""
        self.open()
        trexio.write_nucleus_point_group(self.test_file, point_group)
        assert trexio.has_nucleus_point_group(self.test_file)


    def test_array_str(self):
        """Write an array of strings."""
        self.open()
        if not trexio.has_nucleus_num(self.test_file):
            self.test_num()
        trexio.write_nucleus_label(self.test_file, nucleus_label)
        assert trexio.has_nucleus_label(self.test_file)


    def test_array_1D(self):
        """Write array of charges."""
        self.open()
        if not trexio.has_nucleus_num(self.test_file):
            self.test_num()
        trexio.write_nucleus_charge(self.test_file, nucleus_charge)
        assert trexio.has_nucleus_charge(self.test_file)


    def test_array_2D(self):
        """Write array of coordinates."""
        self.open()
        if not trexio.has_nucleus_num(self.test_file):
            self.test_num()
        trexio.write_nucleus_coord(self.test_file, nucleus_coord)
        assert trexio.has_nucleus_coord(self.test_file)


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


    def test_sparse(self):
        """Write a sparse array."""
        self.open()
        # write ao_num (needed later to write sparse ao_2e_int_eri integrals)
        trexio.write_ao_num(self.test_file, ao_num)
        # one complete write (no chunking)
        offset = 0
        trexio.write_ao_2e_int_eri(self.test_file, offset, num_integrals, indices, values)
        assert trexio.has_ao_2e_int_eri(self.test_file)


    def test_determinant(self):
        """Write CI determinants and coefficients."""
        self.open()
        # write mo_num (needed later to write determinants)
        trexio.write_mo_num(self.test_file, mo_num)
        # get the number of bit-strings per spin component
        int_num = trexio.get_int64_num(self.test_file)
        assert int_num == int64_num
        # write the data for the ground state
        offset = 0
        trexio.write_determinant_list(self.test_file, offset, det_num, dets)
        assert trexio.has_determinant_list(self.test_file)
        trexio.write_determinant_coefficient(self.test_file, offset, det_num, coeffs)
        assert trexio.has_determinant_coefficient(self.test_file)
        # write the data for some other state
        self.test_file.set_state(2)
        trexio.write_determinant_coefficient(self.test_file, offset, det_num, coeffs_s2)
        assert trexio.has_determinant_coefficient(self.test_file)
        self.test_file.set_state(0)
        # manually check the consistency between coefficient_size and number of determinants
        assert trexio.read_determinant_coefficient_size(self.test_file) == trexio.read_determinant_num(self.test_file)


    def test_delete_group(self):
        """Delete a group."""
        self.open(filename='unsafe_' + self.filename, mode='u', back_end=self.back_end)

        self.test_num()
        self.test_array_1D()
        self.test_array_2D()

        assert trexio.has_nucleus(self.test_file)

        trexio.delete_nucleus(self.test_file)

        assert not trexio.has_nucleus_num(self.test_file)
        assert not trexio.has_nucleus_charge(self.test_file)
        assert not trexio.has_nucleus_coord(self.test_file)
        assert not trexio.has_nucleus(self.test_file)


    def test_has_group(self):
        """Check existense of a group."""
        self.open()
        assert trexio.has_nucleus(self.test_file)
        assert not trexio.has_rdm(self.test_file)


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


    def test_read_array_1D(self):
        """Read an array."""
        self.open(mode='r')
        charges_np_r = trexio.read_nucleus_charge(self.test_file)
        assert charges_np_r.dtype is np.dtype(np.float64)
        assert charges_np_r.size == nucleus_num
        np.testing.assert_array_almost_equal(charges_np_r, np.array(nucleus_charge), decimal=8)


    def test_read_array_2D(self):
        """Read an array."""
        self.open(mode='r')
        # read nuclear coordinates without providing optional argument dim
        coords_np = trexio.read_nucleus_coord(self.test_file)
        assert coords_np.dtype is np.dtype(np.float64)
        assert coords_np.size == nucleus_num * 3
        np.testing.assert_array_almost_equal(coords_np, np.array(nucleus_coord).reshape(nucleus_num,3), decimal=8)


    def test_read_errors(self):
        """Test some reading errors."""
        self.open(mode='r')
        # unsafe call to read_safe should fail with error message corresponding to TREXIO_UNSAFE_ARRAY_DIM
        with pytest.raises(trexio.Error):
            _ = trexio.read_nucleus_charge(self.test_file, dim=nucleus_num/2)


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


    def test_determinant_read(self):
        """Read the CI determinants."""
        self.open(mode='r')
        # read determinants (list of ints and float coefficients)
        buf_size    = 100
        offset_file = 0
        # read full buf_size (i.e. the one that does not reach EOF)
        dets_np, read_buf_size, eof = trexio.read_determinant_list(self.test_file, offset_file, buf_size)
        #print(f'First complete read of determinant list: {read_buf_size}')
        assert not eof
        assert read_buf_size == buf_size
        assert dets_np[0][0] == 0
        assert dets_np[read_buf_size-1][int64_num*2-1] == read_buf_size * int64_num * 2- 1

        coefficients_np, read_buf_size, eof = trexio.read_determinant_coefficient(self.test_file, offset_file, buf_size)
        #print(f'First complete read of determinant coefficients: {read_buf_size}')
        assert not eof
        assert read_buf_size == buf_size


    def test_array_str_read(self):
        """Read an array of strings."""
        self.open(mode='r')
        labels_r = trexio.read_nucleus_label(self.test_file)
        assert len(labels_r) == nucleus_num
        assert labels_r == nucleus_label


    def test_str_read(self):
        """Read a string."""
        self.open(mode='r')
        point_group_r = trexio.read_nucleus_point_group(self.test_file)
        assert point_group_r == point_group
