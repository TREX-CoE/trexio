use crate::c;

/// Possible back ends
#[derive(Debug)]
#[derive(PartialEq)]
pub enum BackEnd {
  Text,
  Hdf5,
  Auto,
}

impl BackEnd {

    /// Creation from a C value
    pub fn from(b : c::back_end_t) -> Self {
       match b {
          c::TREXIO_TEXT     => Self::Text,
          c::TREXIO_HDF5     => Self::Hdf5,
          c::TREXIO_AUTO     => Self::Auto,
          _                  => panic!("Invalid backend"),
       }
    }

    /// Conversion to a C value
    pub fn to_c(self) -> c::back_end_t {
        match self {
            Self::Text   => c::TREXIO_TEXT,
            Self::Hdf5   => c::TREXIO_HDF5,
            Self::Auto   => c::TREXIO_AUTO,
        }
    }
}
