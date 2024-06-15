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
	../$(OSTYPE)/$(OBJECTNAME) -i data/in.lst -o data/out.W -info2 data/in.ctflst -ctfMode 33 -W 1.0
	../$(OSTYPE)/$(OBJECTNAME) -i data/in.lst -o data/out.WR -info2 data/in.ctflst -ctfMode 33 -W 0.06 -WR 10
	../$(OSTYPE)/$(OBJECTNAME) -i data/in.lst -o data/out.WRmax -info2 data/in.ctflst -ctfMode 33 -W 0.06 -WR 10 -maxWR 0.1
	../$(OSTYPE)/$(OBJECTNAME) -i data/in.lst -o data/out.WRmaxNdep -info2 data/in.ctflst -ctfMode 33 -W 0.06 -WR 10 -maxWR 0.1 -NdepWR 100
	@echo "----- Calc check -----"		

init:
	pdb2mrc2d -i data/121p-GC.pdb -o data/test.mrc2d -n 128 128 -d 2  2 -S -128 -128 -sig 1.6 -w 1.0
	mrcImageCTFObservation -i data/test.mrc2d -o data/test.mrc2d.def2 -kV 200 -df 20000 -Cs 1.7 -Ain 0.04 -A 0.1 -ctfMode 33 -white 1.0 
	mrcImageNoiseAdd -i data/test.mrc2d.def2 -o  data/test.mrc2d.def2.tst -SN 1.0
	mrcImageCTFObservation -i data/test.mrc2d -o data/test.mrc2d.def5 -kV 200 -df 50000 -Cs 1.7 -Ain 0.04 -A 0.1 -ctfMode 33 -white 1.0 
	mrcImageNoiseAdd -i data/test.mrc2d.def5 -o  data/test.mrc2d.def5.tst -SN 1.0
	echo "data/test.mrc2d.def2.tst" >  data/in.lst	
	echo "data/test.mrc2d.def5.tst" >> data/in.lst	
	echo "data/test.mrc2d.def2.ctfinfo" >  data/in.ctflst
	echo "data/test.mrc2d.def5.ctfinfo" >> data/in.ctflst
	echo "kV: 200"  >  data/def.ctfinfo 
	echo "Cs: 1.7"  >> data/def.ctfinfo 
	echo "Ai: 0.04" >> data/def.ctfinfo 
	echo "AoverP: 0.1" >> data/def.ctfinfo 
	cp data/def.ctfinfo data/test.mrc2d.def2.ctfinfo
	cp data/def.ctfinfo data/test.mrc2d.def5.ctfinfo
	echo "defocus: 20000" >> data/test.mrc2d.def2.ctfinfo
	echo "defocus: 50000" >> data/test.mrc2d.def5.ctfinfo

clean:
