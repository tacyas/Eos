include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

init::
	pdbMove -i data/4xvr.pdb -o data/test.pdb -GCtoOrigin
	pdb2mrc -i data/test.pdb -o data/test.mrc -nx 64 -ny 64 -nz 64 -Sx -32 -Sy -32 -Sz -32 -dx 1 -dy 1 -dz 1 -sig 1.8

exec: data/test.ims data/test2.ims data/test-5.ims data/test2-5.ims data/test4.ims data/test2-2.ims
	@echo "----- Execution End -----"
	ls -l data/*.ims


data/test.ims:data/test.mrc ../$(OSTYPE)/$(OBJECTNAME)
	rm -rf data/test.ims 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc -o data/test.ims

data/test-5.ims:data/test.mrc ../$(OSTYPE)/$(OBJECTNAME)
	rm -rf data/test-5.ims 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc -o data/test-5.ims -nres 5

data/test2.ims:data/test.mrc ../$(OSTYPE)/$(OBJECTNAME)
	rm -rf data/test2.ims 
	../$(OSTYPE)/$(OBJECTNAME) -I data/test.lst -o data/test2.ims

data/test2-2.ims:data/test.mrc ../$(OSTYPE)/$(OBJECTNAME)
	rm -rf data/test2-2.ims 
	../$(OSTYPE)/$(OBJECTNAME) -I data/test.lst -I2 data/test.lst -o data/test2-2.ims

data/test4.ims:data/test.mrc ../$(OSTYPE)/$(OBJECTNAME)
	rm -rf data/test4.ims 
	../$(OSTYPE)/$(OBJECTNAME) -I data/test4.lst -o data/test4.ims

data/test2-5.ims:data/test.mrc ../$(OSTYPE)/$(OBJECTNAME)
	rm -rf data/test2-5.ims 
	../$(OSTYPE)/$(OBJECTNAME) -I data/test.lst -o data/test2-5.ims -nres 4

clean:
