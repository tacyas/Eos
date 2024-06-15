include ../Config/Define.inc
include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc

EOSHOME=../../../../../
DSTDIR=$(EOSHOME)/bin
DSTDOC=$(EOSHOME)/doc
DSTTAR=$(EOSHOME)/tar

INCFILES   = 

LIBFILES   = \
			$(LIBPREFIX)EosObjects$(LIBSUFFIX) 

LIBFILESDEBUG   = \
			$(LIBPREFIX)EosObjects.debug$(LIBSUFFIX) 

SRCC  = \
			$(OBJECTNAME).c \
			init.c \
			argCheck.c \
			usage.c  \
			util.c \

SRCCXX  = \
			$(OBJECTNAME).cc \
			init.cc \
			argCheck.cc \
			usage.cc  \
			util.cc \

MODULES    = \
			$(OBJECTNAME).o \
			init.o \
			argCheck.o \
			usage.o  \
			util.o \

REALMODULES    = \
			$(OSTYPE)/$(OBJECTNAME).o \
			$(OSTYPE)/init.o \
			$(OSTYPE)/argCheck.o \
			$(OSTYPE)/usage.o \
			$(OSTYPE)/util.o 

MODULESDEBUG    = \
			$(OBJECTNAME).debugo \
			init.debugo \
			argCheck.debugo \
			usage.debugo  \
			util.debugo \

REALMODULESDEBUG    = \
			$(OSTYPE)/$(OBJECTNAME).debugo \
			$(OSTYPE)/init.debugo \
			$(OSTYPE)/argCheck.debugo \
			$(OSTYPE)/usage.debugo \
			$(OSTYPE)/util.debugo 

all: $(OSTYPE)/$(OBJECTNAME)

debug: $(OSTYPE)/$(OBJECTNAME).debug

$(OSTYPE)/$(OBJECTNAME)::
	@cd $(OSTYPE); \
	$(RM) -f Makefile ; \
	$(CP) ../../../../../Config/Template/$(WORLDNAME)Template.Dir/src/ARCH/Makefile Makefile ; \
	$(MAKE) $(OBJECTNAME)

$(OSTYPE)/$(OBJECTNAME).debug::
	cd $(OSTYPE); \
	$(RM) -f Makefile ; \
	$(CP) ../../../../../Config/Template/$(WORLDNAME)Template.Dir/src/ARCH/Makefile Makefile ; \
	$(MAKE) $(OBJECTNAME).debug

cvsupdate::
	cvs -d $(EOS_CVSROOT) update -d	

cvscommit::
	cvs -d $(EOS_CVSROOT) commit 

edit:
	@if [ -r $(OBJECTNAME).c ]; \
	then \
		sccsEdit $(OBJECTNAME).c; \
	else \
		echo "Source files are already editable"; \
	fi
	@if [ -r wish/$(OBJECTNAME).wish ]; \
	then \
		cd wish; sccsEdit $(OBJECTNAME).wish; \
	else \
		echo "Source files (wish) are already editable."; \
	fi
	@if [ -r ruby/$(OBJECTNAME).rb ]; \
	then \
		cd ruby; sccsEdit $(OBJECTNAME).rb; \
	else \
		echo "Source files (ruby) are already editable."; \
	fi
	@if [ -r perl/$(OBJECTNAME).pl ]; \
	then \
		cd perl; sccsEdit $(OBJECTNAME).pl ; \
	else \
		echo "Source files (perl) are already editable."; \
	fi
	@if [ -r ../Config/OptionControlFile ]; \
	then \
		cd ../Config; sccsEdit OptionControlFile; \
	else \
		echo "OptionControlFile are already editable."; \
	fi
	
unedit:
	@if [ -w $(OBJECTNAME).c ]; \
	then \
		sccsUnedit $(OBJECTNAME).c; \
	else \
		echo "Source files are not editable"; \
	fi
	@if [ -w wish/$(OBJECTNAME).wish ]; \
	then \
		cd wish; sccsUnedit $(OBJECTNAME).wish; \
	else \
		echo "Source files (wish) are not editable."; \
	fi
	@if [ -w ruby/$(OBJECTNAME).rb]; \
	then \
		cd ruby; sccsUnedit $(OBJECTNAME).rb; \
	else \
		echo "Source files (ruby) are not editable."; \
	fi
	@if [ -w perl/$(OBJECTNAME).pl ]; \
	then \
		cd perl; sccsUnedit $(OBJECTNAME).pl ; \
	else \
		echo "Source files (ruby) are not editable."; \
	fi
	@if [ -w ../Config/OptionControlFile ]; \
	then \
		cd ../Config; sccsUnedit OptionControlFile; \
	else \
		echo "OptionControlFile are not editable."; \
	fi
	
report:
	@if [ -r $(OBJECTNAME).c ]; \
	then \
		sccsReport $(OBJECTNAME).c; \
	else \
		echo "Source files are already editable"; \
	fi
	@if [ -r wish/$(OBJECTNAME).wish ]; \
	then \
		cd wish; sccsReport $(OBJECTNAME).wish; \
	else \
		echo "Source files (wish) are already editable."; \
	fi
	@if [ -r ruby/$(OBJECTNAME).rb ]; \
	then \
		cd ruby; sccsReport $(OBJECTNAME).rb; \
	else \
		echo "Source files (ruby) are already editable."; \
	fi
	@if [ -r perl/$(OBJECTNAME).pl ] ; \
	then \
		cd perl; sccsReport $(OBJECTNAME).pl ; \
	else \
		echo "Source files (perl) are already editable."; \
	fi
	@if [ -r ../Config/OptionControlFile ]; \
	then \
		cd ../Config; sccsReport OptionControlFile; \
	else \
		echo "OptionControlFile are already editable."; \
	fi

clean : 
	rm -f *.debugo $(OSTYPE)/*.debugo *.o $(OSTYPE)/*.o \
		$(OSTYPE)/$(OBJECTNAME) $(OSTYPE)/*.$(OSTYPE) \
		$(OSTYPE)/$(OBJECTNAME).debug $(OSTYPE)/*.$(OSTYPE).debug \
		*.bak *.$(OSTYPE) core

install: install-bin install-doc install-wish install-ruby install-shell install-perl
	@if [ dummy$(KHOROS_KENGOBJ) != dummy ]  ; \
	then \
		if [ -x $(KHOROS_KGENOBJ) ] ;  \
		then \
			make install-khoros ; \
		fi; \
	fi 

install-bin:$(DSTDIR)/$(OSTYPE)/$(OBJECTNAME) 

$(DSTDIR)/$(OSTYPE)/$(OBJECTNAME):$(OSTYPE)/$(OBJECTNAME) $(DSTDIR)/$(OBJECTNAME) 
	@echo ---- Installing to bin
	@if [ ! -d $(DSTDIR)/$(OSTYPE) ]; \
	then \
		mkdir $(DSTDIR)/$(OSTYPE); \
	fi
	@if [ -x $(DSTDIR)/$(OSTYPE)/$(OBJECTNAME) ]; \
	then \
		$(RM) -f $(DSTDIR)/$(OSTYPE)/$(OBJECTNAME); \
	fi
	@$(CD) $(OSTYPE); $(INSTALL) -m 555 $(OBJECTNAME) ../$(DSTDIR)/$(OSTYPE)
	@$(CHMOD) 555 $(DSTDIR)/$(OSTYPE)/$(OBJECTNAME)
	@$(CHGRP) Eos $(DSTDIR)/$(OSTYPE)/$(OBJECTNAME)
	@echo $(DSTDIR)/$(OSTYPE)/$(OBJECTNAME)
	@echo ---- end of bin

install-wish:
	@if [ -d wish ]; \
	then \
		echo "---- Tcl/Tk file Install"; \
		if [ ! -d $(DSTDIR)/wish/$(OBJECTNAME) ]; \
		then \
			mkdir $(DSTDIR)/wish/$(OBJECTNAME) ; \
		fi ; \
		$(CP) -f wish/* $(DSTDIR)/wish/$(OBJECTNAME); \
		$(CHMOD) 555 $(DSTDIR)/wish/$(OBJECTNAME)/*  ;\
		touch $(DSTDIR)/wish/$(OBJECTNAME)/tclIndex;\
		$(CHMOD) 666 $(DSTDIR)/wish/$(OBJECTNAME)/tclIndex;\
		$(CHGRP) Eos $(DSTDIR)/wish/$(OBJECTNAME)/*;\
		echo "---- Tcl/Tk file Installed";\
	fi

install-ruby:
	@if [ -d ruby ]; \
	then \
		echo "---- Ruby/Tk file Install"; \
		if [ ! -d $(DSTDIR)/ruby/$(OBJECTNAME) ]; \
		then \
			mkdir $(DSTDIR)/ruby/$(OBJECTNAME) ; \
		fi ; \
		$(CP) -f ruby/* $(DSTDIR)/ruby/$(OBJECTNAME); \
		$(CHMOD) 555 $(DSTDIR)/ruby/$(OBJECTNAME)/* ; \
		$(CHGRP) Eos $(DSTDIR)/ruby/$(OBJECTNAME)/* ; \
		echo "---- Ruby/Tk file Installed"; \
	fi

install-perl:
	@if [ -d perl ]; \
	then \
		echo "---- Perl/Tk file Install"; \
		if [ ! -d $(DSTDIR)/perl/$(OBJECTNAME) ]; \
		then \
			mkdir $(DSTDIR)/perl/$(OBJECTNAME) ; \
		fi; \
		$(CP) -f perl/* $(DSTDIR)/perl/$(OBJECTNAME); \
		$(CHMOD) 555 $(DSTDIR)/perl/$(OBJECTNAME)/* ; \
		$(CHGRP) Eos $(DSTDIR)/perl/$(OBJECTNAME)/* ; \
		echo "---- Perl/Tk file Installed"; \
	fi

install-shell:
	@if [ ! -d $(DSTDIR)/shell/$(OBJECTNAME) ]; \
	then \
		mkdir $(DSTDIR)/shell/$(OBJECTNAME) ; \
	fi
	@if [ -d shell ]; \
	then \
		echo "---- Shell file Install"; \
		if [ ! -d $(DSTDIR)/shell/$(OBJECTNAME) ]; \
		then \
			mkdir $(DSTDIR)/shell/$(OBJECTNAME) ; \
		fi ; \
		$(CP) -f shell/* $(DSTDIR)/shell/$(OBJECTNAME); \
		$(CHMOD) 555 $(DSTDIR)/shell/$(OBJECTNAME)/*; \
		$(CHGRP) Eos $(DSTDIR)/shell/$(OBJECTNAME)/*; \
		echo "---- Shell file Installed"; \
	fi

install-khoros:
	@echo Installing to khoros
	@if [ ! -d ../../../../../objects/script/$(OBJECTNAME) -a -f $(KHOROS_KGENOBJ) ]; \
	then \
		echo kgenobj;\
		$(KHOROS_KGENOBJ) -tb Eos -oname $(OBJECTNAME) -type script -pane -cantata true -cat Eos -subcat $(CLASSNAME) -description $(OBJECTNAME) -bname $(OBJECTNAME) -form  -lang ksh ; \
	fi
	@if [ ! -d ../../../../../objects/script/$(OBJECTNAME) -a -f $(KHOROS_KSET) ]; \
	then \
		$(KHOROS_KSET) -tb Eos -oname $(OBJECTNAME) -icon $(OBJECTNAME) ; \
	fi
	@if [ -d ../../../../../objects/script/$(OBJECTNAME) -a -f $(KHOROS_KSET) ]; \
	then \
		$(CHMOD) -R 775 ../../../../../objects/script/$(OBJECTNAME) ; \
		if [ $?  ] ; \
		then \
			echo "-- setting khoros ---" ; \
			if [ -d ../../../../../objects/script/$(OBJECTNAME)/uis/ ] ; \
			then \
				$(CD) ../../../../../objects/script/$(OBJECTNAME)/uis/ ; \
				$(RM) -f $(OBJECTNAME).pane ; \
				$(LN) -s ../../../../src/Tools/$(CLASSNAME)/$(OBJECTNAME)/src/$(OBJECTNAME).pane $(OBJECTNAME).pane; \
				$(CD) ../../ ; \
				$(CHGRP) -R Eos $(OBJECTNAME); \
				$(CHMOD) -R 555 $(OBJECTNAME); \
			else \
				echo "../../../../../objects/script/$(OBJECTNAME)/uis/ does not exist."; \
			fi ; \
		else \
			echo "Failed !!: Cannot chage mode in installing  $(OBJECTNAME) to khoros system"; \
		fi ; \
		echo "-- end of khoros-installing"; \
	fi

install-doc: html 
	@if [ ! -d $(DSTDOC)/SmallTools ]; \
	then \
		mkdir $(DSTDOC)/SmallTools ;\
	fi
	@if [ -f $(DSTDOC)/SmallTools/$(OBJECTNAME).html ]; \
	then \
		$(RM) -f $(DSTDOC)/SmallTools/$(OBJECTNAME).html ;\
	fi
	@$(CP) $(OBJECTNAME).html  $(DSTDOC)/SmallTools/$(OBJECTNAME).html
	@$(CHMOD) 444 $(DSTDOC)/SmallTools/$(OBJECTNAME).html
	@if [ -f ../doc/*.html ]; \
	then \
		$(CP) ../doc/*.html  $(DSTDOC)/SmallTools/ ;\
	fi
	@$(CHMOD) 444 $(DSTDOC)/SmallTools/$(OBJECTNAME).html
	@if [ -f $(DSTDOC)/SmallTools/Makefile ]; \
	then \
		cd $(DSTDOC)/SmallTools; $(MAKE); \
	fi

html: $(OBJECTNAME).html

configFileRead:
	@ctrl2configFileRead $(CLASSNAME) $(OBJECTNAME) ../Config/OptionControlFile

$(OBJECTNAME).html: $(OSTYPE)/$(OBJECTNAME)
	@echo creating html
	@$(OSTYPE)/$(OBJECTNAME) -html 2> $(OBJECTNAME).html.tmp
	@sed -e s/$(OSTYPE)\\/// $(OBJECTNAME).html.tmp > $(OBJECTNAME).html
	@$(RM) $(OBJECTNAME).html.tmp

$(DSTDIR)/$(OBJECTNAME): $(OSTYPE)/$(OBJECTNAME)
	@ln -s -f ../sbin/MachineIndependent $@

depend::
	@echo dependency checking now
	@if [ ! -d $(OSTYPE) ] ; \
	then \
		mkdir $(OSTYPE); \
	else \
		rm -f $(OSTYPE)/.Depend	; \
	fi
	#echo C
	@if [ -f $(OBJECTNAME).c ] ; \
	then \
		echo "dependency: *.c"; \
		echo $(DEPENDCOMMAND) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_DEFINE) *.c   ; \
		     $(DEPENDCOMMAND) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_DEFINE) *.c   > $(OSTYPE)/.Depend ; \
	fi
	#echo CC
	@if [ -f $(OBJECTNAME).cc ] ; \
	then \
		echo "dependency: *.cc"; \
		echo $(DEPENDCOMMAND) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_DEFINE) $(EXTRA_CCOPTS) *.cc ; \
		     $(DEPENDCOMMAND) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_DEFINE) $(EXTRA_CCOPTS) *.cc >> $(OSTYPE)/.Depend ; \
	fi
	@if [ -f $(OBJECTNAME).ccm ] ; \
	then \
		echo "dependency: *.ccm"; \
		echo $(DEPENDCOMMAND) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_DEFINE) $(EXTRA_CCOPTS) *.ccm ; \
		     $(DEPENDCOMMAND) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_DEFINE) $(EXTRA_CCOPTS) *.ccm >> $(OSTYPE)/.Depend ; \
	fi

update:../Config/OptionControlFile
	maketool $(CLASSNAME) $(OBJECTNAME) update

changeName::

Test:$(OSTYPE)/$(OBJECTNAME) TestDir
	@if [ -f test/Makefile ] ; \
	then \
		cd test; make ; \
	else \
		echo "No test Makefile"; \
	fi

TestDir::
	@if [ ! -d test ] ; \
	then \
		echo "Creating test dir"; \
		mkdir  test; \
	fi
	@if [ ! -f test/Makefile ] ; \
	then \
		echo "Creating Makefile"; \
		cd test; \
		protoTestMakefileCreate; \
	fi
	@if [ ! -d test/data ]; \
	then \
		mkdir $(EOSHOME)/data/$(OBJECTNAME); \
		cd test; \
		ln -sf ../$(EOSHOME)/data/$(OBJECTNAME) data; \
	fi 

tar::
	cd $(DSTTAR); tar cvf Tools.$(CLASSNAME).$(OBJECTNAME).tar ../bin/$(OBJECTNAME) \
	                                                     ../bin/*/$(OBJECTNAME).* \
	                                                     ../src/Tools/$(CLASSNAME)/$(OBJECTNAME) \
				; gzip Tools.$(CLASSNAME).$(OBJECTNAME).tar

include $(OSTYPE)/.Depend
include ../Config/Target.inc
