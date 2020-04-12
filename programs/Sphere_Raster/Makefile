# To execute, run 'make Makefile make'
SOURCE = Sphere_Raster
WIDTH = 256
DENSITY = 300
MWIDTH = 512
DESTINATION = ../../images/

make:
	make clean
	gcc $(SOURCE).c -O2 -o $(SOURCE) -lm
	./$(SOURCE) >> $(SOURCE).ppm
	make png
	make clean

png:
	convert -density $(DENSITY) $(SOURCE).ppm  -resize $(MWIDTH)x$(MWIDTH) $(SOURCE).png
	cp $(SOURCE).png $(DESTINATION)
	rm -f $(SOURCE).png
	convert -density $(DENSITY) $(SOURCE).ppm  -resize $(WIDTH)x$(WIDTH) $(SOURCE).png

svg:
	convert -density $(DENSITY) $(SOURCE).svg  -resize $(MWIDTH)x$(MWIDTH) $(SOURCE).pdf
	cp $(SOURCE).pdf $(DESTINATION)
	rm -f $(SOURCE).pdf
	convert -density $(DENSITY) $(SOURCE).svg  -resize $(WIDTH)x$(WIDTH) $(SOURCE).png

clean:
	rm -rf $(SOURCE).pdf  $(SOURCE).svg $(SOURCE) $(SOURCE).ppm
