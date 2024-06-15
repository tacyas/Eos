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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.star -o data/testOut.star
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2.cif -o data/testOut2.cif
	@echo "----- Calc check -----"		

clean:
