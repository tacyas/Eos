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
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-centre.mrc -o data/121p-centre.radial.Cyl -centre 49 49 -m 0 -Avg
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-centre.mrc -o data/121p-centre.radial.Sph -Cs 49 49 49 -m 1 -Avg
	@echo "----- Calc check -----"		

clean:
