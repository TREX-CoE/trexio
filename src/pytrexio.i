%module pytrexio
/* Define SWIGWORDSIZE in order to properly align long integers on 64-bit system */
#define SWIGWORDSIZE64
%{
/* Include the headers in the wrapper code */
#include "trexio.h"
#include "trexio_s.h"
#include "trexio_private.h"
#include "trexio_text.h"
#include "trexio_hdf5.h"
%}

/* Include stdint to recognize types from stdint.h */
%include <stdint.i>
/* Include carrays to work with C-like arrays */
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
/* TODO: Redefine trexio_exit_code and back_end_t types to gain access to the list 
   of back ends and exit codes. Currently: hard-coded back ends
*/
/*%typemap(out) back_end_t {
  // $1 is what we got from our C or C++ call
  $result = PyInt_FromLong((long) $1);
  // $result is what gets given back to Python and we are responsible for setting it
}*/
%constant int TREXIO_HDF5 = 0;
%constant int TREXIO_TEXT = 1;

/* This tells SWIG to treat char ** as a special case */
%typemap(in) char ** {
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
%typemap(freearg) char ** {
  free((char *) $1);
}
/* Now a test function
%inline %{
int print_args(char ** argv) {
  int i = 0;
  while (argv[i]) {
    printf("argv[%d] = %s\n", i, argv[i]);
    i++;
  }
  return i;
}
%}*/
/* Parse the header files to generate wrappers */
%include "trexio.h"
%include "trexio_s.h"
%include "trexio_private.h"
%include "trexio_text.h"
%include "trexio_hdf5.h"
