#!/usr/bin/env python3
from generator_tools import *

# --------------------- GET CONFIGURATION FROM THE TREX.JSON ---------------- #
config_file = 'trex.json'
trex_config = read_json(config_file)
# --------------------------------------------------------------------------- #

# -------------------- GET ATTRIBUTES FROM THE CONFIGURATION ---------------- #
group_dict = get_group_dict(trex_config)
detailed_nums = get_detailed_num_dict(trex_config)
detailed_strs = get_detailed_str_dict(trex_config)
# helper dictionaries that contain names of groups, nums or dsets as keys
dsets = get_dset_dict(trex_config)
detailed_dsets_nostr, detailed_dsets_str, detailed_dsets_sparse = split_dset_dict_detailed(dsets)
detailed_dsets = detailed_dsets_nostr.copy()
detailed_dsets.update(detailed_dsets_str)
# build a big dictionary with all pre-processed data
detailed_all = {
    'datasets' : dict(detailed_dsets_nostr, **detailed_dsets_str, **detailed_dsets_sparse),
    'groups'   : group_dict,
    'numbers'  : detailed_nums,
    'strings'  : detailed_strs
}
# consistency check for dimensioning variables
check_dim_consistency(detailed_nums, dsets)
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
    iterative_populate_file(fname, template_paths, detailed_all)

# populate has/read/write_num functions with recursive scheme
for fname in files_todo['attr_num']:
    recursive_populate_file(fname, template_paths, detailed_nums)

# populate has/read/write_str functions with recursive scheme
for fname in files_todo['attr_str']:
    recursive_populate_file(fname, template_paths, detailed_strs)

# populate has/read/write_dset (numerical) functions with recursive scheme
for fname in files_todo['dset_data']:
    recursive_populate_file(fname, template_paths, detailed_dsets_nostr)

# populate has/read/write_dset (strings) functions with recursive scheme
for fname in files_todo['dset_str']:
    recursive_populate_file(fname, template_paths, detailed_dsets_str)

# populate has/read/write_dset (sparse) functions with recursive scheme
for fname in files_todo['dset_sparse']:
    recursive_populate_file(fname, template_paths, detailed_dsets_sparse)

# populate group-related functions with mixed scheme
for fname in files_todo['group']:
    # recursive scheme for delete_group functions
    if 'delete' in fname or 'has' in fname:
        recursive_populate_file(fname, template_paths, group_dict)
    # mixed (iterative+recursive) scheme [text backend]
    else:
        special_populate_text_group(fname, template_paths, group_dict, detailed_dsets, detailed_nums, detailed_strs)

# --------------------------------------------------------------------------- #
