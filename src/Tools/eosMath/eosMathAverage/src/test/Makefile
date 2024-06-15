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
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.in -o data/test.out
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.in -o data/test.trim.out -trim 0.2
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test2.in -o data/test2.out
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test2.in -o data/test2.trim.out -trim 0.2
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test2.in -o data/test2-1.out -m 1
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test2.in -o data/test2-1.trim.out -m 1 -trim 0.2
	@echo "----- Calc check -----"		

clean:
