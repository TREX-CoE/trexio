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
impl File {""" ]

   for group in data:
      group_l = group.lower()
      r += [ """
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
pub fn read_{group_l}_{element_l}(&self) -> Result<{type_r}, ExitCode> {
   let mut data_c: {type_c} = 0{type_c};
   let (rc, data) = unsafe {
      let rc = c::trexio_read_{group}_{element}_64(self.ptr, &mut data_c);
      (rc, data_c.try_into().expect("try_into failed in read_{group_l}_{element_l}"))
   };
   rc_return(data, rc)
}

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
pub fn read_{group_l}_{element_l}(&self, capacity: usize) -> Result<String, ExitCode> {
   let mut data_c = String::with_capacity(capacity);
   let data_c = data_c.as_mut_ptr() as *mut c_char;
   let (rc, data) = unsafe {
      let rc = c::trexio_read_{group}_{element}(self.ptr, data_c, capacity.try_into().expect("try_into failed in read_{group_l}_{element_l}"));
      (rc, String::from_raw_parts(data_c as *mut u8, capacity, capacity))
   };
   rc_return(data, rc)
}

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
               t = [ """pub fn read_{group_l}_{element_l}(&self) -> Result<Vec<{type_r}>, ExitCode> {
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
   let data: Vec<{type_r}> = Vec::with_capacity(size);
   let data_c = data.as_ptr() as *mut {type_c};
   let (rc, data) = unsafe {
      let rc = c::trexio_read_safe_{group}_{element}_64(self.ptr, data_c, size.try_into().expect("try_into failed in read_{group}_{element}"));
      (rc, data)
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
pub fn write_{group_l}_{element_l}(&self, data: Vec<{type_r}>) -> Result<(), ExitCode> {
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
   let data = vec![ String::with_capacity(capacity) ; size ];
   let data_c = data.as_ptr() as *mut *mut c_char;
      
   let (rc, data) = unsafe {
      let rc = c::trexio_read_{group}_{element}(self.ptr, data_c, capacity.try_into().expect("try_into failed in read_{group}_{element}") );
      (rc, data)
   };
   rc_return(data, rc)
}
""" ]
               r += [ '\n'.join(t)
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]

               r += [ """
pub fn write_{group_l}_{element_l}(&self, data: Vec<&str>) -> Result<(), ExitCode> {
    let mut size = 0;
    // Find longest string
    for s in data.iter() {
       let l = s.len();
       size = if l>size {l} else {size};
    }
    size = size+1;
    let data_c : Vec<std::ffi::CString> = data.iter().map(|&x| string_to_c(x)).collect::<Vec<_>>();
    let data_c : Vec<*const c_char> = data_c.iter().map(|x| x.as_ptr() as *const c_char).collect::<Vec<_>>();
    let size : i32 = size.try_into().expect("try_into failed in write_{group}_{element}");
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
               typ = "&[(" + ",".join( [ "usize" for _ in range(size) ]) + ", f64)]"
               r += [ ("""
pub fn write_{group_l}_{element_l}(&self, offset: usize, data: {typ}) -> Result<(), ExitCode> {
    let mut idx = Vec::<i32>::with_capacity({size}*data.len());
    let mut val = Vec::<f64>::with_capacity(data.len());
    // Array of indices
    for d in data.iter() {
""" +
'\n'.join([ f"       idx.push(d.{i}.try_into().unwrap());" for i in range(size) ]) +
f"\n       val.push(d.{size});" +
"""
    }

    let size_max: i64 = data.len().try_into().expect("try_into failed in write_{group}_{element}");
    let buffer_size = size_max;
    let idx_ptr = idx.as_ptr() as *const i32;
    let val_ptr = val.as_ptr() as *const f64;
    let offset: i64 = offset.try_into().expect("try_into failed in write_{group}_{element}");
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
