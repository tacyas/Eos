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
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.rect -o data/test.rect.edge0 -w 2 -e 0
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.rect -o data/test.rect.edge1 -w 2 -e 1
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.rect -o data/test.rect.edge0-10 -w 10 -e 0
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.rect -o data/test.rect.edge1-10 -w 10 -e 1
	@echo "----- Calc check -----"		

init:
	mrcImageSiemensStar -o data/test.rect -m 0 -N 256 256 -R 64 -n 18 -Shape 0 -m 2


clean:
