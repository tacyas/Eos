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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.nor -o data/test.0.0.nor -m 0 -P 0               -paramo data/test.0.0.param
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.nor -o data/test.0.1.nor -m 0 -P 1 -thres 0.9999 -paramo data/test.0.1.param 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.nor -o data/test.0.2.nor -m 0 -P 2 -thres 0.01   -paramo data/test.0.2.param
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.nor -o data/test.1.0.nor -m 1 -P 0               -paramo data/test.1.0.param
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.nor -o data/test.1.1.nor -m 1 -P 1 -thres 0.9999 -paramo data/test.1.1.param
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.nor -o data/test.1.2.nor -m 1 -P 2 -thres 0.01   -paramo data/test.1.2.param
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.nor -o data/test.2.0.nor -m 2 -P 0               -paramo data/test.2.0.param
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.nor -o data/test.2.1.nor -m 2 -P 1 -thres 0.9999 -paramo data/test.2.1.param
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.nor -o data/test.2.2.nor -m 2 -P 2 -thres 0.01   -paramo data/test.2.2.param
	@echo "----- Calc check -----"		

clean:
