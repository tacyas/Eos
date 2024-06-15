all:
	for dir in ${SOURCE}; \
	do \
		${CD} $${dir}; make all; $(CD) ..; \
	done

install:
	for dir in ${SOURCE}; \
	do \
		${CD} $${dir}; make install; ${CD} ..; \
	done

put:
	for dir in ${SOURCE}; \
	do \
		${CD} $${dir}; make put; ${CD} ..; \
	done

clean:
	for dir in ${SOURCE}; \
	do \
		${CD} $${dir}; make clean; ${CD} ..; \
	done

check:
	@for dir in ${SOURCE}; \
	do \
		$(CD) $${dir}; \
		dotSourceInMakefileCreate ./ $$dir $(WORLDNAME) ; \
		$(RM) -f Makefile; \
		$(CP) ../../Config/Template/$(WORLDNAME)ClassTemplate.Dir/Makefile Makefile; \
		$(CD) Config; \
		$(RM) -f Target.inc ; \
		$(CP) ../../../Config/Template/$(WORLDNAME)ClassTemplate.Dir/Config/Target.inc Target.inc ; \
		$(CD) .. ; 	\
		$(MAKE) check; \
		${CD} ..; \
	done

depend: check
	@for dir in ${SOURCE}; \
	do \
		${CD} $${dir}; make depend; ${CD} ..; \
	done
		
backup: 
	cd ../.. ; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/Config   ;  \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/Makefile ;  \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/.[A-z]* 
	@for dir in ${SOURCE}; \
	do \
		${CD} $${dir}; make backup; ${CD} ..; \
	done

backup-all: 
	cd ../.. ; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/Config   ;  \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/Makefile ;  \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/.[A-z]* 
	@for dir in ${SOURCE}; \
	do \
		${CD} $${dir}; make backup; ${CD} ..; \
	done
		
distribute: 
	cd ../.. ; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/Config   ;  \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/Makefile ;  \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/.[A-z]* 
	@for dir in ${SOURCE}; \
	do \
		${CD} $${dir}; make distribute; ${CD} ..; \
	done
		
distribute-all: 
	cd ../.. ; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/Config   ;  \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/Makefile ;  \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/.[A-z]* 
	@for dir in ${SOURCE}; \
	do \
		${CD} $${dir}; make distribute-all; ${CD} ..; \
	done
		
