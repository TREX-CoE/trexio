#!/bin/bash

# prefixes
cat prefix_front.c   > trexio.c
cat prefix_front.h   > trexio.h
cat prefix_s_front.h > trexio_s.h
cat prefix_fortran.f90   > trexio_f.f90

# c front end
cat populated/pop_*.c >> trexio.c
cat populated/pop_*.h >> trexio.h

# fortran front end
cat populated/pop_*.f90  >> trexio_f.f90
# add helper functions
cat helper_fortran.f90 >> trexio_f.f90
cat populated/pop_*.fh_90 >> trexio_f.f90

# suffixes
cat suffix_s_front.h >> trexio_s.h
cat suffix_front.h   >> trexio.h
cat suffix_fortran.f90 >> trexio_f.f90

