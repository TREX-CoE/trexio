%module pytrexio
/* Define SWIGWORDSIZE in order to properly align long integers on 64-bit system */
#define SWIGWORDSIZE64
%{
#define SWIG_FILE_WITH_INIT
/* Include the headers in the wrapper code */
#include "trexio_s.h"
#include "trexio.h"
%}

/* Include stdint to recognize types from stdint.h */
%include <stdint.i>

/* NOTE:
   carrays was useful before numpy.i was introduced.
   For Python interface it's better to use numpy arrays instead of carrays, because the latter are less python-ic.
   On the other hand, carrays might be more portable to other target languages.
// Include carrays to work with C pointers to arrays
%include "carrays.i"
// Include classes that correspond to integer and float arrays
%array_class(double, doubleArray);
%array_class(float, floatArray);
%array_class(int32_t, int32Array);
%array_class(int64_t, int64Array);
*/

/* Include typemaps to play with input/output re-casting
   Useful when working with C pointers
*/
%include typemaps.i
/* Redefine the [int32_t*, int64_t*, float*, double*] num
   pattern to be appended to the output tuple.
   Useful for TREXIO read_num functions where the
   num variable is modified by address
*/
/* Return num variables as part of the output tuple */
%apply int *OUTPUT { int32_t* const num};
%apply int *OUTPUT { int64_t* const num};
%apply float *OUTPUT { float* const num};
%apply float *OUTPUT { double* const num};
/* Return TREXIO exit code from trexio_open as part of the output tuple */
%apply int *OUTPUT { trexio_exit_code* const rc_open};
/* Return number of sparse data points stored in the file as part of the output tuple */
%apply int *OUTPUT { int64_t* const size_max};
/* Return number of sparse data points read from the file as part of the output tuple */
%apply int *INOUT { int64_t* const buffer_size_read};

/* Does not work for arrays (SIGSEGV) */

/* This enables access to trexio_[...]_read_dset_str_low set of functions
   in order to return one long string with TREXIO_DELIM delimeter as 2-nd argument of output tuple
   */
%include <cstring.i>
/* This enables read of long strings with TREXIO_DELIM delimeters that can be further converted into an array of string */
%cstring_bounded_output(char* dset_out, 4096);
/* This enables read of single string attributes with pre-defined max_str_len
   for Python we pre-define max_str_len = PYTREXIO_MAX_STR_LENGTH everywhere for simplicity
*/
%cstring_output_maxsize(char* const str_out, const int32_t max_str_len);


/* This block is needed make SWIG treat (double * dset_out|_in, int64_t dim_out|_in) pattern
   as a special case in order to return the NumPy array to Python from C pointer to array
   provided by trexio_read_safe_[dset_num] function.
   NOTE: numpy.i is currently not part of SWIG but included in the numpy distribution (under numpy/tools/swig/numpy.i)
*/
%include "numpy.i"

%init %{
import_array();
%}

/* Typemaps below change the type of numpy array dimensions from int to int64_t */
%numpy_typemaps(double, NPY_DOUBLE, int64_t)
%numpy_typemaps(float, NPY_FLOAT, int64_t)
%numpy_typemaps(int32_t, NPY_INT32, int64_t)
%numpy_typemaps(int64_t, NPY_INT64, int64_t)
/* Enable write|read_safe functions to convert numpy arrays from/to double arrays */
%apply (double* ARGOUT_ARRAY1, int64_t DIM1) {(double* const dset_out, const int64_t dim_out)};
%apply (double* IN_ARRAY1, int64_t DIM1) {(const double* dset_in, const int64_t dim_in)};
/* Enable write|read_safe functions to convert numpy arrays from/to float arrays */
%apply (float* ARGOUT_ARRAY1, int64_t DIM1) {(float* const dset_out, const int64_t dim_out)};
%apply (float* IN_ARRAY1, int64_t DIM1) {(const float* dset_in, const int64_t dim_in)};
/* Enable write|read_safe functions to convert numpy arrays from/to int32 arrays */
%apply (int32_t* ARGOUT_ARRAY1, int64_t DIM1) {(int32_t* const dset_out, const int64_t dim_out)};
%apply (int32_t* IN_ARRAY1, int64_t DIM1) {(const int32_t* dset_in, const int64_t dim_in)};
/* Enable write|read_safe functions to convert numpy arrays from/to int64 arrays */
%apply (int64_t* ARGOUT_ARRAY1, int64_t DIM1) {(int64_t* const dset_out, const int64_t dim_out)};
%apply (int64_t* IN_ARRAY1, int64_t DIM1) {(const int64_t* dset_in, const int64_t dim_in)};
/* Enable write|read_safe functions to convert numpy arrays from/to sparse arrays */
%apply (double* IN_ARRAY1, int64_t DIM1) {(const double* value_sparse_write, const int64_t size_value_write)};
%apply (int32_t* IN_ARRAY1, int64_t DIM1) {(const int32_t* index_sparse_write, const int64_t size_index_write)};

%apply (double* ARGOUT_ARRAY1, int64_t DIM1) {(double* const value_sparse_read, const int64_t size_value_read)};
%apply (int32_t* ARGOUT_ARRAY1, int64_t DIM1) {(int32_t* const index_sparse_read, const int64_t size_index_read)};

/* This tells SWIG to treat char ** dset_in pattern as a special case
   Enables access to trexio_[...]_write_dset_str set of functions directly, i.e.
   by converting input list of strings from Python into char ** of C
*/
%typemap(in) char** dset_in {
  /* Check if is a list */
  if (PyList_Check($input)) {
    int size = PyList_Size($input);
    Py_ssize_t i = 0;
    $1 = (char **) malloc((size+1)*sizeof(char *));
    for (i = 0; i < size; i++) {
      PyObject *o = PyList_GetItem($input, i);
      if (PyUnicode_Check(o)) {
        $1[i] = PyUnicode_AsUTF8(PyList_GetItem($input,i));
      } else {
        PyErr_Format(PyExc_TypeError, "list must contain strings. %d/%d element was not string.", i, size);
        free($1);
        return NULL;
      }
    }
    $1[i] = 0;
  } else {
    PyErr_SetString(PyExc_TypeError, "not a list");
    return NULL;
  }
}
/* This cleans up the char ** array we malloc-ed before */
%typemap(freearg) char** dset_in {
  free((char *) $1);
}

/* Parse the header files to generate wrappers */
%include "trexio_s.h"
%include "trexio.h"
