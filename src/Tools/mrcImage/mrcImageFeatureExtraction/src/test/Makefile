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

clean:

posMake:
	LIST=`echo "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 "` ;\
	for i in $$LIST ;\
	do \
		mrcImagePosterization -i 1vS-106-20-n5.mrc -o 1vS-106-20-n5-pos$$i.mrc -g $$i ;\
	done

colDisp:
	LIST=`ls 1vS-106-20-n5-pos*.*` ;\
	for i in $$LIST ;\
	do \
		Display2 -i $$i ;\
	done

