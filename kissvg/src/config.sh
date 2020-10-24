#!/bin/bash

osstring=`uname`

if [ "$osstring" = "Darwin" ]; then
	CC=gcc-10
elif [ "$osstring" = "Linux" ]; then
	CC=gcc
else
    echo "Operating System not recognized"
    echo "Only MacOSX and Linux supported"
    echo "Exiting script"
    exit 1
fi

echo "Clearing older files..."
rm -f *.so
rm -f *.o

echo "Compiling KissVG..."
CompilerArgs="-std=c89 -pedantic -pedantic-errors -Wall -Wextra -Wpedantic"
CompilerArgs="$CompilerArgs -Wmisleading-indentation -Wmissing-prototypes"
CompilerArgs="$CompilerArgs -Wold-style-definition -I../../"
CompilerArgs="$CompilerArgs -DNDEBUG -g -fPIC -Wstrict-prototypes -O2 -c"

# $CC $CompilerArgs kissvg.c
# $CC $CompilerArgs kissvg_label.c
$CC $CompilerArgs kissvg_matrix.c
$CC $CompilerArgs kissvg_vector.c
$CC $CompilerArgs kissvg_pen.c
$CC $CompilerArgs kissvg_circle.c

# $CC $CompilerArgs kissvg_euclidean.c
# $CC $CompilerArgs kissvg_inversive_geometry.c
# 
# echo "Building KissVG Shared Object (.so)"
# $CC -L/usr/local/lib \
# kissvg.o \
# kissvg_label.o \
# kissvg_matrix.o \
# kissvg_vector.o \
# kissvg_euclidean.o \
# kissvg_inversive_geometry.o	\
# -shared -o libkissvg.so -lcairo
# 
# echo "Moving to /usr/local/lib/libkissvg.so"
# sudo mv libkissvg.so /usr/local/lib/libkissvg.so

echo "Cleaning up..."
rm -f *.o

echo "Done"
