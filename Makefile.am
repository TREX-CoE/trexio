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
EXTRA_DIST = .git_hash

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
  src/trexio_text.c \
  src/trexio_text.h

if HAVE_HDF5
SOURCES += src/trexio_hdf5.c \
           src/trexio_hdf5.h
endif

ORG_FILES = \
  src/templates_front/templator_front.org \
  src/templates_text/templator_text.org \
  src/templates_hdf5/templator_hdf5.org \
  trex.org


src_libtrexio_la_SOURCES = $(SOURCES)

# Include CMake-related files in the distribution.
EXTRA_DIST += CMakeLists.txt \
              src/CMakeLists.txt \
              tests/CMakeLists.txt \
              cmake/cmake_uninstall.cmake.in \
              cmake/FindTREXIO.cmake


# Include files needed to produce the debian package.
DEB_FILES = \
  debian/changelog     \
  debian/compat        \
  debian/control       \
  debian/copyright     \
  debian/patches       \
  debian/README.Debian \
  debian/README.md     \
  debian/rules         \
  debian/source        \
  debian/watch

EXTRA_DIST += $(DEB_FILES)

debian_from_dist: $(DEB_FILES) $(SOURCES) $(trexio_h)
	VERSION=`echo ../trexio-*.tar.gz | grep -Eo '[[:digit:]].[[:digit:]].[[:digit:]]'` && \
		cp ../trexio-${VERSION}.tar.gz ../libtrexio_${VERSION}.orig.tar.gz
	debuild

# =============== TESTS =============== #

TESTS_C = \
  tests/open_text \
  tests/io_num_text \
  tests/io_dset_float_text \
  tests/io_dset_int_text \
  tests/io_dset_sparse_text \
  tests/io_safe_dset_float_text \
  tests/io_str_text \
  tests/io_dset_str_text \
  tests/delete_group_text \
  tests/overwrite_all_text \
  tests/io_all

if HAVE_HDF5
TESTS_C += \
  tests/open_hdf5 \
  tests/io_num_hdf5 \
  tests/io_dset_float_hdf5 \
  tests/io_dset_int_hdf5 \
  tests/io_dset_sparse_hdf5 \
  tests/io_safe_dset_float_hdf5 \
  tests/io_str_hdf5 \
  tests/io_dset_str_hdf5 \
  tests/delete_group_hdf5 \
  tests/overwrite_all_hdf5
endif

TESTS_F = \
  tests/test_f

TESTS = $(TESTS_C) $(TESTS_F)
check_PROGRAMS = $(TESTS)

# specify common LDADD options for all tests
LDADD = src/libtrexio.la

test_trexio_f = $(srcdir)/tests/trexio_f.f90
CLEANFILES += $(test_trexio_f)

$(test_trexio_f): $(trexio_f)
	cp $(trexio_f) $(test_trexio_f)

trexio.mod: tests/trexio_f.o

tests_test_f_SOURCES = $(test_trexio_f) tests/test_f.f90

clean-local:
	-rm -rf -- *.dir/ *.h5 __pycache__/

# =============== DOCUMENTATION =============== #

HTML_TANGLED = docs/index.html            \
               docs/examples.html         \
               docs/templator_hdf5.html   \
               docs/trex.html             \
               docs/README.html           \
               docs/templator_front.html  \
               docs/templator_text.html

htmldir = $(docdir)
# This $(htmlizer) file and the corresponding target rule allow to avoid circular dependency,
# which was introduced before to force htmlization of org-mode files.
# The circular dependency did not impose issues on GNU make but produced errors on bmake.
htmlizer = docs/.htmlizer

HTML_FILES = $(HTML_TANGLED) \
             docs/trexio.css \
             docs/tutorial_benzene.html \
             $(htmlizer)

dist_html_DATA = $(HTML_FILES)

$(HTML_TANGLED): $(htmlizer)

html-local: $(dist_html_DATA)
doc: html-local

# =============== DEVELOPER MODE =============== #

SWIG          = @SWIG@
HDF5_LDFLAGS  = @HDF5_LDFLAGS@
HDF5_CFLAGS   = @HDF5_CFLAGS@
HDF5_CPPFLAGS = @HDF5_CPPFLAGS@

if TREXIO_DEVEL

CLEANFILES += $(SOURCES) $(trexio_f) $(trexio_h) $(HTML_TANGLED) $(htmlizer) .git_hash

BUILT_SOURCES += $(SOURCES) $(trexio_f) $(test_trexio_f)

.git_hash: FORCE
	git log | head -1 | cut -d ' ' -f 2 > .git_hash

all: .git_hash

GENERATOR_FILES = $(srcdir)/tools/generator.py \
		  $(srcdir)/tools/generator_tools.py

$(SOURCES): $(trexio_f)
src/trexio.c: $(trexio_h)

$(trexio_f): $(ORG_FILES) $(GENERATOR_FILES)
	cd $(srcdir)/tools && ./build_trexio.sh

$(htmlizer): $(ORG_FILES) $(srcdir)/src/README.org
	touch $(htmlizer)
	cd $(srcdir)/tools && ./build_doc.sh

cppcheck: cppcheck.out
	cat cppcheck.out

cppcheck.out: $(trexio_h)
	cd src/ && \
	cppcheck --addon=cert -q --error-exitcode=0  \
	  --enable=all \
	  --language=c --std=c99 -rp --platform=unix64  \
	  -I../include *.c *.h 2>../$@

setup_py      = $(srcdir)/python/setup.py
setup_cfg     = $(srcdir)/python/setup.cfg
pytrexio_py   = $(srcdir)/python/pytrexio/pytrexio.py
trexio_py     = $(srcdir)/python/trexio.py
TEST_PY       = python/test/test_api.py
pytrexio_c    = $(srcdir)/src/pytrexio_wrap.c
pytrexio_i    = $(srcdir)/src/pytrexio.i
numpy_i       = $(srcdir)/src/numpy.i


python-test: $(TEST_PY)
	python3 $(TEST_PY)
	$(RM) -r -- __pycache__

python-install: $(pytrexio_py) $(setup_py) $(setup_cfg)
	cd python && \
		./install_pytrexio.sh $(HDF5_CFLAGS) $(HDF5_CPPFLAGS) $(HDF5_LDFLAGS)

python-sdist: $(pytrexio_py) $(setup_py) $(setup_cfg)
	cd python && \
		python3 -m build --sdist

$(pytrexio_py): $(pytrexio_c)
	cd tools && ./prepare_python.sh

# Build Python module and C wrapper code for TREXIO using SWIG
# [?] swig -python -threads pytrexio.i ----> Add thread support for all the interface
$(pytrexio_c): $(ORG_FILES) $(GENERATOR_FILES) $(trexio_h) $(pytrexio_i) $(numpy_i)
	cp $(trexio_h) src/
	cd src/ && \
		$(SWIG) -python -py3 -o pytrexio_wrap.c pytrexio.i
	$(RM) -- src/trexio.h

$(numpy_i):
	wget https://raw.githubusercontent.com/numpy/numpy/main/tools/swig/numpy.i -O $(numpy_i)

check-numpy:
	cd tools && ./check_numpy_i.sh

CLEANFILES += $(pytrexio_c) \
              $(pytrexio_py) \
              $(trexio_py) \
              python/src/*.c \
              python/src/*.h

.PHONY: cppcheck python-test python-install python-sdist check-numpy FORCE

endif
