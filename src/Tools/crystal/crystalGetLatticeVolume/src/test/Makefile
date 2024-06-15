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
	../$(OSTYPE)/$(OBJECTNAME) -a 3 0 0 -b 0 4 0 -c 0 0 5
	../$(OSTYPE)/$(OBJECTNAME) -a 3 3 0 -b 0 4 4 -c 5 0 5
	../$(OSTYPE)/$(OBJECTNAME) -i data/crystalInfo
	@echo "----- Calc check -----"		

clean:
