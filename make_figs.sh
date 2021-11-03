#!/bin/bash
if [ ! "$BASH_VERSION" ] ; then
        echo "Please use BASH to run this script ($0)" 1>&2
        exit 1
fi

for x in $(find asymptote/ -name *.asy -not -path "asymptote/animations/*"); do
    filename=$(basename $x .asy)
    echo "Processing: $x"
    asy $x;

    if [ -e $filename.pdf ]; then
        mv $filename.pdf ./images/
    elif [ -e $filename.eps ]; then
        mv $filename.eps ./images/
    fi
done

