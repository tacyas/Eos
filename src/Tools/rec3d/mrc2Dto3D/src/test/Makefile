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
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc2d3d -o data/test.mrc2d3d.mrc3d.1 -Double -CounterThreshold 1 -WeightMode 3 -m 1 -InterpolationMode 2 -DoubleCounter data/test.mrc2d3d.mrc3d.counter.1 2> /dev/null
	time ~/Eos/bin/$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc2d3d -o data/test.mrc2d3d.mrc3d -Double -CounterThreshold 1 -WeightMode 3 -m 1 -InterpolationMode 2 -DoubleCounter data/test.mrc2d3d.mrc3d.counter 2> /dev/null

exec2:
	@echo "----- Execution Check 2-----"
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test2.mrc2d3d -o data/test2.mrc2d3d.mrc3d.2 -Double -CounterThreshold 1 -WeightMode 3 -m 1 -InterpolationMode 2 -DoubleCounter data/test2.mrc2d3d.mrc3d.counter.2 2> /dev/null
	time ~/Eos/bin/$(OSTYPE)/$(OBJECTNAME) -i data/test2.mrc2d3d -o data/test2.mrc2d3d.mrc3d -Double -CounterThreshold 1 -WeightMode 3 -m 1 -InterpolationMode 2 -DoubleCounter data/test2.mrc2d3d.mrc3d.counter 2> /dev/null

exec-pthread:
	@echo "----- Execution Check -----"
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc2d3d -o data/test.mrc2d3d.mrc3d-pthread -Double -CounterThreshold 1 -WeightMode 3 -m 1 -InterpolationMode 2 -DoubleCounter data/test.mrc2d3d.mrc3d.counter-pthread -pthread 8 

exec2-pthread:
	@echo "----- Execution Check -----"
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test2.mrc2d3d -o data/test2.mrc2d3d.mrc3d-pthread -Double -CounterThreshold 1 -WeightMode 3 -m 1 -InterpolationMode 2 -DoubleCounter data/test2.mrc2d3d.mrc3d.counter-pthread -pthread 8 

exec3-pthread:
	@echo "----- Execution Check -----"
	time ../$(OSTYPE)/$(OBJECTNAME) -I data/test.mrc2d3d.Info -each -o data/test.mrc2d3d.mrc3d-each-pthread -Double -CounterThreshold 1 -WeightMode 3 -m 1 -InterpolationMode 2 -DoubleCounter data/test.mrc2d3d.mrc3d.counter-each-pthread -pthread 8 

exec4-pthread:
	@echo "----- Execution Check -----"
	time ../$(OSTYPE)/$(OBJECTNAME) -I data/test2.mrc2d3d.Info -each -o data/test2.mrc2d3d.mrc3d-each-pthread -Double -CounterThreshold 1 -WeightMode 3 -m 1 -InterpolationMode 2 -DoubleCounter data/test2.mrc2d3d.mrc3d.counter-each-pthread -pthread 16 

exec-1:
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc2d3d -o data/test.mrc2d3d.mrc3d1 -m 1
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc2d3d -o data/test.mrc2d3d.mrc3d1-d -Double -m 1
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc2d3d -o data/test.mrc2d3d.mrc3d1-d-s -Double -SIRT -rms 0.01 -max 30 -m 1

exec-2:
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc2d3d -o data/test.mrc2d3d.mrc3d0 -m 0 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc2d3d -o data/test.mrc2d3d.mrc3d0-d -Double -m 0 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc2d3d -o data/test.mrc2d3d.mrc3d0-d-s -Double -SIRT -rms 0.01 -max 30-m 0 

exec-5:
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc2d3d -o data/test.mrc2d3d.mrc3d2 -m 2 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc2d3d -o data/test.mrc2d3d.mrc3d2-d -Double -m 2 
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test.mrc2d3d -o data/test.mrc2d3d.mrc3d2-d-s -Double -SIRT -rms 0.01 -max 30 -m 2 

prepare:
	# GC: 6.727136e+01    3.631518e+01   -2.983928e+01
	pdb2mrc -i data/1vomTrans.pdb -o data/test.mrc3d -nx 21 -ny 21 -nz 21 -dx 10 -dy 10 -dz 10 -Sx -100 -Sy -100 -Sz -100
	pdb2mrc2d -i data/1vomTrans.pdb -o data/test.mrc2d -d 10 10 -s -100 -100 -Rot 30 30 -n 21 21 -O data/test.mrc2d3d -m 1  

prepare2:
	# GC: 6.727136e+01    3.631518e+01   -2.983928e+01
	pdb2mrc -i data/1vomTrans.pdb -o data/test2.mrc3d -nx 81 -ny 81 -nz 81 -dx 2.5 -dy 2.5 -dz 2.5 -Sx -100 -Sy -100 -Sz -100 -sig 2.5
	pdb2mrc2d -i data/1vomTrans.pdb -o data/test2.mrc2d -d 2.5 2.5 -s -100 -100 -Rot 30 30 -n 81 81 -O data/test2.mrc2d3d -m 1 -sig 2.5 

prepare-all:
	# GC: 6.727136e+01    3.631518e+01   -2.983928e+01
	pdb2mrc   -i data/1vomTrans.pdb -o data/test00.mrc3d -nx 10 -ny 10 -nz 10 -dx 20 -dy 20 -dz 20 -Sx -100 -Sy -100 -Sz -100 -sig 2.5 
	pdb2mrc2d -i data/1vomTrans.pdb -o data/test00.mrc2d -d 20 20     -s -100 -100 -Rot 10 10 -n 10 10 -O data/test00.mrc2d3d -m 1 -sig 2.5 
	pdb2mrc   -i data/1vomTrans.pdb -o data/test01.mrc3d -nx 20 -ny 20 -nz 20 -dx 10 -dy 10 -dz 20 -Sx -100 -Sy -100 -Sz -100 -sig 2.5 
	pdb2mrc2d -i data/1vomTrans.pdb -o data/test01.mrc2d -d 10 10     -s -100 -100 -Rot 10 10 -n 20 20 -O data/test01.mrc2d3d -m 1 -sig 2.5 
	pdb2mrc   -i data/1vomTrans.pdb -o data/test02.mrc3d -nx 40 -ny 40 -nz 40 -dx 5 -dy 5 -dz 5 -Sx -100 -Sy -100 -Sz -100 -sig 2.5 
	pdb2mrc2d -i data/1vomTrans.pdb -o data/test02.mrc2d -d 5 5       -s -100 -100 -Rot 10 10 -n 40 40 -O data/test02.mrc2d3d -m 1 -sig 2.5 
	pdb2mrc   -i data/1vomTrans.pdb -o data/test03.mrc3d -nx 80 -ny 80 -nz 80 -dx 2.5 -dy 2.5 -dz 2.5 -Sx -100 -Sy -100 -Sz -100 -sig 2.5 
	pdb2mrc2d -i data/1vomTrans.pdb -o data/test03.mrc2d -d 2.5 2.5   -s -100 -100 -Rot 10 10 -n 80 80 -O data/test03.mrc2d3d -m 1 -sig 2.5
	pdb2mrc   -i data/1vomTrans.pdb -o data/test04.mrc3d -nx 160 -ny 160 -nz 160 -dx 1.25 -dy 1.25 -dz 1.25 -Sx -100 -Sy -100 -Sz -100 -sig 2.5 
	pdb2mrc2d -i data/1vomTrans.pdb -o data/test04.mrc2d -d 1.25 1.25 -s -100 -100 -Rot 10 10 -n 160 160 -O data/test04.mrc2d3d -m 1 -sig 2.5

exec-all:
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test00.mrc2d3d -o data/test00.mrc2d3d.mrc3d -m 1 -InterpolationMode 2 -single 1 2> /dev/null
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test01.mrc2d3d -o data/test01.mrc2d3d.mrc3d -m 1 -InterpolationMode 2 -single 1 2> /dev/null
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test02.mrc2d3d -o data/test02.mrc2d3d.mrc3d -m 1 -InterpolationMode 2 -single 1 2> /dev/null
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test03.mrc2d3d -o data/test03.mrc2d3d.mrc3d -m 1 -InterpolationMode 2 -single 1 2> /dev/null
	time ../$(OSTYPE)/$(OBJECTNAME) -i data/test04.mrc2d3d -o data/test04.mrc2d3d.mrc3d -m 1 -InterpolationMode 2 -single 1 2> /dev/null
clean:
