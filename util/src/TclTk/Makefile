include ../../Config/Define.inc
include ../../Config/Target.inc

UTILS=Tcl Tk BLT VTK

SHELL=/bin/ksh

include ${EOS_HOME}/src/Config/${EOS_HOST}.inc

### TCL
TCLVERSION=8.6.12
TCLNAME=tcl$(TCLVERSION)
TCLWHERE=http://sourceforge.net/projects/tcl/files/Tcl/$(TCLVERSION)/$(TCLNAME)-src.tar.gz/download
#TCLVERSION=8.5.18
#TCLNAME=tcl$(TCLVERSION)
#TCLWHERE=http://sourceforge.net/projects/tcl/files/Tcl/8.5.18/tcl8518-src.zip/download

### TK 
TKVERSION=8.6.12
TKNAME=tk$(TCLVERSION)
TKWHERE=http://sourceforge.net/projects/tcl/files/Tcl/$(TKVERSION)/$(TKNAME)-src.tar.gz/download
#TKVERSION=8.5.18
#TKNAME=tk$(TCLVERSION)
#TKWHERE=http://sourceforge.net/projects/tcl/files/Tcl/8.5.18/tk8518-src.zip/download

### TCLLIB
TCLLIBVERSION=1.17
TCLLIBNAME=tcllib-$(TCLLIBVERSION)
TCLLIBWHERE=http://sourceforge.net/projects/tcllib/files/tcllib/$(TCLLIBVERSION/$(TCLLIBNAME).zip/download 

### BLT
BLTVERSION=2.5.3
#BLTVERSION=3.2.23
#BLTNAME=blt-src-$(BLTVERSION)
BLTNAME=blt-src-$(BLTVERSION)
BLTNAMEDIR=blt2.5
#BLTNAMEDIR=wjoye-tkblt-2c9ea39
BLTWHERE=http://sourceforge.net/projects/wize/files/$(BLTNAME).zip/download
#BLTWHERE=https://sourceforge.net/projects/tkblt/files/V$(BLTVERSION)/V$(BLTVERSION).tar.gz

### VTK
#VTKVERSION1=Nighty
#VTKVERSION=5.4.2
#VTKVERSION=6.2.0
VTKVERSION=6.3.0
VTKNAME=VTK-$(VTKVERSION)
VTKWHERE=http://www.vtk.org/files/release/6.3/
#VTKWHERE=http://www.vtk.org/files/release/6.2/

help::
	@echo "make tcl"
	@echo "make tk"
	@echo "make BLT"

tcl::
	make TclCheck
	make TclConfig
	make TclAll

tk::
	make TkCheck
	make TkConfig
	make TkAll

blt:
	make BLTCheck
	make BLTConfig
	make BLTAll

vtk:
	make VTKCheck
	make VTKConfig
	make VTKAll

TclCheck::
	#@ln -s ../../src/TclTk/tcl$(TCLVERSION)-src.tar.gz .
	#@gzip -dc tcl$(TCLVERSION)-src.tar.gz | tar xvf - 
	#curl -L $(TCLWHERE) > $(TCLNAME)-src.zip
	#unzip $(TCLNAME)-src.zip
	curl -L $(TCLWHERE) > $(TCLNAME)-src.tar.gz
	tar xvzf  $(TCLNAME)-src.tar.gz

TkCheck::
	#@ln -s ../../src/TclTk/tk$(TKVERSION)-src.tar.gz .
	#@gzip -dc tk$(TKVERSION)-src.tar.gz | tar xvf - 
	curl -L $(TKWHERE) > $(TKNAME)-src.tar.gz
	tar xvzf $(TKNAME)-src.tar.gz

TkImgCheck::
	@ln -s ../../src/TclTk/tkimg$(TKIMGVERSION).tar.gz .
	@gzip -dc tkimg$(TKIMGVERSION)tar.gz | tar xvf - 

BLTCheck::
	#@ln -s ../../src/TclTk/BLT$(BLTVERSION).tar.gz .
	#@gzip -dc BLT$(BLTVERSION).tar.gz | tar xvf - 
	curl -L $(BLTWHERE) > $(BLTNAME).tar.gz
	tar xvzf $(BLTNAME).tar.gz

