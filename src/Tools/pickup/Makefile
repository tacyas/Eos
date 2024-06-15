include ../../Config/Define.inc
include ../Config/Define.inc
include Config/Define.inc
include .Source

all:
	for dir in ${SOURCE} ; \
	do \
		if [ -d $${dir} ] ; then \
			$(CD) $${dir}; make all; $(CD) ..; \
		fi \
	done

install:
	for dir in ${SOURCE} ; \
	do \
		if [ -d $${dir} ] ; then \
			$(CD) $${dir}; make install; $(CD) ..; \
		fi \
	done

put:
	for dir in ${SOURCE} ; \
	do \
		if [ -d $${dir} ] ; then \
			$(CD) $${dir}; make put; $(CD) ..; \
		fi \
	done

putSF:
	if [ -f private ] ; then \
		echo "$(WORLDNAME)/$(CLASSNAME) is private " ; \
	else \
		for dir in ${SOURCE} ; \
		do \
			if [ -d $${dir} ] ; then \
				$(CD) $${dir}; make putSF; $(CD) ..; \
			fi \
		done \
	fi

clean:
	for dir in ${SOURCE} ; \
	do \
		$(CD) $${dir}; make clean; $(CD) ..; \
	done

check:
	@for dir in ${SOURCE} ; do \
		if [ -d $${dir} ] ; then \
			$(CD) $${dir}; \
			echo  $${dir}; \
			$(RM) Makefile; \
			$(CP) ../../../Config/Template/$(WORLDNAME)Template.Dir/Makefile Makefile ; \
			make check; \
			$(CD) ..; \
		fi \
	done

update:
	@for dir in ${SOURCE} ; do \
		if [ -d $${dir} ] ; then \
			$(CD) $${dir}; \
			echo  $${dir}; \
			$(RM) Makefile; \
			$(CP) ../../../Config/Template/$(WORLDNAME)Template.Dir/Makefile Makefile ; \
			make update; \
			$(CD) ..; \
		fi \
	done

depend: check
	@for dir in ${SOURCE} ; \
	do \
		$(CD) $${dir}; make depend; $(CD) ..; \
	done

backup: 
	cd ../../..; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/Config; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/Makefile; \
	tar uvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/.[A-z]*
	tar uvf ${EOS_HOME}/backup/EosBase.tar .[A-z]*
	@for dir in ${SOURCE} ; \
	do \
		$(CD) $${dir}; make backup; $(CD) ..; \
	done

backup-all: 
	cd ../../..; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/Config; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/Makefile; \
	tar rvf ${EOS_HOME}/backup/EosBase.tar src/$(WORLDNAME)/$(CLASSNAME)/.[A-z]*
	tar rvf ${EOS_HOME}/backup/EosBase.tar .[A-z]*
	@for dir in ${SOURCE} ; \
	do \
		$(CD) $${dir}; make backup; $(CD) ..; \
	done

distribute: 
	cd ../../..; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/Config; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/Makefile; \
	tar uvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/.[A-z]*
	@for dir in ${SOURCE} ; \
	do \
		$(CD) $${dir}; make distribute; $(CD) ..; \
	done

distribute-all: 
	cd ../../..; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/Config; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/Makefile; \
	tar rvf ${EOS_HOME}/distribute/src.$(OSTYPE).tar src/$(WORLDNAME)/$(CLASSNAME)/.[A-z]*
	@for dir in ${SOURCE} ; \
	do \
		$(CD) $${dir}; make distribute-all; $(CD) ..; \
	done

