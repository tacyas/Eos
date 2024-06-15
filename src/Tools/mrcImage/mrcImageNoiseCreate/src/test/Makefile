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
	../$(OSTYPE)/$(OBJECTNAME) -r data/test.mrc3d.msk -o data/test.mrc3d.noise 
	mrcImageMultiplyingbyFile -i1 data/test.mrc3d.msk -i2 data/test.mrc3d.noise -o data/test.mrc3d.noise.msk 
	@echo "----- Calc check -----"		

init:
	pdb2mrc -i data/121p-GC.pdb -o data/test.mrc3d -nx 80 -ny 80 -nz 80 -dx 2 -dy 2 -dz 2 -Sx -80 -Sy -80 -Sz -80 -sig 1.    6 -w 1.0
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.sn1 -SN 1
	mrcImageLowPassFilter -i data/test.mrc3d.sn1 -o data/test.mrc3d.sn1.low -hvp 0.05 -m 4
	mrcImageBinalization -i data/test.mrc3d.sn1.low -o data/test.mrc3d.msk -m 32
 
clean:
