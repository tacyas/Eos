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
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc3d -o data/test.mrc3d.sphere    -nx 5 -ny 10 -nz 15 -cx 10 -cy 10 -cz 10 -Shape 0 -m 2
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc3d -o data/test.mrc3d.rectangle -nx 5 -ny 10 -nz 15 -cx 10 -cy 10 -cz 10 -Shape 1 -m 2
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc3d -o data/test.mrc3d.cylinder  -nx 5 -ny 10 -nz 15 -cx 10 -cy 10 -cz 10 -Shape 2 -m 2
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc3d -o data/test.mrc3d.sphereR    -nx 5 -ny 10 -nz 15 -cx 10 -cy 10 -cz 10 -Shape 0 -m 2 -Rot ZOYS 45 0 0
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc3d -o data/test.mrc3d.rectangleR -nx 5 -ny 10 -nz 15 -cx 10 -cy 10 -cz 10 -Shape 1 -m 2 -Rot ZOYS 45 0 0 
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc3d -o data/test.mrc3d.cylinderR  -nx 5 -ny 10 -nz 15 -cx 10 -cy 10 -cz 10 -Shape 2 -m 2 -Rot ZOYS 45 0 0
	#
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc3d -o data/test.mrc3d.sphereS    -nx 5 -ny 10 -nz 15 -cx 10 -cy 10 -cz 10 -Shape 0 -m 2 -Soft 0 -SoftWidth 2
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc3d -o data/test.mrc3d.rectangleS -nx 5 -ny 10 -nz 15 -cx 10 -cy 10 -cz 10 -Shape 1 -m 2 -Soft 0 -SoftWidth 2
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc3d -o data/test.mrc3d.cylinderS  -nx 5 -ny 10 -nz 15 -cx 10 -cy 10 -cz 10 -Shape 2 -m 2 -Soft 0 -SoftWidth 2
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc3d -o data/test.mrc3d.sphereRS    -nx 5 -ny 10 -nz 15 -cx 10 -cy 10 -cz 10 -Shape 0 -m 2 -Rot ZOYS 45 0 0 -Soft 0 -SoftWidth 2
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc3d -o data/test.mrc3d.rectangleRS -nx 5 -ny 10 -nz 15 -cx 10 -cy 10 -cz 10 -Shape 1 -m 2 -Rot ZOYS 45 0 0 -Soft 0 -SoftWidth 2
	../$(OSTYPE)/$(OBJECTNAME)  -i data/test.mrc3d -o data/test.mrc3d.cylinderRS  -nx 5 -ny 10 -nz 15 -cx 10 -cy 10 -cz 10 -Shape 2 -m 2 -Rot ZOYS 45 0 0 -Soft 0 -SoftWidth 2
	@echo "----- Calc check -----"		

clean:
