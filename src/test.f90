program test_trexio

  use trexio

  implicit none

  type(c_ptr) :: file1

  integer :: rc 
  integer (c_int64_t) :: num

  type(c_ptr) :: num_test 
  integer, pointer :: num_read
  integer, target :: num666

  real, dimension(12), target :: charge
  real, dimension(36) :: coord

  type(c_ptr) :: charge_ptr
  real(c_double), pointer :: charge_cp(:)

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

  rc = 0

  num_test = c_loc(num666)

  file1 = trexio_open('trexio_test' // c_null_char, 'w', 1)
!  file1 = trexio_open('test_fort.h5' // c_null_char, 'w', 0)

  rc = trexio_write_nucleus_num(file1, num)
  if (rc == 0) write(*,*) 'SUCCESS WRITE NUM'

  rc = trexio_write_nucleus_charge(file1, charge_ptr)
  if (rc == 0) write(*,*) 'SUCCESS WRITE CHARGE'

  rc = trexio_read_nucleus_num(file1, num_test)

  call c_f_pointer(num_test, num_read)

  if (rc == 0 .and. num_read == num) write(*,*) 'SUCCESS READ'

  rc = trexio_close(file1)
  if (rc == 0) write(*,*) 'SUCCESS CLOSE' 

  deallocate(charge_cp)

end program test_trexio
