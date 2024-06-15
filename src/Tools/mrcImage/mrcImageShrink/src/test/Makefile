include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

NAME=data/121p

all: help exec


help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(NAME).mrc3d -o $(NAME).mrc3d.shrink -S 4
	../$(OSTYPE)/$(OBJECTNAME) -i $(NAME).mrc2d -o $(NAME).mrc2d.shrink -S 4
	@echo "----- Calc check -----"		

clean:

init:
	pdb2mrc   -i $(NAME).pdb -o $(NAME).mrc3d -nx 64 -ny 64 -nz 64 -Sx -32 -Sy -32 -Sz -32 -dx 1 -dy 1 -dz 1 -w 1 -sig 2.6 -m 0 
	pdb2mrc2d -i $(NAME).pdb -o $(NAME).mrc2d -d 1 1 -s -32 -32 -n 64 64 -w 1.0 -sig 2.6 -Rot 1 1  