TcllibCheck::
	curl -L $(TCLLIBWHERE) > $(TCLLIBNAME).zip
	unzip $(TCLLIBNAME).zip

VTKCheck::
	#@ln -s ../../src/TclTk/vtk$(VTKVERSION)-src-unix.tgz .
	#@gzip -dc vtk$(VTKVERSION)-src-unix.tgz | tar xvf - 
	#@ln -s ../../src/TclTk/vtk$(VTKVERSION1)Src.tar.gz .
	#@gzip -dc vtk$(VTKVERSION1)Src.tar.gz | tar xvf - 
	#@ln -s ../../src/TclTk/vtk-$(VTKVERSION).tar.gz .
	#@gzip -dc vtk-$(VTKVERSION).tar.gz | tar xvf - 
	#curl -O $(VTKWHERE)/$(VTKNAME).tar.gz
	#tar xvzf $(VTKNAME).tar.gz
	curl -O $(VTKWHERE)/$(VTKNAME).zip
	unzip $(VTKNAME).zip

TclConfig::
	cd tcl$(TCLVERSION)/unix ; \
	./configure --prefix=${EOS_HOME}/util/$(OSTYPE) \
			    --enable-shared --enable-threads --enable-symbols
	#./configure --prefix=${EOS_HOME}/util/$(OSTYPE) \
	#		    --enable-shared --enable-symbol \
	#			--enable-threads

TkConfig::
	cd tk$(TKVERSION)/unix  ; \
	./configure --prefix=${EOS_HOME}/util/$(OSTYPE) \
				--with-tcl=../../tcl$(TCLVERSION)/unix \
				--with-libtiff --enable-symbol --enable-shared --enable-symbols \
				--with-x --x-libraries=/opt/X11/lib --x-includes=/opt/X11/include --with-gnu-ld

TkImgConfig::
	cd tkimg$(TKIMGVERSION)  ; \ $(MAKE) clean; \
	./configure --prefix=${EOS_HOME}/util/$(OSTYPE) \
				--with-tcl=${EOS_HOME}/util/src$(OSTYPE)/TclTk/tcl$(TCLVERSION)/unix \
				--with-tk=${EOS_HOME}/util/src$(OSTYPE)/TclTk/tk$(TKVERSION)/unix  \

BLTConfig::
	#cd $(BLTNAMEDIR); ./configure --prefix=${EOS_HOME}/util/$(OSTYPE) \
				--with-tcl=${EOS_HOME}/util/$(OSTYPE)  \
				--with-tk=${EOS_HOME}/util/$(OSTYPE) \
				--enable-jpeg=${EOS_HOME}/util/$(OSTYPE) \
				--enable-shared \
				--with-cflags="-DUSE_INTERP_ERRORLINE -DUSE_INTERP_RESULT -DSIZEOF_VOID_P=8" \
				--with-x --x-libraries=/opt/X11/lib --x-includes=/opt/X11/include --with-gnu-ld
	cd $(BLTNAMEDIR) ; ./configure --prefix=${EOS_HOME}/util/$(OSTYPE) \
				--with-tcl=../tcl$(TCLVERSION)/unix \
				--with-tk=../tk$(TKVERSION)/unix  \
				--enable-jpeg=${EOS_HOME}/util/$(OSTYPE) \
				--enable-shared \
				--with-cflags="-DUSE_INTERP_ERRORLINE -DUSE_INTERP_RESULT" \
				--with-x --x-libraries=/opt/X11/lib --x-includes=/opt/X11/include --with-gnu-ld

TcllibConfig::
	@cd $(TCLLIBNAME); \
	$(MAKE) clean ; \
	./configure --prefix=${EOS_HOME}/util/$(OSTYPE) \
				--with-tcl=../tcl$(TCLVERSION)/unix \
				--with-tk=../tk$(TKVERSION)/unix  \
				--enable-jpeg=${EOS_HOME}/util/$(OSTYPE) \
				--enable-shared \
				--with-x --with-gnu-ld

VTKConfig::
	cd $(VTKNAME); \
	ccmake .
	#cd vtk$(VTKVERSION); \
	#$(MAKE) clean ; \ #if [ $(OSTYPE) = "SGI" ] ; \ #then \ #	echo "Using GL" ; \ #	./configure --prefix=${EOS_HOME}/util/$(OSTYPE) \ #			--with-tcl=../tcl$(TCLVERSION)/unix \ #			--with-tk=../tk$(TKVERSION)/unix  \ #			--with-tkwidget  \ #			--with-x ; \ #else \
	#	echo "Using MESA" ; \
	#	./configure --prefix=${EOS_HOME}/util/$(OSTYPE) \
	#			--with-tcl \
	#			--with-tkwidget \
	#			--without-gl \
	#			--with-mesa \
	#			--without-python \
	#			--with-graphics \
	#			--with-imaging \
	#			--with-patented  \
	#			--with-x ; \
	#	echo "TCL_INCLUDE=-I${EOS_HOME}/util/$(OSTYPE)/include"     >> user.make ; \
	#	echo "TCL_LIB=${EOS_HOME}/util/$(OSTYPE)/lib/libtcl8.3.a "  >> user.make ; \
	#	echo "TK_INCLUDE=-I${EOS_HOME}/util/$(OSTYPE)/include"      >> user.make ; \
	#	echo "TK_LIB=${EOS_HOME}/util/$(OSTYPE)/lib/libtk8.3.a "    >> user.make ; \
	#	echo "MESA_INCLUDE=-I${EOS_HOME}/util/$(OSTYPE)/include"    >> user.make ; \
	#	echo "MESA_LIB=${EOS_HOME}/util/$(OSTYPE)/lib/libMesaGL.a " >> user.make  ; \
	#fi 

TclAll::
	@cd tcl$(TCLVERSION)/unix ; \
	$(MAKE) install	

TkAll::
	@cd tk$(TKVERSION)/unix  ; \
	CPPFLAGS="-DUSE_INTERP_ERRORLINE -DUSE_INTERP_RESULT" $(MAKE) install

TkImg::
	@cd tkimg$(TKIMGVERSION)/; \
	$(MAKE) install


BLTAll::
	@cd $(BLTNAMEDIR); \
	CPPFLAGS="-DUSE_INTERP_ERRORLINE -DUSE_INTERP_RESULT -DSIZEOF_VOID_P=8" $(MAKE) install  ; \
	cp generic/bltOldConfig.h ${EOS_HOME}/util/$(OSTYPE)/include/ ; \
	# $(MAKE) INSTALL=${EOS_HOME}/sbin/eosinstall install 


Tcllib::
	@cd $(TCLLIBNAME); \
	$(MAKE) install  ; \

VTKAll::
	cd VTK ; \
	$(MAKE)   ; \
	$(MAKE) install


TclClean::
	@cd tcl$(TCLVERSION)/unix ; \
	$(MAKE) distclean 

TclCleanAll::
	@rm -rf tcl$(TCLVERSION) ; 
	@rm -f tcl$(TCLVERSION)-src.tar.gz ;
	#@rm -f tcl$(TCLVERSION)-src.zip ;

TkClean::
	@cd tk$(TKVERSION)/unix  ; \
	$(MAKE) distclean

TkCleanAll::
	@rm -rf tk$(TKVERSION) ; 
	@rm -f $(TKNAME)-src.tar.gz ; 


BLTClean::
	@cd $(BLTNAMEDIR); \
	$(MAKE) distclean

BLTCleanAll::
	@rm -rf $(BLTNAMEDIR); 
	@rm -f $(BLTNAME).zip ; 

TcllibClean::
	@cd $(TCLLIBNAME); \
	$(MAKE) clean

TcllibCleanAll::
	@rm -rf $(TCLLIBNAME)
	@rm -f  $(TCLLIBNAME).zip 

VTKClean::
	cd vtk$(VTKVERSION) ; \
	$(MAKE) distclean 

VTKCleanAll::
	@rm -rf vtk$(VTKVERSION) 
	@rm -f $(VTKNAME).zip


