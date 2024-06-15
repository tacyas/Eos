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
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.transpose.0 -m 0
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.transpose.1 -m 1 
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.transpose.2 -m 2 
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.transpose.3 -m 3 
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.transpose.4 -m 4 
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc -o data/test.mrc.transpose.5 -m 5 
	@echo "----- Calc check -----"		

init:
	pdb2mrc -i data/121p.pdb2 -o data/test.mrc -nx 64 -ny 48 -nz 32 -dx 2 -dy 2 -dz 2 -Sx -64 -Sy -48 -Sz -32 -sig 1.6 -w 1.0
   
clean:
