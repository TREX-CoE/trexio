use trexio::back_end::BackEnd;
use trexio::bitfield::Bitfield;

fn write(file_name: &str, back_end: BackEnd) -> Result<(), trexio::ExitCode> {
    // Prepare data to be written

    let nucleus_num = 12;
    let state_id = 2;
    let charge = vec![6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1.0f64];
    let coord = vec![
        [0.00000000f64, 1.39250319, 0.00],
        [-1.20594314, 0.69625160, 0.00],
        [-1.20594314, -0.69625160, 0.00],
        [0.00000000, -1.39250319, 0.00],
        [1.20594314, -0.69625160, 0.00],
        [1.20594314, 0.69625160, 0.00],
        [-2.14171677, 1.23652075, 0.00],
        [-2.14171677, -1.23652075, 0.00],
        [0.00000000, -2.47304151, 0.00],
        [2.14171677, -1.23652075, 0.00],
        [2.14171677, 1.23652075, 0.00],
        [0.00000000, 2.47304151, 0.00],
    ];
    let flat_coord = coord.into_iter().flatten().collect::<Vec<f64>>();
    let mo_num = 150;
    let ao_num = 1000;
    let basis_shell_num = 24;
    let basis_nucleus_index: Vec<usize> = (0..24).collect();

    let label = vec![
        "C", "Na", "C", "C 66", "C", "C", "H 99", "Ru", "H", "H", "H", "H",
    ];

    let sym_str = "B3U with some comments";

    println!("Write {}", file_name);
    assert!(!trexio::File::inquire(file_name)?);

    let trex_file = trexio::File::open(file_name, 'w', back_end)?;

    assert!(!trex_file.has_nucleus()?);
    assert!(!trex_file.has_nucleus_num()?);
    assert!(!trex_file.has_nucleus_charge()?);
    assert!(!trex_file.has_ao_2e_int()?);
    assert!(!trex_file.has_ao_2e_int_eri()?);
    assert!(!trex_file.has_determinant_list()?);

    trex_file.write_nucleus_num(nucleus_num)?;
    trex_file.write_nucleus_charge(&charge)?;
    trex_file.write_nucleus_point_group(sym_str)?;
    trex_file.write_nucleus_coord(&flat_coord)?;
    trex_file.write_nucleus_label(&label)?;
    trex_file.write_basis_shell_num(basis_shell_num)?;
    trex_file.write_basis_nucleus_index(&basis_nucleus_index)?;
    trex_file.write_state_id(state_id)?;

    if !trex_file.has_ao_num()? {
        trex_file.write_ao_num(ao_num)?;
    }

    if !trex_file.has_mo_num()? {
        trex_file.write_mo_num(mo_num)?;
    }

    let mut energy = Vec::with_capacity(mo_num);
    for i in 0..mo_num {
        let e: f64 = i as f64 - 100.0f64;
        energy.push(e);
    }
    trex_file.write_mo_energy(&energy)?;

    let mut spin = vec![0; mo_num];
    for i in mo_num / 2..mo_num {
        spin[i] = 1;
    }
    trex_file.write_mo_spin(&spin)?;

    // Integrals
    let nmax = 100;
    let mut ao_2e_int_eri = Vec::<(usize, usize, usize, usize, f64)>::with_capacity(nmax);

    let n_buffers = 5;
    let bufsize = nmax / n_buffers;

    for i in 0..100 {
        // Quadruplet of indices + value
        let data = (4 * i, 4 * i + 1, 4 * i + 2, 4 * i + 3, 3.14 + (i as f64));
        ao_2e_int_eri.push(data);
    }

    let mut offset = 0;
    for _ in 0..n_buffers {
        trex_file.write_ao_2e_int_eri(offset, &ao_2e_int_eri[offset..offset + bufsize])?;
        offset += bufsize;
    }

    // Determinants. The electron counts have to be in the file first: writing a
    // determinant list validates every determinant against them.
    trex_file.write_electron_up_num(ELEC_UP)?;
    trex_file.write_electron_dn_num(ELEC_DN)?;

    let det_num = DET_NUM;
    let det_list = determinant_list();

    let n_buffers = 5;
    let bufsize = det_num / n_buffers;
    let mut offset = 0;
    for _ in 0..n_buffers {
        trex_file.write_determinant_list(offset, &det_list[offset..offset + bufsize])?;
        offset += bufsize;
    }

    trex_file.close()
}

/// Determinants the C library will accept: it checks every one of them against
/// electron_up_num and electron_dn_num, so the number of bits set per spin has
/// to match. With mo_num = 150 a determinant is 2*3 = 6 integers, the first
/// three for up spin and the last three for down.
const DET_NUM: usize = 50;
const ELEC_UP: i64 = 4;
const ELEC_DN: i64 = 3;

fn determinant_list() -> Vec<Bitfield> {
    let mut list = Vec::with_capacity(DET_NUM);
    for i in 0..DET_NUM {
        let mut d = [0i64; 6];
        for j in 0..ELEC_UP as usize {
            let orbital = i + j;
            d[orbital / 64] |= 1i64 << (orbital % 64);
        }
        for j in 0..ELEC_DN as usize {
            let orbital = i + j;
            d[3 + orbital / 64] |= 1i64 << (orbital % 64);
        }
        list.push(Bitfield::from_vec(&d));
    }
    list
}

fn read(file_name: &str, back_end: BackEnd) -> Result<(), trexio::ExitCode> {
    println!("Read {}", file_name);
    assert!(trexio::File::inquire(file_name)?);

    let trex_file = trexio::File::open(file_name, 'r', back_end)?;

    assert!(trex_file.has_nucleus()?);
    assert!(trex_file.has_nucleus_num()?);
    assert!(trex_file.has_nucleus_charge()?);
    assert!(trex_file.has_ao_2e_int()?);
    assert!(trex_file.has_ao_2e_int_eri()?);
    assert!(trex_file.has_determinant_list()?);

    let nucleus_num = trex_file.read_nucleus_num()?;
    assert_eq!(nucleus_num, 12);

    let sym_str = trex_file.read_nucleus_point_group(64)?;
    assert_eq!(sym_str, "B3U with some comments");

    let charge = trex_file.read_nucleus_charge()?;
    assert_eq!(
        charge,
        vec![6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1.0f64]
    );

    let coord = trex_file.read_nucleus_coord()?;
    assert_eq!(
        coord,
        vec![
            0.00000000f64,
            1.39250319,
            0.00,
            -1.20594314,
            0.69625160,
            0.00,
            -1.20594314,
            -0.69625160,
            0.00,
            0.00000000,
            -1.39250319,
            0.00,
            1.20594314,
            -0.69625160,
            0.00,
            1.20594314,
            0.69625160,
            0.00,
            -2.14171677,
            1.23652075,
            0.00,
            -2.14171677,
            -1.23652075,
            0.00,
            0.00000000,
            -2.47304151,
            0.00,
            2.14171677,
            -1.23652075,
            0.00,
            2.14171677,
            1.23652075,
            0.00,
            0.00000000,
            2.47304151,
            0.00
        ]
    );

    let label = trex_file.read_nucleus_label(6)?;
    assert_eq!(
        label,
        vec!["C", "Na", "C", "C 66", "C", "C", "H 99", "Ru", "H", "H", "H", "H"]
    );

    let basis_shell_num = trex_file.read_basis_shell_num()?;
    assert_eq!(basis_shell_num, 24);

    let basis_nucleus_index = trex_file.read_basis_nucleus_index()?;
    let ref_val: Vec<usize> = (0..24).collect();
    assert_eq!(basis_nucleus_index, ref_val);

    let state_id = trex_file.read_state_id()?;
    assert_eq!(state_id, 2);

    let ao_num = trex_file.read_ao_num()?;
    assert_eq!(ao_num, 1000);

    let mo_num = trex_file.read_mo_num()?;
    assert_eq!(mo_num, 150);

    let mut energy_ref = Vec::with_capacity(mo_num);
    for i in 0..mo_num {
        let e: f64 = i as f64 - 100.0f64;
        energy_ref.push(e);
    }
    let energy = trex_file.read_mo_energy()?;
    assert_eq!(energy, energy_ref);

    let mut spin_ref = vec![0; mo_num];
    for i in mo_num / 2..mo_num {
        spin_ref[i] = 1;
    }
    let spin = trex_file.read_mo_spin()?;
    assert_eq!(spin, spin_ref);

    // Integrals
    let nmax = 100;
    let mut ao_2e_int_eri_ref = Vec::<(usize, usize, usize, usize, f64)>::with_capacity(nmax);

    let n_buffers = 8;
    let bufsize = nmax / n_buffers + 10;

    for i in 0..100 {
        // Quadruplet of indices + value
        let data = (4 * i, 4 * i + 1, 4 * i + 2, 4 * i + 3, 3.14 + (i as f64));
        ao_2e_int_eri_ref.push(data);
    }

    let mut offset = 0;
    let mut ao_2e_int_eri = Vec::<(usize, usize, usize, usize, f64)>::with_capacity(nmax);
    for _ in 0..n_buffers {
        let buffer = trex_file.read_ao_2e_int_eri(offset, bufsize)?;
        offset += buffer.len();
        ao_2e_int_eri.extend(buffer);
    }
    assert_eq!(ao_2e_int_eri_ref, ao_2e_int_eri);

    // Determinants
    let det_num = trex_file.read_determinant_num()?;
    assert_eq!(det_num, 50);

    let det_list_ref = determinant_list();

    let n_buffers = 8;
    let bufsize = det_num / n_buffers + 20;
    let mut offset = 0;
    let mut det_list: Vec<Bitfield> = Vec::with_capacity(det_num);
    for _ in 0..n_buffers {
        let buffer = trex_file.read_determinant_list(offset, bufsize)?;
        offset += buffer.len();
        det_list.extend(buffer);
    }
    assert_eq!(det_list_ref, det_list);

    trex_file.close()
}

#[test]
pub fn info() {
    let _ = trexio::info();
}

use std::fs;

#[test]
pub fn text_backend() {
    let _ = write("tmp/test_write.dir", trexio::BackEnd::Text).unwrap();
    let _ = read("tmp/test_write.dir", trexio::BackEnd::Text).unwrap();
    fs::remove_dir_all("tmp/test_write.dir").unwrap()
}

#[test]
pub fn hdf5_backend() {
    let _ = write("tmp/test_write.hdf5", trexio::BackEnd::Hdf5).unwrap();
    let _ = read("tmp/test_write.hdf5", trexio::BackEnd::Hdf5).unwrap();
    fs::remove_file("tmp/test_write.hdf5").unwrap()
}
