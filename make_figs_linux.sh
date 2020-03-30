#!/bin/bash
Destination="../../images/"

# Make the asymptote files.
cd asymptote/

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

echo -e "\nDone cleaning\n"

# Remove unnecessary junk if it exists.
rm -rf *.pre *.prc *.js *.tex *.pdf *.png

# Create gallery pages for the images.
for filename in ./*.asy; do

	# Extract the file name (returns file from file.asy).
	file=$(basename -- "$filename")
	file="${file%.*}"

	# The _custom_arrows module should not be processed, skip it.
	if [ "$file" == "_custom_arrows" ] || [ "$file" == "_cassini_oval" ] ; then
		continue
	fi

	# Create the output pdf file.
	echo "Processing $file"

	# Remove excess junk.
	rm -rf *.pre *.prc *.js *.tex *.pdf *.svg *.eps *.aux *.dvi *.log
	echo "Creating Folder $file/"
	mkdir "$file"
	mv "$filename" "$file/"

	# Create the README file.
	echo "Creating README..."
	touch "$file/README.md"
	echo "Note:" >> "$file/README.md"
	echo "-----" >> "$file/README.md"
	echo "" >> "$file/README.md"
	echo "The compiled example was compressed to a 256" >> "$file/README.md"
	echo "pixel width. Actual sizes vary." >> "$file/README.md"
	echo "Compiled Figure" >> "$file/README.md"
	echo "---------------" >> "$file/README.md"
	echo "![Example]($file.png)" >> "$file/README.md"

	# Create the make file.
	echo "Creating Makefile..."
	touch "$file/Makefile"
	echo "# To execute, run 'make Makefile make'" >> "$file/Makefile"
	echo "SOURCE = $file" >> "$file/Makefile"
	echo "WIDTH = 256" >> "$file/Makefile"
	echo "DESTINATION = $Destination" >> "$file/Makefile"
	echo "" >> "$file/Makefile"
	echo "make:" >> "$file/Makefile"
	echo -e "\tmake clean" >> "$file/Makefile"
	echo -e "\trm -f \$(SOURCE).png" >> "$file/Makefile"
	echo -e "\tasy \$(SOURCE).asy" >> "$file/Makefile"
	echo -e "\tcp \$(SOURCE).pdf \$(DESTINATION)" >> "$file/Makefile"
	echo -e "\tmake png" >> "$file/Makefile"
	echo -e "\tmake clean" >> "$file/Makefile"
	echo "" >> "$file/Makefile"
	echo "png:" >> "$file/Makefile"
	echo -e "\tmake svg" >> "$file/Makefile"
	echo -e "\tinkscape \$(SOURCE).svg"\
			" -w \$(WIDTH) --export-png=\$(SOURCE).png" >> "$file/Makefile"
	echo "" >> "$file/Makefile"
	echo "svg:" >> "$file/Makefile"
	echo -e "\tpdf2svg \$(SOURCE).pdf \$(SOURCE).svg" >> "$file/Makefile"
	echo -e "\tinkscape \$(SOURCE).svg"\
			" --export-plain-svg=\$(SOURCE).svg" >> "$file/Makefile"
	echo "" >> "$file/Makefile"
	echo "clean:" >> "$file/Makefile"
	echo -e "\trm -rf \$(SOURCE).pdf \$(SOURCE).svg" >> "$file/Makefile"

	# Run the make file.
	echo "Running make file..."
	cd "$file/"
	make Makefile make
	cd ../
	echo -e "Done\n"
done

# Execute the C programs.
cd ../programs/

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
			rm -f Makefile
			rm -f README.md

			# Make sure to remove the compiled binary file.
			rm -f "$folder/$file"
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

echo -e "\nDone cleaning\n"

# Create gallery pages for the images.
for filename in ./*.c; do

	# Extract the file name (returns file from file.asy).
    file=$(basename -- "$filename")
    file="${file%.*}"

	# Remove excess junk.
	rm -rf *.pre *.prc *.js *.tex *.pdf *.ppm *.png *.svg
	echo "Creating Folder $file/"
	mkdir "$file"
	mv "$filename" "$file/"

	# Create the README file.
	echo "Creating README..."
	touch "$file/README.md"
	echo "Note:" >> "$file/README.md"
	echo "-----" >> "$file/README.md"
	echo "" >> "$file/README.md"
	echo "The compiled example was compressed to a 256" >> "$file/README.md"
	echo "pixel width. Actual sizes vary." >> "$file/README.md"
	echo "Compiled Figure" >> "$file/README.md"
	echo "---------------" >> "$file/README.md"
	echo "![Example]($file.png)" >> "$file/README.md"

	# Create the make file.
	echo "Creating Makefile..."
	touch "$file/Makefile"
	echo "# To execute, run 'make Makefile make'" >> "$file/Makefile"
	echo "SOURCE = $file" >> "$file/Makefile"
	echo "WIDTH = 256" >> "$file/Makefile"
	echo "MAIN_WIDTH = 512" >> "$file/Makefile"
	echo "DESTINATION = $Destination" >> "$file/Makefile"
	echo "" >> "$file/Makefile"
	echo "make:" >> "$file/Makefile"
	echo -e "\tmake clean" >> "$file/Makefile"
	echo -e "\tgcc \$(SOURCE).c -O2 -o \$(SOURCE) -lm" >> "$file/Makefile"
	if [ "${file: -6}" == "Raster" ] ; then
		echo -e "\t./\$(SOURCE) >> \$(SOURCE).ppm" >> "$file/Makefile"
		echo -e "\tmake png" >> "$file/Makefile"
	elif [ "${file: -6}" == "Vector" ] ; then
		echo -e "\t./\$(SOURCE) >> \$(SOURCE).svg" >> "$file/Makefile"
		echo -e "\tmake svg" >> "$file/Makefile"
	else
		echo "Last characters should be 'Raster' or 'Vector'"
		echo "Aborting."
		exit 1
	fi
	echo -e "\tmake clean" >> "$file/Makefile"
	echo "" >> "$file/Makefile"
	echo "png:" >> "$file/Makefile"
	echo -e "\tinkscape \$(SOURCE).ppm"\
			" -w \$(MAIN_WIDTH) --export-png=\$(SOURCE).png" >> "$file/Makefile"
	echo -e "\tcp \$(SOURCE).png \$(DESTINATION)" >> "$file/Makefile"
	echo -e "\trm -f \$(SOURCE).png" >> "$file/Makefile"
	echo -e "\tinkscape \$(SOURCE).ppm"\
			" -w \$(WIDTH) --export-png=\$(SOURCE).png" >> "$file/Makefile"
	echo "" >> "$file/Makefile"
	echo "svg:" >> "$file/Makefile"
	echo -e "\tinkscape \$(SOURCE).svg"\
			" -w \$(MAIN_WIDTH) --export-png=\$(SOURCE).png" >> "$file/Makefile"
	echo -e "\tcp \$(SOURCE).png \$(DESTINATION)" >> "$file/Makefile"
	echo -e "\trm -f \$(SOURCE).png" >> "$file/Makefile"
	echo -e "\tinkscape \$(SOURCE).svg"\
			" --export-plain-svg=\$(SOURCE).svg" >> "$file/Makefile"
	echo -e "\tinkscape \$(SOURCE).svg"\
			" -w \$(WIDTH) --export-png=\$(SOURCE).png" >> "$file/Makefile"
	echo "" >> "$file/Makefile"
	echo "clean:" >> "$file/Makefile"
	echo -e "\trm -rf \$(SOURCE).pdf"\
			" \$(SOURCE).svg \$(SOURCE) \$(SOURCE).ppm" >> "$file/Makefile"

	# Run the make file.
	echo "Running make file..."
	cd "$file/"
	make Makefile make
	cd ../
	echo -e "Done\n"
done

cd ../
