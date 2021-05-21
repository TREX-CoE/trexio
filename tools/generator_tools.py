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
