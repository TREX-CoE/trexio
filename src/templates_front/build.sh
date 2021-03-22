#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# prefixes
cat $DIR/prefix_front.c   > trexio.c
cat $DIR/prefix_front.h   > trexio.h
cat $DIR/prefix_s_front.h > trexio_s.h
cat $DIR/prefix_fortran.f90   > trexio_f.f90

# c front end
cat $DIR/populated/pop_*.c >> trexio.c
cat $DIR/populated/pop_*.h >> trexio.h

# fortran front end
cat $DIR/populated/pop_*.f90  >> trexio_f.f90

# suffixes
cat $DIR/suffix_s_front.h >> trexio_s.h
cat $DIR/suffix_front.h   >> trexio.h
cat $DIR/suffix_fortran.f90 >> trexio_f.f90

