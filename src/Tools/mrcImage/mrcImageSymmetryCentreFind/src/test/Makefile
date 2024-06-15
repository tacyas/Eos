include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

DATA=data/FlagellaSection-0001

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).roi -o $(DATA).out0 -O $(DATA).info0 -m 0  
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).roi -o $(DATA).out1 -O $(DATA).info1 -m 1 
	@echo "----- Calc check -----"		

clean:
