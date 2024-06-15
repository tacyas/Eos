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
	../$(OSTYPE)/$(OBJECTNAME) -i data/1atnH.mrc3d -ip data/1atnH.output.pdb.coor -o data/1atnH.pdb2.current -s 0.0625
	@echo "----- Calc check -----"		

exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/1atnH.mrc3d -ip data/1atnH.output.pdb.coord2 -o data/1atnH.pdb2.current2 -s 0.0625
	../$(OSTYPE)/$(OBJECTNAME) -i data/1atnH.mrc3d -ip data/1atnH.output.pdb.coord2 -o data/1atnH.pdb2.current2NoWat -s 0.0625 -nowat
	@echo "----- Calc check -----"		

clean:
