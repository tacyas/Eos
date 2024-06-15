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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test-00.mrc -o data/test-00-2-3.mrc -nx 2 -ny 3 -nz 1 -M 2 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test-00.mrc -o data/test-00-2-3-50-50.mrc -nx 2 -ny 3 -nz 1 -M 2 -A 50 0 0 -B 0 50 0 -M 2
	../$(OSTYPE)/$(OBJECTNAME) -i data/test-00.mrc -o data/test-00-2-3-50-5050.mrc -nx 2 -ny 3 -nz 1 -M 2 -A 50 0 0 -B 50 50 0  -M 2
	../$(OSTYPE)/$(OBJECTNAME) -i data/test-00.mrc -o data/test-00-2-3-100-100.mrc -nx 2 -ny 3 -nz 1 -M 2 -A 100 0 0 -B 0 100 0 -M 2
	../$(OSTYPE)/$(OBJECTNAME) -i data/test-00.mrc -o data/test-00-2-3-100-100100.mrc -nx 2 -ny 3 -nz 1 -M 2 -A 100 0 0 -B 100 100 0  -M 2
	../$(OSTYPE)/$(OBJECTNAME) -i data/test-000.mrc -o data/test-000-2-3-4.mrc -nx 2 -ny 3 -nz 4 -M 2 -start -40 -40 -40
	../$(OSTYPE)/$(OBJECTNAME) -i data/test-000.mrc -o data/test-000-2-3-4-80-80-80.mrc -nx 2 -ny 3 -nz 4 -M 2 -A 80 0 0 -B 0 80 0 -C 0 0 80 -start  -40 -40 -40 -M 2
	../$(OSTYPE)/$(OBJECTNAME) -i data/test-000.mrc -o data/test-000-2-3-4-80_0_0-80_80_0-0_80_80.mrc -nx 2 -ny 3 -nz 4 -M 2 -A 80 0 0 -B 80 80 0 -C 0 80 80 -start -40 -40 -40 -M 2
	@echo "----- Calc check -----"		

clean:
