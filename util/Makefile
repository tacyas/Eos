include ${EOS_HOME}/src/Config/${EOS_HOST}${FLAG_ICC}.inc
include Config/Define.inc

help:
	@echo ">>>> How to set a new util for a new architecture"
	@echo "$$ make setting"
	@echo ">>> Rebuild"
	@echo "$$ make rebuild"
	@echo "$$  or "
	@echo "$$ make check"
	@echo "$$ make clean"
	@echo "$$ make config"
	@echo "$$ make all"
	@echo ">>> Cleaning directories"
	@echo "$$ make clean"
	@echo "$$ make cleanAll"

rebuild:
	make check
	make clean
	make config
	make all
	make cleanAll

check: 
	cd src$(OSTYPE)	; \
	make check

config: 
	cd src$(OSTYPE)	; \
	make config 

all: 
	cd src$(OSTYPE)	; \
	make all 

clean: 
	cd src$(OSTYPE)	; \
	make clean 

cleanAll: 
	cd src$(OSTYPE)	; \
	make cleanAll 


setting: orgsetting
	@if [ -L orgsrc ] ; then \
		echo "Already orgsrc"; \
	else \
		echo "Create orgsrc"; \
		mkdir -p ../others/utilsrc/; \
		ln -sf   ../others/utilsrc/ orgsrc; \
	fi
	@if [ -L src$(OSTYPE) ] ; then    \
		echo "Already src$(OSTYPE)"; \
	else \
		echo "Create src$(OSTYPE)";     \
		mkdir -p orgsrc/src$(OSTYPE);   \
		ln -sf   orgsrc/src$(OSTYPE) .; \
	fi
	@if [ -L orghostdepend ] ; then \
		echo "Already orghostdepnd"; \
	else \
		echo "Create orghostdepnd"; \
		mkdir -p ../hostdepend/; \
		ln -sf   ../hostdepend/ orghostdepend; \
	fi
	@if [ -L $(OSTYPE) ] ; then    \
		echo "Already $(OSTYPE)"; \
	else \
		echo "Create $(OSTYPE)";     \
		mkdir -p orghostdepend/$(OSTYPE);   \
		ln -sf   orghostdepend/$(OSTYPE) .; \
	fi
	@cd src$(OSTYPE)	; \
	if [ -L  Makefile ] ; then \
		echo "Already Makefile"; \
	else \
		ln -sf ../src/Makefile .; \
	fi; \

orgsetting:
	@if [ -d ../others ] ; then \
		echo "Already ../others" ; \
	else \
		echo "You must get others by git first."; \
	fi
	@if [ -d ../hostdepend ] ; then \
		echo "Already ../hostdepend" ; \
	else \
		echo "You must get hostdepend by git first."; \
	fi
