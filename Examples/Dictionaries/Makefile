SRCDIR = ../..
TARGETS = bag dict hash
include $(SRCDIR)/SiteSpecific
include $(SRCDIR)/PiRules
include .depend

test:: $(patsubst %.pi, %.tst, $(wildcard *.pi))
