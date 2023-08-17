#!/bin/bash
export ASYMPTOTE_DIR=$(pwd)

for x in $(find 3d/ -name "*.asy"); do
    filename=$(basename $x .asy)
    echo "Processing: $x"
    asy $x

    if [ -e $filename.pdf ]; then
        mv $filename.pdf ../images/
    elif [ -e $filename.eps ]; then
        mv $filename.eps ../images/
    fi
done
