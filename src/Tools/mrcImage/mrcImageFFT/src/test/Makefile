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
	time ../$(OSTYPE)/$(OBJECTNAME)  -i data/testLarge.3d -o data/testLarge.3d.fft
	time ../$(OSTYPE)/$(OBJECTNAME)  -i data/testLarge.3d -o data/testLarge.3d.fft -cuda 0
	@echo "----- Calc check -----"		

clean:
