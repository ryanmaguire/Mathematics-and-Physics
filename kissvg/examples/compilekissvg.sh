#!/bin/bash/

gcc -std=c89 -pedantic -pedantic-errors -Wall -Wextra -Wstrict-prototypes \
-I/usr/include/cairo/ -I../../ -L./ -O2 $1 -o test -lcairo -lkissvg -lm
