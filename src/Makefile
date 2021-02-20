COMPILER=GNU
#COMPILER=INTEL
#COMPILER=LLVM

ifeq ($(COMPILER),GNU)
CC=gcc -g
CFLAGS=-fPIC -fexceptions -Wall -Werror -Wpedantic -Wextra

LIBS= #-lgfortran -lm
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


OBJECT_FILES= trio.o trio_text.o
HEADER_FILES= trio.h trio_text.h trio_s.h

export CC CFLAGS LIBS

.PHONY: clean

libtrio.so: $(OBJECT_FILES) $(HEADER_FILES)
	$(CC) -shared $(OBJECT_FILES) -o libtrio.so

test: libtrio.so test.c
	$(CC) $(CFLAGS) -Wl,-rpath,$(PWD) -L. test.c -ltrio $(LIBS) -o test

clean:
	rm -f *.o libtrio.so

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $*.c -o $*.o

