#[derive(Debug)]
#[derive(PartialEq)]
pub struct Bitfield {
    data: Vec<i64>,
}

use crate::c;
use crate::ExitCode;

impl Bitfield {

    /// Creates a new bitfield , using a number of i64 elements consistent
    /// with the number of MOs in the TREXIO file.
    pub fn from(n_int: usize, orb_list: &[usize]) -> (Self, f64) {

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

        let result = Bitfield { data };

        match ExitCode::from(rc) {
            ExitCode::Success => (result, 1.0),
            ExitCode::PhaseChange=> (result,-1.0),
            x => panic!("TREXIO Error {}", x)
        }
    }

    pub fn from_alpha_beta(alpha: &Bitfield, beta: &Bitfield) -> Bitfield {
        if alpha.data.len() != beta.data.len() {
            panic!("alpha and beta parts have different lengths");
        };
        let mut data = alpha.data.clone();
        data.extend_from_slice(&beta.data);
        Bitfield { data }
    }

    /// Returns the alpha part
    pub fn alpha(&self) -> Bitfield {
        let n_int = self.data.len()/2;
        Bitfield { data: (&self.data[0..n_int]).to_vec() }
    }

    /// Returns the beta part
    pub fn beta(&self) -> Bitfield {
        let n_int = self.data.len()/2;
        Bitfield { data: (&self.data[n_int..2*n_int]).to_vec() }
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
    pub fn to_orbital_list(&self) -> Vec<usize> {

        let n_int : i32 = self.data.len().try_into().expect("try_into failed in to_orbital_list");
        let d1 = self.as_ptr();
        let cap = self.data.len() * 64;
        let mut list = vec![ 0i32 ; cap ];
        let list_c = list.as_mut_ptr() as *mut i32;
        std::mem::forget(list);

        let mut occ_num : i32 = 0;

        let rc = unsafe { c::trexio_to_orbital_list(n_int, d1, list_c, &mut occ_num) };
        match ExitCode::from(rc) {
            ExitCode::Success => (),
            x => panic!("TREXIO Error {}", x)
        };

        let occ_num = occ_num as usize;
        let list = unsafe { Vec::from_raw_parts(list_c, occ_num, cap) };

        let mut result: Vec<usize> = Vec::with_capacity(occ_num);
        for i in list.iter() {
            result.push( *i as usize );
        }
        result
    }

    /// Converts the determinant into a list of orbital indices (0-based)
    pub fn to_orbital_list_up_dn(&self) -> (Vec<usize>, Vec<usize>) {

        let n_int : i32 = (self.data.len()/2).try_into().expect("try_into failed in to_orbital_list");
        let d1 = self.as_ptr();
        let cap = self.data.len()/2 * 64;
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
            x => panic!("TREXIO Error {}", x)
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
        (result_up, result_dn)
    }

}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn creation_from_list() {

        let list0 = vec![0, 1, 2, 3, 4];
        let list1 = vec![0, 1, 2, 4, 3];
        let list2 = vec![0, 1, 4, 2, 3];

        let (alpha0, phase0) = Bitfield::from(2, &list0);
        let list = alpha0.to_orbital_list();
        assert_eq!(list, list0);

        let (alpha1, phase1) = Bitfield::from(2, &list1);
        let list = alpha1.to_orbital_list();
        assert_eq!(list, list0);
        assert_eq!(phase1, -phase0);

        let (alpha2, phase2) = Bitfield::from(2, &list2);
        let list = alpha2.to_orbital_list();
        assert_eq!(list, list0);
        assert_eq!(phase2, phase0);

    }

    #[test]
    fn creation_alpha_beta() {
        let (alpha, _) = Bitfield::from(2, &[0, 1, 2, 3, 4]);
        let (beta , _) = Bitfield::from(2, &[0, 1, 2, 4, 5]);
        let det = Bitfield::from_alpha_beta(&alpha, &beta);
        let list = det.to_orbital_list();
        assert_eq!(list, [0,1,2,3,4,128,129,130,132,133]);
        assert_eq!(det.alpha(), alpha);
        assert_eq!(det.beta(), beta);
    }

    #[test]
    #[should_panic]
    fn creation_alpha_beta_with_different_nint() {
        let (alpha, _) = Bitfield::from(1, &[0, 1, 2, 3, 4]);
        let (beta , _) = Bitfield::from(2, &[0, 1, 2, 4, 5]);
        let _ = Bitfield::from_alpha_beta(&alpha, &beta);
    }
}
