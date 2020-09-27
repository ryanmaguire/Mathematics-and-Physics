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

-Wall -Wextra -Wpedantic -pedantic -pedantic-errors -Wmisleading-indentation 

$CC -std=c89 -pedantic -pedantic-errors -Wall -Wextra -Wpedantic \
-Wmisleading-indentation -Wmissing-prototypes -Wold-style-definition \
$CAIROPATH -I../../ -DNDEBUG -g -fPIC -Wstrict-prototypes -O2 -c kissvg.c

$CC $CAIROLIB kissvg.o -shared -o libkissvg.so -lcairo

sudo mv libkissvg.so /usr/local/lib/libkissvg.so

rm -f kissvg.o


