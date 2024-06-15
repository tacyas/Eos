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
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.in -r data/121p-rot.in -cor data/test.cor -o data/test.out -fit data/test.fit -EA YOYS -Rot1 0 360 30 -Rot2 0 180 30 -Rot3 0 360 30 -m 2 -MR 16 -M 16 -Xrange -5 5 -Yrange -5 5 -Zrange -5 5
	@echo "----- Calc check -----"		

exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.in -r data/121p-rotmov.in -cor data/test2.cor -o data/test2.out -fit data/test2.fit -EA YOYS -Rot1 0 360 30 -Rot2 0 180 30 -Rot3 0 360 30 -m 2 -MR 16 -M 16 -Xrange -5 5 -Yrange -5 5 -Zrange -5 5
	@echo "----- Calc check -----"		

clean:

data::
	pdbRotation -i data/121p.pdb -o data/121p-rot.pdb -EA YOYS -60 -90 -30  
	pdbMove     -i data/121p-rot.pdb -o data/121p-rotmov.pdb -x 4 -y 8 -z 12 
	pdb2mrc -i data/121p.pdb     -o data/121p.in     -nx 64 -ny 64 -nz 64 -dx 2 -dy 2 -dz 2 -Sx -64 -Sy -64 -Sz -64 -m 0 -sig 3
	pdb2mrc -i data/121p-rot.pdb -o data/121p-rot.in -nx 64 -ny 64 -nz 64 -dx 2 -dy 2 -dz 2 -Sx -64 -Sy -64 -Sz -64 -m 0 -sig 3
	pdb2mrc -i data/121p-rotmov.pdb -o data/121p-rotmov.in -nx 64 -ny 64 -nz 64 -dx 2 -dy 2 -dz 2 -Sx -64 -Sy -64 -Sz -64 -m 0 -sig 3
