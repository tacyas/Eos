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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in  -n 3 -o data/test.out  -m 0; cat data/test.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test1.in -n 3 -o data/test1.out -m 0; cat data/test1.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2.in -n 4 -o data/test2.out -m 0; cat data/test2.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in  -n 3 -o data/test-2.out  -ot 2 -delta data/test.delta -m 0; cat data/test-2.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test1.in -n 3 -o data/test1-2.out -ot 2 -delta data/test-1.delta -m 0; cat data/test1-2.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2.in -n 4 -o data/test2-2.out -ot 2 -delta data/test-2.delta -m 0; cat data/test2-2.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in  -n 3 -o data/test-3.out  -ot 3 -delta data/test.delta -m 0; cat data/test-3.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test1.in -n 3 -o data/test1-3.out -ot 3 -delta data/test-1.delta -m 0; cat data/test1-3.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2.in -n 4 -o data/test2-3.out -ot 3 -delta data/test-2.delta -m 0; cat data/test2-3.out
	@echo "----- Calc check -----"		

clean:
