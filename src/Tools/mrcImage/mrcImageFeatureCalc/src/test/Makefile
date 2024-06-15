include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec exec2

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2D.bin -o data/test2D.info -oGC data/test2D.gc -oL data/test2D.label -oP data/test2D.peri
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.info -oGC data/test.gc -oL data/test.label -oS data/test.sa
	@echo "----- Calc check -----"		

exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test2D.bin -o data/test2D.info8 -oGC data/test2D.gc8 -oL data/test2D.label8 -oP data/test2D.peri8 -n 8
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.info18 -oGC data/test.gc18 -oL data/test.label18 -oS data/test.sa18 -n 18
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.bin -o data/test.info26 -oGC data/test.gc26 -oL data/test.label26 -oS data/test.sa26 -n 26 
	@echo "----- Calc check -----"		

clean:
