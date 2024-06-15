include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec: exec4 exec5 exec6

exec4:
	@echo "----- Execution Check -----"
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth4.1 -m 4 -M 1 -r 2 -times 1
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth4.2 -m 4 -M 1 -r 2 -times 2 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth4.3 -m 4 -M 1 -r 2 -times 3 

exec5:
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth5.1 -m 5 -times 1 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth5.2 -m 5 -times 2 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth5.3 -m 5 -times 3 

exec6:
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth6.1 -m 6 -times 1 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth6.2 -m 6 -times 2 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth6.3 -m 6 -times 3 
	@echo "----- Calc check -----"		

exec7:
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth7.1 -m 7 -sigma 5 -times 1 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth7.2 -m 7 -sigma 5 -times 2 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth7.3 -m 7 -sigma 5 -times 3 
	@echo "----- Calc check -----"		

exec8:
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth7.1 -m 8 -times 1 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth7.2 -m 8 -times 2 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-noise1.mrc -o data/test-noise1.smooth7.3 -m 8 -times 3 
	@echo "----- Calc check -----"		

clean:
