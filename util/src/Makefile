include ${EOS_HOME}/src/Config/${EOS_HOST}.inc

CLASS = \
	Admin    \
	AI \
	CUDA \
	Database \
	DataFormat \
	Graphics \
	ImageAnalysis \
	MATH \
	Sound \
	TclTk 

help::
	@echo make check
	@echo make config
	@echo make all
	@echo make clean 
	@echo make cleanAll

check:
	@echo "---- Checking Directories ----"
	@for class in $(CLASS);  \
	do \
		echo "Checking $${class}" ; \
		if [ ! -d $${class} ] ;  \
		then \
			mkdir $${class}; \
		fi; \
		cd $${class}; \
		if [ -d ../../src/$${class}/Config ] ; \
		then \
			ln -sf ../../src/$${class}/Config; \
		fi ; \
		ln -sf ../../src/$${class}/Makefile . ; \
		cd ..; \
	done
	@for class in $(CLASS);  \
	do \
		echo "Checking in $${class}"; \
		cd $${class};                 \
		$(MAKE) check ;               \
		cd ..; \
	done

config: 
	for class in $(CLASS);  \
	do \
		echo "Configuration $${class}" ; \
		cd $${class}; \
		$(MAKE) config; \
		cd ..; \
	done

all: 
	for class in $(CLASS);  \
	do \
		echo "Installation $${class}" ; \
		cd $${class}; \
		$(MAKE) ; \
		cd ..; \
	done

clean: 
	for class in $(CLASS);  \
	do \
		echo "Cleaning $${class}" ; \
		cd $${class}; \
		$(MAKE) clean; \
		cd ..; \
	done


cleanAll: 
	for class in $(CLASS);  \
	do \
		echo "Cleaning $${class}" ; \
		cd $${class}; \
		$(MAKE) cleanAll; \
		cd ..; \
	done


