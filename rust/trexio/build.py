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
                 "string" : "string"}

   convert_c = { "int": "i64",
                 "int special" : "i64",
                 "float" : "f64",
                 "float sparse" : "f64",
                 "float buffered" : "f64",
                 "dim" : "i64",
                 "dim readonly" : "i64",
                 "index" : "i64",
                 "string" : "string"}
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
   let data = unsafe {
      let data_c: {type_c};
      let rc = c::trexio_read_{group}_{element}_64(trex_file, &data);
      data_c.try_into().unwrap();
   };
   rc_return(rc, data)
}

pub fn write_{group_l}_{element_l}<T>(trex_file: File, data: T) -> Result<(), ExitCode>
               where {type_c}: From<T> {
    let data: {type_c} = data.try_into().unwrap();
    let rc = unsafe { c::trexio_write_{group}_{element}_64(trex_file, data) };
    rc_return(rc, ())
}
"""
.replace("{type_c}",type_c)
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]

            elif data[group][element][0] in [ "string" ]:
               pass  # TODO

            elif data[group][element][0] in [ "dim readonly" ]:
               r += [ """
pub fn write_{group_l}_{element_l}<T>(trex_file: File, data: T) -> Result<(), ExitCode>
               where {type_c}: From<T> {
    let data: {type_c} = data.try_into().unwrap();
    let rc = unsafe { c::trexio_write_{group}_{element}_64(trex_file, data) };
    rc_return(rc, ())
}
"""
.replace("{type_c}",type_c)
.replace("{group}",group)
.replace("{group_l}",group_l)
.replace("{element}",element)
.replace("{element_l}",element_l) ]



   with open(generated_rs,'w') as f:
      f.write('\n'.join(r))



if __name__ == '__main__':
   check_version()
   make_interface()
   make_functions()
