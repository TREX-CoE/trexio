#!/usr/bin/env python3

import json

from os import listdir, scandir, remove
from os.path import isfile, join, dirname, abspath

from generator_tools import *

fileDir = dirname(abspath(__file__))
parentDir = dirname(fileDir)

with open(join(parentDir,'trex.json'), 'r') as f:
    config = json.load(f)

print('Metadata I/O currently not supported')
# TODO, for now remove metadata-related stuff
del config['metadata']
# for now remove rdm because it is hardcoded
##del config['rdm']

# TODO, for now remove char-related stuff
print('Strings I/O currently not supported')

group_dict = get_group_dict(config)
group_list = [item for item in group_dict.keys()]

dim_dict = get_dim_dict(config)

datasets = get_dset_dict(config)
#print(datasets)

numbers = get_num_dict(config)

dset_per_group = get_dset_per_group(config, datasets)
#print(dset_per_group)

num_per_group = get_num_per_group(config, numbers)
#print(num_per_group)

num_detailed = {}
for num in num_per_group.keys():
    tmp_dict = {}
    tmp_dict['group'] = num_per_group[num]
    tmp_dict['group_num'] = num
    num_detailed[num] = tmp_dict

datasets_nostr, datasets_str = split_dset_dict(datasets)


# print all special $group_*$ related keys
#print( [item for item in datasets_nostr['nucleus_coord'].keys() if 'group_' in item])

path_dict = {}
for dir in ['front', 'hdf5', 'text']:
    path_dict[dir] = join(fileDir,f'templates_{dir}')

templ_path_text = join(fileDir,'templates_text')
templ_path_hdf5 = join(fileDir,'templates_hdf5')
templ_path_front = join(fileDir,'templates_front')

files_text = [f for f in listdir(templ_path_text) if isfile(join(templ_path_text, f))]
files_hdf5 = [f for f in listdir(templ_path_hdf5) if isfile(join(templ_path_hdf5, f))]
files_front = [f for f in listdir(templ_path_front) if isfile(join(templ_path_front, f))]

files = files_text + files_hdf5 + files_front

files_funcs = [f for f in files if 'read_' in f or 'write_' in f or 'flush_' in f or 'free_' in f or 'hrw_' in f or 'has_' in f]
files_funcs_dsets = [f for f in files_funcs if 'dset' in f]
files_funcs_nums  = [f for f in files_funcs if 'num' in f]
files_funcs_groups = [f for f in files_funcs if 'group' in f]
files_funcs_groups.append('struct_text_group_dset.h')
# files that correspond to todo1 group (e.g. only iterative population within the function body)
files_auxil = ['def_hdf5.c', 'basic_hdf5.c', 'basic_text_group.c', 'struct_hdf5.h', 'struct_text_group.h'] 


# build files with $group$ and $group$-based
add_condition = 'rc = trexio_text_free_$group$'
triggers = [add_condition, '$group_dset$', '$group_num$', '$group$']
for fname in files_auxil:
    iterative_populate_file(fname, path_dict, triggers, datasets, numbers, group_dict)


# populate has/read/write_num functions 
for fname in files_funcs_nums:
    recursive_populate_file(fname, path_dict, num_detailed)


# populate has/read/write_dset functions 
for fname in files_funcs_dsets:
    recursive_populate_file(fname, path_dict, datasets_nostr)


# build files with functions for text groups
for fname in files_funcs_groups:
    special_populate_text_group(fname, path_dict, group_list, datasets_nostr, num_detailed)

