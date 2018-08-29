#!/bin/bash
pdflatex main.tex
makeglossaries main
pdflatex main.tex
makeindex -l -s main.ist -o 
main.gls main.glo
pdflatex main.tex
