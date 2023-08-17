#!/bin/bash
export ASYMPTOTE_DIR=$(pwd)

# 2D drawings.
for x in $(find 2d/ -name "*.asy"); do
    filename=$(basename $x .asy)
    echo "Processing: $x"
    asy $x

    if [ -e $filename.pdf ]; then
        mv $filename.pdf ../images/
    elif [ -e $filename.eps ]; then
        mv $filename.eps ../images/
    fi
done
