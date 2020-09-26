#!/bin/bash/

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

$CC -std=c89 -pedantic -pedantic-errors -Wall -Wextra -Wstrict-prototypes \
$CAIROPATH $CAIROLIB -I../../ -L/usr/local/lib/ -O2 $1 -o test -lcairo -lkissvg -lm

./test

rm -f test
