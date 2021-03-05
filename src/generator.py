import json

with open('trex.json', 'r') as f:
    config0 = json.load(f)

print('Metadata I/O currently not supported')
# TODO, for now remove metadata-related stuff
del config0['metadata']

config = {}
for k,v in config0.items():
    if k == 'nucleus' or k == 'electron':
        config[k] = v

print(config)

groups = [group for group in config.keys()]

dim_variables = {}
dim_list = []
for k1,v1 in config.items():
    for v2 in v1.values():
        for dim in v2[1]:
            if not dim.isdigit():
                tmp = dim.replace('.','_')
                dim_variables[tmp] = 0
                if dim not in dim_list: 
                    dim_list.append(dim)

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
print(numbers)

#print(attributes)
#print(groups)

file_list = ['temp_trexio_hdf5.c']
path = 'src/templates'
for fname in file_list:
    fname_new = fname.replace('temp_','')
    with open(f'{path}/{fname}', 'r') as f_in:
        with open(f'{path}/{fname_new}', 'w') as f_out:
            isfunc = False
            for line in f_in:
                if '$group$' in line and 'hdf5' in line:
                    # probably a good function criterion 
                    isfunc = True
                    

                if '$group$' in line or '$GROUP$' in line:
                    for group_name in config.keys():
                        templine = line.replace('$group$', f'{group_name}')
                        newline = templine.replace('$GROUP$', f'{group_name.upper()}')

                        f_out.write(newline)
                else:        
                    f_out.write(line)


