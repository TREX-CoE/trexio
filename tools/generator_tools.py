
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

    print(output_block)
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
        elif v[0] == 'int':
            datatype = 'int64_t'
        elif v[0] == 'str':
            datatype = 'string'
        # add the datatype
        tmp_dict['dtype'] = datatype
        # add the list of dimensions
        tmp_dict['dims'] = [dim.replace('.','_') for dim in v[1]]
        # add the rank
        tmp_dict['rank'] = len(v[1])
        # build a list of dimensions to be inserted in the dims array initialization, e.g. {ao_num, ao_num}
        dim_list = tmp_dict['dims'][0]
        if tmp_dict['rank'] > 1:
            for i in range(1, tmp_dict['rank']):
                dim_toadd = tmp_dict['dims'][i]
                dim_list += f', {dim_toadd}'
        tmp_dict['dim_list'] = dim_list
        # split datasets in numerical and string 
        if (datatype=='string'):
            dset_string_dict[k] = tmp_dict
        else:
            dset_numeric_dict[k] = tmp_dict

    return (dset_numeric_dict, dset_string_dict)
