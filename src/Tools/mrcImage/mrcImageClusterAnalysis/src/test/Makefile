include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

AR=24
PTHREAD=4

all: help exec exec-noave

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

initial-data:
	mrcImageGaussDisc -o data/test-00.roi -H 100 -W 100 -sigmax 10 -sigmay 10 -size 2 -a  0 -cx  0 -cy  0  
	mrcImageGaussDisc -o data/test-01.roi -H 100 -W 100 -sigmax 10 -sigmay 11 -size 2 -a  0 -cx 10 -cy  5  
	mrcImageGaussDisc -o data/test-02.roi -H 100 -W 100 -sigmax 10 -sigmay 12 -size 2 -a 30 -cx  0 -cy  0  
	mrcImageGaussDisc -o data/test-03.roi -H 100 -W 100 -sigmax 10 -sigmay 13 -size 2 -a 30 -cx 10 -cy  5  
	mrcImageGaussDisc -o data/test-04.roi -H 100 -W 100 -sigmax 10 -sigmay 21 -size 2 -a  0 -cx  0 -cy  0  
	mrcImageGaussDisc -o data/test-05.roi -H 100 -W 100 -sigmax 10 -sigmay 22 -size 2 -a  0 -cx 10 -cy  5  
	mrcImageGaussDisc -o data/test-06.roi -H 100 -W 100 -sigmax 10 -sigmay 23 -size 2 -a 30 -cx  0 -cy  0  
	mrcImageGaussDisc -o data/test-07.roi -H 100 -W 100 -sigmax 10 -sigmay 24 -size 2 -a 30 -cx 10 -cy  5  
	mrcImageGaussDisc -o data/test-08.roi -H 100 -W 100 -sigmax 10 -sigmay 31 -size 2 -a  0 -cx  0 -cy  0  
	mrcImageGaussDisc -o data/test-09.roi -H 100 -W 100 -sigmax 10 -sigmay 32 -size 2 -a  0 -cx 10 -cy  5  
	mrcImageGaussDisc -o data/test-0a.roi -H 100 -W 100 -sigmax 10 -sigmay 33 -size 2 -a 30 -cx  0 -cy  0  
	mrcImageGaussDisc -o data/test-0b.roi -H 100 -W 100 -sigmax 10 -sigmay 34 -size 2 -a 30 -cx 10 -cy  5  
	mrcImageGaussDisc -o data/test-0c.roi -H 100 -W 100 -sigmax 15 -sigmay 15 -size 2 -a  0 -cx  0 -cy  0  
	mrcImageGaussDisc -o data/test-0d.roi -H 100 -W 100 -sigmax 15 -sigmay 16 -size 2 -a  0 -cx 10 -cy  5  
	mrcImageGaussDisc -o data/test-0e.roi -H 100 -W 100 -sigmax 15 -sigmay 17 -size 2 -a 30 -cx  0 -cy  0  
	mrcImageGaussDisc -o data/test-0f.roi -H 100 -W 100 -sigmax 15 -sigmay 18 -size 2 -a 30 -cx 10 -cy  5  
	for i in `ls data/*.roi`; do \
		name=`basename $$i .roi`; \
		for j in `seq 0 3`; do \
			mrcImageNoiseAdd -i data/$$name.roi -o data/$$name-`printf "%02d" $$j`.noise-roi -SD 4; \
		done; \
	done
	ls -1 data/test-*.roi > data/test.roiinfo

exec:
	@echo "----- Execution Check -----"
	rm -f data/test.distance	
	time ../$(OSTYPE)/$(OBJECTNAME) -I data/test.roiinfo -O -N 1 -AR $(AR) -o data/test.cluster -ARMethod 0 -m 2 -Log data/test.distance -Log2 data/test.log2 2> data/test.err | tee data/test.log 
	diff data/test.distance data/test.distance.org
	@echo "----- Calc check -----"		
	clusterShow -i data/test.distance -PS data/test.distance.ps -I data/test.roiinfo 

exec-noave:
	@echo "----- Execution Check -----"
	rm -f data/test-noave.distance	
	time ../$(OSTYPE)/$(OBJECTNAME) -I data/test.roiinfo -O -N 1 -AR $(AR) -o data/test-noave.cluster -ARMethod 0 -m 2 -NoRecalc -Log data/test-noave.distance -Log2 data/test-noave.log2 2> data/test-noave.err | tee data/test-noave.log 
	diff data/test-noave.distance data/test.distance.org
	@echo "----- Calc check -----"		
	clusterShow -i data/test-noave.distance -PS data/test-noave.distance.ps -I data/test.roiinfo

exec-pthread:
	@echo "----- Execution Check -----"
	time ../$(OSTYPE)/$(OBJECTNAME) -I data/test.roiinfo -O -N 1 -AR $(AR) -o data/test.cluster-pthread -ARMethod 0 -m 2 -Log data/test.distance-pthread -Log2 data/test.log2-pthread -pthread $(PTHREAD) 2> data/test.err-pthread| tee data/test.log-pthread
	diff data/test.distance-pthread data/test.distance.org
	@echo "----- Calc check -----"		

exec2:
	@echo "----- Execution Check -----"
	time ../$(OSTYPE)/$(OBJECTNAME) -I data/test.roiinfo -O -N 1 -AR $(AR) -o data/test2.cluster -ARMethod 2 -m 2 -Log data/test2.distance -Log2 data/testlog2 2> data/test2.err | tee data/test2.log 
	diff data/test.cluster data/test.cluster.org
	@echo "----- Calc check -----"		

clean:
	rm data/test.log2 data/test.distance
