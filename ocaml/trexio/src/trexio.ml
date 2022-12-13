
type trexio_file

type trexio_exit_code = int

type trexio_backend =
| HDF5
| TEXT
| AUTO

type index = int
type dim   = int

external open_file : string -> char -> trexio_backend -> trexio_file = "caml_open_file"
external close_file : trexio_file -> unit = "caml_close_file"
external inquire_file : string -> bool = "caml_inquire_file"
external set_one_based : trexio_file -> unit = "caml_set_one_based"
external get_state : trexio_file -> int = "caml_get_state"
external set_state : trexio_file -> int -> unit = "caml_set_state"
external info : unit -> unit = "caml_info"

external to_orbital_list : Int64.t array -> int list = "caml_to_orbital_list"


(**** ****)

external read_determinant_list : trexio_file -> offset:int -> buffer_size:int -> (bytes * bytes) array = "caml_read_determinant_list"
external write_determinant_list : trexio_file -> offset:int -> (bytes * bytes) array -> unit = "caml_write_determinant_list"

external read_determinant_coefficient : trexio_file -> offset:int -> buffer_size:int -> float array = "caml_read_determinant_coefficient"
external write_determinant_coefficient : trexio_file -> offset:int -> float array -> unit = "caml_write_determinant_coefficient"


let to_orbital_list_up_dn (up,dn) =
  (to_orbital_list up, to_orbital_list dn)


