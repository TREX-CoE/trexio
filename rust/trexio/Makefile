default: src/generated.rs
	cargo build
	cargo test

src/generated.rs: build.py
	python3 build.py

test: default
	- cargo test -- --show-output

