cd asymptote/

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
			rm -f .DS_Store
			rm -f $folder/.DS_Store

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