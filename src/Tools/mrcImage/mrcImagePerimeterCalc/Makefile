include ../../../Config/Define.inc
include ../../Config/Define.inc
include ../Config/Define.inc
include Config/Define.inc

all:
	cd src; make all; cd ..

install:
	cd src; make install; cd ..


putSF:
	if [ -f private ] ; \
	then \
		echo "$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME) is private"; \
	else \
		cvs -z4 -d:ext:$$USER@$$EOS_SOURCEFORGE commit || cvs -z4 -d:ext:$$USER@$$EOS_SOURCEFORGE import src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME); \
	fi

put:
	cd src; make put; cd ..

clean:
	cd src; make clean; cd ..

depend:
	cd src; make depend; cd ..

check:
	@if [ ! -d $(EOS_HOME)/hostdepend/$(OSTYPE)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE) ] ; then \
		echo making directory; \
		mkdir -p $(EOS_HOME)/hostdepend/$(OSTYPE)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE); \
	fi
	@if [ ! -L src/$(OSTYPE) ] ; then \ 
		rm -rf src/$(OSTYPE);  \
	fi
	ln -sf ../../../../../hostdepend/$(OSTYPE)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE) src/$(OSTYPE); 
	@$(RM) src/Makefile
	@echo "New src/Makefile" 
	@$(CP) ../../../Config/Template/$(WORLDNAME)Template.Dir/src/Makefile src/Makefile
	@cd src; rm -f $(OSTYPE)/.Depend; touch $(OSTYPE)/.Depend; make depend

update:
	@if [ ! -d $(EOS_HOME)/hostdepend/$(OSTYPE)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE) ] ; then \
		echo making directory; \
		mkdir -p $(EOS_HOME)/hostdepend/$(OSTYPE)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE); \
	fi
	ln -sf ../../../../../hostdepend/$(OSTYPE)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE) src/$(OSTYPE); 
	@$(RM) src/Makefile
	@echo "New src/Makefile" 
	@$(CP) ../../../Config/Template/$(WORLDNAME)Template.Dir/src/Makefile src/Makefile
	@cd src; rm -f $(OSTYPE)/.Depend; touch $(OSTYPE)/.Depend; echo "Y" | make update      

cvsupdate::
	cvs -d $(EOS_CVSROOT) update -d 

cvscommit::
	cvs -d $(EOS_CVSROOT) commit

backup:
	@cd ../../../..;     \
	echo $(OBJECTNAME) ; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Config	; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Makefile ;\
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/.[A-z]* ; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/inc ; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/doc; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/wish; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/[A-z]*.[A-z]*; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/.[A-z]*; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/Makefile

backup-all:
	@cd ../../../..;     \
	echo $(OBJECTNAME) ; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Config	; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Makefile ;\
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/.[A-z]* ; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/inc ; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/doc; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/wish; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/[A-z]*.[A-z]*; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/.[A-z]*; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/Makefile
	
distribute:
	cd ../../../..;     \
	echo $(OBJECTNAME) ; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Config	; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Makefile ;\
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/.[A-z]* ; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/inc ; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/doc; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/wish; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/[A-z]*.[A-z]*; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/.[A-z]*; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/Makefile ; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE)
	
distribute-all:
	@cd ../../../..;     \
	echo $(OBJECTNAME) ; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Config	; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Makefile ;\
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/.[A-z]* ; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/inc ; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/doc; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/wish; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/[A-z]*.[A-z]*; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/.[A-z]*; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/Makefile ; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE)

eosintroduce:
	${EOS_HOME}/sbin/eosintroduce ${WORLDNAME} ${CLASSNAME} ${OBJECTNAME} ./ 

include Config/Target.inc
