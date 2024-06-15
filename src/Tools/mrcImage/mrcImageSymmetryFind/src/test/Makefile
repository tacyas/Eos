include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

DATA=data/FlagellaSection

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA)-0001.roi -O $(DATA)-0001.info1 -nRange 10 16 -A $(DATA)-0001.avg1 -centreMode 0 -m1 1 -m2 1 -t1 1.5
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA)-0001.roi -O $(DATA)-0001.info1-r -nRange 10 16 -A $(DATA)-0001.avg1-r -centreMode 0 -m1 1 -m2 1 -t1 1.5 -rrange 40 110 

exec2:
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA)-0001.roi -O $(DATA)-0001.info2 -nRange 10 16 -A $(DATA)-0001.avg2 -centreMode 0 -m1 2 -m2 0 

exec4:
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA)-0001.roi -O $(DATA)-0001.info4 -nRange 10 16 -A $(DATA)-0001.avg4 -centreMode 0 -m1 4 -m2 0 

exec4_1:
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA)-0001.roi -O $(DATA)-0001.info4_1 -nRange 10 16 -A $(DATA)-0001.avg4_1 -centreMode 1 -m1 4 -m2 0 



clean:

init:
	mrcImagePad -i $(DATA)-0001.roi -o $(DATA)-0001.pad -m 3 -H 256 -W 256
	mrcImageWindowing -i $(DATA)-0001.pad -o $(DATA)-0001.win -m 18 -W 0.05 0 0.05 0
	mrcImageShift -i $(DATA)-0001.win -o $(DATA)-0001.shift -x 128 -y 128
	mrcImageToneReversal -i $(DATA)-0001.shift -o $(DATA)-0001.neg
