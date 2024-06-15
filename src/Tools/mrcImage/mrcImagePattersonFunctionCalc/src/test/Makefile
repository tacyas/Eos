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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc -o data/mrc.pat -O data/mrc.patterson
	@echo "----- Calc check -----"		

init:
	pdb2mrc -i data/121p.pdb2 -o data/test.mrc -nx 32 -ny 32 -nz 32 -dx 2 -dy 2 -dz 2 -Sx -32 -Sy -32 -Sz -32 -sig 1.6 -w 1.0
  
clean:
