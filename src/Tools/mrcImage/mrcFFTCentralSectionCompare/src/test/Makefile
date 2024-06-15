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
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.0.fft2d -i3d data/121p.fft3d -EA YOYS  0.0  0.0 0.0 -trans 0 0 -InterpMode 1 -o  Out.txt -m 0 

	@echo "----- Calc check -----"		

clean:
