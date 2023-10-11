use trexio::back_end::BackEnd;

pub fn test_write(file_name: &str, back_end: BackEnd) {

    // Prepare data to be written
    let n_buffers = 5;
    let buf_size_sparse = 100/n_buffers;
    let buf_size_det    = 50/n_buffers;
    let mut value_sparse_ao_2e_int_eri = vec![0.0f64 ; 100];
    let mut index_sparse_ao_2e_int_eri = vec![0i32 ; 400];
    for i in 0..100 {
        let i : usize = i;
        let j : i32 = i.try_into().unwrap();
        let fj : f64 = j.try_into().unwrap();
        value_sparse_ao_2e_int_eri[i] = 3.14 + fj;
        index_sparse_ao_2e_int_eri[4*i + 0] = 4*j   - 3;
        index_sparse_ao_2e_int_eri[4*i + 1] = 4*j+1 - 3;
        index_sparse_ao_2e_int_eri[4*i + 2] = 4*j+2 - 3;
        index_sparse_ao_2e_int_eri[4*i + 3] = 4*j+3 - 3;
    }

    let nucleus_num = 12;
    let state_id = 2;
    let charge = vec![6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1.0f64];
    let coord = vec![ 0.00000000,  1.39250319 ,  0.00 ,
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
    let basis_nucleus_index = vec!([ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 ]);

    let label = vec![
          "C       ",
          "Na      ",
          "C       ",
          "C 66    ",
          "C       ",
          "C       ",
          "H 99    ",
          "Ru      ",
          "H       ",
          "H       ",
          "H       ",
          "H       " ];
    let mut label = label.concat();
    let sym_str = b"B3U with some comments";


    println!("{}", file_name);
    assert!( ! trexio::inquire(file_name).unwrap() );

    let trex_file = trexio::open(file_name, 'w', back_end).unwrap();

    assert!( ! trexio::has_nucleus(trex_file).unwrap() );
    assert!( ! trexio::has_nucleus_num(trex_file).unwrap() );
    assert!( ! trexio::has_nucleus_charge(trex_file).unwrap() );
    assert!( ! trexio::has_ao_2e_int(trex_file).unwrap() );
    assert!( ! trexio::has_ao_2e_int_eri(trex_file).unwrap() );
    assert!( ! trexio::has_determinant_list(trex_file).unwrap() );

    trexio::write_nucleus_num(trex_file, nucleus_num).unwrap();
    trexio::write_nucleus_charge(trex_file, charge).unwrap();

/*
    let rc = unsafe { trexio_write_nucleus_coord(trex_file, coord.as_ptr() as *const f64) };
    assert!(rc == TREXIO_SUCCESS);

    let rc = unsafe { trexio_write_nucleus_label(trex_file, label.as_ptr(), label[0].len().try_into().unwrap()) };
    assert!(rc == TREXIO_SUCCESS);

    let rc = unsafe { trexio_write_nucleus_point_group(trex_file, sym_str.as_ptr() as *const i8, sym_str.len().try_into().unwrap()) };
    assert!(rc == TREXIO_SUCCESS);

    let rc = unsafe { trexio_write_basis_shell_num(trex_file, basis_shell_num) };
    assert!(rc == TREXIO_SUCCESS);

    let rc = unsafe { trexio_write_basis_nucleus_index(trex_file, basis_nucleus_index.as_ptr() as *const i32) };
    assert!(rc == TREXIO_SUCCESS);

    let rc = unsafe { trexio_write_state_id(trex_file, state_id) };
    assert!(rc == TREXIO_SUCCESS);

    if (unsafe { trexio_has_ao_num(trex_file) } == TREXIO_HAS_NOT) {
        let rc = unsafe { trexio_write_ao_num(trex_file, ao_num) };
        assert!(rc == TREXIO_SUCCESS);
    }

    if (unsafe { trexio_has_mo_num(trex_file) } == TREXIO_HAS_NOT) {
        let rc = unsafe { trexio_write_mo_num(trex_file, mo_num) };
        assert!(rc == TREXIO_SUCCESS);
    }
    */

    trexio::close(trex_file).expect("Unable to close File");

}
