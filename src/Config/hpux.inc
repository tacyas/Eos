OSTYPE  = HP
ARCHTYPE = -DM68 -D$(OSTYPE)

MAKE    = /usr/local/bin/gmake

CD      = cd

INSTALL = $(EOS_HOME)/sbin/eosinstall

CC     = gcc

CXX    = g++

CCOPTS = -finline-functions -O2 -g -Wall $(EXTRA_DEFINE) $(ARCHTYPE) \
	-I$(EOS_HOME)/util/$(OSTYPE)/include -N

AR     = /bin/ar

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

#HOSTDEPENDENTLIB =  -L/usr/cxsoft/lib -lcl /usr/lib/libisamstub.1 -lM /usr/lib/libdld.1
HOSTDEPENDENTLIB =  -lM /usr/lib/libdld.1 -L$(EOS_HOME)/util/$(OSTYPE)/lib

# X11 
#LIBX11         = -L/usr/local/X11R6/lib/ -lXt -L/usr/lib/X11R6/ -lXt -lXhp11 -lX11 -lXwindow -L/opt/graphics/common/lib -lhpgfx
LIBX11         = -L/usr/local/X11R6/lib/ -lXt -L/usr/lib/X11R6/ -lXt -lX11 -lXwindow -L/opt/graphics/common/lib -lhpgfx
INCX11         = -I/usr/local/X11R6/include 

# TCL/TK & VTK
#LIBTCLTKVTK    = -ldld -L/usr/local/lib -ltk -ltcl -lBLT -lvtk -lvtkTcl -lvtk \
				-lMesaGL -lMesaaux -lMesatk -lMesaGLU 
#LIBTCLTKVTK    = -ldld -L$(EOS_HOME)/util/$(OSTYPE)/lib \
				-lBLT -lVTKCommon -lVTKCommonTcl \
				-lVTKGraphics -lVTKGraphicsTcl \
				-lVTKImaging -lVTKImagingTcl \
				-ltk8.3 -ltcl8.3 -ltcl8.3 \
				-lMesaGL -lMesaaux -lMesatk -lMesaGLU 

#LIBTCLTKVTK    = -ldld -L$(EOS_HOME)/util/$(OSTYPE)/lib \
				-lBLT -lVTKCommon -lVTKCommonTcl \
				-lVTKGraphics -lVTKGraphicsTcl \
				-lVTKImaging -lVTKImagingTcl \
				-ltk8.3 -ltcl8.3 \
				-lMesaGL -lMesaaux -lMesatk -lMesaGLU 

LIBTCLTKVTK    = -L$(EOS_HOME)/util/$(OSTYPE)/lib \
				-lBLT \
				-ltk8.3 -ltcl8.3  -ldld -lm -lc -Wl,+s,+b,$(EOS_HOME)/util/$(OSTYPE)/lib


#INCTCLTKVTK    = -I/usr/local/include -I/usr/local/include/tk -I/usr/local/include/vtk
INCTCLTKVTK    = -I$(EOS_HOME)/util/$(OSTYPE)/include \
				 -I$(EOS_HOME)/util/$(OSTYPE)/include/tk \
				 -I$(EOS_HOME)/util/$(OSTYPE)/include/vtk
#DEFTCLTKVTK    = -DHAVE_GETCWD=1 -DHAVE_UNISTD_H=1 -DUSE_TERMIOS=1 -DHAVE_SYS_TIME_H=1 -DTIME_WITH_SYS_TIME=1 \
				 -DHAVE_TM_ZONE=1 -DHAVE_TIMEZONE_VAR=1 -DHAVE_ST_BLKSIZE=1 -DSTDC_HEADERS=1 -DNO_UNION_WAIT=1 \
				 -DNEED_MATHERR=1 -DHAVE_SIGNED_CHAR=1 -DHAVE_SYS_IOCTL_H=1  \
				 -DHAVE_UNISTD_H=1 -DHAVE_LIMITS_H=1 -DSTDC_HEADERS=1 -DHAVE_SYS_TIME_H=1 -DTIME_WITH_SYS_TIME=1

DEFTCLTKVTK    = -DHAVE_UNISTD_H=1 -DHAVE_LIMITS_H=1 -DHAVE_GETCWD=1 -DHAVE_OPENDIR=1 -DHAVE_STRSTR=1 -DHAVE_STRTOL=1 -DHAVE_TMPNAM=1 -DHAVE_WAITPID=1 -DNO_DLFCN_H=1 -DHAVE_UNISTD_H=1 -DHAVE_SYS_PARAM_H=1 -DUSE_TERMIOS=1 -DHAVE_SYS_TIME_H=1 -DTIME_WITH_SYS_TIME=1 -DHAVE_TZNAME=1 -DHAVE_TIMEZONE_VAR=1 -DHAVE_ST_BLKSIZE=1 -DSTDC_HEADERS=1 -DNO_UNION_WAIT=1 -DNEED_MATHERR=1 -DHAVE_SYS_IOCTL_H=1 -DSTATIC_BUILD=1         -DTCL_SHLIB_EXT=\".sl\"

# VECLIB
#LIBVECLIB      = -L/usr/cxsoft/lib  
#INCVECLIB      = -I/usr/cxsoft/include

# LIBTIFF
LIBTIFF        = -L$(EOS_HOME)/util/$(OSTYPE)/lib -ltiff

# LIBGIF
LIBGIF         = -L$(EOS_HOME)/util/$(OSTYPE)/lib -lgif

# LIBJPEG
LIBJPEG        = -L$(EOS_HOME)/util/$(OSTYPE)/lib -ljpeg

# Khoros System
#KHOROS_HOME    = /usr/local/khoros210
#KHOROS_KGENOBJ = $(KHOROS_HOME)/bin/kgenobj
#KHOROS_KSET    = $(KHOROS_HOME)/bin/kset
#KHOROS_OPTIONS = -DKHOROS
#KHOROS_LIBS    = -L/usr/local/khoros210/lib -L/usr/local/khoros/lib \
				 -lkaps -lkapu -lkclui -lkcms -lkdac -lkdms -lkgen \
				 -lklm -lktu -lku -lkvf

#KHOROS_INCS    =  -I/usr/local/khoros/bootstrap/include \
				  -I/usr/local/khoros/dataserv/include  \
				  -I/usr/local/khoros/datamanip/include \
				  -I/usr/local/khoros/image/include

#
# PVM
#
DEFPVM = -DPVM \
		 -DNOWAIT3 -DNOUNIXDOM -DRSHCOMMAND=\"/usr/bin/rsh\" -DNEEDENDIAN \
		 -DHASSTDLIB -DSYSVSTR -DHASERRORVARS -DFDSETNOTSTRUCT
INCPVM = -I$(PVM_ROOT)/include
LIBPVM = -L$(PVM_ROOT)/lib/$(PVM_ARCH) -lpvm3

