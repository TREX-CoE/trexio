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

ACLOCAL_AMFLAGS = -I m4
CLEANFILES = trexio.mod

VERSION_MAJOR   = @VERSION_MAJOR@
VERSION_MINOR   = @VERSION_MINOR@
VERSION_PATCH   = @VERSION_PATCH@

SUBDIRS = 

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = pkgconfig/trexio.pc


trexio_h = $(srcdir)/include/trexio.h
trexio_f = $(srcdir)/include/trexio_f.f90

include_HEADERS = $(trexio_h) $(trexio_f)

AM_CPPFLAGS = -I$(srcdir)/src -I$(srcdir)/include

lib_LTLIBRARIES = src/libtrexio.la


SOURCES = \
 $(trexio_h) \
 $(srcdir)/src/trexio.c \
 $(srcdir)/src/trexio_private.h \
 $(srcdir)/src/trexio_s.h \
 $(srcdir)/src/trexio_hdf5.c \
 $(srcdir)/src/trexio_hdf5.h \
 $(srcdir)/src/trexio_text.c \
 $(srcdir)/src/trexio_text.h

ORG_FILES = \
  src/templates_front/templator_front.org \
  src/templates_text/templator_text.org \
  src/templates_hdf5/templator_hdf5.org \
  trex.org


src_libtrexio_la_SOURCES = $(SOURCES)

# section related to tests

TESTS_C = \
  tests/io_all \
  tests/io_num_hdf5 \
  tests/io_num_text 

TESTS_F = \
  tests/test_f

TESTS_ALL = $(TESTS_C) $(TESTS_F)

TESTS = $(TESTS_ALL)
check_PROGRAMS = $(TESTS)

# specify common options for all tests
LDADD = src/libtrexio.la

# in principal, specifying -no-install (see example below) for each test provides better 
# and faster (?) `make check` but becomes tedious as the number of tests increases

#tests_io_all_LDFLAGS = -no-install

test_trexio_f = $(srcdir)/tests/trexio_f.f90

$(test_trexio_f): $(trexio_f)
	cp $(trexio_f) $(test_trexio_f)


tests_test_f_SOURCES = $(test_trexio_f) tests/test_f.f90


if TREXIO_DEVEL

CLEANFILES += $(SOURCES) $(trexio_f) $(trexio_h)

BUILT_SOURCES = $(SOURCES) $(trexio_f) $(test_trexio_f)

$(SOURCES): $(trexio_f)
src/trexio.c: $(trexio_h)

$(trexio_f): $(ORG_FILES)
	cd $(srcdir)/tools && ./build_trexio.sh

cppcheck: cppcheck.out
	cat cppcheck.out

cppcheck.out: $(trexio_h)
	cd src/ && \
	cppcheck --addon=cert -q --error-exitcode=0  \
	  --enable=all \
	  --language=c --std=c99 -rp --platform=unix64  \
	  -I../include *.c *.h 2>../$@

.PHONY: cppcheck

endif

clean-local:
	-rm -rf -- *.dir/ *.h5

