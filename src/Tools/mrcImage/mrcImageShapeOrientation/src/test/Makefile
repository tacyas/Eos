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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.out -thres 0
	cat data/test.out
	@echo "----- Calc check -----"		

clean:

data::
	mrcImageGaussSphere -o data/test.in -sigmax 10 -sigmay 20 -sigmaz 30 -size 2 -W 50 -S 50 -H 50
