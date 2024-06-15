include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

DATA=data/TEM_filter_sample

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).open -o $(DATA).auto -O $(DATA).win -Wy 1
	@echo "----- Calc check -----"		

clean:

init:
	mrcImageBinalization -i $(DATA).mrc -o $(DATA).bin -t 240
	mrcImageOpening -i $(DATA).bin -o $(DATA).open -times 2 -m 2 -r 1
