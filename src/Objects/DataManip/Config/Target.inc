all: 
	for i in $(SOURCE); \
	do \
		echo "---- $$i ----" ; \
		$(CD) $$i; $(MAKE) all; $(CD) ..; \
	done

install:
	for i in $(SOURCE);\
	do \
		echo "---- $$i ----" ; \
		$(CD) $$i; $(MAKE) install; $(CD) ..; \
	done

debug: 
	for i in $(SOURCE); \
	do \
		echo "---- $$i ----" ; \
		$(CD) $$i; $(MAKE) debug; $(CD) ..; \
	done

install-debug:
	for i in $(SOURCE);\
	do \
		echo "---- $$i ----" ; \
		$(CD) $$i; $(MAKE) install-debug; $(CD) ..; \
	done

clean: 
	for i in $(SOURCE);\
	do \
		echo "---- $$i ----" ; \
		$(CD) $$i; $(MAKE) clean; $(CD) ..; \
	done

depend: check
	for i in $(SOURCE);\
	do \
		echo "---- $$i ----" ; \
		$(CD) $$i; $(MAKE) depend; $(CD) ..; \
	done

check:: 
	@for i in $(SOURCE);\
	do \
		echo "---- $$i ----" ; \
		$(CD) $$i; \
		dotSourceInMakefileCreate ./ $$i $(CLASSNAME); \
		$(RM) -f Makefile; \
		$(CP) ../../../Config/Template/$(WORLDNAME)Template.Dir/Makefile Makefile; \
		$(CD) Config; \
		$(RM) -f Target.inc; \
		$(CP) ../../../../Config/Template/$(WORLDNAME)Template.Dir/Config/Target.inc Target.inc; \
		$(CD) ..; \
		$(MAKE) check; \
		$(CD) ..; \
	done

backup:: 
	@cd ../../.. ; \
	echo $(CLASSNAME); \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/Config; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/.[A-z]*; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/Makefile 
	for i in $(SOURCE);\
	do \
		$(CD) $$i; \
		$(MAKE) backup; \
		$(CD) ..; \
	done

backup-all:: 
	@cd ../../.. ; \
	echo $(CLASSNAME); \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/Config; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/.[A-z]*; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/Makefile 
	for i in $(SOURCE);\
	do \
		$(CD) $$i; \
		$(MAKE) backup-all; \
		$(CD) ..; \
	done

distribute:: 
	@cd ../../.. ; \
	echo $(CLASSNAME); \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/Config; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/.[A-z]*; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/Makefile 
	@echo $(CLASSNAME); \
	for i in $(SOURCE);\
	do \
		$(CD) $$i; $(MAKE) distribute; $(CD) ..; \
	done

distribute-all:: 
	@cd ../../.. ; \
	echo $(CLASSNAME); \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/Config; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/.[A-z]*; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/Makefile 
	@echo $(CLASSNAME); \
	for i in $(SOURCE); \
	do \
		$(CD) $$i; $(MAKE) distribute-all; $(CD) ..; \
	done

