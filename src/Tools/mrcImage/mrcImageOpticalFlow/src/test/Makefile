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
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/test_s8.mrc -i2 data/test1_s8.mrc -o data/test.vx data/test.vy data/test.vz -oBILD data/test.bild -oCOMMAND data/test.cmd -bg 6.0 -oF data/test.fx data/test.fy data/test.fz data/test.di -oSize data/test.flow -bildThresLow 1.0 -bildRangeLow 1.0
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/test_s8.mrc -i2 data/test1_s8.mrc -i3 data/test2_s8.mrc -o data/test.vx data/test.vy data/test.vz -oBILD data/test.bild -oCOMMAND data/test.cmd -bg 6.0 -oF data/test.fx data/test.fy data/test.fz data/test.di -oSize data/test.flow -bildThresLow 0.5 -bildRangeLow 0.5
	@echo "----- Calc check -----"		

clean:
