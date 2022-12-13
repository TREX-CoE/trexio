(*
(** Constants *)
val package_version : string
val version_major   : int
val version_minor   : int
val version_patch   : int
val git_hash        : string
*)

(** Open/close *)

type trexio_file
type trexio_exit_code
type trexio_backend =
  | HDF5
  | TEXT
  | AUTO

type index = int
type dim   = int

val open_file : string -> char -> trexio_backend -> trexio_file
val inquire_file : string -> bool
val close_file : trexio_file -> unit
val set_one_based : trexio_file -> unit
val get_state : trexio_file -> int
val set_state : trexio_file -> int -> unit
val info : unit -> unit

val to_orbital_list : Int64.t array -> int list
val to_orbital_list_up_dn : (Int64.t array)*(Int64.t array) -> (int list)*(int list)

(**** ****)

val read_determinant_list : trexio_file -> offset:int -> buffer_size:int -> (bytes * bytes) array
val write_determinant_list : trexio_file -> offset:int -> (bytes * bytes) array -> unit

val read_determinant_coefficient : trexio_file -> offset:int -> buffer_size:int -> float array
val write_determinant_coefficient : trexio_file -> offset:int -> float array -> unit


