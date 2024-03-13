default: sources
	dune build

lib/trexio.ml: ../../trex.json read_json.py src/trexio.ml src/trexio.mli src/trexio_stubs.c
	./read_json.py

lib/trexio.h:
	cp ../../include/trexio.h lib/

sources: lib/trexio.ml lib/trexio.h

clean:
	rm lib/trexio.h lib/trexio.ml lib/trexio.mli lib/trexio_stubs.c
	dune clean

.PHONY: sources default
