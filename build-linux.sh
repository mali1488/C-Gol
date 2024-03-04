#!/bin/bash

set -xe

RAYLIB_FLAG="-lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Ideps"
CFLAGS="-Wall -Wextra -pedantic -std=c11 -ggdb"
gcc src/gol.c deps/libraylib.a -o build/gol $CFLAGS $RAYLIB_FLAG
