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
	../$(OSTYPE)/$(OBJECTNAME) -i  $(DATA).inlst -t3d $(DATA).fft3d -o $(DATA).recfft3d -InterpMode 1 
	@echo "----- Calc check -----"		

init:
	make init1
	make init2
	make init3

init1:
	cp $${EOS_HOME}/data/SampleData/PDB-DEMO/121p-centre.pdb data
	pdb2mrc -i $(DATA).pdb -o $(DATA).mrc3d -nx 128 -ny 128\
		 -nz 128 -Sx -64 -Sy -64 -Sz -64 -dx 1 -dy 1 -dz 1 -sig 1.6 -m 0 
	mrcImageProjection -i $(DATA).mrc3d -o $(DATA).mrc2d

init2:
	mrcImageFFT -i $(DATA).mrc2d -o $(DATA).fft2d
	mrcImageFFT -i $(DATA).mrc3d -o $(DATA).fft3d

init3:
	mrc3Dto2DFFT -i $(DATA).mrc3d -o $(DATA).roilst -t $(DATA).fft2d \
		-EulerMode YOYS -Rot1 0 359 30 -Rot2 0 359 30 -Rot3 0 359 30 \
		-InterpMode 1 

init4: 
	awk '{printf("%s %f\n", $$0, 1.0);}' $(DATA).roilst > $(DATA).inlst

clean:

