import json

from os import listdir
from os.path import isfile, join

with open('../trex.json', 'r') as f:
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

print(dim_variables)
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
    if 'char' not in v[0]:
        datasets_nostr[k] = v

#print(datasets_nostr)
#print(numbers)

#print(attributes)
#print(groups)

#file_list = ['temp_trexio_hdf5.c']
file_list = []

temp_path = 'templates_hdf5'

files_exclude = ['prefix_hdf5.c', 'prefix_hdf5.h', 'suffix_hdf5.h', 'templator_hdf5.org']

files = [f for f in listdir(temp_path) if isfile(join(temp_path, f)) and f not in files_exclude]
#print(files)

files_funcs = [f for f in files if 'read_' in f or 'write_' in f or 'rw_' in f ]
files_auxil = [f for f in files if not ('read_' in f or 'write_' in f or 'rw_' in f)]
print(files_auxil)

# build files with $group$ only
for fname in ['basic_hdf5.c', 'struct_hdf5.h']:
    fname_new = 'populated/pop_' + fname
    with open(f'{temp_path}/{fname}', 'r') as f_in:
        with open(f'{temp_path}/{fname_new}', 'w') as f_out:
            for line in f_in:
                if '$group$' in line or '$GROUP$' in line:
                    for grname in config.keys():
                        templine1 = line.replace('$group$', grname)
                        templine2 = templine1.replace('$GROUP$', grname.upper())
                        #templine1 = templine2.replace('$GROUP_NUM$', dim.upper())
                        #templine2 = templine1.replace('$group_num$', dim)
                        #templine1 = templine2.replace('$GROUP_DSET$', '')
                        #templine2 = templine1.replace('$group_dset$', '')

                        f_out.write(templine2)
                else:        
                    f_out.write(line)

# build files with $group$ and $group$-based
for fname in ['def_hdf5.c'] :
    fname_new = 'populated/pop_' + fname
    with open(f'{temp_path}/{fname}', 'r') as f_in :
        with open(f'{temp_path}/{fname_new}', 'w') as f_out :
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


