include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec exec2 exec3 exec4

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME)  -i data/121p.shift.pdb -o data/121p.mrc2d -O data/121p.mrc2dStack -s -30 -30 -n 13 13 -d 5 5 -Rot 8 8  -m 3 -sig 3
	@echo "----- Calc check -----"		

exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME)  -i data/121p.shift.pdb -o data/121p.mrc2d2 -O data/121p.mrc2dStack2 -s -32 -32 -n 32 32 -d 2 2 -Rot 12 12 -m 3 -sig 3 
	@echo "----- Calc check -----"		

exec3:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME)  -i data/121p.shift.pdb -o data/121p.mrc2d3 -O data/121p.mrc2dStack3 -s -32 -32 -n 32 32 -d 2 2 -Rot 4 4 -m 3 -sig 3 
	@echo "----- Calc check -----"		

exec4:

clean:
