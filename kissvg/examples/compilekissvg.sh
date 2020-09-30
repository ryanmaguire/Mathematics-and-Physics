#!/bin/bash/

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

CompilerArgs="-std=c89 -pedantic -pedantic-errors -Wall -Wextra -Wpedantic"
CompilerArgs="$CompilerArgs -Wmisleading-indentation -Wmissing-prototypes"
CompilerArgs="$CompilerArgs -Wold-style-definition -I../../ -L/usr/local/lib/"
CompilerArgs="$CompilerArgs -Werror -DNDEBUG -g -Wstrict-prototypes -O2"

$CC $CompilerArgs $1 -o compilefig -lcairo -lkissvg -lm
./compilefig

rm -f compilefig
rm -f *.o *.log *.aux
