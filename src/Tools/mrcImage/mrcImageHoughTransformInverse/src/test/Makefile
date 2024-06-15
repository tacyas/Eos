include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

NAME=data/test

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i $(NAME).hough00 -o $(NAME).inverse00 -Nx 100 -Ny 100 -d 5 
	../$(OSTYPE)/$(OBJECTNAME) -i $(NAME).hough01 -o $(NAME).inverse01 -Nx 100 -Ny 100 -d 5 
	@echo "----- Calc check -----"		

clean:

init:
	mrcImageModelCreate -o $(NAME).tst -nx 100 -ny 100 -nz 1 -m 2 
	mrcImageHoughTransform -i $(NAME).tst -o $(NAME).hough00 -dTheta 0.5 -dRho 0.5 -m 0 -M 0 
	mrcImageHoughTransform -i $(NAME).tst -o $(NAME).hough01 -dTheta 0.5 -dRho 0.5 -m 1 -M 0  
