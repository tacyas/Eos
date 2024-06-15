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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -I -rmax 100 -m 2 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -I -m 0
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -I -m 1
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -I -m 2
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -I -m 3
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -I -m 4
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -I -m 5
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -I -m 6
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -I -m 7
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -H 32  -High 255 -Low 0 -o data/test.H.out;  cat data/test.H.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -H2 1  -High 255 -Low 0 -o data/test.H2.out; cat data/test.H2.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -H3 32 -High 255 -Low 0 -o data/test.H3.out; cat data/test.H3.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -H4 1  -High 255 -Low 0 -o data/test.H4.out; cat data/test.H4.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -H5 32 -High 255 -Low 0 -o data/test.H5.out; cat data/test.H5.out
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.roi -H6 1  -High 255 -Low 0 -o data/test.H6.out; cat data/test.H6.out
	@echo "----- Calc check -----"		

exec2:
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.in -I -m 8 
	@echo "----- Calc check -----"		

clean:
