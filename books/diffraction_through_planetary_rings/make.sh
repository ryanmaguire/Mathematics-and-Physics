####################################LICENSE#####################################
#   This file is part of Mathematics-and-Physics.                              #
#                                                                              #
#   Mathematics-and-Physics is free software: you can redistribute it and/or   #
#   modify it under the terms of the GNU General Public License as             #
#   published by the Free Software Foundation, either version 3 of the         #
#   License, or (at your option) any later version.                            #
#                                                                              #
#   Mathematics-and-Physics is distributed in the hope that it will be useful, #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License along    #
#   with Mathematics-and-Physics.  If not, see <https://www.gnu.org/licenses/>.#
################################################################################
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
rm -f main.blg
rm -f main.bbl
rm -f main.fdb_latexmk
rm -f main.fls


# Change the name of the output pdf file.
mv main.pdf Diffraction_Through_Planetary_Rings.pdf
