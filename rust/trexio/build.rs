extern crate reqwest;
extern crate tar;
extern crate flate2;

const WRAPPER_H: &str = "wrapper.h";
const GENERATED_RS: &str = "generated.rs";

use std::env;
use std::path::PathBuf;
use std::collections::HashMap;
use std::fs::File;
use std::io::{self, BufRead, BufReader, Write};
use serde_json::Value;
use flate2::read::GzDecoder;
use tar::Archive;



fn download_trexio() -> PathBuf {
    let version = env::var("CARGO_PKG_VERSION").unwrap();
    println!("Version : {}", version);

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    let trexio_url = format!("https://github.com/TREX-CoE/trexio/releases/download/v{version}/trexio-{version}.tar.gz");

    // Download the .tar.gz archive
    let tar_gz = out_path.join("trexio.tar.gz");
    let trexio_dir= out_path.join("trexio_dir");
    let mut resp = reqwest::blocking::get(trexio_url).expect("Failed to download the archive");
    let mut out = File::create(tar_gz.clone()).expect("Failed to create archive file");
    std::io::copy(&mut resp, &mut out).expect("Failed to copy content");

    // Unpack the .tar.gz archive
    let tar_gz = File::open(tar_gz).unwrap();
    let tar = GzDecoder::new(tar_gz);
    let mut archive = Archive::new(tar);
    archive.unpack(trexio_dir.clone()).expect("Failed to unpack");

    // Assume that the archive extracts to a directory named 'trexio-0.1.0'
    trexio_dir.join(format!("trexio-{}", version))
}


fn install_trexio(trexio_dir: &PathBuf) -> PathBuf {
    println!("{}", trexio_dir.display());
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    let install_path = out_path.join("trexio_install");

    // Run configure script
    let configure_status = std::process::Command::new("./configure")
        .arg(format!("--prefix={}",install_path.display()))
        .arg("--without-fortran")
        .current_dir(&trexio_dir)
        .status()
        .unwrap();

    assert!(configure_status.success());

    // Run make
    let make_status = std::process::Command::new("make")
        .arg("install")
        .current_dir(&trexio_dir)
        .status()
        .unwrap();

    assert!(make_status.success());
    install_path
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
                        r.push(format!(r#"   // Allocate an array of pointers to C strings (initialized to null).
    // c_char is what bindgen uses for char, and it is not the same type
    // everywhere: char is signed on x86-64 and unsigned on aarch64, so spelling
    // this i8 would only compile on some machines.
    use std::os::raw::c_char;
    let mut dset_out: Vec<*mut c_char> = vec![std::ptr::null_mut(); size];

    // Allocate C-style strings and populate dset_out
    for item in dset_out.iter_mut().take(size) {{
        let c_str: *mut c_char = unsafe {{ std::alloc::alloc_zeroed(std::alloc::Layout::array::<c_char>(capacity).unwrap()) as *mut c_char }};
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
        unsafe {{ std::alloc::dealloc(c_str as *mut u8, std::alloc::Layout::array::<c_char>(capacity).unwrap()) }};
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
    let mut idx = Vec::<i32>::with_capacity({size}*buffer_size);
    let mut val = Vec::<f64>::with_capacity(buffer_size);
    let idx_ptr = idx.as_ptr() as *mut i32;
    let val_ptr = val.as_ptr() as *mut f64;
    let offset: i64 = offset.try_into().expect("try_into failed in read_{group}_{element} (offset)");
    let mut buffer_size_read: i64 = buffer_size.try_into().expect("try_into failed in read_{group}_{element} (buffer_size)");
    // The index array holds {size} indices per element, and the C API checks the
    // size it is given against that, not against the number of elements.
    let size_index: i64 = {size} * buffer_size_read;
    let rc = unsafe {{ c::trexio_read_safe_{group}_{element}(self.ptr,
           offset, &mut buffer_size_read, idx_ptr, size_index, val_ptr, buffer_size_read)
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
    let buffer_size = size_max;
    // The index array holds {size} indices per element, and the C API checks the
    // size it is given against that, not against the number of elements.
    let size_index: i64 = {size} * size_max;
    let idx_ptr = idx.as_ptr() as *const i32;
    let val_ptr = val.as_ptr() as *const f64;
    let offset: i64 = offset.try_into().expect("try_into failed in write_{group}_{element} (offset)");
    let rc = unsafe {{ c::trexio_write_safe_{group}_{element}(self.ptr,
           offset, buffer_size, idx_ptr, size_index, val_ptr, size_max) }};
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





fn main() {
    // By default a released TREXIO is downloaded and built here, so that the
    // crate can be published on its own. TREXIO_DIR overrides that with the
    // prefix of an existing installation, and TREXIO_SRC with the source
    // directory holding trex.json; that is how the CI tests these bindings
    // against the tree they are shipped in rather than against the last
    // release. The two default to each other's usual layout.
    for var in ["TREXIO_DIR", "TREXIO_INCLUDE_DIR", "TREXIO_LIB_DIR", "TREXIO_SRC"] {
        println!("cargo:rerun-if-env-changed={var}");
    }

    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    let prefix = env::var("TREXIO_DIR").ok().map(PathBuf::from);
    let include_dir = env::var("TREXIO_INCLUDE_DIR").ok().map(PathBuf::from);
    let lib_dir = env::var("TREXIO_LIB_DIR").ok().map(PathBuf::from);

    // A build tree is not a prefix -- the headers are in the source directory and
    // the library under src/.libs -- so the two directories can also be given
    // separately, which is what the TREXIO build systems do.
    let existing = prefix.is_some() || (include_dir.is_some() && lib_dir.is_some());

    let (include_dirs, lib_dirs, source_path) = if existing {
        // trex.json is not installed, so it comes from the source or build tree:
        // the crate sits in rust/trexio, two levels below the top.
        let source_path = env::var("TREXIO_SRC")
            .map(PathBuf::from)
            .unwrap_or_else(|_| manifest_dir.join("..").join(".."));
        let mut include_dirs = Vec::new();
        let mut lib_dirs = Vec::new();
        if let Some(dir) = include_dir {
            include_dirs.push(dir);
        }
        if let Some(dir) = lib_dir {
            lib_dirs.push(dir);
        }
        if let Some(prefix) = prefix {
            include_dirs.push(prefix.join("include"));
            // Both names, because Autotools and CMake pick lib or lib64
            // according to the distribution.
            lib_dirs.push(prefix.join("lib"));
            lib_dirs.push(prefix.join("lib64"));
        }
        (include_dirs, lib_dirs, source_path)
    } else {
        let source_path = download_trexio();
        let install_path = install_trexio(&source_path);
        (
            vec![install_path.join("include")],
            vec![install_path.join("lib")],
            source_path,
        )
    };
    println!("source path: {}", source_path.display());

    for dir in &lib_dirs {
        println!("cargo:rustc-link-search={}", dir.display());
    }

    // Tell cargo to tell rustc to link the system trexio shared library.
    println!("cargo:rustc-link-lib=trexio");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    let trexio_h = include_dirs
        .iter()
        .map(|dir| dir.join("trexio.h"))
        .find(|header| header.exists())
        .unwrap_or_else(|| {
            panic!(
                "trexio.h was not found in any of {include_dirs:?}. Set TREXIO_DIR to \
                 an installation prefix, or TREXIO_INCLUDE_DIR and TREXIO_LIB_DIR to \
                 a build tree."
            )
        });
    println!("trexio.h: {}", trexio_h.display());

    make_interface(&trexio_h).unwrap();
    // The bindgen::Builder is the main entry point
    // to bindgen, and lets you build up options for
    // the resulting bindings.
    let wrapper_h = out_path.join(WRAPPER_H);
    println!("wrapper.h: {}", wrapper_h.display());

    let bindings = bindgen::Builder::default()
        // The input header we would like to generate
        // bindings for.
        .header(wrapper_h.to_str().unwrap())
        // wrapper.h includes <trexio.h>, which is not anywhere clang looks by
        // default.
        .clang_args(
            include_dirs
                .iter()
                .map(|dir| format!("-I{}", dir.display())),
        )
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

    let json_path = source_path.join("trex.json");
    println!("json path: {}", json_path.display());

    make_functions(&json_path).unwrap();
}
