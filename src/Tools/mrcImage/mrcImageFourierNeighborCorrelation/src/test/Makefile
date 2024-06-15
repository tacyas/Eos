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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d       -o data/test.mrc3d.FNC 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn0.3 -o data/test.mrc3d.sn0.3.FNC 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn1   -o data/test.mrc3d.sn1.FNC 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn3   -o data/test.mrc3d.sn3.FNC 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn10  -o data/test.mrc3d.sn10.FNC 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn100 -o data/test.mrc3d.sn100.FNC 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d       -o data/test.mrc3d.FSC       -FSC -mask data/test.mrc3d.msk       -maskBack data/test.back
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn0.3 -o data/test.mrc3d.sn0.3.FSC -FSC -mask data/test.mrc3d.sn0.3.msk -maskBack data/test.back
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn1   -o data/test.mrc3d.sn1.FSC   -FSC -mask data/test.mrc3d.sn1.msk   -maskBack data/test.back
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn3   -o data/test.mrc3d.sn3.FSC   -FSC -mask data/test.mrc3d.sn3.msk   -maskBack data/test.back
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn10  -o data/test.mrc3d.sn10.FSC  -FSC -mask data/test.mrc3d.sn10.msk  -maskBack data/test.back
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn100 -o data/test.mrc3d.sn100.FSC -FSC -mask data/test.mrc3d.sn100.msk -maskBack data/test.back
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d       -o data/test.mrc3d.FSC2       -FSC -mask data/test.mrc3d.msk       -maskBack data/test.back -FSCfull -Cref -NoiseWeighted -100
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn0.3 -o data/test.mrc3d.sn0.3.FSC2 -FSC -mask data/test.mrc3d.sn0.3.msk -maskBack data/test.back  -FSCfull -Cref -NoiseWeighted -100
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn1   -o data/test.mrc3d.sn1.FSC2   -FSC -mask data/test.mrc3d.sn1.msk   -maskBack data/test.back  -FSCfull -Cref -NoiseWeighted -100
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn3   -o data/test.mrc3d.sn3.FSC2   -FSC -mask data/test.mrc3d.sn3.msk   -maskBack data/test.back  -FSCfull -Cref -NoiseWeighted -100
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn10  -o data/test.mrc3d.sn10.FSC2  -FSC -mask data/test.mrc3d.sn10.msk  -maskBack data/test.back  -FSCfull -Cref -NoiseWeighted -100
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn100 -o data/test.mrc3d.sn100.FSC2 -FSC -mask data/test.mrc3d.sn100.msk -maskBack data/test.back  -FSCfull -Cref -NoiseWeighted -100
	@echo "----- Calc check -----"		

init:
	pdb2mrc -i data/121p-GC.pdb -o data/test.mrc3d -nx 80 -ny 80 -nz 80 -dx 2 -dy 2 -dz 2 -Sx -80 -Sy -80 -Sz -80 -sig 1.6 -w 1.0
	mrcImageLowPassFilter -i data/test.mrc3d -o data/test.mrc3d.low -hvp 0.05 -m 4
	mrcImageBinalization -i data/test.mrc3d.low -o data/test.mrc3d.msk -m 32
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.sn0.3 -SN 0.3 
	mrcImageLowPassFilter -i data/test.mrc3d.sn0.3 -o data/test.mrc3d.sn0.3.low -hvp 0.05 -m 4
	mrcImageBinalization -i data/test.mrc3d.sn0.3.low -o data/test.mrc3d.sn0.3.msk -m 32
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.sn1 -SN 1
	mrcImageLowPassFilter -i data/test.mrc3d.sn1 -o data/test.mrc3d.sn1.low -hvp 0.05 -m 4
	mrcImageBinalization -i data/test.mrc3d.sn1.low -o data/test.mrc3d.sn1.msk -m 32
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.sn3 -SN 3 
	mrcImageLowPassFilter -i data/test.mrc3d.sn3 -o data/test.mrc3d.sn3.low -hvp 0.05 -m 4
	mrcImageBinalization -i data/test.mrc3d.sn3.low -o data/test.mrc3d.sn3.msk -m 32
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.sn10 -SN 10
	mrcImageLowPassFilter -i data/test.mrc3d.sn10 -o data/test.mrc3d.sn10.low -hvp 0.05 -m 4
	mrcImageBinalization -i data/test.mrc3d.sn10.low -o data/test.mrc3d.sn10.msk -m 32
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.sn100 -SN 100
	mrcImageLowPassFilter -i data/test.mrc3d.sn100 -o data/test.mrc3d.sn100.low -hvp 0.05 -m 4
	mrcImageBinalization -i data/test.mrc3d.sn100.low -o data/test.mrc3d.sn100.msk -m 32
	mrcImageNullImageCreate -o data/test.back -Nx 80 -Ny 80 -Nz 80 -d 2.0 -v 1

clean:
