SRCDIR=..
include ../SiteSpecific

config.h: autoconf runtest hasgot async.c bytecopy.c div.c \
  sockets.c sprintf.c x11.c
	./autoconf

all:: config.h

tags::
	etags autoconf runtest hasgot *.c

clean::
	rm -f Config test.h config.h *.output file test test.c *.o a.out
