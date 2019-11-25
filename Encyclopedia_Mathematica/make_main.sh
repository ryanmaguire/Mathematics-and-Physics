#!/bin/bash

# Run pdflatex to create auxiliary files.
pdflatex main.tex

# Create glossaries and acronyms.
makeglossaries main

# Run pdflatex again, with glossaries.
pdflatex main.tex

# Make more auxiliary files.
makeindex -l -s main.ist -o main.gls main.glo

# Run pdflatex with all necessary files.
pdflatex main.tex

# Remove auxiliary files from directory.
rm -f main.ist
rm -f main.aux
rm -f main.out
rm -f main.glo
rm -f main.acn
rm -f main.toc
rm -f main.log
rm -f main.lot
rm -f main.lof
rm -f main.glg
rm -f main.acr
rm -f main.alg
rm -f main.gls
rm -f main.ilg
rm -r main.blg
rm -r main.bbl
rm -r main.fdb_latexmk
rm -r main.fls


# Change the name of the output pdf file.
mv main.pdf Mathematics_and_Physics.pdf
