#!/bin/bash

cat prefix_json.h > trexio_json.h
cat prefix_json.c > trexio_json.c

cat basic_json.h >> trexio_json.h
cat basic_json.c >> trexio_json.c

cat populated/pop_has_group_json.h >> trexio_json.h
cat populated/pop_delete_group_json.h >> trexio_json.h
cat populated/pop_hrw_attr_num_json.h >> trexio_json.h
cat populated/pop_hrw_attr_str_json.h >> trexio_json.h
cat populated/pop_hrw_dset_data_json.h >> trexio_json.h
cat populated/pop_hrw_dset_str_json.h >> trexio_json.h
cat populated/pop_hrw_dset_sparse_json.h >> trexio_json.h
cat populated/pop_hrw_buffered_json.h >> trexio_json.h
cat hrw_determinant_json.h >> trexio_json.h

cat populated/pop_has_group_json.c    >> trexio_json.c
cat populated/pop_delete_group_json.c >> trexio_json.c

cat populated/pop_has_attr_num_json.c   >> trexio_json.c
cat populated/pop_read_attr_num_json.c  >> trexio_json.c
cat populated/pop_write_attr_num_json.c >> trexio_json.c

cat populated/pop_has_attr_str_json.c   >> trexio_json.c
cat populated/pop_read_attr_str_json.c  >> trexio_json.c
cat populated/pop_write_attr_str_json.c >> trexio_json.c

cat populated/pop_has_dset_data_json.c   >> trexio_json.c
cat populated/pop_read_dset_data_json.c  >> trexio_json.c
cat populated/pop_write_dset_data_json.c >> trexio_json.c

cat populated/pop_has_dset_str_json.c   >> trexio_json.c
cat populated/pop_read_dset_str_json.c  >> trexio_json.c
cat populated/pop_write_dset_str_json.c >> trexio_json.c

cat populated/pop_has_dset_sparse_json.c   >> trexio_json.c
cat populated/pop_read_dset_sparse_json.c  >> trexio_json.c
cat populated/pop_write_dset_sparse_json.c >> trexio_json.c

cat populated/pop_has_buffered_json.c   >> trexio_json.c
cat populated/pop_read_buffered_json.c  >> trexio_json.c
cat populated/pop_write_buffered_json.c >> trexio_json.c

cat has_determinant_json.c   >> trexio_json.c
cat read_determinant_json.c  >> trexio_json.c
cat write_determinant_json.c >> trexio_json.c

cat suffix_json.h >> trexio_json.h
