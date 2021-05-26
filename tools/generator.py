#!/usr/bin/env python3
from generator_tools import *

# --------------------- GET CONFIGURATION FROM THE TREX.JSON ---------------- #
config_file = 'trex.json'
trex_config = read_json(config_file)
# --------------------------------------------------------------------------- #

# -------------------------------- [WIP] ------------------------------------ #
print('Metadata I/O currently not supported')
# TODO, for now remove metadata-related stuff
del trex_config['metadata']
# for now remove rdm from config because it functions are hardcoded
del trex_config['rdm']
# TODO, for now remove char-related stuff
print('Strings I/O currently not supported')
# --------------------------------------------------------------------------- #

# -------------------- GET ATTRIBUTES FROM THE CONFIGURATION ---------------- #
group_dict = get_group_dict(trex_config)
detailed_num = get_detailed_num_dict(trex_config)
# helper dictionaries contain group, num or dset names as keys
datasets = get_dset_dict(trex_config)
detailed_dset_nostr, detailed_dset_str = split_dset_dict_detailed(datasets)
# --------------------------------------------------------------------------- #

# -------------------- GET TEMPLATED FILES TO BE POPULATED ------------------ #
source = ['front', 'text', 'hdf5']
# build helper dictionaries with paths per source directory 
template_paths = get_template_paths(source)
# build helper dictionaries with source files per source directory 
source_files = get_source_files(template_paths)
# build helper dictionaries with templated files
files_todo = get_files_todo(source_files)
# --------------------------------------------------------------------------- #

# ----------------------- POPULATE TEMPLATED FILES -------------------------- #

# populate files with iterative scheme, i.e. for unique functions
for fname in files_todo['auxiliary']:
    iterative_populate_file(fname, template_paths, group_dict, detailed_dset_nostr, detailed_num)

# populate has/read/write_num functions with recursive scheme
for fname in files_todo['num']:
    recursive_populate_file(fname, template_paths, detailed_num)

# populate has/read/write_dset functions with recursive scheme 
for fname in files_todo['dset']:
    recursive_populate_file(fname, template_paths, detailed_dset_nostr)

# populate group-related functions with mixed (iterative+recursive) scheme [text backend]
for fname in files_todo['group']:
    special_populate_text_group(fname, template_paths, group_dict, detailed_dset_nostr, detailed_num)

# --------------------------------------------------------------------------- #
