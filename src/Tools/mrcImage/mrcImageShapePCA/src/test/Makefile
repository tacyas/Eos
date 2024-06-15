include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec exec3

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec: exec2
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-move.mrc -o data/121p-move.mrc.PCA -m 7 -C 23696.7 
	pdbPCA -i data/121p-move.pdb -o data/121p-move.pdb.PCA
	@echo "----- Calc check -----"		

exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/myosinSwissModRefine2.mrc -o data/myosinSwissModRefine2.mrc.PCA -m 7 -C 3.11319 
	pdbPCA -i data/myosinSwissModRefine2.pdb -o data/myosinSwissModRefine2.pdb.PCA
	@echo "----- Calc check -----"		

exec3:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-move-2d.mrc -o data/121p-move-2d.mrc.PCA -m 7 -C 1e5 
	@echo "----- Calc check -----"		

clean:
