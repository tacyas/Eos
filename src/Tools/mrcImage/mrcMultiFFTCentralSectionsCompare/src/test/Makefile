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
<<<<<<< HEAD
	../$(OSTYPE)/$(OBJECTNAME) -i TEST.fft2d -i3d REF.txt -Prior PRIOR.txt -EulerMode YOYS -InterpMode 1 -o OUT.txt -Lmode 0 0.0 0.90
			../$(OSTYPE)/$(OBJECTNAME) -i data/datashellshell/121p.0.0.0.fft2d -i3d /Users/nakanosaki/Eos/src/Tools/rec3d/mrc3Dto2DFFT/src/test/data/Postshell-nor/Postshell-20.txt /Users/nakanosaki/Eos/src/Tools/rec3d/mrc3Dto2DFFT/src/test/  -EulerMode YOYS -InterpMode 1 -o data/TESTPostshell/Test-0-0-0.txt -Lmode 0 0.0 0.90
	
=======
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).fft2d ./ -i3d data/$(DATABASE).roilst data/refData/ -EulerMode YOYS -InterpMode 1 -o $(DATA).out0 -oL $(DATA).outProb0 -Lmode 0 0.0 0.90 -EulerMode YOYS -Rot1 0 359 30 -Rot2 0 359 30 -Rot3 0 359 30
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).fft2d ./ -i3d data/$(DATABASE).roilst data/refData/ -EulerMode YOYS -InterpMode 1 -o $(DATA).out1 -oL $(DATA).outProb1 -Lmode 1 0.0 0.90

NUM=00171
>>>>>>> dca254b48207ce4fe547f3ad98197ffcf409cf50
exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA)-$(NUM).fft2d ./ -i3d data/$(DATABASE).roilst data/refData/ -EulerMode YOYS -InterpMode 1 -o $(DATA)-$(NUM).out0 -oL $(DATA)-$(NUM).outProb0 -Lmode 0 0.0 0.90 -EulerMode YOYS -Rot1 0 359 30 -Rot2 0 359 30 -Rot3 0 359 30
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA)-$(NUM).fft2d ./ -i3d data/$(DATABASE).roilst data/refData/ -EulerMode YOYS -InterpMode 1 -o $(DATA)-$(NUM).out1 -oL $(DATA)-$(NUM).outProb1 -Lmode 1 0.0 0.90 -EulerMode YOYS -Rot1 0 359 30 -Rot2 0 359 30 -Rot3 0 359 30

init:
	mkdir data/InData
	mkdir data/refData
	make init1
	make init2
	make init3
	make init4

init1:
	pdb2mrc -i data/121p-centre.pdb -o data/121p-centre.mrc3d -nx 64 -ny 64 -nz 64 -Sx -64 -Sy -64 -dx 2 -dy 2 -dz 2 -sig 1.6 -m 0
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

init4:
	mkdir data/refData
	mv $(DATA)-*.fft2d data/refData


clean:



