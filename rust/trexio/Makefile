default:
	cargo build
	cargo test

docs_rs:
	cargo doc --no-deps --all-features

test: default
	- cargo test -- --show-output

