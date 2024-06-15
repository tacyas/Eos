include ../../../../Config/Define.inc
include ../../../Config/Define.inc
include ../../Config/Define.inc
include ../Config/Define.inc

SOURCEDOC  = $(OBJECTNAME).html
DOCDSTDIR  = $(EOS_HOME)/doc/Objects
TARGETDOC  = $(DOCDSTDIR)/$(SOURCEDOC)

all: $(SOURCEDOC)

install : $(TARGETDOC) 

$(TARGETDOC):$(SOURCEDOC)
	$(INSTALL) -m 444 *.html $(DOCDSTDIR)
	@cd $(DOCDSTDIR); make

$(SOURCEDOC) : .$(SOURCEDOC) .header .footer ../inc/$(OBJECTNAME).h Makefile ../src/*.c
	@echo Creating $(OBJECTNAME).html
	@cat .header	 			 > $(SOURCEDOC)
	@#htmlUpdateTime 			>> $(SOURCEDOC)
	@cat .$(SOURCEDOC) 			>> $(SOURCEDOC)
	@echo \<HR\>  				>> $(SOURCEDOC)
	@echo "<A NAME=\"Information\">" >> $(SOURCEDOC)
	@echo "<H2>Information from source codes</H2>" >> $(SOURCEDOC)
	@echo "</A>"               >> $(SOURCEDOC)
	@echo "<PRE>"               >> $(SOURCEDOC)
	-@ident ../src/*.c  			>> $(SOURCEDOC)
	@echo "</PRE>"              >> $(SOURCEDOC)
	@echo \<HR\>  				>> $(SOURCEDOC)
	@echo \<A NAME=\"include\"\>>> $(SOURCEDOC)
	@echo "<H2>$(OBJECTNAME).h</H2>">> $(SOURCEDOC)
	@echo \</A\>				>>$(SOURCEDOC)
	@echo \<PRE\> 				>> $(SOURCEDOC)
	@cat ../inc/$(OBJECTNAME).h >> $(SOURCEDOC)
	@echo \</PRE\>				>> $(SOURCEDOC) 
	@cat .footer				>> $(SOURCEDOC)

clean:

depend:
