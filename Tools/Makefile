SRCDIR = ..
TARGETS = src2tex src2pi
include ../SiteSpecific

install:: all
	cp -f src2tex src2pi $(INSTALLLIB)
	chmod 755 $(INSTALLLIB)/src2tex $(INSTALLLIB)/src2pi
tags::
	etags *.mll

ifneq ($(wildcard *.mll),)

clean::
	rm -f *.cmi *.cmo *.cmx *.o a.out 
	rm -f src2tex.ml src2pi.ml $(TARGETS)

%.ml : %.mll
	@rm -f $@
	ocamllex $<
	@chmod -w $@
 
src2pi src2tex : % : %.ml
  ifeq ($(OCAMLOPT),yes)
	ocamlopt -o $@ $<
  else
	ocamlc -custom -o $@ $<
  endif

endif
