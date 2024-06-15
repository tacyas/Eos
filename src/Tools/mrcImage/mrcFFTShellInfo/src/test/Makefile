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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.fft -o data/test.out -m 3 
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.fft -o data/test-0.10-0.12.out -m 3 -R 0.10 0.12
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.fft -o data/test-0.10-0.11.out -m 3 -R 0.10 0.11
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.fft -o data/test-0.11-0.12.out -m 3 -R 0.11 0.12
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.fft -o data/test-0.12-0.14.out -m 3 -R 0.12 0.14
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.fft -o data/test-0.12-0.13.out -m 3 -R 0.12 0.13
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.fft -o data/test-0.13-0.14.out -m 3 -R 0.13 0.14
	@echo "----- Calc check -----"		

clean:
