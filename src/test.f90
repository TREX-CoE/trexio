program test_trexio

  use trexio

  implicit none

  type(c_ptr) :: file1

  integer :: rc 
  integer (c_int64_t) :: num

  type(c_ptr) :: num_test 
  integer, pointer :: num_read
  integer, target :: num666

  rc = 0
  num = 10

  num_test = c_loc(num666)

  file1 = trexio_open('trexio_test' // c_null_char, 'w', 1)
!  file1 = trexio_open('test_fort.h5' // c_null_char, 'w', 0)

  rc = trexio_write_nucleus_num(file1, num)
  if (rc == 0) write(*,*) 'SUCCESS WRITE'

  rc = trexio_read_nucleus_num(file1, num_test)

  call c_f_pointer(num_test, num_read)

  if (rc == 0 .and. num_read == num) write(*,*) 'SUCCESS READ'

  rc = trexio_close(file1)
  if (rc == 0) write(*,*) 'SUCCESS CLOSE' 

end program test_trexio
