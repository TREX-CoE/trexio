use crate::c;

#[derive(Debug, PartialEq)]
pub enum ExitCode {
    /// Unknown failure
    Failure,

    /// Everything went fine
    Success,

    /// Invalid argument
    InvalidArg(usize),

    /// End of file
    End,

    /// Read-only file
    ReadOnly,

    /// Error returned by Errno
    Errno,

    /// Invalid ID
    InvalidId,

    /// Allocation failed
    AllocationFailed,

    /// Element absent
    HasNot,

    /// Invalid (negative or 0) dimension
    InvalidNum,

    /// Attribute already exists
    AttrAlreadyExists,

    /// Dataset already exists
    DsetAlreadyExists,

    /// Error opening file
    OpenError,

    /// Error locking file
    LockError,

    /// Error unlocking file
    UnlockError,

    /// Invalid file
    FileError,

    /// Error reading group
    GroupReadError,

    /// Error writing group
    GroupWriteError,

    /// Error reading element
    ElemReadError,

    /// Error writing element
    ElemWriteError,

    /// Access to memory beyond allocated
    UnsafeArrayDim,

    /// Attribute does not exist in the file
    AttrMissing,

    /// Dataset does not exist in the file
    DsetMissing,

    /// Requested back end is disabled
    BackEndMissing,

    /// Invalid max_str_len
    InvalidStrLen,

    /// Possible integer overflow
    IntSizeOverflow,

    /// Unsafe operation in safe mode
    SafeMode,

    /// Inconsistent number of electrons
    InvalidElectronNum,

    /// Inconsistent number of determinants
    InvalidDeterminantNum,

    /// Inconsistent state of the file
    InvalidState,

    /// Failed to parse package_version
    VersionParsingIssue,

    /// The function succeeded with a change of sign
    PhaseChange,
}

impl ExitCode {
    /// Creation from a C value
    pub fn from(rc: c::trexio_exit_code) -> Self {
        match rc {
            c::TREXIO_FAILURE => Self::Failure,
            c::TREXIO_SUCCESS => Self::Success,
            c::TREXIO_INVALID_ARG_1 => Self::InvalidArg(1),
            c::TREXIO_INVALID_ARG_2 => Self::InvalidArg(2),
            c::TREXIO_INVALID_ARG_3 => Self::InvalidArg(3),
            c::TREXIO_INVALID_ARG_4 => Self::InvalidArg(4),
            c::TREXIO_INVALID_ARG_5 => Self::InvalidArg(5),
            c::TREXIO_END => Self::End,
            c::TREXIO_READONLY => Self::ReadOnly,
            c::TREXIO_ERRNO => Self::Errno,
            c::TREXIO_INVALID_ID => Self::InvalidId,
            c::TREXIO_ALLOCATION_FAILED => Self::AllocationFailed,
            c::TREXIO_HAS_NOT => Self::HasNot,
            c::TREXIO_INVALID_NUM => Self::InvalidNum,
            c::TREXIO_ATTR_ALREADY_EXISTS => Self::AttrAlreadyExists,
            c::TREXIO_DSET_ALREADY_EXISTS => Self::DsetAlreadyExists,
            c::TREXIO_OPEN_ERROR => Self::OpenError,
            c::TREXIO_LOCK_ERROR => Self::LockError,
            c::TREXIO_UNLOCK_ERROR => Self::UnlockError,
            c::TREXIO_FILE_ERROR => Self::FileError,
            c::TREXIO_GROUP_READ_ERROR => Self::GroupReadError,
            c::TREXIO_GROUP_WRITE_ERROR => Self::GroupWriteError,
            c::TREXIO_ELEM_READ_ERROR => Self::ElemReadError,
            c::TREXIO_ELEM_WRITE_ERROR => Self::ElemWriteError,
            c::TREXIO_UNSAFE_ARRAY_DIM => Self::UnsafeArrayDim,
            c::TREXIO_ATTR_MISSING => Self::AttrMissing,
            c::TREXIO_DSET_MISSING => Self::DsetMissing,
            c::TREXIO_BACK_END_MISSING => Self::BackEndMissing,
            c::TREXIO_INVALID_ARG_6 => Self::InvalidArg(6),
            c::TREXIO_INVALID_ARG_7 => Self::InvalidArg(7),
            c::TREXIO_INVALID_ARG_8 => Self::InvalidArg(8),
            c::TREXIO_INVALID_STR_LEN => Self::InvalidStrLen,
            c::TREXIO_INT_SIZE_OVERFLOW => Self::IntSizeOverflow,
            c::TREXIO_SAFE_MODE => Self::SafeMode,
            c::TREXIO_INVALID_ELECTRON_NUM => Self::InvalidElectronNum,
            c::TREXIO_INVALID_DETERMINANT_NUM => Self::InvalidDeterminantNum,
            c::TREXIO_INVALID_STATE => Self::InvalidState,
            c::TREXIO_VERSION_PARSING_ISSUE => Self::VersionParsingIssue,
            c::TREXIO_PHASE_CHANGE => Self::PhaseChange,
            _ => panic!("Unknown exit code"),
        }
    }

    /// Conversion to a C value
    pub fn to_c(&self) -> c::trexio_exit_code {
        match self {
            Self::Failure => c::TREXIO_FAILURE,
            Self::Success => c::TREXIO_SUCCESS,
            Self::InvalidArg(1) => c::TREXIO_INVALID_ARG_1,
            Self::InvalidArg(2) => c::TREXIO_INVALID_ARG_2,
            Self::InvalidArg(3) => c::TREXIO_INVALID_ARG_3,
            Self::InvalidArg(4) => c::TREXIO_INVALID_ARG_4,
            Self::InvalidArg(5) => c::TREXIO_INVALID_ARG_5,
            Self::End => c::TREXIO_END,
            Self::ReadOnly => c::TREXIO_READONLY,
            Self::Errno => c::TREXIO_ERRNO,
            Self::InvalidId => c::TREXIO_INVALID_ID,
            Self::AllocationFailed => c::TREXIO_ALLOCATION_FAILED,
            Self::HasNot => c::TREXIO_HAS_NOT,
            Self::InvalidNum => c::TREXIO_INVALID_NUM,
            Self::AttrAlreadyExists => c::TREXIO_ATTR_ALREADY_EXISTS,
            Self::DsetAlreadyExists => c::TREXIO_DSET_ALREADY_EXISTS,
            Self::OpenError => c::TREXIO_OPEN_ERROR,
            Self::LockError => c::TREXIO_LOCK_ERROR,
            Self::UnlockError => c::TREXIO_UNLOCK_ERROR,
            Self::FileError => c::TREXIO_FILE_ERROR,
            Self::GroupReadError => c::TREXIO_GROUP_READ_ERROR,
            Self::GroupWriteError => c::TREXIO_GROUP_WRITE_ERROR,
            Self::ElemReadError => c::TREXIO_ELEM_READ_ERROR,
            Self::ElemWriteError => c::TREXIO_ELEM_WRITE_ERROR,
            Self::UnsafeArrayDim => c::TREXIO_UNSAFE_ARRAY_DIM,
            Self::AttrMissing => c::TREXIO_ATTR_MISSING,
            Self::DsetMissing => c::TREXIO_DSET_MISSING,
            Self::BackEndMissing => c::TREXIO_BACK_END_MISSING,
            Self::InvalidArg(6) => c::TREXIO_INVALID_ARG_6,
            Self::InvalidArg(7) => c::TREXIO_INVALID_ARG_7,
            Self::InvalidArg(8) => c::TREXIO_INVALID_ARG_8,
            Self::InvalidStrLen => c::TREXIO_INVALID_STR_LEN,
            Self::IntSizeOverflow => c::TREXIO_INT_SIZE_OVERFLOW,
            Self::SafeMode => c::TREXIO_SAFE_MODE,
            Self::InvalidElectronNum => c::TREXIO_INVALID_ELECTRON_NUM,
            Self::InvalidDeterminantNum => c::TREXIO_INVALID_DETERMINANT_NUM,
            Self::InvalidState => c::TREXIO_INVALID_STATE,
            Self::VersionParsingIssue => c::TREXIO_VERSION_PARSING_ISSUE,
            Self::PhaseChange => c::TREXIO_PHASE_CHANGE,
            _ => panic!("Unknown exit code"),
        }
    }

    pub fn to_str(&self) -> Result<&'static str, Utf8Error> {
        let c_error = self.to_c();
        let c_buf: *const c_char = unsafe { c::trexio_string_of_error(c_error) };
        let c_str: &CStr = unsafe { CStr::from_ptr(c_buf) };
        c_str.to_str()
    }
}

use std::error::Error;
use std::ffi::c_char;
use std::ffi::CStr;
use std::fmt;
use std::str::Utf8Error;

impl fmt::Display for ExitCode {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.to_str().unwrap())
    }
}

impl Error for ExitCode {
    fn description(&self) -> &str {
        self.to_str().unwrap()
    }
}
