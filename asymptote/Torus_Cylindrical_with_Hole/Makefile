# To execute, run 'make Makefile make'
SOURCE = Torus_Cylindrical_with_Hole
WIDTH = 256
DENSITY = 300
DESTINATION = ../../images/

make:
	make clean
	rm -f $(SOURCE).png
	asy $(SOURCE).asy
	cp $(SOURCE).pdf $(DESTINATION)
	convert -density $(DENSITY) $(SOURCE).pdf  -resize $(WIDTH)x$(WIDTH) $(SOURCE).png
	make clean

clean:
	rm -rf $(SOURCE).pdf $(SOURCE).svg
