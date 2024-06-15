include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/DefineTool.inc

LIBFILES   = \
			$(LIBPREFIX)EosObjects$(LIBSUFFIX) 

LIBFILESDEBUG   = \
			$(LIBPREFIX)EosObjects.debug$(LIBSUFFIX) 

SRCC  = \
			$(OBJECTNAME).c \
			init.c \
			argCheck.c \
			usage.c  \
			util.c 

SRCCXX  = \
			$(OBJECTNAME).cc \
			init.cc \
			argCheck.cc \
			usage.cc  \
			util.cc 

MODULES    = \
			$(OBJECTNAME).o \
			init.o \
			argCheck.o \
			usage.o  \
			util.o 

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
			util.debugo 

REALMODULESDEBUG    = \
			$(OSTYPE)/$(OBJECTNAME).debugo \
			$(OSTYPE)/init.debugo \
			$(OSTYPE)/argCheck.debugo \
			$(OSTYPE)/usage.debugo \
			$(OSTYPE)/util.debugo 


$(OBJECTNAME): $(MODULES) $(LIBFILES)
	@if [ -f ../$(OBJECTNAME).c ] ; \
	then \
		echo $(CC) $(CCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@ ;  \
		$(CC) $(CCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@ ;  \
	fi
	@if [ -f ../$(OBJECTNAME).cc ] ; \
	then \
		echo $(CXX) $(CCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
		$(CXX) $(CCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
	fi
	@if [ -f ../$(OBJECTNAME).ccm ] ; \
	then \
		echo "MICO"; \
		echo $(MICOLD) $(CCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
		$(MICOLD) $(CCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
	fi


$(OBJECTNAME).debug: $(MODULESDEBUG) $(LIBFILESDEBUG)
	@if [ -f ../$(OBJECTNAME).c ] ; \
	then \
		echo $(CC) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@ ;  \
		$(CC) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@ ;  \
	fi
	@if [ -f ../$(OBJECTNAME).cc ] ; \
	then \
		echo $(CXX) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
		$(CXX) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
	fi
	@if [ -f ../$(OBJECTNAME).ccm ] ; \
	then \
		echo "MICO"; \
		echo $(MICOLD) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
		$(MICOLD) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
	fi


include ./.Depend
include ../../Config/Target.inc
