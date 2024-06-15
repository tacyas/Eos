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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.2d -o data/test.2d.grad -oDx data/test.2d.dx -oDy data/test.2d.dy 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.3d -o data/test.3d.grad -oDx data/test.3d.dx -oDy data/test.3d.dy -oDz data/test.3d.dz 
	@echo "----- Calc check -----"		

init:
	mrcImageModelCreate -o data/test.2d -nx 64 -ny 64 -nz  1 -lx 2 -ly 2 -lz 2 -m 6
	mrcImageModelCreate -o data/test.3d -nx 64 -ny 64 -nz 64 -lx 2 -ly 2 -lz 2 -m 7

clean:
