include ../../../../Config/Define.inc
include ../../../Config/Define.inc
include ../../Config/Define.inc
include ../Config/Define.inc

INCFILE = $(OBJECTNAME).h

all: 

install:$(EOS_HOME)/include/$(INCFILE)

$(EOS_HOME)/include/$(INCFILE):$(INCFILE)
	if [ ! -d  $(EOS_HOME)/include ] ; then \
		mkdir $(EOS_HOME)/include ; \
	fi
	$(INSTALL) -m 444 $(INCFILE) $(EOS_HOME)/include/

clean:
	$(RM) -f *.bak

depend:
	$(RM) -f *.bak	

cvsupdate::
	cvs -d $(EOS_CVSROOT) update 

cvscommit::
	@echo "cvs -d $(EOS_CVSROOT) commit"  

cvsadd::
	@echo "cvs -d $(EOS_CVSROOT) add"  
