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

# for now copy entire src/ directory into $(distdir) in order for distcheck rule to work
# later on can be changed to ship only files like *.c *.h *.f90 *.so *.mod
$(distdir): FORCE
	mkdir -p $(distdir)
	cp -r src/ $(distdir)
	cp Makefile LICENSE README.md $(distdir)


FORCE:
	-rm $(distdir).tar.gz >/dev/null 2>&1
	-rm -rf $(distdir) >/dev/null 2>&1


distcheck: $(distdir).tar.gz
	gzip -cd $(distdir).tar.gz | tar xvf -
	cd $(distdir) && $(MAKE) build
	cd $(distdir) && $(MAKE) clean
	rm -rf $(distdir)
	@echo "*** Package $(distdir).tar.gz is ready for distribution."


.PHONY: FORCE build clean dist distcheck
