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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.edge4 -m 0 -n 4 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.edge8 -m 0 -n 8 
	@echo "----- Calc check -----"		

clean:
