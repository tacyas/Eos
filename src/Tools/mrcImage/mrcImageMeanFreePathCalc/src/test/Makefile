include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec exec2 exec3 exec4

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp -m 0 -Ow data/test.white -Owe data/test.whiteEdge -Ob data/test.black -Obe data/test.blackEdge
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp16 -m 16 -Ow data/test.white16 -Owe data/test.whiteEdge16 -Ob data/test.black16 -Obe data/test.blackEdge16
	@echo "----- Calc check -----"		

exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp2 -m 0 -Ow data/test.white2 -Owe data/test.whiteEdge2 -Ob data/test.black2 -Obe data/test.blackEdge2 -lt 2 2 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp216 -m 16 -Ow data/test.white216 -Owe data/test.whiteEdge216 -Ob data/test.black216 -Obe data/test.blackEdge216 -lt 2 2
	@echo "----- Calc check -----"		

exec3:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp3-00 -m 0 -Ow data/test.white3-00 -Owe data/test.whiteEdge3-00 -Ob data/test.black3-00 -Obe data/test.blackEdge3-00 -lt 3 3 -ls 0 -lm 0
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp3-01 -m 0 -Ow data/test.white3-01 -Owe data/test.whiteEdge3-01 -Ob data/test.black3-01 -Obe data/test.blackEdge3-01 -lt 3 3 -ls 0 -lm 1  
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp3-02 -m 0 -Ow data/test.white3-02 -Owe data/test.whiteEdge3-02 -Ob data/test.black3-02 -Obe data/test.blackEdge3-02 -lt 3 3 -ls 0 -lm 2
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp3-10 -m 0 -Ow data/test.white3-10 -Owe data/test.whiteEdge3-10 -Ob data/test.black3-10 -Obe data/test.blackEdge3-10 -lt 3 3 -ls 1 -lm 0
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp3-11 -m 0 -Ow data/test.white3-11 -Owe data/test.whiteEdge3-11 -Ob data/test.black3-11 -Obe data/test.blackEdge3-11 -lt 3 3 -ls 1 -lm 1  
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp3-12 -m 0 -Ow data/test.white3-12 -Owe data/test.whiteEdge3-12 -Ob data/test.black3-12 -Obe data/test.blackEdge3-12 -lt 3 3 -ls 1 -lm 2


exec4:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp.x -Ow data/test.white.x -Owe data/test.whiteEdge.x -Ob data/test.black.x -Obe data/test.blackEdge.x -m 1
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp.y -Ow data/test.white.y -Owe data/test.whiteEdge.y -Ob data/test.black.y -Obe data/test.blackEdge.y -m 2

exec5:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.mfp.any -Ow data/test.white.any -Owe data/test.whiteEdge.any -Ob data/test.black.any -Obe data/test.blackEdge.any -Odir data/test.mode3.dir -m 3 -deltaPhi 10 -deltaTheta 10 -Owall data/test.white.all -Oball data/test.black.all


init:
	pdb2mrc -i data/121p.pdb2 -o data/test.mrc -nx 64 -ny 48 -nz 32 -dx 2 -dy 2 -dz 2 -Sx -64 -Sy -48 -Sz -32 -sig 1.6 -w 1.0
	mrcImageBinalization -i data/test.mrc -o data/test.bin -m 32
clean:
