#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

cat $DIR/prefix_front.c   > trexio.c
cat $DIR/prefix_front.h   > trexio.h
cat $DIR/prefix_s_front.h > trexio_s.h

cat $DIR/populated/pop_*.c >> trexio.c
cat $DIR/populated/pop_*.h >> trexio.h

cat $DIR/suffix_s_front.h >> trexio_s.h
cat $DIR/suffix_front.h   >> trexio.h


