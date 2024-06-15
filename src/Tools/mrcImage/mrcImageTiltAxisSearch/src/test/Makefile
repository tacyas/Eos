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
	../$(OSTYPE)/$(OBJECTNAME) -i data/1vom-rot.mrc -r data/1vom.mrc  -o data/1vom-rot.dat -range 0 20 1 -w 0.82 -M 2 -CM 17 
	../$(OSTYPE)/$(OBJECTNAME) -i data/1vom-rot2.mrc -r data/1vom.mrc  -o data/1vom-rot.dat -range 0 20 1 -w 0.82 -M 2 -CM 17 
	@echo "----- Calc check -----"		

exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -I data/1vom-rot.lst -r data/1vom.mrc  -o data/1vom-rot.dat -range 0 20 1 -w 0.82 -M 2 -CM 17 -O data/1vom-rot.tilt
	@echo "----- Calc check -----"		

initialize:
	pdb2mrc2d -i data/1vom-shift.pdb -o data/1vom.mrc  -d 2 2 -s -64 -64  -n 64 64 -sig 1.6 
	pdb2mrc2d -i data/1vom-shift.pdb -o data/1vom-rot0.mrc  -d 2 2 -s -64 -64  -n 64 64 -sig 1.6 -startEA ZEYS 10  2 0 
	pdb2mrc2d -i data/1vom-shift.pdb -o data/1vom-rot1.mrc  -d 2 2 -s -64 -64  -n 64 64 -sig 1.6 -startEA ZEYS 10 10 0 
	pdb2mrc2d -i data/1vom-shift.pdb -o data/1vom-rot2.mrc  -d 2 2 -s -64 -64  -n 64 64 -sig 1.6 -startEA ZEYS 10 45 0 
	pdb2mrc2d -i data/1vom-shift.pdb -o data/1vom-rot3.mrc  -d 2 2 -s -64 -64  -n 64 64 -sig 1.6 -startEA ZEYS 10 60 0 
	ls -1 data/*rot*.mrc > data/1vom-rot.lst

clean:
