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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.bin.6  -n  6 -m 0 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.bin.18 -n 18 -m 0 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.bin.26 -n 26 -m 0 
	@echo "----- Calc check -----"		

exec2D:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2D.bin -o data/test2D.bin.4  -n 4 -m 0 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2D.bin -o data/test2D.bin.8 -n 8 -m 0 
	@echo "----- Calc check -----"		

clean:
