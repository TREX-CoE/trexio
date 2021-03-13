#!/bin/sh

cat prefix_front.c   > trexio.c
cat prefix_front.h   > trexio.h
cat prefix_s_front.h > trexio_s.h

cat populated/pop_*.c >> trexio.c
cat populated/pop_*.h >> trexio.h

cat suffix_s_front.h >> trexio_s.h
cat suffix_front.h   >> trexio.h


