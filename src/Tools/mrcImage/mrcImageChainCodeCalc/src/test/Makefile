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
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.bin -o data/test.chain0 -m 0
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.bin -o data/test.chain1 -m 1 
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.bin -o data/test.chain2 -m 2
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.bin -o data/test.chain3 -m 3 
	@echo "----- Calc check -----"		

clean:
