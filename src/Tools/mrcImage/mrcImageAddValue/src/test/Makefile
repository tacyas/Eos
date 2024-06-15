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
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.out -v 3
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.out -v 3 -cuda 0
	@echo "----- Calc check -----"		

clean:
