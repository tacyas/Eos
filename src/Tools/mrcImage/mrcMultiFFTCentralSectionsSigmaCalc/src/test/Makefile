include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

DATABASE=121p-centre
DATA=data/$(DATABASE)


all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATABASE).fft2d data/ -i3d $(DATA).roilst data/refData/ -EulerMode YOYS -InterpMode 1 -o $(DATA).sigma0 -iL $(DATA).outProb0 ./
	@echo "----- Calc check -----"		

init:
	make init1
	make init2
	make init3
	make init4

init1:
	mkdir data/InData
	mkdir data/refData
	pdb2mrc -i data/121p-centre.pdb -o data/121p-centre.mrc3d -nx 64 -ny 64 -nz 64 -Sx -64 -Sy -64 -dx 2 -dy 2 -dz 2 -sig 1.6 -m     0
	cd data/InData; \
	for i in 000 030 060 090 120 150 180 210 240 270 300 330 ; do \
	for j in 000 030 060 090 120 150 180 210 240 270 300 330 ; do \
	for k in 000 030 060 090 120 150 180 210 240 270 300 330 ; do \
		echo $$i, $$j, $$k; \
		mrcImageRotation3D -i ../121p-centre.mrc3d -o 121p-centre.$$i.$$j.$$k.mrc3d -EA YOYS $$i $$j $$k -M 2 -m 0 ; \
		mrcImageProjection -i 121p-centre.$$i.$$j.$$k.mrc3d -o 121p-centre.$$i.$$j.$$k.prj; \
		mrcImageFFT -i 121p-centre.$$i.$$j.$$k.prj -o 121p-centre.$$i.$$j.$$k.fft2d ; \
	done; \
	done; \
	done

init2:
	mrcImageFFT -i $(DATA).mrc3d        -o $(DATA).fft3d
	mrcImageProjection -i $(DATA).mrc3d -o $(DATA).prj
	mrcImageFFT -i $(DATA).prj -o $(DATA).fft2d
	
init3:
	cd data; mrc3Dto2DFFT -i $(DATABASE).fft3d -t $(DATABASE).fft2d -o $(DATABASE).roilst -EulerMode YOYS \
		-Rot1 0 359 30 -Rot2 0 359 30 -Rot3 0 359 30 -trans 0 0 -InterpMode 1
	mv $(DATA)*.fft2d data/refData
	mv data/refData/$(DATABASE).fft2d data


init4:
	mrcMultiFFTCentralSectionsCompare -i $(DATA).fft2d ./ -i3d data/$(DATABASE).roilst data/refData/ -EulerMode YOYS -InterpMode 1 -o     $(DATA).out0 -oL $(DATA).outProb0 -Lmode 0 0.0 0.90

clean:
