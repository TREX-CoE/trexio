from os import listdir
from os.path import join, dirname, abspath, isfile
from json import load as json_load


def read_json(fname: str) -> dict:
    """ 
    Read configuration from the input `fname` JSON file.

            Parameters:
                    fname (str)     : JSON file name

            Returns:
                    config (dict)   : full configuration dictionary loaded from the input file
    """
    fileDir = dirname(abspath(__file__))
    parentDir = dirname(fileDir)

    with open(join(parentDir,fname), 'r') as f:
        config = json_load(f)

    return config


def get_files_todo(source_files: dict) -> dict:
    """ 
    Build dictionaries of templated files per objective.

            Parameters:
                    source_files (dict) : dictionary with source files per source directory

            Returns:
                    file_todo (dict)    : dictionary with objective title : [list of files] as key-value pairs
    """
    all_files = []
    for key in source_files.keys():
        all_files += source_files[key]

    files_todo = {}       
    #files_todo['all'] = list(filter(lambda x: 'read' in x or 'write' in x or 'has' in x or 'hrw' in x or 'flush' in x or 'free' in x, all_files))
    files_todo['all'] = [f for f in all_files if 'read' in f or 'write' in f or 'has' in f or 'flush' in f or 'free' in f or 'hrw' in f]
    for key in ['dset_data', 'dset_str', 'attr_num', 'attr_str', 'group']:
        files_todo[key] = list(filter(lambda x: key in x, files_todo['all']))

    files_todo['group'].append('struct_text_group_dset.h')
    # files that correspond to iterative population (e.g. the code is repeated within the function body but the function itself is unique)
    files_todo['auxiliary'] = ['def_hdf5.c', 'basic_hdf5.c', 'basic_text_group.c', 'struct_hdf5.h', 'struct_text_group.h'] 

    return files_todo


def get_source_files(paths: dict) -> dict:
    """ 
    Build dictionaries of all files per source directory.

            Parameters:
                    paths (dict)     : dictionary with paths to source directories

            Returns:
                    file_dict (dict) : dictionary with source title : [list of files] as key-value pairs
    """
    file_dict = {}
    for key in paths.keys():
        file_dict[key] = [f for f in listdir(paths[key]) if isfile(join(paths[key], f))]

    return file_dict


def get_template_paths(source: list) -> dict:
    """ 
    Build dictionary of the absolute paths to directory with templates per source.

            Parameters:
                    source (list)    : list of source titles, i.e. ['front', 'text', 'hdf5']

            Returns:
                    path_dict (dict) : dictionary with source title : absolute path as key-value pairs
    """
    fileDir = dirname(abspath(__file__))
    path_dict = {}

    for dir in source:
        path_dict[dir] = join(fileDir,f'templates_{dir}')

    return path_dict


def recursive_populate_file(fname: str, paths: dict, detailed_source: dict) -> None:
    """ 
    Populate files containing basic read/write/has functions.

            Parameters:
                    filename (str)          : template file to be populated
                    paths (dict)            : dictionary of paths per source directory
                    detailed_source (dict)  : dictionary of variables with substitution details (usually either datasets or numbers)

            Returns:
                    None
    """
    fname_new = join('populated',f'pop_{fname}')
    templ_path = get_template_path(fname, paths)

    triggers = ['group_dset_dtype', 'group_dset_py_dtype', 'group_dset_h5_dtype', 'default_prec', 'is_index',
                'group_dset_f_dtype_default', 'group_dset_f_dtype_double', 'group_dset_f_dtype_single',
                'group_dset_dtype_default', 'group_dset_dtype_double', 'group_dset_dtype_single',
                'group_dset_rank', 'group_dset_dim_list', 'group_dset_f_dims',
                'group_num_f_dtype_default', 'group_num_f_dtype_double', 'group_num_f_dtype_single',
                'group_num_dtype_default', 'group_num_dtype_double', 'group_num_dtype_single',
                'group_num_h5_dtype', 'group_num_py_dtype',
                'group_dset', 'group_num', 'group_str', 'group']

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
                                if '_read' in templine and (not 'fortran' in fname):
                                        line_toadd = indentlevel*" " + rc_line
                                        templine += line_toadd

                                f_out.write(templine)
                        num_written = []
                        continue
                    # special case to uncomment check for positive dimensioning variables in templates
                    elif 'uncommented by the generator for dimensioning' in line:
                        # only uncomment and write the line if `num` is in the name
                        if 'dim' in detailed_source[item]['trex_json_int_type']:
                            templine = line.replace('//', '') 
                            f_out.write(templine)
                    # general case of recursive replacement of inline triggers 
                    else:
                        populated_line = recursive_replace_line(line, triggers, detailed_source[item])
                        f_out.write(populated_line)

                f_out.write("\n")


def recursive_replace_line (input_line: str, triggers: list, source: dict) -> str:
    """ 
    Recursive replacer. Recursively calls itself as long as there is at least one "$" present in the `input_line`. 

            Parameters:
                    input_line (str)    : input line
                    triggers (list)     : list of triggers (templated variables to be replaced)
                    source (dict)       : dictionary of variables with substitution details (usually either datasets or numbers)

            Returns:
                    output_line (str)   : processed (replaced) line
    """    
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


def iterative_populate_file (filename: str, paths: dict, groups: dict, datasets: dict, numbers: dict, strings: dict) -> None:
    """ 
    Iteratively populate files with unique functions that contain templated variables.

            Parameters:
                    filename (str)          : template file to be populated
                    paths (dict)            : dictionary of paths per source directory
                    groups (dict)           : dictionary of groups
                    datasets (dict)         : dictionary of datasets with substitution details
                    numbers (dict)          : dictionary of numbers with substitution details
                    strings (dict)          : dictionary of strings with substitution details

            Returns:
                    None
    """
    add_trigger = 'rc = trexio_text_free_$group$'
    triggers = [add_trigger, '$group_dset$', '$group_num$', '$group_str$', '$group$']

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
                    populated_line = iterative_replace_line(line, '$group$', groups, add_line=error_handler)
                    f_out.write(populated_line)
                elif id == 1:
                    populated_line = iterative_replace_line(line, triggers[id], datasets, None)
                    f_out.write(populated_line)
                elif id == 2:
                    populated_line = iterative_replace_line(line, triggers[id], numbers, None)
                    f_out.write(populated_line)
                elif id == 3:
                    populated_line = iterative_replace_line(line, triggers[id], strings, None)
                    f_out.write(populated_line)
                elif id == 4:
                    populated_line = iterative_replace_line(line, triggers[id], groups, None)
                    f_out.write(populated_line)
                else:
                    f_out.write(line)
                    
            f_out.write("\n")


def iterative_replace_line (input_line: str, case: str, source: dict, add_line: str) -> str:
    """ 
    Iterative replacer. Iteratively copy-pastes `input_line` each time with a new substitution of a templated variable depending on the `case`. 

            Parameters:
                    input_line (str)    : input line
                    case (str)          : single trigger case (templated variable to be replaced)
                    source (dict)       : dictionary of variables with substitution details
                    add_line (str)      : special line to be added (e.g. for error handling)

            Returns:
                    output_block (str)   : processed (replaced) block of text
    """    
    output_block = ""
    for item in source.keys():
        templine1 = input_line.replace(case.upper(), item.upper())
        templine2 = templine1.replace(case, item)
        if add_line != None:
            templine2 += add_line

        output_block += templine2

    return output_block


def check_triggers (input_line: str, triggers: list) -> int:
    """
    Check the presence of the trigger in the `input_line`.

            Parameters:
                    input_line (str)    : string to be checked
                    triggers (list)     : list of triggers (templated variables)

            Returns:
                    out_id (int)        : id of the trigger item in the list
    """
    out_id = -1
    for id,trig in enumerate(triggers):
        if trig in input_line or trig.upper() in input_line:
            out_id = id
            return out_id
        
    return out_id


def special_populate_text_group(fname: str, paths: dict, group_dict: dict, detailed_dset: dict, detailed_numbers: dict, detailed_strings: dict) -> None:
    """ 
    Special population for group-related functions in the TEXT back end.

            Parameters:
                    fname (str)             : template file to be populated
                    paths (dict)            : dictionary of paths per source directory
                    group_dict (dict)       : dictionary of groups
                    detailed_dset (dict)    : dictionary of datasets with substitution details
                    detailed_numbers (dict) : dictionary of numbers with substitution details
                    detailed_strings (dict) : dictionary of string attributes with substitution details

            Returns:
                    None
    """
    fname_new = join('populated',f'pop_{fname}')
    templ_path = get_template_path(fname, paths)

    triggers = ['group_dset_dtype', 'group_dset_std_dtype_out', 'group_dset_std_dtype_in',
                'group_num_dtype_double', 'group_num_std_dtype_out', 'group_num_std_dtype_in',
                'group_dset', 'group_num', 'group_str', 'group']

    for group in group_dict.keys():

        with open(join(templ_path,fname), 'r') as f_in :
            with open(join(templ_path,fname_new), 'a') as f_out :

                subloop_dset = False
                subloop_num = False
                loop_body = ''
                dset_allocated = []
                str_allocated = []

                for line in f_in :

                    if 'START REPEAT GROUP_DSET' in line:
                        subloop_dset = True
                        continue
                    # this can be merged in one later using something like START REPEAT GROUP_ATTR in line
                    elif 'START REPEAT GROUP_NUM' in line or 'START REPEAT GROUP_ATTR_STR' in line:
                        subloop_num = True
                        continue
                    
                    if 'END REPEAT GROUP_DSET' in line:

                        for dset in detailed_dset.keys():
                            if group != detailed_dset[dset]['group']: 
                                continue

                            if ('REPEAT GROUP_DSET_STR' in line) and (detailed_dset[dset]['dtype'] != 'char*'):
                                continue
                            if ('REPEAT GROUP_DSET_NUM' in line) and (detailed_dset[dset]['dtype'] == 'char*'):
                                continue

                            dset_allocated.append(dset)

                            if 'FREE($group$->$group_dset$)' in loop_body:
                                tmp_string = ''
                                for dset_alloc in dset_allocated:
                                    tmp_string += f'FREE({group}->{dset_alloc});\n        '

                                tmp_body = loop_body.replace('FREE($group$->$group_dset$);', tmp_string)

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

                    elif 'END REPEAT GROUP_ATTR_STR' in line:
                        for str in detailed_strings.keys():
                            if group != detailed_strings[str]['group']: 
                                continue

                            str_allocated.append(str)

                            if 'FREE($group$->$group_str$)' in loop_body:
                                tmp_string = ''
                                for str_alloc in str_allocated:
                                    tmp_string += f'FREE({group}->{str_alloc});\n        '

                                tmp_body = loop_body.replace('FREE($group$->$group_str$);', tmp_string)

                                populated_body = recursive_replace_line(tmp_body, triggers, detailed_strings[str])
                                f_out.write(populated_body)
                            else:
                                save_body = loop_body
                                populated_body = recursive_replace_line(save_body, triggers, detailed_strings[str])
                                f_out.write(populated_body)

                        subloop_num = False
                        loop_body = ''
                        str_allocated = []

                        continue

                    if not subloop_num and not subloop_dset:
                        # NORMAL CASE WITHOUT SUBLOOPS 
                        if '$group_dset' in line:
                            for dset in detailed_dset.keys():
                                if group != detailed_dset[dset]['group']: 
                                    continue
                                populated_line = recursive_replace_line(line, triggers, detailed_dset[dset])
                                f_out.write(populated_line)
                        elif '$group_str' in line:
                            for str in detailed_strings.keys():
                                if group != detailed_strings[str]['group']: 
                                    continue
                                populated_line = recursive_replace_line(line, triggers, detailed_strings[str])
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
                        loop_body += line

                f_out.write("\n")


def get_template_path (filename: str, path_dict: dict) -> str:
    """ 
    Returns the absolute path to the directory with indicated `filename` template.

            Parameters:
                    filename (str)   : template file to be populated
                    path_dict (dict) : dictionary of paths per source directory

            Returns:
                    path (str) : resulting path
    """
    for dir_type in path_dict.keys():
        if dir_type in filename:
            path = path_dict[dir_type]
            return path
        
    raise ValueError('Filename should contain one of the keywords')


