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
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.ali -o data/test.mrc 
	@echo "----- Calc check -----"		 

exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.ali -O
	@echo "----- Calc check -----"		 

clean:
