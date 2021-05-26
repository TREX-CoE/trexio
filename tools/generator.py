#!/usr/bin/env python3
from generator_tools import *

config_file = 'trex.json'
trex_config = read_json(config_file)

print('Metadata I/O currently not supported')
# TODO, for now remove metadata-related stuff
del trex_config['metadata']
# for now remove rdm because it is hardcoded
del trex_config['rdm']
# TODO, for now remove char-related stuff
print('Strings I/O currently not supported')

# ------------------ REDO -------------------
group_dict = get_group_dict(trex_config)
group_list = [item for item in group_dict.keys()]

dim_dict = get_dim_dict(trex_config)

datasets = get_dset_dict(trex_config)

numbers = get_num_dict(trex_config)

dset_per_group = get_dset_per_group(trex_config, datasets)

num_per_group = get_num_per_group(trex_config, numbers)

num_detailed = {}
for num in num_per_group.keys():
    tmp_dict = {}
    tmp_dict['group'] = num_per_group[num]
    tmp_dict['group_num'] = num
    num_detailed[num] = tmp_dict

datasets_nostr, datasets_str = split_dset_dict(datasets)
# ------------------ REDO -------------------

source = ['front', 'text', 'hdf5']
# build helper dictionaries with paths and source files per source directory 
template_paths = get_template_paths(source)
source_files = get_source_files(template_paths)
# build helper dictionaries with templated files
files_todo = get_files_todo(source_files)

# populate files with iterative scheme, i.e. for unique functions
for fname in files_todo['auxiliary']:
    iterative_populate_file(fname, template_paths, datasets, numbers, group_dict)

# populate has/read/write_num functions with recursive scheme
for fname in files_todo['num']:
    recursive_populate_file(fname, template_paths, num_detailed)

# populate has/read/write_dset functions with recursive scheme 
for fname in files_todo['dset']:
    recursive_populate_file(fname, template_paths, datasets_nostr)

# populate group-related functions with mixed (iterative+recursive) scheme [text backend]
for fname in files_todo['group']:
    special_populate_text_group(fname, template_paths, group_list, datasets_nostr, num_detailed)
