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
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/test.nea   -i2 data/test.far \
							   -o1 data/test.asnea -o2 data/test.asfar \
							   -a  data/test.avg   \
							   -o  data/test.param -op2 data/test.paramP2 \
							   -t  764.4 \
							   -l  data/llaxis.info \
							   -O 0 0 1 \
							   -x -20 20 1 \
							   -R 20 
	@echo "----- Calc check -----"		
	diff test.param-dist test.param	
	#diff test.avg-dist   test.avg

exec2:
	@echo "----- Execution Check 2 -----"
	../$(OSTYPE)/$(OBJECTNAME) -i1 data/test2.nea   -i2 data/test2.far \
							   -o1 data/test2.asnea -o2 data/test2.asfar \
							   -a  data/test2.avg   \
							   -o  data/test2.param -op2 data/test2.paramP2 \
							   -t  430 \
							   -l  data/llaxis.info2 \
							   -O   0 0 1 \
							   -x -100 100 1 \
							   -R 30 
	@echo "----- Calc check -----"		
	diff data/test2.param-dist data/test2.param	
	#diff test2.avg-dist   test2.avg

clean:
	@echo "----- Cleaning -----"
	@rm -f data/test.asnea  data/test.asfar  data/test.paramP2  data/test.param  data/test.avg
	@rm -f data/test2.asnea data/test2.asfar data/test2.paramP2 data/test2.param data/test2.avg

