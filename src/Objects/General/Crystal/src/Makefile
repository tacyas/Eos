SHELL=/bin/ksh
include ../Config/Define.inc
include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc

include $(OSTYPE)/.Source
include .CHeader
include .CCHeader
include .Wish
include .Ruby

LIBNAME=lib$(OBJECTNAME).a
SHAREDLIB=lib$(OBJECTNAME).so
LIBNAMEDEBUG=lib$(OBJECTNAME).debug.a

DSTDIR=$(EOS_HOME)/lib/$(OSTYPE)/
SOURCE=$(OSTYPE)/.Source
ARCHTEMPLATEDIR=$(EOS_HOME)/src/Config/Template/$(WORLDNAME)Template.Dir/src/ARCH

all: hostdepend static-lib shared-lib ruby-lib debug
	@echo LIBNAME:$(LIBNAME)
	@echo OBJECTNAME:$(OBJECTNAME)

hostdepend:
	@if [ ! -L $(OSTYPE) ] ; then  \
		moveHostdependent ; \
	fi

debug: debug-lib

static-lib::
	@echo static-lib:LIBNAME:$(LIBNAME) ; \
	$(RM) -f $(OSTYPE)/Makefile; \
	$(CP) $(ARCHTEMPLATEDIR)/Makefile $(OSTYPE)/Makefile ; \
	cd $(OSTYPE); \
	$(MAKE) $(LIBNAME) CLASSNAME=$(CLASSNAME) OBJECTNAME=$(OBJECTNAME) WORLDNAME=$(WORLDNAME) 

shared-lib::
	@echo shared-lib:LIBNAME:$(LIBNAME) ; \
	$(RM) -f $(OSTYPE)/Makefile;  \
	$(CP) $(ARCHTEMPLATEDIR)/Makefile $(OSTYPE)/Makefile ; \
	cd  $(OSTYPE); \
	$(MAKE) $(SHAREDLIB) CLASSNAME=$(CLASSNAME) OBJECTNAME=$(OBJECTNAME) WORLDNAME=$(WORLDNAME) 

ruby-lib::
	@if [ -d Swig ]; then \
		echo "--- Swig ---"; \
		cd Swig; \
		if [ -f extconf.rb ] ; then \
			swig -ruby -I/usr/include -I$(EOS_HOME)/include *.i ; \
			ruby extconf.rb --with-Eos-include=$(EOS_HOME)/include --with-Eos-lib=$(EOS_HOME)/lib/$(OSTYPE) --with-opt-lib=$LD_LIBRARY_PATH --with-opt-lib=$(EOS_HOME)/util/$(OSTYPE)/lib --with-GL-lib=/usr/lib ; \
			make ; \
			make sitearchdir=$(EOS_HOME)/lib/$(OSTYPE) install; \
		fi ; \
	fi  

debug-lib::
	@cd $(OSTYPE); \
	$(RM) -f Makefile; \
	$(CP) $(ARCHTEMPLATEDIR)/Makefile Makefile ; \
	$(MAKE) $(LIBNAMEDEBUG) CLASSNAME=$(CLASSNAME) OBJECTNAME=$(OBJECTNAME) WORLDNAME=$(WORLDNAME) 

clean: 
	rm -f *.[oa] *.debugo *.cudagdbo *.so *.sharedo *.linkinfo $(OSTYPE)/*.[ao] $(OSTYPE)/*.debugo $(OSTYPE)/*.cudagdbo $(OSTYPE)/*.linkinfo *.bak core $(OSTYPE)/*.sharedo $(OSTYPE)/*.so

Makefile:
	touch .Source
	touch .CHeader
	touch .CCHeader

install: all install-static install-shared install-ascii 
	@echo "Installation has completed: $(LIBNAME)" 

install-static: $(DSTDIR)/$(LIBNAME)
install-shared: $(DSTDIR)/$(SHAREDLIB)

install-debug: debug $(DSTDIR)/$(LIBNAMEDEBUG) install-ascii 
	@echo "Installation has completed: $(LIBNAMEDEBUG)" 

install-ascii: h hh wish ruby 

h:
	@if [ -n "$(CHeader)" ] ; \
	then\
		echo "C Header Install" ; \
		for file in $(CHeader) dummy ; \
		do \
			if [ -f $${file} ] ; \
			then\
				echo $${file}; $(INSTALL) -m 444 $${file} $(EOS_HOME)/include ; \
			fi;\
		done; \
	fi

hh:
	@if [ -n "$(CCHeader)" ] ; \
	then \
		echo "C++ Header Install" ; \
		for file in $(CCHeader) dummy ; \
		do \
			if [ -f $${file} ] ; \
			then\
				echo $${file}; $(INSTALL) -m 444 $${file} $(EOS_HOME)/include ; \
			fi;\
		done; \
	fi

wish:
	@if [ -n "$(Wish)" ] ; \
	then \
		echo "Wish Install" ; \
		for file in $(Wish) dummy ; \
		do \
			if [ -f $${file} ] ; \
			then\
				echo $${file}; $(INSTALL) -m 444 $${file} $(EOS_HOME)/lib ; \
			fi;\
		done; \
	fi

ruby:
	@if [ -n "$(Ruby)" ] ; \
	then \
		echo "Ruby Install" ; \
		for file in $(Ruby) dummy ; \
		do \
			if [ -f $${file} ] ; \
			then\
				echo $${file}; $(INSTALL) -m 444 $${file} $(EOS_HOME)/lib ; \
			fi;\
		done; \
	fi

put:
	@Files=`ls -l | grep $${USER} | grep rw | grep -e "\.c" ` ;\
	for file in $${Files} dummy; \
	do \
		if [ -w $${file} ] ; \
		then\
			echo $${file}; sccsPut $${file} ; \
		fi;\
	done

$(DSTDIR)/$(LIBNAME): static-lib
	@echo Installing lib: $(LIBNAME)
	@if [ ! -d $(DSTDIR) ] ; then mkdir $(DSTDIR) ; fi
	@cd $(OSTYPE); $(INSTALL) -m 444 $(LIBNAME) ../$(DSTDIR)
	@echo LIBNAME:$(LIBNAME)
	@echo Link EosObjects
	@OBJLIST=`ls $(OSTYPE)/*.o `;\
	echo $${OBJLIST} | sed -f ../../../../Config/o2nl.sed > .tmp1 ; \
	echo $(REALOBJ)  | sed -f ../../../../Config/o2nl.sed > .tmp2 ; \
	echo "#### Attention Uncompiled file ####";\
	comm -13 .tmp1 .tmp2 ; \
	echo "########";\
	echo $(AR) r $(DSTDIR)/libEosObjects.a $${OBJLIST} ; \
	$(AR) r $(DSTDIR)/libEosObjects.a $${OBJLIST}; \
	echo $(AR) s $(DSTDIR)/libEosObjects.a ; \
	$(AR) s $(DSTDIR)/libEosObjects.a \
	chmod 660 $(DSTDIR)/libEosObjects.a
	@rm .tmp1 .tmp2

$(DSTDIR)/$(LIBNAMEDEBUG): debug 
	@echo Installing lib: $(LIBNAMEDEBUG)
	@if [ ! -d $(DSTDIR) ] ; then mkdir $(DSTDIR) ; fi
	@cd $(OSTYPE); $(INSTALL) -m 444 $(LIBNAMEDEBUG) $(DSTDIR)
	@echo LIBNAME:$(LIBNAMEDEBUG)
	@echo Link EosObjects
	@OBJLISTDEBUG=`ls $(OSTYPE)/*.debugo `;\
	echo $${OBJLISTDEBUG} | sed -f ../../../../Config/o2nl.sed > .tmp1 ; \
	echo $(REALOBJDEBUG)  | sed -f ../../../../Config/o2nl.sed > .tmp2 ; \
	echo "#### Attention Uncompiled file ####";\
	comm -13 .tmp1 .tmp2 ; \
	echo "########";\
	echo $(AR) r $(DSTDIR)/libEosObjects.debug.a $${OBJLISTDEBUG} ; \
	$(AR) r $(DSTDIR)/libEosObjects.debug.a $${OBJLISTDEBUG}; 
	echo $(AR) s $(DSTDIR)/libEosObjects.debug.a ; \
	$(AR) s $(DSTDIR)/libEosObjects.debug.a 
	chmod 660 $(DSTDIR)/libEosObjects.debug.a
	@rm .tmp1 .tmp2

$(DSTDIR)/$(SHAREDLIB): shared-lib
	@echo Installing lib: $(SHAREDLIB)
	@if [ ! -d $(DSTDIR) ] ; then mkdir $(DSTDIR) ; fi
	@cd $(OSTYPE); $(INSTALL) -m 444 $(SHAREDLIB) $(DSTDIR)
	@echo LIBNAME:$(SHAREDLIB)
	@echo Link EosObjects
	@OBJLIST=`ls $(OSTYPE)/*.sharedo `;\
	echo $${OBJLIST} | sed -f ../../../../Config/o2nl.sed > .tmp1 ; \
	echo $(REALSHAREDOBJ)  | sed -f ../../../../Config/o2nl.sed > .tmp2 ; \
	echo "#### Attention Uncompiled file ####";\
	comm -13 .tmp1 .tmp2 ; \
	echo "########"; \
	if [ ! -d  $(DSTDIR)/shared ] ; then \
		mkdir $(DSTDIR)/shared; \
	fi; \
	$(CP) $${OBJLIST} $(DSTDIR)/shared ; \
	echo "$(CP) $${OBJLIST} $(DSTDIR)/shared" ; \
	$(SHARED) $(DSTDIR)/libEosObjects.so $(DSTDIR)/shared/*.sharedo ; \
	echo "$(SHARED) $(DSTDIR)/libEosObjects.so $(DSTDIR)/shared/*.sharedo" ; \
	chmod 660 $(DSTDIR)/libEosObjects.so
	@rm .tmp1 .tmp2

install-all: 
	@cd ..  ; $(MAKE) install

install-ruby: ruby-lib
	cd $(OSTYPE); $(RUBY) -r ftools -e 'File::install(ARGV[0], ARGV[1], 0555, true)' $(SHAREDLIB) $(RUBYSHAREDLIB)/$(SHAREDLIB)	

depend:
	@echo dependency checking now 
	@echo $(OSTYPE)
	@echo SRC = \\ > $(SOURCE) 
	@ls -1 *.c  | sed -e "s/\.c/.c \\\\/"   >> $(SOURCE)
	@ls -1 *.cc | sed -e "s/\.cc/.cc \\\\/" >> $(SOURCE)
	@ls -1 *.ccm | sed -e "s/\.ccm/.ccm \\\\/" >> $(SOURCE)
	@ls -1 *.idl | sed -e "s/\.idl/.idl \\\\/" >> $(SOURCE)
	@ls -1 *.cu | sed -e "s/\.cu/.cu \\\\/" >> $(SOURCE)
	@echo >> $(SOURCE)
	@#
	@echo OBJ = \\ >> $(SOURCE)
	@ls -1 *.c   | sed -e "s/\.c/.o \\\\/"    >> $(SOURCE)
	@ls -1 *.cc  | sed -e "s/\.cc/.o  \\\\/"  >> $(SOURCE)
	@ls -1 *.ccm  | sed -e "s/\.ccm/.o  \\\\/"  >> $(SOURCE)
	@ls -1 *.idl | sed -e "s/\.idl/.o  \\\\/" >> $(SOURCE)
	@ls -1 *.cu  | sed -e "s/\.cu/.o  \\\\/"  >> $(SOURCE)
	@echo >> $(SOURCE)
	@#
	@echo SHAREDOBJ = \\ >> $(SOURCE)
	@ls -1 *.c   | sed -e "s/\.c/.sharedo \\\\/"    >> $(SOURCE)
	@ls -1 *.cc  | sed -e "s/\.cc/.sharedo  \\\\/"  >> $(SOURCE)
	@ls -1 *.ccm  | sed -e "s/\.ccm/.sharedo  \\\\/"  >> $(SOURCE)
	@ls -1 *.idl | sed -e "s/\.idl/.sharedo  \\\\/" >> $(SOURCE)
	@ls -1 *.cu  | sed -e "s/\.cu/.sharedo  \\\\/"  >> $(SOURCE)
	@echo >> $(SOURCE)
	@#
	@echo REALOBJ = \\ >> $(SOURCE)
	@ls -1 *.c   | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.c/.o \\\\/"  >> $(SOURCE)
	@ls -1 *.cc  | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.cc/.o \\\\/" >> $(SOURCE)
	@ls -1 *.ccm  | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.ccm/.o \\\\/" >> $(SOURCE)
	@ls -1 *.idl | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.idl/.o \\\\/" >> $(SOURCE)
	@ls -1 *.cu  | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.cu/.o \\\\/" >> $(SOURCE)
	@echo >> $(SOURCE) 
	@echo REALSHAREDOBJ = \\ >> $(SOURCE)
	@ls -1 *.c   | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.c/.sharedo \\\\/"  >> $(SOURCE)
	@ls -1 *.cc  | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.cc/.sharedo \\\\/" >> $(SOURCE)
	@ls -1 *.ccm  | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.ccm/.sharedo \\\\/" >> $(SOURCE)
	@ls -1 *.idl | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.idl/.sharedo \\\\/" >> $(SOURCE)
	@ls -1 *.cu  | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.cu/.sharedo \\\\/" >> $(SOURCE)
	@echo >> $(SOURCE) 
	@echo OBJDEBUG = \\ >> $(SOURCE)
	@ls -1 *.c   | sed -e "s/\.c/.debugo \\\\/"    >> $(SOURCE)
	@ls -1 *.cc  | sed -e "s/\.cc/.debugo  \\\\/"  >> $(SOURCE)
	@ls -1 *.ccm  | sed -e "s/\.ccm/.debugo  \\\\/"  >> $(SOURCE)
	@ls -1 *.idl | sed -e "s/\.idl/.debugo  \\\\/" >> $(SOURCE)
	@echo >> $(SOURCE)
	@#
	@echo REALOBJDEBUG = \\ >> $(SOURCE)
	@ls -1 *.c   | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.c/.debugo \\\\/"  >> $(SOURCE)
	@ls -1 *.cc  | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.cc/.debugo \\\\/" >> $(SOURCE)
	@ls -1 *.ccm  | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.ccm/.debugo \\\\/" >> $(SOURCE)
	@ls -1 *.idl | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.idl/.debugo \\\\/" >> $(SOURCE)
	@ls -1 *.cu  | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.cu/.debugo \\\\/" >> $(SOURCE)
	@echo >> $(SOURCE) 
	@echo OBJCUDAGDB = \\ >> $(SOURCE)
	@ls -1 *.c   | sed -e "s/\.c/.cudagdb.o \\\\/"    >> $(SOURCE)
	@ls -1 *.cc  | sed -e "s/\.cc/.cudagdb.o  \\\\/"  >> $(SOURCE)
	@ls -1 *.cu  | sed -e "s/\.cu/.cudagdb.o  \\\\/"  >> $(SOURCE)
	@echo >> $(SOURCE)
	@#
	@echo REALOBJCUDAGDB = \\ >> $(SOURCE)
	@ls -1 *.c   | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.c/.cudagdb.o \\\\/"  >> $(SOURCE)
	@ls -1 *.cc  | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.cc/.cudagdb.o \\\\/" >> $(SOURCE)
	@ls -1 *.cu  | sed -e "s/^/\$(OSTYPE)\//" -e "s/\.cu/.cudagdb.o \\\\/" >> $(SOURCE)
	@echo >> $(SOURCE) 
	@#
	@echo >> $(SOURCE)
	@echo CCHeader = \\ > .CCHeader
	@ls -1 *.hh | sed -e "s/\.hh/.hh \\\\/" >> .CCHeader
	@echo >> .CCHeader
	@#
	@echo CHeader = \\ > .CHeader
	@ls -1 *.h | sed -e "s/\.h/.h \\\\/" >> .CHeader
	@echo >> .CHeader
	@#
	@echo Wish = \\ > .Wish
	@ls -1 *.wish | sed -e "s/\.wish/.wish \\\\/" >> .Wish
	@echo >> .Wish
	@#
	@echo Ruby = \\ > .Ruby
	@ls -1 *.rb | sed -e "s/\.rb/.rb \\\\/" >> .Ruby
	@echo >> .Ruby
	@#
	@ls -1 *.c *.cc *.ccm | \
	awk -vHostType=$(OSTYPE) -f$(EOS_HOME)/sbin/awk/objectdependency.awk > $(OSTYPE)/.Depend
	@#
	@$(DEPENDCOMMAND) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_DEFINE) $(KHOROS_INCS) *.c *.cc *.ccm >> $(OSTYPE)/.Depend
	@for file in $(SRC) dummy ; \
	do  \
		if [ -f $${file} ] ; \
		then \
			echo $${file} ; \
			ln -sf ../$${file} $(OSTYPE)/$${file}; \
		fi ;\
	done

#
#
#
test::
	@if [ -d test ] ; then \
		cd test; \
		$(MAKE); \
	else \
		echo "No test directory: making test"; \
		mkdir test; \
		cd test; \
		touch Makefile; \
	fi

#
# cvs
#
cvsupdate::
	cvs -d $(EOS_CVSROOT) update -d 

cvslogin::
	cvs -d $(EOS_CVSROOT) login 

cvscommit::
	@echo "cvs -d $(EOS_CVSROOT) commit -m @"message@" filename"

cvsadd::
	@echo "cvs -d $(EOS_CVSROOT) add  filename|dirname"
	@echo "Need Commit for filename"
	@echo "make cvscommit"

cvsremove::
	@echo "cvs -d $(EOS_CVSROOT) remove filename"
	@echo "Need Commit for filename"
	@echo "make cvscommit" 

include $(OSTYPE)/.Depend
include ../Config/Target.inc
