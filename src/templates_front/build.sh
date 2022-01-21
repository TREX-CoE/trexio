#!/bin/bash

# prefixes
cat prefix_front.c   > trexio.c
cat prefix_front.h   > trexio.h

# parse the config-defined version attributes to pass them to Fortran module file
VERSION_VAL=`grep "PACKAGE_VERSION" ../../include/config.h | cut -d " " -f 3`
VERSION_MAJOR_VAL=`grep "VERSION_MAJOR" ../../include/config.h | cut -d " " -f 3`
VERSION_MINOR_VAL=`grep "VERSION_MINOR" ../../include/config.h | cut -d " " -f 3`
VERSION_PATCH_VAL=`grep "VERSION_PATCH" ../../include/config.h | cut -d " " -f 3`

# grep some usefull constants from the config.h
echo "" >> trexio.h
echo "#define TREXIO_PACKAGE_VERSION ${VERSION_VAL:='0.0.0'}" >> trexio.h
echo "#define TREXIO_VERSION_MAJOR ${VERSION_MAJOR_VAL:=0}" >> trexio.h
echo "#define TREXIO_VERSION_MINOR ${VERSION_MINOR_VAL:=0}" >> trexio.h
echo "#define TREXIO_VERSION_PATCH ${VERSION_PATCH_VAL:=0}" >> trexio.h
echo "" >> trexio.h

cat prefix_s_front.h > trexio_s.h
cat prefix_fortran.f90   > trexio_f.f90
cat prefix_python.py   > trexio.py

# append version string and attributes to the Fortran module file
echo "" >> trexio_f.f90
echo "character(len = 12) :: TREXIO_PACKAGE_VERSION = ${VERSION_VAL}" >> trexio_f.f90
echo "integer :: TREXIO_VERSION_MAJOR = ${VERSION_MAJOR_VAL}" >> trexio_f.f90
echo "integer :: TREXIO_VERSION_MINOR = ${VERSION_MINOR_VAL}" >> trexio_f.f90
echo "integer :: TREXIO_VERSION_PATCH = ${VERSION_PATCH_VAL}" >> trexio_f.f90
echo "" >> trexio_f.f90

# c front end
cat populated/pop_*.c >> trexio.c
cat populated/pop_*.h >> trexio.h

# fortran front end
cat populated/pop_*.f90  >> trexio_f.f90
# add helper functions
cat helper_fortran.f90 >> trexio_f.f90
cat populated/pop_*.fh_90 >> trexio_f.f90

# python front end
cat basic_python.py >> trexio.py
cat populated/pop_*.py >> trexio.py

# suffixes
cat suffix_s_front.h >> trexio_s.h
cat suffix_front.h   >> trexio.h
cat suffix_fortran.f90 >> trexio_f.f90
