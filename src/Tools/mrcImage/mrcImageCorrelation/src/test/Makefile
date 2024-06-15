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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.move -r data/test.move2 -o data/test.cor -s data/test.shift -m 16 -corInfo data/test.corinfo
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.mrc3d.move -r data/121p.mrc3d -o data/121p.cor -s data/121p.shift -m 16 -corInfo data/121p.corinfo
	@echo "----- Calc check -----"		

init:
	pdb2mrc -i data/121p-centre.pdb -o data/121p.mrc3d  -Sx -50 -Sy -50 -Sz -50 -nx 100 -ny 100 -nz 100 -dx 1 -dy 1 -dz 1 -m 0 -sig 1.6	
	pdb2mrc -i data/121p-centre.pdb -o data/121p.mrc3d.move  -Sx -40 -Sy -45 -Sz -55 -nx 100 -ny 100 -nz 100 -dx 1 -dy 1 -dz 1 -m 0 -sig 1.6	

clean:
