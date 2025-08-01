"""The Python API of the TREXIO library.

This package is a top-level wrapper of the SWIG-generated pytrexio module.
"""

from os import path

try:
    import numpy as np
except ImportError:
    raise Exception("NumPy cannot be imported.")

try:
    import pytrexio.pytrexio as pytr
except ImportError:
    raise Exception("Could not import pytrexio module from trexio package")

# define max length of a string to be read, required for the low-level C routines
PYTREXIO_MAX_STR_LENGTH = 2048

# setuptools do not assign __version__ variable to the trexio package, so we set it manually
__trexio_path__ = path.dirname(path.abspath(__file__))
with open(path.join(path.join(__trexio_path__, 'pytrexio'), '_version.py')) as version_file:
    __version__ = version_file.read().split('"')[1]

__trexio_path__ = None

# define TREXIO exit codes
TREXIO_FAILURE                 = -1
TREXIO_SUCCESS                 = 0
TREXIO_INVALID_ARG_1           = 1
TREXIO_INVALID_ARG_2           = 2
TREXIO_INVALID_ARG_3           = 3
TREXIO_INVALID_ARG_4           = 4
TREXIO_INVALID_ARG_5           = 5
TREXIO_END                     = 6
TREXIO_READONLY                = 7
TREXIO_ERRNO                   = 8
TREXIO_INVALID_ID              = 9
TREXIO_ALLOCATION_FAILED       = 10
TREXIO_HAS_NOT                 = 11
TREXIO_INVALID_NUM             = 12
TREXIO_ATTR_ALREADY_EXISTS     = 13
TREXIO_DSET_ALREADY_EXISTS     = 14
TREXIO_OPEN_ERROR              = 15
TREXIO_LOCK_ERROR              = 16
TREXIO_UNLOCK_ERROR            = 17
TREXIO_FILE_ERROR              = 18
TREXIO_GROUP_READ_ERROR        = 19
TREXIO_GROUP_WRITE_ERROR       = 20
TREXIO_ELEM_READ_ERROR         = 21
TREXIO_ELEM_WRITE_ERROR        = 22
TREXIO_UNSAFE_ARRAY_DIM        = 23
TREXIO_ATTR_MISSING            = 24
TREXIO_DSET_MISSING            = 25
TREXIO_BACK_END_MISSING        = 26
TREXIO_INVALID_ARG_6           = 27
TREXIO_INVALID_ARG_7           = 28
TREXIO_INVALID_ARG_8           = 29
TREXIO_INVALID_STR_LEN         = 30
TREXIO_INT_SIZE_OVERFLOW       = 31
TREXIO_SAFE_MODE               = 32
TREXIO_INVALID_ELECTRON_NUM    = 33
TREXIO_INVALID_DETERMINANT_NUM = 34
TREXIO_INVALID_STATE           = 35
TREXIO_VERSION_PARSING_ISSUE   = 36
TREXIO_PHASE_CHANGE            = 37
TREXIO_INVALID_MO_INDEX        = 38
TREXIO_INVALID_ARG_9           = 39
TREXIO_INVALID_ARG_10          = 40
TREXIO_INVALID_ARG_11          = 41
TREXIO_INVALID_ARG_12          = 42
TREXIO_INVALID_ARG_13          = 43
TREXIO_INVALID_ARG_14          = 44
TREXIO_CORRUPTION_ATTEMPT      = 45

class Error(Exception):
    """Base class for TREXIO errors.

    Attributes:
       error: int -- exit code returned by the call to TREXIO library;
       message: str -- decoded string corresponding to trexio_exit_code.

    """

    def __init__(self, trexio_return_code):
        self.error = trexio_return_code
        self.message = string_of_error(trexio_return_code)
        super().__init__(self.message)


def string_of_error(return_code: int) -> str:
    """Decode the TREXIO exit code.

    Argument is an integer return code that correspond to one of the TREXIO errors.
    Returns a string that contains description of TREXIO ~return_code~.
    """

    return pytr.trexio_string_of_error(return_code)

# define TREXIO back ends
TREXIO_HDF5 = 0
TREXIO_TEXT = 1
#TREXIO_JSON = 2
TREXIO_INVALID_BACK_END = 2
TREXIO_AUTO = TREXIO_INVALID_BACK_END
class File:
    """trexio.File class.

    General information about the TREXIO file.

    Parameters:

    filename: str
        Is a name of the full path to the TREXIO file.
    back_end: int
        One of the currently supported TREXIO back ends.
        For example, TREXIO_HDF5 (0) or TREXIO_TEXT (1).
    mode: str
        One of the currently supported TREXIO open modes.
        For example, 'r' or 'w'.
    state: int
        Active (excited or ground) state of the file.
        Default is 0.
    isOpen: bool
        Flag indicating whether the current object is still open for I/O
    pytrexio_s:
        A PyObject corresponding to SWIG proxy of the trexio_s struct in C.
        This argument is in fact a TREXIO file handle, which is required for
        communicating with the C back end.
    info: dict
        Dictionary of key-value pairs with additional information about the file.
    """


    def __init__(self, filename, mode='r', back_end=TREXIO_HDF5,
                 pytrexio_s=None, info=None):
        """TREXIO File class constructor."""
        self.filename = filename
        self.mode = mode
        self.state = 0

        self.isOpen = False
        self.exists = False
        if pytrexio_s is None:
            self.pytrexio_s = _open(filename, mode, back_end)
            self.isOpen = True
            self.exists = True
        else:
            self.pytrexio_s = pytrexio_s
            self.isOpen = None
            self.exists = None

        self.back_end = self.pytrexio_s.back_end
        self.info = info


    def __enter__(self):
        """Enter statement for with ... as ... handling."""
        return self


    def __exit__(self, *args):
        """Exit statement for with ... as ... handling."""
        if self.isOpen:
           self.close()


    def close(self):
        """Close a TREXIO File."""
        if self.isOpen:
            _close(self.pytrexio_s)
            self.isOpen = False
        else:
            raise Exception("TREXIO File object has not been opened.")


    def set_state(self, state):
        """Set the state of the TREXIO File."""
        if not isinstance(state, int):
            raise TypeError("state argument has to be int")

        rc = pytr.trexio_set_state(self.pytrexio_s, state)
        if rc != TREXIO_SUCCESS:
            raise Error(rc)

        self.state = state


    def get_state(self):
        """Get the state of the TREXIO File."""
        rc, state = pytr.trexio_get_state(self.pytrexio_s)
        if rc != TREXIO_SUCCESS:
            raise Error(rc)

        if state != self.state:
            raise Exception("Inconsistent state of the TREXIO file.")

        return self.state


    def flush(self):
        """Flush the data on disk."""
        rc = pytr.trexio_flush(self.pytrexio_s)
        if rc != TREXIO_SUCCESS:
            raise Error(rc)


    def inquire(self):
        """Inquire whether a TREXIO file exists."""
        self.exists = _inquire(self.filename)


    def __del__(self):
        """TREXIO File class destructor."""
        if self.isOpen:
            _close(self.pytrexio_s)
        elif self.isOpen is None:
            raise Exception("[WIP]: TREXIO file handle provided but what if the file is already closed?")
        else:
            pass

def _open(file_name: str, mode: str, back_end: int):
    """Create TREXIO file or open existing one.

    Parameters:

    file_name: str
        Name of the TREXIO file

    mode: str
        One of the currently supported ~open~ modes (e.g. 'w', 'r')

    back_end: int
        One of the currently supported TREXIO back ends (e.g. TREXIO_HDF5, TREXIO_TEXT)

    Return:
        SWIG object of type trexio_s.

    Examples:
    >>> from trexio import open as tr_open
    >>> trex_file = tr_open("example.h5", "w", TREXIO_HDF5)
    """

    # The new trexio_open function is capable of returning error code which SWIG can append to the output trexio_s file struct
    # However, if trexio_s* == NULL, then SWIG returns only an error code rc_open instead of a list [trexio_s, rc_open]
    # Thus, the following try/except sequence is needed
    try:
        return_obj = pytr.trexio_open(file_name, mode, back_end)
        assert return_obj is not None
        if isinstance(return_obj, int):
            raise Error(return_obj)
        else:
            rc_open = return_obj[1]
            # this is a sanity check in case the code evolves and SWIG issue is patched
            if rc_open == TREXIO_SUCCESS:
                trexio_file = return_obj[0]
                assert trexio_file is not None

            return trexio_file
    except:
        raise Error(18) # 18 is an error code for encountering an invalid file

def _close(trexio_file):
    """Close TREXIO file.

    Parameter is a ~trexio_file~ object that has been created by a call to ~open~ function.
    """

    rc = pytr.trexio_close(trexio_file)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def flush(trexio_file):
    """Flush buffers into the TREXIO file.

    Parameter is a ~trexio_file~ object that has been created by a call to ~open~ function.
    """

    rc = pytr.trexio_flush(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def _inquire(file_name: str) -> bool:
    """Check whether ~file_name~ TREXIO file exists.
    """
    rc = pytr.trexio_inquire(trexio_file_name)
    if rc == TREXIO_SUCCESS:
        return True
    elif rc == TREXIO_FAILURE:
        return False
    else:
        raise Error(rc)

def _cp(source: str, destination: str):
    """Copies a TREXIO file

    Parameters:

    source: str
        Name of the source file

    destination: str
        Name of the destination file

    Examples:
    >>> from trexio import cp as tr_cp
    >>> tr_cp("example.h5", "new.h5")
    """

    from shutil import copytree, copyfile

    f = File(filename=source, mode='r', back_end=TREXIO_AUTO)
    if f.back_end == TREXIO_TEXT:
      copytree(source, destination)
    elif f.back_end == TREXIO_HDF5:
      copyfile(source, destination)

def info():
    """Print the info about the installed TREXIO library."""

    rc = pytr.trexio_info()
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def to_bitfield_list(n_int: int, orbitals: list) -> list:
    """Convert a list of occupied orbitals into a bitfield determinant.

    Input:
        ~orbitals~ - list of occupied orbital indices fields (integers)
        ~n_int~ - number of bitfields per determinant of a given spin

    Returns:
        ~bitfield_list~: list

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """


    rc, bitfield_list = pytr.trexio_to_bitfield_list(orbitals, n_int)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if len(bitfield_list) != n_int:
        raise Exception("Inconsistent size of the bitfield_list.")

    return bitfield_list

def to_orbital_list(n_int: int, determinant: list) -> list:
    """Convert a given determinant into a list of occupied orbitals.

    Input:
        ~determinant~ - list of bit fields (integers)
        ~n_int~ - number of bit fields per determinant of a given spin

    Returns:
        ~orbital_list~: list

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    # max possible size of the orbital list per spin component (upper limit on the number of MOs)
    size_max = n_int * 64

    rc, orbital_list, occ_num = pytr.trexio_safe_to_orbital_list(n_int, determinant, size_max)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if len(orbital_list) < occ_num:
        raise Exception("Inconsistent size of the orbital_list.")

    return orbital_list[0:occ_num]

def to_orbital_list_up_dn(n_int: int, determinant: list) -> tuple:
    """Convert a given determinant into two lists of occupied orbitals.

    Input:
        ~determinant~ - list of bit fields (integers)
        ~n_int~ - number of bit fields per determinant of a given spin

    Returns:
        result: tuple with the following items:
          ~orbital_list_up~: list of orbitals occupied by up-spin electrons
          ~orbital_list_dn~: list of orbitals occupied by down-spin electrons

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    # max possible size of the orbital list per spin component (upper limit on the number of MOs)
    size_max = n_int * 64

    rc, orbital_list_up, orbital_list_dn, occ_num_up, occ_num_dn = pytr.trexio_safe_to_orbital_list_up_dn(n_int, determinant, size_max, size_max)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if len(orbital_list_up) < occ_num_up:
        raise Exception("Inconsistent size of the orbital_list for up-spin electrons.")
    if len(orbital_list_dn) < occ_num_dn:
        raise Exception("Inconsistent size of the orbital_list for down-spin electrons.")

    return (orbital_list_up[0:occ_num_up], orbital_list_dn[0:occ_num_dn])

def convert_nao_radius(r: float, grid_r) -> float:
  """Converts the radius r as a distance from a nucleus to the shell
  s logarithmic grid.

  Input:
      ~r~ - the radius to be converted
      ~grid_r~ - The radial grid of the shell. Note that this is only the
                 grid of the shell of interest, not the array of all shells.

      Returns:
        Float that gives the radius in the shell's logarithmic units

      Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).

  """

  rc, r_log = pytr.trexio_convert_nao_radius_py(r, grid_r)

  if rc != TREXIO_SUCCESS:
    raise Error(rc)

  return r_log

def evaluate_nao_radial(shell_index, r, grid_start, grid_size, grid_r, interpolator, normalization) -> float:
  """Evaluates the radial function of a given NAO shell at a distance from its center.

  Input:
      ~shell_index~ - index of the shell of interest
      ~r~ - distance from the shell center
      ~grid_start~ - array of starting points of the individual splines
      ~grid_size~ - array of number of data points per spline
      ~grid_r~ - The radial grid of the shell. Note that this is only the
                 grid of the shell of interest, not the array of all shells.
      ~interpolator~ - Interpolator of the spline. It is assumed to contain a cubic spline.
                       An interpolator for a kinetic energy spline can also be passed.
      ~normalization~ - array of radial function normalization constants.

      Returns:
        Value of the spline at the given radius

      Raises:
        - Error from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Error from some other error (e.g. RuntimeError).

  """
  rc, amplitude = pytr.trexio_evaluate_nao_radial_py(shell_index, r, grid_start, grid_size, grid_r, interpolator.flatten(), normalization)

  if rc != TREXIO_SUCCESS:
    raise Error(rc)

  return amplitude

def evaluate_nao_radial_all(nucleus_index, nucleus_coords, grid_start,
  grid_size, grid_r, interpolator, normalization, r) -> float:
  """Evaluates the radial functions of all NAO shells at a given position in space.

  Input:
      ~nucleus_index~ - array giving the centers of the NAO
      ~nucleus_coords~ - array giving the coordinates of the NAO centers
      ~grid_start~ - array of starting points of the individual splines
      ~grid_size~ - array of number of data points per spline
      ~grid_r~ - The radial grid of the shell. Note that this is only the
                 grid of the shell of interest, not the array of all shells.
      ~interpolator~ - Interpolator of the spline. It is assumed to contain a cubic spline.
                       An interpolator for a kinetic energy spline can also be passed.
      ~normalization~ - array of radial function normalization constants.
      ~r~ - the position in space at which the functions are evaluated

      Returns:
        Array of spline values at ~r~

      Raises:
        - Error if ~r~ is not three dimensional
        - Error from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Error from some other error (e.g. RuntimeError).

  """
  if len(r) != 3:
    raise Error(TREXIO_INVALID_ARG7)
  shell_cnt = len(nucleus_index)
  rc, amplitudes = pytr.trexio_evaluate_nao_radial_all_py(shell_cnt, \
    nucleus_index, nucleus_coords.flatten(), grid_start, grid_size, grid_r, \
    interpolator.flatten(), normalization, r[0], r[1], r[2], shell_cnt)

  if rc != TREXIO_SUCCESS:
    raise Error(rc)

  return amplitudes
def delete_metadata(trexio_file) -> None:
    """Delete the entire metadata group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_metadata(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_nucleus(trexio_file) -> None:
    """Delete the entire nucleus group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_nucleus(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_cell(trexio_file) -> None:
    """Delete the entire cell group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_cell(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_pbc(trexio_file) -> None:
    """Delete the entire pbc group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_pbc(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_electron(trexio_file) -> None:
    """Delete the entire electron group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_electron(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_state(trexio_file) -> None:
    """Delete the entire state group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_state(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_basis(trexio_file) -> None:
    """Delete the entire basis group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_basis(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_ecp(trexio_file) -> None:
    """Delete the entire ecp group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_ecp(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_grid(trexio_file) -> None:
    """Delete the entire grid group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_grid(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_ao(trexio_file) -> None:
    """Delete the entire ao group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_ao(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_ao_1e_int(trexio_file) -> None:
    """Delete the entire ao_1e_int group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_ao_1e_int(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_ao_2e_int(trexio_file) -> None:
    """Delete the entire ao_2e_int group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_ao_2e_int(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_mo(trexio_file) -> None:
    """Delete the entire mo group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_mo(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_mo_1e_int(trexio_file) -> None:
    """Delete the entire mo_1e_int group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_mo_1e_int(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_mo_2e_int(trexio_file) -> None:
    """Delete the entire mo_2e_int group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_mo_2e_int(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_determinant(trexio_file) -> None:
    """Delete the entire determinant group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_determinant(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_csf(trexio_file) -> None:
    """Delete the entire csf group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_csf(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_amplitude(trexio_file) -> None:
    """Delete the entire amplitude group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_amplitude(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_rdm(trexio_file) -> None:
    """Delete the entire rdm group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_rdm(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_jastrow(trexio_file) -> None:
    """Delete the entire jastrow group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_jastrow(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def delete_qmc(trexio_file) -> None:
    """Delete the entire qmc group from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_delete_qmc(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def has_metadata_code_num(trexio_file) -> bool:
    """Check that metadata_code_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_metadata_code_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_metadata_author_num(trexio_file) -> bool:
    """Check that metadata_author_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_metadata_author_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_metadata_unsafe(trexio_file) -> bool:
    """Check that metadata_unsafe variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_metadata_unsafe(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_nucleus_num(trexio_file) -> bool:
    """Check that nucleus_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_nucleus_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_nucleus_repulsion(trexio_file) -> bool:
    """Check that nucleus_repulsion variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_nucleus_repulsion(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_cell_two_pi(trexio_file) -> bool:
    """Check that cell_two_pi variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_cell_two_pi(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_pbc_periodic(trexio_file) -> bool:
    """Check that pbc_periodic variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_pbc_periodic(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_pbc_k_point_num(trexio_file) -> bool:
    """Check that pbc_k_point_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_pbc_k_point_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_pbc_madelung(trexio_file) -> bool:
    """Check that pbc_madelung variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_pbc_madelung(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_electron_num(trexio_file) -> bool:
    """Check that electron_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_electron_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_electron_up_num(trexio_file) -> bool:
    """Check that electron_up_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_electron_up_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_electron_dn_num(trexio_file) -> bool:
    """Check that electron_dn_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_electron_dn_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_state_num(trexio_file) -> bool:
    """Check that state_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_state_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_state_id(trexio_file) -> bool:
    """Check that state_id variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_state_id(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_state_energy(trexio_file) -> bool:
    """Check that state_energy variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_state_energy(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_prim_num(trexio_file) -> bool:
    """Check that basis_prim_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_prim_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_shell_num(trexio_file) -> bool:
    """Check that basis_shell_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_shell_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_nao_grid_num(trexio_file) -> bool:
    """Check that basis_nao_grid_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_nao_grid_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_interp_coeff_cnt(trexio_file) -> bool:
    """Check that basis_interp_coeff_cnt variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_interp_coeff_cnt(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_e_cut(trexio_file) -> bool:
    """Check that basis_e_cut variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_e_cut(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ecp_num(trexio_file) -> bool:
    """Check that ecp_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ecp_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_rad_precision(trexio_file) -> bool:
    """Check that grid_rad_precision variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_rad_precision(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_num(trexio_file) -> bool:
    """Check that grid_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_max_ang_num(trexio_file) -> bool:
    """Check that grid_max_ang_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_max_ang_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_min_ang_num(trexio_file) -> bool:
    """Check that grid_min_ang_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_min_ang_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_ang_num(trexio_file) -> bool:
    """Check that grid_ang_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_ang_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_rad_num(trexio_file) -> bool:
    """Check that grid_rad_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_rad_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_cartesian(trexio_file) -> bool:
    """Check that ao_cartesian variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_cartesian(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_num(trexio_file) -> bool:
    """Check that ao_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_2e_int_eri_cholesky_num(trexio_file) -> bool:
    """Check that ao_2e_int_eri_cholesky_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_2e_int_eri_cholesky_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_2e_int_eri_lr_cholesky_num(trexio_file) -> bool:
    """Check that ao_2e_int_eri_lr_cholesky_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_2e_int_eri_lr_cholesky_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_num(trexio_file) -> bool:
    """Check that mo_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_2e_int_eri_cholesky_num(trexio_file) -> bool:
    """Check that mo_2e_int_eri_cholesky_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_2e_int_eri_cholesky_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_2e_int_eri_lr_cholesky_num(trexio_file) -> bool:
    """Check that mo_2e_int_eri_lr_cholesky_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_2e_int_eri_lr_cholesky_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_determinant_num(trexio_file) -> bool:
    """Check that determinant_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_determinant_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_csf_num(trexio_file) -> bool:
    """Check that csf_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_csf_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e_cholesky_num(trexio_file) -> bool:
    """Check that rdm_2e_cholesky_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e_cholesky_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e_upup_cholesky_num(trexio_file) -> bool:
    """Check that rdm_2e_upup_cholesky_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e_upup_cholesky_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e_dndn_cholesky_num(trexio_file) -> bool:
    """Check that rdm_2e_dndn_cholesky_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e_dndn_cholesky_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e_updn_cholesky_num(trexio_file) -> bool:
    """Check that rdm_2e_updn_cholesky_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e_updn_cholesky_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_jastrow_en_num(trexio_file) -> bool:
    """Check that jastrow_en_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_jastrow_en_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_jastrow_ee_num(trexio_file) -> bool:
    """Check that jastrow_ee_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_jastrow_ee_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_jastrow_een_num(trexio_file) -> bool:
    """Check that jastrow_een_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_jastrow_een_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_jastrow_ee_scaling(trexio_file) -> bool:
    """Check that jastrow_ee_scaling variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_jastrow_ee_scaling(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_qmc_num(trexio_file) -> bool:
    """Check that qmc_num variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_qmc_num(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_metadata_package_version(trexio_file) -> bool:
    """Check that metadata_package_version variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_metadata_package_version(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_metadata_description(trexio_file) -> bool:
    """Check that metadata_description variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_metadata_description(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_nucleus_point_group(trexio_file) -> bool:
    """Check that nucleus_point_group variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_nucleus_point_group(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_state_current_label(trexio_file) -> bool:
    """Check that state_current_label variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_state_current_label(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_type(trexio_file) -> bool:
    """Check that basis_type variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_type(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_oscillation_kind(trexio_file) -> bool:
    """Check that basis_oscillation_kind variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_oscillation_kind(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_interpolator_kind(trexio_file) -> bool:
    """Check that basis_interpolator_kind variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_interpolator_kind(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_description(trexio_file) -> bool:
    """Check that grid_description variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_description(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_type(trexio_file) -> bool:
    """Check that mo_type variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_type(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_jastrow_type(trexio_file) -> bool:
    """Check that jastrow_type variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_jastrow_type(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_determinant_coefficient(trexio_file) -> bool:
    """Check that determinant_coefficient exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_determinant_coefficient(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_csf_coefficient(trexio_file) -> bool:
    """Check that csf_coefficient exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_csf_coefficient(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_nucleus_charge(trexio_file) -> bool:
    """Check that nucleus_charge variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_nucleus_charge(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_nucleus_coord(trexio_file) -> bool:
    """Check that nucleus_coord variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_nucleus_coord(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_cell_a(trexio_file) -> bool:
    """Check that cell_a variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_cell_a(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_cell_b(trexio_file) -> bool:
    """Check that cell_b variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_cell_b(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_cell_c(trexio_file) -> bool:
    """Check that cell_c variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_cell_c(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_cell_g_a(trexio_file) -> bool:
    """Check that cell_g_a variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_cell_g_a(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_cell_g_b(trexio_file) -> bool:
    """Check that cell_g_b variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_cell_g_b(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_cell_g_c(trexio_file) -> bool:
    """Check that cell_g_c variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_cell_g_c(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_pbc_k_point(trexio_file) -> bool:
    """Check that pbc_k_point variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_pbc_k_point(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_pbc_k_point_weight(trexio_file) -> bool:
    """Check that pbc_k_point_weight variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_pbc_k_point_weight(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_nucleus_index(trexio_file) -> bool:
    """Check that basis_nucleus_index variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_nucleus_index(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_shell_ang_mom(trexio_file) -> bool:
    """Check that basis_shell_ang_mom variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_shell_ang_mom(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_shell_factor(trexio_file) -> bool:
    """Check that basis_shell_factor variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_shell_factor(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_r_power(trexio_file) -> bool:
    """Check that basis_r_power variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_r_power(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_nao_grid_start(trexio_file) -> bool:
    """Check that basis_nao_grid_start variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_nao_grid_start(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_nao_grid_size(trexio_file) -> bool:
    """Check that basis_nao_grid_size variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_nao_grid_size(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_shell_index(trexio_file) -> bool:
    """Check that basis_shell_index variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_shell_index(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_exponent(trexio_file) -> bool:
    """Check that basis_exponent variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_exponent(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_exponent_im(trexio_file) -> bool:
    """Check that basis_exponent_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_exponent_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_coefficient(trexio_file) -> bool:
    """Check that basis_coefficient variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_coefficient(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_coefficient_im(trexio_file) -> bool:
    """Check that basis_coefficient_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_coefficient_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_oscillation_arg(trexio_file) -> bool:
    """Check that basis_oscillation_arg variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_oscillation_arg(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_prim_factor(trexio_file) -> bool:
    """Check that basis_prim_factor variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_prim_factor(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_nao_grid_radius(trexio_file) -> bool:
    """Check that basis_nao_grid_radius variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_nao_grid_radius(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_nao_grid_phi(trexio_file) -> bool:
    """Check that basis_nao_grid_phi variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_nao_grid_phi(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_nao_grid_grad(trexio_file) -> bool:
    """Check that basis_nao_grid_grad variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_nao_grid_grad(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_nao_grid_lap(trexio_file) -> bool:
    """Check that basis_nao_grid_lap variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_nao_grid_lap(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_interpolator_phi(trexio_file) -> bool:
    """Check that basis_interpolator_phi variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_interpolator_phi(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_interpolator_grad(trexio_file) -> bool:
    """Check that basis_interpolator_grad variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_interpolator_grad(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis_interpolator_lap(trexio_file) -> bool:
    """Check that basis_interpolator_lap variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis_interpolator_lap(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ecp_max_ang_mom_plus_1(trexio_file) -> bool:
    """Check that ecp_max_ang_mom_plus_1 variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ecp_max_ang_mom_plus_1(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ecp_z_core(trexio_file) -> bool:
    """Check that ecp_z_core variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ecp_z_core(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ecp_ang_mom(trexio_file) -> bool:
    """Check that ecp_ang_mom variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ecp_ang_mom(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ecp_nucleus_index(trexio_file) -> bool:
    """Check that ecp_nucleus_index variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ecp_nucleus_index(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ecp_exponent(trexio_file) -> bool:
    """Check that ecp_exponent variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ecp_exponent(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ecp_coefficient(trexio_file) -> bool:
    """Check that ecp_coefficient variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ecp_coefficient(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ecp_power(trexio_file) -> bool:
    """Check that ecp_power variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ecp_power(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_coord(trexio_file) -> bool:
    """Check that grid_coord variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_coord(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_weight(trexio_file) -> bool:
    """Check that grid_weight variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_weight(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_ang_coord(trexio_file) -> bool:
    """Check that grid_ang_coord variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_ang_coord(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_ang_weight(trexio_file) -> bool:
    """Check that grid_ang_weight variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_ang_weight(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_rad_coord(trexio_file) -> bool:
    """Check that grid_rad_coord variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_rad_coord(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid_rad_weight(trexio_file) -> bool:
    """Check that grid_rad_weight variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid_rad_weight(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_shell(trexio_file) -> bool:
    """Check that ao_shell variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_shell(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_normalization(trexio_file) -> bool:
    """Check that ao_normalization variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_normalization(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_1e_int_overlap(trexio_file) -> bool:
    """Check that ao_1e_int_overlap variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_1e_int_overlap(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_1e_int_kinetic(trexio_file) -> bool:
    """Check that ao_1e_int_kinetic variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_1e_int_kinetic(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_1e_int_potential_n_e(trexio_file) -> bool:
    """Check that ao_1e_int_potential_n_e variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_1e_int_potential_n_e(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_1e_int_ecp(trexio_file) -> bool:
    """Check that ao_1e_int_ecp variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_1e_int_ecp(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_1e_int_core_hamiltonian(trexio_file) -> bool:
    """Check that ao_1e_int_core_hamiltonian variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_1e_int_core_hamiltonian(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_1e_int_overlap_im(trexio_file) -> bool:
    """Check that ao_1e_int_overlap_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_1e_int_overlap_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_1e_int_kinetic_im(trexio_file) -> bool:
    """Check that ao_1e_int_kinetic_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_1e_int_kinetic_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_1e_int_potential_n_e_im(trexio_file) -> bool:
    """Check that ao_1e_int_potential_n_e_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_1e_int_potential_n_e_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_1e_int_ecp_im(trexio_file) -> bool:
    """Check that ao_1e_int_ecp_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_1e_int_ecp_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_1e_int_core_hamiltonian_im(trexio_file) -> bool:
    """Check that ao_1e_int_core_hamiltonian_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_1e_int_core_hamiltonian_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_coefficient(trexio_file) -> bool:
    """Check that mo_coefficient variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_coefficient(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_coefficient_im(trexio_file) -> bool:
    """Check that mo_coefficient_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_coefficient_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_occupation(trexio_file) -> bool:
    """Check that mo_occupation variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_occupation(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_energy(trexio_file) -> bool:
    """Check that mo_energy variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_energy(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_spin(trexio_file) -> bool:
    """Check that mo_spin variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_spin(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_k_point(trexio_file) -> bool:
    """Check that mo_k_point variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_k_point(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_1e_int_overlap(trexio_file) -> bool:
    """Check that mo_1e_int_overlap variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_1e_int_overlap(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_1e_int_kinetic(trexio_file) -> bool:
    """Check that mo_1e_int_kinetic variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_1e_int_kinetic(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_1e_int_potential_n_e(trexio_file) -> bool:
    """Check that mo_1e_int_potential_n_e variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_1e_int_potential_n_e(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_1e_int_ecp(trexio_file) -> bool:
    """Check that mo_1e_int_ecp variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_1e_int_ecp(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_1e_int_core_hamiltonian(trexio_file) -> bool:
    """Check that mo_1e_int_core_hamiltonian variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_1e_int_core_hamiltonian(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_1e_int_overlap_im(trexio_file) -> bool:
    """Check that mo_1e_int_overlap_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_1e_int_overlap_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_1e_int_kinetic_im(trexio_file) -> bool:
    """Check that mo_1e_int_kinetic_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_1e_int_kinetic_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_1e_int_potential_n_e_im(trexio_file) -> bool:
    """Check that mo_1e_int_potential_n_e_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_1e_int_potential_n_e_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_1e_int_ecp_im(trexio_file) -> bool:
    """Check that mo_1e_int_ecp_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_1e_int_ecp_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_1e_int_core_hamiltonian_im(trexio_file) -> bool:
    """Check that mo_1e_int_core_hamiltonian_im variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_1e_int_core_hamiltonian_im(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_1e(trexio_file) -> bool:
    """Check that rdm_1e variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_1e(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_1e_up(trexio_file) -> bool:
    """Check that rdm_1e_up variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_1e_up(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_1e_dn(trexio_file) -> bool:
    """Check that rdm_1e_dn variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_1e_dn(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_1e_transition(trexio_file) -> bool:
    """Check that rdm_1e_transition variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_1e_transition(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_jastrow_en(trexio_file) -> bool:
    """Check that jastrow_en variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_jastrow_en(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_jastrow_ee(trexio_file) -> bool:
    """Check that jastrow_ee variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_jastrow_ee(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_jastrow_een(trexio_file) -> bool:
    """Check that jastrow_een variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_jastrow_een(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_jastrow_en_nucleus(trexio_file) -> bool:
    """Check that jastrow_en_nucleus variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_jastrow_en_nucleus(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_jastrow_een_nucleus(trexio_file) -> bool:
    """Check that jastrow_een_nucleus variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_jastrow_een_nucleus(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_jastrow_en_scaling(trexio_file) -> bool:
    """Check that jastrow_en_scaling variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_jastrow_en_scaling(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_qmc_point(trexio_file) -> bool:
    """Check that qmc_point variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_qmc_point(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_qmc_psi(trexio_file) -> bool:
    """Check that qmc_psi variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_qmc_psi(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_qmc_e_loc(trexio_file) -> bool:
    """Check that qmc_e_loc variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_qmc_e_loc(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_2e_int_eri(trexio_file) -> bool:
    """Check that ao_2e_int_eri variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_2e_int_eri(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_2e_int_eri_lr(trexio_file) -> bool:
    """Check that ao_2e_int_eri_lr variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_2e_int_eri_lr(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_2e_int_eri_cholesky(trexio_file) -> bool:
    """Check that ao_2e_int_eri_cholesky variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_2e_int_eri_cholesky(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_2e_int_eri_lr_cholesky(trexio_file) -> bool:
    """Check that ao_2e_int_eri_lr_cholesky variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_2e_int_eri_lr_cholesky(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_2e_int_eri(trexio_file) -> bool:
    """Check that mo_2e_int_eri variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_2e_int_eri(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_2e_int_eri_lr(trexio_file) -> bool:
    """Check that mo_2e_int_eri_lr variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_2e_int_eri_lr(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_2e_int_eri_cholesky(trexio_file) -> bool:
    """Check that mo_2e_int_eri_cholesky variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_2e_int_eri_cholesky(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_2e_int_eri_lr_cholesky(trexio_file) -> bool:
    """Check that mo_2e_int_eri_lr_cholesky variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_2e_int_eri_lr_cholesky(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_csf_det_coefficient(trexio_file) -> bool:
    """Check that csf_det_coefficient variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_csf_det_coefficient(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_amplitude_single(trexio_file) -> bool:
    """Check that amplitude_single variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_amplitude_single(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_amplitude_single_exp(trexio_file) -> bool:
    """Check that amplitude_single_exp variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_amplitude_single_exp(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_amplitude_double(trexio_file) -> bool:
    """Check that amplitude_double variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_amplitude_double(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_amplitude_double_exp(trexio_file) -> bool:
    """Check that amplitude_double_exp variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_amplitude_double_exp(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_amplitude_triple(trexio_file) -> bool:
    """Check that amplitude_triple variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_amplitude_triple(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_amplitude_triple_exp(trexio_file) -> bool:
    """Check that amplitude_triple_exp variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_amplitude_triple_exp(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_amplitude_quadruple(trexio_file) -> bool:
    """Check that amplitude_quadruple variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_amplitude_quadruple(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_amplitude_quadruple_exp(trexio_file) -> bool:
    """Check that amplitude_quadruple_exp variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_amplitude_quadruple_exp(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e(trexio_file) -> bool:
    """Check that rdm_2e variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e_upup(trexio_file) -> bool:
    """Check that rdm_2e_upup variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e_upup(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e_dndn(trexio_file) -> bool:
    """Check that rdm_2e_dndn variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e_dndn(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e_updn(trexio_file) -> bool:
    """Check that rdm_2e_updn variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e_updn(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e_transition(trexio_file) -> bool:
    """Check that rdm_2e_transition variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e_transition(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e_cholesky(trexio_file) -> bool:
    """Check that rdm_2e_cholesky variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e_cholesky(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e_upup_cholesky(trexio_file) -> bool:
    """Check that rdm_2e_upup_cholesky variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e_upup_cholesky(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e_dndn_cholesky(trexio_file) -> bool:
    """Check that rdm_2e_dndn_cholesky variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e_dndn_cholesky(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm_2e_updn_cholesky(trexio_file) -> bool:
    """Check that rdm_2e_updn_cholesky variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm_2e_updn_cholesky(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_metadata_code(trexio_file) -> bool:
    """Check that metadata_code variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_metadata_code(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_metadata_author(trexio_file) -> bool:
    """Check that metadata_author variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_metadata_author(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_nucleus_label(trexio_file) -> bool:
    """Check that nucleus_label variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_nucleus_label(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_state_label(trexio_file) -> bool:
    """Check that state_label variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_state_label(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_state_file_name(trexio_file) -> bool:
    """Check that state_file_name variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_state_file_name(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_class(trexio_file) -> bool:
    """Check that mo_class variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_class(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_symmetry(trexio_file) -> bool:
    """Check that mo_symmetry variable exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_symmetry(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_metadata(trexio_file) -> bool:
    """Check that metadata group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_metadata(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_nucleus(trexio_file) -> bool:
    """Check that nucleus group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_nucleus(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_cell(trexio_file) -> bool:
    """Check that cell group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_cell(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_pbc(trexio_file) -> bool:
    """Check that pbc group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_pbc(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_electron(trexio_file) -> bool:
    """Check that electron group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_electron(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_state(trexio_file) -> bool:
    """Check that state group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_state(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_basis(trexio_file) -> bool:
    """Check that basis group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_basis(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ecp(trexio_file) -> bool:
    """Check that ecp group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ecp(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_grid(trexio_file) -> bool:
    """Check that grid group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_grid(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao(trexio_file) -> bool:
    """Check that ao group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_1e_int(trexio_file) -> bool:
    """Check that ao_1e_int group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_1e_int(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_ao_2e_int(trexio_file) -> bool:
    """Check that ao_2e_int group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_ao_2e_int(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo(trexio_file) -> bool:
    """Check that mo group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_1e_int(trexio_file) -> bool:
    """Check that mo_1e_int group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_1e_int(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_mo_2e_int(trexio_file) -> bool:
    """Check that mo_2e_int group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_mo_2e_int(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_determinant(trexio_file) -> bool:
    """Check that determinant group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_determinant(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_csf(trexio_file) -> bool:
    """Check that csf group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_csf(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_amplitude(trexio_file) -> bool:
    """Check that amplitude group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_amplitude(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_rdm(trexio_file) -> bool:
    """Check that rdm group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_rdm(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_jastrow(trexio_file) -> bool:
    """Check that jastrow group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_jastrow(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def has_qmc(trexio_file) -> bool:
    """Check that qmc group exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_qmc(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS

def read_metadata_code_num(trexio_file) -> int:
    """Read the metadata_code_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of metadata_code_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_metadata_code_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_metadata_author_num(trexio_file) -> int:
    """Read the metadata_author_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of metadata_author_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_metadata_author_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_metadata_unsafe(trexio_file) -> int:
    """Read the metadata_unsafe variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of metadata_unsafe variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_metadata_unsafe(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_nucleus_num(trexio_file) -> int:
    """Read the nucleus_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of nucleus_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_nucleus_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_nucleus_repulsion(trexio_file) -> float:
    """Read the nucleus_repulsion variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of nucleus_repulsion variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_nucleus_repulsion(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_cell_two_pi(trexio_file) -> int:
    """Read the cell_two_pi variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of cell_two_pi variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_cell_two_pi(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_pbc_periodic(trexio_file) -> int:
    """Read the pbc_periodic variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of pbc_periodic variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_pbc_periodic(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_pbc_k_point_num(trexio_file) -> int:
    """Read the pbc_k_point_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of pbc_k_point_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_pbc_k_point_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_pbc_madelung(trexio_file) -> float:
    """Read the pbc_madelung variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of pbc_madelung variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_pbc_madelung(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_electron_num(trexio_file) -> int:
    """Read the electron_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of electron_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_electron_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_electron_up_num(trexio_file) -> int:
    """Read the electron_up_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of electron_up_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_electron_up_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_electron_dn_num(trexio_file) -> int:
    """Read the electron_dn_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of electron_dn_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_electron_dn_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_state_num(trexio_file) -> int:
    """Read the state_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of state_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_state_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_state_id(trexio_file) -> int:
    """Read the state_id variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of state_id variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_state_id(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_state_energy(trexio_file) -> float:
    """Read the state_energy variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of state_energy variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_state_energy(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_basis_prim_num(trexio_file) -> int:
    """Read the basis_prim_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of basis_prim_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_basis_prim_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_basis_shell_num(trexio_file) -> int:
    """Read the basis_shell_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of basis_shell_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_basis_shell_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_basis_nao_grid_num(trexio_file) -> int:
    """Read the basis_nao_grid_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of basis_nao_grid_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_basis_nao_grid_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_basis_interp_coeff_cnt(trexio_file) -> int:
    """Read the basis_interp_coeff_cnt variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of basis_interp_coeff_cnt variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_basis_interp_coeff_cnt(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_basis_e_cut(trexio_file) -> float:
    """Read the basis_e_cut variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of basis_e_cut variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_basis_e_cut(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_ecp_num(trexio_file) -> int:
    """Read the ecp_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of ecp_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_ecp_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_grid_rad_precision(trexio_file) -> float:
    """Read the grid_rad_precision variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of grid_rad_precision variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_grid_rad_precision(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_grid_num(trexio_file) -> int:
    """Read the grid_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of grid_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_grid_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_grid_max_ang_num(trexio_file) -> int:
    """Read the grid_max_ang_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of grid_max_ang_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_grid_max_ang_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_grid_min_ang_num(trexio_file) -> int:
    """Read the grid_min_ang_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of grid_min_ang_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_grid_min_ang_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_grid_ang_num(trexio_file) -> int:
    """Read the grid_ang_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of grid_ang_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_grid_ang_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_grid_rad_num(trexio_file) -> int:
    """Read the grid_rad_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of grid_rad_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_grid_rad_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_ao_cartesian(trexio_file) -> int:
    """Read the ao_cartesian variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of ao_cartesian variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_ao_cartesian(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_ao_num(trexio_file) -> int:
    """Read the ao_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of ao_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_ao_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_ao_2e_int_eri_cholesky_num(trexio_file) -> int:
    """Read the ao_2e_int_eri_cholesky_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of ao_2e_int_eri_cholesky_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_ao_2e_int_eri_cholesky_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_ao_2e_int_eri_lr_cholesky_num(trexio_file) -> int:
    """Read the ao_2e_int_eri_lr_cholesky_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of ao_2e_int_eri_lr_cholesky_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_ao_2e_int_eri_lr_cholesky_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_mo_num(trexio_file) -> int:
    """Read the mo_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of mo_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_mo_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_mo_2e_int_eri_cholesky_num(trexio_file) -> int:
    """Read the mo_2e_int_eri_cholesky_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of mo_2e_int_eri_cholesky_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_mo_2e_int_eri_cholesky_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_mo_2e_int_eri_lr_cholesky_num(trexio_file) -> int:
    """Read the mo_2e_int_eri_lr_cholesky_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of mo_2e_int_eri_lr_cholesky_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_mo_2e_int_eri_lr_cholesky_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_determinant_num(trexio_file) -> int:
    """Read the determinant_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of determinant_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_determinant_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_csf_num(trexio_file) -> int:
    """Read the csf_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of csf_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_csf_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_rdm_2e_cholesky_num(trexio_file) -> int:
    """Read the rdm_2e_cholesky_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of rdm_2e_cholesky_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_rdm_2e_cholesky_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_rdm_2e_upup_cholesky_num(trexio_file) -> int:
    """Read the rdm_2e_upup_cholesky_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of rdm_2e_upup_cholesky_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_rdm_2e_upup_cholesky_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_rdm_2e_dndn_cholesky_num(trexio_file) -> int:
    """Read the rdm_2e_dndn_cholesky_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of rdm_2e_dndn_cholesky_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_rdm_2e_dndn_cholesky_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_rdm_2e_updn_cholesky_num(trexio_file) -> int:
    """Read the rdm_2e_updn_cholesky_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of rdm_2e_updn_cholesky_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_rdm_2e_updn_cholesky_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_jastrow_en_num(trexio_file) -> int:
    """Read the jastrow_en_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of jastrow_en_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_jastrow_en_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_jastrow_ee_num(trexio_file) -> int:
    """Read the jastrow_ee_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of jastrow_ee_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_jastrow_ee_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_jastrow_een_num(trexio_file) -> int:
    """Read the jastrow_een_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of jastrow_een_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_jastrow_een_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_jastrow_ee_scaling(trexio_file) -> float:
    """Read the jastrow_ee_scaling variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of jastrow_ee_scaling variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_jastrow_ee_scaling(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_qmc_num(trexio_file) -> int:
    """Read the qmc_num variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_r~: int
        Integer value of qmc_num variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_r = pytr.trexio_read_qmc_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_r

def read_metadata_package_version(trexio_file) -> str:
    """Read the metadata_package_version variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~str_r~: str
        String corresponding to the metadata_package_version variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, str_r = pytr.trexio_read_metadata_package_version(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return str_r

def read_metadata_description(trexio_file) -> str:
    """Read the metadata_description variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~str_r~: str
        String corresponding to the metadata_description variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, str_r = pytr.trexio_read_metadata_description(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return str_r

def read_nucleus_point_group(trexio_file) -> str:
    """Read the nucleus_point_group variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~str_r~: str
        String corresponding to the nucleus_point_group variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, str_r = pytr.trexio_read_nucleus_point_group(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return str_r

def read_state_current_label(trexio_file) -> str:
    """Read the state_current_label variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~str_r~: str
        String corresponding to the state_current_label variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, str_r = pytr.trexio_read_state_current_label(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return str_r

def read_basis_type(trexio_file) -> str:
    """Read the basis_type variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~str_r~: str
        String corresponding to the basis_type variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, str_r = pytr.trexio_read_basis_type(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return str_r

def read_basis_oscillation_kind(trexio_file) -> str:
    """Read the basis_oscillation_kind variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~str_r~: str
        String corresponding to the basis_oscillation_kind variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, str_r = pytr.trexio_read_basis_oscillation_kind(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return str_r

def read_basis_interpolator_kind(trexio_file) -> str:
    """Read the basis_interpolator_kind variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~str_r~: str
        String corresponding to the basis_interpolator_kind variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, str_r = pytr.trexio_read_basis_interpolator_kind(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return str_r

def read_grid_description(trexio_file) -> str:
    """Read the grid_description variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~str_r~: str
        String corresponding to the grid_description variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, str_r = pytr.trexio_read_grid_description(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return str_r

def read_mo_type(trexio_file) -> str:
    """Read the mo_type variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~str_r~: str
        String corresponding to the mo_type variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, str_r = pytr.trexio_read_mo_type(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return str_r

def read_jastrow_type(trexio_file) -> str:
    """Read the jastrow_type variable from the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~str_r~: str
        String corresponding to the jastrow_type variable read from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, str_r = pytr.trexio_read_jastrow_type(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return str_r

def read_determinant_coefficient(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read determinant_coefficient from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of values to be skipped in the file when reading.

    buffer_size: int
        The number of values to read from the file.

    Returns:
        (dset, n_int_read, eof_flag) tuple where
          - dset is the NumPy array [numpy.ndarray] with the default int64 precision;
          - n_int_read [int] is the number of coefficients read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of values already in the file
    det_num = read_determinant_coefficient_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - det_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, dset = pytr.trexio_read_safe_determinant_coefficient(trexio_file.pytrexio_s, offset_file, verified_size, verified_size)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if dset is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    return (dset, n_int_read, eof_flag)


def read_determinant_coefficient_size(trexio_file) -> int:
    """Read the number of elements stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num~: int
        Integer value of corresponding to the size of the determinant_coefficient array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num = pytr.trexio_read_determinant_coefficient_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num

def read_csf_coefficient(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read csf_coefficient from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of values to be skipped in the file when reading.

    buffer_size: int
        The number of values to read from the file.

    Returns:
        (dset, n_int_read, eof_flag) tuple where
          - dset is the NumPy array [numpy.ndarray] with the default int64 precision;
          - n_int_read [int] is the number of coefficients read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of values already in the file
    det_num = read_csf_coefficient_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - det_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, dset = pytr.trexio_read_safe_csf_coefficient(trexio_file.pytrexio_s, offset_file, verified_size, verified_size)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if dset is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    return (dset, n_int_read, eof_flag)


def read_csf_coefficient_size(trexio_file) -> int:
    """Read the number of elements stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num~: int
        Integer value of corresponding to the size of the csf_coefficient array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num = pytr.trexio_read_csf_coefficient_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num

def read_nucleus_charge(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the nucleus_charge array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of nucleus_charge will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to nucleus_charge values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        nucleus_num = read_nucleus_num(trexio_file)

        dims_list = [nucleus_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_nucleus_charge_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_nucleus_coord(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the nucleus_coord array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of nucleus_coord will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to nucleus_coord values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        nucleus_num = read_nucleus_num(trexio_file)

        dims_list = [nucleus_num, 3]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_nucleus_coord_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_cell_a(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the cell_a array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of cell_a will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to cell_a values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:

        dims_list = [3]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_cell_a_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_cell_b(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the cell_b array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of cell_b will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to cell_b values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:

        dims_list = [3]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_cell_b_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_cell_c(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the cell_c array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of cell_c will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to cell_c values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:

        dims_list = [3]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_cell_c_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_cell_g_a(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the cell_g_a array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of cell_g_a will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to cell_g_a values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:

        dims_list = [3]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_cell_g_a_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_cell_g_b(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the cell_g_b array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of cell_g_b will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to cell_g_b values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:

        dims_list = [3]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_cell_g_b_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_cell_g_c(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the cell_g_c array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of cell_g_c will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to cell_g_c values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:

        dims_list = [3]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_cell_g_c_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_pbc_k_point(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the pbc_k_point array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of pbc_k_point will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to pbc_k_point values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:

        dims_list = [3]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_pbc_k_point_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_pbc_k_point_weight(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the pbc_k_point_weight array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of pbc_k_point_weight will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to pbc_k_point_weight values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        pbc_k_point_num = read_pbc_k_point_num(trexio_file)

        dims_list = [pbc_k_point_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_pbc_k_point_weight_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_nucleus_index(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_nucleus_index array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_nucleus_index will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_nucleus_index values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_shell_num = read_basis_shell_num(trexio_file)

        dims_list = [basis_shell_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_nucleus_index_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_shell_ang_mom(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_shell_ang_mom array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_shell_ang_mom will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_shell_ang_mom values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_shell_num = read_basis_shell_num(trexio_file)

        dims_list = [basis_shell_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_shell_ang_mom_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_shell_factor(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_shell_factor array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_shell_factor will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_shell_factor values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_shell_num = read_basis_shell_num(trexio_file)

        dims_list = [basis_shell_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_shell_factor_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_r_power(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_r_power array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_r_power will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_r_power values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_shell_num = read_basis_shell_num(trexio_file)

        dims_list = [basis_shell_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_r_power_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_nao_grid_start(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_nao_grid_start array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_nao_grid_start will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_nao_grid_start values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_shell_num = read_basis_shell_num(trexio_file)

        dims_list = [basis_shell_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_nao_grid_start_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_nao_grid_size(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_nao_grid_size array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_nao_grid_size will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_nao_grid_size values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_shell_num = read_basis_shell_num(trexio_file)

        dims_list = [basis_shell_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_nao_grid_size_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_shell_index(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_shell_index array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_shell_index will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_shell_index values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_prim_num = read_basis_prim_num(trexio_file)

        dims_list = [basis_prim_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_shell_index_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_exponent(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_exponent array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_exponent will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_exponent values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_prim_num = read_basis_prim_num(trexio_file)

        dims_list = [basis_prim_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_exponent_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_exponent_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_exponent_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_exponent_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_exponent_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_prim_num = read_basis_prim_num(trexio_file)

        dims_list = [basis_prim_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_exponent_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_coefficient(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_coefficient array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_coefficient will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_coefficient values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_prim_num = read_basis_prim_num(trexio_file)

        dims_list = [basis_prim_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_coefficient_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_coefficient_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_coefficient_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_coefficient_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_coefficient_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_prim_num = read_basis_prim_num(trexio_file)

        dims_list = [basis_prim_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_coefficient_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_oscillation_arg(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_oscillation_arg array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_oscillation_arg will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_oscillation_arg values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_prim_num = read_basis_prim_num(trexio_file)

        dims_list = [basis_prim_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_oscillation_arg_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_prim_factor(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_prim_factor array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_prim_factor will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_prim_factor values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_prim_num = read_basis_prim_num(trexio_file)

        dims_list = [basis_prim_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_prim_factor_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_nao_grid_radius(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_nao_grid_radius array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_nao_grid_radius will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_nao_grid_radius values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_nao_grid_num = read_basis_nao_grid_num(trexio_file)

        dims_list = [basis_nao_grid_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_nao_grid_radius_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_nao_grid_phi(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_nao_grid_phi array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_nao_grid_phi will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_nao_grid_phi values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_nao_grid_num = read_basis_nao_grid_num(trexio_file)

        dims_list = [basis_nao_grid_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_nao_grid_phi_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_nao_grid_grad(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_nao_grid_grad array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_nao_grid_grad will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_nao_grid_grad values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_nao_grid_num = read_basis_nao_grid_num(trexio_file)

        dims_list = [basis_nao_grid_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_nao_grid_grad_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_nao_grid_lap(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_nao_grid_lap array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_nao_grid_lap will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_nao_grid_lap values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_nao_grid_num = read_basis_nao_grid_num(trexio_file)

        dims_list = [basis_nao_grid_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_nao_grid_lap_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_interpolator_phi(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_interpolator_phi array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_interpolator_phi will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_interpolator_phi values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_nao_grid_num = read_basis_nao_grid_num(trexio_file)
        basis_interp_coeff_cnt = read_basis_interp_coeff_cnt(trexio_file)

        dims_list = [basis_nao_grid_num, basis_interp_coeff_cnt]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_interpolator_phi_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_interpolator_grad(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_interpolator_grad array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_interpolator_grad will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_interpolator_grad values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_nao_grid_num = read_basis_nao_grid_num(trexio_file)
        basis_interp_coeff_cnt = read_basis_interp_coeff_cnt(trexio_file)

        dims_list = [basis_nao_grid_num, basis_interp_coeff_cnt]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_interpolator_grad_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_basis_interpolator_lap(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the basis_interpolator_lap array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of basis_interpolator_lap will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to basis_interpolator_lap values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        basis_nao_grid_num = read_basis_nao_grid_num(trexio_file)
        basis_interp_coeff_cnt = read_basis_interp_coeff_cnt(trexio_file)

        dims_list = [basis_nao_grid_num, basis_interp_coeff_cnt]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_basis_interpolator_lap_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ecp_max_ang_mom_plus_1(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ecp_max_ang_mom_plus_1 array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ecp_max_ang_mom_plus_1 will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ecp_max_ang_mom_plus_1 values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        nucleus_num = read_nucleus_num(trexio_file)

        dims_list = [nucleus_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ecp_max_ang_mom_plus_1_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ecp_z_core(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ecp_z_core array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ecp_z_core will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ecp_z_core values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        nucleus_num = read_nucleus_num(trexio_file)

        dims_list = [nucleus_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ecp_z_core_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ecp_ang_mom(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ecp_ang_mom array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ecp_ang_mom will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ecp_ang_mom values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ecp_num = read_ecp_num(trexio_file)

        dims_list = [ecp_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ecp_ang_mom_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ecp_nucleus_index(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ecp_nucleus_index array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ecp_nucleus_index will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ecp_nucleus_index values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ecp_num = read_ecp_num(trexio_file)

        dims_list = [ecp_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ecp_nucleus_index_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ecp_exponent(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ecp_exponent array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ecp_exponent will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ecp_exponent values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ecp_num = read_ecp_num(trexio_file)

        dims_list = [ecp_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ecp_exponent_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ecp_coefficient(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ecp_coefficient array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ecp_coefficient will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ecp_coefficient values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ecp_num = read_ecp_num(trexio_file)

        dims_list = [ecp_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ecp_coefficient_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ecp_power(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ecp_power array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ecp_power will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ecp_power values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ecp_num = read_ecp_num(trexio_file)

        dims_list = [ecp_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ecp_power_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_grid_coord(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the grid_coord array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of grid_coord will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to grid_coord values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        grid_num = read_grid_num(trexio_file)

        dims_list = [grid_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_grid_coord_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_grid_weight(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the grid_weight array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of grid_weight will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to grid_weight values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        grid_num = read_grid_num(trexio_file)

        dims_list = [grid_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_grid_weight_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_grid_ang_coord(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the grid_ang_coord array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of grid_ang_coord will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to grid_ang_coord values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        grid_ang_num = read_grid_ang_num(trexio_file)

        dims_list = [grid_ang_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_grid_ang_coord_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_grid_ang_weight(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the grid_ang_weight array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of grid_ang_weight will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to grid_ang_weight values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        grid_ang_num = read_grid_ang_num(trexio_file)

        dims_list = [grid_ang_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_grid_ang_weight_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_grid_rad_coord(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the grid_rad_coord array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of grid_rad_coord will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to grid_rad_coord values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        grid_rad_num = read_grid_rad_num(trexio_file)

        dims_list = [grid_rad_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_grid_rad_coord_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_grid_rad_weight(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the grid_rad_weight array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of grid_rad_weight will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to grid_rad_weight values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        grid_rad_num = read_grid_rad_num(trexio_file)

        dims_list = [grid_rad_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_grid_rad_weight_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_shell(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ao_shell array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ao_shell will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ao_shell values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ao_num = read_ao_num(trexio_file)

        dims_list = [ao_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ao_shell_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_normalization(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ao_normalization array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ao_normalization will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ao_normalization values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ao_num = read_ao_num(trexio_file)

        dims_list = [ao_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ao_normalization_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_1e_int_overlap(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ao_1e_int_overlap array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ao_1e_int_overlap will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ao_1e_int_overlap values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ao_num = read_ao_num(trexio_file)

        dims_list = [ao_num, ao_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ao_1e_int_overlap_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_1e_int_kinetic(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ao_1e_int_kinetic array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ao_1e_int_kinetic will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ao_1e_int_kinetic values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ao_num = read_ao_num(trexio_file)

        dims_list = [ao_num, ao_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ao_1e_int_kinetic_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_1e_int_potential_n_e(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ao_1e_int_potential_n_e array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ao_1e_int_potential_n_e will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ao_1e_int_potential_n_e values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ao_num = read_ao_num(trexio_file)

        dims_list = [ao_num, ao_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ao_1e_int_potential_n_e_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_1e_int_ecp(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ao_1e_int_ecp array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ao_1e_int_ecp will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ao_1e_int_ecp values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ao_num = read_ao_num(trexio_file)

        dims_list = [ao_num, ao_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ao_1e_int_ecp_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_1e_int_core_hamiltonian(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ao_1e_int_core_hamiltonian array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ao_1e_int_core_hamiltonian will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ao_1e_int_core_hamiltonian values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ao_num = read_ao_num(trexio_file)

        dims_list = [ao_num, ao_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ao_1e_int_core_hamiltonian_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_1e_int_overlap_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ao_1e_int_overlap_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ao_1e_int_overlap_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ao_1e_int_overlap_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ao_num = read_ao_num(trexio_file)

        dims_list = [ao_num, ao_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ao_1e_int_overlap_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_1e_int_kinetic_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ao_1e_int_kinetic_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ao_1e_int_kinetic_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ao_1e_int_kinetic_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ao_num = read_ao_num(trexio_file)

        dims_list = [ao_num, ao_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ao_1e_int_kinetic_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_1e_int_potential_n_e_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ao_1e_int_potential_n_e_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ao_1e_int_potential_n_e_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ao_1e_int_potential_n_e_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ao_num = read_ao_num(trexio_file)

        dims_list = [ao_num, ao_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ao_1e_int_potential_n_e_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_1e_int_ecp_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ao_1e_int_ecp_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ao_1e_int_ecp_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ao_1e_int_ecp_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ao_num = read_ao_num(trexio_file)

        dims_list = [ao_num, ao_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ao_1e_int_ecp_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_1e_int_core_hamiltonian_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the ao_1e_int_core_hamiltonian_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of ao_1e_int_core_hamiltonian_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to ao_1e_int_core_hamiltonian_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        ao_num = read_ao_num(trexio_file)

        dims_list = [ao_num, ao_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_ao_1e_int_core_hamiltonian_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_coefficient(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_coefficient array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_coefficient will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_coefficient values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)
        ao_num = read_ao_num(trexio_file)

        dims_list = [mo_num, ao_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_coefficient_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_coefficient_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_coefficient_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_coefficient_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_coefficient_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)
        ao_num = read_ao_num(trexio_file)

        dims_list = [mo_num, ao_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_coefficient_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_occupation(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_occupation array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_occupation will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_occupation values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_occupation_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_energy(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_energy array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_energy will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_energy values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_energy_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_spin(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_spin array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_spin will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_spin values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_spin_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_k_point(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_k_point array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_k_point will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_k_point values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_k_point_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_1e_int_overlap(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_1e_int_overlap array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_1e_int_overlap will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_1e_int_overlap values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_1e_int_overlap_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_1e_int_kinetic(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_1e_int_kinetic array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_1e_int_kinetic will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_1e_int_kinetic values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_1e_int_kinetic_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_1e_int_potential_n_e(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_1e_int_potential_n_e array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_1e_int_potential_n_e will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_1e_int_potential_n_e values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_1e_int_potential_n_e_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_1e_int_ecp(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_1e_int_ecp array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_1e_int_ecp will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_1e_int_ecp values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_1e_int_ecp_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_1e_int_core_hamiltonian(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_1e_int_core_hamiltonian array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_1e_int_core_hamiltonian will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_1e_int_core_hamiltonian values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_1e_int_core_hamiltonian_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_1e_int_overlap_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_1e_int_overlap_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_1e_int_overlap_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_1e_int_overlap_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_1e_int_overlap_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_1e_int_kinetic_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_1e_int_kinetic_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_1e_int_kinetic_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_1e_int_kinetic_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_1e_int_kinetic_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_1e_int_potential_n_e_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_1e_int_potential_n_e_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_1e_int_potential_n_e_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_1e_int_potential_n_e_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_1e_int_potential_n_e_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_1e_int_ecp_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_1e_int_ecp_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_1e_int_ecp_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_1e_int_ecp_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_1e_int_ecp_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_mo_1e_int_core_hamiltonian_im(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the mo_1e_int_core_hamiltonian_im array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_1e_int_core_hamiltonian_im will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to mo_1e_int_core_hamiltonian_im values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_mo_1e_int_core_hamiltonian_im_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_rdm_1e(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the rdm_1e array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of rdm_1e will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to rdm_1e values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_rdm_1e_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_rdm_1e_up(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the rdm_1e_up array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of rdm_1e_up will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to rdm_1e_up values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_rdm_1e_up_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_rdm_1e_dn(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the rdm_1e_dn array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of rdm_1e_dn will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to rdm_1e_dn values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        mo_num = read_mo_num(trexio_file)

        dims_list = [mo_num, mo_num]
        dim_real  = 1
        for i in range(2):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_rdm_1e_dn_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_rdm_1e_transition(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the rdm_1e_transition array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of rdm_1e_transition will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to rdm_1e_transition values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        state_num = read_state_num(trexio_file)
        mo_num = read_mo_num(trexio_file)

        dims_list = [state_num, state_num, mo_num, mo_num]
        dim_real  = 1
        for i in range(4):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_rdm_1e_transition_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_jastrow_en(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the jastrow_en array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of jastrow_en will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to jastrow_en values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        jastrow_en_num = read_jastrow_en_num(trexio_file)

        dims_list = [jastrow_en_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_jastrow_en_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_jastrow_ee(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the jastrow_ee array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of jastrow_ee will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to jastrow_ee values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        jastrow_ee_num = read_jastrow_ee_num(trexio_file)

        dims_list = [jastrow_ee_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_jastrow_ee_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_jastrow_een(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the jastrow_een array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of jastrow_een will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to jastrow_een values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        jastrow_een_num = read_jastrow_een_num(trexio_file)

        dims_list = [jastrow_een_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_jastrow_een_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_jastrow_en_nucleus(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the jastrow_en_nucleus array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of jastrow_en_nucleus will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to jastrow_en_nucleus values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        jastrow_en_num = read_jastrow_en_num(trexio_file)

        dims_list = [jastrow_en_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_jastrow_en_nucleus_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_jastrow_een_nucleus(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the jastrow_een_nucleus array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of jastrow_een_nucleus will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to jastrow_een_nucleus values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        jastrow_een_num = read_jastrow_een_num(trexio_file)

        dims_list = [jastrow_een_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_jastrow_een_nucleus_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_jastrow_en_scaling(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the jastrow_en_scaling array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of jastrow_en_scaling will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to jastrow_en_scaling values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        nucleus_num = read_nucleus_num(trexio_file)

        dims_list = [nucleus_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_jastrow_en_scaling_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_qmc_point(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the qmc_point array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of qmc_point will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to qmc_point values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        qmc_num = read_qmc_num(trexio_file)
        electron_num = read_electron_num(trexio_file)

        dims_list = [qmc_num, electron_num, 3]
        dim_real  = 1
        for i in range(3):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_qmc_point_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_qmc_psi(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the qmc_psi array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of qmc_psi will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to qmc_psi values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        qmc_num = read_qmc_num(trexio_file)

        dims_list = [qmc_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_qmc_psi_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_qmc_e_loc(trexio_file, dim = None, doReshape = None, dtype = None):
    """Read the qmc_e_loc array of numbers from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of qmc_e_loc will be returned)
        If None, the function will read all necessary array dimensions from the file.

    dtype (Optional): type
        NumPy data type of the output (e.g. np.int32|int16 or np.float32|float16). If specified, the output array will be converted from the default double precision.

    doReshape (Optional): bool
        Flag to determine whether the output NumPy array has be reshaped or not. Be default, reshaping is performed
        based on the dimensions from the ~trex.json~ file. Otherwise, ~shape~ array (list or tuple) is used if provided by the user.

    Returns:
        ~dset_64~ if dtype is None or ~dset_converted~ otherwise: numpy.ndarray
        1D NumPy array with ~dim~ elements corresponding to qmc_e_loc values read from the TREXIO file.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
"""

    if doReshape is None:
        doReshape = True

    # if dim is not specified, read dimensions from the TREXIO file
    dims_list = None
    if doReshape:
        qmc_num = read_qmc_num(trexio_file)

        dims_list = [qmc_num]
        dim_real  = 1
        for i in range(1):
            dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    shape = tuple(dims_list)
    if shape is None and doReshape:
        raise ValueError("Reshaping failure: shape is None.")


    rc, dset_64 = pytr.trexio_read_safe_qmc_e_loc_64(trexio_file.pytrexio_s, dim)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    isConverted = False
    dset_converted = None
    if dtype is not None:
        try:
            assert isinstance(dtype, type)
        except AssertionError:
            raise TypeError("dtype argument has to be an instance of the type class (e.g. np.float32).")

        if not dtype==np.int64 or not dtype==np.float64:
            dset_converted = np.array(dset_64, dtype=dtype)
            isConverted = True

    # additional assert can be added here to check that read_safe functions returns numpy array of proper dimension

    if doReshape:
        # in-place reshaping did not work so I have to make a copy
        if isConverted:
            dset_reshaped = np.reshape(dset_converted, shape, order='C')
        else:
            dset_reshaped = np.reshape(dset_64, shape, order='C')

    if isConverted:
        return dset_converted
    elif doReshape:
        return dset_reshaped
    else:
        return dset_64

def read_ao_2e_int_eri(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the ao_2e_int_eri indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_ao_2e_int_eri_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_ao_2e_int_eri(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 4,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 4])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_ao_2e_int_eri_size(trexio_file) -> int:
    """Read the number of ao_2e_int_eri integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the ao_2e_int_eri sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_ao_2e_int_eri_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_ao_2e_int_eri_lr(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the ao_2e_int_eri_lr indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_ao_2e_int_eri_lr_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_ao_2e_int_eri_lr(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 4,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 4])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_ao_2e_int_eri_lr_size(trexio_file) -> int:
    """Read the number of ao_2e_int_eri_lr integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the ao_2e_int_eri_lr sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_ao_2e_int_eri_lr_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_ao_2e_int_eri_cholesky(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the ao_2e_int_eri_cholesky indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_ao_2e_int_eri_cholesky_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_ao_2e_int_eri_cholesky(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 3,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 3])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_ao_2e_int_eri_cholesky_size(trexio_file) -> int:
    """Read the number of ao_2e_int_eri_cholesky integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the ao_2e_int_eri_cholesky sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_ao_2e_int_eri_cholesky_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_ao_2e_int_eri_lr_cholesky(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the ao_2e_int_eri_lr_cholesky indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_ao_2e_int_eri_lr_cholesky_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_ao_2e_int_eri_lr_cholesky(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 3,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 3])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_ao_2e_int_eri_lr_cholesky_size(trexio_file) -> int:
    """Read the number of ao_2e_int_eri_lr_cholesky integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the ao_2e_int_eri_lr_cholesky sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_ao_2e_int_eri_lr_cholesky_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_mo_2e_int_eri(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the mo_2e_int_eri indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_mo_2e_int_eri_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_mo_2e_int_eri(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 4,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 4])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_mo_2e_int_eri_size(trexio_file) -> int:
    """Read the number of mo_2e_int_eri integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the mo_2e_int_eri sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_mo_2e_int_eri_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_mo_2e_int_eri_lr(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the mo_2e_int_eri_lr indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_mo_2e_int_eri_lr_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_mo_2e_int_eri_lr(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 4,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 4])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_mo_2e_int_eri_lr_size(trexio_file) -> int:
    """Read the number of mo_2e_int_eri_lr integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the mo_2e_int_eri_lr sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_mo_2e_int_eri_lr_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_mo_2e_int_eri_cholesky(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the mo_2e_int_eri_cholesky indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_mo_2e_int_eri_cholesky_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_mo_2e_int_eri_cholesky(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 3,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 3])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_mo_2e_int_eri_cholesky_size(trexio_file) -> int:
    """Read the number of mo_2e_int_eri_cholesky integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the mo_2e_int_eri_cholesky sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_mo_2e_int_eri_cholesky_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_mo_2e_int_eri_lr_cholesky(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the mo_2e_int_eri_lr_cholesky indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_mo_2e_int_eri_lr_cholesky_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_mo_2e_int_eri_lr_cholesky(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 3,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 3])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_mo_2e_int_eri_lr_cholesky_size(trexio_file) -> int:
    """Read the number of mo_2e_int_eri_lr_cholesky integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the mo_2e_int_eri_lr_cholesky sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_mo_2e_int_eri_lr_cholesky_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_csf_det_coefficient(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the csf_det_coefficient indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_csf_det_coefficient_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_csf_det_coefficient(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 2,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 2])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_csf_det_coefficient_size(trexio_file) -> int:
    """Read the number of csf_det_coefficient integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the csf_det_coefficient sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_csf_det_coefficient_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_amplitude_single(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the amplitude_single indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_amplitude_single_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_amplitude_single(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 2,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 2])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_amplitude_single_size(trexio_file) -> int:
    """Read the number of amplitude_single integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the amplitude_single sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_amplitude_single_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_amplitude_single_exp(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the amplitude_single_exp indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_amplitude_single_exp_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_amplitude_single_exp(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 2,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 2])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_amplitude_single_exp_size(trexio_file) -> int:
    """Read the number of amplitude_single_exp integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the amplitude_single_exp sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_amplitude_single_exp_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_amplitude_double(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the amplitude_double indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_amplitude_double_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_amplitude_double(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 4,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 4])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_amplitude_double_size(trexio_file) -> int:
    """Read the number of amplitude_double integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the amplitude_double sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_amplitude_double_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_amplitude_double_exp(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the amplitude_double_exp indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_amplitude_double_exp_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_amplitude_double_exp(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 4,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 4])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_amplitude_double_exp_size(trexio_file) -> int:
    """Read the number of amplitude_double_exp integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the amplitude_double_exp sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_amplitude_double_exp_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_amplitude_triple(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the amplitude_triple indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_amplitude_triple_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_amplitude_triple(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 6,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 6])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_amplitude_triple_size(trexio_file) -> int:
    """Read the number of amplitude_triple integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the amplitude_triple sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_amplitude_triple_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_amplitude_triple_exp(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the amplitude_triple_exp indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_amplitude_triple_exp_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_amplitude_triple_exp(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 6,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 6])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_amplitude_triple_exp_size(trexio_file) -> int:
    """Read the number of amplitude_triple_exp integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the amplitude_triple_exp sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_amplitude_triple_exp_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_amplitude_quadruple(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the amplitude_quadruple indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_amplitude_quadruple_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_amplitude_quadruple(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 8,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 8])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_amplitude_quadruple_size(trexio_file) -> int:
    """Read the number of amplitude_quadruple integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the amplitude_quadruple sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_amplitude_quadruple_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_amplitude_quadruple_exp(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the amplitude_quadruple_exp indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_amplitude_quadruple_exp_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_amplitude_quadruple_exp(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 8,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 8])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_amplitude_quadruple_exp_size(trexio_file) -> int:
    """Read the number of amplitude_quadruple_exp integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the amplitude_quadruple_exp sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_amplitude_quadruple_exp_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_rdm_2e(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the rdm_2e indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_rdm_2e_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_rdm_2e(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 4,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 4])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_rdm_2e_size(trexio_file) -> int:
    """Read the number of rdm_2e integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the rdm_2e sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_rdm_2e_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_rdm_2e_upup(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the rdm_2e_upup indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_rdm_2e_upup_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_rdm_2e_upup(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 4,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 4])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_rdm_2e_upup_size(trexio_file) -> int:
    """Read the number of rdm_2e_upup integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the rdm_2e_upup sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_rdm_2e_upup_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_rdm_2e_dndn(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the rdm_2e_dndn indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_rdm_2e_dndn_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_rdm_2e_dndn(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 4,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 4])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_rdm_2e_dndn_size(trexio_file) -> int:
    """Read the number of rdm_2e_dndn integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the rdm_2e_dndn sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_rdm_2e_dndn_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_rdm_2e_updn(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the rdm_2e_updn indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_rdm_2e_updn_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_rdm_2e_updn(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 4,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 4])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_rdm_2e_updn_size(trexio_file) -> int:
    """Read the number of rdm_2e_updn integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the rdm_2e_updn sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_rdm_2e_updn_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_rdm_2e_transition(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the rdm_2e_transition indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_rdm_2e_transition_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_rdm_2e_transition(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 6,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 6])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_rdm_2e_transition_size(trexio_file) -> int:
    """Read the number of rdm_2e_transition integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the rdm_2e_transition sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_rdm_2e_transition_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_rdm_2e_cholesky(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the rdm_2e_cholesky indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_rdm_2e_cholesky_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_rdm_2e_cholesky(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 3,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 3])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_rdm_2e_cholesky_size(trexio_file) -> int:
    """Read the number of rdm_2e_cholesky integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the rdm_2e_cholesky sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_rdm_2e_cholesky_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_rdm_2e_upup_cholesky(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the rdm_2e_upup_cholesky indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_rdm_2e_upup_cholesky_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_rdm_2e_upup_cholesky(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 3,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 3])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_rdm_2e_upup_cholesky_size(trexio_file) -> int:
    """Read the number of rdm_2e_upup_cholesky integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the rdm_2e_upup_cholesky sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_rdm_2e_upup_cholesky_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_rdm_2e_dndn_cholesky(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the rdm_2e_dndn_cholesky indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_rdm_2e_dndn_cholesky_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_rdm_2e_dndn_cholesky(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 3,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 3])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_rdm_2e_dndn_cholesky_size(trexio_file) -> int:
    """Read the number of rdm_2e_dndn_cholesky integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the rdm_2e_dndn_cholesky sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_rdm_2e_dndn_cholesky_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_rdm_2e_updn_cholesky(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read the rdm_2e_updn_cholesky indices and values from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when reading.

    buffer_size: int
        The number of integrals to read from the file.

    Returns:
        (indices, values, n_int_read, eof_flag) tuple where
          - indices and values are NumPy arrays [numpy.ndarray] with the default int32 and float64 precision, respectively;
          - n_int_read [int] is the number of integrals read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS
            and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of integrals already in the file
    integral_num = read_rdm_2e_updn_cholesky_size(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - integral_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # as the last 2 arguments (for numpy arrays of indices and values, respectively)
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, indices, values = pytr.trexio_read_safe_rdm_2e_updn_cholesky(trexio_file.pytrexio_s,
                                                                         offset_file,
                                                                         verified_size,
                                                                         verified_size * 3,
                                                                         verified_size)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if indices is None or values is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array of indices according to group_dset_rank
    shape = tuple([verified_size, 3])
    indices_reshaped = np.reshape(indices, shape, order='C')

    return (indices_reshaped, values, n_int_read, eof_flag)


def read_rdm_2e_updn_cholesky_size(trexio_file) -> int:
    """Read the number of rdm_2e_updn_cholesky integrals stored in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num_integral~: int
        Integer value of corresponding to the size of the rdm_2e_updn_cholesky sparse array from ~trexio_file~.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num_integral = pytr.trexio_read_rdm_2e_updn_cholesky_size(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num_integral

def read_metadata_code(trexio_file, dim = None) -> list:
    """Read the metadata_code array of strings from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of metadata_code will be returned)
        If None, the function will read all necessary array dimensions from the file.

    Returns:
        ~dset_r~: list
        1D list with ~dim~ elements corresponding to metadata_code strings read from the TREXIO file.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    metadata_code_num = read_metadata_code_num(trexio_file)

    dims_list = [metadata_code_num]
    dim_real  = 1
    for i in range(1):
        dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    rc, dset_1d_r = pytr.trexio_read_metadata_code_low(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    dset_full = dset_1d_r.split(pytr.TREXIO_DELIM)
    dset_2d_r = [dset_full[i] for i in range(dim) if dset_full[i]]
    if not dset_2d_r:
        raise ValueError(f"Output of {read_metadata_code.__name__} function cannot be an empty list.")

    return dset_2d_r

def read_metadata_author(trexio_file, dim = None) -> list:
    """Read the metadata_author array of strings from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of metadata_author will be returned)
        If None, the function will read all necessary array dimensions from the file.

    Returns:
        ~dset_r~: list
        1D list with ~dim~ elements corresponding to metadata_author strings read from the TREXIO file.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    metadata_author_num = read_metadata_author_num(trexio_file)

    dims_list = [metadata_author_num]
    dim_real  = 1
    for i in range(1):
        dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    rc, dset_1d_r = pytr.trexio_read_metadata_author_low(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    dset_full = dset_1d_r.split(pytr.TREXIO_DELIM)
    dset_2d_r = [dset_full[i] for i in range(dim) if dset_full[i]]
    if not dset_2d_r:
        raise ValueError(f"Output of {read_metadata_author.__name__} function cannot be an empty list.")

    return dset_2d_r

def read_nucleus_label(trexio_file, dim = None) -> list:
    """Read the nucleus_label array of strings from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of nucleus_label will be returned)
        If None, the function will read all necessary array dimensions from the file.

    Returns:
        ~dset_r~: list
        1D list with ~dim~ elements corresponding to nucleus_label strings read from the TREXIO file.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    nucleus_num = read_nucleus_num(trexio_file)

    dims_list = [nucleus_num]
    dim_real  = 1
    for i in range(1):
        dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    rc, dset_1d_r = pytr.trexio_read_nucleus_label_low(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    dset_full = dset_1d_r.split(pytr.TREXIO_DELIM)
    dset_2d_r = [dset_full[i] for i in range(dim) if dset_full[i]]
    if not dset_2d_r:
        raise ValueError(f"Output of {read_nucleus_label.__name__} function cannot be an empty list.")

    return dset_2d_r

def read_state_label(trexio_file, dim = None) -> list:
    """Read the state_label array of strings from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of state_label will be returned)
        If None, the function will read all necessary array dimensions from the file.

    Returns:
        ~dset_r~: list
        1D list with ~dim~ elements corresponding to state_label strings read from the TREXIO file.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    state_num = read_state_num(trexio_file)

    dims_list = [state_num]
    dim_real  = 1
    for i in range(1):
        dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    rc, dset_1d_r = pytr.trexio_read_state_label_low(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    dset_full = dset_1d_r.split(pytr.TREXIO_DELIM)
    dset_2d_r = [dset_full[i] for i in range(dim) if dset_full[i]]
    if not dset_2d_r:
        raise ValueError(f"Output of {read_state_label.__name__} function cannot be an empty list.")

    return dset_2d_r

def read_state_file_name(trexio_file, dim = None) -> list:
    """Read the state_file_name array of strings from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of state_file_name will be returned)
        If None, the function will read all necessary array dimensions from the file.

    Returns:
        ~dset_r~: list
        1D list with ~dim~ elements corresponding to state_file_name strings read from the TREXIO file.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    state_num = read_state_num(trexio_file)

    dims_list = [state_num]
    dim_real  = 1
    for i in range(1):
        dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    rc, dset_1d_r = pytr.trexio_read_state_file_name_low(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    dset_full = dset_1d_r.split(pytr.TREXIO_DELIM)
    dset_2d_r = [dset_full[i] for i in range(dim) if dset_full[i]]
    if not dset_2d_r:
        raise ValueError(f"Output of {read_state_file_name.__name__} function cannot be an empty list.")

    return dset_2d_r

def read_mo_class(trexio_file, dim = None) -> list:
    """Read the mo_class array of strings from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_class will be returned)
        If None, the function will read all necessary array dimensions from the file.

    Returns:
        ~dset_r~: list
        1D list with ~dim~ elements corresponding to mo_class strings read from the TREXIO file.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    mo_num = read_mo_num(trexio_file)

    dims_list = [mo_num]
    dim_real  = 1
    for i in range(1):
        dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    rc, dset_1d_r = pytr.trexio_read_mo_class_low(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    dset_full = dset_1d_r.split(pytr.TREXIO_DELIM)
    dset_2d_r = [dset_full[i] for i in range(dim) if dset_full[i]]
    if not dset_2d_r:
        raise ValueError(f"Output of {read_mo_class.__name__} function cannot be an empty list.")

    return dset_2d_r

def read_mo_symmetry(trexio_file, dim = None) -> list:
    """Read the mo_symmetry array of strings from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dim (Optional): int
        Size of the block to be read from the file (i.e. how many items of mo_symmetry will be returned)
        If None, the function will read all necessary array dimensions from the file.

    Returns:
        ~dset_r~: list
        1D list with ~dim~ elements corresponding to mo_symmetry strings read from the TREXIO file.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    mo_num = read_mo_num(trexio_file)

    dims_list = [mo_num]
    dim_real  = 1
    for i in range(1):
        dim_real *= dims_list[i]

    if dim:
        if dim_real != dim:
            raise Error(TREXIO_UNSAFE_ARRAY_DIM)
    else:
        dim = dim_real

    rc, dset_1d_r = pytr.trexio_read_mo_symmetry_low(trexio_file.pytrexio_s, PYTREXIO_MAX_STR_LENGTH)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)


    dset_full = dset_1d_r.split(pytr.TREXIO_DELIM)
    dset_2d_r = [dset_full[i] for i in range(dim) if dset_full[i]]
    if not dset_2d_r:
        raise ValueError(f"Output of {read_mo_symmetry.__name__} function cannot be an empty list.")

    return dset_2d_r

def write_metadata_code_num(trexio_file, num_w: int) -> None:
    """Write the metadata_code_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the metadata_code_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_metadata_code_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_metadata_author_num(trexio_file, num_w: int) -> None:
    """Write the metadata_author_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the metadata_author_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_metadata_author_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_metadata_unsafe(trexio_file, num_w: int) -> None:
    """Write the metadata_unsafe variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the metadata_unsafe variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_metadata_unsafe(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_nucleus_num(trexio_file, num_w: int) -> None:
    """Write the nucleus_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the nucleus_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_nucleus_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_nucleus_repulsion(trexio_file, num_w: float) -> None:
    """Write the nucleus_repulsion variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the nucleus_repulsion variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_nucleus_repulsion(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_cell_two_pi(trexio_file, num_w: int) -> None:
    """Write the cell_two_pi variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the cell_two_pi variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_cell_two_pi(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_pbc_periodic(trexio_file, num_w: int) -> None:
    """Write the pbc_periodic variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the pbc_periodic variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_pbc_periodic(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_pbc_k_point_num(trexio_file, num_w: int) -> None:
    """Write the pbc_k_point_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the pbc_k_point_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_pbc_k_point_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_pbc_madelung(trexio_file, num_w: float) -> None:
    """Write the pbc_madelung variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the pbc_madelung variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_pbc_madelung(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_electron_num(trexio_file, num_w: int) -> None:
    """Write the electron_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the electron_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_electron_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_electron_up_num(trexio_file, num_w: int) -> None:
    """Write the electron_up_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the electron_up_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_electron_up_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_electron_dn_num(trexio_file, num_w: int) -> None:
    """Write the electron_dn_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the electron_dn_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_electron_dn_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_state_num(trexio_file, num_w: int) -> None:
    """Write the state_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the state_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_state_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_state_id(trexio_file, num_w: int) -> None:
    """Write the state_id variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the state_id variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_state_id(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_state_energy(trexio_file, num_w: float) -> None:
    """Write the state_energy variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the state_energy variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_state_energy(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_prim_num(trexio_file, num_w: int) -> None:
    """Write the basis_prim_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the basis_prim_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_basis_prim_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_shell_num(trexio_file, num_w: int) -> None:
    """Write the basis_shell_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the basis_shell_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_basis_shell_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_nao_grid_num(trexio_file, num_w: int) -> None:
    """Write the basis_nao_grid_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the basis_nao_grid_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_basis_nao_grid_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_interp_coeff_cnt(trexio_file, num_w: int) -> None:
    """Write the basis_interp_coeff_cnt variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the basis_interp_coeff_cnt variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_basis_interp_coeff_cnt(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_e_cut(trexio_file, num_w: float) -> None:
    """Write the basis_e_cut variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the basis_e_cut variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_basis_e_cut(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ecp_num(trexio_file, num_w: int) -> None:
    """Write the ecp_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the ecp_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_ecp_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_rad_precision(trexio_file, num_w: float) -> None:
    """Write the grid_rad_precision variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the grid_rad_precision variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_grid_rad_precision(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_num(trexio_file, num_w: int) -> None:
    """Write the grid_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the grid_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_grid_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_max_ang_num(trexio_file, num_w: int) -> None:
    """Write the grid_max_ang_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the grid_max_ang_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_grid_max_ang_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_min_ang_num(trexio_file, num_w: int) -> None:
    """Write the grid_min_ang_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the grid_min_ang_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_grid_min_ang_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_ang_num(trexio_file, num_w: int) -> None:
    """Write the grid_ang_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the grid_ang_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_grid_ang_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_rad_num(trexio_file, num_w: int) -> None:
    """Write the grid_rad_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the grid_rad_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_grid_rad_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_cartesian(trexio_file, num_w: int) -> None:
    """Write the ao_cartesian variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the ao_cartesian variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_ao_cartesian(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_num(trexio_file, num_w: int) -> None:
    """Write the ao_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the ao_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_ao_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_2e_int_eri_cholesky_num(trexio_file, num_w: int) -> None:
    """Write the ao_2e_int_eri_cholesky_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the ao_2e_int_eri_cholesky_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_ao_2e_int_eri_cholesky_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_2e_int_eri_lr_cholesky_num(trexio_file, num_w: int) -> None:
    """Write the ao_2e_int_eri_lr_cholesky_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the ao_2e_int_eri_lr_cholesky_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_ao_2e_int_eri_lr_cholesky_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_num(trexio_file, num_w: int) -> None:
    """Write the mo_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the mo_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_mo_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_2e_int_eri_cholesky_num(trexio_file, num_w: int) -> None:
    """Write the mo_2e_int_eri_cholesky_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the mo_2e_int_eri_cholesky_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_mo_2e_int_eri_cholesky_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_2e_int_eri_lr_cholesky_num(trexio_file, num_w: int) -> None:
    """Write the mo_2e_int_eri_lr_cholesky_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the mo_2e_int_eri_lr_cholesky_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_mo_2e_int_eri_lr_cholesky_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_csf_num(trexio_file, num_w: int) -> None:
    """Write the csf_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the csf_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_csf_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e_cholesky_num(trexio_file, num_w: int) -> None:
    """Write the rdm_2e_cholesky_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the rdm_2e_cholesky_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_rdm_2e_cholesky_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e_upup_cholesky_num(trexio_file, num_w: int) -> None:
    """Write the rdm_2e_upup_cholesky_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the rdm_2e_upup_cholesky_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_rdm_2e_upup_cholesky_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e_dndn_cholesky_num(trexio_file, num_w: int) -> None:
    """Write the rdm_2e_dndn_cholesky_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the rdm_2e_dndn_cholesky_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_rdm_2e_dndn_cholesky_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e_updn_cholesky_num(trexio_file, num_w: int) -> None:
    """Write the rdm_2e_updn_cholesky_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the rdm_2e_updn_cholesky_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_rdm_2e_updn_cholesky_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_jastrow_en_num(trexio_file, num_w: int) -> None:
    """Write the jastrow_en_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the jastrow_en_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_jastrow_en_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_jastrow_ee_num(trexio_file, num_w: int) -> None:
    """Write the jastrow_ee_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the jastrow_ee_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_jastrow_ee_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_jastrow_een_num(trexio_file, num_w: int) -> None:
    """Write the jastrow_een_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the jastrow_een_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_jastrow_een_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_jastrow_ee_scaling(trexio_file, num_w: float) -> None:
    """Write the jastrow_ee_scaling variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the jastrow_ee_scaling variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_jastrow_ee_scaling(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_qmc_num(trexio_file, num_w: int) -> None:
    """Write the qmc_num variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    num_w: int
        Value of the qmc_num variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_write_qmc_num(trexio_file.pytrexio_s, num_w)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_metadata_package_version(trexio_file, str_w: str) -> None:
    """Write the metadata_package_version variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    str_w: str
        String corresponding to the metadata_package_version variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(str_w) + 1

    rc = pytr.trexio_write_metadata_package_version(trexio_file.pytrexio_s, str_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_metadata_description(trexio_file, str_w: str) -> None:
    """Write the metadata_description variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    str_w: str
        String corresponding to the metadata_description variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(str_w) + 1

    rc = pytr.trexio_write_metadata_description(trexio_file.pytrexio_s, str_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_nucleus_point_group(trexio_file, str_w: str) -> None:
    """Write the nucleus_point_group variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    str_w: str
        String corresponding to the nucleus_point_group variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(str_w) + 1

    rc = pytr.trexio_write_nucleus_point_group(trexio_file.pytrexio_s, str_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_state_current_label(trexio_file, str_w: str) -> None:
    """Write the state_current_label variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    str_w: str
        String corresponding to the state_current_label variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(str_w) + 1

    rc = pytr.trexio_write_state_current_label(trexio_file.pytrexio_s, str_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_type(trexio_file, str_w: str) -> None:
    """Write the basis_type variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    str_w: str
        String corresponding to the basis_type variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(str_w) + 1

    rc = pytr.trexio_write_basis_type(trexio_file.pytrexio_s, str_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_oscillation_kind(trexio_file, str_w: str) -> None:
    """Write the basis_oscillation_kind variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    str_w: str
        String corresponding to the basis_oscillation_kind variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(str_w) + 1

    rc = pytr.trexio_write_basis_oscillation_kind(trexio_file.pytrexio_s, str_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_interpolator_kind(trexio_file, str_w: str) -> None:
    """Write the basis_interpolator_kind variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    str_w: str
        String corresponding to the basis_interpolator_kind variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(str_w) + 1

    rc = pytr.trexio_write_basis_interpolator_kind(trexio_file.pytrexio_s, str_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_description(trexio_file, str_w: str) -> None:
    """Write the grid_description variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    str_w: str
        String corresponding to the grid_description variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(str_w) + 1

    rc = pytr.trexio_write_grid_description(trexio_file.pytrexio_s, str_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_type(trexio_file, str_w: str) -> None:
    """Write the mo_type variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    str_w: str
        String corresponding to the mo_type variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(str_w) + 1

    rc = pytr.trexio_write_mo_type(trexio_file.pytrexio_s, str_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_jastrow_type(trexio_file, str_w: str) -> None:
    """Write the jastrow_type variable in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    str_w: str
        String corresponding to the jastrow_type variable to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(str_w) + 1

    rc = pytr.trexio_write_jastrow_type(trexio_file.pytrexio_s, str_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_determinant_coefficient(trexio_file: File, offset_file: int, buffer_size: int, dset) -> None:
    """Write the determinant_coefficient in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of values to be skipped in the file when writing.

    buffer_size: int
        The number of values to write in the file.

    dset: list OR numpy.ndarray
        Array of determinant_coefficient to be written. If array data type does not correspond to int64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(dset, (list, tuple, np.ndarray)):
        raise TypeError("dset argument has to be an array (list, tuple or NumPy ndarray).")

    if isinstance(dset, np.ndarray) and not dset.dtype==np.float64:
        # convert to float64 if input is in a different precision
        dset_64 = np.float64(dset)
        rc = pytr.trexio_write_safe_determinant_coefficient(trexio_file.pytrexio_s, offset_file, buffer_size, dset_64)
    else:
        rc = pytr.trexio_write_safe_determinant_coefficient(trexio_file.pytrexio_s, offset_file, buffer_size, dset)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_csf_coefficient(trexio_file: File, offset_file: int, buffer_size: int, dset) -> None:
    """Write the csf_coefficient in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of values to be skipped in the file when writing.

    buffer_size: int
        The number of values to write in the file.

    dset: list OR numpy.ndarray
        Array of csf_coefficient to be written. If array data type does not correspond to int64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(dset, (list, tuple, np.ndarray)):
        raise TypeError("dset argument has to be an array (list, tuple or NumPy ndarray).")

    if isinstance(dset, np.ndarray) and not dset.dtype==np.float64:
        # convert to float64 if input is in a different precision
        dset_64 = np.float64(dset)
        rc = pytr.trexio_write_safe_csf_coefficient(trexio_file.pytrexio_s, offset_file, buffer_size, dset_64)
    else:
        rc = pytr.trexio_write_safe_csf_coefficient(trexio_file.pytrexio_s, offset_file, buffer_size, dset)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_nucleus_charge(trexio_file, dset_w) -> None:
    """Write the nucleus_charge array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of nucleus_charge values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_nucleus_charge_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_nucleus_charge_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_nucleus_charge_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_nucleus_coord(trexio_file, dset_w) -> None:
    """Write the nucleus_coord array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of nucleus_coord values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_nucleus_coord_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_nucleus_coord_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_nucleus_coord_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_cell_a(trexio_file, dset_w) -> None:
    """Write the cell_a array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of cell_a values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_cell_a_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_cell_a_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_cell_a_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_cell_b(trexio_file, dset_w) -> None:
    """Write the cell_b array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of cell_b values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_cell_b_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_cell_b_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_cell_b_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_cell_c(trexio_file, dset_w) -> None:
    """Write the cell_c array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of cell_c values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_cell_c_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_cell_c_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_cell_c_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_cell_g_a(trexio_file, dset_w) -> None:
    """Write the cell_g_a array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of cell_g_a values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_cell_g_a_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_cell_g_a_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_cell_g_a_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_cell_g_b(trexio_file, dset_w) -> None:
    """Write the cell_g_b array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of cell_g_b values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_cell_g_b_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_cell_g_b_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_cell_g_b_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_cell_g_c(trexio_file, dset_w) -> None:
    """Write the cell_g_c array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of cell_g_c values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_cell_g_c_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_cell_g_c_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_cell_g_c_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_pbc_k_point(trexio_file, dset_w) -> None:
    """Write the pbc_k_point array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of pbc_k_point values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_pbc_k_point_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_pbc_k_point_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_pbc_k_point_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_pbc_k_point_weight(trexio_file, dset_w) -> None:
    """Write the pbc_k_point_weight array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of pbc_k_point_weight values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_pbc_k_point_weight_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_pbc_k_point_weight_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_pbc_k_point_weight_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_nucleus_index(trexio_file, dset_w) -> None:
    """Write the basis_nucleus_index array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_nucleus_index values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_nucleus_index_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_nucleus_index_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_nucleus_index_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_shell_ang_mom(trexio_file, dset_w) -> None:
    """Write the basis_shell_ang_mom array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_shell_ang_mom values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_shell_ang_mom_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_shell_ang_mom_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_shell_ang_mom_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_shell_factor(trexio_file, dset_w) -> None:
    """Write the basis_shell_factor array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_shell_factor values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_shell_factor_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_shell_factor_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_shell_factor_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_r_power(trexio_file, dset_w) -> None:
    """Write the basis_r_power array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_r_power values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_r_power_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_r_power_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_r_power_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_nao_grid_start(trexio_file, dset_w) -> None:
    """Write the basis_nao_grid_start array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_nao_grid_start values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_nao_grid_start_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_nao_grid_start_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_nao_grid_start_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_nao_grid_size(trexio_file, dset_w) -> None:
    """Write the basis_nao_grid_size array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_nao_grid_size values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_nao_grid_size_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_nao_grid_size_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_nao_grid_size_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_shell_index(trexio_file, dset_w) -> None:
    """Write the basis_shell_index array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_shell_index values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_shell_index_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_shell_index_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_shell_index_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_exponent(trexio_file, dset_w) -> None:
    """Write the basis_exponent array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_exponent values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_exponent_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_exponent_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_exponent_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_exponent_im(trexio_file, dset_w) -> None:
    """Write the basis_exponent_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_exponent_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_exponent_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_exponent_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_exponent_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_coefficient(trexio_file, dset_w) -> None:
    """Write the basis_coefficient array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_coefficient values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_coefficient_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_coefficient_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_coefficient_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_coefficient_im(trexio_file, dset_w) -> None:
    """Write the basis_coefficient_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_coefficient_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_coefficient_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_coefficient_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_coefficient_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_oscillation_arg(trexio_file, dset_w) -> None:
    """Write the basis_oscillation_arg array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_oscillation_arg values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_oscillation_arg_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_oscillation_arg_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_oscillation_arg_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_prim_factor(trexio_file, dset_w) -> None:
    """Write the basis_prim_factor array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_prim_factor values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_prim_factor_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_prim_factor_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_prim_factor_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_nao_grid_radius(trexio_file, dset_w) -> None:
    """Write the basis_nao_grid_radius array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_nao_grid_radius values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_nao_grid_radius_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_nao_grid_radius_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_nao_grid_radius_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_nao_grid_phi(trexio_file, dset_w) -> None:
    """Write the basis_nao_grid_phi array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_nao_grid_phi values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_nao_grid_phi_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_nao_grid_phi_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_nao_grid_phi_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_nao_grid_grad(trexio_file, dset_w) -> None:
    """Write the basis_nao_grid_grad array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_nao_grid_grad values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_nao_grid_grad_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_nao_grid_grad_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_nao_grid_grad_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_nao_grid_lap(trexio_file, dset_w) -> None:
    """Write the basis_nao_grid_lap array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_nao_grid_lap values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_nao_grid_lap_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_nao_grid_lap_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_nao_grid_lap_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_interpolator_phi(trexio_file, dset_w) -> None:
    """Write the basis_interpolator_phi array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_interpolator_phi values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_interpolator_phi_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_interpolator_phi_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_interpolator_phi_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_interpolator_grad(trexio_file, dset_w) -> None:
    """Write the basis_interpolator_grad array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_interpolator_grad values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_interpolator_grad_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_interpolator_grad_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_interpolator_grad_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_basis_interpolator_lap(trexio_file, dset_w) -> None:
    """Write the basis_interpolator_lap array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of basis_interpolator_lap values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_basis_interpolator_lap_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_basis_interpolator_lap_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_basis_interpolator_lap_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ecp_max_ang_mom_plus_1(trexio_file, dset_w) -> None:
    """Write the ecp_max_ang_mom_plus_1 array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ecp_max_ang_mom_plus_1 values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ecp_max_ang_mom_plus_1_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ecp_max_ang_mom_plus_1_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ecp_max_ang_mom_plus_1_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ecp_z_core(trexio_file, dset_w) -> None:
    """Write the ecp_z_core array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ecp_z_core values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ecp_z_core_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ecp_z_core_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ecp_z_core_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ecp_ang_mom(trexio_file, dset_w) -> None:
    """Write the ecp_ang_mom array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ecp_ang_mom values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ecp_ang_mom_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ecp_ang_mom_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ecp_ang_mom_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ecp_nucleus_index(trexio_file, dset_w) -> None:
    """Write the ecp_nucleus_index array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ecp_nucleus_index values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ecp_nucleus_index_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ecp_nucleus_index_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ecp_nucleus_index_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ecp_exponent(trexio_file, dset_w) -> None:
    """Write the ecp_exponent array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ecp_exponent values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ecp_exponent_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ecp_exponent_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ecp_exponent_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ecp_coefficient(trexio_file, dset_w) -> None:
    """Write the ecp_coefficient array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ecp_coefficient values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ecp_coefficient_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ecp_coefficient_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ecp_coefficient_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ecp_power(trexio_file, dset_w) -> None:
    """Write the ecp_power array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ecp_power values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ecp_power_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ecp_power_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ecp_power_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_coord(trexio_file, dset_w) -> None:
    """Write the grid_coord array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of grid_coord values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_grid_coord_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_grid_coord_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_grid_coord_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_weight(trexio_file, dset_w) -> None:
    """Write the grid_weight array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of grid_weight values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_grid_weight_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_grid_weight_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_grid_weight_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_ang_coord(trexio_file, dset_w) -> None:
    """Write the grid_ang_coord array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of grid_ang_coord values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_grid_ang_coord_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_grid_ang_coord_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_grid_ang_coord_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_ang_weight(trexio_file, dset_w) -> None:
    """Write the grid_ang_weight array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of grid_ang_weight values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_grid_ang_weight_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_grid_ang_weight_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_grid_ang_weight_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_rad_coord(trexio_file, dset_w) -> None:
    """Write the grid_rad_coord array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of grid_rad_coord values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_grid_rad_coord_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_grid_rad_coord_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_grid_rad_coord_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_grid_rad_weight(trexio_file, dset_w) -> None:
    """Write the grid_rad_weight array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of grid_rad_weight values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_grid_rad_weight_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_grid_rad_weight_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_grid_rad_weight_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_shell(trexio_file, dset_w) -> None:
    """Write the ao_shell array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ao_shell values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ao_shell_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ao_shell_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ao_shell_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_normalization(trexio_file, dset_w) -> None:
    """Write the ao_normalization array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ao_normalization values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ao_normalization_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ao_normalization_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ao_normalization_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_1e_int_overlap(trexio_file, dset_w) -> None:
    """Write the ao_1e_int_overlap array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ao_1e_int_overlap values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ao_1e_int_overlap_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ao_1e_int_overlap_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ao_1e_int_overlap_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_1e_int_kinetic(trexio_file, dset_w) -> None:
    """Write the ao_1e_int_kinetic array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ao_1e_int_kinetic values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ao_1e_int_kinetic_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ao_1e_int_kinetic_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ao_1e_int_kinetic_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_1e_int_potential_n_e(trexio_file, dset_w) -> None:
    """Write the ao_1e_int_potential_n_e array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ao_1e_int_potential_n_e values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ao_1e_int_potential_n_e_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ao_1e_int_potential_n_e_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ao_1e_int_potential_n_e_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_1e_int_ecp(trexio_file, dset_w) -> None:
    """Write the ao_1e_int_ecp array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ao_1e_int_ecp values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ao_1e_int_ecp_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ao_1e_int_ecp_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ao_1e_int_ecp_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_1e_int_core_hamiltonian(trexio_file, dset_w) -> None:
    """Write the ao_1e_int_core_hamiltonian array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ao_1e_int_core_hamiltonian values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ao_1e_int_core_hamiltonian_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ao_1e_int_core_hamiltonian_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ao_1e_int_core_hamiltonian_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_1e_int_overlap_im(trexio_file, dset_w) -> None:
    """Write the ao_1e_int_overlap_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ao_1e_int_overlap_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ao_1e_int_overlap_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ao_1e_int_overlap_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ao_1e_int_overlap_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_1e_int_kinetic_im(trexio_file, dset_w) -> None:
    """Write the ao_1e_int_kinetic_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ao_1e_int_kinetic_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ao_1e_int_kinetic_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ao_1e_int_kinetic_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ao_1e_int_kinetic_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_1e_int_potential_n_e_im(trexio_file, dset_w) -> None:
    """Write the ao_1e_int_potential_n_e_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ao_1e_int_potential_n_e_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ao_1e_int_potential_n_e_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ao_1e_int_potential_n_e_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ao_1e_int_potential_n_e_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_1e_int_ecp_im(trexio_file, dset_w) -> None:
    """Write the ao_1e_int_ecp_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ao_1e_int_ecp_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ao_1e_int_ecp_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ao_1e_int_ecp_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ao_1e_int_ecp_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_1e_int_core_hamiltonian_im(trexio_file, dset_w) -> None:
    """Write the ao_1e_int_core_hamiltonian_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of ao_1e_int_core_hamiltonian_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_ao_1e_int_core_hamiltonian_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_ao_1e_int_core_hamiltonian_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_ao_1e_int_core_hamiltonian_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_coefficient(trexio_file, dset_w) -> None:
    """Write the mo_coefficient array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_coefficient values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_coefficient_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_coefficient_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_coefficient_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_coefficient_im(trexio_file, dset_w) -> None:
    """Write the mo_coefficient_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_coefficient_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_coefficient_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_coefficient_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_coefficient_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_occupation(trexio_file, dset_w) -> None:
    """Write the mo_occupation array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_occupation values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_occupation_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_occupation_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_occupation_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_energy(trexio_file, dset_w) -> None:
    """Write the mo_energy array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_energy values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_energy_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_energy_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_energy_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_spin(trexio_file, dset_w) -> None:
    """Write the mo_spin array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_spin values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_spin_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_spin_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_spin_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_k_point(trexio_file, dset_w) -> None:
    """Write the mo_k_point array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_k_point values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_k_point_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_k_point_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_k_point_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_1e_int_overlap(trexio_file, dset_w) -> None:
    """Write the mo_1e_int_overlap array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_1e_int_overlap values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_1e_int_overlap_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_1e_int_overlap_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_1e_int_overlap_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_1e_int_kinetic(trexio_file, dset_w) -> None:
    """Write the mo_1e_int_kinetic array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_1e_int_kinetic values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_1e_int_kinetic_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_1e_int_kinetic_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_1e_int_kinetic_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_1e_int_potential_n_e(trexio_file, dset_w) -> None:
    """Write the mo_1e_int_potential_n_e array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_1e_int_potential_n_e values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_1e_int_potential_n_e_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_1e_int_potential_n_e_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_1e_int_potential_n_e_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_1e_int_ecp(trexio_file, dset_w) -> None:
    """Write the mo_1e_int_ecp array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_1e_int_ecp values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_1e_int_ecp_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_1e_int_ecp_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_1e_int_ecp_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_1e_int_core_hamiltonian(trexio_file, dset_w) -> None:
    """Write the mo_1e_int_core_hamiltonian array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_1e_int_core_hamiltonian values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_1e_int_core_hamiltonian_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_1e_int_core_hamiltonian_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_1e_int_core_hamiltonian_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_1e_int_overlap_im(trexio_file, dset_w) -> None:
    """Write the mo_1e_int_overlap_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_1e_int_overlap_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_1e_int_overlap_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_1e_int_overlap_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_1e_int_overlap_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_1e_int_kinetic_im(trexio_file, dset_w) -> None:
    """Write the mo_1e_int_kinetic_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_1e_int_kinetic_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_1e_int_kinetic_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_1e_int_kinetic_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_1e_int_kinetic_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_1e_int_potential_n_e_im(trexio_file, dset_w) -> None:
    """Write the mo_1e_int_potential_n_e_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_1e_int_potential_n_e_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_1e_int_potential_n_e_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_1e_int_potential_n_e_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_1e_int_potential_n_e_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_1e_int_ecp_im(trexio_file, dset_w) -> None:
    """Write the mo_1e_int_ecp_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_1e_int_ecp_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_1e_int_ecp_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_1e_int_ecp_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_1e_int_ecp_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_1e_int_core_hamiltonian_im(trexio_file, dset_w) -> None:
    """Write the mo_1e_int_core_hamiltonian_im array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of mo_1e_int_core_hamiltonian_im values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_mo_1e_int_core_hamiltonian_im_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_mo_1e_int_core_hamiltonian_im_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_mo_1e_int_core_hamiltonian_im_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_1e(trexio_file, dset_w) -> None:
    """Write the rdm_1e array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of rdm_1e values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_rdm_1e_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_rdm_1e_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_rdm_1e_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_1e_up(trexio_file, dset_w) -> None:
    """Write the rdm_1e_up array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of rdm_1e_up values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_rdm_1e_up_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_rdm_1e_up_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_rdm_1e_up_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_1e_dn(trexio_file, dset_w) -> None:
    """Write the rdm_1e_dn array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of rdm_1e_dn values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_rdm_1e_dn_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_rdm_1e_dn_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_rdm_1e_dn_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_1e_transition(trexio_file, dset_w) -> None:
    """Write the rdm_1e_transition array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of rdm_1e_transition values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_rdm_1e_transition_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_rdm_1e_transition_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_rdm_1e_transition_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_jastrow_en(trexio_file, dset_w) -> None:
    """Write the jastrow_en array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of jastrow_en values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_jastrow_en_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_jastrow_en_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_jastrow_en_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_jastrow_ee(trexio_file, dset_w) -> None:
    """Write the jastrow_ee array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of jastrow_ee values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_jastrow_ee_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_jastrow_ee_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_jastrow_ee_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_jastrow_een(trexio_file, dset_w) -> None:
    """Write the jastrow_een array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of jastrow_een values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_jastrow_een_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_jastrow_een_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_jastrow_een_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_jastrow_en_nucleus(trexio_file, dset_w) -> None:
    """Write the jastrow_en_nucleus array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of jastrow_en_nucleus values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_jastrow_en_nucleus_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_jastrow_en_nucleus_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_jastrow_en_nucleus_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_jastrow_een_nucleus(trexio_file, dset_w) -> None:
    """Write the jastrow_een_nucleus array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of jastrow_een_nucleus values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.int64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       else:
           if doConversion:
               dset_64 = np.int64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.int64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_jastrow_een_nucleus_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_jastrow_een_nucleus_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_jastrow_een_nucleus_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_jastrow_en_scaling(trexio_file, dset_w) -> None:
    """Write the jastrow_en_scaling array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of jastrow_en_scaling values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_jastrow_en_scaling_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_jastrow_en_scaling_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_jastrow_en_scaling_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_qmc_point(trexio_file, dset_w) -> None:
    """Write the qmc_point array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of qmc_point values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_qmc_point_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_qmc_point_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_qmc_point_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_qmc_psi(trexio_file, dset_w) -> None:
    """Write the qmc_psi array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of qmc_psi values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_qmc_psi_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_qmc_psi_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_qmc_psi_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_qmc_e_loc(trexio_file, dset_w) -> None:
    """Write the qmc_e_loc array of numbers in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list OR numpy.ndarray
        Array of qmc_e_loc values to be written. If array data type does not correspond to int64 or float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    doConversion = False
    doFlatten = False
    if not isinstance(dset_w, (list, tuple)):
       # if input array is not a list or tuple then it is probably a numpy array
       if isinstance(dset_w, np.ndarray) and (not dset_w.dtype==np.int64 or not dset_w.dtype==np.float64):
           doConversion = True

       if len(dset_w.shape) > 1:
           doFlatten = True
           if doConversion:
               dset_64 = np.float64(dset_w).flatten()
           else:
               dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       else:
           if doConversion:
               dset_64 = np.float64(dset_w)

    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           ncol = len(dset_w[0])
           dset_flat = np.array(dset_w, dtype=np.float64).flatten()
       except TypeError:
           doFlatten = False
           pass


    if doConversion:
        rc = pytr.trexio_write_safe_qmc_e_loc_64(trexio_file.pytrexio_s, dset_64)
    elif doFlatten:
        rc = pytr.trexio_write_safe_qmc_e_loc_64(trexio_file.pytrexio_s, dset_flat)
    else:
        rc = pytr.trexio_write_safe_qmc_e_loc_64(trexio_file.pytrexio_s, dset_w)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_2e_int_eri(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the ao_2e_int_eri indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of ao_2e_int_eri indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of ao_2e_int_eri values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_ao_2e_int_eri(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_ao_2e_int_eri(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_ao_2e_int_eri(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_ao_2e_int_eri(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_2e_int_eri_lr(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the ao_2e_int_eri_lr indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of ao_2e_int_eri_lr indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of ao_2e_int_eri_lr values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_ao_2e_int_eri_lr(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_ao_2e_int_eri_lr(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_ao_2e_int_eri_lr(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_ao_2e_int_eri_lr(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_2e_int_eri_cholesky(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the ao_2e_int_eri_cholesky indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of ao_2e_int_eri_cholesky indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of ao_2e_int_eri_cholesky values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_ao_2e_int_eri_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_ao_2e_int_eri_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_ao_2e_int_eri_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_ao_2e_int_eri_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_ao_2e_int_eri_lr_cholesky(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the ao_2e_int_eri_lr_cholesky indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of ao_2e_int_eri_lr_cholesky indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of ao_2e_int_eri_lr_cholesky values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_ao_2e_int_eri_lr_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_ao_2e_int_eri_lr_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_ao_2e_int_eri_lr_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_ao_2e_int_eri_lr_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_2e_int_eri(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the mo_2e_int_eri indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of mo_2e_int_eri indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of mo_2e_int_eri values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_mo_2e_int_eri(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_mo_2e_int_eri(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_mo_2e_int_eri(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_mo_2e_int_eri(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_2e_int_eri_lr(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the mo_2e_int_eri_lr indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of mo_2e_int_eri_lr indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of mo_2e_int_eri_lr values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_mo_2e_int_eri_lr(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_mo_2e_int_eri_lr(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_mo_2e_int_eri_lr(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_mo_2e_int_eri_lr(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_2e_int_eri_cholesky(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the mo_2e_int_eri_cholesky indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of mo_2e_int_eri_cholesky indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of mo_2e_int_eri_cholesky values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_mo_2e_int_eri_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_mo_2e_int_eri_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_mo_2e_int_eri_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_mo_2e_int_eri_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_2e_int_eri_lr_cholesky(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the mo_2e_int_eri_lr_cholesky indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of mo_2e_int_eri_lr_cholesky indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of mo_2e_int_eri_lr_cholesky values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_mo_2e_int_eri_lr_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_mo_2e_int_eri_lr_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_mo_2e_int_eri_lr_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_mo_2e_int_eri_lr_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_csf_det_coefficient(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the csf_det_coefficient indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of csf_det_coefficient indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of csf_det_coefficient values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_csf_det_coefficient(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_csf_det_coefficient(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_csf_det_coefficient(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_csf_det_coefficient(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_amplitude_single(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the amplitude_single indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of amplitude_single indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of amplitude_single values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_single(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_amplitude_single(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_single(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_amplitude_single(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_amplitude_single_exp(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the amplitude_single_exp indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of amplitude_single_exp indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of amplitude_single_exp values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_single_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_amplitude_single_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_single_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_amplitude_single_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_amplitude_double(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the amplitude_double indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of amplitude_double indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of amplitude_double values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_double(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_amplitude_double(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_double(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_amplitude_double(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_amplitude_double_exp(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the amplitude_double_exp indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of amplitude_double_exp indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of amplitude_double_exp values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_double_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_amplitude_double_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_double_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_amplitude_double_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_amplitude_triple(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the amplitude_triple indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of amplitude_triple indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of amplitude_triple values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_triple(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_amplitude_triple(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_triple(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_amplitude_triple(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_amplitude_triple_exp(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the amplitude_triple_exp indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of amplitude_triple_exp indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of amplitude_triple_exp values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_triple_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_amplitude_triple_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_triple_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_amplitude_triple_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_amplitude_quadruple(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the amplitude_quadruple indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of amplitude_quadruple indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of amplitude_quadruple values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_quadruple(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_amplitude_quadruple(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_quadruple(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_amplitude_quadruple(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_amplitude_quadruple_exp(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the amplitude_quadruple_exp indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of amplitude_quadruple_exp indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of amplitude_quadruple_exp values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_quadruple_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_amplitude_quadruple_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_amplitude_quadruple_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_amplitude_quadruple_exp(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the rdm_2e indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of rdm_2e indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of rdm_2e values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_rdm_2e(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_rdm_2e(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e_upup(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the rdm_2e_upup indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of rdm_2e_upup indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of rdm_2e_upup values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_upup(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_upup(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_upup(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_rdm_2e_upup(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e_dndn(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the rdm_2e_dndn indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of rdm_2e_dndn indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of rdm_2e_dndn values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_dndn(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_dndn(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_dndn(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_rdm_2e_dndn(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e_updn(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the rdm_2e_updn indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of rdm_2e_updn indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of rdm_2e_updn values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_updn(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_updn(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_updn(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_rdm_2e_updn(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e_transition(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the rdm_2e_transition indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of rdm_2e_transition indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of rdm_2e_transition values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_transition(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_transition(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_transition(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_rdm_2e_transition(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e_cholesky(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the rdm_2e_cholesky indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of rdm_2e_cholesky indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of rdm_2e_cholesky values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_rdm_2e_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e_upup_cholesky(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the rdm_2e_upup_cholesky indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of rdm_2e_upup_cholesky indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of rdm_2e_upup_cholesky values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_upup_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_upup_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_upup_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_rdm_2e_upup_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e_dndn_cholesky(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the rdm_2e_dndn_cholesky indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of rdm_2e_dndn_cholesky indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of rdm_2e_dndn_cholesky values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_dndn_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_dndn_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_dndn_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_rdm_2e_dndn_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_rdm_2e_updn_cholesky(trexio_file: File, offset_file: int, buffer_size: int, indices: list, values: list) -> None:
    """Write the rdm_2e_updn_cholesky indices and values in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of integrals to be skipped in the file when writing.

    buffer_size: int
        The number of integrals to write in the file from the provided sparse arrays.

    indices: list OR numpy.ndarray
        Array of rdm_2e_updn_cholesky indices to be written. If array data type does not correspond to int32, the conversion is performed.

    values: list OR numpy.ndarray
        Array of rdm_2e_updn_cholesky values to be written. If array data type does not correspond to float64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(indices, (list, tuple, np.ndarray)):
        raise TypeError("indices argument has to be an array (list, tuple or NumPy ndarray).")
    if not isinstance(values, (list, tuple, np.ndarray)):
        raise TypeError("values argument has to be an array (list, tuple or NumPy ndarray).")

    convertIndices = False
    convertValues = False
    flattenIndices = False
    if isinstance(indices, np.ndarray):
       # convert to int32 if input indices are in a different precision
       if not indices.dtype==np.int32:
           convertIndices = True

       if len(indices.shape) > 1:
           flattenIndices = True
           if convertIndices:
               indices_32 = np.int32(indices).flatten()
           else:
               indices_32 = np.array(indices, dtype=np.int32).flatten()
       else:
           if convertIndices:
               indices_32 = np.int32(indices)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           doFlatten = True
           # if list of indices is flat - the attempt to compute len(indices[0]) will raise a TypeError
           ncol = len(indices[0])
           indices_32 = np.array(indices, dtype=np.int32).flatten()
       except TypeError:
           doFlatten = False
           pass

    if isinstance(values, np.ndarray):
       # convert to float64 if input values are in a different precision
       if not values.dtype==np.float64:
           convertValues = True
       if convertValues:
           values_64 = np.float64(values)

    if (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_updn_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values_64)
    elif (convertIndices or flattenIndices) and not convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_updn_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices_32, values)
    elif not (convertIndices or flattenIndices) and convertValues:
        rc = pytr.trexio_write_safe_rdm_2e_updn_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values_64)
    else:
        rc = pytr.trexio_write_safe_rdm_2e_updn_cholesky(trexio_file.pytrexio_s, offset_file, buffer_size, indices, values)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_metadata_code(trexio_file, dset_w: list) -> None:
    """Write the metadata_code array of strings in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list
        Array of metadata_code strings to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(max(dset_w, key=len)) + 1

    rc = pytr.trexio_write_metadata_code(trexio_file.pytrexio_s, dset_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_metadata_author(trexio_file, dset_w: list) -> None:
    """Write the metadata_author array of strings in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list
        Array of metadata_author strings to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(max(dset_w, key=len)) + 1

    rc = pytr.trexio_write_metadata_author(trexio_file.pytrexio_s, dset_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_nucleus_label(trexio_file, dset_w: list) -> None:
    """Write the nucleus_label array of strings in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list
        Array of nucleus_label strings to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(max(dset_w, key=len)) + 1

    rc = pytr.trexio_write_nucleus_label(trexio_file.pytrexio_s, dset_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_state_label(trexio_file, dset_w: list) -> None:
    """Write the state_label array of strings in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list
        Array of state_label strings to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(max(dset_w, key=len)) + 1

    rc = pytr.trexio_write_state_label(trexio_file.pytrexio_s, dset_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_state_file_name(trexio_file, dset_w: list) -> None:
    """Write the state_file_name array of strings in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list
        Array of state_file_name strings to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(max(dset_w, key=len)) + 1

    rc = pytr.trexio_write_state_file_name(trexio_file.pytrexio_s, dset_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_class(trexio_file, dset_w: list) -> None:
    """Write the mo_class array of strings in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list
        Array of mo_class strings to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(max(dset_w, key=len)) + 1

    rc = pytr.trexio_write_mo_class(trexio_file.pytrexio_s, dset_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def write_mo_symmetry(trexio_file, dset_w: list) -> None:
    """Write the mo_symmetry array of strings in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    dset_w: list
        Array of mo_symmetry strings to be written.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    max_str_length = len(max(dset_w, key=len)) + 1

    rc = pytr.trexio_write_mo_symmetry(trexio_file.pytrexio_s, dset_w, max_str_length)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

def has_determinant_list(trexio_file) -> bool:
    """Check that determinant_list exists in the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
          True if the variable exists, False otherwise

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is TREXIO_FAILURE and prints the error message using string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc = pytr.trexio_has_determinant_list(trexio_file.pytrexio_s)
    if rc == TREXIO_FAILURE:
        raise Error(rc)

    return rc == TREXIO_SUCCESS
def read_determinant_list(trexio_file: File, offset_file: int, buffer_size: int) -> tuple:
    """Read determinant_list from the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of determinants to be skipped in the file when reading.

    buffer_size: int
        The number of determinants to read from the file.

    Returns:
        (determinants, n_int_read, eof_flag) tuple where
          - determinants are NumPy arrays [numpy.ndarray] with the default int64 precision;
          - n_int_read [int] is the number of determinants read from the trexio_file
            (either strictly equal to buffer_size or less than buffer_size if EOF has been reached);
          - eof_flag [bool] is True when EOF has been reached (i.e. when call to low-level pytrexio API returns TREXIO_END)
                               False otherwise.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")


    # read the number of determinants already in the file
    det_num = read_determinant_num(trexio_file)
    # calculate the int_num (number of int bit fields per determinant)
    int_num = 2 * get_int64_num(trexio_file)

    # additional modification needed to avoid allocating more memory than needed if EOF will be reached during read
    overflow = offset_file + buffer_size - det_num
    eof_flag = False
    if overflow > 0:
        verified_size = buffer_size - overflow
        eof_flag = True
    else:
        verified_size = buffer_size

    # main call to the low-level (SWIG-wrapped) trexio_read function, which also requires the sizes of the output to be provided
    # read_buf_size contains the number of elements being read from the file, useful when EOF has been reached
    rc, n_int_read, determinants = pytr.trexio_read_safe_determinant_list(trexio_file.pytrexio_s,
                                                                          offset_file,
                                                                          verified_size,
                                                                          verified_size * int_num)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)
    if n_int_read == 0:
        raise ValueError("No integrals have been read from the file.")
    if determinants is None:
        raise ValueError("Returned NULL array from the low-level pytrexio API.")

    # conversion to custom types can be performed on the user side, here we only reshape the returned flat array according to int_num
    dets_reshaped = np.reshape(determinants, (verified_size, int_num), order='C')

    return (dets_reshaped, n_int_read, eof_flag)


def get_int64_num(trexio_file) -> int:
    """Compute the number of int64 bit fields corresponding to the TREXIO file.

    Parameter is a ~TREXIO File~ object that has been created by a call to ~open~ function.

    Returns:
        ~num~: int
        Number of int64 bit fields per determinant.

    Raises:
        - Exception from AssertionError if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message using trexio_string_of_error.
        - Exception from some other error (e.g. RuntimeError).
    """

    rc, num = pytr.trexio_get_int64_num(trexio_file.pytrexio_s)
    if rc != TREXIO_SUCCESS:
        raise Error(rc)

    return num
def write_determinant_list(trexio_file: File, offset_file: int, buffer_size: int, determinants: list) -> None:
    """Write the determinant list in the TREXIO file.

    Parameters:

    trexio_file:
        TREXIO File object.

    offset_file: int
        The number of determinants to be skipped in the file when writing.

    buffer_size: int
        The number of determinants to write in the file.

    determinants: list OR numpy.ndarray
        Array of determinant_list to be written. If array data type does not correspond to int64, the conversion is performed.

    Raises:
        - trexio.Error if TREXIO return code ~rc~ is different from TREXIO_SUCCESS and prints the error message.
        - Exception from some other error (e.g. RuntimeError).
    """

    if not isinstance(offset_file, int):
        raise TypeError("offset_file argument has to be an integer.")
    if not isinstance(buffer_size, int):
        raise TypeError("buffer_size argument has to be an integer.")
    if not isinstance(determinants, (list, tuple, np.ndarray)):
        raise TypeError("determinants argument has to be an array (list, tuple or NumPy ndarray).")

    convert = False
    flatten = False
    if isinstance(determinants, np.ndarray):
       # convert to int64 if input determinants are in a different precision
       if not determinants.dtype==np.int64:
           convert= True

       if len(determinants.shape) > 1:
           flatten = True
           if convert:
               dets_64 = np.int64(determinants).flatten()
           else:
               dets_64 = np.array(determinants, dtype=np.int64).flatten()
       else:
           if convert:
               dets_64 = np.int64(determinants)
    else:
       # if input array is a multidimensional list or tuple, we have to convert it
       try:
           # if list is flat - the attempt to compute len() will raise a TypeError
           _ = len(determinants[0])
           dets_64 = np.array(determinants, dtype=np.int64).flatten()
           flatten = True
       except TypeError:
           pass

    if flatten or convert:
        rc = pytr.trexio_write_safe_determinant_list(trexio_file.pytrexio_s, offset_file, buffer_size, dets_64)
    else:
        rc = pytr.trexio_write_safe_determinant_list(trexio_file.pytrexio_s, offset_file, buffer_size, determinants)

    if rc != TREXIO_SUCCESS:
        raise Error(rc)
