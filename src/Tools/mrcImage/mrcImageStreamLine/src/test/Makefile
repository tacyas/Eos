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
	../$(OSTYPE)/$(OBJECTNAME)  -i2 data/test.2d.dx data/test.2d.dy -o data/test.2d.streamLine -oP data/test.2d.streamLineA -oBILD data/test.2d.streamLine.bild -f 25
	../$(OSTYPE)/$(OBJECTNAME)  -i2 data/test.2d.dx data/test.2d.dy -o data/test.2d.streamLine2 -oP data/test.2d.streamLine2A -oBILD data/test.2d.streamLine2.bild -dt 0.2 -f 100
	../$(OSTYPE)/$(OBJECTNAME)  -i3 data/test.3d.dx data/test.3d.dy data/test.3d.dz -o data/test.3d.streamLine -oP data/test.3d.streamLineA -oBILD data/test.3d.streamLine.bild -f 25
	../$(OSTYPE)/$(OBJECTNAME)  -i3 data/test.3d.dx data/test.3d.dy data/test.3d.dz -o data/test.3d.streamLine2 -oP data/test.3d.streamLine2A -oBILD data/test.3d.streamLine2.bild -dt 0.2 -f 100
	@echo "----- Calc check -----"		

init:
	mrcImageModelCreate -o data/test.2d -nx 128 -ny 128 -nz  1 -lx 2 -ly 2 -lz 2 -m 6
	mrcImageModelCreate -o data/test.3d -nx 32 -ny 32 -nz 32-lx 2 -ly 2 -lz 2 -m 7
	mrcImageGradient -i data/test.2d -o data/test.2d.grad -oDx data/test.2d.dx -oDy data/test.2d.dy
	mrcImageGradient -i data/test.3d -o data/test.3d.grad -oDx data/test.3d.dx -oDy data/test.3d.dy -oDz data/test.3d.dz
	mrcImageDivergence -i2 data/test.2d.dx data/test.2d.dy -o data/test.2.div
	mrcImageDivergence -i3 data/test.3d.dx data/test.3d.dy data/test.3d.dz -o data/test.3d.div

clean:
