#!/bin/bash
export ASYMPTOTE_DIR=$(pwd)

# 2D drawings.
for x in $(find 2d/ -name "*.asy"); do
    filename=$(basename $x .asy)
    echo "Processing: $x"
    asy -f "pdf" $x
    mv $filename.pdf ../images/
done
