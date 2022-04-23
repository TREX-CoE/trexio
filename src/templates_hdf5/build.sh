#!/bin/bash

cat prefix_hdf5.c   > trexio_hdf5.c
cat prefix_hdf5.h   > trexio_hdf5.h

cat populated/pop_def_hdf5.c >> trexio_hdf5.c
cat populated/pop_struct_hdf5.h >> trexio_hdf5.h

cat populated/pop_basic_hdf5.c >> trexio_hdf5.c
cat populated/pop_has_*.c >> trexio_hdf5.c
cat populated/pop_read_*.c >> trexio_hdf5.c
cat populated/pop_write_*.c >> trexio_hdf5.c
cat populated/pop_delete_group_hdf5.c >> trexio_hdf5.c
cat populated/pop_hrw_*.h >> trexio_hdf5.h
cat populated/pop_delete_group_hdf5.h >> trexio_hdf5.h

cat hrw_determinant_hdf5.h >> trexio_hdf5.h
cat *_determinant_hdf5.c >> trexio_hdf5.c

cat helpers_hdf5.c  >> trexio_hdf5.c
cat suffix_hdf5.h   >> trexio_hdf5.h
