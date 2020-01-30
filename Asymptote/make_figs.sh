#!/bin/bash

# Old method with pdflatex flag.
# for filename in ./*.asy; do
# 	file=$(basename -- "$filename")
# 	file="${file%.*}"
# 	echo "Processing $file"
# 	asy "$filename"
# 	rm -f "${file}_0.pdf"
# 	mv "${file}_pdf+0_0.pdf" "${file}.pdf"
# done

# New method without pdflatex flag.
for filename in ./*.asy; do
	file=$(basename -- "$filename")
	file="${file%.*}"
	echo "Processing $file"
	asy "$filename"
done

# Remove unnecessary junk if it exists.
rm -rf *.pre *.prc *.js *.tex
mv *.pdf ../images/
