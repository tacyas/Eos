SHELL=/bin/ksh
include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/DefineObject.inc

include .Source
include ../.CHeader
include ../.CCHeader
include ../.Wish

LIBNAME=lib$(OBJECTNAME).a
SHAREDLIB=lib$(OBJECTNAME).so
LIBNAMEDEBUG=lib$(OBJECTNAME).debug.a

$(LIBNAME): $(OBJ)
	@echo LIBNAME:$(LIBNAME)
	$(AR) rs $(LIBNAME) $(OBJ)

$(SHAREDLIB): $(OBJ)
	@COMPILEDOBJ=`ls $(OBJ)` ; echo "#### Compiled Objects"; echo $${COMPILEDOBJ};  echo "################"; \
	$(SHARED) $(SHAREDLIB) $${COMPILEDOBJ} 

$(LIBNAMEDEBUG): $(OBJDEBUG)
	@echo LIBNAME:$(LIBNAMEDEBUG)
	$(AR) rs $(LIBNAMEDEBUG) $(OBJDEBUG)

include .Depend

