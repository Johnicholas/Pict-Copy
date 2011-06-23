SRCDIR=..
NOPICTDEP=yes
include $(SRCDIR)/SiteSpecific
include $(SRCDIR)/PiRules
PIFLAGS += -reset lib

all:: pict

$(INSTALLDIR)/% : % Makefile ../SiteSpecific
	@echo Generating $@
	@rm -f $@
	@echo '#!/bin/sh'                 >$@
	@echo VERSION=$(VERSION)          >>$@
	@echo export VERSION              >>$@
	@echo PICTLIB=$(INSTALLLIB)       >>$@
	@echo export PICTLIB              >>$@
	@echo PICTRTS=$(INSTALLLIB)       >>$@
	@echo export PICTRTS              >>$@
	@echo X11INCLUDE=$(X11INCLUDE)    >>$@
	@echo export X11INCLUDE           >>$@
	@echo "X11EXTRA=\"$(X11EXTRA)\""  >>$@
	@echo export X11EXTRA             >>$@
	@echo X11LIB=$(X11LIB)            >>$@
	@echo export X11LIB               >>$@
	@echo GCC=$(GCC)                  >>$@
	@echo export GCC                  >>$@
	@echo exec $(INSTALLLIB)/$< $$'*' >>$@
	@chmod 755 $@

install:: all $(INSTALLDIR)/pict
	cp -f pict $(INSTALLLIB)
	chmod 755 $(INSTALLLIB)/pict

ifneq ($(wildcard *.ml),)

%.cmi : %.mli
	@echo "OCAML: $< $(ZFLAGS) ---> $@"
	@ocamlc $(ZFLAGS) -c $(CWD)/$<

%.cmo : %.ml
	@echo "OCAML: $< $(ZFLAGS) ---> $@"
	@ocamlc $(ZFLAGS) -c $(CWD)/$<

%.cmx : %.ml
	@echo "OCAMLOPT: $< $(ZFLAGS) ---> $@"
	@ocamlopt $(ZFLAGS) -c $(CWD)/$<

OBJS = \
  error.cmo misc.cmo debug.cmo flags.cmo stats.cmo var.cmo ccode.cmo \
  kind.cmo syntax.cmo lexer.cmo parser.cmo types.cmo kinding.cmo leq.cmo \
  inter.cmo simplify.cmo match.cmo check.cmo lint.cmo status.cmo fv.cmo \
  occur.cmo optimise.cmo copt.cmo codegen.cmo compile.cmo

ZFLAGS += -unsafe

ifeq ($(OCAMLOPT),yes)
  OBJS := $(patsubst %.cmo, %.cmx, $(OBJS))
  LINK = unix.cmxa -cclib -lunix
else
  LINK = -custom unix.cma -cclib -lunix
endif

pict: $(OBJS)
  ifeq ($(OCAMLOPT),yes)
	ocamlopt -o $@ $(ZFLAGS) $(LINK) $(OBJS)
  else
	ocamlc -o $@ $(ZFLAGS) $(LINK) $(OBJS)
  endif

parser.mly: parser.src
	@rm -f parser.mly
	$(SRCDIR)/Tools/src2pi <parser.src >parser.mly
	@chmod -w parser.mly

parser.ml parser.mli: parser.mly
	@rm -f parser.ml parser.mli
	ocamlyacc -v parser.mly
	@chmod -w parser.ml parser.mli

lexer.mll: lexer.src
	@rm -f lexer.mll
	$(SRCDIR)/Tools/src2pi <lexer.src >lexer.mll
	@chmod -w lexer.mll

lexer.ml: lexer.mll
	@rm -f lexer.ml
	ocamllex lexer.mll
	@chmod -w lexer.ml

tags:: 
	etags $(wildcard *.ml *.mli *.src)

depend:: lexer.ml parser.ml parser.mli
	ocamldep *.mli *.ml > .depend

clean::
	rm -f *.cmi *.cmo *.cmx *.o *.px a.out quickTest noLib pict
	rm -f lexer.mll lexer.ml parser.mly parser.ml parser.mli parser.output

safeTest:
	$(MAKE) -C $(SRCDIR) all
	$(MAKE) quickTest

libTest:
	$(MAKE) -C $(SRCDIR)/Lib all
	$(MAKE) quickTest

noLib: noLib.pi pict
quickTest: quickTest.pi pict

include .depend

endif
