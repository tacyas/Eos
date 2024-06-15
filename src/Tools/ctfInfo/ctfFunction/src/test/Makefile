include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

NAME=data/test

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME)  -df 10000 -o $(NAME).ctf1 -Rmax 0.001
	../$(OSTYPE)/$(OBJECTNAME)  -df 10000 -o $(NAME).ctf2 -Rmax 0.001 -pvm 10 
	../$(OSTYPE)/$(OBJECTNAME)  -df 10000 -o $(NAME).ctf3 -Rmax 0.001 -pvmList pvmList 
	@echo "----- Calc check -----"		
	diff $(NAME).ctf $(NAME).ctf1
	diff $(NAME).ctf $(NAME).ctf2
	diff $(NAME).ctf $(NAME).ctf3
clean:
