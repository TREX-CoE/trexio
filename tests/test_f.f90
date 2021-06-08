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
  use, intrinsic :: iso_c_binding

  implicit none

  character*(*), intent(in) :: file_name
  integer, intent(in) :: back_end

  integer(8) :: trex_file

  integer :: rc = 1

  integer :: i
  integer :: num
  character*(128) :: str

  double precision :: charge(12)
  double precision :: coord(3,12)

  character(len=:), allocatable :: label_str
  character(len=:), allocatable :: sym_str
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

  label_str = ''
  do i = 1,num
    label_str = label_str // trim(label(i)) // TREXIO_DELIM
  enddo

  sym_str = 'B3U with some juice' // c_null_char
! ================= START OF TEST ===================== !

  trex_file = trexio_open(file_name, 'w', back_end)

  rc = trexio_has_nucleus_num(trex_file)
  if (rc == TREXIO_HAS_NOT) then
    write(*,*) 'SUCCESS HAS NOT 1'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_has_nucleus_charge(trex_file)
  if (rc == TREXIO_HAS_NOT) then
    write(*,*) 'SUCCESS HAS NOT 2'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(1)
  endif


  rc = trexio_write_nucleus_num(trex_file, num)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS WRITE NUM'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_write_nucleus_charge(trex_file, charge)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS WRITE CHARGE'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_write_nucleus_coord(trex_file, coord)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS WRITE COORD'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(1)
  endif

  if (back_end == TREXIO_HDF5) rc = trexio_write_nucleus_label(trex_file, label_str, 4)
  deallocate(label_str)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS WRITE LABEL'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(1)
  endif

  if (back_end == TREXIO_HDF5) rc = trexio_write_nucleus_point_group(trex_file, sym_str, 32)
  deallocate(sym_str)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS WRITE POINT GROUP'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_has_nucleus_num(trex_file)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS HAS 1'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_has_nucleus_coord(trex_file)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS HAS 2'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(1)
  endif

  rc = trexio_close(trex_file)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS CLOSE'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(1)
  endif

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
  integer :: num, num_read

  double precision :: charge(12)
  double precision :: coord(3,12)

  character :: label_str(128)
  character(len=4) :: tmp_str
  character(len=4) :: label(12)

  character(len=32) :: sym_str

  character*(128) :: str

  num = 12

! ================= START OF TEST ===================== !

  trex_file = trexio_open(file_name, 'r', back_end)

  rc = trexio_read_nucleus_num(trex_file, num_read)

  if (rc == TREXIO_SUCCESS .and. num_read == num) then
    write(*,*) 'SUCCESS READ NUM'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(1)
  endif


  rc = trexio_read_nucleus_charge(trex_file, charge)

  if (rc == TREXIO_SUCCESS .and. (dabs(charge(11) - 1.d0) < 1.0D-8) ) then
    write(*,*) 'SUCCESS READ CHARGE'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(-1)
  endif

  rc = trexio_read_nucleus_coord(trex_file, coord)

  if (rc == TREXIO_SUCCESS .and. (dabs(coord(2,1) - 1.39250319d0) < 1.0D-8) ) then
    write(*,*) 'SUCCESS READ COORD'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(-1)
  endif

  if (back_end == TREXIO_HDF5) then 
  
  rc = trexio_read_nucleus_label(trex_file, label_str, 4)

  ! --------------------------------------------------
  ! dummy parser of big string with TREXIO_DELIM delimeters
  ! --------------------------------------------------
  ind=1
  offset=1
  do i=1,num
    k = 1
    tmp_str=''
    do j=ind,128

      if ( (label_str(j)==TREXIO_DELIM) ) then
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

  if (rc == TREXIO_SUCCESS .and. (trim(label(2)) == 'Na') ) then
    write(*,*) 'SUCCESS READ LABEL'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(-1)
  endif

  rc = trexio_read_nucleus_point_group(trex_file, sym_str, 32)
  write(*,*) sym_str(1:3)
  if (rc == TREXIO_SUCCESS .and. (sym_str(1:3) == 'B3U') ) then
    write(*,*) 'SUCCESS READ POINT GROUP'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(-1)
  endif

  endif

  rc = trexio_close(trex_file)
  if (rc == TREXIO_SUCCESS) then
    write(*,*) 'SUCCESS CLOSE'
  else
    call trexio_string_of_error(TREXIO_READONLY,str)
    print *, trim(str)
    call exit(1)
  endif


! ================= END OF TEST ===================== !

end subroutine test_read

