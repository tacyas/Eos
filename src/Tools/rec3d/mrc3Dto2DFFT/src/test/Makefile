include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

DATA=data/121p-centre

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).mrc3d -o $(DATA).outlst -t $(DATA).fft2d \
		-EulerMode YOYS -Rot1 0 359 30 -Rot2 0 359 30 -Rot3 0 359 30 -InterpMode 1
	@echo "----- Calc check -----"		

init:
	cp $(EOS_HOME)/data/SampleData/PDB-DEMO/121p-centre.pdb data
	pdb2mrc -i $(DATA).pdb -o $(DATA).mrc3d -nx 128 -ny 128 -nz 128 -Sx -64 -Sy -64 -Sz -64 -dx 1 -dy 1 -dz 1 -sig 1.6
	mrcImageProjection -i $(DATA).mrc3d -o $(DATA).mrc2d
	mrcImageFFT -i $(DATA).mrc2d -o $(DATA).fft2d


clean:
