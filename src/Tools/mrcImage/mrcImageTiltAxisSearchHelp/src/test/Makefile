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
	#../$(OSTYPE)/$(OBJECTNAME) -I data/all.mullst -o1d data/test.o1d -o1de data/test.o1de -o2d data/test.o2d -aP 245.5 245.5 0 -a 0 0 -R 0.05 0.1
	#../$(OSTYPE)/$(OBJECTNAME) -I data/all.mullst -o1d data/test-01.o1d -o1de data/test-01.o1de -o2d data/test-01.o2d -aP 128 245.5 0 -a 0 0 -R 0.05 0.1
	../$(OSTYPE)/$(OBJECTNAME) -I data/all.mullst -o1d data/test-02.o1d -o1de data/test-02.o1de -o2d data/test-02.o2d -aP 128 245.5 0 -a 0.1 0 -R 0.05 0.1
	#../$(OSTYPE)/$(OBJECTNAME) -I data/all.mullst -o1d data/test2.o1d -o1de data/test2.o1de -o2d data/test2.o2d -aP 245.5 235.5 245.5 -a 0 0 -R 0.05 0.1
	#../$(OSTYPE)/$(OBJECTNAME) -I data/all.mullst -o1d data/test3.o1d -o1de data/test3.o1de -o2d data/test3.o2d -aP 245.5 245.5 245.5 -a 7.5 0 -R 0.05 0.1
	@echo "----- Calc check -----"		

clean:

