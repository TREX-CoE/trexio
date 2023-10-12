use std::error::Error;

mod test;

fn main() -> Result<(), Box<dyn Error>> {
        println!("============================================");
        println!("         TREXIO VERSION : {}", trexio::PACKAGE_VERSION );
        println!("============================================");

    let file_name = "test_write_rust.dir";

    let back_end = trexio::BackEnd::Text;
    test::test_write(file_name, back_end)?;

    Ok(())
}
