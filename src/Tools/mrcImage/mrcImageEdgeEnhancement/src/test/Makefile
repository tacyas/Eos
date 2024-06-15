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
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/Lighthouse.mrc -o data/Lighthouse.edge.0 -m 0 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/Lighthouse.mrc -o data/Lighthouse.edge.1 -m 1 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/Lighthouse.mrc -o data/Lighthouse.edge.2 -m 2
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/Lighthouse.mrc -o data/Lighthouse.edge.3 -m 3 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/Lighthouse.mrc -o data/Lighthouse.edge.4 -m 4 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/Lighthouse.mrc -o data/Lighthouse.edge.5 -m 5 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/Lighthouse.mrc -o data/Lighthouse.edge.6 -m 6 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/Lighthouse.mrc -o data/Lighthouse.edge.7 -m 7  
	@echo "----- Calc check -----"		

clean:
