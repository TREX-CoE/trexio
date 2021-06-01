program test_trexio

  call test_write()
  call test_read()

end program test_trexio

subroutine test_write()

! ============ Test write functionality =============== !

  use trexio
  use, intrinsic :: iso_c_binding, only: c_new_line

  implicit none

  integer(8) :: trex_file

  integer :: rc = 1
  integer :: i, num

  double precision :: charge(12)
  double precision :: coord(3,12)

  character(len=:), allocatable :: label_str
  character(len=4):: label(12)

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

  label = [character(len=4) :: 'C', 'Na','C', 'C', 'C','C', 'H', 'H', 'H', 'Ru',  'H', 'H' ]

  label_str=''
  do i = 1,num
!    label_str=label_str//trim(label(i))//' '
    label_str=label_str//trim(label(i))//c_new_line
  enddo


! ================= START OF TEST ===================== !

!  trex_file = trexio_open('trexio_test_fort', 'w', TREXIO_TEXT)
  trex_file = trexio_open('test_hdf5_fort.h5', 'w', TREXIO_HDF5)

  rc = trexio_has_nucleus_num(trex_file)
  if (rc == TREXIO_HAS_NOT) write(*,*) 'SUCCESS HAS NOT 1'
  rc = trexio_has_nucleus_charge(trex_file)
  if (rc == TREXIO_HAS_NOT) write(*,*) 'SUCCESS HAS NOT 2'

  rc = trexio_write_nucleus_num(trex_file, num)
  if (rc == TREXIO_SUCCESS) write(*,*) 'SUCCESS WRITE NUM'

  rc = trexio_write_nucleus_charge(trex_file, charge)
  if (rc == TREXIO_SUCCESS) write(*,*) 'SUCCESS WRITE CHARGE'

  rc = trexio_write_nucleus_coord(trex_file, coord)
  if (rc == TREXIO_SUCCESS) write(*,*) 'SUCCESS WRITE COORD'

  rc = trexio_write_nucleus_label(trex_file, label_str)
  if (rc == TREXIO_SUCCESS) write(*,*) 'SUCCESS WRITE LABEL'
  deallocate(label_str)

  rc = trexio_has_nucleus_num(trex_file)
  if (rc == TREXIO_SUCCESS) write(*,*) 'SUCCESS HAS 1'
  rc = trexio_has_nucleus_coord(trex_file)
  if (rc == TREXIO_SUCCESS) write(*,*) 'SUCCESS HAS 2'

  rc = trexio_close(trex_file)
  if (rc == TREXIO_SUCCESS) write(*,*) 'SUCCESS CLOSE'

! ---------------------------------- !
! to modify fiels of existing file:
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

subroutine test_read()

! ============ Test read functionality =============== !

  use trexio
  implicit none

  integer(8) :: trex_file

  integer :: i, j, k, ind, offset, flag
  integer :: rc = 1
  integer :: num, num_read

  double precision :: charge(12)
  double precision :: coord(3,12)
  character :: label_str(128)
  character(len=4) :: tmp_str
  character(len=4) :: label(12)

  character*(128) :: str

  num = 12

! ================= START OF TEST ===================== !

!  trex_file = trexio_open('trexio_test_fort', 'r', TREXIO_TEXT)
  trex_file = trexio_open('test_hdf5_fort.h5', 'r', TREXIO_HDF5)

  rc = trexio_read_nucleus_num(trex_file, num_read)

  if (rc == TREXIO_SUCCESS .and. num_read == num) write(*,*) 'SUCCESS READ NUM'

  rc = trexio_read_nucleus_charge(trex_file, charge)

  if (rc == TREXIO_SUCCESS .and. (abs(charge(11) - 1.0) < 1.0D-8) ) write(*,*) 'SUCCESS READ CHARGE'

  rc = trexio_read_nucleus_coord(trex_file, coord)

  if (rc == TREXIO_SUCCESS .and. (abs(coord(2,1) - 1.39250319d0) < 1.0D-8) ) write(*,*) 'SUCCESS READ COORD'

  rc = trexio_read_nucleus_label(trex_file, label_str)

  ! --------------------------------------------------
  ! dummy parser of big string with space delimeters
  ! --------------------------------------------------
  ind=1
  offset=1
  do i=1,num
    k = 1
    tmp_str=''
    do j=ind,128

      if ( (label_str(j)==c_new_line) ) then
	ind=j+1
	exit
      endif
      tmp_str(k:k) = label_str(j) 
      k = k + 1
    enddo
    label(i)=tmp_str
    offset=ind
  enddo
  write(*,*) label
  ! --------------------------------------------------

  if (rc == TREXIO_SUCCESS .and. (trim(label(2)) == 'Na' )) write(*,*) 'SUCCESS READ LABEL'

  rc = trexio_close(trex_file)
  if (rc == TREXIO_SUCCESS) write(*,*) 'SUCCESS CLOSE'

  call trexio_string_of_error(TREXIO_READONLY,str)
  write(*,*) str

! ================= END OF TEST ===================== !

end subroutine test_read

