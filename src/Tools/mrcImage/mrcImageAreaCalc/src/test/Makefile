include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec exec1 exec2 exec3 

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.area -l data/test.label 
	@echo "----- Calc check -----"		

exec1:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test1.bin -o data/test1.area -l data/test1.label -OH data/test1.hist
	@echo "----- Calc check -----"		

exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2.bin -o data/test2.area -l data/test2.label 
	@echo "----- Calc check -----"		

exec3:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test3.bin -o data/test3.area -l data/test3.label -OH data/test3.hist
	@echo "----- Calc check -----"		

clean:

init:
	pdb2mrc -i data/121p.pdb2 -o data/test.mrc -nx 32 -ny 32 -nz 32 -dx 2 -dy 2 -dz 2 -Sx -32 -Sy -32 -Sz -32 -sig 1.6 -w 1.0
	mrcImageBinalization -i data/test.mrc -o data/test.bin -m 32
	mrcImageErosin       -i data/test.bin -o data/test1.bin 
	mrcImageBinalization -i data/test2.mrc -o data/test2.bin -m 33
	mrcImageErosion      -i data/test2.bin -o data/test3.bin 

