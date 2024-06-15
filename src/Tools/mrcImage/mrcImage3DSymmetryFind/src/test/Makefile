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
	../$(OSTYPE)/$(OBJECTNAME) -i data/3I5I-C2.mrc3d -o data/3I5I-C2.log -S 5 -Rot1 0 360 90 -Rot2 -90 90 45 -InterpolationMode 1 -RotMode "XOYS" -dCos 1 -a data/3I5I-C2.mrc3d.avg
	@echo "----- Calc check -----"		

exec1:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/3I5I-C2-Rot1.mrc3d -o data/3I5I-C2-Rot1.log -S 5 -Rot1 0 360 20 -Rot2 -90 90 45 -InterpolationMode 1 -RotMode "XOYS" -dCos 1 -a data/3I5I-C2-Rot1.mrc3d.avg
	@echo "----- Calc check -----"		

exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/3I5I-C2-Rot2.mrc3d -o data/3I5I-C2-Rot2.log -S 5 -Rot1 0 360 60 -Rot2 -90 90 10 -InterpolationMode 1 -RotMode "XOYS" -dCos 1 -a data/3I5I-C2-Rot2.mrc3d.avg
	@echo "----- Calc check -----"		

init:
	pdb2mrc -i data/3I5I-C2-shift.pdb -o data/3I5I-C2.mrc3d -m 0 -sig 2 -dx 2 -dy 2 -dz 2 -Sx -120 -Sy -120 -Sz -120 -nx 120 -ny 120 -nz 120
	pdbRotation -i data/3I5I-C2-shift.pdb -o data/3I5I-C2-shift-Rot1.pdb -EA "XOYS" 60 45 0 
	pdb2mrc -i data/3I5I-C2-shift-Rot1.pdb -o data/3I5I-C2-Rot1.mrc3d -m 0 -sig 2 -dx 2 -dy 2 -dz 2 -Sx -120 -Sy -120 -Sz -120 -nx 120 -ny 120 -nz 120
	pdbRotation -i data/3I5I-C2-shift.pdb -o data/3I5I-C2-shift-Rot2.pdb -EA "XOYS" 60 10 0 
	pdb2mrc -i data/3I5I-C2-shift-Rot2.pdb -o data/3I5I-C2-Rot2.mrc3d -m 0 -sig 2 -dx 2 -dy 2 -dz 2 -Sx -120 -Sy -120 -Sz -120 -nx 120 -ny 120 -nz 120


clean:
