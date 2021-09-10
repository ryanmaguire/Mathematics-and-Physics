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
for filename in `find . -name "*.asy"`; do

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

        asy "$filename"

        if [ -e "$file.pdf" ]; then
            mv "$file.pdf" "$Destination"
        else
            mv "$file.eps" "$Destination"
        fi
    fi
done

# Remove excess junk.
rm -f *.pre *.prc *.js *.tex *.pdf *.svg *.eps *.aux *.dvi *.log

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
    if [ -e "$file.pdf" ]; then
        mv $file.pdf $Destination
    elif [ -e "$file.svg" ]
        mv $file.svg $Destination
    else
        mv $file.ppm $Destination
    fi
    rm -f $file
done
