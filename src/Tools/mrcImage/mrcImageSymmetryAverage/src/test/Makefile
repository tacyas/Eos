include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

DATA=data/FlagellaSection-0001

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).cen -o $(DATA).rot12 -n 12 -centre 128 128 0
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).cen -o $(DATA).rot13 -n 13 -centre 128 128 0
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).cen -o $(DATA).rot14 -n 14 -centre 128 128 0
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).cen -o $(DATA).0.rot12 -n 12 -centre 0 0 0
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).cen -o $(DATA).0.rot13 -n 13 -centre 0 0 0
	../$(OSTYPE)/$(OBJECTNAME) -i $(DATA).cen -o $(DATA).0.rot14 -n 14 -centre 0 0 0
	@echo "----- Calc check -----"		

clean:

init:
	mrcImageSymmetryCentreFind -i $(DATA).roi -o $(DATA).cen -O $(DATA).info -m 0 
