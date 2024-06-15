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
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-shift2.mrc2d -i2 data/121p-shift.mrc2d -o data/121p-shift2.fit -pf data/121p-shift2.param  
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-shift3.mrc2d -i2 data/121p-shift.mrc2d -o data/121p-shift3.fit -pf data/121p-shift3.param  
	@echo "----- Calc check -----"		

init:
	pdb2mrc2d -i data/121p-shift.pdb -o data/121p-shift.mrc2d -s -30 -30 -n 30 30 -d 2 2 -m 3 -sig 3
	mrcImageMultiplying -i data/121p-shift.mrc2d  -o data/121p-shift2.mrc2d -v 2.0
	mrcImageAddValue    -i data/121p-shift2.mrc2d -o data/121p-shift3.mrc2d -v 3.0 

clean:
