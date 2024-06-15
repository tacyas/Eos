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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2.tst -o data/test2.NoHole4 -n 4 -bA data/test2.area4 -bL data/test2.label4 -b data/test2.black4
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2.tst -o data/test2.NoHole8 -n 8 -bA data/test2.area8 -bL data/test2.label8 -b data/test2.black8
	@echo "----- Calc check -----"		

exec3:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test3.tst -o data/test3.NoHole6 -n 6 -bA data/test3.area6 -bL data/test3.label6 -b data/test3.black6
	@echo "----- Calc check -----"		

init:
	mrcImageShrink -i data/test2.mrc -o data/test2.shrink -S 4 
	mrcImageBinalization -i data/test2.shrink -o data/test2.bin -m 33 
	mrcImageOpening -i data/test2.bin -o data/test2.open -m 1 -times 3 
	cd data; ln -sf test2.open test2.tst
	mrcImageBinalization -i data/test3.mrc -o data/test3.bin -m 0 -t 1.2 
	cd data; ln -sf test3.bin test3.tst

clean:
