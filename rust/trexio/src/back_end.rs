use crate::c;

#[derive(Debug, PartialEq)]
pub enum BackEnd {
    /// The TREXIO "file" is a directory with text files for each group.
    /// A fallback when HDF5 is not available.
    Text,

    /// Should be used for production. The TREXIO file is a single HDF5 file.
    Hdf5,

    /// In-memory I/O
    Memory,

    /// Automatic discovery of the appropriate backend
    Auto,
}

impl BackEnd {
    /// Creation from a C value
    pub fn from(b: c::back_end_t) -> Self {
        match b {
            c::TREXIO_TEXT => Self::Text,
            c::TREXIO_MEMORY => Self::Memory,
            c::TREXIO_HDF5 => Self::Hdf5,
            c::TREXIO_AUTO => Self::Auto,
            _ => panic!("Invalid backend"),
        }
    }

    /// Conversion to a C value
    pub fn to_c(self) -> c::back_end_t {
        match self {
            Self::Hdf5 => c::TREXIO_HDF5,
            Self::Text => c::TREXIO_TEXT,
            Self::Memory => c::TREXIO_MEMORY,
            Self::Auto => c::TREXIO_AUTO,
        }
    }
}
