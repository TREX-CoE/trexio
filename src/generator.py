import json

from os import listdir
from os.path import isfile, join, dirname, abspath

fileDir = dirname(abspath(__file__))
parentDir = dirname(fileDir)

with open(join(parentDir,'trex.json'), 'r') as f:
    config0 = json.load(f)

print('Metadata I/O currently not supported')
# TODO, for now remove metadata-related stuff
del config0['metadata']

config = {}
for k,v in config0.items():
    if k == 'nucleus' or k == 'ecp':
        config[k] = v

#print(config)

groups = [group for group in config.keys()]

dim_variables = {}
dim_list = []
dim_dict = {}
for k1,v1 in config.items():
    grname = k1
    for v2 in v1.values():
        for dim in v2[1]:
            if not dim.isdigit():
                tmp = dim.replace('.','_')
                dim_variables[tmp] = 0
                if dim not in dim_list: 
                    dim_list.append(tmp)
                    
                dim_dict[grname] = dim_list
                dim_list = []

#print(dim_variables)
#print(dim_dict)

datasets = {}
numbers = {}
for k1,v1 in config.items():
    for k2,v2 in v1.items():
        if len(v2[1]) > 0:
            datasets[f'{k1}_{k2}'] = v2
        else:
            var_name = f'{k1}_{k2}'
            if var_name not in dim_variables.keys():
                numbers[var_name] = v2[0]

print('Strings I/O currently not supported')
# TODO, for now remove char-related stuff
datasets_nostr = {}
for k,v in datasets.items():
    tmp_dict = {}
    if 'char' not in v[0]:
        if v[0] == 'float':
            datatype = 'double'
        elif v[0] == 'int':
            datatype = 'int64_t'
        tmp_dict['dtype'] = datatype
        tmp_dict['dims'] = [dim.replace('.','_') for dim in v[1]] 
        tmp_dict['rank'] = len(v[1]) 
        dim_str = tmp_dict['dims'][0]
        if tmp_dict['rank'] > 1:
            for i in range(1, tmp_dict['rank']):
                dim_toadd = tmp_dict['dims'][i]
                dim_str += f', {dim_toadd}'
        tmp_dict['dim_list'] = dim_str 
        datasets_nostr[k] = tmp_dict

print(datasets_nostr['nucleus_coord'])
#print(numbers)

templ_path_hdf5 = join(fileDir,'templates_hdf5')
templ_path_front = join(fileDir,'templates_front')

files_exclude = ['prefix_hdf5.c', 'prefix_hdf5.h', 'suffix_hdf5.h', 
                 'prefix_front.c', 'prefix_front.h', 'suffix_front.h', 
                 'prefix_s_front.h', 'suffix_s_front.h',
                 'templator_front.org', 'templator_hdf5.org']

files_hdf5 = [f for f in listdir(templ_path_hdf5) if isfile(join(templ_path_hdf5, f)) and f not in files_exclude]
files_front = [f for f in listdir(templ_path_front) if isfile(join(templ_path_front, f)) and f not in files_exclude]

files = files_hdf5 + files_front

files_funcs = [f for f in files if 'read_' in f or 'write_' in f or 'rw_' in f ]
files_funcs_dsets = [f for f in files_funcs if 'dset' in f]
files_funcs_nums  = [f for f in files_funcs if 'num' in f]

files_auxil = [f for f in files if not ('read_' in f or 'write_' in f or 'rw_' in f)]

# build files with functions
for fname in files_funcs_nums:
    fname_new = join('populated',f'pop_{fname}')
    if '_hdf5' in fname:
        templ_path = templ_path_hdf5
    if '_front' in fname:
        templ_path = templ_path_front
        
    for dim in dim_variables.keys():

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

# build files with functions
for fname in files_funcs_dsets:
    fname_new = join('populated',f'pop_{fname}')
    if '_hdf5' in fname:
        templ_path = templ_path_hdf5
    if '_front' in fname:
        templ_path = templ_path_front
    for dset,params in datasets_nostr.items():

        grname = dset.split('_')[0]
        with open(join(templ_path,fname), 'r') as f_in :
            with open(join(templ_path,fname_new), 'a') as f_out :
                for line in f_in :
                    if '$' in line:

                        if '$group_dset_dim$' in line:
                            rc_line = '  if (rc != TREXIO_SUCCESS) return rc;\n'
                            for dim in params['dims']:
                                if not dim.isdigit():
                                    templine1 = line.replace('$group_dset_dim$', dim)
                                    templine2 = templine1
                                    if '_read' in templine2:
                                            templine1 = rc_line
                                            templine2 += templine1   

                                    f_out.write(templine2)
                            continue

                        templine1 = line.replace('$GROUP$_$GROUP_DSET$', dset.upper())
                        templine2 = templine1.replace('$group$_$group_dset$', dset)

                        templine1 = templine2.replace('$group_dset$', dset)
                        templine2 = templine1

                        templine1 = templine2.replace('$group_dset_dtype$', params['dtype'])
                        templine2 = templine1

                        if params['dtype'] == 'double':
                            h5_dtype = 'double'
                        elif params['dtype'] == 'int64_t':
                            h5_dtype = 'long'

                        templine1 = templine2.replace('$group_dset_h5_dtype$', h5_dtype)
                        templine2 = templine1.replace('$group_dset_h5_dtype$'.upper(), h5_dtype.upper())

                        templine1 = templine2.replace('$group_dset_rank$', str(params['rank']))
                        templine2 = templine1

                        templine1 = templine2.replace('$group_dset_dim_list$', params['dim_list'])
                        templine2 = templine1

                        templine1 = templine2.replace('$group$', grname)
                        templine2 = templine1.replace('$GROUP$', grname.upper())
                            
                        f_out.write(templine2)                
                    else:        
                        f_out.write(line)

# build files with $group$ and $group$-based
for fname in ['def_hdf5.c', 'basic_hdf5.c', 'struct_hdf5.h'] :
    fname_new = join('populated',f'pop_{fname}')
    if '_hdf5' in fname:
        templ_path = templ_path_hdf5
    if '_front' in fname:
        templ_path = templ_path_front

    with open(join(templ_path,fname), 'r') as f_in :
        with open(join(templ_path,fname_new), 'a') as f_out :
            for line in f_in :
                if '$group_dset$' in line or '$GROUP_DSET$' in line :
                    for dset in datasets_nostr.keys():
                        templine1 = line.replace('$GROUP$_$GROUP_DSET$', dset.upper())
                        templine2 = templine1.replace('$group_dset$', dset)
                        f_out.write(templine2)
                elif '$group_num$' in line or '$GROUP_NUM$' in line :
                    for num in dim_variables.keys():
                        templine1 = line.replace('$GROUP_NUM$', num.upper())
                        templine2 = templine1.replace('$group_num$', num)
                        f_out.write(templine2)                
                elif '$group$' in line or '$GROUP$' in line :
                    for grname in config.keys():
                        templine1 = line.replace('$group$', grname)
                        templine2 = templine1.replace('$GROUP$', grname.upper())
                        f_out.write(templine2)                
                else:        
                    f_out.write(line)


