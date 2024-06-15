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
	../$(OSTYPE)/$(OBJECTNAME) -o data/test.out -Nx 50 -Ny 50 -Nz 1 -M 2 -d 2.0 
	../$(OSTYPE)/$(OBJECTNAME) -r data/test.mrc -o data/test.outRef 
	../$(OSTYPE)/$(OBJECTNAME) -o data/test.outDef -Nx 50 -Ny 50 -Nz 1 -Def -v 1
	@echo "----- Calc check -----"		

clean:
