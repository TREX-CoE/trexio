program test_trexio

  call test_write()
  call test_read()

end program test_trexio

subroutine test_write()
   
  use trexio
  use, intrinsic :: iso_c_binding
  implicit none

  integer(8) :: trex_file

  integer :: rc = 1
  integer(8) :: num

  double precision :: charge(12)
  double precision :: coord(36)

  num = 12
  charge = (/6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1. /)
  coord = (/ 0.00000000 ,  1.39250319 ,  0.00000000 , &
            -1.20594314 ,  0.69625160 ,  0.00000000 , &
            -1.20594314 , -0.69625160 ,  0.00000000 , &
             0.00000000 , -1.39250319 ,  0.00000000 , &
             1.20594314 , -0.69625160 ,  0.00000000 , &
             1.20594314 ,  0.69625160 ,  0.00000000 , &
            -2.14171677 ,  1.23652075 ,  0.00000000 , &
            -2.14171677 , -1.23652075 ,  0.00000000 , &
             0.00000000 , -2.47304151 ,  0.00000000 , &
             2.14171677 , -1.23652075 ,  0.00000000 , &
             2.14171677 ,  1.23652075 ,  0.00000000 , &
             0.00000000 ,  2.47304151 ,  0.00000000 /)

!  trex_file = trexio_open('test_text_fort', 'w', TREXIO_TEXT)
  trex_file = trexio_open('test_hdf5_fort.h5', 'w', TREXIO_HDF5)

  rc = trexio_write_nucleus_num(trex_file, num)
  if (rc == 0) write(*,*) 'SUCCESS WRITE NUM'

  rc = trexio_write_nucleus_charge(trex_file, charge)
  if (rc == 0) write(*,*) 'SUCCESS WRITE CHARGE'

  rc = trexio_write_nucleus_coord(trex_file, coord)
  if (rc == 0) write(*,*) 'SUCCESS WRITE COORD'

  rc = trexio_close(trex_file)
  if (rc == 0) write(*,*) 'SUCCESS CLOSE' 

! ---------------------------------- !
! to modify fiels of existing file:
! text backend -> open with 'w'
! hdf5 backend -> open with 'a'
! ---------------------------------- !

!!  trex_file = trexio_open('test_text_fort', 'w', TREXIO_TEXT);
!!  trex_file = trexio_open('test_hdf5_fort.h5', 'a', TREXIO_HDF5)
  
!  coord(1) = 666.666

!  rc = trexio_write_nucleus_coord(trex_file,coord)
!  if (rc == 0) write(*,*) 'SUCCESS MODIFY COORD'

!  rc = trexio_close(trex_file)
!  if (rc == 0) write(*,*) 'SUCCESS CLOSE' 

end subroutine test_write

subroutine test_read()

  use trexio
  use, intrinsic :: iso_c_binding
  implicit none

  integer(8) :: trex_file

  integer :: rc = 1
  integer(8) :: num, num_read

  double precision :: charge(12) 
  double precision :: coord(36) 

  num = 12

!  trex_file = trexio_open('test_text_fort', 'r', TREXIO_TEXT)
  trex_file = trexio_open('test_hdf5_fort.h5', 'r', TREXIO_HDF5)

  rc = trexio_read_nucleus_num(trex_file, num_read)

  if (rc == 0 .and. num_read == num) write(*,*) 'SUCCESS READ NUM'

  rc = trexio_read_nucleus_charge(trex_file, charge)
   
  if (rc == 0 .and. (abs (charge(11) - 1.0) < 1.0D-8) ) write(*,*) 'SUCCESS READ CHARGE'

  rc = trexio_read_nucleus_coord(trex_file, coord)
   
  if (rc == 0 .and. (abs (coord(2) - 1.39250319) < 1.0D-8) ) write(*,*) 'SUCCESS READ COORD'

  rc = trexio_close(trex_file)
  if (rc == 0) write(*,*) 'SUCCESS CLOSE' 

end subroutine test_read

