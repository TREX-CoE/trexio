#include <stdio.h>
#include <trexio.h>
#include <string.h>
#define CAML_NAME_SPACE
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <caml/misc.h>

static trexio_t* File_val( value file )
{
  return *((trexio_t**) Data_abstract_val(file));
}


CAMLprim value caml_open_file(value filename, value mode, value backend)
{
  CAMLparam3(filename, mode, backend);

  trexio_exit_code rc = 0;
  value v = caml_alloc(1, Abstract_tag);

  trexio_t* result = trexio_open (String_val(filename),
                                  Int_val(mode),
                                  Int_val(backend),
                                  &rc);

  *((trexio_t **) Data_abstract_val(v)) = result;

  if (rc == TREXIO_SUCCESS) {
    CAMLreturn( v );
  } else  {
    caml_failwith(trexio_string_of_error(rc));
  }
}


CAMLprim value caml_close_file(value file)
{
  CAMLparam1(file);
  trexio_exit_code rc = trexio_close( File_val(file) );
  if (rc == TREXIO_SUCCESS) {
    CAMLreturn ( Val_unit );
  } else {
    caml_failwith(trexio_string_of_error(rc));
  }
}


CAMLprim value caml_inquire_file(value filename)
{
  CAMLparam1 (filename);
  trexio_exit_code rc = trexio_inquire( String_val (filename) );
  CAMLreturn(Val_bool(rc == TREXIO_SUCCESS));
}


CAMLprim value caml_set_one_based(value file)
{
  CAMLparam1(file);
  trexio_exit_code rc = trexio_set_one_based( File_val(file) );
  if (rc == TREXIO_SUCCESS) {
    CAMLreturn ( Val_unit );
  } else {
    caml_failwith(trexio_string_of_error(rc));
  }
}


CAMLprim value caml_set_state(value file, value state)
{
  CAMLparam2(file, state);
  printf("%d\n", Int_val(state));
  trexio_exit_code rc = trexio_set_state( File_val(file), (int32_t) Int_val(state) );
  if (rc == TREXIO_SUCCESS) {
    CAMLreturn ( Val_unit );
  } else {
    caml_failwith(trexio_string_of_error(rc));
  }
}


CAMLprim value caml_get_state(value file)
{
  CAMLparam1(file);
  int32_t result;
  trexio_exit_code rc = trexio_get_state( File_val(file), &result );
  if (rc == TREXIO_SUCCESS) {
    CAMLreturn ( Val_int(result) );
  } else {
    caml_failwith(trexio_string_of_error(rc));
  }
}


CAMLprim value caml_info(value unit)
{
  CAMLparam1(unit);
  trexio_exit_code rc = trexio_info();
  if (rc == TREXIO_SUCCESS) {
    CAMLreturn ( Val_unit );
  } else {
    caml_failwith(trexio_string_of_error(rc));
  }
}


CAMLprim value caml_to_orbital_list(value bitfield)
{
  CAMLparam1 ( bitfield );
  CAMLlocal2 ( result, cons );

  int32_t N_int = Wosize_val(bitfield);
  bitfield_t* d1 = (bitfield_t*) malloc (N_int * sizeof(bitfield_t));
  for (int i=0 ; i<N_int ; ++i) {
      d1[i] = Int64_val(Field(bitfield,i));
  }

  int32_t* list = (int32_t*) malloc(N_int * sizeof(bitfield_t) * sizeof(int32_t));
  int32_t occupied_num = 0;

  trexio_exit_code rc = trexio_to_orbital_list (N_int, d1, list, &occupied_num);
  if (rc != TREXIO_SUCCESS) {
     caml_failwith(trexio_string_of_error(rc));
  }

  free(d1);

  result = Val_emptylist;
  for (int i=occupied_num-1 ; i >= 0 ; --i) {
    cons = caml_alloc(2, 0);
    Store_field(cons, 0, Val_int(list[i])); // head
    Store_field(cons, 1, result); // head
    result = cons;
  }

  free(list);
  CAMLreturn(result);
}


/**** ****/

