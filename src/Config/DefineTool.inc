.SUFFIXES: .debugo .ccm .idl .cu .cudagdbo
.IGNORE:
include ${EOS_HOME}/src/Config/${EOS_HOST}${FLAG_ICC}.inc

TOP     = ${EOS_HOME}
VPATH = $(EOS_HOME)/src/$(WORLDNAME)/$(CLASSNAME)/$(OBJECTNAME)/src

INCLUDEDIR = -I$(VPATH)/../inc -I${TOP}/include 

LIBDIR    = ${TOP}/lib/$(OSTYPE)
LIBPREFIX = ${LIBDIR}/lib
LIBSUFFIX = .a

STANDARDLIB = 

.c.o:
	$(CC) -c $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(DEFPVM) $(INCPVM) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(VPATH)/$*.c -o $*.o  

.cc.o:
	$(CXX) -c $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(DEFPVM) $(INCPVM) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(VPATH)/$*.cc -o $*.o 

.c.debugo:
	$(CC) -c $(CCOPTSDEBUG) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(DEFPVM) $(INCPVM) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(VPATH)/$*.c -o $*.debugo  

.cc.debugo:
	$(CXX) -c $(CCOPTSDEBUG) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(DEFPVM) $(INCPVM) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(VPATH)/$*.cc -o $*.debugo 


.idl.ccm:
	$(IDL) $(VPATH)/$*.idl 
	mv $(VPATH)/$*.cc $(VPATH)/$*.ccm

.ccm.o:
	cp  $(VPATH)/$*.ccm $(VPATH)/$*.cc 
	$(MICOCC)  -c $(VPATH)/$*.cc -o $*.o $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(INCMICO)
	rm ../$*.cc

	
.ccm.debugo:
	cp  $(VPATH)/$*.ccm $(VPATH)/$*.cc 
	$(MICOCC)  -c $(VPATH)/$*.cc -o $*.debugo $(CCOPTSDEBUG) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(INCMICO)
	rm ../$*.cc

	
#CUDA
.cu.o:
	$(RM) -rf $*.o
	$(NVCC)  -c $(VPATH)/$*.cu -o $*.o $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(NVCCOPTS) $(INCCUDA)

	
.cu.debugo:
	$(NVCC) -c  $(VPATH)/$*.cu -o $*.debugo $(INCLUDEDIR) $(EXTRA_INC) $(DEFPVM) $(INCPVM) $(KHOROS_INCS) $(NVCCOPTSGDB) $(INCCUDA)

	
%.cudagdb.o : %.cu
	$(NVCC) -c  $< -o $@ $(INCLUDEDIR) $(EXTRA_INC) $(DEFPVM) $(INCPVM) $(KHOROS_INCS) $(NVCCOPTSCUDAGDB) $(INCCUDA)

	
%.cudagdb.o : %.c
	$(CP) $< $(VPATH)/$*.cu
	$(NVCC) -c  $(VPATH)/$*.cu -o $@ $(INCLUDEDIR) $(EXTRA_INC) $(DEFPVM) $(INCPVM) $(KHOROS_INCS) $(NVCCOPTSCUDAGDB) $(INCCUDA)
	$(RM) $(VPATH)/$*.cu

	
%.cudagdb.o : $.cc
	$(CP) $< $(VPATH)/$*.cu
	$(NVCC) -c  $(VPATH)/$*.cu -o $@ $(INCLUDEDIR) $(EXTRA_INC) $(DEFPVM) $(INCPVM) $(KHOROS_INCS) $(NVCCOPTSCUDAGDB) $(INCCUDA)
	$(RM) $(VPATH)/$*.cu

