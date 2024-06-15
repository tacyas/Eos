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
	../$(OSTYPE)/$(OBJECTNAME) -i data/in.lst -r data/test-000.mrc -o data/test.avg -Periodic -range 0 360 5 -M 18 -m 0 -maxIter 10 -iter 4 -log data/test.log  -thres 0.4
	cat data/test.log
	@echo "----- Calc check -----"		

init:
	pdb2mrc2d -i data/121p-GC.pdb -o data/test-000.roi -d 2.5 2.5 -s -40 -40 -n 32 32 -sig 2.0 -w 1.0	
	echo "data/test-000.mrc" > data/in.lst
	for i in 030 060 090 120 150 180 ; do \
		mrcImageRotation -i data/test-000.roi -o data/test-$$i.roi -a $$i -Periodic; \
		echo "data/test-$$i.mrc" >> data/in.lst; \
	done
	for i in 000 030 060 090 120 150 180 ; do \
		mrcImageNoiseAdd -i data/test-$$i.roi -o data/test-$$i.mrc -SN 1.5 ; \
	done
	
clean:
