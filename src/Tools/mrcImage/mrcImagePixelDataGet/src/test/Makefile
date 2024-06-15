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
	time ../$(OSTYPE)/$(OBJECTNAME)  -i data/test.in -o data/test.out1 -x 128   -y 128   -z 0 -m 0
	time ../$(OSTYPE)/$(OBJECTNAME)  -i data/test.in -o data/test.out2 -x 128.2 -y 128.2 -z 0 -m 1 
	time ../$(OSTYPE)/$(OBJECTNAME)  -i data/test.in -o data/test.out3 -In data/test.inCoord -m 0
	time ../$(OSTYPE)/$(OBJECTNAME)  -i data/test.in -o data/test.out4 -In data/test.inCoord -m 1
	time ../$(OSTYPE)/$(OBJECTNAME)  -i data/test.in -o data/test.out5 -In data/test.inCoord -m 0 -cuda 0
	time ../$(OSTYPE)/$(OBJECTNAME)  -i data/test.in -o data/test.out6 -In data/test.inCoord -m 1 -cuda 0 
	time ../$(OSTYPE)/$(OBJECTNAME)  -i data/test.in -o data/test.out7 -In data/test.inCoord -om 1 -m 2 
	@echo "----- Calc check -----"		

clean:
