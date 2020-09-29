#!/bin/bash

osstring=`uname`

if [ "$osstring" = "Darwin" ]; then
	CC=gcc-10
	CAIROPATH=$(pkg-config --cflags --libs cairo)
	CAIROLIB=-L/usr/local/Cellar/cairo/1.16.0_2/lib
elif [ "$osstring" = "Linux" ]; then
	CC=gcc
	CAIROPATH=-I/usr/include/cairo/
	CAIROLIB=-L/usr/lib/
else
    echo "Operating System not recognized"
    echo "Only MacOSX and Linux supported"
    echo "Exiting script"
    exit 1
fi


rm -f *.so
rm -f *.o

CompilerArgs="-std=c89 -pedantic -pedantic-errors -Wall -Wextra -Wpedantic"
CompilerArgs="$CompilerArgs -Wmisleading-indentation -Wmissing-prototypes"
CompilerArgs="$CompilerArgs -Wold-style-definition $CAIROPATH -I../../"
CompilerArgs="$CompilerArgs -DNDEBUG -g -fPIC -Wstrict-prototypes -O2 -c"

$CC $CompilerArgs kissvg.c
$CC $CompilerArgs kissvg_vector.c
$CC $CompilerArgs kissvg_euclidean.c
$CC $CompilerArgs kissvg_inversive_geometry.c

$CC $CAIROLIB \
kissvg.o \
kissvg_vector.o \
kissvg_euclidean.o \
kissvg_inversive_geometry.o	\
-shared -o libkissvg.so -lcairo

sudo mv libkissvg.so /usr/local/lib/libkissvg.so

rm -f kissvg.o
rm -f kissvg_vector.o
rm -f kissvg_euclidean.o
rm -f kissvg_inversive_geometry.o

