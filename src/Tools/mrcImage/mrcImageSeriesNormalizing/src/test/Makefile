include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

init:
	rm -rf data/test.in.lst;
	rm -rf data/test.out.lst;
	while read i max min ; do \
		echo $$i, $$min, $$max; \
		mrcImageNormalizing -m 4 -A $$max -B $$min -i data/121p.mrc3d -o data/121p.$$i ; \
		mrcImageNoiseAdd -i data/121p.$$i -o data/121p.$$i.mrc -SD 0.01 ; \
		echo "data/121p.$$i.mrc" >> data/test.in.lst;  \
		echo "data/121p.$$i.out" >> data/test.out.lst; \
	done < test.init;  

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in.lst -o data/test.out.lst -H 0.9 -L 0.1  -High 0.95 -Low 0.7 -param data/test.param  -m 0 -LowExp 0.32 5 0  -HighExp 32 5 0 -maxIter 100 -UseLH 1 1
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.in.lst -o data/test.out.lst -H 0.9 -L 0.1  -High 0.95 -Low 0.7 -param data/test2.param -m 0 -LowExp 0.32 5 0  -HighExp 32 5 0 -maxIter 100 -UseLH 1 0
	cat data/test.param
	cat data/test2.param
	@echo "----- Calc check -----"		

clean:
