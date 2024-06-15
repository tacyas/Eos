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
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/test.mrc3d.1.sn1   -i2 data/test.mrc3d.2.sn1   -o data/test.sn1.FSC   -SNR -FSCfull -Cref -NoiseWeighted -1000
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/test.mrc3d.1.sn10  -i2 data/test.mrc3d.2.sn10  -o data/test.sn10.FSC  -SNR -FSCfull -Cref -NoiseWeighted -1000
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/test.mrc3d.1.sn100 -i2 data/test.mrc3d.2.sn100 -o data/test.sn100.FSC -SNR -FSCfull -Cref -NoiseWeighted -1000
	@echo "----- Calc check -----"		

init:
	pdb2mrc -i data/121p-GC.pdb -o data/test.mrc3d -nx 80 -ny 80 -nz 80 -dx 2 -dy 2 -dz 2 -Sx -80 -Sy -80 -Sz -80 -sig 1.6 -w 1.0
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.1.sn1 -SN 1
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.2.sn1 -SN 1
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.1.sn10 -SN 10
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.2.sn10 -SN 10
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.1.sn100 -SN 100
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.2.sn100 -SN 100
clean:
