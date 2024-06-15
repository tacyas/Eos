include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

DATA=FlagellaSectionROI

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/$(DATA).dist  -o data/$(DATA).max -S 3 -T 1
	@echo "----- Calc check -----"		

clean:

init:
	mrcImageBinalization -i data/$(DATA).mrc -o data/$(DATA).bin -m 0 -t 1.5
	mrcImageDistanceConversion -i data/$(DATA).bin -o data/$(DATA).dist