def get_group_dict (configuration: dict) -> dict:
    """ 
    Returns the dictionary of all groups.

            Parameters:
                    configuration (dict) : configuration from `trex.json`

            Returns:
                    group_dict (dict) : dictionary of groups
    """
    group_dict = {}
    for k in configuration.keys():
        group_dict[k] = 0

    return group_dict


def get_detailed_num_dict (configuration: dict) -> dict:
    """ 
    Returns the dictionary of all `num`-suffixed variables.
    Keys are names, values are subdictionaries containing corresponding group and group_num names. 

            Parameters:
                    configuration (dict) : configuration from `trex.json`

            Returns:
                    num_dict (dict) : dictionary of num-suffixed variables
    """
    num_dict = {}
    for k1,v1 in configuration.items():
        for k2,v2 in v1.items():
            if len(v2[1]) == 0:
                tmp_num = f'{k1}_{k2}'
                if 'str' not in v2[0]:
                    tmp_dict = {}
                    tmp_dict['group'] = k1
                    tmp_dict['group_num'] = tmp_num
                    num_dict[tmp_num] = tmp_dict

                    # TODO the arguments below are almost the same as for group_dset (except for trex_json_int_type) and can be exported from somewhere
                    if v2[0] == 'float':
                        tmp_dict['datatype'] = 'double'
                        tmp_dict['group_num_h5_dtype']       = 'native_double'
                        tmp_dict['group_num_f_dtype_default']= 'real(8)'
                        tmp_dict['group_num_f_dtype_double'] = 'real(8)'
                        tmp_dict['group_num_f_dtype_single'] = 'real(4)'
                        tmp_dict['group_num_dtype_default']= 'double'
                        tmp_dict['group_num_dtype_double'] = 'double'
                        tmp_dict['group_num_dtype_single'] = 'float'
                        tmp_dict['default_prec']   = '64'
                        tmp_dict['group_num_std_dtype_out'] = '24.16e'
                        tmp_dict['group_num_std_dtype_in'] = 'lf'
                        tmp_dict['group_num_py_dtype'] = 'float'
                    elif v2[0] in ['int', 'dim']:
                        tmp_dict['datatype'] = 'int64_t'
                        tmp_dict['group_num_h5_dtype'] = 'native_int64'
                        tmp_dict['group_num_f_dtype_default']= 'integer(4)'
                        tmp_dict['group_num_f_dtype_double'] = 'integer(8)'
                        tmp_dict['group_num_f_dtype_single'] = 'integer(4)'
                        tmp_dict['group_num_dtype_default']= 'int32_t'
                        tmp_dict['group_num_dtype_double'] = 'int64_t'
                        tmp_dict['group_num_dtype_single'] = 'int32_t'
                        tmp_dict['default_prec']   = '32'
                        tmp_dict['group_num_std_dtype_out'] = '" PRId64 "'
                        tmp_dict['group_num_std_dtype_in']  = '" SCNd64 "' 
                        tmp_dict['group_num_py_dtype'] = 'int'
                        tmp_dict['trex_json_int_type'] = v2[0]

    return num_dict


def get_detailed_str_dict (configuration: dict) -> dict:
    """
    Returns the dictionary of all `str`-like attributes.
    Keys are names, values are subdictionaries containing corresponding group and group_str names.

            Parameters:
                    configuration (dict) : configuration from `trex.json`

            Returns:
                    str_dict (dict) : dictionary of string attributes
    """
    str_dict = {}
    for k1,v1 in configuration.items():
        for k2,v2 in v1.items():
            if len(v2[1]) == 0:
                tmp_str = f'{k1}_{k2}'
                if 'str' in v2[0]:
                    tmp_dict = {}
                    tmp_dict['group'] = k1
                    tmp_dict['group_str'] = tmp_str
                    str_dict[tmp_str] = tmp_dict

    return str_dict


def get_dset_dict (configuration: dict) -> dict:
    """ 
    Returns the dictionary of datasets. 
    Keys are names, values are lists containing datatype, list of dimensions and group name

            Parameters:
                    configuration (dict) : configuration from `trex.json`

            Returns:
                    dset_dict (dict) : dictionary of datasets
    """
    dset_dict = {}
    for k1,v1 in configuration.items():
        for k2,v2 in v1.items():
            if len(v2[1]) != 0:
                tmp_dset = f'{k1}_{k2}'
                dset_dict[tmp_dset] = v2
                # append a group name for postprocessing
                dset_dict[tmp_dset].append(k1)

    return dset_dict


def split_dset_dict_detailed (datasets: dict) -> tuple:
    """ 
    Returns the detailed dictionary of datasets. 
    Keys are names, values are subdictionaries containing substitutes for templated variables

            Parameters:
                    configuration (dict) : configuration from `trex.json`

            Returns:
                    dset_numeric_dict, dset_string_dict (tuple) : dictionaries corresponding to all numeric- and string-based datasets, respectively.
    """
    dset_numeric_dict = {}
    dset_string_dict = {}
    for k,v in datasets.items():
        # create a temp dictionary
        tmp_dict = {}
        # specify details required to replace templated variables later
        if v[0] == 'float':
            datatype = 'double'
            group_dset_h5_dtype       = 'native_double'
            group_dset_f_dtype_default= 'real(8)'
            group_dset_f_dtype_double = 'real(8)'
            group_dset_f_dtype_single = 'real(4)'
            group_dset_dtype_default= 'double'
            group_dset_dtype_double = 'double'
            group_dset_dtype_single = 'float'
            default_prec   = '64'
            group_dset_std_dtype_out = '24.16e'
            group_dset_std_dtype_in = 'lf'
            group_dset_py_dtype = 'float'
        elif v[0] in ['int', 'index']:
            datatype = 'int64_t'
            group_dset_h5_dtype = 'native_int64'
            group_dset_f_dtype_default= 'integer(4)'
            group_dset_f_dtype_double = 'integer(8)'
            group_dset_f_dtype_single = 'integer(4)'
            group_dset_dtype_default= 'int32_t'
            group_dset_dtype_double = 'int64_t'
            group_dset_dtype_single = 'int32_t'
            default_prec   = '32'
            group_dset_std_dtype_out = '" PRId64 "'
            group_dset_std_dtype_in  = '" SCNd64 "' 
            group_dset_py_dtype = 'int'
        elif v[0] == 'str':
            datatype = 'char*'
            group_dset_h5_dtype = ''
            group_dset_f_dtype_default = ''
            group_dset_f_dtype_double = ''
            group_dset_f_dtype_single = ''
            group_dset_dtype_default = 'char*'
            group_dset_dtype_double = ''
            group_dset_dtype_single = ''
            default_prec   = ''
            group_dset_std_dtype_out = 's'
            group_dset_std_dtype_in  = 's' 
            group_dset_py_dtype = 'str'
        
        # add the dset name for templates
        tmp_dict['group_dset'] = k
        # add flag to detect index types
        if 'index' == v[0]:
            tmp_dict['is_index'] = 'file->one_based'
        else:
            tmp_dict['is_index'] = 'false'
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
        tmp_dict['group_dset_py_dtype'] = group_dset_py_dtype
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

        # split datasets in numeric- and string- based
        if (datatype == 'char*'):
            dset_string_dict[k] = tmp_dict
        else:
            dset_numeric_dict[k] = tmp_dict

    return (dset_numeric_dict, dset_string_dict)


def check_dim_consistency(num: dict, dset: dict) -> None:
    """ 
    Consistency check to make sure that each dimensioning variable exists as a num attribute of some group. 

            Parameters:
                    num (dict)  : dictionary of num-suffixed variables
                    dset (dict) : dictionary of datasets

            Returns:
                    None
    """
    dim_tocheck = []
    for v in dset.values():
        tmp_dim_list = [dim.replace('.','_') for dim in v[1] if not dim.isdigit()]
        for dim in tmp_dim_list:
            if dim not in dim_tocheck:
                dim_tocheck.append(dim)

    for dim in dim_tocheck:
        if not dim in num.keys():
            raise ValueError(f"Dimensioning variable {dim} is not a num attribute of any group.\n")
