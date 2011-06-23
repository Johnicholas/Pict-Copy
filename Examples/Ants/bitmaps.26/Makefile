ORIGMAPS = ant0.ppm ant1.ppm food.ppm


BITMAPS = ant2.ppm ant3.ppm ant4.ppm \
          ant5.ppm ant6.ppm ant7.ppm \
          antf0.ppm antf1.ppm antf2.ppm antf3.ppm antf4.ppm \
          antf5.ppm antf6.ppm antf7.ppm 

bitmaps: $(BITMAPS)

ant2.ppm: ant0.ppm
	../../Pictsmap/rotateppm ant0.ppm ant2.ppm

ant4.ppm: ant2.ppm
	../../Pictsmap/rotateppm ant2.ppm ant4.ppm

ant6.ppm: ant4.ppm
	../../Pictsmap/rotateppm ant4.ppm ant6.ppm

ant3.ppm: ant1.ppm
	../../Pictsmap/rotateppm ant1.ppm ant3.ppm

ant5.ppm: ant3.ppm
	../../Pictsmap/rotateppm ant3.ppm ant5.ppm

ant7.ppm: ant5.ppm
	../../Pictsmap/rotateppm ant5.ppm ant7.ppm

antf2.ppm: antf0.ppm
	../../Pictsmap/rotateppm antf0.ppm antf2.ppm

antf4.ppm: antf2.ppm
	../../Pictsmap/rotateppm antf2.ppm antf4.ppm

antf6.ppm: antf4.ppm
	../../Pictsmap/rotateppm antf4.ppm antf6.ppm

antf3.ppm: antf1.ppm
	../../Pictsmap/rotateppm antf1.ppm antf3.ppm

antf5.ppm: antf3.ppm
	../../Pictsmap/rotateppm antf3.ppm antf5.ppm

antf7.ppm: antf5.ppm
	../../Pictsmap/rotateppm antf5.ppm antf7.ppm


