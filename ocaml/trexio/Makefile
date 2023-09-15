default: sources
	dune build

lib/trexio.ml: ../../trex.json read_json.py src/trexio.ml src/trexio.mli src/trexio_stubs.c
	./read_json.py

lib/trexio.h:
	cp ../../include/trexio.h lib/

sources: lib/trexio.ml lib/trexio.h

clean:
	dune clean

.PHONY: sources default
