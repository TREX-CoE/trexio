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
    files_todo['all'] = [
        f for f in all_files
        if 'read' in f or 'write' in f or 'has' in f or 'flush' in f or 'free' in f or 'hrw' in f or 'delete' in f
        ]
    for key in ['dset_data', 'dset_str', 'dset_sparse', 'attr_num', 'attr_str', 'group']:
        files_todo[key] = list(filter(lambda x: key in x, files_todo['all']))

    files_todo['group'].append('struct_text_group_dset.h')
    # files that correspond to iterative population (e.g. the code is repeated within the function body but the function itself is unique)
    files_todo['auxiliary'] = [
        'def_hdf5.c', 'basic_hdf5.c', 'struct_hdf5.h',
        'basic_text_group.c', 'struct_text_group.h'
    ]

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
                    detailed_source (dict)  : dictionary of variables with substitution details

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
                'group_dset_format_scanf', 'group_dset_format_printf', 'group_dset_sparse_dim',
                'group_dset_sparse_indices_printf', 'group_dset_sparse_indices_scanf',
                'sparse_format_printf_8', 'sparse_format_printf_16', 'sparse_format_printf_32',
                'sparse_line_length_8', 'sparse_line_length_16', 'sparse_line_length_32',
                'group_dset', 'group_num', 'group_str', 'group']

    for item in detailed_source.keys():

        # special case to exclude write functions for readonly dimensions (like determinant_num) from the public API
        if 'write' in fname and 'front' in fname and ('.f90' in fname or '.py' in fname):
            if 'trex_json_int_type' in detailed_source[item].keys():
                if 'readonly' in detailed_source[item]['trex_json_int_type']:
                    continue

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
                        # only uncomment and write the line if `dim` is in the name
                        if 'dim' in detailed_source[item]['trex_json_int_type']:
                            templine = line.replace('//', '')
                            f_out.write(templine)
                    # general case of recursive replacement of inline triggers
                    else:
                        populated_line = recursive_replace_line(line, triggers, detailed_source[item])
                        # special case to include some functions in the private header
                        if 'trex_json_int_type' in detailed_source[item].keys():
                            if 'readonly' in detailed_source[item]['trex_json_int_type'] and 'write' in line and 'front.h' in fname:
                                with open(join(templ_path,'populated/private_pop_front.h'), 'a') as f_priv:
                                    f_priv.write(populated_line)
                            else:
                                f_out.write(populated_line)
                        else:
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


def iterative_populate_file (filename: str, paths: dict, detailed_all: dict) -> None:
    """
    Iteratively populate files with unique functions that contain templated variables.

            Parameters:
                    filename (str)          : template file to be populated
                    paths (dict)            : dictionary of paths per source directory
                    detailed_all(dict)      : dictionary with substitution details with the following keys:
                        'groups'            : dictionary of groups with substitution details
                        'datasets'          : dictionary of datasets with substitution details
                        'numbers'           : dictionary of numbers with substitution details
                        'strings'           : dictionary of strings with substitution details

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
                    # special case for proper error handling when deallocating text groups
                    error_handler = '  if (rc != TREXIO_SUCCESS) return rc;\n'
                    populated_line = iterative_replace_line(line, '$group$', detailed_all['groups'], add_line=error_handler)
                    f_out.write(populated_line)
                elif id == 1:
                    populated_line = iterative_replace_line(line, triggers[id], detailed_all['datasets'], None)
                    f_out.write(populated_line)
                elif id == 2:
                    populated_line = iterative_replace_line(line, triggers[id], detailed_all['numbers'], None)
                    f_out.write(populated_line)
                elif id == 3:
                    populated_line = iterative_replace_line(line, triggers[id], detailed_all['strings'], None)
                    f_out.write(populated_line)
                elif id == 4:
                    populated_line = iterative_replace_line(line, triggers[id], detailed_all['groups'], None)
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

    triggers = ['group_dset_dtype', 'group_dset_format_printf', 'group_dset_format_scanf',
                'group_num_dtype_double', 'group_num_format_printf', 'group_num_format_scanf',
                'group_dset', 'group_num', 'group_str', 'group']

    for group in group_dict.keys():

        with open(join(templ_path,fname), 'r') as f_in :
            with open(join(templ_path,fname_new), 'a') as f_out :

                subloop_dset = False
                subloop_num = False
                loop_body = ''

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

                            if ('REPEAT GROUP_DSET_STR' in line) and (detailed_dset[dset]['group_dset_dtype'] != 'char*'):
                                continue
                            if ('REPEAT GROUP_DSET_NUM' in line) and (detailed_dset[dset]['group_dset_dtype'] == 'char*'):
                                continue

                            save_body = loop_body
                            populated_body = recursive_replace_line(save_body, triggers, detailed_dset[dset])
                            f_out.write(populated_body)

                        subloop_dset = False
                        loop_body = ''
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

                            save_body = loop_body
                            populated_body = recursive_replace_line(save_body, triggers, detailed_strings[str])
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
        group_dict[k] = {'group' : k}

    return group_dict


def get_dtype_dict (dtype: str, target: str, rank = None, int_len_printf = None) -> dict:
    """
    Returns the dictionary of dtype-related templated variables set for a given `dtype`.
    Keys are names of templated variables, values are strings to be used by the generator.

            Parameters:
                    dtype (str)         : dtype corresponding to the trex.json (i.e. int/dim/float/float sparse/str)
                    target (str)        : `num` or `dset`
                    rank (int)          : [optional] value of n in n-index (sparse) dset; needed to build the printf/scanf format string
                    int_len_printf(dict): [optional]
                                          keys: precision (e.g. 32 for int32_t)
                                          values: lengths reserved for one index when printing n-index (sparse) dset (e.g. 10 for int32_t)

            Returns:
                    dtype_dict (dict) : dictionary dtype-related substitutions
    """
    if not target in ['num', 'dset']:
        raise Exception('Only num or dset target can be set.')
    if 'sparse' in dtype:
        if rank is None or int_len_printf is None:
            raise Exception("Both rank and int_len_printf arguments has to be provided to build the dtype_dict for sparse data.")
    if rank is not None and rank <= 1:
        raise Exception('Rank of sparse quantity cannot be lower than 2.')
    if int_len_printf is not None and not isinstance(int_len_printf, dict):
        raise Exception('int_len_printf has to be a dictionary of lengths for different precisions.')

    dtype_dict = {}
    # set up the key-value pairs dependending on the dtype
    if dtype == 'float':
        dtype_dict.update({
            'default_prec'                    : '64',
            f'group_{target}_dtype'           : 'double',
            f'group_{target}_h5_dtype'        : 'native_double',
            f'group_{target}_f_dtype_default' : 'real(c_double)',
            f'group_{target}_f_dtype_double'  : 'real(c_double)',
            f'group_{target}_f_dtype_single'  : 'real(c_float)',
            f'group_{target}_dtype_default'   : 'double',
            f'group_{target}_dtype_double'    : 'double',
            f'group_{target}_dtype_single'    : 'float',
            f'group_{target}_format_printf'   : '24.16e',
            f'group_{target}_format_scanf'    : 'lf',
            f'group_{target}_py_dtype'        : 'float'
        })
    elif dtype in ['int', 'dim', 'dim readonly', 'index']:
        dtype_dict.update({
            'default_prec'                    : '32',
            f'group_{target}_dtype'           : 'int64_t',
            f'group_{target}_h5_dtype'        : 'native_int64',
            f'group_{target}_f_dtype_default' : 'integer(c_int32_t)',
            f'group_{target}_f_dtype_double'  : 'integer(c_int64_t)',
            f'group_{target}_f_dtype_single'  : 'integer(c_int32_t)',
            f'group_{target}_dtype_default'   : 'int32_t',
            f'group_{target}_dtype_double'    : 'int64_t',
            f'group_{target}_dtype_single'    : 'int32_t',
            f'group_{target}_format_printf'   : '" PRId64 "',
            f'group_{target}_format_scanf'    : '" SCNd64 "',
            f'group_{target}_py_dtype'        : 'int'
        })
    elif dtype == 'str':
        dtype_dict.update({
            'default_prec'                   : '',
            f'group_{target}_dtype'          : 'char*',
            f'group_{target}_h5_dtype'       : '',
            f'group_{target}_f_dtype_default': '',
            f'group_{target}_f_dtype_double' : '',
            f'group_{target}_f_dtype_single' : '',
            f'group_{target}_dtype_default'  : 'char*',
            f'group_{target}_dtype_double'   : '',
            f'group_{target}_dtype_single'   : '',
            f'group_{target}_format_printf'  : 's',
            f'group_{target}_format_scanf'   : 's',
            f'group_{target}_py_dtype'       : 'str'
        })
    elif 'sparse' in dtype:
        # build format string for n-index sparse quantity
        item_printf_8  = f'%{int_len_printf[8]}" PRIu8 " '
        item_printf_16 = f'%{int_len_printf[16]}" PRIu16 " '
        item_printf_32 = f'%{int_len_printf[32]}" PRId32 " '
        item_scanf  = '%" SCNd32 " '
        group_dset_format_printf_8 = '"'
        group_dset_format_printf_16 = '"'
        group_dset_format_printf_32 = '"'
        group_dset_format_scanf  = ''
        for _ in range(rank):
            group_dset_format_printf_8  += item_printf_8
            group_dset_format_printf_16 += item_printf_16
            group_dset_format_printf_32 += item_printf_32
            group_dset_format_scanf  += item_scanf
        # append the format string for float values
        group_dset_format_printf_8  += '%24.16e" '
        group_dset_format_printf_16 += '%24.16e" '
        group_dset_format_printf_32 += '%24.16e" '
        group_dset_format_scanf  += '%lf'

        # set up the dictionary for sparse
        dtype_dict.update({
            'default_prec'                   : '',
            f'group_{target}_dtype'          : 'double',
            f'group_{target}_h5_dtype'       : '',
            f'group_{target}_f_dtype_default': '',
            f'group_{target}_f_dtype_double' : '',
            f'group_{target}_f_dtype_single' : '',
            f'group_{target}_dtype_default'  : '',
            f'group_{target}_dtype_double'   : '',
            f'group_{target}_dtype_single'   : '',
            f'sparse_format_printf_8'        : group_dset_format_printf_8,
            f'sparse_format_printf_16'       : group_dset_format_printf_16,
            f'sparse_format_printf_32'       : group_dset_format_printf_32,
            f'group_{target}_format_scanf'   : group_dset_format_scanf,
            f'group_{target}_py_dtype'       : ''
        })

    return dtype_dict



def get_detailed_num_dict (configuration: dict) -> dict:
    """
    Returns the dictionary of all `num`-suffixed variables.
    Keys are names, values are subdictionaries containing corresponding group and group_num names.

            Parameters:
                    configuration (dict) : configuration from `trex.json`

            Returns:
                    num_dict (dict) : dictionary of all numerical attributes (of types int, float, dim)
    """
    num_dict = {}
    for k1,v1 in configuration.items():
        for k2,v2 in v1.items():
            if len(v2[1]) == 0:
                tmp_num = f'{k1}_{k2}'
                if not 'str' in v2[0]:
                    tmp_dict = {}

                    tmp_dict['group'] = k1
                    tmp_dict['group_num'] = tmp_num
                    tmp_dict.update(get_dtype_dict(v2[0], 'num'))
                    if v2[0] in ['int', 'dim', 'dim readonly']:
                        tmp_dict['trex_json_int_type'] = v2[0]
                    else:
                        tmp_dict['trex_json_int_type'] = ''

                    num_dict[tmp_num] = tmp_dict

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
    dset_sparse_dict = {}
    for k,v in datasets.items():

        # create a temp dictionary
        tmp_dict = {}
        rank = len(v[1])
        datatype = v[0]

        # skip the data which has 'special' datatype (e.g. determinants for which the code is not templated)
        if 'special' in datatype:
            continue

        # define whether the dset is sparse
        is_sparse = False
        int_len_printf = {}
        if 'sparse' in datatype:
            is_sparse = True
            int_len_printf[32] = 10
            int_len_printf[16] = 5
            int_len_printf[8] = 3

        # get the dtype-related substitutions required to replace templated variables later
        if not is_sparse:
            dtype_dict = get_dtype_dict(datatype, 'dset')
        else:
            dtype_dict = get_dtype_dict(datatype, 'dset', rank, int_len_printf)

        tmp_dict.update(dtype_dict)

        # set the group_dset key to the full name of the dset
        tmp_dict['group_dset'] = k
        # add flag to detect index types
        if 'index' in datatype:
            tmp_dict['is_index'] = 'file->one_based'
        else:
            tmp_dict['is_index'] = 'false'

        # add the rank
        tmp_dict['rank'] = rank
        tmp_dict['group_dset_rank'] = str(rank)
        # add the list of dimensions
        tmp_dict['dims'] = [dim.replace('.','_') for dim in v[1]]
        # build a list of dimensions to be inserted in the dims array initialization, e.g. {ao_num, ao_num}
        dim_list = tmp_dict['dims'][0]
        if rank > 1:
            for i in range(1, rank):
                dim_toadd = tmp_dict['dims'][i]
                dim_list += f', {dim_toadd}'

        tmp_dict['group_dset_dim_list'] = dim_list

        if rank == 0:
            dim_f_list = ""
        else:
            dim_f_list = "(*)"
        tmp_dict['group_dset_f_dims'] = dim_f_list

        if is_sparse:
            # store the max possible dim of the sparse dset (e.g. mo_num)
            tmp_dict['group_dset_sparse_dim'] = tmp_dict['dims'][0]
            # build printf/scanf sequence and compute line length for n-index sparse quantity
            index_printf = f'*(index_sparse + {str(rank)}*i'
            index_scanf  = f'index_sparse + {str(rank)}*i'
            # one index item consumes up to index_length characters (int32_len_printf for int32 + 1 for space)
            group_dset_sparse_indices_printf = index_printf + ')'
            group_dset_sparse_indices_scanf  = index_scanf
            sparse_line_length_32            = int_len_printf[32] + 1
            sparse_line_length_16            = int_len_printf[16] + 1
            sparse_line_length_8             = int_len_printf[8]  + 1
            # loop from 1 because we already have stored one index
            for index_count in range(1,rank):
                group_dset_sparse_indices_printf += f', {index_printf} + {index_count})'
                group_dset_sparse_indices_scanf  += f', {index_scanf} + {index_count}'
                sparse_line_length_32            += int_len_printf[32] + 1
                sparse_line_length_16            += int_len_printf[16] + 1
                sparse_line_length_8             += int_len_printf[8]  + 1

            # add 24 chars occupied by the floating point value of sparse dataset + 1 char for "\n"
            sparse_line_length_32 += 24 + 1
            sparse_line_length_16 += 24 + 1
            sparse_line_length_8  += 24 + 1

            tmp_dict['sparse_line_length_32']    = str(sparse_line_length_32)
            tmp_dict['sparse_line_length_16']    = str(sparse_line_length_16)
            tmp_dict['sparse_line_length_8']     = str(sparse_line_length_8)
            tmp_dict['group_dset_sparse_indices_printf'] = group_dset_sparse_indices_printf
            tmp_dict['group_dset_sparse_indices_scanf']  = group_dset_sparse_indices_scanf

        # add group name as a key-value pair to the dset dict
        tmp_dict['group'] = v[2]

        # split datasets in numeric- and string- based
        if 'str' in datatype:
            dset_string_dict[k] = tmp_dict
        elif is_sparse:
            dset_sparse_dict[k] = tmp_dict
        else:
            dset_numeric_dict[k] = tmp_dict

    return (dset_numeric_dict, dset_string_dict, dset_sparse_dict)


def check_dim_consistency(num: dict, dset: dict) -> None:
    """
    Consistency check to make sure that each dimensioning variable exists as a num attribute of some group.

            Parameters:
                    num (dict)  : dictionary of numerical attributes
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

    num_onlyDim = [
        attr_name for attr_name, specs in num.items()
        if 'dim' in specs['trex_json_int_type']
        ]

    for dim in dim_tocheck:
        if not dim in num_onlyDim:
            raise ValueError(f"Dimensioning variable {dim} is not a num attribute of any group.\n")
