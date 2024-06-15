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
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.pdb -o data/121p-CA.pdb
	@echo "----- Calc check -----"		
	diff data/121p-CA.pdb.org data/121p-CA.pdb

exec1:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.pdb -oCoord data/121p.coord
	@echo "----- Calc check -----"		
	diff data/121p.coord.org data/121p.coord



clean:
