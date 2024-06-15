include ../../../Config/Define.inc
include ../../Config/Define.inc
include ../Config/Define.inc
include Config/Define.inc

DIRS = src inc doc

all:
	for dir in ${DIRS} ; \
	do \
		$(CD) $${dir}; $(MAKE) all; $(CD) ..; \
	done

install:
	for dir in ${DIRS}; \
	do \
		${CD} $${dir} ; $(MAKE) install; $(CD) ..; \
	done

debug:
	for dir in ${DIRS} ; \
	do \
		$(CD) $${dir}; $(MAKE) debug; $(CD) ..; \
	done

install-debug:
	for dir in ${DIRS}; \
	do \
		${CD} $${dir} ; $(MAKE) install-debug; $(CD) ..; \
	done

clean:
	for dir in ${DIRS} ; \
	do \
		$(CD) $${dir}; $(MAKE) clean; $(CD) ..; \
	done

depend:
	for dir in ${DIRS} ; \
	do \
		$(CD) $${dir}; $(MAKE) depend; $(CD) ..; \
	done

put:
	for dir in ${DIRS} ; \
	do \
		$(CD) $${dir}; $(MAKE) put; $(CD) ..; \
	done

check:
	@cd src; \
	if [ ! -d $(EOS_HOME)/hostdepend/$(OSTYPE)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE) ] ; then \
                echo making directory; \
                mkdir -p $(EOS_HOME)/hostdepend/$(OSTYPE)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE); \
        fi 
	if [ ! -L src/$(OSTYPE) ] ; then \
		rm -rf  src/$(OSTYPE) ; \
	fi
	ln -sf ../../../../../hostdepend/$(OSTYPE)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE) src/$(OSTYPE); 
	@$(RM) -f src/Makefile
	@$(RM) -f inc/Makefile
	@$(RM) -f doc/Makefile
	@$(CP) ../../../Config/Template/$(WORLDNAME)Template.Dir/src/Makefile src/Makefile
	@$(CP) ../../../Config/Template/$(WORLDNAME)Template.Dir/inc/Makefile inc/Makefile
	@$(CP) ../../../Config/Template/$(WORLDNAME)Template.Dir/doc/Makefile doc/Makefile
	@rm -f src/.Depend src/.Source
	@touch src/$(OSTYPE)/.Depend
	@touch src/$(OSTYPE)/.Source
	@touch src/.CCHeader
	@touch src/.CHeader
	@touch src/.Wish
	@touch src/.Ruby
	@cd inc; make install
	@cd src; make install-ascii

#
# CVS
#
cvsupdate:: 
	cvs -d $(EOS_CVSROOT) update -d   

cvscommit::
	cvs -d $(EOS_CVSROOT) commit -R

#
# Backup
#
backup:
	@cd ../../../.. ; \
	echo $(OBJECTNAME) ; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Config ; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Makefile ; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/inc ; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/doc; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/.[A-z]*;  \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/[A-z]*.*; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/.[A-z]*

backup-all:
	@cd ../../../.. ; \
	echo $(OBJECTNAME) ; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Config ; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/inc ; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/doc; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/.[A-z]*;  \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/[A-z]*.*; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/.[A-z]*

#
# Distribution
#
distribute:
	@cd ../../../.. ; \
	echo $(OBJECTNAME) ; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Config ; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/inc ; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/doc; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/.[A-z]*;  \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/[A-z]*.*; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/.[A-z]* ; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE) 

distribute-all:
	@cd ../../../.. ; \
	echo $(OBJECTNAME) ; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Config ; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/inc ; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/doc; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/.[A-z]*;  \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/[A-z]*.*; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/.[A-z]* ; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/$(OSTYPE) 

include Config/Target.inc

