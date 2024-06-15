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
	../$(OSTYPE)/$(OBJECTNAME) -i data/all.in -o data/all.out -M data/model2-0.avg -A data/all.avg -t 480 -l data/llAxis.info
	@echo "----- Calc check -----"		

clean:

ROTANGLE=0 10 20 30 

create::
	cd data; \
	pdbMove  -i model0.pdb  -o model1.pdb -x 30; \
	pdbHelix -i model1.pdb  -o model2.pdb -p 30 -z 40 -n 48 ; \
	rm -f all.in ; \
	for i in $(ROTANGLE); \
	do \
		pdbRotation -i model2.pdb -o model2-$$i.pdb -ZYX -90 $$i 0 ;\
		pdb2mrc2d   -i model2-$$i.pdb -o model2-$$i.prj -s -80 -10 -d 5 5 -n 33 384 -sig 10.0 ; \
		mrcImagePad -i model2-$$i.prj -o model2-$$i.pad -W 384 -m 2; \
		mrcImageFFT -i model2-$$i.pad -o model2-$$i.fft ; \
		llExtract   -i model2-$$i.fft -1 model2-$$i.nea -2 model2-$$i.far -c llExtract.info; \
		llDataAxisSearch -i1 model2-$$i.nea -i2 model2-$$i.far -a  model2-$$i.avg -t 480 -l llAxis.info -o1 model2-$$i.asnea -o2 model2-$$i.asfar  -o model2-$$i.param ; \
		echo "model2-$$i.avg 1.0 " >>  all.in ; \
		rm  model2-$$i.pdb model2-$$i.pad  model2-$$i.fft  model2-$$i.nea  model2-$$i.far  model2-$$i.asnea  model2-$$i.asfar ; \
	done
