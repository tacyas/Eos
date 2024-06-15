OSTYPE  = ALPHA
ARCHTYPE =-DII
MAKE    = /usr/local/bin/make

CD      = cd

INSTALL = $(EOS_HOME)/sbin/eosinstall

CC     = gcc
CXX    = g++
CCOPTS = -finline-functions -O0 -g -Wall $(EXTRA_DEFINE) $(ARCHTYPE) -I/usr/local/include -I/usr/local/X11R6/include -I/usr/local/include/tk 

AR     = /bin/ar

RM     = /bin/rm

LS     = /bin/ls

AWK    = /usr/bin/awk

CAT    = /bin/cat

CP     = /bin/cp

CHMOD  = /bin/chmod

DEPENDCOMMAND = gcc $(CCOPT) -E -M

HOSTDEPENDENTLIB =  -lm -lc -lexc

# X11 
LIBX11         = -L/usr/local/X11R6/lib
INCX11         = -I/usr/local/X11R6/include

# TCL/TK & VTK
LIBTCLTKVTK    = -L/usr/local/lib -ltk -ltcl -lvtkTcl -lvtk
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
				 -lkaps -lkapu -lkclui -lkcms -lkdac -lkdms -lkgen \
				 -lklm -lktu -lku -lkvf

KHOROS_INCS    =  -I/usr/local/khoros/bootstrap/include \
				  -I/usr/local/khoros/dataserv/include  \
				  -I/usr/local/khoros/datamanip/include \
				  -I/usr/local/khoros/image/include
