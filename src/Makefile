COMPILER=GNU
#COMPILER=INTEL
#COMPILER=LLVM

ifeq ($(COMPILER),GNU)
CC=gcc -g
CFLAGS=-fPIC -fexceptions -Wall -Werror -Wpedantic -Wextra

FS=gfortran -g
FFLAGS=-fPIC -fcheck=all -Waliasing -Wampersand -Wconversion -Wsurprising -Wintrinsics-std -Wno-tabs -Wintrinsic-shadow -Wline-truncation -Wreal-q-constant -Wuninitialized  -fbacktrace -ffpe-trap=zero,overflow,underflow -finit-real=nan

LIBS= -L/usr/lib/x86_64-linux-gnu/hdf5/serial/ -lz -lm -lhdf5 -lhdf5_hl -lgfortran
INCLUDE     = -I/usr/include/hdf5/serial
endif

ifeq ($(COMPILER),INTEL)
CC=icc -xHost
CFLAGS=-fPIC -g -O2

FC=ifort -xHost
FFLAGS=-fPIC -g -O2

LIBS= #-lm
endif

#TODO
ifeq ($(COMPILER),LLVM)
CC=clang
CFLAGS=-fPIC -g -O2

FC=flang
FFLAGS=fPIC -g -O2

LIBS=-lm
endif

RM=rm -f

OBJECT_FILES= trexio.o trexio_text.o trexio_hdf5.o
SOURCE_FILES= test.c trexio.c trexio_hdf5.c trexio_text.c
HEADER_FILES= trexio.h trexio_text.h trexio_hdf5.h trexio_s.h

export CC CFLAGS FC FFLAGS LIBS

.PHONY: clean

cppcheck.out: $(HEADER_FILES) $(SOURCE_FILES)
	cppcheck --addon=cert -q --error-exitcode=0  \
          --enable=style,warning,unusedFunction,performance,portability,missingInclude \
          --language=c -rp --std=c99 -v $(SOURCE_FILES) 2>$@

libtrexio.so: $(OBJECT_FILES) $(HEADER_FILES) cppcheck.out
	$(CC) -shared $(OBJECT_FILES) -o libtrexio.so

fortran: libtrexio.so trexio_f.f90
	$(FC) $(FFLAGS) -c trexio_f.f90 -o trexio_f.o

test_c: libtrexio.so test.c
	$(CC) $(CFLAGS) $(INCLUDE) -Wl,-rpath,$(PWD) -L. test.c -ltrexio $(LIBS) -o test_c

test_f: libtrexio.so test.f90 trexio_f.o
	$(CC) $(CFLAGS) $(INCLUDE) -Wl,-rpath,$(PWD) -L. test.f90 trexio_f.o -ltrexio $(LIBS) -o test_f

test: test_c test_f
	$(RM) -r trexio_test
	$(RM) -r trexio_test_fort
	./test_c
	./test_f

clean:
	$(RM) *.o libtrexio.so test_*.h5 test_f test_c
	$(RM) -r trexio_test/ trexio_test_fort/

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) $(INCLUDE) -c $*.c -o $*.o

