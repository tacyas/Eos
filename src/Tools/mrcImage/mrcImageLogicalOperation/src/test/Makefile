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
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin.mrc -o data/test.out.0 -m 0 
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin-bottomhat.mrc -o data/test.out.1 -m 1 
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin.mrc -o data/test.out.2 -m 2 
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin-bottomhat.mrc -o data/test.out.3 -m 3 
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin-bottomhat.mrc -o data/test.out.4 -m 4 
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin.mrc -o data/test.out.5 -m 5 
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin-bottomhat.mrc -o data/test.out.6 -m 6
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin-bottomhat.mrc -o data/test.out.7 -m 7 
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin-bottomhat.mrc -o data/test.out.8 -m 8 
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin-bottomhat.mrc -o data/test.out.9 -m 9 
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin-bottomhat.mrc -o data/test.out.10 -m 10
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin-bottomhat.mrc -o data/test.out.11 -m 11 
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin-bottomhat.mrc -o data/test.out.12 -m 12 
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin-bottomhat.mrc -o data/test.out.13 -m 13 
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/121p-bin-tophat.mrc -i2 data/121p-bin-bottomhat.mrc -o data/test.out.14 -m 14
	@echo "----- Calc check -----"		

clean:
