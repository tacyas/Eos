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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.out    -EA YOYS 0 0 0
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.out.30 -EA YOYS 30 0 0
	../$(OSTYPE)/$(OBJECTNAME) -I data/test.inlist -O data/test.outlist
	@echo "----- Calc check -----"		

clean:
