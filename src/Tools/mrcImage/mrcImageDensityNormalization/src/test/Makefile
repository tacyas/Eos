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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -o data/test.nor0 -m 0 -V 1e6
	mrcImageInfo -i data/test.nor0 -o data/test.nor0.inf -I
	diff data/test.nor0.inf data/test.nor0.inf.ok
	@echo "----- Calc check -----"		

clean:
