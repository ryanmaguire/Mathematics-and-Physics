#!/bin/bash

gcc -std=c89 -pedantic -pedantic-errors -Wall -Wextra \
-I/usr/include/cairo/ -I../../ -DNDEBUG -g -fPIC -Wstrict-prototypes \
-Wmissing-prototypes -Wold-style-definition -O2 -c kissvg.c

gcc kissvg.o -shared -o libkissvg.so -lcairo

sudo cp libkissvg.so /usr/local/lib/libkissvg.so



