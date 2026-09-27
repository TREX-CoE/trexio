program bind_c_check
  use, intrinsic :: iso_c_binding
  implicit none

  interface
     integer(c_int) function trexio_bind_c_symbol(value) &
          bind(C, name="trexio_bind_c_symbol")
       import
       integer(c_int), intent(in), value :: value
     end function trexio_bind_c_symbol
  end interface

  if (trexio_bind_c_symbol(41_c_int) /= 42_c_int) stop 1
end program bind_c_check
