SRCDIR=..
include ../SiteSpecific

SUBDIRS = \
  Simple ChanLib Dictionaries Lambda Tests XTests XDemos 

#  Pictsmap Picture ChunDemos Blockade Snc Ants 

all::
	@for d in $(SUBDIRS); do $(MAKE) -C $$d all; done

test::
	@for d in $(SUBDIRS); do $(MAKE) -C $$d test; done

clean::
	@for d in $(SUBDIRS); do $(MAKE) -C $$d clean; done

tags::
	@for d in $(SUBDIRS); do $(MAKE) -C $$d tags; done

depend::
	@for d in $(SUBDIRS); do $(MAKE) -C $$d depend; done

demo::
	@for d in $(SUBDIRS); do $(MAKE) -C $$d demo; done
