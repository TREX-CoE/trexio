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


OBJECT_FILES= trexio.o trexio_text.o trexio_hdf5.o
HEADER_FILES= trexio.h trexio_text.h trexio_hdf5.h trexio_s.h

export CC CFLAGS FC FFLAGS LIBS

.PHONY: clean

libtrexio.so: $(OBJECT_FILES) $(HEADER_FILES)
	$(CC) -shared $(OBJECT_FILES) -o libtrexio.so

fortran: libtrexio.so trexio_f.f90
	$(FC) $(FFLAGS) -c trexio_f.f90 -o trexio_f.o

test: libtrexio.so test.c test.f90 trexio_f.o
	$(CC) $(CFLAGS) $(INCLUDE) -Wl,-rpath,$(PWD) -L. test.c -ltrexio $(LIBS) -o test
	$(CC) $(CFLAGS) $(INCLUDE) -Wl,-rpath,$(PWD) -L. trexio_f.o test.f90 -ltrexio $(LIBS) -o test_f

clean:
	rm -f *.o libtrexio.so test test_*.h5 test_f
	rm -r trexio_test/

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) $(INCLUDE) -c $*.c -o $*.o

