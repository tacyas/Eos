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
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/test_s8.mrc -i2 data/test1_s8.mrc -i3 data/test2_s8.mrc -v3 data/test.vx data/test.vy data/test.vz -o data/test.out -oA data/test.avg
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/test_s8.mrc -i2 data/test1_s8.mrc -i3 data/test2_s8.mrc -v3 data/test.vx data/test.vy data/test.vz -o data/test.enlarge.out -E 2 -oA data/test.enlarge.avg
	@echo "----- Calc check -----"		

clean:
