include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

BASE=data/test
all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(BASE).tst -o $(BASE).hough00 -dTheta 0.5 -dRho 0.5 -M 0 
	../$(OSTYPE)/$(OBJECTNAME) -i $(BASE).tst -o $(BASE).hough01 -dTheta 0.5 -dRho 0.5 -M 0 -m 1
	@echo "----- Calc check -----"		

clean:

init:
	mrcImageModelCreate -o $(BASE).tst -nx 100 -ny 100 -nz 1 -m 2 

