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
	../$(OSTYPE)/$(OBJECTNAME) -o data/test.out -N 256 256 -R 128 -n 18 -delta 1.72
	../$(OSTYPE)/$(OBJECTNAME) -o data/test-1.out -N 256 256 -R 128 -n 18 -delta 1.72 -Shape 1 -m 2
	../$(OSTYPE)/$(OBJECTNAME) -o data/test-2.out -N 256 256 -R 128 -n 18 -delta 1.72 -Shape 2 -m 2
	../$(OSTYPE)/$(OBJECTNAME) -o data/test-3.out -N 512 512 -R 200 -n 18 -delta 1.72 -Shape 3 -m 2
	@echo "----- Calc check -----"		

clean:
