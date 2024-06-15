include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME) -h

exec: exec1 exec2

exec1:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/test.log -o data/test.logout -O data/test.logOut -PS data/test.ps -Last 1 -S 7 100 -P 0 400 -Log -Scaling -I data/test.lst -Offset 1e3 -OL data/test.clstlst -AL data/test.avglst 4 avg
	@echo "----- Calc check -----"		
	diff test.ps test.ps.org

exec2:
	@echo "----- Execution Check2 -----"
	../$(OSTYPE)/$(OBJECTNAME) -ib data/test.logbin -PS data/test.bin.ps -o data/test.bin.logout -O data/test.bin.logOut -Last 1 -S 7 100 -P 0 400 -Log -Scaling -I data/test.lst -Offset 1e3 -OL data/test.clstlst -AL data/test.avglst 4 avg
	@echo "----- Calc check -----"
	diff test.bin.ps test.bin.ps.org

clean:
