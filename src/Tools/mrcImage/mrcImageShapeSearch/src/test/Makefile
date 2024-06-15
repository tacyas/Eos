include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec exec2 exec-all

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-sylinder.bin -o data/test-sylinder.syl -Shape data/test-sylinder.shape0 -n 9 -r 3 5 1 -l 5 5 1 -Phi 0 359 45 -Theta  0 179 45 -Psi 0 0 90 -m 0 -thres 0.5 -OVBILD data/test-sylinder.sylvec.bild  -OV data/test-sylinder.sylvec 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-sylinder.bin -o data/test-sylinder.disk -Shape data/test-sylinder.shape1 -n 9 -r 6 6 1 -l 3 5 1 -Phi 0 359 45 -Theta  0 179 45 -Psi 0 0 90 -m 1 -thres 0.5 -OVBILD data/test-sylinder.diskvec.bild -OV data/test-sylinder.diskvec

exec2:
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-disk.bin -o data/test-disk.disk -Shape data/test-disk.shape0 -n 6 -r 6 6 1 -l 3 5 1 -Phi 0 359 45 -Theta  0 179 45 -Psi 0 0 90 -m 1 -thres 0.5 -OVBILD data/test-disk.sylvec.bild -OV data/test-disk.sylvec
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-disk.bin -o data/test-disk.syl -Shape data/test-disk.shape1 -n 6 -r 3 5 1 -l 5 5 1 -Phi 0 359 45 -Theta  0 179 45 -Psi 0 0 90 -m 0 -thres 0.5 -OVBILD data/test-disk.diskvec.bild -OV data/test-disk.diskvec
	@echo "----- Calc check -----"		

exec3:
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test-disk.bin -o data/test-disk.disk -r 6 6 1 -l 3 5 1 -Phi 0 359 45 -Theta  0 179 45 -Psi 0 0 90 -m 2 -thres 0.5 
	@echo "----- Calc check -----"		

exec-all:
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.syl -Shape data/test.shape0 -n 9 -r 6 6 1 -l 3 5 1 -Phi 0 359 45 -Theta  0 179 45 -Psi 0 0 90 -m 0 -thres 0.5  
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.disk -Shape data/test.shape1 -n 9 -r 6 6 1 -l 3 5 1 -Phi 0 359 45 -Theta  0 179 45 -Psi 0 0 90 -m 1 -thres 0.5 
	@echo "----- Calc check -----"		

init:
	mrcImageModelCreate -o data/test-sylinder.mrc -nx 32 -ny 32 -nz 32 -r 3 -l 20 -m 8
	mrcImageBinalization -i data/test-sylinder.mrc -o data/test-sylinder.bin -m 32
	mrcImageModelCreate -o data/test-disk.mrc -nx 32 -ny 32 -nz 32 -r 10 -l 3 -m 8
	mrcImageBinalization -i data/test-disk.mrc -o data/test-disk.bin -m 32
	mrcImageAdd -i1 data/test-sylinder.mrc -i2 data/test-disk.mrc -o data/test.mrc 
	mrcImageBinalization -i data/test.mrc -o data/test.bin -m 32

clean:
