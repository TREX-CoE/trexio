# TREXIO Tutorial

This interactive Tutorial covers some basic use cases of the TREXIO library based on the Python API. At this point, it is assumed that the TREXIO Python package has been sucessfully installed on the user machine or in the virtual environment. If this is not the case, feel free to follow the [installation guide](https://github.com/TREX-CoE/trexio/blob/master/python/README.md).

## Importing TREXIO

First of all, let's import the TREXIO package.


```python
try:
    import trexio
except ImportError:
    raise Exception("Unable to import trexio. Please check that trexio is properly instaled.")
```

If no error occurs, then it means that the TREXIO package has been sucessfully imported. Within the current import, TREXIO attributes can be accessed using the corresponding `trexio.attribute` notation. If you prefer to bound a shorter name to the imported module (as commonly done by the NumPy users with `import numpy as np`), this is also possible. To do so, replace `import trexio` with `import trexio as tr` for example. To learn more about importing modules, see the corresponding page of the [Python documentation](https://docs.python.org/3/tutorial/modules.html#more-on-modules).

## Creating a new TREXIO file

TREXIO currently supports two back ends for file I/O:

1. `TREXIO_HDF5`, which relies on extensive use of the [HDF5 library](https://portal.hdfgroup.org/display/HDF5/HDF5) and the associated binary file format. This back end is optimized for high performance but it requires HDF5 to be installed on the user machine.

2. `TREXIO_TEXT`, which relies on basic I/O operations that are available in the standard C library. This back end is not optimized for performance but it is supposed to work "out-of-the-box" since there are no external dependencies.

Armed with these new definitions, let's proceed with the tutorial. The first task is to create a TREXIO file called `benzene_demo.h5`. But first we have to remove the file if it exists in the current directory


```python
filename = 'benzene_demo.h5'

import os
try:
    os.remove(filename)
except:
    print(f"File {filename} does not exist.")
```

    File benzene_demo.h5 does not exist.


We are now ready to create a new TREXIO file:


```python
demo_file = trexio.File(filename, mode='w', back_end=trexio.TREXIO_HDF5)
```

This creates an instance of the `trexio.File` class, which we refer to as `demo_file` in this tutorial. You can check that the corresponding file called `benzene_demo.h5` exists in the root directory. It is now open for writing as indicated by the user-supplied argument `mode='w'`. The file has been initiated using `TREXIO_HDF5` back end and will be accessed accordingly from now on. The information about back end is stored internally by TREXIO, which means that there is no need to specify it every time the I/O operation is performed. If the file named `benzene_demo.h5` already exists, then it is re-opened for writing (and not truncated to prevent data loss).

## Writing data in the TREXIO file

Prior to any work with TREXIO library, we highly recommend users to read about [TREXIO internal configuration](https://trex-coe.github.io/trexio/trex.html), which explains the structure of the wavefunction file. The reason is that TREXIO API has a naming convention, which is based on the groups and variables names that are pre-defined by the developers. In this Tutorial, we will only cover contents of the `nucleus` group. Note that custom groups and variables can be added to the TREXIO API.

In this Tutorial, we consider benzene molecule (C6H6) as an example. Since benzene has 12 atoms, let's specify it in the previously created `demo_file`. In order to do so, one has to call `trexio.write_nucleus_num` function, which accepts an instance of the `trexio.File` class as a first argument and an `int` value corresponding to the number of nuclei as a second argument.


```python
nucleus_num = 12
```


```python
trexio.write_nucleus_num(demo_file, nucleus_num)
```

In fact, all API functions that contain `write_` prefix can be used in a similar way. 
Variables that contain `_num` suffix are important part of the TREXIO file because some of them define dimensions of arrays. For example, `nucleus_num` variable corresponds to the number of atoms, which will be internally used to write/read the `nucleus_coord` array of nuclear coordinates. In order for TREXIO files to be self-consistent, overwriting num-suffixed variables is currently disabled.

The number of atoms is not sufficient to define a molecule. Let's first create a list of nuclear charges, which correspond to benzene. 


```python
charges = [6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1.]
```

According to the TREX configuration file, there is a `charge` attribute of the `nucleus` group, which has `float` type and `[nucleus_num]` dimension. The `charges` list defined above fits nicely in the description and can be written as follows


```python
trexio.write_nucleus_charge(demo_file, charges)
```

**Note: TREXIO function names only contain parts in singular form.** This means that, both `write_nucleus_charges` and `write_nuclear_charges` are invalid API calls. These functions simply do not exist in the `trexio` Python package and the corresponding error message should appear.

 Alternatively, one can provide a list of nuclear labels (chemical elements from the periodic table) that correspond to the aforementioned charges. There is a `label` attribute of the `nucleus` group, which has `str` type and `[nucleus_num]` dimension. Let's create a list of 12 strings, which correspond to 6 carbon and 6 hydrogen atoms:


```python
labels = [
    'C',
    'C',
    'C',
    'C',
    'C',
    'C',
    'H',
    'H',
    'H',
    'H',
    'H',
    'H']
```

This can now be written using the corresponding `trexio.write_nucleus_label` function:


```python
trexio.write_nucleus_label(demo_file, labels)
```

Two examples above demonstrate how to write arrays of numbers or strings in the file. TREXIO also supports I/O operations on single numerical or string attributes. In fact, in this Tutorial you have already written one numerical attribute: `nucleus_num`. Let's now write a string `'D6h'`, which indicates a point group of benzene molecule. According to the TREX configuration file, `point_group` is a `str` attribute of the `nucleus` group, thus it can be written in the `demo_file` as follows


```python
point_group = 'D6h'
```


```python
trexio.write_nucleus_point_group(demo_file, point_group)
```

### Writing NumPy arrays (float or int types)

The aforementioned examples cover the majority of the currently implemented functionality related to writing data in the file. It is worth mentioning that I/O of numerical arrays in TREXIO Python API relies on extensive use of the [NumPy package](https://numpy.org/). This will be discussed in more details in the [section about reading data](#Reading-data-from-the-TREXIO-file). However, TREXIO `write_` functions that work with numerical arrays also accept `numpy.ndarray` objects. For example, consider a `coords` list of nuclear coordinates that correspond to benzene molecule


```python
coords = [
    [0.00000000  ,  1.39250319 ,  0.00000000 ],
    [-1.20594314 ,  0.69625160 ,  0.00000000 ],
    [-1.20594314 , -0.69625160 ,  0.00000000 ],
    [0.00000000  , -1.39250319 ,  0.00000000 ],
    [1.20594314  , -0.69625160 ,  0.00000000 ],
    [1.20594314  ,  0.69625160 ,  0.00000000 ],
    [-2.14171677 ,  1.23652075 ,  0.00000000 ],
    [-2.14171677 , -1.23652075 ,  0.00000000 ],
    [0.00000000  , -2.47304151 ,  0.00000000 ],
    [2.14171677  , -1.23652075 ,  0.00000000 ],
    [2.14171677  ,  1.23652075 ,  0.00000000 ],
    [0.00000000  ,  2.47304151 ,  0.00000000 ],
    ]
```

Let's take advantage of using NumPy arrays with fixed precision for floating point numbers. But first, try to import the `numpy` package


```python
try:
    import numpy as np
except ImportError:
    raise Exception("Unable to import numpy. Please check that numpy is properly instaled.")
```

You can now convert the previously defined `coords` list into a numpy array with fixed `float64` type as follows


```python
coords_np = np.array(coords, dtype=np.float64)
```

TREXIO functions that write numerical arrays accept both lists and numpy arrays as a second argument. That is, both `trexio.write_nucleus_coord(demo_file, coords)` and `trexio.write_nucleus_coord(demo_file, coords_np)` are valid API calls. Let's use the latter and see if it works


```python
trexio.write_nucleus_coord(demo_file, coords_np)
```

Congratulations, you have just completed the `nucleus` section of the TREXIO file for benzene molecule! Note that TREXIO API is rather permissive and do not impose any strict ordering on the I/O operations. The only requirement is that dimensioning (`_num` suffixed) variables have to be written in the file **before** writing arrays that depend on these variables. For example, attempting to write `nucleus_charge` or `nucleus_coord` fails if `nucleus_num` has not been written.

### TREXIO error handling

TREXIO Python API provides the `trexio.Error` class which simplifies exception handling in the Python scripts. This class wraps up TREXIO return codes and propagates them all the way from the C back end to the Python front end. Let's try to write a negative number of basis set shells `basis_num` in the TREXIO file.


```python
try:
    trexio.write_basis_num(demo_file, -256)
except trexio.Error as e:
    print(f"TREXIO error message: {e.message}")
```

    TREXIO error message: Invalid argument 2


The error message says **Invalid argument 2**, which indicates that the user-provided value `-256` is not valid.

As mentioned before, `_num`-suffixed variables cannot be overwritten in the file. But what happens if you accidentally attempt to do so? Let's have a look at the `write_nucleus_num` function as an example:


```python
try:
    trexio.write_nucleus_num(demo_file, 24)
except trexio.Error as e:
    print(f"TREXIO error message: {e.message}")
```

    TREXIO error message: Attribute already exists


The API rightfully complains that the target attribute already exists and cannot be overwritten.

Alternatively, the aforementioned case can be handled using `trexio.has_nucleus_num` function as follows


```python
if not trexio.has_nucleus_num:
    trexio.write_nucleus_num(demo_file, 24)
```

TREXIO functions with `has_` prefix return `True` if the corresponding variable exists and `False` otherwise.

What about writing arrays? Let's try to write an list of 48 nuclear indices instead of 12


```python
indices = [i for i in range(nucleus_num*4)]
```


```python
try:
    trexio.write_basis_nucleus_index(demo_file, indices)
except trexio.Error as e:
    print(f"TREXIO error message: {e.message}")
```

    TREXIO error message: Access to memory beyond allocated


According to the TREX configuration file, `nucleus_index` attribute of a `basis` group is supposed to have `[nucleus_num]` elements. In the example above, we have tried to write 4 times more elements, which might lead to memory and/or file corruption. Luckily, TREXIO internally checks the array dimensions and returns an error in case of inconsistency.

## Closing the TREXIO file

It is good practice to close the TREXIO file at the end of the session. In fact, `trexio.File` class has a destructor, which normally takes care of that. However, if you intend to re-open the TREXIO file, it has to be closed explicitly before. This can be done using the `close` method, i.e.


```python
demo_file.close()
```

Good! You are now ready to inspect the contents of the `benzene_demo.h5` file using the reading functionality of TREXIO.

## Reading data from the TREXIO file

First, let's try to open an existing TREXIO file in read-only mode. This can be done by creating a new instance of the `trexio.File` class but this time with `mode='r'` argument. Back end has to be specified as well.


```python
demo_file_r = trexio.File(filename, mode='r', back_end=trexio.TREXIO_HDF5)
```

When reading data from the TREXIO file, the only required argument is a previously created instance of `trexio.File` class. In our case, it is `demo_file_r`. TREXIO functions with `read_` prefix return the desired variable as an output. For example, `nucleus_num` value can be read from the file as follows


```python
nucleus_num_r = trexio.read_nucleus_num(demo_file_r)
```


```python
print(f"nucleus_num from {filename} file ---> {nucleus_num_r}")
```

    nucleus_num from benzene_demo.h5 file ---> 12


The function call assigns `nucleus_num_r` to 12, which is consistent with the number of atoms in benzene that we wrote in the previous section.

All calls to functions that read data can be done in a very similar way. The key point here is a function name, which in turn defines the output format. Hopefully by now you got used to the TREXIO naming convention and the contents of the `nucleus` group. Which function would you call to read a `point_group` attribute of the `nucleus` group? What type does it return? See the answer below:


```python
point_group_r = trexio.read_nucleus_point_group(demo_file_r)
```


```python
print(f"nucleus_point_group from {filename} TREXIO file ---> {point_group_r}\n")
print(f"Is return type of read_nucleus_point_group a string? ---> {isinstance(point_group_r, str)}")
```

    nucleus_point_group from benzene_demo.h5 TREXIO file ---> D6h
    
    Is return type of read_nucleus_point_group a string? ---> True


The `trexio.read_nucleus_point_group` function call returns a string `D6h`, which is exactly what we provided in the previous section. Now, let's read nuclear charges and labels.


```python
labels_r = trexio.read_nucleus_label(demo_file_r)
```


```python
print(f"nucleus_label from {filename} file \n---> {labels_r}")
```

    nucleus_label from benzene_demo.h5 file 
    ---> ['C', 'C', 'C', 'C', 'C', 'C', 'H', 'H', 'H', 'H', 'H', 'H']



```python
charges_r = trexio.read_nucleus_charge(demo_file_r)
```


```python
print(f"nucleus_charge from {filename} file \n---> {charges_r}")
```

    nucleus_charge from benzene_demo.h5 file 
    ---> [6. 6. 6. 6. 6. 6. 1. 1. 1. 1. 1. 1.]


The values are consistent with each other and with the previously written data. Not bad. What about the format of the output? 


```python
print(f"nucleus_label return type: {type(labels_r)}")
```

    nucleus_label return type: <class 'list'>


This makes sense, isn't it? We have written a `list` of nuclear labels and have received back a `list` of values from the file. What about nuclear charges?


```python
print(f"nucleus_charge return type: {type(charges_r)}")
```

    nucleus_charge return type: <class 'numpy.ndarray'>


Looks like `trexio.read_nucleus_charge` function returns a `numpy.ndarray` even though we have provided a python-ic `list` to `trexio.write_nucleus_charge` in the previous section. Why is it so? As has been mentioned before, TREXIO Python API internally relies on the use of the NumPy package to communicate arrays of `float`-like or `int`-like values. This prevents some memory leaks and grants additional flexibility to the API. What kind of flexibility? Check this out:


```python
print(f"return dtype in NumPy notation: ---> {charges_r.dtype}")
```

    return dtype in NumPy notation: ---> float64


It means that the default precision of the TREXIO output is double (`np.float64`) for arrays of floating point numbers like `nucleus_charge`. But what if you do not need this extra precision and would like to read nuclear charges in single (`np.float32`) or even reduced (e.g. `np.float16`) precision? TREXIO Python API provides an additional (optional) argument for this. This argument is called `dtype` and accepts one of the [NumPy data types](https://numpy.org/doc/stable/user/basics.types.html). For example,


```python
charges_np = trexio.read_nucleus_charge(demo_file_r, dtype=np.float32)
```


```python
print(f"return dtype in NumPy notation: ---> {charges_np.dtype}")
```

    return dtype in NumPy notation: ---> float32


### Reading multidimensional arrays

So far, we have only read flat 1D arrays. However, we have also written a 2D array of nuclear coordinates. Let's now read it back from the file:


```python
coords_r = trexio.read_nucleus_coord(demo_file_r)
```


```python
print(f"nucleus_coord from {filename} TREXIO file: \n{coords_r}")
```

    nucleus_coord from benzene_demo.h5 TREXIO file: 
    [[ 0.          1.39250319  0.        ]
     [-1.20594314  0.6962516   0.        ]
     [-1.20594314 -0.6962516   0.        ]
     [ 0.         -1.39250319  0.        ]
     [ 1.20594314 -0.6962516   0.        ]
     [ 1.20594314  0.6962516   0.        ]
     [-2.14171677  1.23652075  0.        ]
     [-2.14171677 -1.23652075  0.        ]
     [ 0.         -2.47304151  0.        ]
     [ 2.14171677 -1.23652075  0.        ]
     [ 2.14171677  1.23652075  0.        ]
     [ 0.          2.47304151  0.        ]]



```python
print(f"return shape: ---> {coords_r.shape}")
```

    return shape: ---> (12, 3)


We can see that TREXIO returns a 2D array with 12 rows and 3 columns, which is consistent with the `nucleus_coord` dimensions `[nucleus_num, 3]`. What this means is that **by default TREXIO reshapes the output flat array into a multidimensional one** whenever applicable. This is done based on the shape specified in the TREX configuration file.

In some cases, it might be a good idea to explicitly check that the data exists in the file before reading it. This can be achieved using `has_`-suffixed functions of the API. For example,


```python
if trexio.has_nucleus_coord(demo_file_r):
    coords_safer = trexio.read_nucleus_coord(demo_file_r)
```

## Conclusion

In this Tutorial, you have created a TREXIO file using HDF5 back end and have written the number of atoms, point group, nuclear charges, labels and coordinates, which correspond to benzene molecule. You have also learned how to read this data back from the TREXIO file and how to handle some TREXIO errors.
