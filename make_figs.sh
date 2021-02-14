#!/bin/bash
top="$(pwd)"
Destination="$top/images/"

# Make the asymptote files.
cd "$top/asymptote/"

# Make sure necessary modules are in the asymptote search path.
export ASYMPTOTE_DIR="$(pwd)/"

# Remove unnecessary junk if it exists.
rm -f *.pre *.prc *.js *.tex *.pdf *.png

# Create gallery pages for the images.
for filename in ./*.asy; do

    # Extract the file name (returns file from file.asy).
    file=$(basename -- "$filename")
    file="${file%.*}"

    # Various modules should not be processed, skip them.
    if [[ $file = _* ]] ; then
        continue
    else

        # Create the output pdf file.
        echo -e "Processing $file"

        # Remove excess junk.
        rm -f *.pre *.prc *.js *.tex *.pdf *.svg *.eps *.aux *.dvi *.log

        asy "$file.asy"
        mv "$file.pdf" "$Destination"
    fi
done

# Remove excess junk.
rm -f *.pre *.prc *.js *.tex *.pdf *.svg *.eps *.aux *.dvi *.log

CompilerArgs1="-std=c89 -ansi -pedantic -pedantic-errors -Wall -Wextra"
CompilerArgs2="-Wpedantic -Wmisleading-indentation -Wmissing-field-initializers"
CompilerArgs3="-Wmissing-prototypes -Wold-style-definition -Winit-self"
CompilerArgs4="-Wmissing-declarations -Wnull-dereference -Wwrite-strings"
CompilerArgs5="-Wconversion -Wdouble-promotion -Wstrict-prototypes -O3"
CompilerArgs="$CompilerArgs1 $CompilerArgs2 $CompilerArgs3"
CompilerArgs="$CompilerArgs $CompilerArgs4 $CompilerArgs5"

# Execute the C programs.
cd "$top/programs/"

# Clear out previous junk.
rm -rf *.pre *.prc *.js *.tex *.pdf *.ppm *.png *.svg *.o *.out

# Create gallery pages for the images.
for filename in ./*.c; do

	# Extract the file name (returns file from file.asy).
    file=$(basename -- "$filename")
    file="${file%.*}"

    echo -e "Processing $file"

    # Compile and execute.
    gcc $CompilerArgs $file.c -o $file -lm
    ./$file
    if [ "${file: -6}" == "Raster" ] ; then
        convert "$file.ppm" "$file.png"
        mv "$file.png" "$Destination"
    elif [ "${file: -6}" == "Vector" ] ; then
        convert "$file.svg" "$file.pdf"
        mv "$file.pdf" "$Destination"
    else
	    echo "Last characters should be 'Raster' or 'Vector'"
	    echo "Aborting."
	    exit 1
    fi
    rm -f "$file" "$file.ppm" "$file.svg"
done
