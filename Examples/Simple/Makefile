SRCDIR = ../..
TARGETS = hello seq hamming ackermann sieve hanoi tak queens hybrid
include ../../SiteSpecific
include ../../PiRules
include .depend

REPLFLAGS   = -set replicatedContinuations
ALLFLAGS    = $(REPLFLAGS) -set unsafeAssumeReplicated
UNFAIRFLAGS = $(ALLFLAGS) -set unfair
PROFFLAGS   = -set profiling

repl/% : %.pi
	@echo "Pict: $< $(REPLFLAGS) $(PIFLAGS) ---> $@"
	@$(EXPORTS) $(SRCDIR)/Pict/pict $(REPLFLAGS) $(PIFLAGS) -o $@ $<

allopt/% : %.pi
	@echo "Pict: $< $(ALLFLAGS) $(PIFLAGS) ---> $@"
	@$(EXPORTS) $(SRCDIR)/Pict/pict $(ALLFLAGS) $(PIFLAGS) -o $@ $<

unfair/% : %.pi
	@echo "Pict: $< $(UNFAIRFLAGS) $(PIFLAGS) ---> $@"
	@$(EXPORTS) $(SRCDIR)/Pict/pict $(UNFAIRFLAGS) $(PIFLAGS) -o $@ $<

prof/% : %.pi
	@echo "Pict: $< $(PROFFLAGS) $(PIFLAGS) ---> $@"
	@$(EXPORTS) $(SRCDIR)/Pict/pict $(PROFFLAGS) $(PIFLAGS) -o $@ $<
	@$(INSTALLDIR)/pict $(PIFLAGS) -o $@ $(CWD)/$<

ocaml/% : %.ml
	ocamlc -custom -o $@ $(ZFLAGS) $<

ocamlopt/% : %.ml
	ocamlopt -o $@ $(ZFLAGS) $<

test:: $(patsubst %.pi, %.tst, $(wildcard *.pi))

RACERS = \
  $(patsubst %.ml, repl/%, $(wildcard *.ml)) \
  $(patsubst %.ml, allopt/%, $(wildcard *.ml)) \
  $(patsubst %.ml, unfair/%, $(wildcard *.ml)) \
  $(patsubst %.ml, ocaml/%, $(wildcard *.ml)) \
  $(patsubst %.ml, ocamlopt/%, $(wildcard *.ml))

race: repl allopt unfair ocaml ocamlopt $(RACERS)
	@for file in $(RACERS); do \
	  echo Timing $$file; \
	  ($$file >/dev/null; times); \
	done

PROFS = $(patsubst %.ml, prof/%, $(wildcard *.ml))

profile: $(PROFS)
	@for file in $(PROFS); do \
	  echo Profiling $$file; \
	  $$file >/dev/null; \
	done

prof:
	mkdir prof
repl:
	mkdir repl
allopt:
	mkdir allopt
unfair:
	mkdir unfair
ocaml:
	mkdir ocaml
ocamlopt:
	mkdir ocamlopt

clean::
	rm -f *.o *.cmo *.cmi
	rm -rf prof repl allopt unfair ocaml ocamlopt
