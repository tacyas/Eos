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
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.fft3d -t data/121p.0.fft2d -o data/121p.0.central   -oI data/121p.0.central.img   -EA YOYS 0  0  0  -trans 0 0    -InterpMode 1 
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.fft3d -t data/121p.0.fft2d -o data/121p.0-0.central -oI data/121p.0-0.central.img -EA YOYS 0  0  0  -trans 5 10   -InterpMode 1 
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.fft3d -t data/121p.0.fft2d -o data/121p.1.central   -oI data/121p.1.central.img   -EA YOYS 90 0  0  -trans 0 0    -InterpMode 1 
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.fft3d -t data/121p.0.fft2d -o data/121p.1-0.central -oI data/121p.1-0.central.img -EA YOYS 90 0  0  -trans 5 -10  -InterpMode 1 
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.fft3d -t data/121p.0.fft2d -o data/121p.2.central   -oI data/121p.2.central.img   -EA YOYS 30 45 60 -trans 0 0    -InterpMode 1 
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.fft3d -t data/121p.0.fft2d -o data/121p.2-0.central -oI data/121p.2-0.central.img -EA YOYS 30 45 60 -trans -5 -10 -InterpMode 1
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.fft3d -t data/121p.0.fft2d -o data/121p.3.central   -oI data/121p.3.central.img   -EA YOYS 0  60 0  -trans 0 0    -InterpMode 1 
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.fft3d -t data/121p.0.fft2d -o data/121p.3-0.central -oI data/121p.3-0.central.img -EA YOYS 0  60 0  -trans -5 10  -InterpMode 1
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.fft3d -t data/121p.0.fft2d -o data/121p.4.central   -oI data/121p.4.central.img   -EA YOYS 0  0  45  -trans 0 0   -InterpMode 1 
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.fft3d -t data/121p.0.fft2d -o data/121p.4-0.central -oI data/121p.4-0.central.img -EA YOYS 0  0  45  -trans 10 5  -InterpMode 1
	@echo "----- Calc check -----"		

init:
	pdb2mrc -i data/121p-centre.pdb -o data/121p.mrc3d -nx 64 -ny 64 -nz 64 -Sx -64 -Sy -64 -Sz -64 -dx 2 -dy 2 -dz 2  -w 1 -sig 2.0 -m 0
	mrcImageFFT -i data/121p.mrc3d -o data/121p.fft3d
	mrc3Dto2D -i data/121p.mrc3d -o data/121p.0.mrc2d -Rot1 0 0 10 -Rot2 0 0 10 -Rot3 0 0 10 -EulerMode YOYS -InterpolationMode 1
	mrc3Dto2D -i data/121p.mrc3d -o data/121p.1.mrc2d -Rot1 90 90 10 -Rot2 0 0 10 -Rot3 0 0 10 -EulerMode YOYS -InterpolationMode 1
	mrc3Dto2D -i data/121p.mrc3d -o data/121p.2.mrc2d -Rot1 30 30 10 -Rot2 45 45 10 -Rot3 60 60 10 -EulerMode YOYS -InterpolationMode 1
	mrc3Dto2D -i data/121p.mrc3d -o data/121p.3.mrc2d -Rot1  0 0  10 -Rot2 60 60 10 -Rot3 0 0 10 -EulerMode YOYS -InterpolationMode 1
	mrc3Dto2D -i data/121p.mrc3d -o data/121p.4.mrc2d -Rot1  0 0  10 -Rot2 0 0 10 -Rot3 45 45 10 -EulerMode YOYS -InterpolationMode 1
	mrcImageFFT -i data/121p.0.mrc2d -o data/121p.0.fft2d
	mrcImageFFT -i data/121p.1.mrc2d -o data/121p.1.fft2d
	mrcImageFFT -i data/121p.2.mrc2d -o data/121p.2.fft2d
	mrcImageFFT -i data/121p.3.mrc2d -o data/121p.3.fft2d
	mrcImageFFT -i data/121p.4.mrc2d -o data/121p.4.fft2d

clean:
