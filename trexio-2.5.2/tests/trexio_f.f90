!
! To include this file in your source code, we recommend creating a new file
! within your source tree named `trexio_module.F90` (note the capital F is
! crucial). The contents of this file should be limited to a single line:
!
! #include <trexio_f.f90>
!
! By following this approach, the C preprocessor will automatically include the
! TREXIO module from its standard installation location. If you update the
! library in the future, your source code won't require any modifications.
!
module trexio

  use, intrinsic :: iso_c_binding, only : c_int32_t, c_int64_t, c_double, c_size_t, c_bool
  use, intrinsic :: iso_c_binding, only : c_float, c_char, c_new_line, c_null_char
  implicit none

  integer, parameter :: trexio_exit_code  = c_int32_t
  integer, parameter :: trexio_back_end_t = c_int32_t
  integer, parameter :: trexio_t          = c_size_t

  character(kind=c_char), parameter :: TREXIO_DELIM = c_new_line

integer(trexio_exit_code), parameter :: TREXIO_FAILURE                 = -1
integer(trexio_exit_code), parameter :: TREXIO_SUCCESS                 = 0
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_1           = 1
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_2           = 2
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_3           = 3
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_4           = 4
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_5           = 5
integer(trexio_exit_code), parameter :: TREXIO_END                     = 6
integer(trexio_exit_code), parameter :: TREXIO_READONLY                = 7
integer(trexio_exit_code), parameter :: TREXIO_ERRNO                   = 8
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ID              = 9
integer(trexio_exit_code), parameter :: TREXIO_ALLOCATION_FAILED       = 10
integer(trexio_exit_code), parameter :: TREXIO_HAS_NOT                 = 11
integer(trexio_exit_code), parameter :: TREXIO_INVALID_NUM             = 12
integer(trexio_exit_code), parameter :: TREXIO_ATTR_ALREADY_EXISTS     = 13
integer(trexio_exit_code), parameter :: TREXIO_DSET_ALREADY_EXISTS     = 14
integer(trexio_exit_code), parameter :: TREXIO_OPEN_ERROR              = 15
integer(trexio_exit_code), parameter :: TREXIO_LOCK_ERROR              = 16
integer(trexio_exit_code), parameter :: TREXIO_UNLOCK_ERROR            = 17
integer(trexio_exit_code), parameter :: TREXIO_FILE_ERROR              = 18
integer(trexio_exit_code), parameter :: TREXIO_GROUP_READ_ERROR        = 19
integer(trexio_exit_code), parameter :: TREXIO_GROUP_WRITE_ERROR       = 20
integer(trexio_exit_code), parameter :: TREXIO_ELEM_READ_ERROR         = 21
integer(trexio_exit_code), parameter :: TREXIO_ELEM_WRITE_ERROR        = 22
integer(trexio_exit_code), parameter :: TREXIO_UNSAFE_ARRAY_DIM        = 23
integer(trexio_exit_code), parameter :: TREXIO_ATTR_MISSING            = 24
integer(trexio_exit_code), parameter :: TREXIO_DSET_MISSING            = 25
integer(trexio_exit_code), parameter :: TREXIO_BACK_END_MISSING        = 26
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_6           = 27
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_7           = 28
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_8           = 29
integer(trexio_exit_code), parameter :: TREXIO_INVALID_STR_LEN         = 30
integer(trexio_exit_code), parameter :: TREXIO_INT_SIZE_OVERFLOW       = 31
integer(trexio_exit_code), parameter :: TREXIO_SAFE_MODE               = 32
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ELECTRON_NUM    = 33
integer(trexio_exit_code), parameter :: TREXIO_INVALID_DETERMINANT_NUM = 34
integer(trexio_exit_code), parameter :: TREXIO_INVALID_STATE           = 35
integer(trexio_exit_code), parameter :: TREXIO_VERSION_PARSING_ISSUE   = 36
integer(trexio_exit_code), parameter :: TREXIO_PHASE_CHANGE            = 37
integer(trexio_exit_code), parameter :: TREXIO_INVALID_MO_INDEX        = 38
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_9           = 39
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_10          = 40
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_11          = 41
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_12          = 42
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_13          = 43
integer(trexio_exit_code), parameter :: TREXIO_INVALID_ARG_14          = 44
integer(trexio_exit_code), parameter :: TREXIO_CORRUPTION_ATTEMPT      = 45

interface
   subroutine trexio_string_of_error_f (error, str_size, string) bind(C)
     import
     integer(trexio_exit_code), intent(in), value :: error
     integer(c_int32_t), intent(in), value            :: str_size
     character(kind=c_char), intent(out)          :: string(str_size)
   end subroutine trexio_string_of_error_f
end interface

integer(trexio_back_end_t), parameter :: TREXIO_HDF5 = 0
  integer(trexio_back_end_t), parameter :: TREXIO_TEXT = 1
! integer(trexio_back_end_t), parameter :: TREXIO_JSON = 2
  integer(trexio_back_end_t), parameter :: TREXIO_INVALID_BACK_END = 2
  integer(trexio_back_end_t), parameter :: TREXIO_AUTO = TREXIO_INVALID_BACK_END

interface
   logical(c_bool) function trexio_has_back_end (back_end) bind(C)
     import
     integer(trexio_back_end_t), intent(in), value :: back_end
   end function trexio_has_back_end
end interface

interface
   logical(c_bool) function trexio_has_backend (back_end) bind(C)
     import
     integer(trexio_back_end_t), intent(in), value :: back_end
   end function trexio_has_backend
end interface

interface
   integer(trexio_t) function trexio_open_c (filename, mode, back_end, rc_open) &
        bind(C, name="trexio_open")
     import
     character(kind=c_char), dimension(*)          :: filename
     character(kind=c_char), intent(in), value     :: mode
     integer(trexio_back_end_t), intent(in), value :: back_end
     integer(trexio_exit_code), intent(out)        :: rc_open
   end function trexio_open_c
end interface

