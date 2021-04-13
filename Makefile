package = trexio
version = 1.0
tarname = $(package)
distdir = $(tarname)-$(version)


build clean:
	cd src && $(MAKE) $@


dist: $(distdir).tar.gz


$(distdir).tar.gz: $(distdir)
	tar chof - $(distdir) | gzip -9 -c > $@
	rm -rf $(distdir)


$(distdir):
	mkdir -p $(distdir)/src
	cp src/libtrexio.so $(distdir)/src
	cp src/trexio* $(distdir)/src
	cp LICENSE README.md $(distdir)


.PHONY: build clean dist
