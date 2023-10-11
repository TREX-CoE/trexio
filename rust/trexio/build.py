#!/usr/bin/env python3

json_file = "../../trex.json"
trexio_h = "../../include/trexio.h"

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

    with open("wrapper.h",'w') as f:
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
  pass

if __name__ == '__main__':
   check_version()
   make_interface()
   make_functions()
