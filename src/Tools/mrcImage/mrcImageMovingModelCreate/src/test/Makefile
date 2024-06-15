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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test0.array -o data/test0.lst -O data/movie0_%04d.mrc
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.array -o data/test.lst -O data/movie_%04d.mrc
	@echo "----- Calc check -----"		

clean:
