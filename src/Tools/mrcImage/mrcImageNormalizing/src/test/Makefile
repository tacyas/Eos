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
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-GC.mrc3d -o data/121p-GC.mode5.mrc3d -m 5 -A 1 -B 0   -paramo data/121p-GC.mode5.mrc3d.param 
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-GC.mrc3d -o data/121p-GC.mode7.mrc3d -m 7 -Low 0.1 -High 0.99  -A 0.9 -B 0.1  -paramo data/121p-GC.mode7.mrc3d.param 
	@echo "----- Calc check -----"		

init:
	pdb2mrc -i data/121p-GC.pdb -o data/121p-GC.mrc3d -nx 40 -ny 40 -nz 40 -Sx -40 -Sy -40 -Sz -40 -dx 2.0 -dy 2.0 -dz 2.0 -w 1.0 -sig 2.0

clean:
