rm -f gallery.{tex,pdf,log,aux}
touch gallery.tex

echo "\documentclass{article}" >> gallery.tex
echo "\usepackage{graphicx}" >> gallery.tex
echo "\title{Gallery of Figures}" >> gallery.tex
echo "\author{Ryan Maguire}" >> gallery.tex
echo "\date{\today}" >> gallery.tex
echo "\begin{document}" >> gallery.tex
echo "\maketitle" >> gallery.tex


for x in *.pdf; do
    caption=${x%.pdf} | tr "_" "-"
    echo "\begin{figure}" >> gallery.tex
    echo "\centering" >> gallery.tex
    echo "\resizebox{\textwidth}{!}{\includegraphics{$x}}" >> gallery.tex
    echo "\caption{$caption}" >> gallery.tex
    \echo "\end{figure}" >> gallery.tex
done

echo "\end{document}" >> gallery.tex

pdflatex gallery.tex
rm -f gallery.{aux,log,tex}
