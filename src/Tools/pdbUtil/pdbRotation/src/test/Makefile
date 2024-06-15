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
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/121p.in -o data/121p-rot.pdb      -EA YOYS 30 60 10
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/121p.in -o data/121p-rot.pdb.cuda -EA YOYS 30 60 10 -cuda 0 
	@echo "----- Calc check -----"		

clean:
