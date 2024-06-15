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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.out6  -n  6 -oS data/test.outSurface6  -oSA data/test.info6 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.out18 -n 18 -oS data/test.outSurface18 -oSA data/test.info18
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.out26 -n 26 -oS data/test.outSurface26 -oSA data/test.info26 
	@echo "----- Calc check -----"		
	mrc2gif -i data/test.bin -o data/test.bin.60.gif -z 60
	mrc2gif -i data/test.out6 -o data/test.out6.60.gif -z 60
	mrc2gif -i data/test.out18 -o data/test.out18.60.gif -z 60
	mrc2gif -i data/test.out26 -o data/test.out26.60.gif -z 60
	mrc2gif -i data/test.outSurface6 -o data/test.outSurface6.60.gif -z 60
	mrc2gif -i data/test.outSurface18 -o data/test.outSurface18.60.gif -z 60
	mrc2gif -i data/test.outSurface26 -o data/test.outSurface26.60.gif -z 60
	mrc2gif -i data/test.bin -o data/test.bin.55.gif -z 55
	mrc2gif -i data/test.out6 -o data/test.out6.55.gif -z 55
	mrc2gif -i data/test.out18 -o data/test.out18.55.gif -z 55
	mrc2gif -i data/test.out26 -o data/test.out26.55.gif -z 55
	mrc2gif -i data/test.outSurface6 -o data/test.outSurface6.55.gif -z 55
	mrc2gif -i data/test.outSurface18 -o data/test.outSurface18.55.gif -z 55
	mrc2gif -i data/test.outSurface26 -o data/test.outSurface26.55.gif -z 55
clean:
