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
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.roi -o data/test.edge0 -m 0 -s 32 
	@echo "----- Calc check -----"		

exec1:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.roi -o data/test.edge1 -m 1 -s 32 
	@echo "----- Calc check -----"		


clean:
