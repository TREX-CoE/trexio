program test_trexio

  use trexio

  implicit none

  type(c_ptr) :: file1

  integer :: rc 
  integer (c_int64_t) :: num 

  rc = 0
  num = 10

  file1 = trexio_open('trexio_test' // c_null_char, 'w', 1)
!  file1 = trexio_open('test_fort.h5' // c_null_char, 'w', 0)

  rc = trexio_write_nucleus_num(file1, num)
  if (rc == 0) write(*,*) 'SUCCESS 1'

  rc = trexio_close(file1)
  if (rc == 0) write(*,*) 'SUCCESS 2' 

end program test_trexio
