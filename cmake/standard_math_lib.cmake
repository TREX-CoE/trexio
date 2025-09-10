# This function checks if the C standard library includes the symbols for
# math operations and if not, will try to locate the auxiliary library (libm on Unix)
# and link the given target to it.
function(target_link_std_math TARGET VISIBILITY)
  include(CheckCSourceCompiles)

  # Clear variable to not be affected by external code
  set(CMAKE_REQUIRED_LIBRARIES "")

  set(TEST_SOURCE
"
#include <math.h>

int main(int argc, char **argv) {
/* Here, we use log( (double) *argv[0]) to convert the address of the string into
a double. This will give random values: it will not convert the string into a
double. But it will make the code valid for the compiler, and will avoid
optimizations by the compiler to enforce the need of linking with the math
library. */
return (int) (log( (double) *argv[0]) + sin( (double) *argv[1]) + sqrt( (double) *argv[2]));
}
"
  )

  set(VAR_BASENAME "${PROJECT_NAME}_COMPILES_C")

  check_c_source_compiles("${TEST_SOURCE}" "${VAR_BASENAME}")

  if ("${VAR_BASENAME}")
    # No explicit linking to math library required
    return()
  endif()

  set(STD_MATH_LIB "m")

  set(CMAKE_REQUIRED_LIBRARIES "${STD_MATH_LIB}")
  check_c_source_compiles("${TEST_SOURCE}" "${VAR_BASENAME}_WITH_STDMATH")

  if (NOT "${${VAR_BASENAME}_WITH_STDMATH}")
    message(FATAL_ERROR "Program doesn't compile even though linked against '${STD_MATH_LIB}'")
  endif()
  
  target_link_libraries("${TARGET}" "${VISIBILITY}" "${STD_MATH_LIB}")
endfunction()
