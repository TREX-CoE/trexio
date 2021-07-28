# TREXIO - TREX Input/Output library
#
# BSD 3-Clause License
#
# Copyright (c) 2020, TREX Center of Excellence
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# =============== SETTINGS =============== #

ACLOCAL_AMFLAGS = -I m4
CLEANFILES = trexio.mod
BUILT_SOURCES = trexio.mod

VERSION_MAJOR   = @VERSION_MAJOR@
VERSION_MINOR   = @VERSION_MINOR@
VERSION_PATCH   = @VERSION_PATCH@

SUBDIRS = 

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pkgconfig/trexio.pc

# =============== BUILD =============== #

trexio_h = $(srcdir)/include/trexio.h
trexio_f = $(srcdir)/include/trexio_f.f90

include_HEADERS = $(trexio_h) $(trexio_f)

AM_CPPFLAGS = -I$(srcdir)/src -I$(srcdir)/include

lib_LTLIBRARIES = src/libtrexio.la


SOURCES = \
  $(trexio_h) \
  src/trexio.c \
  src/trexio_private.h \
  src/trexio_s.h \
  src/trexio_hdf5.c \
  src/trexio_hdf5.h \
  src/trexio_text.c \
  src/trexio_text.h

ORG_FILES = \
  src/templates_front/templator_front.org \
  src/templates_text/templator_text.org \
  src/templates_hdf5/templator_hdf5.org \
  trex.org


src_libtrexio_la_SOURCES = $(SOURCES)

# =============== TESTS =============== #

TESTS_C = \
  tests/open_hdf5 \
  tests/open_text \
  tests/io_num_hdf5 \
  tests/io_num_text \
  tests/io_dset_float_hdf5 \
  tests/io_dset_float_text \
  tests/io_dset_int_hdf5 \
  tests/io_dset_int_text \
  tests/io_safe_dset_float_hdf5 \
  tests/io_safe_dset_float_text \
  tests/io_str_hdf5 \
  tests/io_str_text \
  tests/io_dset_str_hdf5 \
  tests/io_dset_str_text \
  tests/overwrite_all_hdf5 \
  tests/overwrite_all_text \
  tests/io_all

TESTS_F = \
  tests/test_f

TESTS = $(TESTS_C) $(TESTS_F)
check_PROGRAMS = $(TESTS)

# specify common LDADD options for all tests
LDADD = src/libtrexio.la

# in principal, specifying -no-install (see below) is not mandatory
# for the tests to compile and pass, but the produced test binaries differ 
tests_open_hdf5_LDFLAGS = -no-install
tests_open_text_LDFLAGS = -no-install
tests_io_num_hdf5_LDFLAGS = -no-install
tests_io_num_text_LDFLAGS = -no-install
tests_io_dset_float_hdf5_LDFLAGS = -no-install
tests_io_dset_float_text_LDFLAGS = -no-install
tests_io_dset_int_hdf5_LDFLAGS = -no-install
tests_io_dset_int_text_LDFLAGS = -no-install
tests_io_safe_dset_float_hdf5_LDFLAGS = -no-install
tests_io_safe_dset_float_text_LDFLAGS = -no-install
tests_io_str_hdf5_LDFLAGS = -no-install
tests_io_str_text_LDFLAGS = -no-install
tests_io_dset_str_hdf5_LDFLAGS = -no-install
tests_io_dset_str_text_LDFLAGS = -no-install
tests_overwrite_all_hdf5_LDFLAGS = -no-install
tests_overwrite_all_text_LDFLAGS = -no-install
tests_io_all_LDFLAGS = -no-install

test_trexio_f = $(srcdir)/tests/trexio_f.f90

$(test_trexio_f): $(trexio_f)
	cp $(trexio_f) $(test_trexio_f)

trexio.mod: tests/trexio_f.o

tests_test_f_SOURCES = $(test_trexio_f) tests/test_f.f90
tests_test_f_LDFLAGS = -no-install

clean-local:
	-rm -rf -- *.dir/ *.h5

# =============== DOCUMENTATION =============== #

HTML_FILES =  docs/trexio.css            \
              docs/index.html            \
              docs/Sparse.html           \
              docs/templator_hdf5.html   \
              docs/trex.html             \
              docs/README.html           \
              docs/templator_front.html  \
              docs/templator_text.html

htmldir = $(docdir)
dist_html_DATA = $(HTML_FILES)

$(HTML_FILES): docs/index.html

# =============== DEVELOPER MODE =============== #

if TREXIO_DEVEL

CLEANFILES += $(SOURCES) $(trexio_f) $(trexio_h)

BUILT_SOURCES += $(SOURCES) $(trexio_f) $(test_trexio_f)


$(SOURCES): $(trexio_f)
src/trexio.c: $(trexio_h)

$(trexio_f): $(ORG_FILES)
	cd $(srcdir)/tools && ./build_trexio.sh

docs/index.html: $(ORG_FILES) $(srcdir)/src/README.org
	cd $(srcdir)/tools && ./build_doc.sh

cppcheck: cppcheck.out
	cat cppcheck.out

cppcheck.out: $(trexio_h)
	cd src/ && \
	cppcheck --addon=cert -q --error-exitcode=0  \
	  --enable=all \
	  --language=c --std=c99 -rp --platform=unix64  \
	  -I../include *.c *.h 2>../$@


python: _pytrexio*.so

python-test: test.py _pytrexio*.so
	python3 test.py
	$(RM) -r -- __pycache__

python-sdist: setup.py
	python3 setup.py sdist


python-build: pyproject.toml setup.py setup.cfg MANIFEST.in
	python3 -m build

python-release: pyproject.toml setup.py setup.cfg MANIFEST.in
	python3 -m twine upload --repository testpypi dist/*

# Advanced compilation using Python-native distutils
#
# swig -python -threads pytrexio.i ----> Add thread support for all the interface
# 
_pytrexio*.so:  $(ORG_FILES) $(trexio_h) src/pytrexio.i
	cp $(trexio_h) src/
	cd src/ && swig -python -py3 -o pytrexio_wrap.c pytrexio.i
	python3 setup.py build_ext --inplace --swig-opts="-modern"
	$(RM) -- src/trexio.h

# Manual compilation of Python module
#
#src/_pytrexio.so: $(ORG_FILES) $(trexio_h) src/pytrexio.i
#       cp $(trexio_h) src/
#       cd src/ && \
#       swig -python -py3 -o pytrexio_wrap.c pytrexio.i && \
#       $(CC) $(CPPFLAGS) -I/usr/include/python3.8 -fPIC -Wno-discarded-qualifiers \
#       	-c trexio.c trexio_hdf5.c trexio_text.c pytrexio_wrap.c && \
#       $(CC) -shared trexio.o trexio_hdf5.o trexio_text.o pytrexio_wrap.o \
#       	$(LDFLAGS) $(LIBS) -o _pytrexio.so
#       $(RM) -- src/trexio.h
#

CLEANFILES += src/pytrexio_wrap.c src/pytrexio.py _pytrexio*.so 

.PHONY: cppcheck python python-build python-test

endif

