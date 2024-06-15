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
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.pdb -o data/121p-trans.pdb -M data/test.mat
	@echo "----- Calc check -----"		
	diff data/121p-trans.pdb data/121p-trans.pdb.tst
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.pdb -o data/test.pdb -M data/test.mat -cuda 0
	@echo "----- Calc check -----"		
	diff data/test.pdb data/121p-trans.pdb.tst

clean:
