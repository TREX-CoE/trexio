#!/bin/sh

cat prefix_hdf5.c   > trexio_hdf5.c
cat prefix_hdf5.h   > trexio_hdf5.h

cat populated/pop_def_hdf5.c >> trexio_hdf5.c
cat populated/pop_struct_hdf5.h >> trexio_hdf5.h

cat populated/pop_basic_hdf5.c >> trexio_hdf5.c
cat populated/pop_read_dset_hdf5.c >> trexio_hdf5.c
cat populated/pop_read_num_hdf5.c >> trexio_hdf5.c
cat populated/pop_write_dset_hdf5.c >> trexio_hdf5.c
cat populated/pop_write_num_hdf5.c >> trexio_hdf5.c
cat populated/pop_rw_num_hdf5.h >> trexio_hdf5.h
cat populated/pop_rw_dset_hdf5.h >> trexio_hdf5.h

cat suffix_hdf5.h   >> trexio_hdf5.h

