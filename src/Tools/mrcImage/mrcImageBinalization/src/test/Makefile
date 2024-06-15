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
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.16 -m 16 
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.16.dt -m 16 -dt -1
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.16.o -m 16 -O data/test.mrc.16.Out
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.16.o.dt -m 16 -O data/test.mrc.16.Out
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.32 -m 32 
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.48 -m 48 -p 0.25
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.64 -m 64 
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.80 -m 80
	@echo "----- Calc check -----"		

clean:
