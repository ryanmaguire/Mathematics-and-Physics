# To execute, run 'make Makefile make'
SOURCE = Dunce_Cap_001
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