CAMLprim value caml_read_determinant_list(value file_in, value offset_in, value buffer_size_in)
{
  CAMLparam3 ( file_in, offset_in, buffer_size_in );
  CAMLlocal4 ( result, detup, detdn, det );

  trexio_t* file = File_val(file_in);
  int64_t offset = Int_val( offset_in );
  int64_t buffer_size = Int_val( buffer_size_in );

  int32_t int_num = 0;
  trexio_exit_code rc = trexio_get_int64_num(file, &int_num);
  if (rc != TREXIO_SUCCESS) {
     caml_failwith(trexio_string_of_error(rc));
  }

  int64_t* buffer = (int64_t*) malloc ( buffer_size * int_num * 2 * sizeof(int64_t) );

  rc = trexio_read_determinant_list (file, offset, &buffer_size, buffer);
  if (rc != TREXIO_SUCCESS) {
     caml_failwith(trexio_string_of_error(rc));
  }

  result = caml_alloc(buffer_size, 0);
  size_t icount = 0;
  for (size_t i=0 ; i<buffer_size ; ++i) {
     detup = caml_alloc_initialized_string(int_num*sizeof(int64_t), (char*) &(buffer[icount]));
     icount += int_num;
     detdn = caml_alloc_initialized_string(int_num*sizeof(int64_t), (char*) &(buffer[icount]));
     icount += int_num;
     det = caml_alloc_tuple(2);
     Store_field( det, 0, detup );
     Store_field( det, 1, detdn );
     Store_field( result, i, det );
  }

  free(buffer);
  CAMLreturn(result);
}

CAMLprim value caml_write_determinant_list(value file_in, value offset_in, value array)
{
  CAMLparam3 ( file_in, offset_in, array );
  CAMLlocal3 ( detup, detdn, det );

  trexio_t* file = File_val(file_in);
  int64_t offset = Int_val( offset_in );
  int64_t buffer_size = Wosize_val( array );

  int32_t int_num = 0;
  trexio_exit_code rc = trexio_get_int64_num(file, &int_num);
  if (rc != TREXIO_SUCCESS) {
     caml_failwith(trexio_string_of_error(rc));
  }

  int64_t* buffer = (int64_t*) malloc ( buffer_size * int_num * 2 * sizeof(int64_t) );

  for (size_t i=0 ; i<buffer_size ; ++i) {
    det = Field(array, i);
    detup = Field(det, 0);
    detdn = Field(det, 1);
    memcpy(&(buffer[i*int_num*2]), String_val(detup), int_num*sizeof(int64_t));
    memcpy(&(buffer[i*int_num*2 + int_num]), String_val(detdn), int_num*sizeof(int64_t));
  }

  rc = trexio_write_determinant_list (file, offset, buffer_size, buffer);
  if (rc != TREXIO_SUCCESS) {
     caml_failwith(trexio_string_of_error(rc));
  }

  free(buffer);
  CAMLreturn( Val_unit );
}

CAMLprim value caml_read_determinant_coefficient(value file_in, value offset_in, value buffer_size_in)
{
  CAMLparam3 ( file_in, offset_in, buffer_size_in );
  CAMLlocal1 ( result );

  trexio_t* file = File_val(file_in);
  int64_t offset = Int_val( offset_in );
  int64_t buffer_size = Int_val( buffer_size_in );

  double* buffer = (double*) malloc ( buffer_size * sizeof(double) );

  trexio_exit_code rc = trexio_read_determinant_coefficient (file, offset, &buffer_size, buffer);
  if (rc != TREXIO_SUCCESS) {
     caml_failwith(trexio_string_of_error(rc));
  }

  result = caml_alloc(buffer_size * Double_wosize, Double_array_tag);
  for (size_t i=0 ; i<buffer_size ; ++i) {
     Store_double_field( result, i, buffer[i]);
  }

  free(buffer);
  CAMLreturn(result);
}


CAMLprim value caml_write_determinant_coefficient(value file_in, value offset_in, value array)
{
  CAMLparam3 ( file_in, offset_in, array );

  trexio_t* file = File_val(file_in);
  int64_t offset = Int_val( offset_in );
  int64_t buffer_size = Wosize_val( array );

  double* buffer = (double*) malloc ( buffer_size * sizeof(double) );

  for (size_t i=0 ; i<buffer_size ; ++i) {
    buffer[i] = Double_field(array, i);
  }

  trexio_exit_code rc = trexio_write_determinant_coefficient (file, offset, buffer_size, buffer);
  if (rc != TREXIO_SUCCESS) {
     caml_failwith(trexio_string_of_error(rc));
  }

  free(buffer);
  CAMLreturn( Val_unit );
}


