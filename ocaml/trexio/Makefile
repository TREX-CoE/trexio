default: sources
	dune build

lib/trexio.ml: ../../trex.json read_json.py src/trexio.ml src/trexio.mli src/trexio_stubs.c
	./read_json.py

sources: lib/trexio.ml

clean:
	dune clean

.PHONY: sources default
