all: 
	for i in $(SOURCE); \
	do \
		echo $$i;    \
		$(CD) $$i;   \
		$(MAKE) all; \
		$(CD) ..;    \
	done

install:
	for i in $(SOURCE);\
	do \
		$(CD) $$i; $(MAKE) install; $(CD) ..; \
	done

debug: 
	for i in $(SOURCE); \
	do \
		echo $$i;    \
		$(CD) $$i;   \
		$(MAKE) debug; \
		$(CD) ..;    \
	done

install-debug:
	for i in $(SOURCE);\
	do \
		$(CD) $$i; $(MAKE) install-debug; $(CD) ..; \
	done

clean: 
	for i in $(SOURCE);\
	do \
		$(CD) $$i; $(MAKE) clean; $(CD) ..; \
	done

put: 
	for i in $(SOURCE);\
	do \
		$(CD) $$i; $(MAKE) put; $(CD) ..; \
	done

depend: check
	for i in $(SOURCE);\
	do \
		$(CD) $$i; $(MAKE) depend; $(CD) ..; \
	done

check::
	@if [ ! -d $(EOS_HOME)/lib ] ; then \
		mkdir $(EOS_HOME)/lib ; \
	fi
	@if [ ! -d $(EOS_HOME)/include ] ; then \
		mkdir $(EOS_HOME)/include ; \
	fi
	@for i in $(SOURCE);\
	do \
		$(CD) $$i; \
		dotSourceInMakefileCreate ./ $$i $(WORLDNAME); \
		$(RM) -f Makefile; \
		$(CP) ../../Config/Template/$(WORLDNAME)ClassTemplate.Dir/Makefile Makefile; \
		$(CD) Config; \
		$(RM) -f Target.inc; \
		$(CP) ../../../Config/Template/$(WORLDNAME)ClassTemplate.Dir/Config/Target.inc Target.inc; \
		$(CD) ..; \
		$(MAKE) check; \
		$(CD) ..; \
	done

backup::
	@cd ../..; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/Config ; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/Makefile ; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/.[A-z]*
	@for i in $(SOURCE);\
	do \
		$(CD) $$i; $(MAKE) backup; $(CD) ..; \
	done

backup-all::
	@cd ../..; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/Config ; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/Makefile ; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/.[A-z]*
	@for i in $(SOURCE);\
	do \
		$(CD) $$i; $(MAKE) backup-all; $(CD) ..; \
	done

distribute::
	@cd ../..; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/Config ; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/Makefile ; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/.[A-z]*
	@for i in $(SOURCE);\
	do \
		$(CD) $$i; $(MAKE) distribute; $(CD) ..; \
	done

distribute-all::
	@cd ../..; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/Config ; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/Makefile ; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/.[A-z]*
	@for i in $(SOURCE);\
	do \
		$(CD) $$i; $(MAKE) distribute-all; $(CD) ..; \
	done

