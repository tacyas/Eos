include ../../../../Config/Define.inc
include ../../../Config/Define.inc
include ../../Config/Define.inc
include ../Config/Define.inc

INCFILE = $(OBJECTNAME).h

all: 

install:$(EOS_HOME)/include/$(INCFILE)

$(EOS_HOME)/include/$(INCFILE):$(INCFILE)
	$(INSTALL) -m 444 $(INCFILE) $(EOS_HOME)/include/

clean:
	$(RM) -f *.bak

