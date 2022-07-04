#!/bin/bash

cat prefix_text.c   > trexio_text.c
cat prefix_text.h   > trexio_text.h

cat basic_text.c   >> trexio_text.c
cat populated/pop_basic_text_group.c >> trexio_text.c

cat populated/pop_struct_text_group_dset.h >> trexio_text.h
cat populated/pop_struct_text_group.h >> trexio_text.h
cat basic_text.h   >> trexio_text.h

cat hrw_determinant_text.h >> trexio_text.h
cat *_determinant_text.c >> trexio_text.c

cat populated/pop_has_group_text.c >> trexio_text.c
cat populated/pop_hrw_group_text.h >> trexio_text.h

cat populated/pop_free_group_text.c >> trexio_text.c
cat populated/pop_read_group_text.c >> trexio_text.c
cat populated/pop_flush_group_text.c >> trexio_text.c
cat populated/pop_delete_group_text.c >> trexio_text.c
cat populated/pop_free_group_text.h >> trexio_text.h
cat populated/pop_read_group_text.h >> trexio_text.h
cat populated/pop_flush_group_text.h >> trexio_text.h
cat populated/pop_delete_group_text.h >> trexio_text.h

cat populated/pop_has_dset_data_text.c >> trexio_text.c
cat populated/pop_has_dset_str_text.c >> trexio_text.c
cat populated/pop_has_dset_sparse_text.c >> trexio_text.c
cat populated/pop_has_attr_num_text.c >> trexio_text.c
cat populated/pop_has_attr_str_text.c >> trexio_text.c

cat populated/pop_read_dset_data_text.c >> trexio_text.c
cat populated/pop_read_dset_str_text.c >> trexio_text.c
cat populated/pop_read_dset_sparse_text.c >> trexio_text.c
cat populated/pop_read_attr_str_text.c >> trexio_text.c
cat populated/pop_read_attr_num_text.c >> trexio_text.c

cat populated/pop_write_dset_data_text.c >> trexio_text.c
cat populated/pop_write_dset_str_text.c >> trexio_text.c
cat populated/pop_write_dset_sparse_text.c >> trexio_text.c
cat populated/pop_write_attr_str_text.c >> trexio_text.c
cat populated/pop_write_attr_num_text.c >> trexio_text.c

cat populated/pop_hrw_dset_data_text.h >> trexio_text.h
cat populated/pop_hrw_dset_str_text.h >> trexio_text.h
cat populated/pop_hrw_dset_sparse_text.h >> trexio_text.h
cat populated/pop_hrw_attr_num_text.h >> trexio_text.h
cat populated/pop_hrw_attr_str_text.h >> trexio_text.h

cat suffix_text.h   >> trexio_text.h
