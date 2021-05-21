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

dim_dict = get_dim_dict(config)
datasets = get_dset_dict(config)
numbers = get_num_dict(config)

datasets_nostr, datasets_str = split_dset_dict(datasets)

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
# files that correspond to todo1 group (e.g. only groups have to be populated)
files_auxil = ['def_hdf5.c', 'basic_hdf5.c', 'basic_text_group.c', 'struct_hdf5.h', 'struct_text_group.h'] 


# build files with $group$ and $group$-based
for fname in files_auxil:
    fname_new = join('populated',f'pop_{fname}')

    templ_path = get_template_path(fname, path_dict)

    with open(join(templ_path,fname), 'r') as f_in :
        with open(join(templ_path,fname_new), 'a') as f_out :
            for line in f_in :
                if '$group_dset$' in line or '$GROUP_DSET$' in line :
                    for dset in datasets.keys():
                        templine1 = line.replace('$GROUP_DSET$', dset.upper())
                        templine2 = templine1.replace('$group_dset$', dset)
                        f_out.write(templine2)
                elif '$group_num$' in line or '$GROUP_NUM$' in line :
                    for num in numbers.keys():
                        templine1 = line.replace('$GROUP_NUM$', num.upper())
                        templine2 = templine1.replace('$group_num$', num)
                        f_out.write(templine2)
                # special case for proper error handling when deallocting text groups
                elif 'rc = trexio_text_free_$group$' in line:
                    for grname in config.keys():
                        templine1 = line.replace('$group$', grname)
                        templine2 = templine1 + '  if (rc != TREXIO_SUCCESS) return rc;\n'
                        f_out.write(templine2)
                elif '$group$' in line or '$GROUP$' in line :
                    for grname in config.keys():
                        templine1 = line.replace('$group$', grname)
                        templine2 = templine1.replace('$GROUP$', grname.upper())
                        f_out.write(templine2)
                else:
                    f_out.write(line)

# populate has/read/write_num functions 
for fname in files_funcs_nums:
    fname_new = join('populated',f'pop_{fname}')

    templ_path = get_template_path(fname, path_dict)

    for dim in numbers.keys():
        grname = dim.split('_')[0]
        with open(join(templ_path,fname), 'r') as f_in :
            with open(join(templ_path,fname_new), 'a') as f_out :
                for line in f_in :
                    if '$' in line:
                        templine1 = line.replace('$GROUP_NUM$', dim.upper())
                        templine2 = templine1.replace('$group_num$', dim)

                        templine1 = templine2.replace('$group$', grname)
                        templine2 = templine1.replace('$GROUP$', grname.upper())

                        f_out.write(templine2)
                    else:
                        f_out.write(line)


# populate has/read/write_dset functions 
for fname in files_funcs_dsets:
    fname_new = join('populated',f'pop_{fname}')

    templ_path = get_template_path(fname, path_dict)

    for dset,params in datasets_nostr.items():

        # the problem was when group name has underscores in it, special case needed!
        for group_tmp in config.keys():
            if group_tmp in dset:
                grname = group_tmp

        with open(join(templ_path,fname), 'r') as f_in :
            with open(join(templ_path,fname_new), 'a') as f_out :
                num_written = []
                for line in f_in :
                    if '$' in line:

                        if '$group_dset_dim$' in line:
                            rc_line = 'if (rc != TREXIO_SUCCESS) return rc;\n'
                            indentlevel = len(line) - len(line.lstrip())
                            for dim in params['dims']:
                                if not dim.isdigit() and not dim in num_written:
                                    num_written.append(dim)
                                    templine1 = line.replace('$group_dset_dim$', dim)
                                    templine2 = templine1
                                    if '_read' in templine2: 
                                            templine1 = indentlevel*" " + rc_line
                                            templine2 += templine1

                                    f_out.write(templine2)
                            num_written = []
                            continue

                        templine1 = line.replace('$GROUP_DSET$', dset.upper())
                        templine2 = templine1.replace('$group_dset$', dset)

                        templine1 = templine2.replace('$group_dset$', dset)
                        templine2 = templine1

                        templine1 = templine2.replace('$group_dset_dtype$', params['dtype'])
                        templine2 = templine1

                        if params['dtype'] == 'double':
                            h5_dtype       = 'double'
                            f_dtype_default= 'real(8)'
                            f_dtype_double = 'real(8)'
                            f_dtype_single = 'real(4)'
                            c_dtype_default= 'double'
                            c_dtype_double = 'double'
                            c_dtype_single = 'float'
                            default_prec   = '64'

                        elif params['dtype'] == 'int64_t':
                            h5_dtype = 'int64'
                            f_dtype_default= 'integer(4)'
                            f_dtype_double = 'integer(8)'
                            f_dtype_single = 'integer(4)'
                            c_dtype_default= 'int32_t'
                            c_dtype_double = 'int64_t'
                            c_dtype_single = 'int32_t'
                            default_prec   = '32'

                        templine1 = templine2.replace('$group_dset_dtype_double$', c_dtype_double)
                        templine2 = templine1.replace('$group_dset_dtype_single$', c_dtype_single)

                        templine1 = templine2.replace('$group_dset_h5_dtype$', h5_dtype)
                        templine2 = templine1.replace('$group_dset_h5_dtype$'.upper(), h5_dtype.upper())

                        templine1 = templine2.replace('$group_dset_f_dtype_double$', f_dtype_double)
                        templine2 = templine1.replace('$group_dset_f_dtype_single$', f_dtype_single)

                        templine1 = templine2.replace('$group_dset_f_dtype_default$', f_dtype_default)
                        templine2 = templine1.replace('$group_dset_dtype_default$', c_dtype_default)

                        templine1 = templine2.replace('$default_prec$', default_prec)
                        templine2 = templine1

                        templine1 = templine2.replace('$group_dset_rank$', str(params['rank']))
                        templine2 = templine1

                        templine1 = templine2.replace('$group_dset_dim_list$', params['dim_list'])
                        templine2 = templine1

                        templine1 = templine2.replace('$group$', grname)
                        templine2 = templine1.replace('$GROUP$', grname.upper())

                        if "$group_dset_f_dims$" in templine2:
                            dims = "(" + ",".join([":" for _ in range(params['rank'])]) + ")"
                            if dims == "()":
                              dims = ""
                            else:
                              dims = "(*)"
                            templine1 = templine2.replace("$group_dset_f_dims$", dims)
                            templine2 = templine1

                        f_out.write(templine2)
                    else:
                        f_out.write(line)


# build files with functions for text groups
for fname in files_funcs_groups:
    fname_new = join('populated',f'pop_{fname}')
    if '_text' in fname:
        templ_path = templ_path_text

    groups_done = []
    for group in config.keys():

        grname = group
        if grname in groups_done:
            continue
        else:
            groups_done.append(grname)

        subloop = False
        do_dset = False
        do_num = False
        loop_body = ''
        dset_allocated = []
        with open(join(templ_path,fname), 'r') as f_in :
            with open(join(templ_path,fname_new), 'a') as f_out :
                for line in f_in :

                    if 'END REPEAT' in line:

                        if do_dset:
                            for dset,params in datasets_nostr.items():
                                if grname not in dset: 
                                    continue

                                dset_allocated.append(dset)

                                templine1 = loop_body.replace('$group_dset_dtype$', params['dtype'])
                                templine2 = templine1

                                if 'FREE($group$->$group_dset$)' in loop_body:
                                    tmp_string = ''
                                    for dset_alloc in dset_allocated:
                                        tmp_string += f'FREE({grname}->{dset_alloc});\n        '

                                    templine1 =  templine2.replace('FREE($group$->$group_dset$);',tmp_string)
                                    templine2 = templine1

                                templine1 = templine2.replace('$group_dset$', dset)
                                templine2 = templine1.replace('$group$', grname)

                                if params['dtype'] == 'double':
                                    std_dtype_out = '24.16e'
                                    std_dtype_in = 'lf'
                                elif params['dtype'] == 'int64_t':
                                    std_dtype_out = '" PRId64 "'
                                    std_dtype_in = '" SCNd64 "'

                                templine1 = templine2.replace('$group_dset_std_dtype_out$', std_dtype_out)
                                templine2 = templine1.replace('$group_dset_std_dtype_in$', std_dtype_in)

                                f_out.write(templine2)
                        elif do_num:
                            for dim in numbers.keys():

                                if grname not in dim:
                                    continue

                                templine1 = loop_body.replace('$group_num$', dim)
                                templine2 = templine1.replace('$group$', grname)
                                f_out.write(templine2)
                        else:
                            print('fishy')

                        loop_body = ''
                        dset_allocated = []
                        subloop = False
                        do_dset = False
                        do_num = False
                        continue

                    if subloop:
                        loop_body += line

                    if 'START REPEAT' in line:
                        if 'GROUP_DSET' in line:
                            do_dset = True
                        if 'GROUP_NUM' in line:
                            do_num = True
                        subloop = True

                    if '$group_dset' in line and not subloop:
                        for dset,params in datasets_nostr.items():

                            if grname not in dset:
                                continue

                            templine1 = line.replace('$group_dset$', dset)
                            templine2 = templine1

                            templine1 = templine2.replace('$group_dset_dtype$', params['dtype'])
                            templine2 = templine1

                            templine1 = templine2.replace('$group$', grname)
                            templine2 = templine1.replace('$GROUP$', grname.upper())

                            f_out.write(templine2)
                    elif '$group_num' in line and not subloop:
                        for dim in numbers.keys():
                            if grname not in dim: 
                                continue

                            templine1 = line.replace('$GROUP_NUM$', dim.upper())
                            templine2 = templine1.replace('$group_num$', dim)

                            templine1 = templine2.replace('$group$', grname)
                            templine2 = templine1.replace('$GROUP$', grname.upper())

                            f_out.write(templine2)

                    elif '$group$' in line and not subloop:

                        templine1 = line.replace('$group$', grname)
                        templine2 = templine1.replace('$GROUP$', grname.upper())
                        f_out.write(templine2)

                    elif not subloop:
                        f_out.write(line)