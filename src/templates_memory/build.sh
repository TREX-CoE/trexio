#!/bin/bash

# Assemble the in-memory back-end source files from the (populated) templates.
# Mirrors templates_text/build.sh.

cat prefix_memory.c   > trexio_memory.c
cat prefix_memory.h   > trexio_memory.h

cat basic_memory.c                          >> trexio_memory.c
cat populated/pop_basic_memory_group.c      >> trexio_memory.c

cat populated/pop_struct_memory_group_dset.h >> trexio_memory.h
cat populated/pop_struct_memory_group.h      >> trexio_memory.h
cat basic_memory.h                           >> trexio_memory.h

cat hrw_determinant_memory.h >> trexio_memory.h
cat *_determinant_memory.c   >> trexio_memory.c

cat populated/pop_has_group_memory.c   >> trexio_memory.c
cat populated/pop_hrw_group_memory.h   >> trexio_memory.h

cat populated/pop_free_group_memory.c    >> trexio_memory.c
cat populated/pop_read_group_memory.c    >> trexio_memory.c
cat populated/pop_flush_group_memory.c   >> trexio_memory.c
cat populated/pop_delete_group_memory.c  >> trexio_memory.c
cat populated/pop_free_group_memory.h    >> trexio_memory.h
cat populated/pop_read_group_memory.h    >> trexio_memory.h
cat populated/pop_flush_group_memory.h   >> trexio_memory.h
cat populated/pop_delete_group_memory.h  >> trexio_memory.h

cat populated/pop_has_dset_data_memory.c   >> trexio_memory.c
cat populated/pop_has_dset_str_memory.c    >> trexio_memory.c
cat populated/pop_has_dset_sparse_memory.c >> trexio_memory.c
cat populated/pop_has_attr_num_memory.c    >> trexio_memory.c
cat populated/pop_has_attr_str_memory.c    >> trexio_memory.c
cat populated/pop_has_buffered_memory.c    >> trexio_memory.c

cat populated/pop_read_dset_data_memory.c   >> trexio_memory.c
cat populated/pop_read_dset_str_memory.c    >> trexio_memory.c
cat populated/pop_read_dset_sparse_memory.c >> trexio_memory.c
cat populated/pop_read_attr_str_memory.c    >> trexio_memory.c
cat populated/pop_read_attr_num_memory.c    >> trexio_memory.c
cat populated/pop_read_buffered_memory.c    >> trexio_memory.c

cat populated/pop_write_dset_data_memory.c   >> trexio_memory.c
cat populated/pop_write_dset_str_memory.c    >> trexio_memory.c
cat populated/pop_write_dset_sparse_memory.c >> trexio_memory.c
cat populated/pop_write_attr_str_memory.c    >> trexio_memory.c
cat populated/pop_write_attr_num_memory.c    >> trexio_memory.c
cat populated/pop_write_buffered_memory.c    >> trexio_memory.c

cat populated/pop_hrw_dset_data_memory.h   >> trexio_memory.h
cat populated/pop_hrw_dset_str_memory.h    >> trexio_memory.h
cat populated/pop_hrw_dset_sparse_memory.h >> trexio_memory.h
cat populated/pop_hrw_attr_num_memory.h    >> trexio_memory.h
cat populated/pop_hrw_attr_str_memory.h    >> trexio_memory.h
cat populated/pop_hrw_buffered_memory.h    >> trexio_memory.h

cat suffix_memory.h   >> trexio_memory.h
