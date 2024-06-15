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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test60.bin -o data/test60.peri0 -oA data/test60.area0 -oL data/test60.label0 -oC data/test60.chain0 -m 0
	../$(OSTYPE)/$(OBJECTNAME) -i data/test60.bin -o data/test60.peri1 -oA data/test60.area1 -oL data/test60.label1 -oC data/test60.chain1 -m 1
	../$(OSTYPE)/$(OBJECTNAME) -i data/test60.bin -o data/test60.peri2 -oA data/test60.area2 -oL data/test60.label2 -oC data/test60.chain2 -m 2
	../$(OSTYPE)/$(OBJECTNAME) -i data/test60.bin -o data/test60.peri3 -oA data/test60.area3 -oL data/test60.label3 -oC data/test60.chain3 -m 3
	@echo "----- Calc check -----"		

clean:
