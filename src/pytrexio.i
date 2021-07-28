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
/* Include carrays to work with C pointers to arrays */
%include "carrays.i"
/* Include classes that correspond to integer and float arrays */
%array_class(double, doubleArray);
%array_class(float, floatArray);
%array_class(int32_t, int32Array);
%array_class(int64_t, int64Array);
/* Include typemaps to play with input/output re-casting 
   Useful when working with C pointers
*/
%include typemaps.i

/* Redefine the int32_t* and int64_t* num to be output 
   Useful for TREXIO read_num functions where the 
   num variable is modified by address
*/
%apply int *OUTPUT { int32_t* const num};
%apply int *OUTPUT { int64_t* const num};
/* Does not work for arrays (SIGSEGV)
%apply double *OUTPUT { double* const dataset };
*/
/* This enables access to trexio_[...]_read_dset_str_low set of functions
   in order to return one long string with TREXIO_DELIM delimeter as 2-nd argument of output tuple
   */
%include <cstring.i>
%cstring_bounded_output(char* dset_out, 1024);

/* [WIP] TREXIO back ends and exit codes can be redefined in the SWIG target language 
   using %ignore and further #define statements (instead of disabling the type cast in the trexio.h file)
*/
/*
%ignore TREXIO_HDF5;       // Ignore a macro in the header file
%ignore TREXIO_TEST;       // Ignore a macro in the header file
#define TREXIO_HDF5 0
#define TREXIO_TEXT 0
*/

/* This is an attempt to make SWIG treat double * dset_out, const uint64_t dim_out pattern 
   as a special case in order to return the NumPy array to Python from C pointer to array
   provided by trexio_read_safe_[dset_num] function.
   NOTE: numpy.i is currently not part of SWIG but included in the numpy distribution (under numpy/tools/swig/numpy.i)
         This means that the interface file have to be provided to SWIG upon compilation either by 
         copying it to the local working directory or by providing -l/path/to/numpy.i flag upon SWIG compilation
*/
%include "numpy.i"

%init %{
import_array();
%}

%apply (double* ARGOUT_ARRAY1, int DIM1) {(double * const dset_out, const uint64_t dim_out)};

/* This tells SWIG to treat char ** dset_in pattern as a special case 
   Enables access to trexio_[...]_write_dset_str set of functions directly, i.e.
   by converting input list of strings from Python into char ** of C
*/
%typemap(in) char ** dset_in {
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
%typemap(freearg) char ** dset_in {
  free((char *) $1);
}

/* [WIP] This is an attempt to make SWIG treat char ** dset_out as a special case 
   In order to return list of string to Python from C-native char ** dset_out,
   which is modified (but not allocated) within the trexio_[...]_read_dset_str function
*/
%typemap(in, numinputs=0) char ** dset_out (char * temp) {
  /*temp = (char *) malloc(1028*sizeof(char));*/
  $1 = &temp;
}

%typemap(argout) char ** dset_out {
  
  Py_ssize_t i = 0;
  Py_ssize_t mysize = 12;
  PyObject *o_res = PyList_New(mysize);
  PyObject *o;
  for (i = 0; i < mysize; i++) {
     //printf("%s\n", $1[i]);
     o = PyString_FromString($1[i]); 
     PyList_SetItem(o_res, i, o);
  }

  PyObject *o2, *o3;

  if ((!$result) || ($result == Py_None)) {
    $result = o_res;
  } else {
    if (!PyTuple_Check($result)) {
      PyObject *o2 = $result;
      $result = PyTuple_New(1);
      PyTuple_SetItem($result, 0, o2);
    }
    o3 = PyTuple_New(1);
    PyTuple_SetItem(o3, 0, o_res);
    o2 = $result;
    $result = PySequence_Concat(o2, o3);
    Py_DECREF(o2);
    Py_DECREF(o3);
    Py_DECREF(o_res);
  }
}

/* Parse the header files to generate wrappers */
%include "trexio_s.h"
%include "trexio.h"
