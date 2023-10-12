#[derive(Debug)]
pub struct Bitfield {
    data: Vec<i64>,
    n_int: usize
}

use crate::c;
use crate::File;
use crate::ExitCode;

impl Bitfield {

    /// Creates a new bitfield , using a number of i64 elements consistent
    /// with the number of MOs in the TREXIO file.
    pub fn from(n_int: usize, orb_list: Vec<usize>) -> Result<(Self, f64), ExitCode> {

        let orb_list: Vec<i32> = orb_list.iter().map(|&x| x as i32).collect();
        let occ_num  = orb_list.len().try_into().expect("try_into failed in Bitfield::from");
        let orb_list_ptr = orb_list.as_ptr() as *const i32;
        let n_int32: i32 = n_int.try_into().expect("try_into failed in Bitfield::from");
        let mut b = vec![0i64 ; n_int];
        let bit_list = b.as_mut_ptr() as *mut c::bitfield_t;
        std::mem::forget(b);
        let rc = unsafe {
            c::trexio_to_bitfield_list(orb_list_ptr, occ_num, bit_list, n_int32)
            };

        let data = unsafe { Vec::from_raw_parts(bit_list, n_int, n_int) };

        let result = Bitfield { data, n_int };

        match ExitCode::from(rc) {
            ExitCode::Success => Ok( (result, 1.0) ),
            ExitCode::PhaseChange=> Ok( (result,-1.0) ),
            x => return Err(x),
        }
    }

    /// Number of i64 needed to represent a spin sector
    pub fn n_int(&self) -> usize {
        self.n_int
    }

    /// Returns the alpha part
    pub fn alpha(&self) -> &[i64] {
        &self.data[0..self.n_int]
    }

    /// Returns the beta part
    pub fn beta(&self) -> &[i64] {
        let n_int = self.n_int;
        &self.data[n_int..2*n_int]
    }

    /// Converts to a format usable in the C library
    pub fn as_ptr(&self) -> *const c::bitfield_t {
        let len = self.data.len();
        let result = &self.data[0..len];
        result.as_ptr() as *const c::bitfield_t
    }

    /// Converts to a format usable in the C library
    pub fn as_mut_ptr(&mut self) -> *mut c::bitfield_t {
        let len = self.data.len();
        let result = &mut self.data[0..len];
        result.as_mut_ptr() as *mut c::bitfield_t
    }

    /// Converts the bitfield into a list of orbital indices (0-based)
    pub fn to_orbital_list(&self) -> Result< Vec<usize>, ExitCode> {

        let n_int : i32 = self.n_int.try_into().expect("try_into failed in to_orbital_list");
        let d1 = self.as_ptr();
        let cap = self.n_int * 64;
        let mut list = vec![ 0i32 ; cap ];
        let list_c = list.as_mut_ptr() as *mut i32;
        std::mem::forget(list);

        let mut occ_num : i32 = 0;

        let rc = unsafe { c::trexio_to_orbital_list(n_int, d1, list_c, &mut occ_num) };
        match ExitCode::from(rc) {
            ExitCode::Success => (),
            x => return Err(x)
        };

        let occ_num = occ_num as usize;
        let list = unsafe { Vec::from_raw_parts(list_c, occ_num, cap) };

        let mut result: Vec<usize> = Vec::with_capacity(occ_num);
        for i in list.iter() {
            result.push( *i as usize );
        }
        Ok(result)
    }

    /// Converts the determinant into a list of orbital indices (0-based)
    pub fn to_orbital_list_up_dn(&self) -> Result< (Vec<usize>, Vec<usize>), ExitCode> {

        let n_int : i32 = (self.n_int/2).try_into().expect("try_into failed in to_orbital_list");
        let d1 = self.as_ptr();
        let cap = self.n_int * 64;
        let mut b = vec![ 0i32 ; cap ];
        let list_up_c = b.as_mut_ptr() as *mut i32;
        std::mem::forget(b);
        let mut b = vec![ 0i32 ; cap ];
        let list_dn_c = b.as_mut_ptr() as *mut i32;
        std::mem::forget(b);

        let mut occ_num_up : i32 = 0;
        let mut occ_num_dn : i32 = 0;

        let rc = unsafe { c::trexio_to_orbital_list_up_dn(n_int, d1, list_up_c, list_dn_c, &mut occ_num_up, &mut occ_num_dn) };
        match ExitCode::from(rc) {
            ExitCode::Success => (),
            x => return Err(x)
        };

        let occ_num_up = occ_num_up as usize;
        let occ_num_dn = occ_num_dn as usize;
        let list_up = unsafe { Vec::from_raw_parts(list_up_c, occ_num_up, cap) };
        let list_dn = unsafe { Vec::from_raw_parts(list_dn_c, occ_num_dn, cap) };

        let mut result_up: Vec<usize> = Vec::with_capacity(occ_num_up);
        for i in list_up.iter() {
            result_up.push( *i as usize );
        }

        let mut result_dn: Vec<usize> = Vec::with_capacity(occ_num_dn);
        for i in list_dn.iter() {
            result_dn.push( *i as usize );
        }
        Ok( (result_up, result_dn) )
    }

}


