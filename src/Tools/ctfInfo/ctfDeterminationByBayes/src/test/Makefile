include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME) -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i ./data/test.in -i2 ./data/disc.add2.ctf.R.spec -i3 ./data/ctfInfo -i4 ./data/testList.in -o ./data/posterior.out -O ./data/prior.out -n 4 4 -rmax 0.125 -rmin 0.025
	@echo "----- Calc check -----"

clean:
