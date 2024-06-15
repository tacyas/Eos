include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec: prep
	@echo "----- Execution Check -----"
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.move -r data/test.mrc \
		-fit data/test.fit -o data/test.out -O data/test.Out \
		-cor data/test.cor \
		-n 360 -m 3 
	time ~/Eos/bin/$(OSTYPE)/$(OBJECTNAME) -i data/test.move -r data/test.mrc \
		-fit data/test.fit -o data/test.out -O data/test.Out \
		-cor data/test.cor \
		-n 360 -m 3 
	Display2 -i data/test.fit &
	Display2 -i data/test.cor &

exec1: prep
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.move -r data/test.mrc \
		-fit data/test.fit1 -o data/test.out1 -O data/test.Out1 \
		-cor data/test.cor1 \
		-Method 1 \
		-n 360 
	Display2 -i data/test.fit1 &
	Display2 -i data/test.cor1 &

exec2: prep
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.move -r data/test.mrc \
		-fit data/test.fit2 -o data/test.out2 -O data/test.Out2 \
		-cor data/test.cor2 \
		-Method 2 \
		-n 36 -m 0 
	Display2 -i data/test.fit2 &
	Display2 -i data/test.cor2 &
	@echo "----- Calc check -----"		

exec3: prep
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.move2 -r data/test.mrc \
		-fit data/test.fit3 -o data/test.out3 -O data/test.Out3 \
		-cor data/test.cor3 \
		-Method 0 -s -10 -10 10 10  \
		-n 36 -m 0 
	Display2 -i data/test.fit3 &
	Display2 -i data/test.cor3 &
	@echo "----- Calc check -----"		

exec4: prep
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.move3 -r data/test.mrc \
		-fit data/test.fit4 -o data/test.out4 -O data/test.Out4 \
		-cor data/test.cor4 \
		-Method 0 -s -10 -10 10 10  \
		-n 36 -m 0 
	Display2 -i data/test.fit3 &
	Display2 -i data/test.cor3 &
	@echo "----- Calc check -----"		

exec5: prep2
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/121p-move.move -r data/121p-move.mrc \
		-fit data/test.fit5 -o data/test.out5 -O data/test.Out5 \
		-cor data/test.cor5 \
		-Method 0 -s -10 -10 10 10  \
		-n 36 -m 0 
	Display2 -i data/test.fit5 &
	Display2 -i data/test.cor5 &
	@echo "----- Calc check -----"		

exec6: prep2
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/121p-move.move2 -r data/121p-move.mrc \
		-fit data/test.fit6 -o data/test.out6 -O data/test.Out6 \
		-cor data/test.cor6 \
		-Method 0 -s -10 -10 10 10  \
		-n 36 -m 0 
	Display2 -i data/test.fit6 &
	Display2 -i data/test.cor6 &
	@echo "----- Calc check -----"		

prep:
	mrcImageGaussDisc -o data/test.mrc -sigmax 10 -sigmay 20 -W 256 -H 256 -size 1 
	Display2 -i data/test.mrc &
	mrcImageRotation -i data/test.mrc -o data/test.rot -a 30 
	mrcImageMove     -i data/test.rot -o data/test.move  -x 20 -y 10 
	mrcImageMove     -i data/test.rot -o data/test.move2  -x 5 -y 3 
	mrcImageNoiseAdd -i data/test.move2 -o data/test.move3 -SN 1.
	Display2 -i data/test.move &

prep2:
	pdb2mrc2d -i data/121p-move.pdb -o data/121p-move.mrc -n 64 64 -s -64 -64 -d 2 2 -w 1
	mrcImageRotation -i data/121p-move.mrc -o data/121p-move.rot -a 40
	mrcImageMove -i data/121p-move.rot -o data/121p-move.move -x 3 -y 5
	mrcImageNoiseAdd -i data/121p-move.move -o data/121p-move.move2 -SN 1.0
	mrcImageSmoothing -i data/121p-move.move2 -o data/121p-move.move3 -m 1 -r 2 -M 1
	mrcImageNoiseAdd -i data/121p-move.move -o data/121p-move.move4 -SN 0.1 
	mrcImageSmoothing -i data/121p-move.move4 -o data/121p-move.move5 -m 1 -r 2 -M 1
	mrcImageNoiseAdd -i data/121p-move.move -o data/121p-move.move6 -SN 0.3 
	mrcImageSmoothing -i data/121p-move.move6 -o data/121p-move.move7 -m 1 -r 2 -M 1
	mrcImageNoiseAdd -i data/121p-move.move -o data/121p-move.move8 -SN 0.6
	mrcImageSmoothing -i data/121p-move.move8 -o data/121p-move.move9 -m 1 -r 2 -M 1
	mrcImageSmoothing -i data/121p-move.move8 -o data/121p-move.move10 -m 1 -r 1 -M 1

clean:
	rm test.*
