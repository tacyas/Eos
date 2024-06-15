.SUFFIXES: .debugo .ccm .idl .cu .cudagdbo .sharedo 
.IGNORE:
include ${EOS_HOME}/src/Config/${EOS_HOST}${FLAG_ICC}.inc

TOP     = ${EOS_HOME}
VPATH = $(EOS_HOME)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src

INCLUDEDIR = -I$(VPATH)/inc -I$(TOP)/include 

LIBDIR    = ${TOP}/lib
LIBPREFIX = ${LIBDIR}/lib
LIBSUFFIX = .$(OSTYPE).a

STANDARDLIB = 

.c.o:
	$(RM) -rf $*.o
	$(CC) -c $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(VPATH)/$*.c -o $*.o 

.cc.o:
	$(RM) -rf $*.o
	$(CXX) -c $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(VPATH)/$*.cc -o $*.o 

.c.sharedo:
	$(RM) -rf $*.sharedo
	$(SHAREDCC) -c $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(VPATH)/$*.c -o $*.sharedo 

.cc.sharedo:
	$(RM) -rf $*.sharedo
	$(SHAREDCXX) -c $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(VPATH)/$*.cc -o $*.sharedo 

.c.debugo:
	$(RM) -rf $*.debugo
	$(CC) -c $(CCOPTSDEBUG) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(VPATH)/$*.c -o $*.debugo 

.cc.debugo:
	$(RM) -rf $*.debugo
	$(CXX) -c $(CCOPTSDEBUG) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(VPATH)/$*.cc -o $*.debugo 


.idl.o:
	$(IDL) $(VPATH)/$*.idl
	mv $*.cc $(VPATH)/$*.ccm
	mv $*.h  $(VPATH)/$*.h

.ccm.o:
	cp  $(VPATH)/$*.ccm $(VPATH)/$*.cc
	$(MICOCC)  -c $(VPATH)/$*.cc -o $*.o $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(INCMICO)
	rm $(VPATH)/$*.cc

.ccm.debugo:
	cp  $(VPATH)/$*.ccm $(VPATH)/$*.cc
	$(MICOCC)  -c $(VPATH)/$*.cc -o $*.debugo $(CCOPTSDEBUG) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(INCMICO)
	rm $(VPATH)/$*.cc

#CUDA
.cu.o:
	$(RM) -rf $*.o
	$(NVCC) -c $(NVCCOPTS) $(VPATH)/$*.cu -o $*.o $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(NVCCOPTS) $(INCCUDA)

.cu.sharedo:
	$(RM) -rf $*.sharedo
	$(NVCC) -Xcompiler -fPIC -c $(NVCCOPTS) $(VPATH)/$*.cu -o $*.sharedo $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(NVCCOPTS) $(INCCUDA)
	
.cu.debugo:
	$(NVCC) -c $(NVCCOPTS) $(VPATH)/$*.cu -o $*.debugo $(INCLUDEDIR) $(EXTRA_INC) $(DEFPVM) $(INCPVM) $(KHOROS_INCS) $(NVCCOPTSDEBUG) $(INCCUDA)

	
%.cudagdb.o : %.cu
	$(NVCC) -c $< -o $@ $(INCLUDEDIR) $(EXTRA_INC) $(DEFPVM) $(INCPVM) $(KHOROS_INCS) $(NVCCOPTSCUDAGDB) $(INCCUDA)

%.cudagdb.o : %.c
	$(CP) $< $(VPATH)/$*.cu
	$(NVCC) -c  $(VPATH)/$*.cu -o $@ $(INCLUDEDIR) $(EXTRA_INC) $(DEFPVM) $(INCPVM) $(KHOROS_INCS) $(NVCCOPTSCUDAGDB) $(INCCUDA)
	$(RM) $(VPATH)/$*.cu
	
%.cudagdb.o : %.cc
	$(CP) $< $(VPATH)/$*.cu
	$(NVCC) -c $(VPATH)/$*.cu -o $@ $(INCLUDEDIR) $(EXTRA_INC) $(DEFPVM) $(INCPVM) $(KHOROS_INCS) $(NVCCOPTSCUDAGDB) $(INCCUDA)
	$(RM) $(VPATH)/$*.cu

