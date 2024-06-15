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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc -o data/test.out0.mrc -m 0 -ey 50 -wx 1
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc -o data/test.out1.mrc -m 0 -ey 100 -wx 1
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc -o data/test.out2.mrc -m 0 -ey 50 -wx 3
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc -o data/test.out3.mrc -m 0 -ey 100 -wx 3
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc -o data/test.out1-3.mrc -m 1 -ey 100 -wx 3
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc -o data/test.out2-3.mrc -m 2 -ey 100 -wx 3 -trim 0.2
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc -o data/test.out2.1-3.mrc -m 2 -ey 100 -wx 3 -trim 0.0
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc -o data/test.out3-3.mrc -m 3 -ey 100 -wx 3 
	@echo "----- Calc check -----"		

clean:
