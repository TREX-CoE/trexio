const TREXIO_H: &str = "../../include/trexio.h";
const WRAPPER_H: &str = "wrapper.h";
const JSON_FILE: &str = "../../trex.json";
const GENERATED_RS: &str = "src/generated.rs";

use std::env;
use std::path::PathBuf;
use std::collections::HashMap;
use std::fs::File;
use std::io::{self, BufRead, BufReader, Write};
use serde_json::Value;
use std::path::Path;




/// Checks that the version specified in the Cargo.toml file is consistent with the version of the TREXIO C library.
fn check_version() -> Result<(), String> {
    // Read version from Cargo.toml
    let mut rust_version = String::new();
    {
        let file = File::open("Cargo.toml").map_err(|e| e.to_string())?;
        let reader = io::BufReader::new(file);

        for line in reader.lines() {
            let line = line.map_err(|e| e.to_string())?;
            if line.starts_with("version") {
                rust_version = line.split('=').nth(1).unwrap().trim().to_string();
                rust_version = rust_version[1..rust_version.len() - 1].to_string();
                break;
            }
        }
    }

    // Read version from ../../configure.ac
    let mut trexio_version = String::new();
    {
        let file = File::open("../../configure.ac").map_err(|e| e.to_string())?;
        let reader = io::BufReader::new(file);

        for line in reader.lines() {
            let line = line.map_err(|e| e.to_string())?;
            if line.starts_with("AC_INIT") {
                trexio_version = line.split(',').nth(1).unwrap().trim().to_string();
                trexio_version = trexio_version[1..trexio_version.len() - 1].to_string();
                break;
            }
        }
    }

    // Compare versions
    if rust_version != trexio_version {
        eprintln!("Inconsistent versions:\nTREXIO: {}\nRust:   {}\n", trexio_version, rust_version);
        return Err("Inconsistent versions".to_string());
    }

    Ok(())
}



/// This function reads from `trexio.h`, extracts the exit codes and backends, and writes them to `wrapper.h`.
fn make_interface() -> io::Result<()> {
    let mut err = HashMap::new();
    let mut be = HashMap::new();

    let trexio_file = File::open(TREXIO_H)?;
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

    let mut wrapper_file = File::create(WRAPPER_H)?;
    write!(&mut wrapper_file, "#include <trexio.h>\n")?;

    for (k, v) in &err {
        write!(&mut wrapper_file, "#undef {}\n", k)?;
        write!(&mut wrapper_file, "const trexio_exit_code {} = {};\n", k, v)?;
    }

    for (k, v) in &be {
        write!(&mut wrapper_file, "#undef {}\n", k)?;
        write!(&mut wrapper_file, "const back_end_t {} = {};\n", k, v)?;
    }

    write!(&mut wrapper_file, "#undef TREXIO_AUTO;\n")?;
    write!(&mut wrapper_file, "const back_end_t TREXIO_AUTO = TREXIO_INVALID_BACK_END;\n")?;

    Ok(())
}


/// Dictionnary of type conversions
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
}}",
                group = group,
                group_l = group_l
            );
            
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
}}",
                        group = group,
                        group_l = group_l,
                        element = element,
                        element_l = element_l
                    );
                    
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
"#,
                        type_c=type_c, type_r=type_r, group=group, group_l=group_l, element=element, element_l=element_l);
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
"#,
                        group=group, group_l=group_l, element=element, element_l=element_l);
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
"#,
                        type_c=type_c, type_r=type_r, group=group, group_l=group_l, element=element, element_l=element_l);
                        r.push(s);
                    },
                    _ => {}
                }
            }
        }
    }
    r
}












/// Reads the JSON file, processes its contents, and generates Rust functions according to the specifications in the JSON data.
fn make_functions() -> std::io::Result<()> {
    let json_file = Path::new(JSON_FILE);
    let generated_rs = Path::new(GENERATED_RS);

    let data: Value = serde_json::from_reader(File::open(&json_file)?)?;

    let mut r: Vec<String> = vec![
        String::from("
use std::ffi::CString;

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
//    r.append(&mut make_array_functions(&data));

    r.push(String::from("}"));

    let mut f = File::create(&generated_rs)?;
    f.write_all(r.join("\n").as_bytes())?;
    Ok(())
}





fn main() {
    check_version().unwrap();
    make_interface().unwrap();
    make_functions().unwrap();

    // Tell cargo to look for shared libraries in the specified directory
    println!("cargo:rustc-link-search=/usr/local/lib");

    // Tell cargo to tell rustc to link the system trexio shared library.
    println!("cargo:rustc-link-lib=trexio");

    // Tell cargo to invalidate the built crate whenever the wrapper changes
    println!("cargo:rerun-if-changed=wrapper.h");
    println!("cargo:rerun-if-changed=build.py");

    // The bindgen::Builder is the main entry point
    // to bindgen, and lets you build up options for
    // the resulting bindings.
    let bindings = bindgen::Builder::default()
        // The input header we would like to generate
        // bindings for.
        .header("wrapper.h")
        // Tell cargo to invalidate the built crate whenever any of the
        // included header files changed.
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        // Finish the builder and generate the bindings.
        .generate()
        // Unwrap the Result and panic on failure.
        .expect("Unable to generate bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
