SRCDIR = ../..
TARGETS = semaphore sync simple broadcast torus
include $(SRCDIR)/SiteSpecific
include $(SRCDIR)/PiRules
include .depend

test:: $(patsubst %.pi, %.tst, $(wildcard *.pi))
