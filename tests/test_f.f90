program test_trexio
  use trexio
  use, intrinsic :: iso_c_binding
  implicit none

  integer :: rc
  logical :: have_hdf5

  print *      , "============================================"
  print'(a,a)' , "         TREXIO VERSION STRING : ", TREXIO_PACKAGE_VERSION
  print'(a,i3)', "         TREXIO MAJOR VERSION  : ", TREXIO_VERSION_MAJOR
  print'(a,i3)', "         TREXIO MINOR VERSION  : ", TREXIO_VERSION_MINOR
  print *      , "============================================"

  rc = trexio_info()

  call system('rm -rf -- test_write_f.dir')
  print *, 'call test_write(''test_write_f.dir'', TREXIO_TEXT)'
  call test_write('test_write_f.dir', TREXIO_TEXT)
  print *, 'call test_read(''test_write_f.dir'', TREXIO_TEXT)'
  call test_read('test_write_f.dir', TREXIO_TEXT)
  call system('rm -rf -- test_write_f.dir')

  call test_read_void('test_write_f.dir', TREXIO_TEXT)

  ! No way to conditionally check whether compilation was done with HDF5
  ! So temporarily disable the test for HDF5 back end at the moment
  have_hdf5 = trexio_has_backend(TREXIO_HDF5)
  if (have_hdf5) then
    call system('rm -f -- test_write_f.h5')
    print *, 'call test_write(''test_write_f.h5'', TREXIO_HDF5)'
    call test_write('test_write_f.h5', TREXIO_HDF5)
    print *, 'call test_read(''test_write_f.h5'', TREXIO_HDF5)'
    call test_read('test_write_f.h5', TREXIO_HDF5)
    call system('rm -f -- test_write_f.h5')

    call test_read_void('test_write_f.h5', TREXIO_HDF5)
  endif

end program test_trexio

subroutine test_write(file_name, back_end)

! ============ Test write functionality =============== !

  use trexio
  use, intrinsic :: iso_c_binding

  implicit none

  character*(*), intent(in) :: file_name
  integer, intent(in) :: back_end

  integer(trexio_t) :: trex_file

  integer(trexio_exit_code) :: rc = 1

  integer :: nucleus_num, mo_num, ao_num, basis_shell_num

  integer :: basis_nucleus_index(24)
  double precision :: charge(12)
  double precision :: coord(3,12)

  character(len=:), allocatable :: sym_str
  character(len=:), allocatable :: label(:)

  ! sparse data
  integer(4) :: index_sparse_ao_2e_int_eri(4,100)
  double precision :: value_sparse_ao_2e_int_eri(100)

  ! determinants
  integer*8 :: det_list(6, 50)
  integer*8 :: det_num
  integer   :: int_num

  integer :: i, j, n_buffers = 5
  integer(8) :: buf_size_sparse, buf_size_det, offset

  buf_size_sparse = 100/n_buffers
  buf_size_det    = 50/n_buffers

  ! fill sparse indices and values
  do i = 1, 100
    index_sparse_ao_2e_int_eri(1,i) = 4*i   - 3
    index_sparse_ao_2e_int_eri(2,i) = 4*i+1 - 3
    index_sparse_ao_2e_int_eri(3,i) = 4*i+2 - 3
    index_sparse_ao_2e_int_eri(4,i) = 4*i+3 - 3
    value_sparse_ao_2e_int_eri(i) = 3.14 + float(i)
  enddo

  ! fill determinant list
  do i = 1, 50
    do j = 1, 6
      det_list(j,i) = 6*i+(j-1) - 5
    enddo
  enddo

  ! parameters to be written
  nucleus_num = 12
  charge = (/ 6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1.  /)
  coord  = reshape( (/ 0.00000000d0,  1.39250319d0 ,  0.00000000d0 , &
                      -1.20594314d0,  0.69625160d0 ,  0.00000000d0 , &
                      -1.20594314d0, -0.69625160d0 ,  0.00000000d0 , &
                       0.00000000d0, -1.39250319d0 ,  0.00000000d0 , &
                       1.20594314d0, -0.69625160d0 ,  0.00000000d0 , &
                       1.20594314d0,  0.69625160d0 ,  0.00000000d0 , &
                      -2.14171677d0,  1.23652075d0 ,  0.00000000d0 , &
                      -2.14171677d0, -1.23652075d0 ,  0.00000000d0 , &
                       0.00000000d0, -2.47304151d0 ,  0.00000000d0 , &
                       2.14171677d0, -1.23652075d0 ,  0.00000000d0 , &
                       2.14171677d0,  1.23652075d0 ,  0.00000000d0 , &
                       0.00000000d0,  2.47304151d0 ,  0.00000000d0 /), &
                       shape(coord) )

  ! the first dimension of det_list (6) corresponds to mo_num=150; adapt the former if the latter is changed
  mo_num = 150
  ao_num = 1000

  basis_shell_num = 24
  basis_nucleus_index = (/ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 /)

  label = [character(len=8) :: 'C', 'Na','C', 'C 66', 'C','C', 'H 99', 'Ru', 'H', 'H',  'H', 'H' ]

  sym_str = 'B3U with some comments'

! ================= START OF TEST ===================== !

  rc = trexio_inquire(file_name)
  call trexio_assert(rc, TREXIO_FAILURE)

  trex_file = trexio_open(file_name, 'w', back_end, rc)
  call trexio_assert(rc, TREXIO_SUCCESS)

  rc = trexio_has_nucleus_num(trex_file)
  call trexio_assert(rc, TREXIO_HAS_NOT, 'SUCCESS HAS NOT 1')

  rc = trexio_has_nucleus_charge(trex_file)
  call trexio_assert(rc, TREXIO_HAS_NOT, 'SUCCESS HAS NOT 2')

  rc = trexio_has_ao_2e_int_eri(trex_file)
  call trexio_assert(rc, TREXIO_HAS_NOT, 'SUCCESS HAS NOT 3')

  rc = trexio_has_determinant_list(trex_file)
  call trexio_assert(rc, TREXIO_HAS_NOT, 'SUCCESS HAS NOT 4')

  rc = trexio_write_nucleus_num(trex_file, nucleus_num)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE NUM')

  rc = trexio_write_nucleus_charge(trex_file, charge)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE CHARGE')

  rc = trexio_write_nucleus_coord(trex_file, coord)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE COORD')

  rc = trexio_write_nucleus_label(trex_file, label, 5)
  deallocate(label)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE LABEL')

  rc = trexio_write_nucleus_point_group(trex_file, sym_str, 32)
  deallocate(sym_str)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE POINT GROUP')

  rc = trexio_write_basis_shell_num(trex_file, basis_shell_num)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE BASIS NUM')

  rc = trexio_write_basis_nucleus_index(trex_file, basis_nucleus_index)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE INDEX')

  ! write ao_num which will be used to determine the optimal size of int indices
  if (trexio_has_ao_num(trex_file) == TREXIO_HAS_NOT) then
    rc = trexio_write_ao_num(trex_file, ao_num)
    call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE AO NUM')
  endif
  ! write mo_num which will be used to determine the optimal size of the determinants bit fields
  if (trexio_has_mo_num(trex_file) == TREXIO_HAS_NOT) then
    rc = trexio_write_mo_num(trex_file, mo_num)
    call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE MO NUM')
  endif


  offset = 0
  do i = 1,n_buffers
    rc = trexio_write_ao_2e_int_eri(trex_file, offset, buf_size_sparse, &
	                                  index_sparse_ao_2e_int_eri(1,offset+1), &
				                            value_sparse_ao_2e_int_eri(offset+1))
    call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE SPARSE')
    offset = offset + buf_size_sparse
  enddo

  offset = 0
  do i = 1,n_buffers
    rc = trexio_write_determinant_list(trex_file, offset, buf_size_det, &
	                                     det_list(1,offset+1))
    call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE DET LIST')
    offset = offset + buf_size_det
  enddo

  rc = trexio_has_nucleus_num(trex_file)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS HAS 1')

  rc = trexio_has_nucleus_coord(trex_file)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS HAS 2')

  rc = trexio_has_ao_2e_int_eri(trex_file)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS HAS 3')

  rc = trexio_has_determinant_list(trex_file)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS HAS 4')

  rc = trexio_close(trex_file)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS CLOSE')

! ================= END OF TEST ===================== !

end subroutine test_write


subroutine test_read(file_name, back_end)

! ============ Test read functionality =============== !

  use trexio
  implicit none

  character*(*), intent(in) :: file_name
  integer, intent(in) :: back_end

  integer(trexio_t) :: trex_file

  integer :: i, j, k, ind, offset, flag
  integer(trexio_exit_code) :: rc = 1
  integer :: num, num_read, basis_shell_num

  integer :: basis_nucleus_index(24)
  double precision :: charge(12)
  double precision :: coord(3,12)

  character        :: label_str(128)
  character(len=4) :: tmp_str
  character(len=4) :: label(12) ! also works with allocatable arrays

  character(len=32) :: sym_str

  ! sparse data
  integer(4) :: index_sparse_ao_2e_int_eri(4,20)
  double precision :: value_sparse_ao_2e_int_eri(20)
  integer(8) :: read_buf_size = 10
  integer(8) :: read_buf_size_save = 10
  integer(8) :: offset_read = 40
  integer(8) :: offset_data_read = 5
  integer(8) :: offset_eof  = 97
  integer(8) :: offset_data_eof = 1
  integer(8) :: size_toread = 0

  ! determinant data
  integer*8 :: det_list(6,50)
  integer*8 :: read_buf_det_size = 20
  integer*8 :: offset_det_read = 10
  integer*8 :: offset_det_data_read = 5
  integer*8 :: determinant_num
  integer   :: int_num

  ! orbital lists
  integer*4 :: orb_list_up(150)
  integer*4 :: orb_list_dn(150)
  integer*4 :: occ_num_up, occ_num_dn

  character*(128) :: str

  num = 12
  basis_shell_num = 24

  index_sparse_ao_2e_int_eri = 0
  value_sparse_ao_2e_int_eri = 0.0d0

  det_list = 0_8
  orb_list_up = 0
  orb_list_dn = 0

! ================= START OF TEST ===================== !

  rc = trexio_inquire(file_name)
  call trexio_assert(rc, TREXIO_SUCCESS)

  trex_file = trexio_open(file_name, 'r', TREXIO_AUTO, rc)
  call trexio_assert(rc, TREXIO_SUCCESS)

  rc = trexio_read_nucleus_num(trex_file, num_read)
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (num_read == num) then
    write(*,*) 'SUCCESS READ NUM'
  else
    print *, 'FAILURE NUM CHECK'
    call exit(-1)
  endif


  rc = trexio_read_nucleus_charge(trex_file, charge)
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (dabs(charge(11) - 1.d0) < 1.0D-8) then
    write(*,*) 'SUCCESS READ CHARGE'
  else
    print *, 'FAILURE CHARGE CHECK'
    call exit(-1)
  endif


  rc = trexio_read_nucleus_coord(trex_file, coord)
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (dabs(coord(2,1) - 1.39250319d0) < 1.0D-8) then
    write(*,*) 'SUCCESS READ COORD'
  else
    print *, 'FAILURE COORD CHECK'
    call exit(-1)
  endif


  rc = trexio_read_nucleus_label(trex_file, label, 2)
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (trim(label(2)) == 'Na') then
    write(*,*) 'SUCCESS READ LABEL'
  else
    print *, 'FAILURE LABEL CHECK'
    call exit(-1)
  endif


  rc = trexio_read_basis_nucleus_index(trex_file, basis_nucleus_index)
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (basis_nucleus_index(12) == 12) then
    write(*,*) 'SUCCESS READ INDEX'
  else
    print *, 'FAILURE INDEX CHECK'
    call exit(-1)
  endif


  rc = trexio_read_nucleus_point_group(trex_file, sym_str, 10)
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (sym_str(1:3) == 'B3U') then
    write(*,*) 'SUCCESS READ POINT GROUP'
  else
    print *, 'FAILURE POINT GROUP CHECK'
    call exit(-1)
  endif


  rc = trexio_read_ao_2e_int_eri(trex_file, offset_read, read_buf_size, &
	                         index_sparse_ao_2e_int_eri(1, offset_data_read + 1), &
			         value_sparse_ao_2e_int_eri(offset_data_read + 1))
  !do  i = 1,20
  !  write(*,*) index_sparse_ao_2e_int_eri(1,i)
  !enddo
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (index_sparse_ao_2e_int_eri(1, 1) == 0 .and. &
      index_sparse_ao_2e_int_eri(1, offset_data_read + 1) == offset_read*4 + 1) then
    write(*,*) 'SUCCESS READ SPARSE DATA'
  else
    print *, 'FAILURE SPARSE DATA CHECK'
    call exit(-1)
  endif


  ! attempt to read reaching EOF: should return TREXIO_END and
  ! NOT increment the existing values in the buffer (only upd with what has been read)
  rc = trexio_read_ao_2e_int_eri(trex_file, offset_eof, read_buf_size, &
	                         index_sparse_ao_2e_int_eri(1, offset_data_eof + 1), &
			         value_sparse_ao_2e_int_eri(offset_data_eof + 1))
  !do  i = 1,20
  !  write(*,*) index_sparse_ao_2e_int_eri(1,i)
  !enddo
  call trexio_assert(rc, TREXIO_END)
  if (read_buf_size == 3 .and. &
      index_sparse_ao_2e_int_eri(1, 1) == 0 .and. &
      index_sparse_ao_2e_int_eri(1, offset_data_read + 1) == offset_read*4 + 1 .and. &
      index_sparse_ao_2e_int_eri(1, offset_data_eof + 1) == offset_eof*4 + 1) then
    write(*,*) 'SUCCESS READ SPARSE DATA EOF'
    read_buf_size = read_buf_size_save
  else
    print *, 'FAILURE SPARSE DATA EOF CHECK'
    call exit(-1)
  endif

  ! read the size (number of integrals) of the sparse dataset
  rc = trexio_read_ao_2e_int_eri_size(trex_file, size_toread)
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (size_toread == 100) then
    write(*,*) 'SUCCESS READ SPARSE SIZE'
  else
    print *, 'FAILURE SPARSE SIZE CHECK'
    call exit(-1)
  endif

  ! obtain a number of int64 bit fields per determinant
  rc = trexio_get_int64_num(trex_file, int_num)
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (int_num == 3) then
    write(*,*) 'SUCCESS GET INT64_NUM'
  else
    print *, 'FAILURE DET INT64_NUM CHECK'
    call exit(-1)
  endif

  ! read a chunk of determinants
  rc = trexio_read_determinant_list(trex_file, offset_det_read, read_buf_det_size, &
	                            det_list(1, offset_det_data_read + 1))
  !do  i = 1,50
  !  write(*,*) det_list(1,i)
  !enddo
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (det_list(1, 1) == 0 .and. &
      det_list(1, offset_det_data_read + 1) == offset_det_read*6 + 1) then
    write(*,*) 'SUCCESS READ DET LIST'
  else
    print *, 'FAILURE DET LIST CHECK'
    call exit(-1)
  endif

  ! read the total number of stored determinants
  rc = trexio_read_determinant_num_64(trex_file, determinant_num)
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (determinant_num == 50_8) then
    write(*,*) 'SUCCESS READ DET NUM'
  else
    print *, 'FAILURE DET NUM CHECK'
    call exit(-1)
  endif

  ! convert one given determinant into lists of orbitals
  rc = trexio_to_orbital_list_up_dn(3, det_list(:, offset_det_data_read+1), orb_list_up, orb_list_dn, occ_num_up, occ_num_dn)
  !write(*,*) occ_num_up, occ_num_dn
  !write(*,*) orb_list_up(1:occ_num_up)
  !write(*,*) det_list(:, offset_det_data_read+1)
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (occ_num_up == 16 .and. occ_num_dn == 5) then
    write(*,*) 'SUCCESS CONVERT DET LIST'
  else
    print *, 'FAILURE DET CONVERT CHECK'
    call exit(-1)
  endif

  ! close the file
  rc = trexio_close(trex_file)
  call trexio_assert(rc, TREXIO_SUCCESS)

! ================= END OF TEST ===================== !

end subroutine test_read

subroutine test_read_void(file_name, back_end)

! ============ Test read of non-existing file =============== !

  use trexio
  implicit none

  character*(*), intent(in) :: file_name
  integer, intent(in) :: back_end

  integer(8) :: trex_file
  integer :: rc = 1
  character(128) :: str

! ================= START OF TEST ===================== !

  trex_file = trexio_open(file_name, 'r', back_end, rc)
  if (rc /= TREXIO_OPEN_ERROR) then
    rc = trexio_close(trex_file)
  endif
  call trexio_assert(rc, TREXIO_OPEN_ERROR)

  call trexio_string_of_error(rc, str)
  print *, 'Test error message: ', trim(str)

! ================= END OF TEST ===================== !

end subroutine test_read_void
