SRCDIR=..
include ../SiteSpecific

all:: pictLib.a pictLibG.a pictLibP.a pict.h

install: all
	cp -f *.a pict.h $(INSTALLLIB)

ifneq ($(wildcard *.c),)

%.o : %.c pict.h
	$(GCC) -Wall -O2 -fomit-frame-pointer $(CFLAGS) -o $@ -c $(CWD)/$<

%.debug : %.c pict.h
	$(GCC) -Wall -g -DDEBUG $(CFLAGS) -o $@ -c $(CWD)/$<

%.prof : %.c pict.h
	$(GCC) -Wall -DPROFILING -O2 -fomit-frame-pointer \
	  $(CFLAGS) -o $@ -c $(CWD)/$<

pict.h: pict.tmpl $(SRCDIR)/Config/config.h
	rm -f $@
	cat pict.tmpl $(SRCDIR)/Config/config.h >$@
	chmod -w $@

OFILES = profile.o gc.o output.o input.o initGc.o fair.o unfair.o main.o
GFILES = $(patsubst %.o, %.debug, $(OFILES))
PFILES = $(patsubst %.o, %.prof, $(OFILES))

pictLib.a: $(OFILES)
	ar cr pictLib.a $(OFILES)
	-ranlib pictLib.a
pictLibG.a: $(GFILES)
	ar cr pictLibG.a $(GFILES)
	-ranlib pictLibG.a
pictLibP.a: $(PFILES)
	ar cr pictLibP.a $(PFILES)
	-ranlib pictLibP.a

tags::
	etags *.c pict.tmpl

clean::
	rm -f pict.h *.o *.prof *.debug *.a

endif
