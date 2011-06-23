############################################################################
###                                                                      ###
###                    Makefile for PICT system                          ###
###                                                                      ###
###            Site-specific settings are in "SiteSpecific"              ###
###                                                                      ###
############################################################################

SRCDIR = .
include SiteSpecific
-include Config/Config

ifeq ($(PICTDEVEL),yes)
  all::
else
  all:: show
endif

everything: examples
        ifeq ($(PICTDEVEL),yes)
	@$(MAKE) -C Tex all
        endif
	(cd Tex; $(MAKE) export)

examples: all
	@$(MAKE) -C Examples all
        ifeq ($(PICTDEVEL),yes)
	@$(MAKE) -C HardHat all
        endif

demo:: examples
	@$(MAKE) -C Examples demo

all::
	@$(MAKE) -C Config all
	@$(MAKE) -C Tools all
	@$(MAKE) -C Pict all
	@$(MAKE) -C Runtime all
	@$(MAKE) -C Lib all

install:: $(INSTALLDIR) $(INSTALLLIB)
	@$(MAKE) -C Config all
	@$(MAKE) -C Tools install
	@$(MAKE) -C Pict install
	@$(MAKE) -C Runtime install
	@$(MAKE) -C Lib install

test:: all
	@$(MAKE) -C Examples test

show:
	@echo "SRCDIR     " = $(SRCDIR)
	@echo "INSTALLDIR " = $(INSTALLDIR)
	@echo "INSTALLLIB " = $(INSTALLLIB)
	@echo "GCC        " = $(GCC)
	@echo "CWD        " = $(CWD)
	@echo "X11INCLUDE " = $(X11INCLUDE)
	@echo "X11LIB     " = $(X11LIB)
	@echo "X11EXTRA   " = $(X11EXTRA)
	@echo "PICTSITE   " = $(PICTSITE)
	@echo "PICTDEVEL  " = $(PICTDEVEL)
	@echo "OCAMLOPT   " = $(OCAMLOPT)
	@echo 

tags::
	@$(MAKE) -C Config all
	@$(MAKE) -C Tools all
	etags SiteSpecific \
              `find . -name Makefile -print -o -name '*Rules' -print `
	mv TAGS MTAGS
	etags `find Tex \
	  '(' -name '*.src' -o -name '*.err' -o -name '*.pi' ')' -print`
	mv TAGS TTAGS
	etags `find Lib Examples HardHat \
	  '(' -name '*.src' -o -name '*.err' -o -name '*.pi' ')' -print`
	@$(MAKE) -C Config tags
	@$(MAKE) -C Tools tags
	@$(MAKE) -C Pict tags
	@$(MAKE) -C Runtime tags
	@$(MAKE) -C Lib tags
	@$(MAKE) -C Examples tags
	@$(MAKE) -C Doc tags
        ifeq ($(PICTDEVEL),yes)
	@$(MAKE) -C Tex tags
	@$(MAKE) -C Misc tags
	-@$(MAKE) -C HardHat tags
        endif

clean::
	@$(MAKE) -C Config clean
	@$(MAKE) -C Tools clean
	@$(MAKE) -C Pict clean
	@$(MAKE) -C Runtime clean
	@$(MAKE) -C Lib clean
	@$(MAKE) -C Examples clean
	@$(MAKE) -C Doc clean
	rm -f TAGS MTAGS TTAGS ANNOUNCE
        ifeq ($(PICTDEVEL),yes)
	-@$(MAKE) -C Tex clean
	-@$(MAKE) -C Misc clean
	-@$(MAKE) -C HardHat clean
	@$(MAKE) -C Gnu clean
	@$(MAKE) -C Html clean
        endif

$(INSTALLDIR):
	mkdir -p $(INSTALLDIR)

$(INSTALLLIB):
	mkdir -p $(INSTALLLIB)

ifeq ($(PICTDEVEL),yes)
all:: ANNOUNCE
ANNOUNCE: Html/Pict.html
	-rm -f $@
	lynx -dump -nolist $< >$@
	chmod -w $@
endif

bin-dist: all
	@$(MAKE) -C Examples clean
	@$(MAKE) -C Tex export
	tar --create --verbose --file ../pict-$(VERSION).binary.tar.gz \
	  --compress --directory .. pict --exclude='pict/Pict/parser.*' \
	  --exclude='pict/Pict/lexer.*' --exclude 'pict/Pict/*.o' \
	  --exclude=core --exclude=a.out --exclude=quickTest.pi \
	  --exclude=quickTest --exclude=noLib --exclude=noLib.pi \
	  --exclude=pict/Tex --exclude=pict/Misc --exclude=pict/HardHat \
	  --exclude='*TAGS' --exclude=CVS --exclude=.cvsignore \
	  --exclude=pict/Gnu --exclude=pict/Html --exclude='*.ml' \
	  --exclude='*.mli' --exclude='*.cmo' --exclude='*.cmi' \
	  --exclude='*.cmx' --exclude='.PICT*.c' --exclude='.PICT*.o' \
	  --exclude='.#*' --exclude='pict/Runtime/*.o' \
	  --exclude='pict/Runtime/*.c' --exclude='pict/Runtime/*.debug' \
	  --exclude='pict/Runtime/*.prof' --exclude='pict/Tools/*.o' \
	  --exclude='pict/Tools/*.ml' --exclude='pict/Tools/*.mll' \
	  --exclude='Examples/XDemos/bouncy.pi' \
	  --exclude='Examples/XDemos/mines.pi' \
	  --exclude='Examples/XDemos/life.pi' \
	  --exclude='Examples/XDemos/boards' \
	  --exclude='Examples/Picture' \
	  --exclude='Examples/Pictsmap' \
	  --exclude='Examples/Blockade' \
	  --exclude='Examples/Snc' \
	  --exclude='*~' --exclude='*/.#*'

# Build tar files containing various subsets of the current version
EXPORTTMP=pict-$(VERSION)
EXPORTTMPPATH=$(HOME)/$(EXPORTTMP)
EXPORTDIR=$(HOME)/$(EXPORTTMP)-export
export: all
	$(MAKE) -C Tex export
	@$(MAKE) export1

export1:
	-rm -rf $(EXPORTDIR)
	mkdir $(EXPORTDIR)
	-rm -rf $(EXPORTTMPPATH)
	cp -r . $(EXPORTTMPPATH)
	(cd $(EXPORTTMPPATH); $(MAKE) clean)
	(cd $(HOME); tar cvf - $(EXPORTTMP) \
           | gzip --best > $(EXPORTTMP)-devel.tar.gz)
	(cd $(EXPORTDIR); mkdir Html)
	(cd $(EXPORTTMPPATH)/Html; rm Makefile; mv -f * $(EXPORTDIR)/Html)
	(cd $(EXPORTTMPPATH); rm -rf Misc HardHat Tex Html)
	(cd $(HOME); tar cvf - $(EXPORTTMP) \
           | gzip --best > $(EXPORTTMP).tar.gz)
	(cd $(HOME); mv $(EXPORTTMP).tar.gz $(EXPORTDIR))
	(cd $(EXPORTDIR); mkdir Doc)
	(cd $(EXPORTTMPPATH); rm Makefile; mv -f Doc/* $(EXPORTDIR)/Doc; \
         rm -rf Doc)
	(cd $(EXPORTDIR)/Doc; gzip --best *.ps)
	rm -rf $(EXPORTTMPPATH) 
	@echo
	@echo
	@echo "---> don't forget to tag this version with CVS <----"
	@echo
