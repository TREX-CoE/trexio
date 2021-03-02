COMPILER=GNU
#COMPILER=INTEL
#COMPILER=LLVM

ifeq ($(COMPILER),GNU)
CC=gcc -g
CFLAGS=-fPIC -fexceptions -Wall -Werror -Wpedantic -Wextra

LIBS= -L/usr/lib/x86_64-linux-gnu/hdf5/serial/ -lz -lm -lhdf5 -lhdf5_hl #-lgfortran 
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


OBJECT_FILES= trio.o trio_text.o trio_hdf5.o
HEADER_FILES= trio.h trio_text.h trio_hdf5.h trio_s.h 

export CC CFLAGS LIBS

.PHONY: clean

libtrio.so: $(OBJECT_FILES) $(HEADER_FILES)
	$(CC) -shared $(OBJECT_FILES) -o libtrio.so

test: libtrio.so test.c
	$(CC) $(CFLAGS) $(INCLUDE) -Wl,-rpath,$(PWD) -L. test.c -ltrio $(LIBS) -o test
	rm test_write.h5

clean:
	rm -f *.o libtrio.so test test_write.h5

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) $(INCLUDE) -c $*.c -o $*.o

