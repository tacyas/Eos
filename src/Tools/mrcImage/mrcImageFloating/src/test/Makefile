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
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.mrc -o data/FlagellaSection.float0 -v 0 -m 0
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.mrc -o data/FlagellaSection.float1 -v 0 -m 1 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.mrc -o data/FlagellaSection.float2 -v 0 -m 2 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.mrc -o data/FlagellaSection.float3 -v 0 -m 3 
	@echo "----- Calc check -----"		

clean:
