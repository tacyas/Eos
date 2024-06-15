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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn1 -o data/test.mrc3d.fil.sharpen -filter data/test.sn1.FSC -filterCol 1 11 -H 0.25 -L 0.0 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn1 -o data/test.mrc3d.fil.Cref    -filter data/test.sn1.FSC -filterCol 1 9 -H 0.25 -L 0.0 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc3d.sn1 -o data/test.mrc3d.fil.Crefpredicted -filter data/test.sn1.FSCpredicted -filterCol 1 17 -H 0.25 -L 0.0 
	@echo "----- Calc check -----"		

init:
	pdb2mrc -i data/121p-GC.pdb -o data/test.mrc3d -nx 80 -ny 80 -nz 80 -dx 2 -dy 2 -dz 2 -Sx -80 -Sy -80 -Sz -80 -sig 1.6 -w 1.0
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.1.sn1 -SN 1
	mrcImageNoiseAdd -i data/test.mrc3d -o data/test.mrc3d.2.sn1 -SN 1
	mrcImageAdd -i1 data/test.mrc3d.1.sn1 -i2 data/test.mrc3d.2.sn1 -o data/test.mrc3d.sn1
	mrcImageFourierShellCorrelation -i1 data/test.mrc3d.1.sn1 -i2 data/test.mrc3d.2.sn1 -o data/test.sn1.FSC  -SNR -FSCfull -Cref -NoiseWeighted -100 
	mrcImageLowPassFilter -i data/test.mrc3d.1.sn1 -o data/test.mrc3d.1.sn1.low -hvp 0.05 -m 4   
	mrcImageBinalization -i data/test.mrc3d.1.sn1.low -o data/test.mrc3d.1.sn1.mask -m 32
	mrcImageNullImageCreate -r data/test.mrc3d.1.sn1 -o data/test.mrc3d.1.sn1.maskBack -v 1
	mrcImageFourierNeighborCorrelation -i data/test.mrc3d.1.sn1 -o data/test.sn1.FSCpredicted -FSC -mask data/test.mrc3d.1.sn1.mask -maskBack data/test.mrc3d.1.sn1.maskBack -FSCfull -Cref -NoiseWeighted -100 

clean:
