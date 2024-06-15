OSTYPE  = I386LINUX
ARCHTYPE = -DII -D$(OSTYPE) $(CUDA_OPTS) 

SHELL   = /bin/bash

MAKE    = /usr/bin/make

CD      = cd

INSTALL =  /usr/bin/install

CC     = gcc
SHAREDCC = gcc -fpic
CXX    = g++
SHAREDCXX = g++ -fpic
CCOPTS = -finline-functions -O2 -g -Wall $(EXTRA_DEFINE) $(ARCHTYPE) \
	-I$(EOS_HOME)/util/$(OSTYPE)/include
#CCOPTS = -finline-functions -O0 -g -Wall $(EXTRA_DEFINE) $(ARCHTYPE) \
#	-I$(EOS_HOME)/util/$(OSTYPE)/include

AR     = /usr/bin/ar

SHARED = gcc -shared -L$(EOS_HOME)/util/$(OSTYPE)/lib/ruby/1.6/i686-linux  -o 

RM     = /bin/rm

LS     = /bin/ls

AWK    = /usr/bin/awk

CAT    = /bin/cat

CP     = /bin/cp
LN     = /bin/ln

CHMOD  = /bin/chmod

CHOWN  = /bin/chown

CHGRP  = /bin/chgrp

DEPENDCOMMAND = gcc $(CCOPT) -E -M

#HOSTDEPENDENTLIB =  -L/usr/cxsoft/lib /usr/lib/libc.a /usr/lib/libisamstub.1 
HOSTDEPENDENTLIB =  -lm -lc -lnsl -lpthread -L$(EOS_HOME)/util/$(OSTYPE)/lib

# X11 
#LIBX11         = -L/usr/X11R6/lib/ -lXext -lXt -lSM -lICE -lX11 
LIBX11         = -L/usr/lib/ -lXext -lX11 
INCX11         = -I/usr/local/X11R6/include 

# OpenGL/MESA

#LIBGL=-L/usr/lib -lGL -L/usr/X11R6/lib -lGLU -lglut
LIBGL=-L/usr/lib -lGL -lglut 

# TCL/TK & VTK
#LIBTCLTKVTK    = -ldld -L/usr/local/lib -ltk -ltcl -lBLT -lvtk -lvtkTcl -lvtk \
				-lMesaGL -lMesaaux -lMesatk -lMesaGLU 
#LIBTCLTKVTK    = -L$(EOS_HOME)/util/$(OSTYPE)/lib \
				-lBLT \
				-ltk8.3 -ltcl8.3 -ldl -lpthread \
				-lMesaGL -lMesaGLU  $(LIBX11) 
#LIBTCLTKVTK    = -L$(EOS_HOME)/util/$(OSTYPE)/lib \
				-lBLT \
				-lvtkPatentedTCL -lvtkPatented \
				-lvtkImagingTCL  -lvtkImaging  \
				-lvtkGraphicsTCL -lvtkGraphics \
				-lvtkRenderingTCL -lvtkRendering \
				-lvtkCommonTCL   -lvtkCommon   \
				-ltk8.3 -ltcl8.3 -ldl -lpthread \
				-lMesaGL -lMesaGLU  $(LIBX11) 
#LIBTCLTK    = -L$(EOS_HOME)/util/$(OSTYPE)/lib \
				-lBLT \
				-ltk8.3 -ltcl8.3 -ldl -lpthread \
				-lMesaGL -lMesaGLU  $(LIBX11) 
LIBTCLTK    = -L$(EOS_HOME)/util/$(OSTYPE)/lib \
				-lBLT \
				-ltk8.4 -ltcl8.4 -ldl -lpthread \
				$(LIBGL) $(LIBX11) 

LIBTCLTKVTK    = -L$(EOS_HOME)/util/$(OSTYPE)/lib/vtk \
				-lvtkPatentedTCL -lvtkPatented \
				-lvtkRenderingTCL -lvtkRendering \
				-lvtkImagingTCL  -lvtkImaging  \
				-lvtkGraphicsTCL -lvtkGraphics \
				-lvtkFilteringTCL -lvtkFiltering \
				-lvtkParallelTCL  -lvtkParallelTCL \
				-lvtkIOTCL        -lvtkIO \
				-lvtkHybridTCL    -lvtkHybrid \
				-lvtkCommonTCL   -lvtkCommon  -dl $(LIBTCLTK) -lvtkjpeg -lvtkpng -lvtkzlib -lvtkftgl -lvtkfreetype

#LIBTCLTKVTK    = -L$(EOS_HOME)/util/$(OSTYPE)/lib \
				-lBLT \
				-ltk8.3 -ltcl8.3 -ldl        

#INCTCLTKVTK    = -I/usr/local/include -I/usr/local/include/tk -I/usr/local/include/vtk
INCTCLTKVTK    = -I$(EOS_HOME)/util/$(OSTYPE)/include \
				 -I$(EOS_HOME)/util/$(OSTYPE)/include/tk \
				 -I$(EOS_HOME)/util/$(OSTYPE)/include/vtk
INCTCLTK       = -I$(EOS_HOME)/util/$(OSTYPE)/include \
				 -I$(EOS_HOME)/util/$(OSTYPE)/include/tk 
#DEFTCLTKVTK    = -DUSE_OGLR -D_HP_NO_FAST_MACROS -DHAVE_UNISTD_H=1 -DHAVE_LIMITS_H=1 -DSTDC_HEADERS=1 -DTK_FILE_COUNT=_cnt -DTK_LIBRARY=\"/usr/local/lib/tk4.1\"
#DEFTCLTKVTK    = -DUSE_OGLR -D_HP_NO_FAST_MACROS -DHAVE_UNISTD_H=1 -DHAVE_LIMITS_H=1 \
				 -DSTDC_HEADERS=1 -DTK_FILE_COUNT=_cnt \
				 -DTK_LIBRARY=\"$(EOS_HOME)/util/$(OSTYPE)/lib/tk8.0\" 
DEFTCLTK       = 
DEFTCLTKVTK    = -DHAVE_GETCWD=1 -DHAVE_UNISTD_H=1 -DUSE_TERMIOS=1 -DHAVE_SYS_TIME_H=1 -DTIME_WITH_SYS_TIME=1 \
				 -DHAVE_TM_ZONE=1 -DHAVE_TIMEZONE_VAR=1 -DHAVE_ST_BLKSIZE=1 -DSTDC_HEADERS=1 -DNO_UNION_WAIT=1 \
				 -DNEED_MATHERR=1 -DHAVE_SIGNED_CHAR=1 -DHAVE_SYS_IOCTL_H=1  \
				 -DHAVE_UNISTD_H=1 -DHAVE_LIMITS_H=1 -DSTDC_HEADERS=1 -DHAVE_SYS_TIME_H=1 -DTIME_WITH_SYS_TIME=1


#
RUBY             = $(EOS_HOME)/util/$(OSTYPE)/bin/ruby 
RUBYSHAREDLIB    = $(EOS_HOME)/util/$(OSTYPE)/lib/ruby/1.6/i686-linux/
INCRUBY = -I$(EOS_HOME)/util/$(OSTYPE)/include/ruby
DEFRUBY = -fPIC
LIBRUBY = 

# VECLIB
#LIBVECLIB      = -L/usr/cxsoft/lib  
#INCVECLIB      = -I/usr/cxsoft/include

# LIBTIFF
LIBTIFF        = -L$(EOS_HOME)/util/$(OSTYPE)/lib -ltiff

# LIBGIF
LIBGIF         = -L$(EOS_HOME)/util/$(OSTYPE)/lib -lgif

# LIBJPEG
LIBJPEG = -L$(EOS_HOME)/util/$(OSTYPE)/lib -ljpeg

# Khoros System
KHOROS_HOME    = /users/khoros/AdvKhoros2300
KHOROS_KGENOBJ = $(KHOROS_HOME)/bin/kgenobj
KHOROS_KSET    = $(KHOROS_HOME)/bin/kset
#KHOROS_OPTIONS = -DKHOROS
#KHOROS_LIBS    = -L$(KHOROS_HOME)/lib -static \
				 -lkaps -lkapu -lkclui -lkcms -lkdac -lkdms -lkgen \
				 -lklm -lktu -lku -lkvf \
				 -lkc -lkvf -lklang -lkclui -lkcms -lkdms  -lvipl -lkgm -lkaps -lkdac -lkdmanip  \
				 -lkexpr -lkc -lkfmt -lkgdbm -lkgen -lkgm -lkip -lklm -lksegops -lktu -lkvf -lverr -lvipl -lvu -ldl

#KHOROS_INCS    =  -I$(KHOROS_HOME)/bootstrap/include \
				  -I$(KHOROS_HOME)/dataserv/include  \
				  -I$(KHOROS_HOME)/datamanip/include \
				  -I$(KHOROS_HOME)/image/include

#PGSQL
INCPOSTGRES = -I/usr/include/pgsql
POSTGRES_LIBS = -lpq

#MICO
IDL     = idl
MICOCC  = mico-c++
MICOLD  = mico-ld
INCMICO =  -I$(EOS_HOME)/util/$(OSTYPE)/include
LIBMICO =  -I$(EOS_HOME)/util/$(OSTYPE)/lib -lmico2.3.11 -lmicocoss2.3.11
