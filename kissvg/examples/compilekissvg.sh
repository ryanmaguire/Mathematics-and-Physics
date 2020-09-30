#!/bin/bash/

osstring=`uname`

if [ "$osstring" = "Darwin" ]; then
    CC=gcc-10
    CAIROPATH=$(pkg-config --cflags --libs cairo)
    CAIROLIB=-L/usr/local/Cellar/cairo/1.16.0_3/lib
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

CompilerArgs="-std=c89 -pedantic -pedantic-errors -Wall -Wextra -Wpedantic"
CompilerArgs="$CompilerArgs -Wmisleading-indentation -Wmissing-prototypes"
CompilerArgs="$CompilerArgs -Wold-style-definition $CAIROPATH -I../../"
CompilerArgs="$CompilerArgs $CAIROPATH $CAIROLIB -L/usr/local/lib/"
CompilerArgs="$CompilerArgs -Werror -g -Wstrict-prototypes -O2"

$CC $CompilerArgs $1 -o test -lcairo -lkissvg -lm
./test

rm -f test
rm -f *.o
