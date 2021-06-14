program test_trexio
  use trexio
  implicit none

  call system('rm -rf trexio_test_fort')
  print *, 'call test_write(''trexio_test_fort'', TREXIO_TEXT)'
  call test_write('trexio_test_fort', TREXIO_TEXT)
  print *, 'call test_read(''trexio_test_fort'', TREXIO_TEXT)'
  call test_read('trexio_test_fort', TREXIO_TEXT)
  call system('rm -rf trexio_test_fort')

  call system('rm -rf trexio_test_fort')
  print *, 'call test_write(''trexio_test_fort.h5'', TREXIO_HDF5)'
  call test_write('trexio_test_fort.h5', TREXIO_HDF5)
  print *, 'call test_read(''trexio_test_fort.h5'', TREXIO_HDF5)'
  call test_read('trexio_test_fort.h5', TREXIO_HDF5)
  call system('rm -rf trexio_test_fort.h5')

end program test_trexio

subroutine test_write(file_name, back_end)

! ============ Test write functionality =============== !

  use trexio
  implicit none

  character*(*), intent(in) :: file_name
  integer(trexio_backend), intent(in) :: back_end

  integer(8) :: trex_file

  integer :: rc = 1
  integer :: num
  character*(128) :: str


  integer :: basis_nucleus_index(12)
  double precision :: charge(12)
  double precision :: coord(3,12)

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

  basis_nucleus_index = (/ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 /)

! ================= START OF TEST ===================== !

  trex_file = trexio_open(file_name, 'w', back_end)

  rc = trexio_has_nucleus_num(trex_file)
  if (rc == TREXIO_HAS_NOT) then
    write(*,*) 'SUCCESS HAS NOT 1'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_has_nucleus_charge(trex_file)
  if (rc == TREXIO_HAS_NOT) then
    write(*,*) 'SUCCESS HAS NOT 2'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(1)
  endif


  rc = trexio_write_nucleus_num(trex_file, num)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS WRITE NUM'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_write_nucleus_charge(trex_file, charge)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS WRITE CHARGE'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_write_nucleus_coord(trex_file, coord)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS WRITE COORD'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_has_nucleus_num(trex_file)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS HAS 1'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_has_nucleus_coord(trex_file)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS HAS 2'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_write_basis_nucleus_index(trex_file, basis_nucleus_index)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS WRITE INDEX'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_close(trex_file)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS CLOSE'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(1)
  endif


! ---------------------------------- !
! to modify fields of existing file:
! text backend -> open with 'w'
! hdf5 backend -> open with 'a'
! ---------------------------------- !

!!  trex_file = trexio_open('trexio_test_fort', 'w', TREXIO_TEXT);
!!  trex_file = trexio_open('test_hdf5_fort.h5', 'a', TREXIO_HDF5)

!  coord(1) = 666.666

!  rc = trexio_write_nucleus_coord(trex_file,coord)
!  if (rc == TREXIO_SUCCESS) write(*,*) 'SUCCESS MODIFY COORD'

!  rc = trexio_close(trex_file)
!  if (rc == TREXIO_SUCCESS) write(*,*) 'SUCCESS CLOSE'

! ================= END OF TEST ===================== !

end subroutine test_write




subroutine test_read(file_name, back_end)

! ============ Test read functionality =============== !

  use trexio
  implicit none

  character*(*), intent(in) :: file_name
  integer(trexio_backend), intent(in) :: back_end

  integer(8) :: trex_file

  integer :: rc = 1
  integer :: num, num_read

  integer :: basis_nucleus_index(12)
  double precision :: charge(12)
  double precision :: coord(3,12)

  character*(128) :: str

  num = 12

! ================= START OF TEST ===================== !

  trex_file = trexio_open(file_name, 'r', back_end)

  rc = trexio_read_nucleus_num(trex_file, num_read)

  if (rc == TREXIO_SUCCESS .and. num_read == num) then
    write(*,*) 'SUCCESS READ NUM'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(1)
  endif


  rc = trexio_read_nucleus_charge(trex_file, charge)

  if (rc == TREXIO_SUCCESS .and. (dabs(charge(11) - 1.d0) < 1.0D-8) ) then
    write(*,*) 'SUCCESS READ CHARGE'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(-1)
  endif

  rc = trexio_read_nucleus_coord(trex_file, coord)

  if (rc == TREXIO_SUCCESS .and. (dabs(coord(2,1) - 1.39250319d0) < 1.0D-8) ) then
    write(*,*) 'SUCCESS READ COORD'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(-1)
  endif

  rc = trexio_read_basis_nucleus_index(trex_file, basis_nucleus_index)
  if (rc == TREXIO_SUCCESS .and. (basis_nucleus_index(12) == 12) ) then
    write(*,*) 'SUCCESS READ INDEX'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(-1)
  endif


  rc = trexio_close(trex_file)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS CLOSE'
  else
    call trexio_string_of_error(rc,str)
    print *, trim(str)
    call exit(1)
  endif


! ================= END OF TEST ===================== !

end subroutine test_read

