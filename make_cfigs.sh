#!/bin/bash
if [ ! "$BASH_VERSION" ] ; then
        echo "Please use BASH to run this script ($0)" 1>&2
        exit 1
fi

for x in $(find programs/ -name *.c); do
    filename=$(basename $x .c)
    echo "Processing: $x"
    gcc -O3 $x -o test -lm && ./test && rm -f ./test
done

for x in *.ppm; do
    filename=$(basename $x .ppm)
    convert $filename.ppm $filename.png
    mv $filename.png ./images/
    rm -f $filename.ppm
done

for x in *.svg; do
    filename=$(basename $x .svg)
    convert $filename.svg $filename.pdf
    mv $filename.pdf ./images/
    rm -f $filename.svg
done
