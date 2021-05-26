from os.path import join

def special_populate_text_group(fname: str, paths: dict, group_list: list, detailed_dset: dict, detailed_numbers: dict):

    fname_new = join('populated',f'pop_{fname}')
    templ_path = get_template_path(fname, paths)

    triggers = ['group_dset_dtype', 'group_dset_std_dtype_out', 'group_dset_std_dtype_in',
                'group_dset', 'group_num', 'group']

    for group in group_list:

        with open(join(templ_path,fname), 'r') as f_in :
            with open(join(templ_path,fname_new), 'a') as f_out :

                subloop_dset = False
                subloop_num = False
                loop_body = ''
                dset_allocated = []

                for line in f_in :

                    if 'START REPEAT GROUP_DSET' in line:
                        subloop_dset = True
                        continue
                    elif 'START REPEAT GROUP_NUM' in line:
                        subloop_num = True
                        continue
                    
                    if 'END REPEAT GROUP_DSET' in line:

                        for dset in detailed_dset.keys():
                            if group != detailed_dset[dset]['group']: 
                                continue

                            dset_allocated.append(dset)

                            if 'FREE($group$->$group_dset$)' in loop_body:
                                tmp_string = ''
                                for dset_alloc in dset_allocated:
                                    tmp_string += f'FREE({group}->{dset_alloc});\n        '

                                tmp_body = loop_body.replace('FREE($group$->$group_dset$);',tmp_string)

                                populated_body = recursive_replace_line(tmp_body, triggers, detailed_dset[dset])
                                f_out.write(populated_body)
                            else:
                                save_body = loop_body
                                populated_body = recursive_replace_line(save_body, triggers, detailed_dset[dset])
                                f_out.write(populated_body)

                        subloop_dset = False
                        loop_body = ''
                        dset_allocated = []
                        continue

                    elif 'END REPEAT GROUP_NUM' in line:
                        for dim in detailed_numbers.keys():
                            if group != detailed_numbers[dim]['group']: 
                                continue

                            save_body = loop_body
                            populated_body = recursive_replace_line(save_body, triggers, detailed_numbers[dim])
                            f_out.write(populated_body)

                        subloop_num = False
                        loop_body = ''
                        continue

                    if not subloop_num and not subloop_dset:
                        # NORMAL CASE WITHOUT SUBLOOPS 
                        if '$group_dset' in line:
                            for dset in detailed_dset.keys():
                                if group != detailed_dset[dset]['group']: 
                                    continue
                                populated_line = recursive_replace_line(line, triggers, detailed_dset[dset])
                                f_out.write(populated_line)
                        elif '$group_num$' in line:
                            for dim in detailed_numbers.keys():
                                if group != detailed_numbers[dim]['group']: 
                                    continue
                                populated_line = recursive_replace_line(line, triggers, detailed_numbers[dim])
                                f_out.write(populated_line)
                        elif '$group$' in line:
                            populated_line = line.replace('$group$', group)
                            f_out.write(populated_line)
                        else:
                            f_out.write(line)
                    else:
                        if subloop_dset or subloop_num:
                            loop_body += line



def recursive_populate_file(fname: str, paths: dict, detailed_source: dict):

    fname_new = join('populated',f'pop_{fname}')
    templ_path = get_template_path(fname, paths)

    triggers = ['group_dset_dtype', 'group_dset_h5_dtype', 'default_prec',
                'group_dset_f_dtype_default', 'group_dset_f_dtype_double', 'group_dset_f_dtype_single', 
                'group_dset_dtype_default', 'group_dset_dtype_double', 'group_dset_dtype_single', 
                'group_dset_rank', 'group_dset_dim_list', 'group_dset_f_dims',
                'group_dset', 'group_num', 'group']

    for item in detailed_source.keys():
        with open(join(templ_path,fname), 'r') as f_in :
            with open(join(templ_path,fname_new), 'a') as f_out :
                num_written = []
                for line in f_in :
                        # special case to add error handling for read/write of dimensioning variables
                        if '$group_dset_dim$' in line:
                            rc_line = 'if (rc != TREXIO_SUCCESS) return rc;\n'
                            indentlevel = len(line) - len(line.lstrip())
                            for dim in detailed_source[item]['dims']:
                                if not dim.isdigit() and not dim in num_written:
                                    num_written.append(dim)
                                    templine = line.replace('$group_dset_dim$', dim)
                                    if '_read' in templine: 
                                            line_toadd = indentlevel*" " + rc_line
                                            templine += line_toadd

                                    f_out.write(templine)
                            num_written = []
                            continue
                        # general case of recursive replacement of inline triggers 
                        else:
                            populated_line = recursive_replace_line(line, triggers, detailed_source[item])
                            f_out.write(populated_line)


def recursive_replace_line (input_line: str, triggers: list, source: dict) -> str:
    
    is_triggered = False
    output_line = input_line
    
    if '$' in input_line:
        for case in triggers:
            test_case = f'${case}$'
            if test_case in input_line:
                output_line = input_line.replace(test_case, source[case])
                is_triggered = True
                break
            elif test_case.upper() in input_line:
                output_line = input_line.replace(test_case.upper(), source[case].upper())
                is_triggered = True
                break

        if is_triggered:
            return recursive_replace_line(output_line, triggers, source)
        else:
            print(output_line)
            raise ValueError('Recursion went wrong, not all cases considered')
        
    return output_line



def iterative_populate_file (filename: str, paths: dict, datasets: dict, numbers: dict, groups: dict):

    add_trigger = 'rc = trexio_text_free_$group$'
    triggers = [add_trigger, '$group_dset$', '$group_num$', '$group$']

    templ_path = get_template_path(filename, paths)
    filename_out = join('populated',f'pop_{filename}')
# Note: it is important that special conditions like add_trigger above will be checked before standard triggers
# that contain only basic $-ed variable (like $group$). Otherwise, the standard triggers will be removed 
# from the template and the special condition will never be met.
    with open(join(templ_path,filename), 'r') as f_in :
        with open(join(templ_path,filename_out), 'a') as f_out :
            for line in f_in :
                id = check_triggers(line, triggers)
                if id == 0:
                    # special case for proper error handling when deallocting text groups
                    error_handler = '  if (rc != TREXIO_SUCCESS) return rc;\n'
                    populated_line = iterative_replace_str(line, triggers[3], groups, add_line=error_handler)
                    f_out.write(populated_line)
                elif id == 1:
                    populated_line = iterative_replace_str(line, triggers[id], datasets, None)
                    f_out.write(populated_line)
                elif id == 2:
                    populated_line = iterative_replace_str(line, triggers[id], numbers, None)
                    f_out.write(populated_line)
                elif id == 3:
                    populated_line = iterative_replace_str(line, triggers[id], groups, None)
                    f_out.write(populated_line)
                else:
                    f_out.write(line)


def check_triggers (input_line: str, triggers: list) -> int:

    out_id = -1
    for id,trig in enumerate(triggers):
        if trig in input_line or trig.upper() in input_line:
            out_id = id
            return out_id
        
    return out_id


def iterative_replace_str (input_line: str, case: str, source: dict, add_line: str) -> str:
    output_block = ""
    for item in source.keys():
        templine1 = input_line.replace(case.upper(), item.upper())
        templine2 = templine1.replace(case, item)
        if add_line != None:
            templine2 += add_line

        output_block += templine2

    return output_block


def recursive_replace_str (input_str: str) -> str:
    return input_str


def get_template_path (filename: str, path_dict: dict) -> str:
    for dir_type in ['front', 'hdf5', 'text']:
        if dir_type in filename:
            path = path_dict[dir_type]
            return path
        
    raise ValueError('Filename should contain one of the keywords')


def get_group_dict (configuration: dict) -> dict:
    group_dict = {}
    for k in configuration.keys():
        group_dict[k] = 0

    return group_dict


def get_dset_per_group (configuration: dict, datasets: dict) -> dict:
    
    output = {}
    for k1,v1 in configuration.items():
        tmp_list = []
        for k2,v2 in v1.items():
            if len(v2[1]) != 0:
                tmp_dset = f'{k1}_{k2}'
                tmp_list.append(tmp_dset)

        output[k1] = tmp_list

    return output


def get_num_per_group (configuration: dict, numbers: dict) -> dict:
    
    output = {}
    for k1,v1 in configuration.items():
        # the code below return dictionary with num names as keys and corresponding groups as values
        for k2,v2 in v1.items():
            if len(v2[1]) == 0 and v2[0] == 'int':
                output[f'{k1}_{k2}'] = k1
        
        # the code below returns dictionary with groups as keys and values as lists of corresponding num names
        #tmp_list = []
        #for k2,v2 in v1.items():
        #    if len(v2[1]) == 0 and v2[0] == 'int':
        #        tmp_dset = f'{k1}_{k2}'
        #        tmp_list.append(tmp_dset)
        #output[k1] = tmp_list

    return output

def get_dim_dict (configuration: dict) -> dict:
    ''' 
    Returns the dictionary of dimensioning variables. 
    Keys are names, values are zeros.
    The dimensioning variable is the `num`-suffixed variable that appears as a dimension of at least one array.

            Parameters:
                    configuration (dict) : configuration from `trex.json`

            Returns:
                    dim_dict (dict) : dictionary of dimensioning variables
    '''
    dim_dict = {}
    for v1 in configuration.values():
        for v2 in v1.values():
            for dim in v2[1]:
                if not dim.isdigit():
                    tmp_dim = dim.replace('.','_')
                    dim_dict[tmp_dim] = 0

    return dim_dict


def get_dset_dict (configuration: dict) -> dict:
    ''' 
    Returns the dictionary of datasets. 
    Keys are names, values are lists containing datatype and list of dimensions.

            Parameters:
                    configuration (dict) : configuration from `trex.json`

            Returns:
                    dset_dict (dict) : dictionary of datasets
    '''
    dset_dict = {}
    for k1,v1 in configuration.items():
        for k2,v2 in v1.items():
            if len(v2[1]) != 0:
                tmp_dset = f'{k1}_{k2}'
                dset_dict[tmp_dset] = v2
                # append a group name for postprocessing
                dset_dict[tmp_dset].append(k1)

    return dset_dict


def get_num_dict (configuration: dict) -> dict:
    ''' 
    Returns the dictionary of all `num`-suffixed variables.
    Keys are names, values are datatypes (int). 

            Parameters:
                    configuration (dict) : configuration from `trex.json`

            Returns:
                    num_dict (dict) : dictionary of num-suffixed variables
    '''
    num_dict = {}
    for k1,v1 in configuration.items():
        for k2,v2 in v1.items():
            if len(v2[1]) == 0:
                tmp_num = f'{k1}_{k2}'
                if 'str' not in v2[0]:
                    num_dict[tmp_num] = v2[0]

    return num_dict

def split_dset_dict (datasets: dict) -> tuple:
    
    dset_numeric_dict = {}
    dset_string_dict = {}

    for k,v in datasets.items():
        # create a temp dictionary
        tmp_dict = {}
        # transform datatypes to the more C-like analogues
        if v[0] == 'float':
            datatype = 'double'
            group_dset_h5_dtype       = 'double'
            group_dset_f_dtype_default= 'real(8)'
            group_dset_f_dtype_double = 'real(8)'
            group_dset_f_dtype_single = 'real(4)'
            group_dset_dtype_default= 'double'
            group_dset_dtype_double = 'double'
            group_dset_dtype_single = 'float'
            default_prec   = '64'
            group_dset_std_dtype_out = '24.16e'
            group_dset_std_dtype_in = 'lf'
        elif v[0] == 'int':
            datatype = 'int64_t'
            group_dset_h5_dtype = 'int64'
            group_dset_f_dtype_default= 'integer(4)'
            group_dset_f_dtype_double = 'integer(8)'
            group_dset_f_dtype_single = 'integer(4)'
            group_dset_dtype_default= 'int32_t'
            group_dset_dtype_double = 'int64_t'
            group_dset_dtype_single = 'int32_t'
            default_prec   = '32'
            group_dset_std_dtype_out = '" PRId64 "'
            group_dset_std_dtype_in  = '" SCNd64 "' 

        elif v[0] == 'str':
            datatype = 'string'
        
        # add the dset name for templates
        tmp_dict['group_dset'] = k
        # add the datatypes for templates
        tmp_dict['dtype'] = datatype
        tmp_dict['group_dset_dtype'] = datatype
        tmp_dict['group_dset_h5_dtype'] = group_dset_h5_dtype 
        tmp_dict['group_dset_f_dtype_default'] = group_dset_f_dtype_default
        tmp_dict['group_dset_f_dtype_double'] = group_dset_f_dtype_double
        tmp_dict['group_dset_f_dtype_single'] = group_dset_f_dtype_single
        tmp_dict['group_dset_dtype_default'] = group_dset_dtype_default
        tmp_dict['group_dset_dtype_double'] = group_dset_dtype_double
        tmp_dict['group_dset_dtype_single'] = group_dset_dtype_single
        tmp_dict['default_prec'] = default_prec
        tmp_dict['group_dset_std_dtype_in'] = group_dset_std_dtype_in
        tmp_dict['group_dset_std_dtype_out'] = group_dset_std_dtype_out
        # add the rank
        tmp_dict['rank'] = len(v[1])
        tmp_dict['group_dset_rank'] = str(tmp_dict['rank'])
        # add the list of dimensions
        tmp_dict['dims'] = [dim.replace('.','_') for dim in v[1]]
        # build a list of dimensions to be inserted in the dims array initialization, e.g. {ao_num, ao_num}
        dim_list = tmp_dict['dims'][0]
        if tmp_dict['rank'] > 1:
            for i in range(1, tmp_dict['rank']):
                dim_toadd = tmp_dict['dims'][i]
                dim_list += f', {dim_toadd}'
        
        tmp_dict['group_dset_dim_list'] = dim_list

        if tmp_dict['rank'] == 0:
            dim_f_list = ""
        else:
            dim_f_list = "(*)"
        tmp_dict['group_dset_f_dims'] = dim_f_list

        # add group name as a key-value pair to the dset dict
        tmp_dict['group'] = v[2]

        # split datasets in numerical and string 
        if (datatype == 'string'):
            dset_string_dict[k] = tmp_dict
        else:
            dset_numeric_dict[k] = tmp_dict

    return (dset_numeric_dict, dset_string_dict)
