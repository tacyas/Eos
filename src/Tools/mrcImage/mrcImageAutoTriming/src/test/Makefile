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
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p.bin -o data/121p.roi -O data/121p.param -m 0 -EAMode ZONS -Rot1 -10 10 1 -Rot2 0 0 1 -Rot3 0 0 1
	@echo "----- Calc check -----"		

init:
	mrcImageBinalization -i data/121p.in -o data/121p.bin -m 32

clean:
