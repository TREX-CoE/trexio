const WRAPPER_H: &str = "wrapper.h";
const GENERATED_RS: &str = "generated.rs";

use std::env;
use std::path::PathBuf;
use std::collections::HashMap;
use std::fs::File;
use std::io::{self, BufRead, BufReader, Write};
use serde_json::Value;
use pkg_config::Config;


/// The header path will be searched in the following order:
///
/// 1. pkg-config
/// 2. Environment variable TREXIO_INCLUDE_DIR
/// 3. Common system paths
///
/// If the header is found, the JSON configuration will be extracted and
/// written to trex.json in the output directory.
/// For documentation builds on docs.rs, see `make_docs_rs_bindings()` instead.
fn find_header_path() -> Option<PathBuf> {
    // First try pkg-config
    if let Ok(lib) = Config::new().probe("trexio") {
        // pkg-config returns include paths, we need to append trexio.h
        for include_path in lib.include_paths {
            let header_path = include_path.join("trexio.h");
            if header_path.exists() {
                return Some(header_path);
            }
        }
    }

    // Try environment variable next
    if let Ok(dir) = env::var("TREXIO_INCLUDE_DIR") {
        let path = PathBuf::from(dir).join("trexio.h");
        if path.exists() {
            return Some(path);
        }
    }

    // Finally check common system paths
    let possible_paths = vec![
        "/usr/include/trexio.h",
        "/usr/local/include/trexio.h",
        "/opt/local/include/trexio.h",
    ];

    for path in possible_paths {
        let p = PathBuf::from(path);
        if p.exists() {
            return Some(p);
        }
    }

    None
}


/// This function reads from `trexio.h`, extracts the exit codes and backends, and writes them to `wrapper.h`.
fn make_interface(trexio_h: &PathBuf) -> io::Result<()> {
    let mut err = HashMap::new();
    let mut be = HashMap::new();

    let trexio_file = File::open(trexio_h)?;
    let trexio_reader = BufReader::new(trexio_file);

    for line in trexio_reader.lines() {
        let line = line?;
        let buf = line.trim_start();

        if buf.starts_with("#define TREXIO_") && buf.contains("(trexio_exit_code)") {
            let buf2 = buf.replace(")", "");
            let buf2 = buf2.replace("(", "");
            let buf2: Vec<&str> = buf2.split_whitespace().collect();
            err.insert(buf2[1].to_string(), buf2[3].trim().parse::<i32>().unwrap());
        }

        if buf.starts_with("#define TREXIO_") && buf.contains("(back_end_t)") {
            let buf2 = buf.replace(")", "");
            let buf2 = buf2.replace("(", "");
            let buf2: Vec<&str> = buf2.split_whitespace().collect();
            be.insert(buf2[1].to_string(), buf2[3].trim().parse::<i32>().unwrap());
        }
    }

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    let wrapper_h = out_path.join(WRAPPER_H);
    let mut wrapper_file = File::create(wrapper_h)?;
    write!(&mut wrapper_file, "#include <trexio.h>\n")?;

    for (k, v) in &err {
        write!(&mut wrapper_file, "#undef {}\n", k)?;
        write!(&mut wrapper_file, "const trexio_exit_code {} = {};\n", k, v)?;
    }

    for (k, v) in &be {
        write!(&mut wrapper_file, "#undef {}\n", k)?;
        write!(&mut wrapper_file, "const back_end_t {} = {};\n", k, v)?;
    }

    write!(&mut wrapper_file, "#undef TREXIO_AUTO\n")?;
    write!(&mut wrapper_file, "const back_end_t TREXIO_AUTO = TREXIO_INVALID_BACK_END;\n")?;

    Ok(())
}


/// Type conversions for Rust API
fn convert_r(typ: &str) -> String {
    match typ {
        "int" => "i64",
        "int special" => "usize",
        "float" | "float sparse" | "float buffered" => "f64",
        "dim" | "dim readonly" | "index" => "usize",
        "str" => "str",
        _ => panic!("Unknown type to convert: {}", typ)
    }.to_string()
}

/// Type conversion to call C functions
fn convert_c(typ: &str) -> String {
    match typ {
        "int" | "int special" | "dim" | "dim readonly" | "index" => "i64",
        "float" | "float sparse" | "float buffered" => "f64",
        "str" => "str",
        _ => panic!("Unknown type to convert: {}", typ)
    }.to_string()
}


/// Generate has-functions for checking the existence of groups and elements in a TREXIO file.
///
/// # Parameters
/// * `data` - The JSON-like data containing the groups and elements.
///
/// # Returns
/// A `Vec<String>` containing the generated Rust code as strings.
fn make_has_functions(data: &Value) -> Vec<String> {
    let mut r = Vec::new();

    if let Value::Object(groups) = data {
        for (group, elements) in groups.iter() {
            let group_l = group.to_lowercase();

            let has_group_func = format!(
                "/// Checks if the group `{group}` exists in the file.
/// # Parameters
///
/// None
///
/// # Returns
///
/// * `Result<bool, ExitCode>` - Returns `Ok(true)` if the element exists in the file,
/// otherwise returns `Ok(false)`. An error during the execution results in `Err(ExitCode)`.
pub fn has_{group_l}(&self) -> Result<bool, ExitCode> {{
    let rc = unsafe {{ c::trexio_has_{group}(self.ptr) }};
    match rc {{
        c::TREXIO_SUCCESS   =>  Ok(true),
        c::TREXIO_HAS_NOT   =>  Ok(false),
        x                   =>  Err(ExitCode::from(x)),
    }}
}}");

            r.push(has_group_func);

            if let Value::Object(elements_map) = elements {
                for (element, _types_value) in elements_map.iter() {
                    let element_l = element.to_lowercase();

                    let has_element_func = format!(
                        "/// Checks if the element `{element}` of the group `{group}` exists in the file.
///
/// # Parameters
///
/// None
///
/// # Returns
///
/// * `Result<bool, ExitCode>` - Returns `Ok(true)` if the element exists in the file,
/// otherwise returns `Ok(false)`. An error during the execution results in `Err(ExitCode)`.
pub fn has_{group_l}_{element_l}(&self) -> Result<bool, ExitCode> {{
    let rc = unsafe {{ c::trexio_has_{group}_{element}(self.ptr) }};
    match rc {{
        c::TREXIO_SUCCESS   =>  Ok(true),
        c::TREXIO_HAS_NOT   =>  Ok(false),
        x                   =>  Err(ExitCode::from(x)),
    }}
}}");

                    r.push(has_element_func);
                }
            }
        }
    }
    r
}




fn make_scalar_functions(data: &serde_json::Value) -> Vec<String> {
    let mut r: Vec<String> = Vec::new();

    for group in data.as_object().unwrap().keys() {
        let group_l = group.to_lowercase();

        for (element, attributes) in data[group].as_object().unwrap() {
            let typ = attributes[0].as_str().unwrap();
            let type_c = convert_c(typ);
            let type_r = convert_r(typ);
            let element_l = element.to_lowercase();

            if attributes[1].as_array().unwrap().is_empty() {
                match typ {
                    "int" | "float" | "dim" | "index" => {
                        let s = format!(r#"
/// Reads the scalar element `{element}` from the group `{group}` in the file.
///
/// # Parameters
///
/// None
///
/// # Returns
///
/// * `Result<{type_r}, ExitCode>` - Returns the scalar element as a `{type_r}` upon successful
/// operation. If the operation fails, it returns `Err(ExitCode)`.
pub fn read_{group_l}_{element_l}(&self) -> Result<{type_r}, ExitCode> {{
   let mut data_c: {type_c} = 0{type_c};
   let (rc, data) = unsafe {{
      let rc = c::trexio_read_{group}_{element}_64(self.ptr, &mut data_c);
      (rc, data_c.try_into().expect("try_into failed in read_{group_l}_{element_l}"))
   }};
   rc_return(data, rc)
}}

/// Writes the scalar element `{element}` into the group `{group}` in the file.
///
/// # Parameters
///
/// * `data: {type_r}` - A `{type_r}` scalar element that will be written into `{element}` in the group `{group}`.
///
/// # Returns
///
/// * `Result<(), ExitCode>` - Returns `Ok(())` upon successful operation, otherwise returns `Err(ExitCode)`.
pub fn write_{group_l}_{element_l}(&self, data: {type_r}) -> Result<(), ExitCode> {{
    let data: {type_c} = data.try_into().expect("try_into failed in write_{group_l}_{element_l}");
    let rc = unsafe {{ c::trexio_write_{group}_{element}_64(self.ptr, data) }};
    rc_return((), rc)
}}
"#);
                        r.push(s);
                    },
                    "str" => {
                        let s = format!(r#"
/// Reads the string attribute `{element}` contained in the group `{group}`.
/// # Parameters
///
/// * `capacity: usize` - The maximum buffer size allocated for the string to be read.
///
/// # Returns
///
/// * `Result<String, ExitCode>` - Returns the attribute as a `String` upon successful operation.
///   If the operation fails, it returns `Err(ExitCode)`.
pub fn read_{group_l}_{element_l}(&self, capacity: usize) -> Result<String, ExitCode> {{
   let data_c = CString::new(vec![ b' ' ; capacity]).expect("CString::new failed");
   let (rc, data) = unsafe {{
      let data_c = data_c.into_raw() as *mut c_char;
      let rc = c::trexio_read_{group}_{element}(self.ptr, data_c, capacity.try_into().expect("try_into failed in read_{group_l}_{element_l}"));
      (rc, CString::from_raw(data_c))
   }};
   let result : String = CString::into_string(data).expect("into_string failed in read_{group_l}_{element_l}");
   rc_return(result, rc)
}}


/// Writes the string attribute `{element}` into the group `{group}`.
///
/// # Parameters
///
/// * `data: &str` - The string attribute that will be written into the `{element}` field in the `{group}` group.
///
/// # Returns
///
/// * `Result<(), ExitCode>` - Returns `Ok(())` upon successful operation.
///   If the operation fails, it returns `Err(ExitCode)`.
pub fn write_{group_l}_{element_l}(&self, data: &str) -> Result<(), ExitCode> {{
    let size : i32 = data.len().try_into().expect("try_into failed in write_{group_l}_{element_l}");
    let data = string_to_c(data);
    let data = data.as_ptr() as *const c_char;
    let rc = unsafe {{ c::trexio_write_{group}_{element}(self.ptr, data, size) }};
    rc_return((), rc)
}}
"#);
                        r.push(s);
                    },
                    "dim readonly" => {
                        let s = format!(r#"
/// Reads the dimensioning variable `{element}` from the group `{group}`.
///
/// # Parameters
///
/// None.
///
/// # Returns
///
/// * `Result<{type_r}, ExitCode>` - Returns the dimensioning variable `{element}` of type `{type_r}`
///   upon successful operation. If the operation fails, it returns `Err(ExitCode)`.
pub fn read_{group_l}_{element_l}(&self) -> Result<{type_r}, ExitCode> {{
   let mut data_c: {type_c} = 0{type_c};
   let (rc, data) = unsafe {{
      let rc = c::trexio_read_{group}_{element}_64(self.ptr, &mut data_c);
      (rc, data_c.try_into().expect("try_into failed in read_{group_l}_{element_l}"))
   }};
   rc_return(data, rc)
}}
"#);
                        r.push(s);
                    },
                    _ => {}
                }
            }
        }
    }
    r
}



fn make_array_functions(data: &serde_json::Value) -> Vec<String> {
    let mut r: Vec<String> = Vec::new();

    for group in data.as_object().unwrap().keys() {
        let group_l = group.to_lowercase();

        for (element, attributes) in data[group].as_object().unwrap() {
            let typ = attributes[0].as_str().unwrap();
            let type_c = convert_c(typ);
            let type_r = convert_r(typ);
            let element_l = element.to_lowercase();
            let dimensions = attributes[1].as_array().unwrap();
            let dimensions: Vec<&str> = dimensions.iter().map(|x| x.as_str().unwrap()).collect();
            let dimensions_str = format!("{:?}", dimensions).replace("\"","");
            if ! dimensions.is_empty() {
                match typ {
                    "int" | "float" | "dim" | "index" => {
                        r.push(format!(r#"
/// Reads the `{element}` array from the group `{group}` in the file.
///
/// # Dimensions
///
/// The array is of dimension `{dimensions_str}`.
///
/// # Returns
///
/// * `Result<Vec<{type_r}>, ExitCode>` - Returns a flattened one-dimensional vector that contains
/// the elements of the `{element}` array. If the operation is unsuccessful, it returns `Err(ExitCode)`.
///
///"#));
                        if dimensions.len() > 1 {
                            r.push(format!(r#"
/// # Example
///
/// To reshape the one-dimensional vector back into a two-dimensional array, you can use the [`chunks`] method:
///
/// ```text
/// let one_d_array = trexio_file.read_{}_{}()?;"#, group_l, element_l));
                            if let Some(dim) = dimensions.first() {
                                if dim.contains('.') {
                                    let parts: Vec<&str> = dim.split('.').collect();
                                    r.push(format!("/// let {}_{} = trexio_file.read_{}_{}()?;", parts[0], parts[1], parts[0], parts[1]));
                                    r.push(format!("/// let two_d_array: Vec<_> = one_d_array.chunks({}_{}).collect();", parts[0], parts[1]));
                                } else {
                                    r.push(format!("/// let two_d_array: Vec<_> = one_d_array.chunks({}).collect();", dim));
                                }
                            }
                            r.push(String::from("/// ```"));
                            r.push(String::from("///\n/// [`chunks`]: slice::chunks"));
                        }
                        r.push(format!(r#"pub fn read_{}_{}(&self) -> Result<Vec<{}>, ExitCode> {{
  let mut size = 1;"#, group_l, element_l, type_r));

                        for dim in &dimensions {
                            if dim.contains('.') {
                                  let parts: Vec<&str> = dim.split('.').collect();
                                  r.push(format!("  size *= self.read_{}_{}()?;", parts[0], parts[1]));
                            } else {
                                  r.push(format!("  size *= {};", dim));
                            }
                        }
                        r.push(format!(r#"   let mut data: Vec<{type_r}> = Vec::with_capacity(size);
   let rc = unsafe {{
      let data_c = data.as_mut_ptr() as *mut {type_c};
      let rc = c::trexio_read_safe_{group}_{element}_64(self.ptr, data_c, size.try_into().expect("try_into failed in read_{group}_{element} (size)"));
      data.set_len(size);
      rc
   }};
   rc_return(data, rc)
}}"#));
                        r.push(format!(r#"
/// Writes the `{element}` array into the group `{group}` in the file.
///
/// # Parameters
///
/// * `data: &[{type_r}]` - A one-dimensional vector that contains the elements of the `{element}` array
/// to be written into the file. The vector should be flattened from a two-dimensional array with
/// dimensions `{dimensions_str}`.
///
/// # Returns
///
/// * `Result<(), ExitCode>` - Returns `Ok(())` if the operation is successful,
/// otherwise returns `Err(ExitCode)`.""", """\
pub fn write_{group_l}_{element_l}(&self, data: &[{type_r}]) -> Result<(), ExitCode> {{
    let size: i64 = data.len().try_into().expect("try_into failed in write_{group_l}_{element_l}");
    let data = data.as_ptr() as *const {type_c};
    let rc = unsafe {{ c::trexio_write_safe_{group}_{element}_64(self.ptr, data, size) }};
    rc_return((), rc)
}}
"#));
                    }
                    ,
                    "str" => {
                        r.push(format!(r#"
/// Reads the `{element}` array from the group `{group}` in the file.
///
/// # Dimensions
///
/// The array is of dimension `{dimensions_str}`.
///
/// # Returns
///
/// * `Result<Vec<{type_r}>, ExitCode>` - Returns a flattened one-dimensional vector that contains
/// the elements of the `{element}` array. If the operation is unsuccessful, it returns `Err(ExitCode)`.
///
/// "#));
                        if dimensions.len() > 1 {
                            r.push(format!(r#"/// # Example
///
/// To reshape the one-dimensional vector back into a two-dimensional array, you can use the [`chunks`] method:
///
/// ```text
/// let one_d_array = trexio_file.read_{}_{}()?;"#, group_l, element_l));
                            if let Some(dim) = dimensions.first() {
                                if dim.contains('.') {
                                    let parts: Vec<&str> = dim.split('.').collect();
                                    r.push(format!("/// let {}_{} = trexio_file.read_{}_{}()?;", parts[0], parts[1], parts[0], parts[1]));
                                    r.push(format!("/// let two_d_array: Vec<_> = one_d_array.chunks({}_{}).collect();", parts[0], parts[1]));
                                } else {
                                    r.push(format!("/// let two_d_array: Vec<_> = one_d_array.chunks({}).collect();", dim));
                                }
                            }
                            r.push(String::from("/// ```"));
                            r.push(String::from("///\n/// [`chunks`]: slice::chunks"));
                        }
                        r.push(format!(r#"pub fn read_{}_{}(&self, capacity: usize) -> Result<Vec<String>, ExitCode> {{
  let mut size = 1;"#, group_l, element_l));
                        for dim in &dimensions {
                            if dim.contains('.') {
                                  let parts: Vec<&str> = dim.split('.').collect();
                                  r.push(format!("  size *= self.read_{}_{}()?;", parts[0], parts[1]));
                            } else {
                                  r.push(format!("  size *= {};", dim));
                            }
                        }
                        r.push(format!(r#"   // Allocate an array of *mut i8 pointers (initialized to null)
    let mut dset_out: Vec<*mut i8> = vec![std::ptr::null_mut(); size];

    // Allocate C-style strings and populate dset_out
    for item in dset_out.iter_mut().take(size) {{
        let c_str: *mut i8 = unsafe {{ std::alloc::alloc_zeroed(std::alloc::Layout::array::<i8>(capacity).unwrap()) as *mut i8 }};
        if c_str.is_null() {{
            return Err(ExitCode::AllocationFailed);
        }}
        *item = c_str;
    }}


   let rc = unsafe {{
      c::trexio_read_{group}_{element}(self.ptr, dset_out.as_mut_ptr(), capacity.try_into().expect("try_into failed in read_{group}_{element} (capacity)") )
   }};

    // Convert the populated C strings to Rust Strings
    let mut rust_strings = Vec::new();
    for &c_str in &dset_out {{
        let rust_str = unsafe {{
            std::ffi::CStr::from_ptr(c_str)
                .to_string_lossy()
                .into_owned()
        }};
        rust_strings.push(rust_str);
    }}

    // Clean up allocated C strings
    for &c_str in &dset_out {{
        unsafe {{ std::alloc::dealloc(c_str as *mut u8, std::alloc::Layout::array::<i8>(capacity).unwrap()) }};
    }}

   rc_return(rust_strings, rc)
}}

/// Writes the `{element}` array into the group `{group}` in the file.
///
/// # Parameters
///
/// * `data: &[{type_r}]` - A one-dimensional vector that contains the elements of the `{element}` array
/// to be written into the file. The vector should be flattened from a two-dimensional array with
/// dimensions `{dimensions_str}`.
///
/// # Returns
///
/// * `Result<(), ExitCode>` - Returns `Ok(())` if the operation is successful,
/// otherwise returns `Err(ExitCode)`.
pub fn write_{group_l}_{element_l}(&self, data: &[&str]) -> Result<(), ExitCode> {{
    let mut size = 0;
    // Find longest string
    for s in data {{
       let l = s.len();
       size = if l>size {{l}} else {{size}};
    }}
    size += 1;
    let data_c : Vec<CString> = data.iter().map(|&x| string_to_c(x)).collect::<Vec<_>>();
    let data_c : Vec<*const c_char> = data_c.iter().map(|x| x.as_ptr() as *const c_char).collect::<Vec<_>>();
    let size : i32 = size.try_into().expect("try_into failed in write_{group}_{element} (size)");
    let data_c = data_c.as_ptr() as *mut *const c_char;
    let rc = unsafe {{ c::trexio_write_{group}_{element}(self.ptr, data_c, size) }};
    rc_return((), rc)
}}
"#));
                    },
                    "float sparse" => {
                        let size = dimensions.len();
                        let typ = [ "(", (vec![ "usize" ; size ]).join(", ").as_str(),", f64)"].join("");
                        r.push(format!(r#"
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
pub fn read_{group_l}_{element_l}(&self, offset: usize, buffer_size:usize) -> Result<Vec<{typ}>, ExitCode> {{
    let size_idx = {size}*buffer_size;
    let mut idx = Vec::<i32>::with_capacity(size_idx);
    let mut val = Vec::<f64>::with_capacity(buffer_size);
    let idx_ptr = idx.as_ptr() as *mut i32;
    let val_ptr = val.as_ptr() as *mut f64;
    let offset: i64 = offset.try_into().expect("try_into failed in read_{group}_{element} (offset)");
    let mut buffer_size_read: i64 = buffer_size.try_into().expect("try_into failed in read_{group}_{element} (buffer_size)");
    let rc = unsafe {{ c::trexio_read_safe_{group}_{element}(self.ptr,
           offset, &mut buffer_size_read, idx_ptr, size_idx.try_into().unwrap(), val_ptr, buffer_size.try_into().unwrap())
    }};
    let rc = match ExitCode::from(rc) {{
              ExitCode::End => ExitCode::to_c(&ExitCode::Success),
              _       => rc
            }};
    let buffer_size_read: usize = buffer_size_read.try_into().expect("try_into failed in read_{group}_{element} (buffer_size)");
    unsafe {{ idx.set_len({size}*buffer_size_read) }};
    unsafe {{ val.set_len(buffer_size_read) }};
    let idx: Vec::<&[i32]> = idx.chunks({size}).collect();

    let mut result = Vec::<{typ}>::with_capacity(buffer_size);
    for (i, v) in zip(idx, val) {{
      result.push( ("#));
                        let mut x = Vec::new();
                        for k in 0..size {
                            x.push(format!("i[{k}].try_into().unwrap()"))
                        };
                        x.push("v));\n    }\n    rc_return(result, rc)\n}".to_string());
                        r.push(x.join(", "));
                        r.push(format!(r#"/// Writes a buffer of {element} from group {group}.
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
pub fn write_{group_l}_{element_l}(&self, offset: usize, data: &[{typ}]) -> Result<(), ExitCode> {{
    let mut idx = Vec::<i32>::with_capacity({size}*data.len());
    let mut val = Vec::<f64>::with_capacity(data.len());

    for d in data {{ "#));
                        let mut x = Vec::new();
                        for k in 0..size {
                            x.push(format!("       idx.push(d.{k}.try_into().unwrap());"))
                        };
                        r.push(x.join("\n"));
                        r.push(format!(r#"
      val.push(d.{size});
    }}

    let size_max: i64 = data.len().try_into().expect("try_into failed in write_{group}_{element} (size_max)");
    let size_max_val: i64 = val.len().try_into().expect("try_into failed in write_{group}_{element} (size_max)");
    let size_max_idx: i64 = idx.len().try_into().expect("try_into failed in write_{group}_{element} (size_max)");
    let buffer_size = size_max;
    let idx_ptr = idx.as_ptr() as *const i32;
    let val_ptr = val.as_ptr() as *const f64;
    let offset: i64 = offset.try_into().expect("try_into failed in write_{group}_{element} (offset)");
    let rc = unsafe {{ c::trexio_write_safe_{group}_{element}(self.ptr,
           offset, buffer_size, idx_ptr, size_max_idx, val_ptr, size_max_val) }};
    rc_return((), rc)
}}"#));
                    },
                    _ => {}
                }
            }
        }
    }
    r
}




fn extract_json(trexio_h: &PathBuf) -> io::Result<()> {
     // Read the header file
    let file = File::open(&trexio_h)?;
    let reader = BufReader::new(file);

    // Extract JSON configuration
    let mut in_json = false;
    let mut json_content = String::new();

    for line in reader.lines() {
        let line = line?;

        if line.contains("/* JSON configuration") {
            in_json = true;
            continue;
        }

        if in_json {
            if line.contains("*/") {
                break;
            }
            json_content.push_str(&line);
            json_content.push('\n');
        }
    }

   // Write JSON to output file
    let out_dir = env::var("OUT_DIR").unwrap();
    let json_path = PathBuf::from(out_dir).join("trex.json");

    let mut output_file = File::create(json_path)?;
    output_file.write_all(json_content.as_bytes())?;

    // Tell cargo to rerun if the header file changes
    println!("cargo:rerun-if-changed={}", trexio_h.display());

    // Rerun if relevant env vars change
    println!("cargo:rerun-if-env-changed=TREXIO_INCLUDE_DIR");
    println!("cargo:rerun-if-env-changed=PKG_CONFIG_PATH");

    Ok(())
}





/// Reads the JSON file, processes its contents, and generates Rust functions according to the specifications in the JSON data.
fn make_functions(json_path: &PathBuf) -> std::io::Result<()> {
    let file = File::open(json_path).unwrap();
    let data: Value = serde_json::from_reader(file).unwrap();

    let mut r: Vec<String> = vec![
        String::from("
use std::ffi::CString;
use std::iter::zip;

/// This implementation block includes additional functions automatically generated from tables.
/// For more details, refer to [TREXIO tables documentation](https://trex-coe.github.io/trexio/trex.html).
impl File {
    #![allow(clippy::unnecessary_cast)]
    #![allow(clippy::useless_conversion)]
    #![allow(clippy::type_complexity)]
"),
    ];

    r.append(&mut make_has_functions(&data));
    r.append(&mut make_scalar_functions(&data));
    r.append(&mut make_array_functions(&data));

    r.push(String::from("}"));

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    let generated_rs = out_path.join(GENERATED_RS);
    let mut f = File::create(&generated_rs)?;
    f.write_all(r.join("\n").as_bytes())?;
    Ok(())
}





/// Generates a minimal `bindings.rs` stub for documentation builds on docs.rs.
///
/// When the `DOCS_RS` environment variable is set (as it is on the docs.rs build
/// infrastructure), the C trexio library is not available. This function writes a
/// self-contained `bindings.rs` that contains:
///
/// - The TREXIO C type aliases (`trexio_exit_code`, `back_end_t`, `trexio_t`, …)
/// - All exit-code and back-end constants, hard-coded from the TREXIO 2.x API
/// - The small set of non-schema C function declarations used by `lib.rs` and `bitfield.rs`
/// - Schema-derived `trexio_has_*`, `trexio_read_*` and `trexio_write_*` declarations
///   generated from the bundled `trexio_for_docs_rs.json` schema file
///
/// The resulting stub is enough for `rustdoc` to type-check and document the crate
/// without a system trexio installation.
fn make_docs_rs_bindings(json_fallback: &PathBuf, out_path: &PathBuf) -> io::Result<()> {
    let bindings_path = out_path.join("bindings.rs");
    let mut f = File::create(&bindings_path)?;

    // --- Types ---
    write!(f, "// Auto-generated stub for docs.rs builds. Do not edit manually.\n\n")?;
    write!(f, "pub type trexio_exit_code = i32;\n")?;
    write!(f, "pub type back_end_t = i32;\n")?;
    write!(f, "pub type bitfield_t = i64;\n")?;
    write!(f, "#[repr(C)]\n#[derive(Debug, Copy, Clone)]\npub struct trexio_s {{ _unused: [u8; 0] }}\n")?;
    write!(f, "pub type trexio_t = trexio_s;\n\n")?;

    // --- TREXIO_PACKAGE_VERSION (use Cargo package version) ---
    let pkg_ver = env::var("CARGO_PKG_VERSION").unwrap_or_else(|_| "0.0.0".to_string());
    let ver_len = pkg_ver.len() + 1; // +1 for null terminator
    write!(f, "pub const TREXIO_PACKAGE_VERSION: &[u8; {ver_len}usize] = b\"{pkg_ver}\\0\";\n\n")?;

    // --- Exit-code constants (TREXIO 2.x, from trexio.h) ---
    let exit_codes: &[(&str, i32)] = &[
        ("TREXIO_FAILURE",                -1),
        ("TREXIO_SUCCESS",                 0),
        ("TREXIO_INVALID_ARG_1",           1),
        ("TREXIO_INVALID_ARG_2",           2),
        ("TREXIO_INVALID_ARG_3",           3),
        ("TREXIO_INVALID_ARG_4",           4),
        ("TREXIO_INVALID_ARG_5",           5),
        ("TREXIO_END",                     6),
        ("TREXIO_READONLY",                7),
        ("TREXIO_ERRNO",                   8),
        ("TREXIO_INVALID_ID",              9),
        ("TREXIO_ALLOCATION_FAILED",      10),
        ("TREXIO_HAS_NOT",                11),
        ("TREXIO_INVALID_NUM",            12),
        ("TREXIO_ATTR_ALREADY_EXISTS",    13),
        ("TREXIO_DSET_ALREADY_EXISTS",    14),
        ("TREXIO_OPEN_ERROR",             15),
        ("TREXIO_LOCK_ERROR",             16),
        ("TREXIO_UNLOCK_ERROR",           17),
        ("TREXIO_FILE_ERROR",             18),
        ("TREXIO_GROUP_READ_ERROR",       19),
        ("TREXIO_GROUP_WRITE_ERROR",      20),
        ("TREXIO_ELEM_READ_ERROR",        21),
        ("TREXIO_ELEM_WRITE_ERROR",       22),
        ("TREXIO_UNSAFE_ARRAY_DIM",       23),
        ("TREXIO_ATTR_MISSING",           24),
        ("TREXIO_DSET_MISSING",           25),
        ("TREXIO_BACK_END_MISSING",       26),
        ("TREXIO_INVALID_ARG_6",          27),
        ("TREXIO_INVALID_ARG_7",          28),
        ("TREXIO_INVALID_ARG_8",          29),
        ("TREXIO_INVALID_STR_LEN",        30),
        ("TREXIO_INT_SIZE_OVERFLOW",      31),
        ("TREXIO_SAFE_MODE",              32),
        ("TREXIO_INVALID_ELECTRON_NUM",   33),
        ("TREXIO_INVALID_DETERMINANT_NUM",34),
        ("TREXIO_INVALID_STATE",          35),
        ("TREXIO_VERSION_PARSING_ISSUE",  36),
        ("TREXIO_PHASE_CHANGE",           37),
        ("TREXIO_INVALID_MO_INDEX",       38),
        ("TREXIO_INVALID_ARG_9",          39),
        ("TREXIO_INVALID_ARG_10",         40),
        ("TREXIO_INVALID_ARG_11",         41),
        ("TREXIO_INVALID_ARG_12",         42),
        ("TREXIO_INVALID_ARG_13",         43),
        ("TREXIO_INVALID_ARG_14",         44),
        ("TREXIO_CORRUPTION_ATTEMPT",     45),
    ];
    for (name, val) in exit_codes {
        write!(f, "pub const {name}: trexio_exit_code = {val};\n")?;
    }
    write!(f, "\n")?;

    // --- Back-end constants ---
    write!(f, "pub const TREXIO_HDF5: back_end_t = 0;\n")?;
    write!(f, "pub const TREXIO_TEXT: back_end_t = 1;\n")?;
    write!(f, "pub const TREXIO_INVALID_BACK_END: back_end_t = 2;\n")?;
    write!(f, "pub const TREXIO_AUTO: back_end_t = 2;\n\n")?;

    // --- Fixed non-schema C function declarations ---
    write!(f, "extern \"C\" {{\n")?;
    write!(f, "    pub fn trexio_string_of_error(error: trexio_exit_code) -> *const ::std::os::raw::c_char;\n")?;
    write!(f, "    pub fn trexio_open(file_name: *const ::std::os::raw::c_char, mode: ::std::os::raw::c_char, back_end: back_end_t, rc_open: *mut trexio_exit_code) -> *mut trexio_t;\n")?;
    write!(f, "    pub fn trexio_close(file: *mut trexio_t) -> trexio_exit_code;\n")?;
    write!(f, "    pub fn trexio_inquire(file_name: *const ::std::os::raw::c_char) -> trexio_exit_code;\n")?;
    write!(f, "    pub fn trexio_get_state(file: *mut trexio_t, num: *mut i32) -> trexio_exit_code;\n")?;
    write!(f, "    pub fn trexio_set_state(file: *mut trexio_t, num: i32) -> trexio_exit_code;\n")?;
    write!(f, "    pub fn trexio_get_int64_num(file: *mut trexio_t, num: *mut i32) -> trexio_exit_code;\n")?;
    write!(f, "    pub fn trexio_write_determinant_list(file: *mut trexio_t, offset: i64, buffer_size: i64, dset: *const i64) -> trexio_exit_code;\n")?;
    write!(f, "    pub fn trexio_read_determinant_list(file: *mut trexio_t, offset: i64, buffer_size: *mut i64, dset: *mut i64) -> trexio_exit_code;\n")?;
    write!(f, "    pub fn trexio_info() -> trexio_exit_code;\n")?;
    write!(f, "    pub fn trexio_to_orbital_list(n_int: i32, d1: *const bitfield_t, list: *mut i32, occupied_num: *mut i32) -> trexio_exit_code;\n")?;
    write!(f, "    pub fn trexio_to_orbital_list_up_dn(n_int: i32, d1: *const bitfield_t, list_up: *mut i32, list_dn: *mut i32, occ_num_up: *mut i32, occ_num_dn: *mut i32) -> trexio_exit_code;\n")?;
    write!(f, "    pub fn trexio_to_bitfield_list(orb_list: *const i32, occupied_num: i32, bit_list: *mut bitfield_t, n_int: i32) -> trexio_exit_code;\n")?;
    write!(f, "}}\n\n")?;

    // --- Schema-derived C function declarations (from trexio_for_docs_rs.json) ---
    let schema_file = File::open(json_fallback)?;
    let data: Value = serde_json::from_reader(schema_file)
        .map_err(|e| io::Error::new(io::ErrorKind::InvalidData, e))?;

    let groups = data.as_object().ok_or_else(|| {
        io::Error::new(io::ErrorKind::InvalidData, "JSON root is not an object")
    })?;

    for (group, elements) in groups {
        // trexio_has_{Group}
        write!(f, "extern \"C\" {{\n")?;
        write!(f, "    pub fn trexio_has_{group}(file: *mut trexio_t) -> trexio_exit_code;\n")?;
        write!(f, "}}\n")?;

        let elements_map = match elements.as_object() {
            Some(m) => m,
            None => continue,
        };

        for (element, attrs) in elements_map {
            let typ = match attrs[0].as_str() {
                Some(t) => t,
                None => continue,
            };
            let dimensions = attrs[1].as_array().unwrap();
            let is_array = !dimensions.is_empty();

            // trexio_has_{Group}_{Element}
            write!(f, "extern \"C\" {{\n")?;
            write!(f, "    pub fn trexio_has_{group}_{element}(file: *mut trexio_t) -> trexio_exit_code;\n")?;
            write!(f, "}}\n")?;

            match (typ, is_array) {
                // Scalar int/dim/index/dim_readonly → _64 variants using i64
                ("int" | "dim" | "index", false) => {
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_read_{group}_{element}_64(file: *mut trexio_t, val: *mut i64) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_write_{group}_{element}_64(file: *mut trexio_t, val: i64) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                },
                // Scalar dim readonly → read-only _64 variant using i64
                ("dim readonly", false) => {
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_read_{group}_{element}_64(file: *mut trexio_t, val: *mut i64) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                },
                // Scalar float → _64 variants using f64
                ("float", false) => {
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_read_{group}_{element}_64(file: *mut trexio_t, val: *mut f64) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_write_{group}_{element}_64(file: *mut trexio_t, val: f64) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                },
                // Scalar string
                ("str", false) => {
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_read_{group}_{element}(file: *mut trexio_t, buf: *mut ::std::os::raw::c_char, max_str_len: i32) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_write_{group}_{element}(file: *mut trexio_t, buf: *const ::std::os::raw::c_char, size: i32) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                },
                // Array int/dim/index → safe _64 variants using i64
                ("int" | "dim" | "index", true) => {
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_read_safe_{group}_{element}_64(file: *mut trexio_t, dset_out: *mut i64, dim_out: i64) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_write_safe_{group}_{element}_64(file: *mut trexio_t, dset_in: *const i64, dim_in: i64) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                },
                // Array float → safe _64 variants using f64
                ("float", true) => {
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_read_safe_{group}_{element}_64(file: *mut trexio_t, dset_out: *mut f64, dim_out: i64) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_write_safe_{group}_{element}_64(file: *mut trexio_t, dset_in: *const f64, dim_in: i64) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                },
                // Array string
                ("str", true) => {
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_read_{group}_{element}(file: *mut trexio_t, dset: *mut *mut ::std::os::raw::c_char, capacity: i32) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_write_{group}_{element}(file: *mut trexio_t, dset: *mut *const ::std::os::raw::c_char, size: i32) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                },
                // Sparse float (float sparse / float buffered) → safe variants without _64
                ("float sparse" | "float buffered", true) => {
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_read_safe_{group}_{element}(file: *mut trexio_t, offset: i64, buffer_size: *mut i64, idx: *mut i32, size_max_idx: i64, val: *mut f64, size_max_val: i64) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                    write!(f, "extern \"C\" {{\n")?;
                    write!(f, "    pub fn trexio_write_safe_{group}_{element}(file: *mut trexio_t, offset: i64, buffer_size: i64, idx: *const i32, size_max_idx: i64, val: *const f64, size_max_val: i64) -> trexio_exit_code;\n")?;
                    write!(f, "}}\n")?;
                },
                // int special and other unhandled types: only has_* needed (already written above)
                _ => {},
            }
        }
    }

    Ok(())
}


fn main() -> Result<(), Box<dyn std::error::Error>>  {
    let out_path = PathBuf::from(env::var("OUT_DIR")?);

    // When building on docs.rs (DOCS_RS env var is set), the C trexio library is not
    // available. Use the bundled trexio_for_docs_rs.json schema and a generated bindings
    // stub so that `rustdoc` can type-check and document the crate without a system install.
    if env::var("DOCS_RS").is_ok() {
        let src_dir = env::current_dir()?;
        let json_fallback = src_dir.join("trexio_for_docs_rs.json");
        if !json_fallback.exists() {
            return Err(format!(
                "trexio_for_docs_rs.json not found in {}. \
                 This file must be present for docs.rs builds.",
                src_dir.display()
            ).into());
        }
        println!("cargo:warning=docs.rs build: using trexio_for_docs_rs.json");
        let json_path = out_path.join("trex.json");
        std::fs::copy(&json_fallback, &json_path)?;
        make_docs_rs_bindings(&json_fallback, &out_path)?;
        make_functions(&json_path)?;
        println!("cargo:rerun-if-changed=trexio_for_docs_rs.json");
        return Ok(());
    }

    let trexio_h = find_header_path()
        .ok_or("Could not find trexio.h - please ensure trexio is installed and findable via pkg-config, TREXIO_INCLUDE_DIR, or in system paths")?;

    // Print some helpful information during build
    println!("cargo:warning=Found trexio.h at: {}", trexio_h.display());

    make_interface(&trexio_h)?;
    extract_json(&trexio_h)?;

    // The bindgen::Builder is the main entry point
    // to bindgen, and lets you build up options for
    // the resulting bindings.
    let wrapper_h = out_path.join(WRAPPER_H);
    println!("wrapper.h: {}", wrapper_h.display());

    let bindings = bindgen::Builder::default()
        // The input header we would like to generate
        // bindings for.
        .header(wrapper_h.to_str().unwrap())
        // Add the directory containing trexio.h to the clang include search path.
        // This is essential when using the bundled fallback header (e.g. on docs.rs)
        // where trexio.h is not installed in a system include directory.
        .clang_arg(format!("-I{}", trexio_h.parent().unwrap().to_str().unwrap()))
        // Tell cargo to invalidate the built crate whenever any of the
        // included header files changed.
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        // Finish the builder and generate the bindings.
        .generate()
        // Unwrap the Result and panic on failure.
        .expect("Unable to generate bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let bindings_path = out_path.join("bindings.rs");
    println!("bindings.rs: {}", bindings_path.display());

    bindings
        .write_to_file(&bindings_path)
        .expect("Couldn't write bindings!");

    let json_path = out_path.join("trex.json");
    println!("json path: {}", json_path.display());

    make_functions(&json_path).unwrap();
    Ok(())
}
