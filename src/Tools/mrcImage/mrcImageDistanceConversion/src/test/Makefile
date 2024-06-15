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
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-move-2d.bin -o data/121p-move-2d.distance4 -m 4
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-move-2d.bin -o data/121p-move-2d.distance8 -m 8 
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-move.bin -o data/121p-move.distance4 -m 4
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-move.bin -o data/121p-move.distance8 -m 8 
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-move.bin -o data/121p-move.distance6 -m 6
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-move.bin -o data/121p-move.distance18 -m 18
	../$(OSTYPE)/$(OBJECTNAME) -i data/121p-move.bin -o data/121p-move.distance26 -m 26
	@echo "----- Calc check -----"		

clean:

init:
	mrcImageBinalization -i data/121p-move-2d.mrc -o data/121p-move-2d.bin -t 1
	mrcImageBinalization -i data/121p-move.mrc -o data/121p-move.bin -t 1
