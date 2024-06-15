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
	../$(OSTYPE)/$(OBJECTNAME) 
	@echo "----- Calc check -----"

stdsin:
	Fname=`cat list`;\
	for i in $$Fname ;\
	do \
		mrcImageSinogramCreate -i $$i -o $$i.sin ;\
	done	

noise:
	Fname=`cat list`;\
	for i in $$Fname ;\
	do \
		for j in 1 3 10 ;\
		do \
			for k in 1 2 3 ;\
			do \
				mrcImageNoiseAdd -i $$i -o $$i.n$$j-$$k.noise -SN $$j ;\
				mrcImageSinogramCreate -i $$i.n$$j-$$k.noise -o $$i.n$$j-$$k.sin ;\
			done ;\
		done ;\
	done 
	
			

clean:
