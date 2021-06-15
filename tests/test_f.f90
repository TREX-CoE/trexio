program test_trexio
  use trexio
  implicit none

  call system('rm -rf test_write_f.dir')
  print *, 'call test_write(''test_write_f.dir'', TREXIO_TEXT)'
  call test_write('test_write_f.dir', TREXIO_TEXT)
  print *, 'call test_read(''test_write_f.dir'', TREXIO_TEXT)'
  call test_read('test_write_f.dir', TREXIO_TEXT)
  call system('rm -rf test_write_f.dir')

  call system('rm -rf test_write_f.h5')
  print *, 'call test_write(''test_write_f.h5'', TREXIO_HDF5)'
  call test_write('test_write_f.h5', TREXIO_HDF5)
  print *, 'call test_read(''test_write_f.h5'', TREXIO_HDF5)'
  call test_read('test_write_f.h5', TREXIO_HDF5)
  call system('rm -rf test_write_f.h5')

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

  integer :: num

  integer :: basis_nucleus_index(12)
  double precision :: charge(12)
  double precision :: coord(3,12)

  character(len=:), allocatable :: sym_str
  character(len=:), allocatable :: label(:)

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

  label = [character(len=8) :: 'C', 'Na','C', 'C 66', 'C','C', 'H 99', 'Ru', 'H', 'H',  'H', 'H' ]

  sym_str = 'B3U with some comments'

! ================= START OF TEST ===================== !

  trex_file = trexio_open(file_name, 'w', back_end)

  rc = trexio_has_nucleus_num(trex_file)
  call trexio_assert(rc, TREXIO_HAS_NOT, 'SUCCESS HAS NOT 1')

  rc = trexio_has_nucleus_charge(trex_file)
  call trexio_assert(rc, TREXIO_HAS_NOT, 'SUCCESS HAS NOT 2')

  rc = trexio_write_nucleus_num(trex_file, num)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE NUM')

  rc = trexio_write_nucleus_charge(trex_file, charge)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE CHARGE')

  rc = trexio_write_nucleus_coord(trex_file, coord)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE COORD')

  rc = trexio_write_nucleus_label(trex_file, label, 5)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE LABEL')
  deallocate(label)

  rc = trexio_write_nucleus_point_group(trex_file, sym_str, 32)
  deallocate(sym_str)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE POINT GROUP')


  rc = trexio_write_basis_nucleus_index(trex_file, basis_nucleus_index)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS WRITE INDEX')


  rc = trexio_has_nucleus_num(trex_file)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS HAS 1')

  rc = trexio_has_nucleus_coord(trex_file)
  call trexio_assert(rc, TREXIO_SUCCESS, 'SUCCESS HAS 2')

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
  integer :: num, num_read

  integer :: basis_nucleus_index(12)
  double precision :: charge(12)
  double precision :: coord(3,12)

  character        :: label_str(128)
  character(len=4) :: tmp_str
  character(len=4) :: label(12) ! also works with allocatable arrays

  character(len=32) :: sym_str

  character*(128) :: str

  num = 12

! ================= START OF TEST ===================== !

  trex_file = trexio_open(file_name, 'r', back_end)


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


  rc = trexio_close(trex_file)
  call trexio_assert(rc, TREXIO_SUCCESS)

! ================= END OF TEST ===================== !

end subroutine test_read

