OSTYPE  = ALPHALINUX
ARCHTYPE =-DII
MAKE    = /usr/bin/make

CD      = cd

INSTALL = /usr/bin/install

CC     = gcc
CXX    = g++
CCOPTS = -finline-functions -O2 -g -Wall $(EXTRA_DEFINE) $(ARCHTYPE) -I/usr/local/include -I/usr/X11R6/include -I/usr/local/include/tk 

AR     = /usr/bin/ar

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

HOSTDEPENDENTLIB =  -lm -lc -ldl

# X11 
LIBX11         = -L/usr/X11R6/lib -lX11 -lXt
INCX11         = -I/usr/X11R6/include

# TCL/TK & VTK
LIBTCLTKVTK    = -L/usr/local/lib -ltk -ltcl -lBLT -lvtk -lvtkTcl
INCTCLTKVTK    = -I/usr/local/include -I/usr/local/include/tcl -I/usr/local/include/tk -I/usr/local/include/vtk
DEFTCLTKVTK    = -DUSE_OGLR -D_HP_NO_FAST_MACROS -DHAVE_UNISTD_H=1 -DHAVE_LIMITS_H=1 -DSTDC_HEADERS=1 -DTK_FILE_COUNT=_cnt -DTK_LIBRARY=\"/usr/local/lib/tk4.1\"

# VECLIB
LIBVECLIB      = -L/usr/cxsoft/lib  
INCVECLIB      = -I/usr/cxsoft/include

# LIBTIFF
LIBTIFF        = -L/usr/local/lib -ltiff

# LIBGIF
LIBGIF         = -L/usr/local/lib -lgif

# Khoros System
KHOROS_HOME = /usr/local/khoros210
KHOROS_KGENOBJ = /usr/local/khoros210/bin/kgenobj
KHOROS_KSET    = /usr/local/khoros210/bin/kset
KHOROS_OPTIONS = -DKHOROS
KHOROS_LIBS    = -L/usr/local/khoros210/lib -L/usr/local/khoros/lib \
				 -lgeometry -lghost -lkaps -lkapu -lkclui -lkcms -lkdac \
				 -lkdmanip -lkdms -lkfmt -lkgen -lkip -lklibdb \
				 -lklm -lksegops \
				 -lktu -lku -lkvf -lverr -lvipl -lvu \
				 -lgeometry -lghost -lkaps -lkapu -lkclui -lkcms -lkdac \
				 -lkdmanip -lkdms -lkfmt -lkgen -lkip -lklibdb \
				 -lklm -lksegops \
				 -lktu -lku -lkvf -lverr -lvipl -lvu  \
				 -lkexpr -lm -lfl 
#                -lkexpr
#				 -lkmatrix 
#				 -lkwid 
#				 -lxva -lxvf -lxvg -lxvl -lxvm -lxvo -lxvobj -lxvs -lxvu -lxvw 
#				 -L/usr/X11R6/lib -lX11 -lXt


KHOROS_INCS    =  -I/usr/local/khoros/bootstrap/include \
				  -I/usr/local/khoros/dataserv/include  \
				  -I/usr/local/khoros/datamanip/include \
				  -I/usr/local/khoros/image/include
