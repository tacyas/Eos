SHELL=/bin/ksh
include $(EOS_HOME)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/Config/Define.inc
include $(EOS_HOME)/src/$(WORLDNAME)/$(CLASSNAME)/Config/Define.inc
include $(EOS_HOME)/src/$(WORLDNAME)/Config/Define.inc
include $(EOS_HOME)/src/Config/DefineObject.inc

include .Source
include $(EOS_HOME)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/.CHeader
include $(EOS_HOME)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/.CCHeader
include $(EOS_HOME)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src/.Wish

LIBNAME=lib$(OBJECTNAME).a
SHAREDLIB=lib$(OBJECTNAME).so
LIBNAMEDEBUG=lib$(OBJECTNAME).debug.a
LIBNAMECUDAGDB=lib$(OBJECTNAME).cudagdb.a

$(LIBNAME): $(OBJ)
	@echo LIBNAME:$(LIBNAME)
	$(AR) rs $(LIBNAME) $(OBJ)

$(SHAREDLIB): $(SHAREDOBJ)
	@COMPILEDOBJ=`ls $(SHAREDOBJ)` ; echo "#### Compiled Objects"; echo $${COMPILEDOBJ};  echo "################"; \
	COMMAND="$(SHARED) $(SHAREDLIB) $${COMPILEDOBJ}" ; echo $${COMMAND}; $${COMMAND} 

debug: $(LIBNAMEDEBUG) $(LIBNAMECUDAGDB)

$(LIBNAMEDEBUG): $(OBJDEBUG)
	@echo LIBNAME:$(LIBNAMEDEBUG)
	$(AR) rs $(LIBNAMEDEBUG) $(OBJDEBUG)

$(LIBNAMECUDAGDB): $(OBJCUDAGDB)
	@echo LIBNAME:$(LIBNAMECUDAGDB)
	$(AR) rs $(LIBNAMECUDAGDB) $(OBJCUDAGDB)

include .Depend

