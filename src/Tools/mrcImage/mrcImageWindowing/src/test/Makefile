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
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.0.out -m 0
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.1.out -m 1 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.2.out -m 2 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.3.out -m 3 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.4.out -m 4 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.5.out -m 5 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.6.out -m 6 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.7.out -m 7 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.8.out.1 -m 8  -Wx 1 -Wy 1 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.8.out.4 -m 8  -Wx 4 -Wy 4 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.9.out -m 9  -Wx 0.05 -Wy 0.05
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.in -o data/test.10.out -m 10  -Wx 0.05 -Wy 0.05
	@echo "----- Calc check -----"		

clean:

init:
	mrcImageModelCreate -o data/test.org -nx 64 -ny 64 -nz 1 -lx 2 -ly 2  -lz 1
	mrcImageNoiseAdd -i data/test.org -o data/test.in -SD 1
