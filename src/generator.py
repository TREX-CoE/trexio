import json

from os import listdir, scandir, remove
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
    #if k == 'nucleus': 
        config[k] = v

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

# TODO, for now remove char-related stuff
print('Strings I/O currently not supported')

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


#put also dimensioning variables in numbers
numbers.update(dim_variables)

templ_path_text = join(fileDir,'templates_text')
templ_path_hdf5 = join(fileDir,'templates_hdf5')
templ_path_front = join(fileDir,'templates_front')


files_exclude = ['prefix_hdf5.c', 'prefix_hdf5.h', 'suffix_hdf5.h', 
                 'prefix_text.c', 'prefix_text.h', 'suffix_text.h', 
                 'prefix_front.c', 'prefix_front.h', 'suffix_front.h', 
                 'prefix_fortran.f90', 'suffix_fortran.f90',
                 'prefix_s_front.h', 'suffix_s_front.h',
                 'templator_front.org', 'templator_hdf5.org', 'templator_text.org']

files_text = [f for f in listdir(templ_path_text) if isfile(join(templ_path_text, f)) and f not in files_exclude]
files_hdf5 = [f for f in listdir(templ_path_hdf5) if isfile(join(templ_path_hdf5, f)) and f not in files_exclude]
files_front = [f for f in listdir(templ_path_front) if isfile(join(templ_path_front, f)) and f not in files_exclude]

files = files_text + files_hdf5 + files_front

files_funcs = [f for f in files if 'read_' in f or 'write_' in f or 'flush_' in f or 'free_' in f or 'rw_' in f ]
files_funcs_dsets = [f for f in files_funcs if 'dset' in f]
files_funcs_nums  = [f for f in files_funcs if 'num' in f]
files_funcs_groups = [f for f in files_funcs if 'group' in f]
files_auxil = [f for f in files if not ('read_' in f or 'write_' in f or 'rw_' in f)]

files_funcs_groups.append('struct_text_group_dset.h')

# build files with functions for text groups
for fname in files_funcs_groups:
    fname_new = join('populated',f'pop_{fname}')
    if '_text' in fname:
        templ_path = templ_path_text

    groups_done = []
    for group in config.keys():

        grname = group.split('_')[0]
        if grname in groups_done:
            continue
        else:
            groups_done.append(grname)

        subloop = False
        do_dset = False
        do_num = False
        loop_body = ''
        with open(join(templ_path,fname), 'r') as f_in :
            with open(join(templ_path,fname_new), 'a') as f_out :
                for line in f_in :
                    
                    if 'END REPEAT' in line:

                        if do_dset:
                            for dset,params in datasets_nostr.items():                           
                                dset_grname = dset.split('_')[0]
                                if dset_grname != grname:
                                    continue         
                                                        
                                templine1 = loop_body.replace('$group_dset$', dset)
                                templine2 = templine1.replace('$group$', grname)  

                                templine1 = templine2.replace('$group_dset_dtype$', params['dtype'])
                                templine2 = templine1

                                if params['dtype'] == 'double':
                                    std_dtype = 'lf'
                                elif params['dtype'] == 'int64_t':
                                    std_dtype = 'ld'

                                templine1 = templine2.replace('$group_dset_std_dtype$', std_dtype)
                                templine2 = templine1

                                f_out.write(templine2)
                        elif do_num:
                            #for dim in dim_variables.keys():
                            for dim in numbers.keys():

                                num_grname = dim.split('_')[0]
                                if num_grname != grname:
                                    continue

                                templine1 = loop_body.replace('$group_num$', dim)
                                templine2 = templine1.replace('$group$', grname)                            
                                f_out.write(templine2)     
                        else:
                            print('fishy')
                    
                        loop_body = ''
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
                            
                            dset_grname = dset.split('_')[0]
                            if dset_grname != grname:
                                continue

                            templine1 = line.replace('$group_dset$', dset)
                            templine2 = templine1

                            templine1 = templine2.replace('$group_dset_dtype$', params['dtype'])
                            templine2 = templine1

                            templine1 = templine2.replace('$group$', grname)
                            templine2 = templine1.replace('$GROUP$', grname.upper())
                            
                            f_out.write(templine2)   
                    elif '$group_num' in line and not subloop:
                        #for dim in dim_variables.keys():
                        for dim in numbers.keys():
                            num_grname = dim.split('_')[0]
                            if num_grname != grname:
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


# build files with functions
for fname in files_funcs_dsets:
    fname_new = join('populated',f'pop_{fname}')
    if '_hdf5' in fname:
        templ_path = templ_path_hdf5
    if '_front' in fname:
        templ_path = templ_path_front
    if '_text' in fname:
        templ_path = templ_path_text

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
                                    if '_read' in templine2 and 'hdf5' in fname:
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
                            f_dtype = 'real(8)'
                        elif params['dtype'] == 'int64_t':
                            h5_dtype = 'long'
                            f_dtype = 'integer(8)'

                        templine1 = templine2.replace('$group_dset_h5_dtype$', h5_dtype)
                        templine2 = templine1.replace('$group_dset_h5_dtype$'.upper(), h5_dtype.upper())

                        templine1 = templine2.replace('$group_dset_f_dtype$', f_dtype)
                        templine2 = templine1.replace('$group_dset_f_dtype$'.upper(), f_dtype.upper())

                        templine1 = templine2.replace('$group_dset_rank$', str(params['rank']))
                        templine2 = templine1

                        templine1 = templine2.replace('$group_dset_dim_list$', params['dim_list'])
                        templine2 = templine1

                        templine1 = templine2.replace('$group$', grname)
                        templine2 = templine1.replace('$GROUP$', grname.upper())
                            
                        f_out.write(templine2)                
                    else:        
                        f_out.write(line)

# build files with functions
for fname in files_funcs_nums:
    fname_new = join('populated',f'pop_{fname}')
    if '_hdf5' in fname:
        templ_path = templ_path_hdf5
    if '_front' in fname:
        templ_path = templ_path_front
    if '_text' in fname:
        templ_path = templ_path_text
        
    for dim in dim_variables.keys():
    #for dim in numbers.keys():
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

# build files with $group$ and $group$-based
for fname in ['def_hdf5.c', 'basic_hdf5.c', 'basic_text_group.c', 
              'struct_hdf5.h', 'struct_text_group.h'] :
    fname_new = join('populated',f'pop_{fname}')
    if '_hdf5' in fname:
        templ_path = templ_path_hdf5
    if '_front' in fname:
        templ_path = templ_path_front
    if '_text' in fname:
        templ_path = templ_path_text

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
                    #for num in numbers.keys():
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


