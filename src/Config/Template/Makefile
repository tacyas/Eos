# Top Level Makefile

all:
	cd Objects; make
	cd Tools; make

check: check-objects check-tools


check-objects:
	rm -f Objects/Makefile; cp -f Config/Template/ObjectsHomeTemplate.Dir/Makefile Objects/Makefile 
	cd Objects; dotSourceInMakefileCreate; make check

check-tools:
	rm -f Tools/Makefile  ; cp -f Config/Template/ToolsHomeTemplate.Dir/Makefile   Tools/Makefile   
	cd Tools  ; dotSourceInMakefileCreate; make check

depend:
	cd Objects; make depend 
	cd Tools; make depend 

install:
	cd Objects; make install 
	cd Tools; make install 

clean:
	cd Objects; make clean 
	cd Tools; make clean 

