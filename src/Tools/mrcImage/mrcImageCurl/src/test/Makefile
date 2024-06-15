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
	../$(OSTYPE)/$(OBJECTNAME) -i2 data/test.2d.dx data/test.2d.dy -o data/test.2d.curl
	../$(OSTYPE)/$(OBJECTNAME) -i2 data/test.2d.dx data/test.2d.dx -o data/test.2d.curl2
	../$(OSTYPE)/$(OBJECTNAME) -i3 data/test.3d.dx data/test.3d.dy data/test.3d.dz -o data/test.3d.curl -o3 data/test.3d.curlx data/test.3d.curly data/test.3d.curlz
	../$(OSTYPE)/$(OBJECTNAME) -i3 data/test.3d.dx data/test.3d.dx data/test.3d.dz -o data/test.3d.curl2 -o3 data/test.3d.curlx2 data/test.3d.curly2 data/test.3d.curlz2
	@echo "----- Calc check -----"		

init:
	mrcImageModelCreate -o data/test.2d -nx 64 -ny 64 -nz  1 -lx 2 -ly 2 -lz 2 -m 6
	mrcImageModelCreate -o data/test.3d -nx 64 -ny 64 -nz 64 -lx 2 -ly 2 -lz 2 -m 7
	mrcImageGradient -i data/test.2d -o data/test.2d.grad -oDx data/test.2d.dx -oDy data/test.2d.dy 
	mrcImageGradient -i data/test.3d -o data/test.3d.grad -oDx data/test.3d.dx -oDy data/test.3d.dy -oDz data/test.3d.dz 

clean:
