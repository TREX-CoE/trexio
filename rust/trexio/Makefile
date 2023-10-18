default: src/generated.rs
	cargo build
	cargo test

generated.rs: build.py
	python3 build.py

test: default
	- cargo test -- --show-output

