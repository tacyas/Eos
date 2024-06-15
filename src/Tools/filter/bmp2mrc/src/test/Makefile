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
	# Mono
	../$(OSTYPE)/$(OBJECTNAME) -i data/Airplane.bmp -o data/Airplane.mrc
	# Color
	../$(OSTYPE)/$(OBJECTNAME) -i data/Mandrill.bmp -o data/Mandrill.mrc
	@echo "----- Calc check -----"		

clean:
