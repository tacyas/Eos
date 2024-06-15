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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.out.0 -m 0
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.out.1 -m 1 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.out.2 -m 2 
	@echo "----- Calc check -----"		

clean:
