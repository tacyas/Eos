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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.prj.0 -m 0 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.prj.1 -m 1  
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.prj.2 -m 2 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.prj.3 -m 3 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.prj.4 -m 4 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.prj.5 -m 5 
	@echo "----- Calc check -----"		

clean:
