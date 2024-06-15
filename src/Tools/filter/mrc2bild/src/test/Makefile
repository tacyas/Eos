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
	../$(OSTYPE)/$(OBJECTNAME) -i3 data/test.mrc3d data/test.mrc3d data/test.mrc3d -o data/test-arrow.bild   -zoom 0.01 -color 1 0 0
	../$(OSTYPE)/$(OBJECTNAME) -i3 data/test.mrc3d data/test.mrc3d data/test.mrc3d -o data/test-arrow2.bild  -zoom 0.02 -skip 3 3 3 -color 0 1 0
	../$(OSTYPE)/$(OBJECTNAME) -i3 data/test.mrc3d data/test.mrc3d data/test.mrc3d -o data/test-arrow3.bild  -zoom 0.02 -rangeX 8 12 -rangeY 9 11 -rangeZ 7 13 -rainbowRangeLow 0 -rainbowRangeHigh 120 -rainbowThresLow 0 -rainbowThresHigh 120 -rainbow 0
	../$(OSTYPE)/$(OBJECTNAME) -i3 data/test.mrc3d data/test.mrc3d data/test.mrc3d -o data/test-arrow4.bild  -zoom 0.02 -rangeR 10 10 10 2 -rainbow 0 -rainbowRangeLow 0 -rainbowRangeHigh 120 -rainbowThresLow 0 -rainbowThresHigh 120
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d -o data/test-sphere.bild -zoom 0.01 -m 1 -color 1 0 1
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d -o data/test-sphere2.bild -zoom 0.02 -m 1 -skip 3 3 3 -color 0 1 1
	@echo "----- Calc check -----"		

clean:
