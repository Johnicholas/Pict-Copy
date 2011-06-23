SRCDIR = ../..
TARGETS = lambda
include $(SRCDIR)/SiteSpecific
include $(SRCDIR)/PiRules
include .depend

test:: $(patsubst %.pi, %.tst, $(wildcard *.pi))