interface
   integer(trexio_exit_code) function trexio_set_one_based(trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_set_one_based
end interface

interface
   integer(trexio_exit_code) function trexio_close (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_close
end interface

interface
   integer(trexio_exit_code) function trexio_flush (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_flush
end interface

interface
   integer(trexio_exit_code) function trexio_inquire_c (filename) bind(C, name="trexio_inquire")
     import
     character(kind=c_char), dimension(*)       :: filename
   end function trexio_inquire_c
end interface

interface
   integer(trexio_exit_code) function trexio_cp_c (source, destination) bind(C, name="trexio_cp")
     import
     character(kind=c_char), dimension(*)          :: source, destination
   end function trexio_cp_c
end interface

interface
   integer(trexio_exit_code) function trexio_set_state (trex_file, state) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: state
   end function trexio_set_state
end interface

interface
   integer(trexio_exit_code) function trexio_get_state (trex_file, state) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out)       :: state
   end function trexio_get_state
end interface

interface
   integer(c_int32_t) function trexio_info_c () bind(C, name="trexio_info")
   import
   end function trexio_info_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_to_bitfield_list_c &
        (list, occupied_num, det_list, N_int) &
        bind(C, name="trexio_to_bitfield_list")
     import
     integer(c_int32_t), intent(in)        :: list(*)
     integer(c_int32_t), intent(in), value :: occupied_num
     integer(c_int64_t), intent(inout)     :: det_list(*)
     integer(c_int32_t), intent(in), value :: N_int
   end function trexio_to_bitfield_list_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_to_orbital_list_c &
        (N_int, d1, list, occupied_num) &
        bind(C, name="trexio_to_orbital_list")
     import
     integer(c_int32_t), intent(in), value :: N_int
     integer(c_int64_t), intent(in)        :: d1(*)
     integer(c_int32_t), intent(inout)     :: list(*)
     integer(c_int32_t), intent(inout)     :: occupied_num
   end function trexio_to_orbital_list_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_to_orbital_list_up_dn_c &
        (N_int, d1, list_up, list_dn, occ_num_up, occ_num_dn) &
        bind(C, name="trexio_to_orbital_list_up_dn")
     import
     integer(c_int32_t), intent(in), value :: N_int
     integer(c_int64_t), intent(in)        :: d1(*)
     integer(c_int32_t), intent(inout)     :: list_up(*)
     integer(c_int32_t), intent(inout)     :: list_dn(*)
     integer(c_int32_t), intent(inout)     :: occ_num_up
     integer(c_int32_t), intent(inout)     :: occ_num_dn
   end function trexio_to_orbital_list_up_dn_c
end interface

interface
  integer(trexio_exit_code) function &
       trexio_convert_nao_radius_32 &
       (r, grid_r, log_r_out) &
       bind(C, name="trexio_convert_nao_radius_32")
    import
    real(c_float), intent(in), value  :: r
    real(c_float), intent(in)  :: grid_r(*)
    real(c_float), intent(out)        :: log_r_out
  end function trexio_convert_nao_radius_32
end interface

interface
  integer(trexio_exit_code) function &
       trexio_convert_nao_radius_64 &
       (r, grid_r, log_r_out) &
       bind(C, name="trexio_convert_nao_radius_64")
    import
    real(c_double), intent(in), value  :: r
    real(c_double), intent(in)  :: grid_r(*)
    real(c_double), intent(out)        :: log_r_out
  end function trexio_convert_nao_radius_64
end interface

interface
  integer(trexio_exit_code) function &
       trexio_evaluate_nao_radial &
       (shell_index, r, &
       grid_start, grid_size, grid_r, interpolator, normalization, amplitude) &
       bind(C, name="trexio_evaluate_nao_radial")
    import
    integer(c_int32_t), intent(in), value  :: shell_index
    real(c_double), intent(in), value   :: r
    integer(c_int32_t), intent(in)  :: grid_start(*)
    integer(c_int32_t), intent(in)  :: grid_size(*)
    real(c_double), intent(in)  :: grid_r(*)
    real(c_double), intent(in)  :: interpolator(*)
    real(c_double), intent(in)  :: normalization(*)
    real(c_double), intent(out)         :: amplitude
  end function trexio_evaluate_nao_radial
end interface

interface
  integer(trexio_exit_code) function &
       trexio_evaluate_nao_radial_all (shell_num, &
          nucleus_index, nucleus_coords, &
          grid_start, grid_size, grid_r, interpolator, &
          normalization, rx, ry, rz, amplitudes) &
          bind(C, name="trexio_evaluate_nao_radial_all")
    import
    integer(c_int32_t), intent(in), value  :: shell_num
    integer(c_int32_t), intent(in) :: nucleus_index(*)
    real(c_double), intent(in)  :: nucleus_coords(*)
    integer(c_int32_t), intent(in)  :: grid_start(*)
    integer(c_int32_t), intent(in)  :: grid_size(*)
    real(c_double), intent(in)  :: grid_r(*)
    real(c_double), intent(in)  :: interpolator(*)
    real(c_double), intent(in)  :: normalization(*)
    real(c_double), intent(in), value   :: rx
    real(c_double), intent(in), value   :: ry
    real(c_double), intent(in), value   :: rz
    real(c_double), intent(out)         :: amplitudes(*)
  end function trexio_evaluate_nao_radial_all
end interface

character(len = 12) :: TREXIO_PACKAGE_VERSION = "2.5.2"
integer :: TREXIO_VERSION_MAJOR = 2
integer :: TREXIO_VERSION_MINOR = 5
integer :: TREXIO_VERSION_PATCH = 2
character(len = 64) :: TREXIO_GIT_HASH = "7226acee17fc7562649931807143795c2f9af893"

interface
   integer(trexio_exit_code) function &
        trexio_delete_metadata &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_metadata
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_nucleus &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_nucleus
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_cell &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_cell
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_pbc &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_pbc
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_electron &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_electron
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_state &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_state
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_basis &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_basis
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_ecp &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_ecp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_grid &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_grid
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_ao &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_ao
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_ao_1e_int &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_ao_1e_int
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_ao_2e_int &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_ao_2e_int
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_mo &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_mo
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_mo_1e_int &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_mo_1e_int
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_mo_2e_int &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_mo_2e_int
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_determinant &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_determinant
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_csf &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_csf
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_amplitude &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_amplitude
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_rdm &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_rdm
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_jastrow &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_jastrow
end interface

interface
   integer(trexio_exit_code) function &
        trexio_delete_qmc &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_delete_qmc
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_metadata_code_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_metadata_code_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_metadata_author_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_metadata_author_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_metadata_unsafe &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_metadata_unsafe
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_nucleus_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_nucleus_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_nucleus_repulsion &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_nucleus_repulsion
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_cell_two_pi &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_cell_two_pi
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_pbc_periodic &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_pbc_periodic
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_pbc_k_point_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_pbc_k_point_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_pbc_madelung &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_pbc_madelung
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_electron_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_electron_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_electron_up_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_electron_up_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_electron_dn_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_electron_dn_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_state_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_state_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_state_id &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_state_id
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_state_energy &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_state_energy
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_prim_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_prim_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_shell_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_shell_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_nao_grid_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_nao_grid_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_interp_coeff_cnt &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_interp_coeff_cnt
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_e_cut &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_e_cut
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ecp_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ecp_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_rad_precision &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid_rad_precision
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_max_ang_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid_max_ang_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_min_ang_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid_min_ang_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_ang_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid_ang_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_rad_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid_rad_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_cartesian &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_cartesian
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_2e_int_eri_cholesky_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_2e_int_eri_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_2e_int_eri_lr_cholesky_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_2e_int_eri_lr_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_2e_int_eri_cholesky_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_2e_int_eri_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_2e_int_eri_lr_cholesky_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_2e_int_eri_lr_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_determinant_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_determinant_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_csf_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_csf_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e_cholesky_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e_upup_cholesky_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e_upup_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e_dndn_cholesky_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e_dndn_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e_updn_cholesky_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e_updn_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_jastrow_en_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_jastrow_en_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_jastrow_ee_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_jastrow_ee_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_jastrow_een_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_jastrow_een_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_jastrow_ee_scaling &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_jastrow_ee_scaling
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_qmc_num &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_qmc_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_metadata_package_version &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_has_metadata_package_version
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_metadata_description &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_has_metadata_description
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_nucleus_point_group &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_has_nucleus_point_group
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_state_current_label &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_has_state_current_label
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_type &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_has_basis_type
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_oscillation_kind &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_has_basis_oscillation_kind
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_interpolator_kind &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_has_basis_interpolator_kind
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_description &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_has_grid_description
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_type &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_has_mo_type
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_jastrow_type &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
   end function trexio_has_jastrow_type
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_determinant_coefficient &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_determinant_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_csf_coefficient &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_csf_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_nucleus_charge &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_nucleus_charge
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_nucleus_coord &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_nucleus_coord
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_cell_a &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_cell_a
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_cell_b &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_cell_b
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_cell_c &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_cell_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_cell_g_a &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_cell_g_a
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_cell_g_b &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_cell_g_b
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_cell_g_c &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_cell_g_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_pbc_k_point &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_pbc_k_point
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_pbc_k_point_weight &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_pbc_k_point_weight
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_nucleus_index &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_nucleus_index
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_shell_ang_mom &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_shell_ang_mom
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_shell_factor &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_shell_factor
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_r_power &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_r_power
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_nao_grid_start &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_nao_grid_start
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_nao_grid_size &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_nao_grid_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_shell_index &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_shell_index
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_exponent &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_exponent
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_exponent_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_exponent_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_coefficient &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_coefficient_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_coefficient_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_oscillation_arg &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_oscillation_arg
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_prim_factor &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_prim_factor
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_nao_grid_radius &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_nao_grid_radius
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_nao_grid_phi &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_nao_grid_phi
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_nao_grid_grad &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_nao_grid_grad
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_nao_grid_lap &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_nao_grid_lap
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_interpolator_phi &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_interpolator_phi
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_interpolator_grad &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_interpolator_grad
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis_interpolator_lap &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis_interpolator_lap
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ecp_max_ang_mom_plus_1 &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ecp_max_ang_mom_plus_1
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ecp_z_core &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ecp_z_core
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ecp_ang_mom &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ecp_ang_mom
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ecp_nucleus_index &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ecp_nucleus_index
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ecp_exponent &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ecp_exponent
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ecp_coefficient &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ecp_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ecp_power &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ecp_power
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_coord &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid_coord
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_weight &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid_weight
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_ang_coord &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid_ang_coord
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_ang_weight &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid_ang_weight
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_rad_coord &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid_rad_coord
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid_rad_weight &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid_rad_weight
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_shell &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_shell
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_normalization &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_normalization
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_1e_int_overlap &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_1e_int_overlap
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_1e_int_kinetic &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_1e_int_kinetic
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_1e_int_potential_n_e &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_1e_int_potential_n_e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_1e_int_ecp &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_1e_int_ecp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_1e_int_core_hamiltonian &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_1e_int_core_hamiltonian
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_1e_int_overlap_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_1e_int_overlap_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_1e_int_kinetic_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_1e_int_kinetic_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_1e_int_potential_n_e_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_1e_int_potential_n_e_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_1e_int_ecp_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_1e_int_ecp_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_1e_int_core_hamiltonian_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_1e_int_core_hamiltonian_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_coefficient &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_coefficient_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_coefficient_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_occupation &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_occupation
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_energy &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_energy
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_spin &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_spin
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_k_point &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_k_point
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_1e_int_overlap &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_1e_int_overlap
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_1e_int_kinetic &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_1e_int_kinetic
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_1e_int_potential_n_e &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_1e_int_potential_n_e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_1e_int_ecp &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_1e_int_ecp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_1e_int_core_hamiltonian &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_1e_int_core_hamiltonian
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_1e_int_overlap_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_1e_int_overlap_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_1e_int_kinetic_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_1e_int_kinetic_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_1e_int_potential_n_e_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_1e_int_potential_n_e_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_1e_int_ecp_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_1e_int_ecp_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_1e_int_core_hamiltonian_im &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_1e_int_core_hamiltonian_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_1e &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_1e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_1e_up &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_1e_up
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_1e_dn &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_1e_dn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_1e_transition &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_1e_transition
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_jastrow_en &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_jastrow_en
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_jastrow_ee &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_jastrow_ee
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_jastrow_een &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_jastrow_een
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_jastrow_en_nucleus &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_jastrow_en_nucleus
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_jastrow_een_nucleus &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_jastrow_een_nucleus
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_jastrow_en_scaling &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_jastrow_en_scaling
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_qmc_point &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_qmc_point
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_qmc_psi &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_qmc_psi
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_qmc_e_loc &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_qmc_e_loc
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_2e_int_eri &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_2e_int_eri
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_2e_int_eri_lr &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_2e_int_eri_lr
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_2e_int_eri_cholesky &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_2e_int_eri_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_2e_int_eri_lr_cholesky &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_2e_int_eri_lr_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_2e_int_eri &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_2e_int_eri
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_2e_int_eri_lr &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_2e_int_eri_lr
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_2e_int_eri_cholesky &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_2e_int_eri_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_2e_int_eri_lr_cholesky &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_2e_int_eri_lr_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_csf_det_coefficient &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_csf_det_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_amplitude_single &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_amplitude_single
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_amplitude_single_exp &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_amplitude_single_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_amplitude_double &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_amplitude_double
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_amplitude_double_exp &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_amplitude_double_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_amplitude_triple &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_amplitude_triple
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_amplitude_triple_exp &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_amplitude_triple_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_amplitude_quadruple &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_amplitude_quadruple
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_amplitude_quadruple_exp &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_amplitude_quadruple_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e_upup &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e_upup
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e_dndn &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e_dndn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e_updn &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e_updn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e_transition &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e_transition
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e_cholesky &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e_upup_cholesky &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e_upup_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e_dndn_cholesky &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e_dndn_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm_2e_updn_cholesky &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm_2e_updn_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_metadata_code &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_metadata_code
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_metadata_author &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_metadata_author
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_nucleus_label &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_nucleus_label
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_state_label &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_state_label
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_state_file_name &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_state_file_name
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_class &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_class
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_symmetry &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_symmetry
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_metadata &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_metadata
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_nucleus &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_nucleus
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_cell &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_cell
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_pbc &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_pbc
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_electron &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_electron
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_state &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_state
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_basis &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_basis
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ecp &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ecp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_grid &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_grid
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_1e_int &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_1e_int
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_ao_2e_int &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_ao_2e_int
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_1e_int &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_1e_int
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_mo_2e_int &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_mo_2e_int
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_determinant &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_determinant
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_csf &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_csf
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_amplitude &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_amplitude
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_rdm &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_rdm
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_jastrow &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_jastrow
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_qmc &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_qmc
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_code_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_metadata_code_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_author_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_metadata_author_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_unsafe_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_metadata_unsafe_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_nucleus_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_repulsion_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: num
   end function trexio_read_nucleus_repulsion_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_two_pi_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_cell_two_pi_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_periodic_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_pbc_periodic_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_k_point_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_pbc_k_point_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_madelung_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: num
   end function trexio_read_pbc_madelung_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_electron_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_electron_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_electron_up_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_electron_up_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_electron_dn_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_electron_dn_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_state_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_state_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_state_id_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_state_id_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_state_energy_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: num
   end function trexio_read_state_energy_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_prim_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_basis_prim_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_shell_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_basis_shell_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_basis_nao_grid_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interp_coeff_cnt_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_basis_interp_coeff_cnt_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_e_cut_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: num
   end function trexio_read_basis_e_cut_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_ecp_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_rad_precision_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: num
   end function trexio_read_grid_rad_precision_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_grid_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_max_ang_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_grid_max_ang_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_min_ang_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_grid_min_ang_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_ang_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_grid_ang_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_rad_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_grid_rad_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_cartesian_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_ao_cartesian_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_ao_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_ao_2e_int_eri_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_lr_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_ao_2e_int_eri_lr_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_mo_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_mo_2e_int_eri_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_lr_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_mo_2e_int_eri_lr_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_determinant_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_determinant_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_csf_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_csf_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_rdm_2e_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_upup_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_rdm_2e_upup_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_dndn_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_rdm_2e_dndn_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_updn_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_rdm_2e_updn_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_en_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_jastrow_en_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_ee_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_jastrow_ee_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_een_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_jastrow_een_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_ee_scaling_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: num
   end function trexio_read_jastrow_ee_scaling_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_qmc_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_qmc_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_code_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_metadata_code_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_author_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_metadata_author_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_unsafe_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_metadata_unsafe_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_nucleus_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_repulsion_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: num
   end function trexio_read_nucleus_repulsion_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_two_pi_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_cell_two_pi_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_periodic_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_pbc_periodic_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_k_point_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_pbc_k_point_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_madelung_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: num
   end function trexio_read_pbc_madelung_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_electron_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_electron_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_electron_up_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_electron_up_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_electron_dn_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_electron_dn_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_state_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_state_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_state_id_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_state_id_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_state_energy_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: num
   end function trexio_read_state_energy_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_prim_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_basis_prim_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_shell_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_basis_shell_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_basis_nao_grid_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interp_coeff_cnt_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_basis_interp_coeff_cnt_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_e_cut_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: num
   end function trexio_read_basis_e_cut_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_ecp_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_rad_precision_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: num
   end function trexio_read_grid_rad_precision_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_grid_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_max_ang_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_grid_max_ang_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_min_ang_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_grid_min_ang_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_ang_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_grid_ang_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_rad_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_grid_rad_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_cartesian_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_ao_cartesian_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_ao_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_ao_2e_int_eri_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_lr_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_ao_2e_int_eri_lr_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_mo_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_mo_2e_int_eri_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_lr_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_mo_2e_int_eri_lr_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_determinant_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_determinant_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_csf_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_csf_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_rdm_2e_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_upup_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_rdm_2e_upup_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_dndn_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_rdm_2e_dndn_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_updn_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_rdm_2e_updn_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_en_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_jastrow_en_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_ee_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_jastrow_ee_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_een_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_jastrow_een_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_ee_scaling_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: num
   end function trexio_read_jastrow_ee_scaling_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_qmc_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: num
   end function trexio_read_qmc_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_code_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_metadata_code_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_author_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_metadata_author_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_unsafe &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_metadata_unsafe
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_nucleus_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_repulsion &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: num
   end function trexio_read_nucleus_repulsion
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_two_pi &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_cell_two_pi
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_periodic &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_pbc_periodic
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_k_point_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_pbc_k_point_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_madelung &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: num
   end function trexio_read_pbc_madelung
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_electron_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_electron_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_electron_up_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_electron_up_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_electron_dn_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_electron_dn_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_state_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_state_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_state_id &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_state_id
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_state_energy &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: num
   end function trexio_read_state_energy
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_prim_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_basis_prim_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_shell_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_basis_shell_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_basis_nao_grid_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interp_coeff_cnt &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_basis_interp_coeff_cnt
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_e_cut &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: num
   end function trexio_read_basis_e_cut
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_ecp_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_rad_precision &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: num
   end function trexio_read_grid_rad_precision
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_grid_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_max_ang_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_grid_max_ang_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_min_ang_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_grid_min_ang_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_ang_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_grid_ang_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_rad_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_grid_rad_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_cartesian &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_ao_cartesian
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_ao_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_ao_2e_int_eri_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_lr_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_ao_2e_int_eri_lr_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_mo_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_mo_2e_int_eri_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_lr_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_mo_2e_int_eri_lr_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_determinant_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_determinant_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_csf_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_csf_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_rdm_2e_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_upup_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_rdm_2e_upup_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_dndn_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_rdm_2e_dndn_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_updn_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_rdm_2e_updn_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_en_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_jastrow_en_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_ee_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_jastrow_ee_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_een_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_jastrow_een_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_ee_scaling &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: num
   end function trexio_read_jastrow_ee_scaling
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_qmc_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_read_qmc_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_package_version_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_read_metadata_package_version")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)   :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_read_metadata_package_version_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_description_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_read_metadata_description")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)   :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_read_metadata_description_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_point_group_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_read_nucleus_point_group")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)   :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_read_nucleus_point_group_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_state_current_label_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_read_state_current_label")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)   :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_read_state_current_label_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_type_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_read_basis_type")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)   :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_read_basis_type_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_oscillation_kind_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_read_basis_oscillation_kind")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)   :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_read_basis_oscillation_kind_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interpolator_kind_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_read_basis_interpolator_kind")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)   :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_read_basis_interpolator_kind_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_description_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_read_grid_description")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)   :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_read_grid_description_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_type_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_read_mo_type")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)   :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_read_mo_type_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_type_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_read_jastrow_type")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)   :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_read_jastrow_type_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_determinant_coefficient &
        (trex_file, &
        offset_file, buffer_size, &
        dset, dset_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     real(c_double), intent(out)           :: dset(*)
     integer(c_int64_t), intent(in), value :: dset_size
   end function trexio_read_safe_determinant_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_determinant_coefficient &
        (trex_file, offset_file, buffer_size, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     real(c_double), intent(out)           :: dset(*)
   end function trexio_read_determinant_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_determinant_coefficient_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_determinant_coefficient_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_csf_coefficient &
        (trex_file, &
        offset_file, buffer_size, &
        dset, dset_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     real(c_double), intent(out)           :: dset(*)
     integer(c_int64_t), intent(in), value :: dset_size
   end function trexio_read_safe_csf_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_csf_coefficient &
        (trex_file, offset_file, buffer_size, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     real(c_double), intent(out)           :: dset(*)
   end function trexio_read_csf_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_csf_coefficient_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_csf_coefficient_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_charge_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_nucleus_charge_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_coord_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_nucleus_coord_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_a_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_cell_a_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_b_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_cell_b_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_c_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_cell_c_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_g_a_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_cell_g_a_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_g_b_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_cell_g_b_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_g_c_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_cell_g_c_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_k_point_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_pbc_k_point_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_k_point_weight_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_pbc_k_point_weight_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nucleus_index_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_basis_nucleus_index_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_shell_ang_mom_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_basis_shell_ang_mom_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_shell_factor_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_shell_factor_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_r_power_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_basis_r_power_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_start_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_start_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_size_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_size_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_shell_index_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_basis_shell_index_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_exponent_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_exponent_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_exponent_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_exponent_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_coefficient_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_coefficient_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_coefficient_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_coefficient_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_oscillation_arg_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_oscillation_arg_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_prim_factor_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_prim_factor_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_radius_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_radius_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_phi_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_phi_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_grad_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_grad_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_lap_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_lap_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interpolator_phi_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_interpolator_phi_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interpolator_grad_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_interpolator_grad_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interpolator_lap_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_basis_interpolator_lap_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_max_ang_mom_plus_1_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_ecp_max_ang_mom_plus_1_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_z_core_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_ecp_z_core_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_ang_mom_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_ecp_ang_mom_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_nucleus_index_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_ecp_nucleus_index_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_exponent_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ecp_exponent_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_coefficient_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ecp_coefficient_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_power_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_ecp_power_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_coord_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_grid_coord_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_weight_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_grid_weight_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_ang_coord_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_grid_ang_coord_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_ang_weight_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_grid_ang_weight_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_rad_coord_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_grid_rad_coord_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_rad_weight_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_grid_rad_weight_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_shell_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_ao_shell_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_normalization_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ao_normalization_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_overlap_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_overlap_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_kinetic_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_kinetic_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_potential_n_e_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_potential_n_e_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_ecp_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_ecp_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_core_hamiltonian_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_core_hamiltonian_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_overlap_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_overlap_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_kinetic_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_kinetic_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_potential_n_e_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_potential_n_e_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_ecp_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_ecp_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_core_hamiltonian_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_core_hamiltonian_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_coefficient_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_coefficient_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_coefficient_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_coefficient_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_occupation_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_occupation_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_energy_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_energy_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_spin_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_mo_spin_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_k_point_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_mo_k_point_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_overlap_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_overlap_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_kinetic_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_kinetic_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_potential_n_e_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_potential_n_e_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_ecp_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_ecp_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_core_hamiltonian_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_core_hamiltonian_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_overlap_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_overlap_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_kinetic_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_kinetic_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_potential_n_e_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_potential_n_e_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_ecp_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_ecp_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_core_hamiltonian_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_core_hamiltonian_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_1e_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_rdm_1e_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_1e_up_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_rdm_1e_up_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_1e_dn_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_rdm_1e_dn_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_1e_transition_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_rdm_1e_transition_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_en_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_jastrow_en_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_ee_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_jastrow_ee_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_een_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_jastrow_een_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_en_nucleus_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_jastrow_en_nucleus_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_een_nucleus_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_jastrow_een_nucleus_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_en_scaling_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_jastrow_en_scaling_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_qmc_point_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_qmc_point_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_qmc_psi_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_qmc_psi_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_qmc_e_loc_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(out) :: dset(*)
   end function trexio_read_qmc_e_loc_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_charge_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_nucleus_charge_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_coord_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_nucleus_coord_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_a_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_cell_a_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_b_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_cell_b_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_c_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_cell_c_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_g_a_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_cell_g_a_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_g_b_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_cell_g_b_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_g_c_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_cell_g_c_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_k_point_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_pbc_k_point_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_k_point_weight_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_pbc_k_point_weight_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nucleus_index_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_basis_nucleus_index_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_shell_ang_mom_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_basis_shell_ang_mom_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_shell_factor_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_shell_factor_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_r_power_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_basis_r_power_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_start_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_start_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_size_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_size_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_shell_index_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_basis_shell_index_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_exponent_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_exponent_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_exponent_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_exponent_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_coefficient_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_coefficient_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_coefficient_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_coefficient_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_oscillation_arg_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_oscillation_arg_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_prim_factor_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_prim_factor_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_radius_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_radius_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_phi_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_phi_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_grad_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_grad_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_lap_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_lap_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interpolator_phi_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_interpolator_phi_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interpolator_grad_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_interpolator_grad_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interpolator_lap_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_interpolator_lap_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_max_ang_mom_plus_1_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_ecp_max_ang_mom_plus_1_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_z_core_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_ecp_z_core_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_ang_mom_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_ecp_ang_mom_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_nucleus_index_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_ecp_nucleus_index_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_exponent_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ecp_exponent_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_coefficient_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ecp_coefficient_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_power_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_ecp_power_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_coord_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_grid_coord_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_weight_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_grid_weight_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_ang_coord_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_grid_ang_coord_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_ang_weight_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_grid_ang_weight_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_rad_coord_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_grid_rad_coord_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_rad_weight_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_grid_rad_weight_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_shell_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_ao_shell_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_normalization_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_normalization_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_overlap_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_overlap_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_kinetic_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_kinetic_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_potential_n_e_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_potential_n_e_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_ecp_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_ecp_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_core_hamiltonian_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_core_hamiltonian_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_overlap_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_overlap_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_kinetic_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_kinetic_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_potential_n_e_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_potential_n_e_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_ecp_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_ecp_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_core_hamiltonian_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_core_hamiltonian_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_coefficient_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_coefficient_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_coefficient_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_coefficient_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_occupation_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_occupation_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_energy_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_energy_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_spin_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_mo_spin_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_k_point_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_mo_k_point_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_overlap_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_overlap_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_kinetic_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_kinetic_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_potential_n_e_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_potential_n_e_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_ecp_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_ecp_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_core_hamiltonian_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_core_hamiltonian_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_overlap_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_overlap_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_kinetic_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_kinetic_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_potential_n_e_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_potential_n_e_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_ecp_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_ecp_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_core_hamiltonian_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_core_hamiltonian_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_1e_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_rdm_1e_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_1e_up_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_rdm_1e_up_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_1e_dn_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_rdm_1e_dn_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_1e_transition_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_rdm_1e_transition_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_en_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_jastrow_en_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_ee_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_jastrow_ee_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_een_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_jastrow_een_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_en_nucleus_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_jastrow_en_nucleus_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_een_nucleus_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: dset(*)
   end function trexio_read_jastrow_een_nucleus_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_en_scaling_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_jastrow_en_scaling_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_qmc_point_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_qmc_point_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_qmc_psi_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_qmc_psi_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_qmc_e_loc_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_qmc_e_loc_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_charge &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_nucleus_charge
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_coord &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_nucleus_coord
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_a &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_cell_a
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_b &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_cell_b
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_c &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_cell_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_g_a &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_cell_g_a
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_g_b &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_cell_g_b
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_cell_g_c &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_cell_g_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_k_point &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_pbc_k_point
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_pbc_k_point_weight &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_pbc_k_point_weight
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nucleus_index &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_basis_nucleus_index
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_shell_ang_mom &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_basis_shell_ang_mom
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_shell_factor &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_shell_factor
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_r_power &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_basis_r_power
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_start &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_start
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_size &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_shell_index &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_basis_shell_index
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_exponent &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_exponent
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_exponent_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_exponent_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_coefficient &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_coefficient_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_coefficient_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_oscillation_arg &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_oscillation_arg
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_prim_factor &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_prim_factor
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_radius &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_radius
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_phi &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_phi
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_grad &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_grad
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_nao_grid_lap &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_nao_grid_lap
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interpolator_phi &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_interpolator_phi
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interpolator_grad &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_interpolator_grad
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_basis_interpolator_lap &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_basis_interpolator_lap
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_max_ang_mom_plus_1 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_ecp_max_ang_mom_plus_1
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_z_core &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_ecp_z_core
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_ang_mom &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_ecp_ang_mom
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_nucleus_index &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_ecp_nucleus_index
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_exponent &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ecp_exponent
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_coefficient &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ecp_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ecp_power &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_ecp_power
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_coord &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_grid_coord
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_weight &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_grid_weight
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_ang_coord &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_grid_ang_coord
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_ang_weight &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_grid_ang_weight
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_rad_coord &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_grid_rad_coord
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_grid_rad_weight &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_grid_rad_weight
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_shell &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_ao_shell
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_normalization &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_normalization
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_overlap &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_overlap
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_kinetic &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_kinetic
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_potential_n_e &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_potential_n_e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_ecp &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_ecp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_core_hamiltonian &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_core_hamiltonian
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_overlap_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_overlap_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_kinetic_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_kinetic_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_potential_n_e_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_potential_n_e_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_ecp_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_ecp_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_1e_int_core_hamiltonian_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_ao_1e_int_core_hamiltonian_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_coefficient &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_coefficient_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_coefficient_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_occupation &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_occupation
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_energy &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_energy
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_spin &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_mo_spin
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_k_point &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_mo_k_point
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_overlap &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_overlap
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_kinetic &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_kinetic
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_potential_n_e &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_potential_n_e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_ecp &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_ecp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_core_hamiltonian &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_core_hamiltonian
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_overlap_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_overlap_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_kinetic_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_kinetic_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_potential_n_e_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_potential_n_e_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_ecp_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_ecp_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_1e_int_core_hamiltonian_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_mo_1e_int_core_hamiltonian_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_1e &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_rdm_1e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_1e_up &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_rdm_1e_up
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_1e_dn &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_rdm_1e_dn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_1e_transition &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_rdm_1e_transition
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_en &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_jastrow_en
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_ee &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_jastrow_ee
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_een &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_jastrow_een
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_en_nucleus &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_jastrow_en_nucleus
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_een_nucleus &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: dset(*)
   end function trexio_read_jastrow_een_nucleus
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_jastrow_en_scaling &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_jastrow_en_scaling
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_qmc_point &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_qmc_point
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_qmc_psi &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_qmc_psi
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_qmc_e_loc &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(out) :: dset(*)
   end function trexio_read_qmc_e_loc
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_ao_2e_int_eri
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_ao_2e_int_eri &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_ao_2e_int_eri
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_lr &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_ao_2e_int_eri_lr
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_ao_2e_int_eri_lr &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_ao_2e_int_eri_lr
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_ao_2e_int_eri_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_ao_2e_int_eri_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_ao_2e_int_eri_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_lr_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_ao_2e_int_eri_lr_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_ao_2e_int_eri_lr_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_ao_2e_int_eri_lr_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_mo_2e_int_eri
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_mo_2e_int_eri &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_mo_2e_int_eri
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_lr &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_mo_2e_int_eri_lr
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_mo_2e_int_eri_lr &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_mo_2e_int_eri_lr
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_mo_2e_int_eri_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_mo_2e_int_eri_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_mo_2e_int_eri_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_lr_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_mo_2e_int_eri_lr_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_mo_2e_int_eri_lr_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_mo_2e_int_eri_lr_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_csf_det_coefficient &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_csf_det_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_csf_det_coefficient &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_csf_det_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_single &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_amplitude_single
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_amplitude_single &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_amplitude_single
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_single_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_amplitude_single_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_amplitude_single_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_amplitude_single_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_double &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_amplitude_double
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_amplitude_double &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_amplitude_double
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_double_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_amplitude_double_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_amplitude_double_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_amplitude_double_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_triple &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_amplitude_triple
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_amplitude_triple &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_amplitude_triple
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_triple_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_amplitude_triple_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_amplitude_triple_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_amplitude_triple_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_quadruple &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_amplitude_quadruple
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_amplitude_quadruple &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_amplitude_quadruple
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_quadruple_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_amplitude_quadruple_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_amplitude_quadruple_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_amplitude_quadruple_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_rdm_2e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_rdm_2e &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_rdm_2e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_upup &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_rdm_2e_upup
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_rdm_2e_upup &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_rdm_2e_upup
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_dndn &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_rdm_2e_dndn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_rdm_2e_dndn &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_rdm_2e_dndn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_updn &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_rdm_2e_updn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_rdm_2e_updn &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_rdm_2e_updn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_transition &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_rdm_2e_transition
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_rdm_2e_transition &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_rdm_2e_transition
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_rdm_2e_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_rdm_2e_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_rdm_2e_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_upup_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_rdm_2e_upup_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_rdm_2e_upup_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_rdm_2e_upup_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_dndn_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_rdm_2e_dndn_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_rdm_2e_dndn_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_rdm_2e_dndn_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_updn_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     real(c_double), intent(out)           :: value_sparse(*)
   end function trexio_read_rdm_2e_updn_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_rdm_2e_updn_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int32_t), intent(out)       :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(out)           :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_read_safe_rdm_2e_updn_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_ao_2e_int_eri_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_lr_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_ao_2e_int_eri_lr_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_cholesky_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_ao_2e_int_eri_cholesky_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_ao_2e_int_eri_lr_cholesky_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_ao_2e_int_eri_lr_cholesky_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_mo_2e_int_eri_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_lr_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_mo_2e_int_eri_lr_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_cholesky_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_mo_2e_int_eri_cholesky_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_2e_int_eri_lr_cholesky_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_mo_2e_int_eri_lr_cholesky_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_csf_det_coefficient_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_csf_det_coefficient_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_single_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_amplitude_single_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_single_exp_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_amplitude_single_exp_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_double_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_amplitude_double_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_double_exp_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_amplitude_double_exp_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_triple_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_amplitude_triple_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_triple_exp_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_amplitude_triple_exp_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_quadruple_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_amplitude_quadruple_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_amplitude_quadruple_exp_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_amplitude_quadruple_exp_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_rdm_2e_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_upup_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_rdm_2e_upup_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_dndn_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_rdm_2e_dndn_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_updn_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_rdm_2e_updn_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_transition_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_rdm_2e_transition_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_cholesky_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_rdm_2e_cholesky_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_upup_cholesky_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_rdm_2e_upup_cholesky_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_dndn_cholesky_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_rdm_2e_dndn_cholesky_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_rdm_2e_updn_cholesky_size &
        (trex_file, size_max) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(out) :: size_max
   end function trexio_read_rdm_2e_updn_cholesky_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_code_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)    :: dset(*)
     integer(c_int32_t), intent(in), value  :: max_str_len
   end function trexio_read_metadata_code_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_metadata_author_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)    :: dset(*)
     integer(c_int32_t), intent(in), value  :: max_str_len
   end function trexio_read_metadata_author_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_nucleus_label_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)    :: dset(*)
     integer(c_int32_t), intent(in), value  :: max_str_len
   end function trexio_read_nucleus_label_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_state_label_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)    :: dset(*)
     integer(c_int32_t), intent(in), value  :: max_str_len
   end function trexio_read_state_label_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_state_file_name_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)    :: dset(*)
     integer(c_int32_t), intent(in), value  :: max_str_len
   end function trexio_read_state_file_name_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_class_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)    :: dset(*)
     integer(c_int32_t), intent(in), value  :: max_str_len
   end function trexio_read_mo_class_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_mo_symmetry_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(out)    :: dset(*)
     integer(c_int32_t), intent(in), value  :: max_str_len
   end function trexio_read_mo_symmetry_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_code_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_metadata_code_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_author_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_metadata_author_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_unsafe_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_metadata_unsafe_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_nucleus_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_repulsion_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in), value :: num
   end function trexio_write_nucleus_repulsion_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_two_pi_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_cell_two_pi_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_periodic_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_pbc_periodic_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_k_point_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_pbc_k_point_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_madelung_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in), value :: num
   end function trexio_write_pbc_madelung_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_electron_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_electron_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_electron_up_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_electron_up_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_electron_dn_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_electron_dn_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_state_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_state_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_state_id_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_state_id_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_state_energy_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in), value :: num
   end function trexio_write_state_energy_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_prim_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_basis_prim_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_shell_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_basis_shell_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_basis_nao_grid_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interp_coeff_cnt_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_basis_interp_coeff_cnt_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_e_cut_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in), value :: num
   end function trexio_write_basis_e_cut_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_ecp_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_rad_precision_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in), value :: num
   end function trexio_write_grid_rad_precision_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_grid_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_max_ang_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_grid_max_ang_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_min_ang_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_grid_min_ang_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_ang_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_grid_ang_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_rad_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_grid_rad_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_cartesian_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_ao_cartesian_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_ao_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_2e_int_eri_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_ao_2e_int_eri_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_2e_int_eri_lr_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_ao_2e_int_eri_lr_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_mo_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_2e_int_eri_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_mo_2e_int_eri_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_2e_int_eri_lr_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_mo_2e_int_eri_lr_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_csf_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_csf_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_rdm_2e_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_upup_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_rdm_2e_upup_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_dndn_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_rdm_2e_dndn_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_updn_cholesky_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_rdm_2e_updn_cholesky_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_en_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_jastrow_en_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_ee_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_jastrow_ee_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_een_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_jastrow_een_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_ee_scaling_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in), value :: num
   end function trexio_write_jastrow_ee_scaling_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_qmc_num_32 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_qmc_num_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_code_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_metadata_code_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_author_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_metadata_author_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_unsafe_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_metadata_unsafe_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_nucleus_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_repulsion_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in), value :: num
   end function trexio_write_nucleus_repulsion_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_two_pi_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_cell_two_pi_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_periodic_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_pbc_periodic_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_k_point_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_pbc_k_point_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_madelung_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in), value :: num
   end function trexio_write_pbc_madelung_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_electron_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_electron_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_electron_up_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_electron_up_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_electron_dn_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_electron_dn_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_state_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_state_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_state_id_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_state_id_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_state_energy_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in), value :: num
   end function trexio_write_state_energy_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_prim_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_basis_prim_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_shell_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_basis_shell_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_basis_nao_grid_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interp_coeff_cnt_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_basis_interp_coeff_cnt_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_e_cut_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in), value :: num
   end function trexio_write_basis_e_cut_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_ecp_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_rad_precision_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in), value :: num
   end function trexio_write_grid_rad_precision_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_grid_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_max_ang_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_grid_max_ang_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_min_ang_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_grid_min_ang_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_ang_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_grid_ang_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_rad_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_grid_rad_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_cartesian_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_ao_cartesian_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_ao_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_2e_int_eri_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_ao_2e_int_eri_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_2e_int_eri_lr_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_ao_2e_int_eri_lr_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_mo_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_2e_int_eri_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_mo_2e_int_eri_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_2e_int_eri_lr_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_mo_2e_int_eri_lr_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_csf_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_csf_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_rdm_2e_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_upup_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_rdm_2e_upup_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_dndn_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_rdm_2e_dndn_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_updn_cholesky_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_rdm_2e_updn_cholesky_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_en_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_jastrow_en_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_ee_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_jastrow_ee_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_een_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_jastrow_een_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_ee_scaling_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in), value :: num
   end function trexio_write_jastrow_ee_scaling_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_qmc_num_64 &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: num
   end function trexio_write_qmc_num_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_code_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_metadata_code_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_author_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_metadata_author_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_unsafe &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_metadata_unsafe
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_nucleus_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_repulsion &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in), value :: num
   end function trexio_write_nucleus_repulsion
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_two_pi &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_cell_two_pi
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_periodic &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_pbc_periodic
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_k_point_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_pbc_k_point_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_madelung &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in), value :: num
   end function trexio_write_pbc_madelung
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_electron_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_electron_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_electron_up_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_electron_up_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_electron_dn_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_electron_dn_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_state_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_state_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_state_id &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_state_id
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_state_energy &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in), value :: num
   end function trexio_write_state_energy
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_prim_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_basis_prim_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_shell_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_basis_shell_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_basis_nao_grid_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interp_coeff_cnt &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_basis_interp_coeff_cnt
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_e_cut &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in), value :: num
   end function trexio_write_basis_e_cut
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_ecp_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_rad_precision &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in), value :: num
   end function trexio_write_grid_rad_precision
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_grid_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_max_ang_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_grid_max_ang_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_min_ang_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_grid_min_ang_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_ang_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_grid_ang_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_rad_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_grid_rad_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_cartesian &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_ao_cartesian
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_ao_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_2e_int_eri_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_ao_2e_int_eri_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_2e_int_eri_lr_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_ao_2e_int_eri_lr_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_mo_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_2e_int_eri_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_mo_2e_int_eri_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_2e_int_eri_lr_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_mo_2e_int_eri_lr_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_csf_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_csf_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_rdm_2e_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_upup_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_rdm_2e_upup_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_dndn_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_rdm_2e_dndn_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_updn_cholesky_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_rdm_2e_updn_cholesky_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_en_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_jastrow_en_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_ee_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_jastrow_ee_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_een_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_jastrow_een_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_ee_scaling &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in), value :: num
   end function trexio_write_jastrow_ee_scaling
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_qmc_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in), value :: num
   end function trexio_write_qmc_num
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_package_version_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_write_metadata_package_version")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(in)    :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_metadata_package_version_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_description_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_write_metadata_description")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(in)    :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_metadata_description_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_point_group_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_write_nucleus_point_group")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(in)    :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_nucleus_point_group_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_state_current_label_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_write_state_current_label")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(in)    :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_state_current_label_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_type_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_write_basis_type")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(in)    :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_basis_type_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_oscillation_kind_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_write_basis_oscillation_kind")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(in)    :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_basis_oscillation_kind_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interpolator_kind_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_write_basis_interpolator_kind")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(in)    :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_basis_interpolator_kind_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_description_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_write_grid_description")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(in)    :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_grid_description_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_type_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_write_mo_type")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(in)    :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_mo_type_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_type_c &
        (trex_file, str, max_str_len) bind(C, &
        name="trexio_write_jastrow_type")
     import
     integer(trexio_t), intent(in), value  :: trex_file
     character(kind=c_char), intent(in)    :: str(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_jastrow_type_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_determinant_coefficient &
        (trex_file, offset_file, buffer_size, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     real(c_double), intent(in)            :: dset(*)
   end function trexio_write_determinant_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_determinant_coefficient &
        (trex_file, &
        offset_file, buffer_size, &
        dset, dset_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     real(c_double), intent(in)            :: dset(*)
     integer(c_int64_t), intent(in), value :: dset_size
   end function trexio_write_safe_determinant_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_csf_coefficient &
        (trex_file, offset_file, buffer_size, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     real(c_double), intent(in)            :: dset(*)
   end function trexio_write_csf_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_csf_coefficient &
        (trex_file, &
        offset_file, buffer_size, &
        dset, dset_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     real(c_double), intent(in)            :: dset(*)
     integer(c_int64_t), intent(in), value :: dset_size
   end function trexio_write_safe_csf_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_charge_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_nucleus_charge_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_coord_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_nucleus_coord_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_a_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_cell_a_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_b_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_cell_b_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_c_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_cell_c_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_g_a_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_cell_g_a_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_g_b_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_cell_g_b_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_g_c_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_cell_g_c_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_k_point_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_pbc_k_point_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_k_point_weight_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_pbc_k_point_weight_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nucleus_index_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_basis_nucleus_index_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_shell_ang_mom_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_basis_shell_ang_mom_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_shell_factor_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_shell_factor_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_r_power_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_basis_r_power_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_start_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_start_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_size_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_size_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_shell_index_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_basis_shell_index_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_exponent_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_exponent_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_exponent_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_exponent_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_coefficient_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_coefficient_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_coefficient_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_coefficient_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_oscillation_arg_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_oscillation_arg_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_prim_factor_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_prim_factor_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_radius_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_radius_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_phi_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_phi_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_grad_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_grad_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_lap_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_lap_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interpolator_phi_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_interpolator_phi_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interpolator_grad_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_interpolator_grad_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interpolator_lap_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_basis_interpolator_lap_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_max_ang_mom_plus_1_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_ecp_max_ang_mom_plus_1_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_z_core_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_ecp_z_core_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_ang_mom_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_ecp_ang_mom_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_nucleus_index_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_ecp_nucleus_index_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_exponent_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ecp_exponent_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_coefficient_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ecp_coefficient_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_power_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_ecp_power_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_coord_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_grid_coord_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_weight_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_grid_weight_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_ang_coord_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_grid_ang_coord_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_ang_weight_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_grid_ang_weight_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_rad_coord_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_grid_rad_coord_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_rad_weight_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_grid_rad_weight_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_shell_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_ao_shell_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_normalization_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ao_normalization_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_overlap_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_overlap_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_kinetic_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_kinetic_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_potential_n_e_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_potential_n_e_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_ecp_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_ecp_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_core_hamiltonian_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_core_hamiltonian_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_overlap_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_overlap_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_kinetic_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_kinetic_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_potential_n_e_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_potential_n_e_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_ecp_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_ecp_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_core_hamiltonian_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_core_hamiltonian_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_coefficient_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_coefficient_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_coefficient_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_coefficient_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_occupation_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_occupation_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_energy_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_energy_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_spin_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_mo_spin_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_k_point_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_mo_k_point_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_overlap_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_overlap_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_kinetic_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_kinetic_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_potential_n_e_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_potential_n_e_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_ecp_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_ecp_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_core_hamiltonian_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_core_hamiltonian_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_overlap_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_overlap_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_kinetic_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_kinetic_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_potential_n_e_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_potential_n_e_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_ecp_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_ecp_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_core_hamiltonian_im_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_core_hamiltonian_im_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_1e_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_rdm_1e_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_1e_up_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_rdm_1e_up_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_1e_dn_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_rdm_1e_dn_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_1e_transition_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_rdm_1e_transition_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_en_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_jastrow_en_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_ee_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_jastrow_ee_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_een_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_jastrow_een_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_en_nucleus_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_jastrow_en_nucleus_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_een_nucleus_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_jastrow_een_nucleus_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_en_scaling_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_jastrow_en_scaling_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_qmc_point_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_qmc_point_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_qmc_psi_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_qmc_psi_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_qmc_e_loc_32 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_float), intent(in) :: dset(*)
   end function trexio_write_qmc_e_loc_32
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_charge_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_nucleus_charge_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_coord_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_nucleus_coord_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_a_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_cell_a_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_b_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_cell_b_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_c_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_cell_c_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_g_a_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_cell_g_a_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_g_b_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_cell_g_b_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_g_c_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_cell_g_c_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_k_point_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_pbc_k_point_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_k_point_weight_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_pbc_k_point_weight_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nucleus_index_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_basis_nucleus_index_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_shell_ang_mom_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_basis_shell_ang_mom_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_shell_factor_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_shell_factor_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_r_power_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_basis_r_power_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_start_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_start_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_size_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_size_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_shell_index_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_basis_shell_index_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_exponent_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_exponent_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_exponent_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_exponent_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_coefficient_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_coefficient_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_coefficient_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_coefficient_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_oscillation_arg_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_oscillation_arg_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_prim_factor_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_prim_factor_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_radius_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_radius_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_phi_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_phi_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_grad_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_grad_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_lap_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_lap_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interpolator_phi_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_interpolator_phi_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interpolator_grad_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_interpolator_grad_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interpolator_lap_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_interpolator_lap_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_max_ang_mom_plus_1_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_ecp_max_ang_mom_plus_1_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_z_core_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_ecp_z_core_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_ang_mom_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_ecp_ang_mom_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_nucleus_index_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_ecp_nucleus_index_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_exponent_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ecp_exponent_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_coefficient_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ecp_coefficient_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_power_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_ecp_power_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_coord_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_grid_coord_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_weight_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_grid_weight_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_ang_coord_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_grid_ang_coord_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_ang_weight_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_grid_ang_weight_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_rad_coord_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_grid_rad_coord_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_rad_weight_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_grid_rad_weight_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_shell_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_ao_shell_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_normalization_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_normalization_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_overlap_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_overlap_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_kinetic_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_kinetic_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_potential_n_e_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_potential_n_e_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_ecp_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_ecp_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_core_hamiltonian_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_core_hamiltonian_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_overlap_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_overlap_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_kinetic_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_kinetic_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_potential_n_e_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_potential_n_e_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_ecp_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_ecp_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_core_hamiltonian_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_core_hamiltonian_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_coefficient_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_coefficient_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_coefficient_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_coefficient_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_occupation_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_occupation_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_energy_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_energy_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_spin_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_mo_spin_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_k_point_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_mo_k_point_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_overlap_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_overlap_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_kinetic_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_kinetic_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_potential_n_e_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_potential_n_e_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_ecp_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_ecp_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_core_hamiltonian_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_core_hamiltonian_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_overlap_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_overlap_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_kinetic_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_kinetic_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_potential_n_e_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_potential_n_e_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_ecp_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_ecp_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_core_hamiltonian_im_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_core_hamiltonian_im_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_1e_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_rdm_1e_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_1e_up_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_rdm_1e_up_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_1e_dn_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_rdm_1e_dn_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_1e_transition_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_rdm_1e_transition_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_en_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_jastrow_en_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_ee_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_jastrow_ee_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_een_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_jastrow_een_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_en_nucleus_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_jastrow_en_nucleus_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_een_nucleus_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in) :: dset(*)
   end function trexio_write_jastrow_een_nucleus_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_en_scaling_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_jastrow_en_scaling_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_qmc_point_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_qmc_point_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_qmc_psi_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_qmc_psi_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_qmc_e_loc_64 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_qmc_e_loc_64
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_charge &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_nucleus_charge
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_coord &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_nucleus_coord
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_a &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_cell_a
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_b &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_cell_b
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_c &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_cell_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_g_a &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_cell_g_a
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_g_b &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_cell_g_b
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_cell_g_c &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_cell_g_c
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_k_point &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_pbc_k_point
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_pbc_k_point_weight &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_pbc_k_point_weight
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nucleus_index &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_basis_nucleus_index
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_shell_ang_mom &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_basis_shell_ang_mom
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_shell_factor &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_shell_factor
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_r_power &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_basis_r_power
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_start &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_start
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_size &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_size
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_shell_index &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_basis_shell_index
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_exponent &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_exponent
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_exponent_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_exponent_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_coefficient &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_coefficient_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_coefficient_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_oscillation_arg &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_oscillation_arg
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_prim_factor &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_prim_factor
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_radius &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_radius
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_phi &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_phi
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_grad &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_grad
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_nao_grid_lap &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_nao_grid_lap
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interpolator_phi &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_interpolator_phi
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interpolator_grad &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_interpolator_grad
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_basis_interpolator_lap &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_basis_interpolator_lap
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_max_ang_mom_plus_1 &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_ecp_max_ang_mom_plus_1
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_z_core &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_ecp_z_core
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_ang_mom &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_ecp_ang_mom
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_nucleus_index &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_ecp_nucleus_index
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_exponent &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ecp_exponent
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_coefficient &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ecp_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ecp_power &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_ecp_power
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_coord &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_grid_coord
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_weight &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_grid_weight
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_ang_coord &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_grid_ang_coord
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_ang_weight &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_grid_ang_weight
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_rad_coord &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_grid_rad_coord
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_grid_rad_weight &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_grid_rad_weight
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_shell &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_ao_shell
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_normalization &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_normalization
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_overlap &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_overlap
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_kinetic &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_kinetic
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_potential_n_e &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_potential_n_e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_ecp &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_ecp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_core_hamiltonian &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_core_hamiltonian
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_overlap_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_overlap_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_kinetic_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_kinetic_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_potential_n_e_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_potential_n_e_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_ecp_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_ecp_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_1e_int_core_hamiltonian_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_ao_1e_int_core_hamiltonian_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_coefficient &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_coefficient_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_coefficient_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_occupation &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_occupation
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_energy &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_energy
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_spin &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_mo_spin
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_k_point &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_mo_k_point
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_overlap &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_overlap
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_kinetic &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_kinetic
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_potential_n_e &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_potential_n_e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_ecp &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_ecp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_core_hamiltonian &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_core_hamiltonian
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_overlap_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_overlap_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_kinetic_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_kinetic_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_potential_n_e_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_potential_n_e_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_ecp_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_ecp_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_1e_int_core_hamiltonian_im &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_mo_1e_int_core_hamiltonian_im
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_1e &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_rdm_1e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_1e_up &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_rdm_1e_up
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_1e_dn &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_rdm_1e_dn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_1e_transition &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_rdm_1e_transition
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_en &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_jastrow_en
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_ee &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_jastrow_ee
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_een &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_jastrow_een
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_en_nucleus &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_jastrow_en_nucleus
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_een_nucleus &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(in) :: dset(*)
   end function trexio_write_jastrow_een_nucleus
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_jastrow_en_scaling &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_jastrow_en_scaling
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_qmc_point &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_qmc_point
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_qmc_psi &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_qmc_psi
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_qmc_e_loc &
        (trex_file, dset) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     real(c_double), intent(in) :: dset(*)
   end function trexio_write_qmc_e_loc
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_2e_int_eri &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_ao_2e_int_eri
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_ao_2e_int_eri &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_ao_2e_int_eri
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_2e_int_eri_lr &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_ao_2e_int_eri_lr
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_ao_2e_int_eri_lr &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_ao_2e_int_eri_lr
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_2e_int_eri_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_ao_2e_int_eri_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_ao_2e_int_eri_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_ao_2e_int_eri_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_ao_2e_int_eri_lr_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_ao_2e_int_eri_lr_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_ao_2e_int_eri_lr_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_ao_2e_int_eri_lr_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_2e_int_eri &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_mo_2e_int_eri
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_mo_2e_int_eri &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_mo_2e_int_eri
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_2e_int_eri_lr &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_mo_2e_int_eri_lr
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_mo_2e_int_eri_lr &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_mo_2e_int_eri_lr
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_2e_int_eri_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_mo_2e_int_eri_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_mo_2e_int_eri_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_mo_2e_int_eri_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_2e_int_eri_lr_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_mo_2e_int_eri_lr_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_mo_2e_int_eri_lr_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_mo_2e_int_eri_lr_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_csf_det_coefficient &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_csf_det_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_csf_det_coefficient &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_csf_det_coefficient
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_amplitude_single &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_amplitude_single
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_amplitude_single &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_amplitude_single
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_amplitude_single_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_amplitude_single_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_amplitude_single_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_amplitude_single_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_amplitude_double &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_amplitude_double
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_amplitude_double &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_amplitude_double
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_amplitude_double_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_amplitude_double_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_amplitude_double_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_amplitude_double_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_amplitude_triple &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_amplitude_triple
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_amplitude_triple &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_amplitude_triple
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_amplitude_triple_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_amplitude_triple_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_amplitude_triple_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_amplitude_triple_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_amplitude_quadruple &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_amplitude_quadruple
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_amplitude_quadruple &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_amplitude_quadruple
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_amplitude_quadruple_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_amplitude_quadruple_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_amplitude_quadruple_exp &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_amplitude_quadruple_exp
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_rdm_2e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_rdm_2e &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_rdm_2e
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_upup &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_rdm_2e_upup
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_rdm_2e_upup &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_rdm_2e_upup
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_dndn &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_rdm_2e_dndn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_rdm_2e_dndn &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_rdm_2e_dndn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_updn &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_rdm_2e_updn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_rdm_2e_updn &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_rdm_2e_updn
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_transition &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_rdm_2e_transition
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_rdm_2e_transition &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_rdm_2e_transition
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_rdm_2e_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_rdm_2e_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_rdm_2e_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_upup_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_rdm_2e_upup_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_rdm_2e_upup_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_rdm_2e_upup_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_dndn_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_rdm_2e_dndn_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_rdm_2e_dndn_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_rdm_2e_dndn_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_rdm_2e_updn_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, value_sparse) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     real(c_double), intent(in)            :: value_sparse(*)
   end function trexio_write_rdm_2e_updn_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_rdm_2e_updn_cholesky &
        (trex_file, &
        offset_file, buffer_size, &
        index_sparse, index_size, &
        value_sparse, value_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int32_t), intent(in)        :: index_sparse(*)
     integer(c_int64_t), intent(in), value :: index_size
     real(c_double), intent(in)            :: value_sparse(*)
     integer(c_int64_t), intent(in), value :: value_size
   end function trexio_write_safe_rdm_2e_updn_cholesky
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_code_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     character(kind=c_char), intent(in)    :: dset(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_metadata_code_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_metadata_author_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     character(kind=c_char), intent(in)    :: dset(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_metadata_author_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_nucleus_label_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     character(kind=c_char), intent(in)    :: dset(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_nucleus_label_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_state_label_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     character(kind=c_char), intent(in)    :: dset(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_state_label_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_state_file_name_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     character(kind=c_char), intent(in)    :: dset(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_state_file_name_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_class_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     character(kind=c_char), intent(in)    :: dset(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_mo_class_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_mo_symmetry_low &
        (trex_file, dset, max_str_len) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     character(kind=c_char), intent(in)    :: dset(*)
     integer(c_int32_t), intent(in), value :: max_str_len
   end function trexio_write_mo_symmetry_low
end interface

interface
   integer(trexio_exit_code) function &
        trexio_has_determinant_list &
        (trex_file) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
   end function trexio_has_determinant_list
end interface

interface
   integer(trexio_exit_code) function &
        trexio_get_int64_num &
        (trex_file, num) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int32_t), intent(out) :: num
   end function trexio_get_int64_num
end interface
interface
   integer(trexio_exit_code) function &
        trexio_read_determinant_list &
     (trex_file, offset_file, buffer_size, list) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int64_t), intent(out)       :: list(*)
   end function trexio_read_determinant_list
end interface

interface
   integer(trexio_exit_code) function &
        trexio_read_safe_determinant_list &
        (trex_file, &
        offset_file, buffer_size, &
        list, list_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(inout)     :: buffer_size
     integer(c_int64_t), intent(out)       :: list(*)
     integer(c_int64_t), intent(in), value :: list_size
   end function trexio_read_safe_determinant_list
end interface
interface
   integer(trexio_exit_code) function &
        trexio_write_determinant_list &
        (trex_file, offset_file, buffer_size, list) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int64_t), intent(in)        :: list(*)
   end function trexio_write_determinant_list
end interface

interface
   integer(trexio_exit_code) function &
        trexio_write_safe_determinant_list &
        (trex_file, &
        offset_file, buffer_size, &
        list, list_size) bind(C)
     import
     integer(trexio_t), intent(in), value :: trex_file
     integer(c_int64_t), intent(in), value :: offset_file
     integer(c_int64_t), intent(in), value :: buffer_size
     integer(c_int64_t), intent(in)        :: list(*)
     integer(c_int64_t), intent(in), value :: list_size
   end function trexio_write_safe_determinant_list
end interface
contains
integer function trexio_info ()
  implicit none
  trexio_info = trexio_info_c()
end function trexio_info

subroutine trexio_string_of_error (error, string)
   implicit none
   integer(trexio_exit_code), intent(in) :: error
   character(len=*), intent(out)            :: string
   integer(c_int32_t)                    :: lenstring
   lenstring = len(string)
   call  trexio_string_of_error_f(error, lenstring, string)
end subroutine trexio_string_of_error

integer(trexio_t) function trexio_open (filename, mode, back_end, rc_open)
  implicit none
  character(len=*), intent(in)                    :: filename
  character, intent(in), value                    :: mode
  integer(trexio_back_end_t), intent(in), value   :: back_end
  integer(trexio_exit_code), intent(out)          :: rc_open
  integer(trexio_exit_code) :: rc

  trexio_open = trexio_open_c(trim(filename) // c_null_char, mode, back_end, rc_open)
  if (trexio_open == 0_8 .or. rc_open /= TREXIO_SUCCESS) then
     return
  endif
  rc = trexio_set_one_based(trexio_open)
  if (rc /= TREXIO_SUCCESS) then
     rc = trexio_close(trexio_open)
     trexio_open = 0_8
  endif
end function trexio_open

integer(trexio_exit_code) function trexio_inquire (filename)
  implicit none
  character(len=*), intent(in)        :: filename

  trexio_inquire = trexio_inquire_c(trim(filename) // c_null_char)
end function trexio_inquire

integer(trexio_exit_code) function trexio_cp (source, destination)
  implicit none
  character(len=*), intent(in)           :: source
  character(len=*), intent(in)           :: destination

  trexio_cp = trexio_cp_c(trim(source) // c_null_char, trim(destination) // c_null_char)
end function trexio_cp

integer(trexio_exit_code) function &
     trexio_to_bitfield_list &
     (list, occupied_num, det_list, N_int)
  implicit none

  integer(c_int32_t), intent(in)        :: list(*)
  integer(c_int32_t), intent(in), value :: occupied_num
  integer(c_int64_t), intent(out)       :: det_list(*)
  integer(c_int32_t), intent(in), value :: N_int
  integer(c_int32_t)                    :: list_0based(occupied_num)

  integer :: i
  do i = 1,occupied_num
    list_0based(i) = list(i) - 1
  enddo

  trexio_to_bitfield_list = trexio_to_bitfield_list_c(list_0based, occupied_num, det_list, N_int)
  if (trexio_to_bitfield_list /= TREXIO_SUCCESS) then
    return
  endif

end function trexio_to_bitfield_list


integer(trexio_exit_code) function trexio_to_orbital_list(N_int, d1, list, occupied_num)
  implicit none

  integer(c_int32_t), intent(in), value :: N_int
  integer(c_int64_t), intent(in)        :: d1(*)
  integer(c_int32_t), intent(out)       :: list(*)
  integer(c_int32_t), intent(out)       :: occupied_num

  integer :: i

  trexio_to_orbital_list = trexio_to_orbital_list_c(N_int, d1, list, occupied_num)
  if (trexio_to_orbital_list /= TREXIO_SUCCESS) then
    return
  endif

  do i = 1,occupied_num
    list(i) = list(i) + 1
  enddo
end function trexio_to_orbital_list


integer(trexio_exit_code) function &
     trexio_to_orbital_list_up_dn &
     (N_int, d1, list_up, list_dn, occ_num_up, occ_num_dn)
  implicit none
  integer(c_int32_t), intent(in), value :: N_int
  integer(c_int64_t), intent(in)        :: d1(*)
  integer(c_int32_t), intent(out)       :: list_up(*)
  integer(c_int32_t), intent(out)       :: list_dn(*)
  integer(c_int32_t), intent(out)       :: occ_num_up
  integer(c_int32_t), intent(out)       :: occ_num_dn

  integer :: i

  trexio_to_orbital_list_up_dn = &
       trexio_to_orbital_list_up_dn_c &
       (N_int, d1, list_up, list_dn, occ_num_up, occ_num_dn)
  if (trexio_to_orbital_list_up_dn /= TREXIO_SUCCESS) then
    return
  endif

  do i = 1,occ_num_up
    list_up(i) = list_up(i) + 1
  enddo
  do i = 1,occ_num_dn
    list_dn(i) = list_dn(i) + 1
  enddo
end function trexio_to_orbital_list_up_dn

subroutine trexio_strarray2str(str_array, max_num_str, str_res)
  implicit none

  integer(c_int64_t), intent(in), value   :: max_num_str  ! number of elements in string array
  character(len=*), intent(in)  :: str_array(*)
  character(len=:), allocatable, intent(out) :: str_res
  integer(c_int64_t) :: i

  str_res = ''
  do i = 1, max_num_str
     str_res = str_res // trim(str_array(i)) // TREXIO_DELIM
  enddo
  str_res = str_res // c_null_char

end subroutine trexio_strarray2str

subroutine trexio_str2strarray(str_flat, max_num_str, max_len_str, str_array)
  implicit none

  integer(c_int64_t), intent(in), value   :: max_num_str  ! number of elements in strign array
  integer(c_int32_t), intent(in), value   :: max_len_str  ! maximum length of a string in an array
  character(kind=c_char), intent(in)      :: str_flat(*)
  character(len=*), intent(inout)         :: str_array(*)

  character(len=max_len_str)  :: tmp_str
  integer(c_int64_t) :: i, j, k, ind, len_flat

  len_flat = (max_len_str+1)*max_num_str + 1

  ind=1
  do i=1,max_num_str
     k = 1
     tmp_str=''
     do j=ind,len_flat
        if (str_flat(j) == TREXIO_DELIM) then
           ind=j+1
           exit
        endif
        tmp_str(k:k) = str_flat(j)
        k = k + 1
     enddo
     str_array(i)=tmp_str
  enddo

end subroutine trexio_str2strarray

subroutine trexio_assert(trexio_rc, check_rc, success_message)
  implicit none

  integer(trexio_exit_code), intent(in), value :: trexio_rc
  integer(trexio_exit_code), intent(in), value :: check_rc
  character(len=*), intent(in), optional  :: success_message

  character(len=128) :: str

  if (trexio_rc == check_rc) then
     if (present(success_message)) write(*,*) success_message
  else
     call trexio_string_of_error(trexio_rc, str)
     print *, trim(str)
     stop 1
  endif

end subroutine trexio_assert
integer(trexio_exit_code) function &
     trexio_read_metadata_package_version &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character, intent(out) :: str(*)

  trexio_read_metadata_package_version = &
   trexio_read_metadata_package_version_c &
   (trex_file, str, max_str_len)

end function trexio_read_metadata_package_version

integer(trexio_exit_code) function &
     trexio_read_metadata_description &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character, intent(out) :: str(*)

  trexio_read_metadata_description = &
   trexio_read_metadata_description_c &
   (trex_file, str, max_str_len)

end function trexio_read_metadata_description

integer(trexio_exit_code) function &
     trexio_read_nucleus_point_group &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character, intent(out) :: str(*)

  trexio_read_nucleus_point_group = &
   trexio_read_nucleus_point_group_c &
   (trex_file, str, max_str_len)

end function trexio_read_nucleus_point_group

integer(trexio_exit_code) function &
     trexio_read_state_current_label &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character, intent(out) :: str(*)

  trexio_read_state_current_label = &
   trexio_read_state_current_label_c &
   (trex_file, str, max_str_len)

end function trexio_read_state_current_label

integer(trexio_exit_code) function &
     trexio_read_basis_type &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character, intent(out) :: str(*)

  trexio_read_basis_type = &
   trexio_read_basis_type_c &
   (trex_file, str, max_str_len)

end function trexio_read_basis_type

integer(trexio_exit_code) function &
     trexio_read_basis_oscillation_kind &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character, intent(out) :: str(*)

  trexio_read_basis_oscillation_kind = &
   trexio_read_basis_oscillation_kind_c &
   (trex_file, str, max_str_len)

end function trexio_read_basis_oscillation_kind

integer(trexio_exit_code) function &
     trexio_read_basis_interpolator_kind &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character, intent(out) :: str(*)

  trexio_read_basis_interpolator_kind = &
   trexio_read_basis_interpolator_kind_c &
   (trex_file, str, max_str_len)

end function trexio_read_basis_interpolator_kind

integer(trexio_exit_code) function &
     trexio_read_grid_description &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character, intent(out) :: str(*)

  trexio_read_grid_description = &
   trexio_read_grid_description_c &
   (trex_file, str, max_str_len)

end function trexio_read_grid_description

integer(trexio_exit_code) function &
     trexio_read_mo_type &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character, intent(out) :: str(*)

  trexio_read_mo_type = &
   trexio_read_mo_type_c &
   (trex_file, str, max_str_len)

end function trexio_read_mo_type

integer(trexio_exit_code) function &
     trexio_read_jastrow_type &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character, intent(out) :: str(*)

  trexio_read_jastrow_type = &
   trexio_read_jastrow_type_c &
   (trex_file, str, max_str_len)

end function trexio_read_jastrow_type

integer(trexio_exit_code) function &
     trexio_read_metadata_code &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(inout) :: dset(*)

  character, allocatable :: str_compiled(:)
  integer(c_int64_t) :: metadata_code_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_metadata_code_num_64 &
       (trex_file, metadata_code_num)
  if (rc /= TREXIO_SUCCESS) then
     trexio_read_metadata_code = rc
  endif

  allocate(str_compiled(metadata_code_num*(max_str_len+1)+1))

  rc = trexio_read_metadata_code_low(trex_file, str_compiled, max_str_len)
  if (rc /= TREXIO_SUCCESS) then
    deallocate(str_compiled)
    trexio_read_metadata_code = rc
  else
    call trexio_str2strarray(str_compiled, &
         metadata_code_num, max_str_len, dset)
    deallocate(str_compiled)
    trexio_read_metadata_code = TREXIO_SUCCESS
  endif

end function trexio_read_metadata_code

integer(trexio_exit_code) function &
     trexio_read_metadata_author &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(inout) :: dset(*)

  character, allocatable :: str_compiled(:)
  integer(c_int64_t) :: metadata_author_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_metadata_author_num_64 &
       (trex_file, metadata_author_num)
  if (rc /= TREXIO_SUCCESS) then
     trexio_read_metadata_author = rc
  endif

  allocate(str_compiled(metadata_author_num*(max_str_len+1)+1))

  rc = trexio_read_metadata_author_low(trex_file, str_compiled, max_str_len)
  if (rc /= TREXIO_SUCCESS) then
    deallocate(str_compiled)
    trexio_read_metadata_author = rc
  else
    call trexio_str2strarray(str_compiled, &
         metadata_author_num, max_str_len, dset)
    deallocate(str_compiled)
    trexio_read_metadata_author = TREXIO_SUCCESS
  endif

end function trexio_read_metadata_author

integer(trexio_exit_code) function &
     trexio_read_nucleus_label &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(inout) :: dset(*)

  character, allocatable :: str_compiled(:)
  integer(c_int64_t) :: nucleus_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_nucleus_num_64 &
       (trex_file, nucleus_num)
  if (rc /= TREXIO_SUCCESS) then
     trexio_read_nucleus_label = rc
  endif

  allocate(str_compiled(nucleus_num*(max_str_len+1)+1))

  rc = trexio_read_nucleus_label_low(trex_file, str_compiled, max_str_len)
  if (rc /= TREXIO_SUCCESS) then
    deallocate(str_compiled)
    trexio_read_nucleus_label = rc
  else
    call trexio_str2strarray(str_compiled, &
         nucleus_num, max_str_len, dset)
    deallocate(str_compiled)
    trexio_read_nucleus_label = TREXIO_SUCCESS
  endif

end function trexio_read_nucleus_label

integer(trexio_exit_code) function &
     trexio_read_state_label &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(inout) :: dset(*)

  character, allocatable :: str_compiled(:)
  integer(c_int64_t) :: state_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_state_num_64 &
       (trex_file, state_num)
  if (rc /= TREXIO_SUCCESS) then
     trexio_read_state_label = rc
  endif

  allocate(str_compiled(state_num*(max_str_len+1)+1))

  rc = trexio_read_state_label_low(trex_file, str_compiled, max_str_len)
  if (rc /= TREXIO_SUCCESS) then
    deallocate(str_compiled)
    trexio_read_state_label = rc
  else
    call trexio_str2strarray(str_compiled, &
         state_num, max_str_len, dset)
    deallocate(str_compiled)
    trexio_read_state_label = TREXIO_SUCCESS
  endif

end function trexio_read_state_label

integer(trexio_exit_code) function &
     trexio_read_state_file_name &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(inout) :: dset(*)

  character, allocatable :: str_compiled(:)
  integer(c_int64_t) :: state_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_state_num_64 &
       (trex_file, state_num)
  if (rc /= TREXIO_SUCCESS) then
     trexio_read_state_file_name = rc
  endif

  allocate(str_compiled(state_num*(max_str_len+1)+1))

  rc = trexio_read_state_file_name_low(trex_file, str_compiled, max_str_len)
  if (rc /= TREXIO_SUCCESS) then
    deallocate(str_compiled)
    trexio_read_state_file_name = rc
  else
    call trexio_str2strarray(str_compiled, &
         state_num, max_str_len, dset)
    deallocate(str_compiled)
    trexio_read_state_file_name = TREXIO_SUCCESS
  endif

end function trexio_read_state_file_name

integer(trexio_exit_code) function &
     trexio_read_mo_class &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(inout) :: dset(*)

  character, allocatable :: str_compiled(:)
  integer(c_int64_t) :: mo_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_mo_num_64 &
       (trex_file, mo_num)
  if (rc /= TREXIO_SUCCESS) then
     trexio_read_mo_class = rc
  endif

  allocate(str_compiled(mo_num*(max_str_len+1)+1))

  rc = trexio_read_mo_class_low(trex_file, str_compiled, max_str_len)
  if (rc /= TREXIO_SUCCESS) then
    deallocate(str_compiled)
    trexio_read_mo_class = rc
  else
    call trexio_str2strarray(str_compiled, &
         mo_num, max_str_len, dset)
    deallocate(str_compiled)
    trexio_read_mo_class = TREXIO_SUCCESS
  endif

end function trexio_read_mo_class

integer(trexio_exit_code) function &
     trexio_read_mo_symmetry &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(inout) :: dset(*)

  character, allocatable :: str_compiled(:)
  integer(c_int64_t) :: mo_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_mo_num_64 &
       (trex_file, mo_num)
  if (rc /= TREXIO_SUCCESS) then
     trexio_read_mo_symmetry = rc
  endif

  allocate(str_compiled(mo_num*(max_str_len+1)+1))

  rc = trexio_read_mo_symmetry_low(trex_file, str_compiled, max_str_len)
  if (rc /= TREXIO_SUCCESS) then
    deallocate(str_compiled)
    trexio_read_mo_symmetry = rc
  else
    call trexio_str2strarray(str_compiled, &
         mo_num, max_str_len, dset)
    deallocate(str_compiled)
    trexio_read_mo_symmetry = TREXIO_SUCCESS
  endif

end function trexio_read_mo_symmetry

integer(trexio_exit_code) function &
     trexio_write_metadata_package_version &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: str

  trexio_write_metadata_package_version = &
   trexio_write_metadata_package_version_c &
   (trex_file, trim(str) // c_null_char, max_str_len)

end function trexio_write_metadata_package_version

integer(trexio_exit_code) function &
     trexio_write_metadata_description &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: str

  trexio_write_metadata_description = &
   trexio_write_metadata_description_c &
   (trex_file, trim(str) // c_null_char, max_str_len)

end function trexio_write_metadata_description

integer(trexio_exit_code) function &
     trexio_write_nucleus_point_group &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: str

  trexio_write_nucleus_point_group = &
   trexio_write_nucleus_point_group_c &
   (trex_file, trim(str) // c_null_char, max_str_len)

end function trexio_write_nucleus_point_group

integer(trexio_exit_code) function &
     trexio_write_state_current_label &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: str

  trexio_write_state_current_label = &
   trexio_write_state_current_label_c &
   (trex_file, trim(str) // c_null_char, max_str_len)

end function trexio_write_state_current_label

integer(trexio_exit_code) function &
     trexio_write_basis_type &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: str

  trexio_write_basis_type = &
   trexio_write_basis_type_c &
   (trex_file, trim(str) // c_null_char, max_str_len)

end function trexio_write_basis_type

integer(trexio_exit_code) function &
     trexio_write_basis_oscillation_kind &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: str

  trexio_write_basis_oscillation_kind = &
   trexio_write_basis_oscillation_kind_c &
   (trex_file, trim(str) // c_null_char, max_str_len)

end function trexio_write_basis_oscillation_kind

integer(trexio_exit_code) function &
     trexio_write_basis_interpolator_kind &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: str

  trexio_write_basis_interpolator_kind = &
   trexio_write_basis_interpolator_kind_c &
   (trex_file, trim(str) // c_null_char, max_str_len)

end function trexio_write_basis_interpolator_kind

integer(trexio_exit_code) function &
     trexio_write_grid_description &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: str

  trexio_write_grid_description = &
   trexio_write_grid_description_c &
   (trex_file, trim(str) // c_null_char, max_str_len)

end function trexio_write_grid_description

integer(trexio_exit_code) function &
     trexio_write_mo_type &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: str

  trexio_write_mo_type = &
   trexio_write_mo_type_c &
   (trex_file, trim(str) // c_null_char, max_str_len)

end function trexio_write_mo_type

integer(trexio_exit_code) function &
     trexio_write_jastrow_type &
     (trex_file, str, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value  :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: str

  trexio_write_jastrow_type = &
   trexio_write_jastrow_type_c &
   (trex_file, trim(str) // c_null_char, max_str_len)

end function trexio_write_jastrow_type

integer(trexio_exit_code) function &
     trexio_write_metadata_code &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: dset(*)

  character(len=:), allocatable :: str_compiled
  integer(c_int64_t) :: metadata_code_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_metadata_code_num_64 &
       (trex_file, metadata_code_num)
  if (rc /= TREXIO_SUCCESS) then
    trexio_write_metadata_code = rc
  else
    call trexio_strarray2str(dset, metadata_code_num, str_compiled)
    trexio_write_metadata_code = &
         trexio_write_metadata_code_low &
         (trex_file, str_compiled, max_str_len)
  endif

end function trexio_write_metadata_code

integer(trexio_exit_code) function &
     trexio_write_metadata_author &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: dset(*)

  character(len=:), allocatable :: str_compiled
  integer(c_int64_t) :: metadata_author_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_metadata_author_num_64 &
       (trex_file, metadata_author_num)
  if (rc /= TREXIO_SUCCESS) then
    trexio_write_metadata_author = rc
  else
    call trexio_strarray2str(dset, metadata_author_num, str_compiled)
    trexio_write_metadata_author = &
         trexio_write_metadata_author_low &
         (trex_file, str_compiled, max_str_len)
  endif

end function trexio_write_metadata_author

integer(trexio_exit_code) function &
     trexio_write_nucleus_label &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: dset(*)

  character(len=:), allocatable :: str_compiled
  integer(c_int64_t) :: nucleus_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_nucleus_num_64 &
       (trex_file, nucleus_num)
  if (rc /= TREXIO_SUCCESS) then
    trexio_write_nucleus_label = rc
  else
    call trexio_strarray2str(dset, nucleus_num, str_compiled)
    trexio_write_nucleus_label = &
         trexio_write_nucleus_label_low &
         (trex_file, str_compiled, max_str_len)
  endif

end function trexio_write_nucleus_label

integer(trexio_exit_code) function &
     trexio_write_state_label &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: dset(*)

  character(len=:), allocatable :: str_compiled
  integer(c_int64_t) :: state_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_state_num_64 &
       (trex_file, state_num)
  if (rc /= TREXIO_SUCCESS) then
    trexio_write_state_label = rc
  else
    call trexio_strarray2str(dset, state_num, str_compiled)
    trexio_write_state_label = &
         trexio_write_state_label_low &
         (trex_file, str_compiled, max_str_len)
  endif

end function trexio_write_state_label

integer(trexio_exit_code) function &
     trexio_write_state_file_name &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: dset(*)

  character(len=:), allocatable :: str_compiled
  integer(c_int64_t) :: state_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_state_num_64 &
       (trex_file, state_num)
  if (rc /= TREXIO_SUCCESS) then
    trexio_write_state_file_name = rc
  else
    call trexio_strarray2str(dset, state_num, str_compiled)
    trexio_write_state_file_name = &
         trexio_write_state_file_name_low &
         (trex_file, str_compiled, max_str_len)
  endif

end function trexio_write_state_file_name

integer(trexio_exit_code) function &
     trexio_write_mo_class &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: dset(*)

  character(len=:), allocatable :: str_compiled
  integer(c_int64_t) :: mo_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_mo_num_64 &
       (trex_file, mo_num)
  if (rc /= TREXIO_SUCCESS) then
    trexio_write_mo_class = rc
  else
    call trexio_strarray2str(dset, mo_num, str_compiled)
    trexio_write_mo_class = &
         trexio_write_mo_class_low &
         (trex_file, str_compiled, max_str_len)
  endif

end function trexio_write_mo_class

integer(trexio_exit_code) function &
     trexio_write_mo_symmetry &
     (trex_file, dset, max_str_len)
  implicit none
  integer(trexio_t), intent(in), value :: trex_file
  integer(c_int32_t), intent(in), value :: max_str_len
  character(len=*), intent(in) :: dset(*)

  character(len=:), allocatable :: str_compiled
  integer(c_int64_t) :: mo_num
  integer(trexio_exit_code) :: rc

  rc = trexio_read_mo_num_64 &
       (trex_file, mo_num)
  if (rc /= TREXIO_SUCCESS) then
    trexio_write_mo_symmetry = rc
  else
    call trexio_strarray2str(dset, mo_num, str_compiled)
    trexio_write_mo_symmetry = &
         trexio_write_mo_symmetry_low &
         (trex_file, str_compiled, max_str_len)
  endif

end function trexio_write_mo_symmetry

end module trexio
