default:
	cargo build
	cargo test

docs_rs:
	cargo doc --no-deps --all-features --open

test: default
	- cargo test -- --show-output

