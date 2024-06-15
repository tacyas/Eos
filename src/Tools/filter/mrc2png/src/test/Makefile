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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2.shrink -o data/test2.shrink.png
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2.byte   -o data/test2.byte.png
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.mrc3d   -o data/121p.mrc3d.png 
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.mrc3d   -o data/121p.mrc3d.png -z 49 
	@echo "----- Calc check -----"		

clean:
