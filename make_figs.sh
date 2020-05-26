#!/bin/bash
top="$(pwd)"
Destination="$top/images/"

# Make the asymptote files.
cd "$top/asymptote/"

# Make sure necessary modules are in the asymptote search path.
export ASYMPTOTE_DIR="$(pwd)/"

# If folders for the gallery already exist, move them back to ./
for folder in */ ; do

	# Check that the folder exists.
	if [ -d "$folder" ]; then

		# If the folder exists, clean it out.
		echo "Cleaning $folder"

		# Check that the folder is not empty.
		if [ "$(ls -A $folder)" ]; then
			mv $folder* ./

			# Clear out older files while keeping the .asy one.
			rm -f Makefile
			rm -f README.md
			rm -f *.png
			rm -f *.svg
			rm -f *.pdf

			# Check that the above line worked and the folder is emtpty.
			if [ "$(ls -A $folder)" ]; then

				# Folder is not empty, aborting.
				echo "$folder is not empty, stopping!"
				exit 1
			else
				# Folder is empty, so kill it.
				rm -rf "$folder"
			fi
		else
			# Folder is empty, remove it.
			rm -rf "$folder"
		fi
	else
		# Folder does not exist, move on to the next one.
		continue
	fi
done

# Remove unnecessary junk if it exists.
rm -rf *.pre *.prc *.js *.tex *.pdf *.png

# Create gallery pages for the images.
for filename in ./*.asy; do

	# Extract the file name (returns file from file.asy).
	file=$(basename -- "$filename")
	file="${file%.*}"

	# Various modules should not be processed, skip them.
	if [ "$file" == "_custom_arrows" ] || [ "$file" == "_cassini_oval" ] \
	|| [ "$file" == "_mimic_three" ]   || [ "$file" == "_euc_geo" ] ; then
		continue
	fi

	# Create the output pdf file.
	echo -e "Processing $file\n"

	# Remove excess junk.
	rm -rf *.pre *.prc *.js *.tex *.pdf *.svg *.eps *.aux *.dvi *.log

    asy "$file.asy"
    mv "$file.pdf" "$Destination"
done

# Execute the C programs.
cd "$top/programs/"

# If folders for the gallery already exist, move them back to ./
for folder in */ ; do

	# Do not process anything in the include folder.
	if [ "$folder" == "include/" ] ; then
		continue
	fi

    file=$(basename -- "$folder")
    file="${file%.*}"

	# Check that the folder exists.
	if [ -d "$folder" ]; then

		# If the folder exists, clean it out.
		echo "Cleaning $folder"

		# Check that the folder is not empty.
		if [ "$(ls -A $folder)" ]; then
			mv $folder* ./

			echo "$file"$

			# Clear out older files while keeping the .c one.
			rm -f Makefile README.md

			# Make sure to remove the compiled binary file.
			rm -f "$folder/$file" *.png *.svg *.pdf

			# Check that the above line worked and the folder is emtpty.
			if [ "$(ls -A $folder)" ]; then

				# Folder is not empty, aborting.
				echo "$folder is not empty, stopping!"
				exit 1
			else
				# Folder is empty, so kill it.
				rm -rf "$folder"
			fi
		else
			# Folder is empty, remove it.
			rm -rf "$folder"
		fi
	else
		# Folder does not exist, move on to the next one.
		continue
	fi
done

# Create gallery pages for the images.
for filename in ./*.c; do

	# Extract the file name (returns file from file.asy).
    file=$(basename -- "$filename")
    file="${file%.*}"

    echo -e "Processing $file\n"

	# Remove excess junk.
	rm -rf *.pre *.prc *.js *.tex *.pdf *.ppm *.png *.svg
    gcc "$file.c" -O2 -o "$file" -lm

    if [ "${file: -6}" == "Raster" ] ; then
        "./$file" >> "$file.ppm"
        convert "$file.ppm" "$file.png"
        mv "$file.png" "$Destination"
    elif [ "${file: -6}" == "Vector" ] ; then
        ./"$file" >> "$file.svg"
        convert "$file.svg" "$file.pdf"
        mv "$file.pdf" "$Destination"
	else
		echo "Last characters should be 'Raster' or 'Vector'"
		echo "Aborting."
		exit 1
	fi
    rm -f "$file" "$file.ppm" "$file.svg"

done
