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
   r = []

   for group in data:
      group_l = group.lower()
      r += [ """
pub fn has_{group_l}(trex_file: File) -> Result<bool, ExitCode> {
    let rc = unsafe { c::trexio_has_{group}(trex_file) };
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
pub fn has_{group_l}_{element_l}(trex_file: File) -> Result<bool, ExitCode> {
    let rc = unsafe { c::trexio_has_{group}_{element}(trex_file) };
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
pub fn read_{group_l}_{element_l}(trex_file: File) -> Result<{type_r}, ExitCode> {
   let mut data_c: {type_c} = 0{type_c};
   let (rc, data) = unsafe {
      let rc = c::trexio_read_{group}_{element}_64(trex_file, &mut data_c);
      (rc, data_c.try_into().unwrap())
   };
   rc_return(rc, data)
}

pub fn write_{group_l}_{element_l}(trex_file: File, data: {type_r}) -> Result<(), ExitCode> {
    let data: {type_c} = data.try_into().unwrap();
    let rc = unsafe { c::trexio_write_{group}_{element}_64(trex_file, data) };
    rc_return(rc, ())
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
pub fn read_{group_l}_{element_l}(trex_file: File, capacity: usize) -> Result<String, ExitCode> {
   let mut data_c = String::with_capacity(capacity);
   let data_c = data_c.as_mut_ptr() as *mut c_char;
   let (rc, data) = unsafe {
      let rc = c::trexio_read_{group}_{element}(trex_file, data_c, capacity.try_into().unwrap());
      (rc, String::from_raw_parts(data_c as *mut u8, capacity, capacity))
   };
   rc_return(rc, data)
}

pub fn write_{group_l}_{element_l}(trex_file: File, data: &str) -> Result<(), ExitCode> {
    let size : i32 = data.len().try_into().unwrap();
    let data = string_to_c(data);
    let data = data.as_ptr() as *const c_char;
    let rc = unsafe { c::trexio_write_{group}_{element}(trex_file, data, size) };
    rc_return(rc, ())
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
pub fn read_{group_l}_{element_l}(trex_file: File) -> Result<{type_r}, ExitCode> {
   let mut data_c: {type_c} = 0{type_c};
   let (rc, data) = unsafe {
      let rc = c::trexio_read_{group}_{element}_64(trex_file, &mut data_c);
      (rc, data_c.try_into().unwrap())
   };
   rc_return(rc, data)
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
               t = [ """pub fn read_{group_l}_{element_l}(trex_file: File) -> Result<Vec<{type_r}>, ExitCode> {
  let size = 1;""" ]
               t_prime = []
               for dim in data[group][element][1]:
                   try:    # A dimensioning variable
                     dim_group, dim_element = dim.split('.')
                     t_prime += [f"  let size = size * read_{dim_group}_{dim_element}(trex_file).unwrap();" ]
                   except: # Only an integer
                     t_prime += [f"  let size = size * {dim};"]
               t += t_prime
               t += [ """
   let data: Vec<{type_r}> = Vec::with_capacity(size);
   let data_c = data.as_ptr() as *mut {type_c};
   let (rc, data) = unsafe {
      let rc = c::trexio_read_safe_{group}_{element}_64(trex_file, data_c, size.try_into().unwrap());
      (rc, data)
   };
   rc_return(rc, data)
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
pub fn write_{group_l}_{element_l}(trex_file: File, data: Vec<{type_r}>) -> Result<(), ExitCode> {
    let size: i64 = data.len().try_into().unwrap();
    let data = data.as_ptr() as *const {type_c};
    let rc = unsafe { c::trexio_write_safe_{group}_{element}_64(trex_file, data, size) };
    rc_return(rc, ())
}
"""
.replace("{type_c}",type_c)
.replace("{type_r}",type_r)
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]

            elif data[group][element][0] in [ "str" ]:
               t = [ """pub fn read_{group_l}_{element_l}(trex_file: File, capacity: usize) -> Result<Vec<String>, ExitCode> {
  let size = 1;""" ]
               t_prime = []
               for dim in data[group][element][1]:
                   try:    # A dimensioning variable
                     dim_group, dim_element = dim.split('.')
                     t_prime += [f"  let size = size * read_{dim_group}_{dim_element}(trex_file).unwrap();" ]
                   except: # Only an integer
                     t_prime += [f"  let size = size * {dim};"]
               t += t_prime
               t += [ """
   let data = vec![ String::with_capacity(capacity) ; size ];
   let data_c = data.as_ptr() as *mut *mut c_char;
      
   let (rc, data) = unsafe {
      let rc = c::trexio_read_{group}_{element}(trex_file, data_c, capacity.try_into().unwrap() );
      (rc, data)
   };
   rc_return(rc, data)
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
pub fn write_{group_l}_{element_l}(trex_file: File, data: Vec<&str>) -> Result<(), ExitCode> {
    let mut size = 0;
    for s in data.iter() {
       let l = s.len();
       size = if l>size {l} else {size};
    }
    size = size+1;
    let data_c : Vec<std::ffi::CString> = data.iter().map(|&x| string_to_c(x)).collect::<Vec<_>>();
    let data_c : Vec<*const c_char> = data_c.iter().map(|x| x.as_ptr() as *const c_char).collect::<Vec<_>>();
    let size : i32 = size.try_into().unwrap();
    let data_c = data_c.as_ptr() as *mut *const c_char;
    let rc = unsafe { c::trexio_write_{group}_{element}(trex_file, data_c, size) };
    rc_return(rc, ())
}
"""
.replace("{type_c}",type_c)
.replace("{type_r}",type_r)
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]

            elif data[group][element][0] in [ "float sparse" ]:
               pass



   with open(generated_rs,'w') as f:
      f.write('\n'.join(r))



if __name__ == '__main__':
   check_version()
   make_interface()
   make_functions()
