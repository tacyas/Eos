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
	../$(OSTYPE)/$(OBJECTNAME) -p 0 0 0 -mat data/test0.mat 
	../$(OSTYPE)/$(OBJECTNAME) -p 1 0 0 -mat data/test1.mat 
	../$(OSTYPE)/$(OBJECTNAME) -p 0.7071 0 0 -mat data/test2.mat 
	@echo "----- Calc check -----"		

clean:
