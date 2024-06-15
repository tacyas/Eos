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
	../$(OSTYPE)/$(OBJECTNAME)  -I data/test.in -o data/test.out
	@echo "----- Calc check -----"		

clean:

init:
	rm -f data/test.in
	for i in 00 10 20 30 40 50 60; do \
		pdb2mrc2d -i data/121p.pdb -o data/121p-$$i.mrc -startEA YOYS $$i 0 0 -d 1.25 1.25 -s -40 -40 -n 64 64 -sig 2.0; \
		echo "data/121p-$$i.mrc" >> data/test.in; \
	done
