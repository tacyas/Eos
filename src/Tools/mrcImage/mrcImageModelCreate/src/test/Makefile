include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec: data/test-8.mrc data/test-9.mrc

data/test-8.mrc:../$(OSTYPE)/$(OBJECTNAME)
	@echo "----- Execution Check : 8-----"
	../$(OSTYPE)/$(OBJECTNAME) -m 8 -o data/test-8.mrc -nx 32 -ny 32 -nz 32 -lx 2 -ly 2 -lz 2 -l 16 -r 4 
	@echo "----- Calc check -----"		

data/test-9.mrc:../$(OSTYPE)/$(OBJECTNAME)
	@echo "----- Execution Check : 9-----"
	../$(OSTYPE)/$(OBJECTNAME) -m 9 -o data/test-9.mrc -nx 256 -ny 32 -nz 1 -lx 1 -ly 1 -lz 1 -range 0 20 
	@echo "----- Calc check -----"		

clean:
