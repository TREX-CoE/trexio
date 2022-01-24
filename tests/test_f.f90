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

  integer(8) :: trex_file

  integer :: rc = 1

  integer :: num, basis_shell_num

  integer :: basis_nucleus_index(24)
  double precision :: charge(12)
  double precision :: coord(3,12)

  character(len=:), allocatable :: sym_str
  character(len=:), allocatable :: label(:)

  ! sparse data
  integer(4) :: index_sparse_mo_2e_int_eri(4,100)
  double precision :: value_sparse_mo_2e_int_eri(100)

  integer :: i, n_buffers = 5
  integer(8) :: buf_size, offset
  buf_size = 100/n_buffers

  do i = 1, 100
    index_sparse_mo_2e_int_eri(1,i) = 4*i   - 3
    index_sparse_mo_2e_int_eri(2,i) = 4*i+1 - 3
    index_sparse_mo_2e_int_eri(3,i) = 4*i+2 - 3
    index_sparse_mo_2e_int_eri(4,i) = 4*i+3 - 3
    value_sparse_mo_2e_int_eri(i) = 3.14 + float(i)
  enddo

  ! parameters to be written
  num = 12
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

  rc = trexio_has_mo_2e_int_eri(trex_file)
  call trexio_assert(rc, TREXIO_HAS_NOT, 'SUCCESS HAS NOT 3')

  rc = trexio_write_nucleus_num(trex_file, num)
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

  ! write mo_num which will be used to determine the optimal size of int indices
  if (trexio_has_mo_num(trex_file) == TREXIO_HAS_NOT) then
    rc = trexio_write_mo_num(trex_file, 1000)
    call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE MO NUM')
  endif

  offset = 0
  do i = 1,n_buffers
    rc = trexio_write_mo_2e_int_eri(trex_file, offset, buf_size, &
	                            index_sparse_mo_2e_int_eri(1,offset+1), &
				    value_sparse_mo_2e_int_eri(offset+1))
    call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE SPARSE')
    offset = offset + buf_size
  enddo

  rc = trexio_has_nucleus_num(trex_file)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS HAS 1')

  rc = trexio_has_nucleus_coord(trex_file)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS HAS 2')

  rc = trexio_has_mo_2e_int_eri(trex_file)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS HAS 3')

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

  integer(8) :: trex_file

  integer :: i, j, k, ind, offset, flag
  integer :: rc = 1
  integer :: num, num_read, basis_shell_num

  integer :: basis_nucleus_index(24)
  double precision :: charge(12)
  double precision :: coord(3,12)

  character        :: label_str(128)
  character(len=4) :: tmp_str
  character(len=4) :: label(12) ! also works with allocatable arrays

  character(len=32) :: sym_str

  ! sparse data
  integer(4) :: index_sparse_mo_2e_int_eri(4,20)
  double precision :: value_sparse_mo_2e_int_eri(20)
  integer(8) :: read_buf_size = 10
  integer(8) :: read_buf_size_save = 10
  integer(8) :: offset_read = 40
  integer(8) :: offset_data_read = 5
  integer(8) :: offset_eof  = 97
  integer(8) :: offset_data_eof = 1
  integer(8) :: size_toread = 0

  character*(128) :: str

  num = 12
  basis_shell_num = 24

  index_sparse_mo_2e_int_eri = 0
  value_sparse_mo_2e_int_eri = 0.0d0

! ================= START OF TEST ===================== !

  rc = trexio_inquire(file_name)
  call trexio_assert(rc, TREXIO_SUCCESS)

  trex_file = trexio_open(file_name, 'r', back_end, rc)
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


  rc = trexio_read_mo_2e_int_eri(trex_file, offset_read, read_buf_size, &
	                         index_sparse_mo_2e_int_eri(1, offset_data_read + 1), &
			         value_sparse_mo_2e_int_eri(offset_data_read + 1))
  !do  i = 1,20
  !  write(*,*) index_sparse_mo_2e_int_eri(1,i)
  !enddo
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (index_sparse_mo_2e_int_eri(1, 1) == 0 .and. &
      index_sparse_mo_2e_int_eri(1, offset_data_read + 1) == offset_read*4 + 1) then
    write(*,*) 'SUCCESS READ SPARSE DATA'
  else
    print *, 'FAILURE SPARSE DATA CHECK'
    call exit(-1)
  endif


  ! attempt to read reaching EOF: should return TREXIO_END and
  ! NOT increment the existing values in the buffer (only upd with what has been read)
  rc = trexio_read_mo_2e_int_eri(trex_file, offset_eof, read_buf_size, &
	                         index_sparse_mo_2e_int_eri(1, offset_data_eof + 1), &
			         value_sparse_mo_2e_int_eri(offset_data_eof + 1))
  !do  i = 1,20
  !  write(*,*) index_sparse_mo_2e_int_eri(1,i)
  !enddo
  call trexio_assert(rc, TREXIO_END)
  if (read_buf_size == 3 .and. &
      index_sparse_mo_2e_int_eri(1, 1) == 0 .and. &
      index_sparse_mo_2e_int_eri(1, offset_data_read + 1) == offset_read*4 + 1 .and. &
      index_sparse_mo_2e_int_eri(1, offset_data_eof + 1) == offset_eof*4 + 1) then
    write(*,*) 'SUCCESS READ SPARSE DATA EOF'
    read_buf_size = read_buf_size_save
  else
    print *, 'FAILURE SPARSE DATA EOF CHECK'
    call exit(-1)
  endif

  rc = trexio_read_mo_2e_int_eri_size(trex_file, size_toread)
  call trexio_assert(rc, TREXIO_SUCCESS)
  if (size_toread == 100) then
    write(*,*) 'SUCCESS READ SPARSE SIZE'
  else
    print *, 'FAILURE SPARSE SIZE CHECK'
    call exit(-1)
  endif


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
  print *, trim(str)

! ================= END OF TEST ===================== !

end subroutine test_read_void
