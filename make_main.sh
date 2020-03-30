#!/bin/bash
#!/bin/bash
if [ ! "$BASH_VERSION" ] ; then
        echo "Please use BASH to run this script ($0)" 1>&2
        exit 1
fi
osstring=`uname`

if [ "$osstring" = "Darwin" ]; then
    ./make_figs_macos.sh
elif [ "$osstring" = "Linux" ]; then
	./make_figs_linux.sh
else
	echo "Operating System not recognized"
	echo "Only MacOSX and Linux supported"
	echo "Exiting script"
	exit 1
fi

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
rm -f main.blg
rm -f main.bbl
rm -f main.fdb_latexmk
rm -f main.fls
rm -f main.ind
rm -f main.idx

# Change the name of the output pdf file.
mv main.pdf Mathematics_and_Physics.pdf
