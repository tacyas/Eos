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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d -o data/test.mrc2d.z.0 -z 0
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d -o data/test.mrc2d     -z -1 
	@echo "----- Calc check -----"		

clean:
