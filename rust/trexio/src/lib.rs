//! TREXIO is an open-source file format and library developed for the storage and manipulation of
//! data produced by quantum chemistry calculations. It was designed with the goal of providing a
//! reliable and efficient method of storing and exchanging wave function parameters and matrix
//! elements.
//!
//! For comprehensive documentation, consult: [TREXIO Documentation](https://trex-coe.github.io/trexio/)
//!
//! The C library source code is available on GitHub: [TREXIO GitHub Repository](https://github.com/trex-coe/trexio)
//!

use ::std::os::raw::c_char;

mod c;

/// Enumeration representing the various error codes that might be returned by function calls.
/// These error codes are mapped to those defined in the original C TREXIO library.
pub mod exit_code;
pub use exit_code::ExitCode;
use exit_code::ExitCode::InvalidArg;

/// Enum representing the different backends that TREXIO can employ for data storage.
pub mod back_end;
pub use back_end::BackEnd;

/// Structure representing bit fields. Mainly utilized for encapsulating determinant descriptions.
pub mod bitfield;
pub use bitfield::Bitfield;

/// A constant string representing the package version of the linked C TREXIO library.
pub const PACKAGE_VERSION: &str =
    unsafe { std::str::from_utf8_unchecked(c::TREXIO_PACKAGE_VERSION) };

/// Utility function to convert Rust results into TREXIO exit codes.
fn rc_return<T>(result: T, rc: c::trexio_exit_code) -> Result<T, ExitCode> {
    let rc = ExitCode::from(rc);
    match rc {
        ExitCode::Success => Ok(result),
        x => Err(x),
    }
}

/// Utility function to convert Rust string to C-compatible string.
fn string_to_c(s: &str) -> std::ffi::CString {
    std::ffi::CString::new(s).unwrap()
}

/// Function to print out diagnostic information about the linked C TREXIO library.
pub fn info() -> Result<(), ExitCode> {
    let rc = unsafe { c::trexio_info() };
    rc_return((), rc)
}

/// Type representing a TREXIO file. Wraps a pointer to the underlying C structure.
pub struct File {
    ptr: *mut c::trexio_t,
}

impl File {
    /// Opens a TREXIO file. Returns a `File` instance that can be used for subsequent I/O operations.
    ///
    /// # Parameters
    /// - `file_name`: The path to the TREXIO file.
    /// - `mode`: Specifies the file access mode. `'r'` for read-only, `'w'` for safe write (write
    ///   if the data doesn't exist), `'u'` for unsafe write (update existing data).
    /// - `back_end`: Specifies the backend used for data storage.
    ///
    /// # Returns
    /// - `Result<File, ExitCode>`: `File` instance or an error code.
    pub fn open(file_name: &str, mode: char, back_end: BackEnd) -> Result<File, ExitCode> {
        let file_name_c = string_to_c(file_name);
        let file_name_c = file_name_c.as_ptr() as *const c_char;
        let mode = mode as c_char;
        let back_end = back_end.to_c();
        let rc: *mut c::trexio_exit_code = &mut c::TREXIO_SUCCESS.clone();
        let result = unsafe { c::trexio_open(file_name_c, mode, back_end, rc) };
        let rc = unsafe { *rc };
        rc_return(File { ptr: result }, rc)
    }

    /// Closes the current TREXIO file and releases associated resources.
    ///
    /// # Returns
    /// - `Result<(), ExitCode>`: An error code in case of failure.
    pub fn close(self) -> Result<(), ExitCode> {
        let rc = unsafe { c::trexio_close(self.ptr) };
        rc_return((), rc)
    }

    /// Inquires if a file with the specified name exists.
    ///
    /// # Parameters
    ///
    /// * `file_name: &str` - The name of the file to inquire about.
    ///
    /// # Returns
    ///
    /// * `Result<bool, ExitCode>` - Returns `Ok(true)` if the file exists,
    /// `Ok(false)` otherwise. Returns `Err(ExitCode)` if an error occurs
    /// during the operation.
    pub fn inquire(file_name: &str) -> Result<bool, ExitCode> {
        let file_name_c = string_to_c(file_name);
        let file_name_c = file_name_c.as_ptr() as *const c_char;
        let rc = unsafe { c::trexio_inquire(file_name_c) };
        match ExitCode::from(rc) {
            ExitCode::Failure => Ok(false),
            ExitCode::Success => Ok(true),
            x => Err(x),
        }
    }

    /// Retrieves the ID of the electronic state stored in the file.
    ///
    /// # Parameters
    ///
    /// None
    ///
    /// # Returns
    ///
    /// * `Result<usize, ExitCode>` - Returns the ID as `Ok(usize)` if the operation is successful,
    /// otherwise returns `Err(ExitCode)`.
    pub fn get_state(&self) -> Result<usize, ExitCode> {
        let mut num = 0i32;
        let rc = unsafe { c::trexio_get_state(self.ptr, &mut num) };
        let result: usize = num.try_into().expect("try_into failed in get_state");
        rc_return(result, rc)
    }

    /// Sets the ID of the electronic state to be stored in the file.
    ///
    /// # Parameters
    ///
    /// * `num: usize` - The ID of the electronic state.
    ///
    /// # Returns
    ///
    /// * `Result<(), ExitCode>` - Returns `Ok(())` if the operation is successful,
    /// otherwise returns `Err(ExitCode)`.
    pub fn set_state(&self, num: usize) -> Result<(), ExitCode> {
        let num: i32 = num.try_into().expect("try_into failed in set_state");
        let rc = unsafe { c::trexio_set_state(self.ptr, num) };
        rc_return((), rc)
    }

    /// Retrieves the number of `i64` required to store a determinant as a bit-field.
    /// This corresponds to \(\frac{\text{mo\_num}}{64}+1\).
    ///
    /// # Parameters
    ///
    /// None
    ///
    /// # Returns
    ///
    /// * `Result<usize, ExitCode>` - Returns the number of `i64` as `Ok(usize)` if the operation is successful,
    /// otherwise returns `Err(ExitCode)`.
    pub fn get_int64_num(&self) -> Result<usize, ExitCode> {
        let mut num = 0i32;
        let rc = unsafe { c::trexio_get_int64_num(self.ptr, &mut num) };
        let num: usize = num.try_into().expect("try_into failed in get_int64_num");
        rc_return(num, rc)
    }

    /// Writes a vector of determinants, represented as [Bitfield] objects.
    ///
    /// # Parameters
    ///
    /// * `offset: usize` - The number of determinants to skip in the file before writing.
    /// * `determinants: &[Bitfield]` - The array of determinants to write.
    ///
    /// # Returns
    ///
    /// * `Result<(), ExitCode>` - Returns `Ok(())` if the operation is successful,
    /// otherwise returns `Err(ExitCode)`.
    pub fn write_determinant_list(
        &self,
        offset: usize,
        determinants: &[Bitfield],
    ) -> Result<(), ExitCode> {
        let n_int = self.get_int64_num()?;
        match determinants.len() {
            0 => return Ok(()),
            _ => {
                if determinants[0].as_vec().len() != 2 * n_int {
                    return Err(InvalidArg(3));
                }
            }
        };
        let offset: i64 = offset
            .try_into()
            .expect("try_into failed in write_determinant_list");
        let buffer_size: i64 = determinants
            .len()
            .try_into()
            .expect("try_into failed in write_determinant_list");
        let mut one_d_array: Vec<i64> = Vec::with_capacity(determinants.len() * n_int);
        for det in determinants {
            for i in det.as_vec() {
                one_d_array.push(*i);
            }
        }
        let dset: *const i64 = one_d_array.as_ptr();
        let rc = unsafe { c::trexio_write_determinant_list(self.ptr, offset, buffer_size, dset) };
        rc_return((), rc)
    }

    /// Reads a vector of determinants, represented as [Bitfield] objects.
    ///
    /// # Parameters
    ///
    /// * `offset: usize` - The number of determinants to skip in the file before reading.
    /// * `buffer_size: usize` - The number of determinants to read.
    ///
    /// # Returns
    ///
    /// * `Result<Vec<Bitfield>, ExitCode>` - Returns the read determinants as `Ok(Vec<Bitfield>)`
    /// if the operation is successful, otherwise returns `Err(ExitCode)`.
    pub fn read_determinant_list(
        &self,
        offset: usize,
        buffer_size: usize,
    ) -> Result<Vec<Bitfield>, ExitCode> {
        let n_int = self.get_int64_num()?;
        let mut one_d_array: Vec<i64> = Vec::with_capacity(buffer_size * 2 * n_int);
        let one_d_array_ptr = one_d_array.as_ptr() as *mut i64;
        let rc = unsafe {
            let offset: i64 = offset
                .try_into()
                .expect("try_into failed in read_determinant_list (offset)");
            let mut buffer_size_read: i64 = buffer_size
                .try_into()
                .expect("try_into failed in read_determinant_list (buffer_size)");
            let rc = c::trexio_read_determinant_list(
                self.ptr,
                offset,
                &mut buffer_size_read,
                one_d_array_ptr,
            );
            let buffer_size_read: usize = buffer_size_read
                .try_into()
                .expect("try_into failed in read_determinant_list (buffer_size)");
            one_d_array.set_len(n_int * 2usize * buffer_size_read);
            match ExitCode::from(rc) {
                ExitCode::End => ExitCode::to_c(&ExitCode::Success),
                ExitCode::Success => {
                    assert_eq!(buffer_size_read, buffer_size);
                    rc
                }
                _ => rc,
            }
        };
        let result: Vec<Bitfield> = one_d_array
            .chunks(2 * n_int)
            .collect::<Vec<_>>()
            .iter()
            .map(|x| (Bitfield::from_vec(x)))
            .collect::<Vec<_>>();
        rc_return(result, rc)
    }
}

include!("generated.rs");
include!("generated_py.rs");
