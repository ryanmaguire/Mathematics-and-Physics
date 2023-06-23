#!/bin/bash

export ASYMPTOTE_DIR=$(pwd)/asymptote/

if [ ! "$BASH_VERSION" ] ; then
        echo "Please use BASH to run this script ($0)" 1>&2
        exit 1
fi

# 2D drawings.
for x in $(find asymptote/2d/ -name *.asy); do
    filename=$(basename $x .asy)
    echo "Processing: $x"
    asy $x;

    if [ -e $filename.pdf ]; then
        mv $filename.pdf ./images/
    elif [ -e $filename.eps ]; then
        mv $filename.eps ./images/
    fi
done

# 3D drawings.
for x in $(find asymptote/3d/ -name *.asy); do
    filename=$(basename $x .asy)
    echo "Processing: $x"
    asy $x;

    if [ -e $filename.pdf ]; then
        mv $filename.pdf ./images/
    elif [ -e $filename.eps ]; then
        mv $filename.eps ./images/
    fi
done
