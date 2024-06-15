KARCH_DEFINE = -DKARCH_PARISC
KOPSYS_DEFINE = -DKOPSYS_HPUX
EOS_PATH = /users/Eos
EOS_LIBDIR = /users/Eos/lib
EOS_BINDIR = /users/Eos/bin
BOOTSTRAP_PATH = /users/khoros/bootstrap
BOOTSTRAP_LIBDIR = /usr/local/khoros210/lib
BOOTSTRAP_BINDIR = /usr/local/khoros210/bin
DATASERV_PATH = /users/khoros/dataserv
DATASERV_LIBDIR = /usr/local/khoros210/lib
DATASERV_BINDIR = /usr/local/khoros210/bin
DESIGN_PATH = /users/khoros/design
DESIGN_LIBDIR = /usr/local/khoros210/lib
DESIGN_BINDIR = /usr/local/khoros210/bin
TB_NAME = $(EOS_PATH)
TOOLBOX_PATH = /users/Eos
SHELL = /bin/sh
ARCH = Architecture
MAKE = make
MV = mv -f
SED = sed
YACC = yacc
YFLAGS = -d
LEX = lex
LFLAGS = -n
LINT = lint
INSTALL = $(SCRIPTSRC)/bsdinst.sh
LIBLD = ld
RM = rm -f
TAGS = ctags
KGENMAKE = kgenmake
DEPEND = kgendepend
KGENIMAKE = kgenimake
BASENAME = /bin/basename
SCRIPTSRC = $(BOOTSTRAP_PATH)/repos/config/scripts
FORTRANSCRIPT = $(SCRIPTSRC)/fortran.sh
GHOSTWRITER = ghostwriter
CONDUCTOR = conductor
KGENSTRUCT = kgenstruct
KLINT = klint
PROTOIZEFLAGS = -fstrength-reduce -fpcc-struct-return -fwritable-strings -ansi
KLD_RUN_PATH = $(EOS_LIBDIR):$(DESIGN_LIBDIR):$(DATASERV_LIBDIR):$(BOOTSTRAP_LIBDIR):$${LD_RUN_PATH+$$LD_RUN_PATH}
OBJECTINCLUDE = $(TOOLBOX_INCLUDE)
OBJECTLIBDIR = $(TOOLBOX_LIBDIR)
OBJECTDEFINES = $(TOOLBOX_DEFINES)
ALLINCLUDES = $(OBJECTINCLUDE) $(EXTRA_INCLUDES) $(STD_INCLUDES)
ALLDEFINES = $(ALLINCLUDES) $(KARCH_DEFINE) $(KOPSYS_DEFINE) $(OBJECTDEFINES) $(LOCALDEFINES) $(DEFINES)
LINTFLAGS = $(ALLDEFINES) $(ALLINCLUDES)
RM_CMD = $(RM) *.o core *.a tags ,* *~ *.i *.u *.B *.G *.T *.s .emacs_* tags TAGS .pure
MAKEFILE_CMD = $(KGENMAKE) $(IMAKE_DEFINES)
SYS_LIBRARIES = -lBSD -lmalloc -lm -ll -lcl
X_LIBRARIES = -lXaw -lXmu -lXt -lXext -lX11
ALLLIBDIRS = $(EXTRALIBDIR)
OBJS = $(YOBJS) $(LOBJS) $(COBJS) $(FOBJS) $(C++OBJS)
SRCS = $(YSRCS) $(LSRCS) $(CSRCS) $(FSRCS) $(C++SRCS)
TOOLBOX_INCLUDE = -I$(EOS_PATH)/include \
 		-I$(DESIGN_PATH)/include \
 		-I$(DATASERV_PATH)/include \
 		-I$(BOOTSTRAP_PATH)/include
TOOLBOX_LIBDIR = -L$(EOS_LIBDIR) \
 		-L$(DESIGN_LIBDIR) \
 		-L$(DATASERV_LIBDIR) \
 		-L$(BOOTSTRAP_LIBDIR)
C_TOOLBOX_LIBRARIES = -lkapu \
 		-lkaps \
 		-lkdms \
 		-lkdac \
 		-lkfmt \
 		-lkgen \
 		-lkcms \
 		-lkclui \
 		-lkvf \
 		-lkexpr \
 		-lklibdb \
 		-lklm \
 		-lku
C_TOOLBOX_DEP_LIBRARIES = $(DATASERV_LIBDIR)/libkapu.a \
 		$(DATASERV_LIBDIR)/libkaps.a \
 		$(DATASERV_LIBDIR)/libkdms.a \
 		$(DATASERV_LIBDIR)/libkdac.a \
 		$(DATASERV_LIBDIR)/libkfmt.a \
 		$(BOOTSTRAP_LIBDIR)/libkgen.a \
 		$(BOOTSTRAP_LIBDIR)/libkcms.a \
 		$(BOOTSTRAP_LIBDIR)/libkclui.a \
 		$(BOOTSTRAP_LIBDIR)/libkvf.a \
 		$(BOOTSTRAP_LIBDIR)/libkexpr.a \
 		$(BOOTSTRAP_LIBDIR)/libklibdb.a \
 		$(BOOTSTRAP_LIBDIR)/libklm.a \
 		$(BOOTSTRAP_LIBDIR)/libku.a
X_TOOLBOX_LIBRARIES = -lxvl \
 		-lxvf \
 		-lxvu \
 		-lxvs \
 		-lxvg \
 		-lxva \
 		-lxvobj \
 		-lkwid \
 		-lxvw
X_TOOLBOX_DEP_LIBRARIES = $(DESIGN_LIBDIR)/libxvl.a \
 		$(DESIGN_LIBDIR)/libxvf.a \
 		$(DESIGN_LIBDIR)/libxvu.a \
 		$(DESIGN_LIBDIR)/libxvs.a \
 		$(DESIGN_LIBDIR)/libxvg.a \
 		$(DESIGN_LIBDIR)/libxva.a \
 		$(DESIGN_LIBDIR)/libxvobj.a \
 		$(DESIGN_LIBDIR)/libkwid.a \
 		$(DESIGN_LIBDIR)/libxvw.a
BINDIR = $(EOS_BINDIR)
LIBDIR = $(EOS_LIBDIR)
OBJECT_TYPE = script
TOOLBOX_NAME = eos
OBJECT_NAME = mrcImageModeChange
BINARY_NAME = mrcImageModeChange
SCRIPTS = mrcImageModeChange.ksh
INSTSCRIPTFLAGS = -m 0755
Makefiles:
Imakefiles:
GenImakefiles:
purecov:
install-purecov:
purify:
install-purify:
quantify:
install-quantify:
gendepend::
	       @true
depend::
	       @true
all:
sbrowser:
help:
RCSco:
	co -l $(SRCS) $(HEADERS) $(SCRIPTS)
RCSci:
	@if [ ! -d RCS ]; then mkdir RCS; fi;     ci $(SRCS) $(HEADERS) $(SCRIPTS)
tags::
	$(TAGS) -w *.[chfylCF] > tags
spotless: clean uninstall cleanout
klint::
	-$(KLINT) -tb $(TOOLBOX_NAME) -oname $(OBJECT_NAME)
install:: $(SCRIPTS)
	-@for i in $(SCRIPTS); do     ($(INSTALL) -c $(INSTPGMFLAGS) $(INSTSCRIPTFLAGS) $$i $(BINDIR)/`$(BASENAME) $$i .ksh`;    echo "installing $$i in $(BINDIR)");    done
uninstall::
	-@for i in $(SCRIPTS); do     ($(RM) $(BINDIR)/`$(BASENAME) $$i .ksh`;    echo "removing `$(BASENAME) $$i .ksh` from $(BINDIR)");    done
struct::
	-@start=0;     for i in `echo "$(XSRCS) none"`; do     if [ "$$i" != "none" ]; then     echo "Running kgenstruct on $$i";     $(KGENSTRUCT) -x $$i;     start=1;     else     if [ "$$start" = "0" ]; then     echo "No *.x files";     fi;     fi;     done
clui::
	$(GHOSTWRITER) -force
gw::
	$(GHOSTWRITER) -force
clean::
	$(RM_CMD) \#*
cleanout::
	$(RM_CMD) Makefile
Makefile::
	$(MAKEFILE_CMD)
Imakefile::
	$(KGENIMAKE) -tb $(TOOLBOX_NAME)
GenImakefile::
	$(KGENIMAKE) -tb $(TOOLBOX_NAME) -recreate
