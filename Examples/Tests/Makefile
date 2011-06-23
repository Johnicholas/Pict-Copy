SRCDIR = ../..
TARGETS = $(patsubst %.pi, %, $(wildcard *.pi))
include $(SRCDIR)/SiteSpecific
include $(SRCDIR)/PiRules
include .depend

test:: $(patsubst %.pi, %.tst, $(wildcard *.pi))

args.tst: args
	-./$< >$<.tmp
	-./$< -int 33 >>$<.tmp
	-./$< -int 33 -int-arg 44 >>$<.tmp
	-./$< -str xxx -a >>$<.tmp
	-./$< -str xxx -a -b >>$<.tmp
	-./$< -str xxx -a -b -a -str ccc >>$<.tmp
	-./$< -str xxx pqrs zzz -b zzz -str ccc 123 123 -a >>$<.tmp
	-diff $<.ok $<.tmp

async.tst: async
	-./async -server >srcv.tmp 2>ssend.tmp &
	-./async >crcv.tmp 2>csend.tmp
	-cat srcv.tmp ssend.tmp crcv.tmp csend.tmp >async.tmp
	-diff async.tmp async.ok

client.tst : client
	@echo client will be tested with server
server.tst : client server
	-./server >server.tmp 2>&1 &
	-./client >client.tmp 2>&1
	-diff client.tmp client.ok
	-diff server.tmp server.ok

persona.tst: persona persona-c
	-./persona >persona.tmp
	-./persona-c >persona-c.tmp
	-diff persona.tmp persona-c.tmp
persona-c: persona.c
	gcc -Wall -o $@ $<

env.tst: env
	-/usr/bin/env - TEST=xxx AAA=aaa BBB=bbb ./env >env.tmp
	-diff env.ok env.tmp

md5.tst: md5
	-./md5 md5.txt >md5.tmp
	-diff md5.ok md5.tmp

clean::
	rm -f persona-c *.o
