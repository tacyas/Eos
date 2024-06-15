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
	../$(OSTYPE)/$(OBJECTNAME) -i data/inP0 -it 0 -r data/refP -rt 0 -o data/out0 -ot 0 -Thres 0.01 -Pattern 100
	../$(OSTYPE)/$(OBJECTNAME) -i data/inP0 -it 0 -r data/refP -rt 0 -o data/out0-100 -ot 0 -Thres 0.01 -Pattern 100 -Pick 1.0
	../$(OSTYPE)/$(OBJECTNAME) -i data/inP0 -it 0 -r data/refP -rt 0 -o data/out0-50 -ot 0 -Thres 0.01 -Pattern 100 -Pick 0.5
	../$(OSTYPE)/$(OBJECTNAME) -i data/inP1 -it 0 -r data/refP -rt 0 -o data/out1 -ot 0 -Thres 0.01 -Pattern 100
	../$(OSTYPE)/$(OBJECTNAME) -i data/inP2 -it 0 -r data/refP -rt 0 -o data/out2 -ot 0 -Thres 0.01 -Pattern 100
	../$(OSTYPE)/$(OBJECTNAME) -i data/inP0 -it 0 -r data/refP1 -rt 0 -o data/out0-1 -ot 0 -Thres 0.01 -Pattern 100
	../$(OSTYPE)/$(OBJECTNAME) -i data/inP1 -it 0 -r data/refP1 -rt 0 -o data/out1-1 -ot 0 -Thres 0.01 -Pattern 100
	../$(OSTYPE)/$(OBJECTNAME) -i data/inP2 -it 0 -r data/refP1 -rt 0 -o data/out2-1 -ot 0 -Thres 0.01 -Pattern 100
	@echo "----- Calc check -----"		

clean:
