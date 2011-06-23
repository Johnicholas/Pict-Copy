SRCDIR = ..
NOPICTDEP = yes
NOPICTTAGS = yes
LOCALLIBS = $(patsubst %.src, %.pi, $(wildcard *.src */*.src))
TARGETS = $(patsubst %.pi, %.px, $(LOCALLIBS))
include $(SRCDIR)/SiteSpecific
include $(SRCDIR)/PiRules

PIFLAGS += -reset lib 

install:: $(TARGETS)
	mkdir -p $(INSTALLLIB)/Contrib $(INSTALLLIB)/Posix
	mkdir -p $(INSTALLLIB)/Picture $(INSTALLLIB)/Std
	mkdir -p $(INSTALLLIB)/X11
	cp *.px *.px.o $(INSTALLLIB)
	cp Contrib/*.px Contrib/*.px.o $(INSTALLLIB)/Contrib
	cp Posix/*.px Posix/*.px.o $(INSTALLLIB)/Posix
	cp Picture/*.px Picture/*.px.o $(INSTALLLIB)/Picture
	cp Std/*.px Std/*.px.o $(INSTALLLIB)/Std
	cp X11/*.px X11/*.px.o $(INSTALLLIB)/X11

ifneq ($(wildcard *.src),)

clean::
	rm -f *.px.o */*.px.o

depend:: $(LOCALLIBS)
	PICTLIB=.; export PICTLIB; \
	  $(SRCDIR)/Pict/pict -reset lib -set dep -o .depend $(LOCALLIBS)

tags::
	etags $(wildcard *.src */*.src)

include .depend

endif
