#!/bin/bash

cat prefix_text.c   > trexio_text.c
cat prefix_text.h   > trexio_text.h

cat basic_text.c   >> trexio_text.c
cat populated/pop_basic_text_group.c >> trexio_text.c

cat populated/pop_struct_text_group_dset.h >> trexio_text.h
cat populated/pop_struct_text_group.h >> trexio_text.h
cat basic_text.h   >> trexio_text.h

cat populated/pop_free_group_text.c >> trexio_text.c
cat populated/pop_read_group_text.c >> trexio_text.c
cat populated/pop_flush_group_text.c >> trexio_text.c
cat populated/pop_free_group_text.h >> trexio_text.h
cat populated/pop_read_group_text.h >> trexio_text.h
cat populated/pop_flush_group_text.h >> trexio_text.h

cat populated/pop_has_dset_data_text.c >> trexio_text.c
#cat populated/pop_has_dset_str_text.c >> trexio_text.c
cat populated/pop_has_num_text.c >> trexio_text.c
cat populated/pop_read_dset_data_text.c >> trexio_text.c
#cat populated/pop_read_dset_str_text.c >> trexio_text.c
cat populated/pop_read_num_text.c >> trexio_text.c
cat populated/pop_write_dset_data_text.c >> trexio_text.c
#cat populated/pop_write_dset_str_text.c >> trexio_text.c
cat populated/pop_write_num_text.c >> trexio_text.c
cat populated/pop_hrw_num_text.h >> trexio_text.h
cat populated/pop_hrw_dset_data_text.h >> trexio_text.h
#cat populated/pop_hrw_dset_str_text.h >> trexio_text.h

cat rdm_text.c >> trexio_text.c
cat rdm_text.h >> trexio_text.h

cat suffix_text.h   >> trexio_text.h

