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
	../$(OSTYPE)/$(OBJECTNAME) -R ZOYS 20 0 0 -o data/test0.mat 
	../$(OSTYPE)/$(OBJECTNAME) -R YOYS 20 0 0 -o data/test1.mat 
	../$(OSTYPE)/$(OBJECTNAME) -R XOYS 20 0 0 -o data/test2.mat 
	../$(OSTYPE)/$(OBJECTNAME) -R ZOYR 20 0 0 -o data/test3.mat 
	../$(OSTYPE)/$(OBJECTNAME) -R YOYR 20 0 0 -o data/test4.mat 
	../$(OSTYPE)/$(OBJECTNAME) -R XOYR 20 0 0 -o data/test5.mat 
	@echo "----- Calc check -----"		

clean:
