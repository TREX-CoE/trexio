#!/usr/bin/env python3
import json

json_file = "../../trex.json"
trexio_h = "../../include/trexio.h"
wrapper_h = "wrapper.h"
generated_rs = "src/generated.rs"

def check_version():
   with open('Cargo.toml','r') as f:
      for line in f:
         if line.startswith("version"):
            rust_version = line.split('=')[1].strip()[1:-1]
            break
   with open('../../configure.ac','r') as f:
      for line in f:
         if line.startswith("AC_INIT"):
            trexio_version = line.split(',')[1].strip()[1:-1]
            break
   if rust_version != trexio_version:
      print(f"Inconsistent versions:\nTREXIO:{trexio_version}\nRust:  {rust_version}\n")
      raise



def make_interface():
    err = {}
    be  = {}
    with open(trexio_h, 'r') as f:
        for line in f:
            buf = line.lstrip()

            # Get exit codes
            if buf.startswith("#define TREXIO_") and "(trexio_exit_code)" in buf :
                buf2 = buf.replace(")","").replace("(","").split()
                err[buf2[1]] = int(buf2[3].strip())

            # Get backends
            if buf.startswith("#define TREXIO_") and "(back_end_t)" in buf :
                buf2 = buf.replace(")","").replace("(","").split()
                be[buf2[1]] = int(buf2[3].strip())

    with open(wrapper_h,'w') as f:
        f.write("#include <trexio.h>\n")

        # Write exit codes
        for k, v in err.items():
            f.write(f"#undef {k}\n")
            f.write(f"const trexio_exit_code {k} = {v};\n")

        # Write backends
        for k, v in be.items():
            f.write(f"#undef {k}\n")
            f.write(f"const back_end_t {k} = {v};\n")

        f.write(f"#undef TREXIO_AUTO;\n")
        f.write(f"const back_end_t TREXIO_AUTO = TREXIO_INVALID_BACK_END;\n")



def make_functions():
   with open(json_file,'r') as f:
      data = json.load(f)

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

   r = ["""
use std::iter::zip;
use std::ffi::CString;

impl File {""" ]

   for group in data:
      group_l = group.lower()
      r += [ """
/// Checks if the group `{group}` exists in the file.
pub fn has_{group_l}(&self) -> Result<bool, ExitCode> {
    let rc = unsafe { c::trexio_has_{group}(self.ptr) };
    match rc {
        c::TREXIO_SUCCESS   =>  Ok(true),
        c::TREXIO_HAS_NOT   =>  Ok(false),
        x                   =>  Err(ExitCode::from(x)),
    }
}
"""
.replace("{group}",group)
.replace("{group_l}",group_l) ]
      for element in data[group]:
         type_c = convert_c[data[group][element][0]]
         type_r = convert_r[data[group][element][0]]
         element_l = element.lower()
         r += [ """
/// Checks if the element `{element}` of the group `{group}` exists in the file.
pub fn has_{group_l}_{element_l}(&self) -> Result<bool, ExitCode> {
    let rc = unsafe { c::trexio_has_{group}_{element}(self.ptr) };
    match rc {
        c::TREXIO_SUCCESS   =>  Ok(true),
        c::TREXIO_HAS_NOT   =>  Ok(false),
        x                   =>  Err(ExitCode::from(x)),
    }
}
"""
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]

         # Scalar elements
         if data[group][element][1] == []:
            if data[group][element][0] in [ "int", "float", "dim", "index" ]:
               r += [ """
/// Reads the scalar element `{element}` contained in the group `{group}`.
pub fn read_{group_l}_{element_l}(&self) -> Result<{type_r}, ExitCode> {
   let mut data_c: {type_c} = 0{type_c};
   let (rc, data) = unsafe {
      let rc = c::trexio_read_{group}_{element}_64(self.ptr, &mut data_c);
      (rc, data_c.try_into().expect("try_into failed in read_{group_l}_{element_l}"))
   };
   rc_return(data, rc)
}

/// Writes the scalar element `{element}` contained in the group `{group}`.
pub fn write_{group_l}_{element_l}(&self, data: {type_r}) -> Result<(), ExitCode> {
    let data: {type_c} = data.try_into().expect("try_into failed in write_{group_l}_{element_l}");
    let rc = unsafe { c::trexio_write_{group}_{element}_64(self.ptr, data) };
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
               r += [ """
/// Reads the string `{element}` contained in the group `{group}`.
pub fn read_{group_l}_{element_l}(&self, capacity: usize) -> Result<String, ExitCode> {
   let data_c = CString::new(vec![ b' ' ; capacity]).expect("CString::new failed");
   let (rc, data) = unsafe {
      let data_c = data_c.into_raw() as *mut c_char;
      let rc = c::trexio_read_{group}_{element}(self.ptr, data_c, capacity.try_into().expect("try_into failed in read_{group_l}_{element_l}"));
      (rc, CString::from_raw(data_c))
   };
   let result : String = CString::into_string(data).expect("into_string failed in read_{group_l}_{element_l}");
   rc_return(result, rc)
}


/// Writes the string `{element}` contained in the group `{group}`.
pub fn write_{group_l}_{element_l}(&self, data: &str) -> Result<(), ExitCode> {
    let size : i32 = data.len().try_into().expect("try_into failed in write_{group_l}_{element_l}");
    let data = string_to_c(data);
    let data = data.as_ptr() as *const c_char;
    let rc = unsafe { c::trexio_write_{group}_{element}(self.ptr, data, size) };
    rc_return((), rc)
}
"""
.replace("{type_c}",type_c)
.replace("{type_r}",type_r)
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]


            elif data[group][element][0] in [ "dim readonly" ]:
               r += [ """
/// Reads the dimensioning variable `{element}` contained in group `{group}`.
pub fn read_{group_l}_{element_l}(&self) -> Result<{type_r}, ExitCode> {
   let mut data_c: {type_c} = 0{type_c};
   let (rc, data) = unsafe {
      let rc = c::trexio_read_{group}_{element}_64(self.ptr, &mut data_c);
      (rc, data_c.try_into().expect("try_into failed in read_{group_l}_{element_l}"))
   };
   rc_return(data, rc)
}
"""
.replace("{type_r}",type_r)
.replace("{type_c}",type_c)
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]

         # Array elements
         else:

            if data[group][element][0] in [ "int", "float", "dim", "index" ]:
               t = [ f"""
/// Reads the array `{element}` contained in the group `{group}`.
///
/// Dimensions are `{data[group][element][1]}`.
/// """ ]
               if len(data[group][element][1]) > 1:
                    t += [ f"""/// The array is returned as a flattened one-dimensional vector.
/// To put it back as a multidimensional array, you can use the [`chunks`] method:
///
/// # Example 
/// ```
/// let one_d_array = trexio_file.read_{group_l}_{element_l}()?;""" ]
                    try:
                        dim_group, dim_element = data[group][element][1][0].split('.')
                        t += [ f"/// let {dim_group}_{dim_element} = trexio_file.read_{dim_group}_{dim_element}()?;",
f"/// let two_d_array = one_d_array.chunks({dim_group}_{dim_element}).collect();"
]
                    except:
                        t += [ f"/// let two_d_array = one_d_array.chunks({data[group][element][1][0]}).collect();" ]
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

               r += [ """
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
               t = [ """pub fn read_{group_l}_{element_l}(&self, capacity: usize) -> Result<Vec<String>, ExitCode> {
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
    for i in 0..size{
        let c_str: *mut i8 = unsafe { std::alloc::alloc_zeroed(std::alloc::Layout::array::<i8>(capacity).unwrap()) as *mut i8 };
        if c_str.is_null() {
            return Err(ExitCode::AllocationFailed);
        }
        dset_out[i] = c_str;
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
pub fn write_{group_l}_{element_l}(&self, data: &[&str]) -> Result<(), ExitCode> {
    let mut size = 0;
    // Find longest string
    for s in data.iter() {
       let l = s.len();
       size = if l>size {l} else {size};
    }
    size = size+1;
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
pub fn write_{group_l}_{element_l}(&self, offset: usize, data: &[{typ}]) -> Result<(), ExitCode> {
    let mut idx = Vec::<i32>::with_capacity({size}*data.len());
    let mut val = Vec::<f64>::with_capacity(data.len());

    for d in data.iter() {
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






   r += [ "}" ]
   with open(generated_rs,'w') as f:
      f.write('\n'.join(r))



if __name__ == '__main__':
   check_version()
   make_interface()
   make_functions()
