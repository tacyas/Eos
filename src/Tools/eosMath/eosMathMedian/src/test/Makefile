include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test-1.out -m 1
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2.in -o data/test2.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2.in -o data/test2-1.out -m 1
	@echo "----- Calc check -----"		

clean:
