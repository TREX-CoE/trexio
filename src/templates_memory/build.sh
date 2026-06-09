#!/bin/bash

# Assemble the in-memory back-end source files from the (populated) templates.
# Mirrors templates_text/build.sh but omits the sparse, buffered and
# determinant categories, which are not yet implemented for this back end.

cat prefix_memory.c   > trexio_memory.c
cat prefix_memory.h   > trexio_memory.h

cat basic_memory.c                          >> trexio_memory.c
cat populated/pop_basic_memory_group.c      >> trexio_memory.c

cat populated/pop_struct_memory_group_dset.h >> trexio_memory.h
cat populated/pop_struct_memory_group.h      >> trexio_memory.h
cat basic_memory.h                           >> trexio_memory.h

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

cat populated/pop_has_dset_data_memory.c >> trexio_memory.c
cat populated/pop_has_dset_str_memory.c  >> trexio_memory.c
cat populated/pop_has_attr_num_memory.c  >> trexio_memory.c
cat populated/pop_has_attr_str_memory.c  >> trexio_memory.c

cat populated/pop_read_dset_data_memory.c >> trexio_memory.c
cat populated/pop_read_dset_str_memory.c  >> trexio_memory.c
cat populated/pop_read_attr_str_memory.c  >> trexio_memory.c
cat populated/pop_read_attr_num_memory.c  >> trexio_memory.c

cat populated/pop_write_dset_data_memory.c >> trexio_memory.c
cat populated/pop_write_dset_str_memory.c  >> trexio_memory.c
cat populated/pop_write_attr_str_memory.c  >> trexio_memory.c
cat populated/pop_write_attr_num_memory.c  >> trexio_memory.c

cat populated/pop_hrw_dset_data_memory.h >> trexio_memory.h
cat populated/pop_hrw_dset_str_memory.h  >> trexio_memory.h
cat populated/pop_hrw_attr_num_memory.h  >> trexio_memory.h
cat populated/pop_hrw_attr_str_memory.h  >> trexio_memory.h

cat suffix_memory.h   >> trexio_memory.h
