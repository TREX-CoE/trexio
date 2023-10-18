#!/usr/bin/env python3
import json

json_file = "../../trex.json"
generated_rs = "src/generated_py.rs"

convert_r = { "int": "i64",
              "int special" : "usize",
              "float" : "f64",
              "float sparse" : "f64",
              "float buffered" : "f64",
              "dim" : "usize",
              "dim readonly" : "usize",
              "index" : "usize",
              "str" : "str"}

convert_c = { "int": "i64",
              "int special" : "i64",
              "float" : "f64",
              "float sparse" : "f64",
              "float buffered" : "f64",
              "dim" : "i64",
              "dim readonly" : "i64",
              "index" : "i64",
              "str" : "str"}

def make_array_functions(data):
   r = []
   for group in data:
      group_l = group.lower()
      for element in data[group]:
         type_c = convert_c[data[group][element][0]]
         type_r = convert_r[data[group][element][0]]
         element_l = element.lower()

         if data[group][element][1] != []:
            if data[group][element][0] in [ "int", "float", "dim", "index" ]:
               t = [ f"""
/// Reads the `{element}` array from the group `{group}` in the file.
///
/// # Dimensions
///
/// The array is of dimension `{data[group][element][1]}`.
///
/// # Returns
///
/// * `Result<Vec<{type_r}>, ExitCode>` - Returns a flattened one-dimensional vector that contains 
/// the elements of the `{element}` array. If the operation is unsuccessful, it returns `Err(ExitCode)`.
///
/// """ ]
               if len(data[group][element][1]) > 1:
                    t += [ f"""
/// # Example
///
/// To reshape the one-dimensional vector back into a two-dimensional array, you can use the [`chunks`] method:
///
/// ```
/// let one_d_array = trexio_file.read_{group_l}_{element_l}()?;""" ]
                    try:
                        dim_group, dim_element = data[group][element][1][0].split('.')
                        t += [ f"/// let {dim_group}_{dim_element} = trexio_file.read_{dim_group}_{dim_element}()?;",
f"/// let two_d_array: Vec<_> = one_d_array.chunks({dim_group}_{dim_element}).collect();"
]
                    except:
                        t += [ f"/// let two_d_array: Vec<_> = one_d_array.chunks({data[group][element][1][0]}).collect();" ]
                    t += [ """
/// ```
///
/// [`chunks`]: slice::chunks"""
]
               t += [ """
pub fn read_{group_l}_{element_l}(&self) -> Result<Vec<{type_r}>, ExitCode> {
  let size = 1;""" ]
               t_prime = []
               for dim in data[group][element][1]:
                   try:    # A dimensioning variable
                     dim_group, dim_element = dim.split('.')
                     t_prime += [f"  let size = size * self.read_{dim_group}_{dim_element}()?;" ]
                   except: # Only an integer
                     t_prime += [f"  let size = size * {dim};"]
               t += t_prime
               t += [ """
   let mut data: Vec<{type_r}> = Vec::with_capacity(size);
   let rc = unsafe {
      let data_c = data.as_mut_ptr() as *mut {type_c};
      let rc = c::trexio_read_safe_{group}_{element}_64(self.ptr, data_c, size.try_into().expect("try_into failed in read_{group}_{element} (size)"));
      data.set_len(size);
      rc
   };
   rc_return(data, rc)
}
""" ]
               r += [ '\n'.join(t)
.replace("{type_c}",type_c)
.replace("{type_r}",type_r)
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]

               r += [ f"""
/// Writes the `{element}` array into the group `{group}` in the file.
///
/// # Parameters
///
/// * `data: &[{type_r}]` - A one-dimensional vector that contains the elements of the `{element}` array
/// to be written into the file. The vector should be flattened from a two-dimensional array with 
/// dimensions `{data[group][element][1]}`.
///
/// # Returns
///
/// * `Result<(), ExitCode>` - Returns `Ok(())` if the operation is successful,
/// otherwise returns `Err(ExitCode)`.""", """\
pub fn write_{group_l}_{element_l}(&self, data: &[{type_r}]) -> Result<(), ExitCode> {
    let size: i64 = data.len().try_into().expect("try_into failed in write_{group_l}_{element_l}");
    let data = data.as_ptr() as *const {type_c};
    let rc = unsafe { c::trexio_write_safe_{group}_{element}_64(self.ptr, data, size) };
    rc_return((), rc)
}
"""
.replace("{type_c}",type_c)
.replace("{type_r}",type_r)
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]

            elif data[group][element][0] in [ "str" ]:
               t = [ f"""
/// Reads the `{element}` array from the group `{group}` in the file.
///
/// # Dimensions
///
/// The array is of dimension `{data[group][element][1]}`.
///
/// # Returns
///
/// * `Result<Vec<{type_r}>, ExitCode>` - Returns a flattened one-dimensional vector that contains 
/// the elements of the `{element}` array. If the operation is unsuccessful, it returns `Err(ExitCode)`.
///
/// """ ]
               if len(data[group][element][1]) > 1:
                    t += [ f"""
/// # Example
///
/// To reshape the one-dimensional vector back into a two-dimensional array, you can use the [`chunks`] method:
///
/// ```
/// let one_d_array = trexio_file.read_{group_l}_{element_l}()?;""" ]
                    try:
                        dim_group, dim_element = data[group][element][1][0].split('.')
                        t += [ f"/// let {dim_group}_{dim_element} = trexio_file.read_{dim_group}_{dim_element}()?;",
f"/// let two_d_array: Vec<_> = one_d_array.chunks({dim_group}_{dim_element}).collect();"
]
                    except:
                        t += [ f"/// let two_d_array: Vec<_> = one_d_array.chunks({data[group][element][1][0]}).collect();" ]
                    t += [ """
/// ```
///
/// [`chunks`]: slice::chunks"""
]
               t += [ """pub fn read_{group_l}_{element_l}(&self, capacity: usize) -> Result<Vec<String>, ExitCode> {
  let size = 1;""" ]
               t_prime = []
               for dim in data[group][element][1]:
                   try:    # A dimensioning variable
                     dim_group, dim_element = dim.split('.')
                     t_prime += [f"  let size = size * self.read_{dim_group}_{dim_element}()?;" ]
                   except: # Only an integer
                     t_prime += [f"  let size = size * {dim};"]
               t += t_prime
               t += [ """
    // Allocate an array of *mut i8 pointers (initialized to null)
    let mut dset_out: Vec<*mut i8> = vec![std::ptr::null_mut(); size];

    // Allocate C-style strings and populate dset_out
    for item in dset_out.iter_mut().take(size){
        let c_str: *mut i8 = unsafe { std::alloc::alloc_zeroed(std::alloc::Layout::array::<i8>(capacity).unwrap()) as *mut i8 };
        if c_str.is_null() {
            return Err(ExitCode::AllocationFailed);
        }
        *item = c_str;
    }


   let rc = unsafe {
      c::trexio_read_{group}_{element}(self.ptr, dset_out.as_mut_ptr(), capacity.try_into().expect("try_into failed in read_{group}_{element} (capacity)") )
   };

    // Convert the populated C strings to Rust Strings
    let mut rust_strings = Vec::new();
    for &c_str in &dset_out {
        let rust_str = unsafe {
            std::ffi::CStr::from_ptr(c_str)
                .to_string_lossy()
                .into_owned()
        };
        rust_strings.push(rust_str);
    }

    // Clean up allocated C strings
    for &c_str in &dset_out {
        unsafe { std::alloc::dealloc(c_str as *mut u8, std::alloc::Layout::array::<i8>(capacity).unwrap()) };
    }

   rc_return(rust_strings, rc)
}
""" ]
               r += [ '\n'.join(t)
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]

               r += [ """
/// Writes the `{element}` array into the group `{group}` in the file.
///
/// # Parameters
///
/// * `data: &[{type_r}]` - A one-dimensional vector that contains the elements of the `{element}` array
/// to be written into the file. The vector should be flattened from a two-dimensional array with 
/// dimensions `{data[group][element][1]}`.
///
/// # Returns
///
/// * `Result<(), ExitCode>` - Returns `Ok(())` if the operation is successful,
/// otherwise returns `Err(ExitCode)`.""", """\
pub fn write_{group_l}_{element_l}(&self, data: &[&str]) -> Result<(), ExitCode> {
    let mut size = 0;
    // Find longest string
    for s in data {
       let l = s.len();
       size = if l>size {l} else {size};
    }
    size += 1;
    let data_c : Vec<CString> = data.iter().map(|&x| string_to_c(x)).collect::<Vec<_>>();
    let data_c : Vec<*const c_char> = data_c.iter().map(|x| x.as_ptr() as *const c_char).collect::<Vec<_>>();
    let size : i32 = size.try_into().expect("try_into failed in write_{group}_{element} (size)");
    let data_c = data_c.as_ptr() as *mut *const c_char;
    let rc = unsafe { c::trexio_write_{group}_{element}(self.ptr, data_c, size) };
    rc_return((), rc)
}
"""
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]

            elif data[group][element][0] in [ "float sparse" ]:
               size = len(data[group][element][1])
               typ = "(" + ",".join( [ "usize" for _ in range(size) ]) + ", f64)"
               r += [ ("""
/// Reads a buffer of {element} from group {group}.
///
/// # Parameters
///
/// * `offset: usize` - The starting point in the array from which data will be read.
/// * `buffer_size: usize` - The size of the buffer in which read data will be stored.
///
/// # Returns
///
/// * `Result<Vec<{typ}>, ExitCode>` - Returns a vector of tuples containing 
/// the indices and the value of the element. The vector has a length of at most `buffer_size`.
///
/// # Notes
///
/// The reading process is a buffered operation, meaning that only a segment of the full array 
/// is read into the memory.
pub fn read_{group_l}_{element_l}(&self, offset: usize, buffer_size:usize) -> Result<Vec<{typ}>, ExitCode> {
    let mut idx = Vec::<i32>::with_capacity({size}*buffer_size);
    let mut val = Vec::<f64>::with_capacity(buffer_size);
    let idx_ptr = idx.as_ptr() as *mut i32;
    let val_ptr = val.as_ptr() as *mut f64;
    let offset: i64 = offset.try_into().expect("try_into failed in read_{group}_{element} (offset)");
    let mut buffer_size_read: i64 = buffer_size.try_into().expect("try_into failed in read_{group}_{element} (buffer_size)");
    let rc = unsafe { c::trexio_read_safe_{group}_{element}(self.ptr,
           offset, &mut buffer_size_read, idx_ptr, buffer_size_read, val_ptr, buffer_size_read)
    };
    let rc = match ExitCode::from(rc) {
              ExitCode::End => ExitCode::to_c(&ExitCode::Success),
              _       => rc
            };
    let buffer_size_read: usize = buffer_size_read.try_into().expect("try_into failed in read_{group}_{element} (buffer_size)");
    unsafe { idx.set_len({size}*buffer_size_read) };
    unsafe { val.set_len(buffer_size_read) };
    let idx: Vec::<&[i32]> = idx.chunks({size}).collect();

    let mut result = Vec::<{typ}>::with_capacity(buffer_size);
    for (i, v) in zip(idx, val) {
      result.push( ( """ +
','.join([ f"i[{k}].try_into().unwrap()" for k in range(size) ]) +
""",v) );
    }
    rc_return(result, rc)
}
""")
.replace("{size}",str(size))
.replace("{typ}",typ)
.replace("{type_c}",type_c)
.replace("{type_r}",type_r)
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]

               r += [ ("""
/// Writes a buffer of {element} from group {group}.
///
/// # Parameters
///
/// * `offset: usize` - The starting point in the array at which data will be written.
/// * `data: &[{typ}]` - A slice of tuples containing the indices and the value of the element.
///
/// # Returns
///
/// * `Result<(), ExitCode>` - Returns `Ok(())` if the writing operation is successful, 
/// otherwise returns `Err(ExitCode)`.
///
/// # Notes
///
/// The writing process is a buffered operation, meaning that only a segment of the full array 
/// is written into the file.
pub fn write_{group_l}_{element_l}(&self, offset: usize, data: &[{typ}]) -> Result<(), ExitCode> {
    let mut idx = Vec::<i32>::with_capacity({size}*data.len());
    let mut val = Vec::<f64>::with_capacity(data.len());

    for d in data {
""" +
'\n'.join([ f"       idx.push(d.{i}.try_into().unwrap());" for i in range(size) ]) +
f"\n       val.push(d.{size});" +
"""
    }

    let size_max: i64 = data.len().try_into().expect("try_into failed in write_{group}_{element} (size_max)");
    let buffer_size = size_max;
    let idx_ptr = idx.as_ptr() as *const i32;
    let val_ptr = val.as_ptr() as *const f64;
    let offset: i64 = offset.try_into().expect("try_into failed in write_{group}_{element} (offset)");
    let rc = unsafe { c::trexio_write_safe_{group}_{element}(self.ptr,
           offset, buffer_size, idx_ptr, size_max, val_ptr, size_max) };
    rc_return((), rc)
}
""")
.replace("{size}",str(size))
.replace("{typ}",typ)
.replace("{type_c}",type_c)
.replace("{type_r}",type_r)
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]
   return r


def make_functions():
   with open(json_file,'r') as f:
      data = json.load(f)

   r = ["""
use std::iter::zip;

/// This implementation block includes additional functions automatically generated from tables.
/// For more details, refer to [TREXIO tables documentation](https://trex-coe.github.io/trexio/trex.html).
impl File {
#![allow(clippy::unnecessary_cast)]
#![allow(clippy::useless_conversion)]
#![allow(clippy::type_complexity)]
""" ]

   r += make_array_functions(data)

   r += [ "}" ]
   with open(generated_rs,'w') as f:
      f.write('\n'.join(r))



if __name__ == '__main__':
   make_functions()
