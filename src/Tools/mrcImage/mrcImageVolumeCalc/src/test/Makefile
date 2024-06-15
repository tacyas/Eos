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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d -o data/test.mrc3dvol -I -n 1 -M 88000 -format "%g %g %d %d %g" -R 0 200 10
	@echo "----- Calc check -----"		
	diff data/test.mrc3dvol data/test.mrc3dvol.original

clean:
