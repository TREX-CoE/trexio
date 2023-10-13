use trexio::back_end::BackEnd;
use trexio::bitfield::Bitfield;

pub fn test_write(file_name: &str, back_end: BackEnd) -> Result<(), trexio::ExitCode> {

    let () = trexio::info()?;

    // Prepare data to be written

    let n_buffers = 5;
    let buf_size_sparse = 100/n_buffers;
    let mut value_sparse_ao_2e_int_eri = vec![0.0f64 ; 100];
    let mut index_sparse_ao_2e_int_eri = vec![0i32 ; 400];
    for i in 0..100 {
        let i : usize = i;
        let j : i32 = i as i32;
        value_sparse_ao_2e_int_eri[i] = 3.14 + (j as f64);
        index_sparse_ao_2e_int_eri[4*i + 0] = 4*j   - 3;
        index_sparse_ao_2e_int_eri[4*i + 1] = 4*j+1 - 3;
        index_sparse_ao_2e_int_eri[4*i + 2] = 4*j+2 - 3;
        index_sparse_ao_2e_int_eri[4*i + 3] = 4*j+3 - 3;
    }

    let nucleus_num = 12;
    let state_id = 2;
    let charge = vec![6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1.0f64];
    let coord = vec![ 0.00000000f64,  1.39250319 ,  0.00 ,
                       -1.20594314,  0.69625160 ,  0.00 ,
                       -1.20594314, -0.69625160 ,  0.00 ,
                       0.00000000, -1.39250319 ,  0.00 ,
                       1.20594314, -0.69625160 ,  0.00 ,
                       1.20594314,  0.69625160 ,  0.00 ,
                       -2.14171677,  1.23652075 ,  0.00 ,
                       -2.14171677, -1.23652075 ,  0.00 ,
                       0.00000000, -2.47304151 ,  0.00 ,
                       2.14171677, -1.23652075 ,  0.00 ,
                       2.14171677,  1.23652075 ,  0.00 ,
                       0.00000000,  2.47304151 ,  0.00 ];
    let mo_num = 150;
    let ao_num = 1000;
    let basis_shell_num = 24;
    let basis_nucleus_index = vec![ 0usize, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 ];

    let label = vec![
          "C",
          "Na",
          "C",
          "C 66",
          "C",
          "C",
          "H 99",
          "Ru",
          "H",
          "H",
          "H",
          "H" ];
    let sym_str = "B3U with some comments";


    println!("{}", file_name);
    assert!( ! trexio::File::inquire(file_name)? );

    let trex_file = trexio::File::open(file_name, 'w', back_end)?;

    assert!( ! trex_file.has_nucleus()? );
    assert!( ! trex_file.has_nucleus_num()? );
    assert!( ! trex_file.has_nucleus_charge()? );
    assert!( ! trex_file.has_ao_2e_int()? );
    assert!( ! trex_file.has_ao_2e_int_eri()? );
    assert!( ! trex_file.has_determinant_list()? );

    trex_file.write_nucleus_num(nucleus_num)?;
    trex_file.write_nucleus_charge(charge)?;
    trex_file.write_nucleus_point_group(sym_str)?;
    trex_file.write_nucleus_coord(coord)?;
    trex_file.write_nucleus_label(label)?;
    trex_file.write_basis_shell_num(basis_shell_num)?;
    trex_file.write_basis_nucleus_index(basis_nucleus_index)?;
    trex_file.write_state_id(state_id)?;

    if ! trex_file.has_ao_num()? {
        trex_file.write_ao_num(ao_num)?;
    }

    if ! trex_file.has_mo_num()? {
        trex_file.write_mo_num(mo_num)?;
    }

    let mut energy = Vec::with_capacity(mo_num);
    for i in 0..mo_num {
        let e: f64 = i as f64 -100.0f64;
        energy.push(e);
    }
    trex_file.write_mo_energy(energy)?;

    let mut spin = vec![0 ; mo_num];
    for i in mo_num/2..mo_num {
        spin[i] = 1;
    }
    trex_file.write_mo_spin(spin)?;

    // Determinants
    //
    let det_num = 50;
    let mut det_list = Vec::with_capacity(det_num);
    for i in 0..det_num {
        let mut d = [0i64 ; 6 ];
        for j in 0..6 {
            d[j] = 6*(i as i64)+(j as i64);
        }
        det_list.push( Bitfield::from_vec(&d) );
    }

    let n_buffers = 5;
    let buf_size_det    = 50/n_buffers;
    let mut offset = 0;
    for i in 0..n_buffers {
        trex_file.write_determinant_list(offset, &det_list[offset..offset+buf_size_det])?;
        offset += buf_size_det;
    }


    trex_file.close()

}
