include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

NAME=data/1atn

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME)  -ipdb $(NAME).pdbtrans -imrc $(NAME).mrc \
				-C 44.6623 -CM 0 \
				-omrc $(NAME).fitmap -otxt $(NAME).fittxt -opdb $(NAME).fitpdb  \
				-Centre \
				-xmin -10  -xmax 0 -xd 1 \
				-ymin -14 -ymax -6 -yd 1 \
				-zmin  30 -zmax 50 -zd 1 \
				-phimin   -5 -phimax   5 -phid 1 \
				-psimin   -2 -psimax   2 -psid 1 \
				-thetamin -2 -thetamax 2 -thetad 1 

	@echo "----- Calc check -----"		

exec2:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME)  -ipdb $(NAME).pdbtrans2 -imrc $(NAME).mrc \
				-C 44.6623 -CM 0 \
				-omrc $(NAME).fitmap2 -otxt $(NAME).fittxt2 -opdb $(NAME).fitpdb2  \
				-Centre \
				-xmin -10  -xmax 0 -xd 1 \
				-ymin -14 -ymax -6 -yd 1 \
				-zmin  30 -zmax 50 -zd 1 \
				-phimin   5 -phimax   15 -phid 1 \
				-psimin   18 -psimax  22 -psid 1 \
				-thetamin 28 -thetamax 32 -thetad 1 

	@echo "----- Calc check -----"		

exec3:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME)  -ipdb $(NAME).pdbtrans -imrc $(NAME).mrc2 \
				-C 3.18388 -CM 0 \
				-omrc $(NAME).fitmap3 -otxt $(NAME).fittxt3 -opdb $(NAME).fitpdb3  \
				-Centre \
				-xmin -10  -xmax 0 -xd 1 \
				-ymin -14 -ymax -6 -yd 1 \
				-zmin  30 -zmax 50 -zd 1 \
				-phimin   -5 -phimax   5 -phid 1 \
				-psimin   -2 -psimax   2 -psid 1 \
				-thetamin -2 -thetamax 2 -thetad 1 

	@echo "----- Calc check -----"		

exec4:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME)  -ipdb $(NAME).pdbtrans2 -imrc $(NAME).mrc2 \
				-C 3.18388 -CM 0 \
				-omrc $(NAME).fitmap4 -otxt $(NAME).fittxt4 -opdb $(NAME).fitpdb4  \
				-Centre \
				-xmin -10  -xmax 0 -xd 1 \
				-ymin -14 -ymax -6 -yd 1 \
				-zmin  30 -zmax 50 -zd 1 \
				-phimin   5 -phimax   15 -phid 1 \
				-psimin   18 -psimax  22 -psid 1 \
				-thetamin 28 -thetamax 32 -thetad 1 

	@echo "----- Calc check -----"		

clean:
