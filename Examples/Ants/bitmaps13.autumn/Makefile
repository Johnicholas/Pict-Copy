ORIGMAPS = ant0.ppm ant1.ppm food.ppm


BITMAPS = ant2.ppm ant3.ppm ant4.ppm \
          ant5.ppm ant6.ppm ant7.ppm \
          antf0.ppm antf1.ppm antf2.ppm antf3.ppm antf4.ppm \
          antf5.ppm antf6.ppm antf7.ppm 

bitmaps: $(BITMAPS)

ant2.ppm: ant0.ppm
	../../Pictsmap/rotate ant0.ppm ant2.ppm

ant4.ppm: ant2.ppm
	../../Pictsmap/rotate ant2.ppm ant4.ppm

ant6.ppm: ant4.ppm
	../../Pictsmap/rotate ant4.ppm ant6.ppm

ant3.ppm: ant1.ppm
	../../Pictsmap/rotate ant1.ppm ant3.ppm

ant5.ppm: ant3.ppm
	../../Pictsmap/rotate ant3.ppm ant5.ppm

ant7.ppm: ant5.ppm
	../../Pictsmap/rotate ant5.ppm ant7.ppm

antf2.ppm: antf0.ppm
	../../Pictsmap/rotate antf0.ppm antf2.ppm

antf4.ppm: antf2.ppm
	../../Pictsmap/rotate antf2.ppm antf4.ppm

antf6.ppm: antf4.ppm
	../../Pictsmap/rotate antf4.ppm antf6.ppm

antf3.ppm: antf1.ppm
	../../Pictsmap/rotate antf1.ppm antf3.ppm

antf5.ppm: antf3.ppm
	../../Pictsmap/rotate antf3.ppm antf5.ppm

antf7.ppm: antf5.ppm
	../../Pictsmap/rotate antf5.ppm antf7.ppm


