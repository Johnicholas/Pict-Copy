SRCDIR = ../..
TARGETS = xtree escher 
BROKEN = bouncy mines life

include $(SRCDIR)/SiteSpecific
include $(SRCDIR)/PiRules
include .depend

demo:: all
	@echo Forking xtree, bouncy, escher, mines, life
	@./xtree & ./bouncy & ./escher & ./mines & ./life &
