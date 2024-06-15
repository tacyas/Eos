include $(EOS_HOME)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Config/Define.inc
include $(EOS_HOME)/src/$(WORLDNAME)/$(CLASSNAME)/Config/Define.inc
include $(EOS_HOME)/src/$(WORLDNAME)/Config/Define.inc
include $(EOS_HOME)/src/Config/DefineTool.inc

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

MODULESCUDAGDB    = \
			$(OBJECTNAME).cudagdb.o \
			init.cudagdb.o \
			argCheck.cudagdb.o \
			usage.cudagdb.o  \
			util.cudagdb.o 

REALMODULESDEBUG    = \
			$(OSTYPE)/$(OBJECTNAME).debugo \
			$(OSTYPE)/init.debugo \
			$(OSTYPE)/argCheck.debugo \
			$(OSTYPE)/usage.debugo \
			$(OSTYPE)/util.debugo 


$(OBJECTNAME): $(MODULES) $(LIBFILES)
	@if [ -f $(VPATH)/$(OBJECTNAME).c ] ; \
	then \
		echo $(CC) $(CCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@ ;  \
		$(CC) $(CCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@ ;  \
	fi
	@if [ -f $(VPATH)/$(OBJECTNAME).cc ] ; \
	then \
		echo $(CXX) $(CCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
		$(CXX) $(CCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
	fi
	@if [ -f $(VPATH)/$(OBJECTNAME).ccm ] ; \
	then \
		echo "MICO"; \
		echo $(MICOLD) $(CCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
		$(MICOLD) $(CCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
	fi
	@if [ -f $(VPATH)/$(OBJECTNAME).cu ] ; \
	then \
		echo $(NVCC) $(NVCCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) $(CUDALIB) $(CUDAINC) -o $@ ;  \
		$(NVCC) $(NVCCOPTS) $(MODULES) $(LIBFILES) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) $(CUDALIB) $(CUDAINC) -o $@ ;  \
	fi


$(OBJECTNAME).debug: $(MODULESDEBUG) $(LIBFILESDEBUG)
	@if [ -f $(VPATH)/$(OBJECTNAME).c ] ; \
	then \
		echo $(CC) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@ ;  \
		$(CC) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@ ;  \
	fi
	@if [ -f $(VPATH)/$(OBJECTNAME).cc ] ; \
	then \
		echo $(CXX) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
		$(CXX) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
	fi
	@if [ -f $(VPATH)/$(OBJECTNAME).ccm ] ; \
	then \
		echo "MICO"; \
		echo $(MICOLD) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
		$(MICOLD) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@  ; \
	fi
	@if [ -f $(VPATH)/$(OBJECTNAME).cu ] ; \
	then \
		echo $(CC) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@ ;  \
		$(CC) $(CCOPTSDEBUG) $(MODULESDEBUG) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@ ;  \
	fi

$(OBJECTNAME).cudagdb: $(MODULESCUDAGDB) $(LIBFILESDEBUG)
	echo $(NVCC) "$(NVCCOPTSCUDAGDB) $(MODULESCUDAGDB) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@"
	$(NVCC) $(NVCCOPTSCUDAGDB) $(MODULESCUDAGDB) $(LIBFILESDEBUG) $(EXTRA_LIB) $(KHOROS_LIBS) $(LIBPVM) $(STANDARDLIB) $(HOSTDEPENDENTLIB) -o $@

include ./.Depend
include  $(EOS_HOME)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Config/Target.inc
