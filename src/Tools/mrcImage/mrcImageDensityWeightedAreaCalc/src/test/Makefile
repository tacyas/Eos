include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

DATA=data/TEM_filter_sample

all: help exec exec1

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).bin3 -d $(DATA).mrc3 -o $(DATA)-8.densWA -oL $(DATA)-8.label -n 8 -m 0
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).bin3 -d $(DATA).mrc3 -o $(DATA)-4.densWA -oL $(DATA)-4.label -n 4 -m 0
	@echo "----- Calc check -----"		

exec1:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).bin3 -d $(DATA).mrc3 -o $(DATA)-8-1.densWA -oL $(DATA)-8-1.label -n 8 -m 1
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).bin3 -d $(DATA).mrc3 -o $(DATA)-4-1.densWA -oL $(DATA)-4-1.label -n 4 -m 1
	@echo "----- Calc check -----"		

clean:
