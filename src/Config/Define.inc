.SUFFIXES: .idl .ccm .debugo .cu .cudagdbo .sharedo
.IGNORE:

SHELL=/bin/bash

include ${EOS_HOME}/src/Config/${EOS_HOST}${FLAG_ICC}.inc

TOP     = ${EOS_HOME}
CVSROOT = ${EOS_CVSROOT} 

INCLUDEDIR = -I../inc -I${TOP}/include 

LIBDIR    = ${TOP}/lib/$(OSTYPE)
LIBPREFIX = ${LIBDIR}/lib
LIBSUFFIX = .a

STANDARDLIB = 
VPATH = ../

.c.o:
	@if [ ! -d $(OSTYPE) ]; \
	then \
		mkdir $(OSTYPE); \
	fi
	@echo $(CC) -c $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $*.c -o $(OSTYPE)/$*.o 
	@if $(CC) -c $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $*.c -o $(OSTYPE)/$*.o ; \
	then \
		touch $*.o ;\
		touch $(OSTYPE)/$*.o ;\
	else \
		rm -f $*.o ;\
		rm -f $(OSTYPE)/$*.o ;\
	fi	


.c.debugo:
	@if [ ! -d $(OSTYPE) ]; \
	then \
		mkdir $(OSTYPE); \
	fi
	@echo $(CC) -c $(CCOPTSDEBUG) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $*.c -o $(OSTYPE)/$*.debug.o 
	@if $(CC) -c $(CCOPTSDEBUG) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $*.c -o $(OSTYPE)/$*.debug.o ; \
	then \
		touch $*.debug.o ;\
		touch $(OSTYPE)/$*.debugo ;\
	else \
		rm -f $*.o ;\
		rm -f $(OSTYPE)/$*.debugo ;\
	fi	

.cc.o:
	@if [ ! -d $(OSTYPE) ]; \
	then \
		mkdir $(OSTYPE); \
	fi
	@echo $(CXX) -c -I../ $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $*.cc -o $(OSTYPE)/$*.o
	@if $(CXX) -c $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $*.cc -o $(OSTYPE)/$*.o ; \
	then \
		touch $*.o ;\
		touch $(OSTYPE)/$*.o;\
	else \
		rm -f $*.o ;\
		rm -f $(OSTYPE)/$*.o ;\
	fi

.cc.debugo:
	@if [ ! -d $(OSTYPE) ]; \
	then \
		mkdir $(OSTYPE); \
	fi
	@echo $(CXX) -c -I../ $(CCOPTSDEBUG) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $*.cc -o $(OSTYPE)/$*.debugo
	@if $(CXX) -c $(CCOPTSDEBUG) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $*.cc -o $(OSTYPE)/$*.debugo ; \
	then \
		touch $*.debugo ;\
		touch $(OSTYPE)/$*.debugo;\
	else \
		rm -f $*.debugo ;\
		rm -f $(OSTYPE)/$*.debugo ;\
	fi

.idl.ccm:
	$(IDL) $*.idl 
	mv $*.cc $*.ccm

.ccm.o:
	cp $*.ccm $*.cc
	$(MICOCC)  -c $*.cc -o $(OSTYPE)/$*.o $(CCOPTS) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(INCMICO)
	rm $*.cc

.ccm.debugo:
	cp $*.ccm $*.cc
	$(MICOCC)  -c $*.cc -o $(OSTYPE)/$*.o $(CCOPTSDEBUG) $(INCLUDEDIR) $(EXTRA_INC) $(EXTRA_CCOPTS) $(KHOROS_OPTIONS) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(INCMICO)
	rm $*.cc

#CUDA
.cu.o:
	@if [ ! -d $(OSTYPE) ]; \
	then \
		mkdir $(OSTYPE); \
	fi
	@echo $(NVCC)  -c $*.cu -o $(OSTYPE)/$*.o $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(NVCCOPTS) $(INCCUDA)
	@if $(NVCC)  -c $*.cu -o $(OSTYPE)/$*.o $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM)  $(NVCCOPTS) $(INCCUDA) ; \
	then \
		touch $*.o ;\
		touch $(OSTYPE)/$*.o ;\
	else \
		rm -f $*.o ;\
		rm -f $(OSTYPE)/$*.o ;\
	fi	

.cu.debugo:
	@if [ ! -d $(OSTYPE) ]; \
	then \
		mkdir $(OSTYPE); \
	fi
	@echo $(NVCC)  -c $*.cu -o $(OSTYPE)/$*.debugo $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(NVCCOPTSGDB) $(INCCUDA)
	@if $(NVCC)  -c $*.cu -o $(OSTYPE)/$*.debugo $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM)  $(NVCCOPTSGDB) $(INCCUDA) ; \
	then \
		touch $*.debugo ;\
		touch $(OSTYPE)/$*.debugo ;\
	else \
		rm -f $*.debugo ;\
		rm -f $(OSTYPE)/$*.debugo ;\
	fi	


%.cudagdb.o : %.cu
	@if [ ! -d $(OSTYPE) ]; \
	then \
		mkdir $(OSTYPE); \
	fi
	@echo $(NVCC)  -c $< -o $(OSTYPE)/$@ $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(NVCCOPTSCUDAGDB) $(INCCUDA)
	@if $(NVCC)  -c $< -o $(OSTYPE)/$@ $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM)  $(NVCCOPTSCUDAGDB) $(INCCUDA) ; \
	then \
		touch $@ ;\
		touch $(OSTYPE)/$@ ;\
	else \
		rm -f $@ ;\
		rm -f $(OSTYPE)/$@ ;\
	fi	

%.cudagdb.o : %.c
	@if [ ! -d $(OSTYPE) ]; \
	then \
		mkdir $(OSTYPE); \
	fi
	$(CP) $< ../$*.cu
	@echo $(NVCC)  -c ../$*.cu -o $(OSTYPE)/$@ $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(NVCCOPTSCUDAGDB) $(INCCUDA)
	@if $(NVCC)  -c ../$*.cu -o $(OSTYPE)/$@ $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM)  $(NVCCOPTSCUDAGDB) $(INCCUDA) ; \
	then \
		touch $@ ;\
		touch $(OSTYPE)/$@ ;\
	else \
		rm -f $@ ;\
		rm -f $(OSTYPE)/$@ ;\
	fi	
	$(RM) -f ../$*.cu

%.cudagdb.o : %.cc
	@if [ ! -d $(OSTYPE) ]; \
	then \
		mkdir $(OSTYPE); \
	fi
	$(CP) $< ../$*.cu
	@echo $(NVCC)  -c ../$*.cu -o $(OSTYPE)/$@ $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM) $(NVCCOPTSCUDAGDB) $(INCCUDA)
	@if $(NVCC)  -c ../$*.cu -o $(OSTYPE)/$@ $(INCLUDEDIR) $(EXTRA_INC) $(KHOROS_INCS) $(DEFPVM) $(INCPVM)  $(NVCCOPTSCUDAGDB) $(INCCUDA) ; \
	then \
		touch $@ ;\
		touch $(OSTYPE)/$@ ;\
	else \
		rm -f $@ ;\
		rm -f $(OSTYPE)/$@ ;\
	fi	
	$(RM) -f ../$*.cu

