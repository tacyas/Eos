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
	../$(OSTYPE)/$(OBJECTNAME) -I data/test.panoinfo -o data/test.pano -N 200 200 1 
	@echo "----- Calc check -----"		

init:
	mrcImageROIs -i data/test.mrc -I data/test.roiinfo 
	awk ' { print $$1,$$3,$$4,0 ; }' data/test.roiinfo  > data/test.panoinfo

clean:
