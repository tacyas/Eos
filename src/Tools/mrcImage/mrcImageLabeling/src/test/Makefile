include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec exec2

DATA=data/TEM_filter_sample

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).open -n 4 -o $(DATA).label0 -m 0 
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).open -n 4 -o $(DATA).label1 -m 1 
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).open -n 8 -o $(DATA).label1.8  -m 1 
	@echo "----- Calc check -----"		

exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -n  6 -o data/test.label6  -m 1 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -n 18 -o data/test.label18 -m 1 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -n 26 -o data/test.label26 -m 1 
	@echo "----- Calc check -----"		

clean:

init:
	mrcImageBinalization -i $(DATA).mrc -o $(DATA).bin -t 240 
	mrcImageOpening -i $(DATA).bin -o $(DATA).open -m 2 -times 2 -r 1 
