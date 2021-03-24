program test_trexio

  call test_write()
  call test_read()

end program test_trexio

subroutine test_write()
   
  use trexio
  use, intrinsic :: iso_c_binding
  implicit none

  type(c_ptr) :: trex_file

  integer :: rc 
  integer (c_int64_t) :: num

  real, dimension(12), target :: charge
  real, dimension(36), target :: coord

  type(c_ptr) :: charge_ptr
  real(c_double), pointer :: charge_cp(:)

  type(c_ptr) :: coord_ptr
  real(c_double), pointer :: coord_cp(:)


  num = 12

  charge = (/6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1. /)

  allocate(charge_cp(size(charge)))
  charge_cp = charge
  charge_ptr = c_loc(charge_cp)

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

  allocate(coord_cp(size(coord)))
  coord_cp = coord
  coord_ptr = c_loc(coord_cp)

  rc = 0

  trex_file = trexio_open('test_text_fort' // c_null_char, 'w', 1)
!  trex_file = trexio_open('test_hdf5_fort.h5' // c_null_char, 'w', 0)

  rc = trexio_write_nucleus_num(trex_file, num)
  if (rc == 0) write(*,*) 'SUCCESS WRITE NUM'

  rc = trexio_write_nucleus_charge(trex_file, charge_ptr)
  if (rc == 0) write(*,*) 'SUCCESS WRITE CHARGE'

  rc = trexio_write_nucleus_coord(trex_file, coord_ptr)
  if (rc == 0) write(*,*) 'SUCCESS WRITE COORD'

  rc = trexio_close(trex_file)
  if (rc == 0) write(*,*) 'SUCCESS CLOSE' 

! ---------------------------------- !
! to modify fiels of existing file:
! text backend -> open with 'w'
! hdf5 backend -> open with 'a'
! ---------------------------------- !

  trex_file = trexio_open('test_text_fort' // c_null_char, 'w', 1);
!  trex_file = trexio_open('test_hdf5_fort.h5' // c_null_char, 'a', 0)
  
  coord(1) = 666.666
  coord_cp = coord
  coord_ptr = c_loc(coord_cp)

  rc = trexio_write_nucleus_coord(trex_file,coord_ptr)
  if (rc == 0) write(*,*) 'SUCCESS MODIFY COORD'

  rc = trexio_close(trex_file)
  if (rc == 0) write(*,*) 'SUCCESS CLOSE 2' 


  deallocate(charge_cp)
  deallocate(coord_cp)

end subroutine test_write

subroutine test_read()

  use trexio
  use, intrinsic :: iso_c_binding
  implicit none

  type(c_ptr) :: trex_file

  integer :: rc 
  integer (c_int64_t) :: num

  type(c_ptr) :: num_test 
  integer, pointer :: num_read
  integer, target :: num666

  real, dimension(12) :: charge

  type(c_ptr) :: charge_ptr
  real(c_double), pointer :: charge_read(:)

  num = 12

  charge = (/0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. /)

  allocate(charge_read(size(charge)))
  charge_read = charge
  charge_ptr = c_loc(charge_read)

  rc = 0

  num_test = c_loc(num666)

  trex_file = trexio_open('test_text_fort' // c_null_char, 'r', 1)
!  trex_file = trexio_open('test_hdf5_fort.h5' // c_null_char, 'r', 0)

  rc = trexio_read_nucleus_num(trex_file, num_test)
  call c_f_pointer(num_test, num_read)

  if (rc == 0 .and. num_read == num) write(*,*) 'SUCCESS READ NUM'

  rc = trexio_read_nucleus_charge(trex_file, charge_ptr)
  call c_f_pointer(charge_ptr, charge_read, [num_read])
   
  if (rc == 0 .and. (abs (charge_read(11) - 1.0) < 1.0D-8) ) write(*,*) 'SUCCESS READ CHARGE'

  rc = trexio_close(trex_file)
  if (rc == 0) write(*,*) 'SUCCESS CLOSE' 

  deallocate(charge_read)

end subroutine test_read

