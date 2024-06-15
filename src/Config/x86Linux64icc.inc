OSTYPE  = X86LINUX64ICC
ARCHTYPE = -DII -DFFTW -D$(OSTYPE) $(CUDA_OPTS)

SHELL   = /bin/bash

MAKE    = /usr/bin/make

CD      = cd

INSTALL =  /usr/bin/install

CC     = icc

CXX    = icpc

SHAREDCC     = icc -fpic 

SHAREDCXX    = icpcc -fpic 

CCOPTS = -O2 -pthread -ip -inline-level=2 -Wall -Zp1 $(EXTRA_DEFINE) $(ARCHTYPE) \
	-I$(EOS_HOME)/util/$(OSTYPE)/include
#CCOPTS = -O2 -pthread -ip -Wall -Zp1 $(EXTRA_DEFINE) $(ARCHTYPE) \
#	-I$(EOS_HOME)/util/$(OSTYPE)/include
CCOPTSDEBUG = -debug all -O2 -pthread -ip -inline-level=2 -Wall -Zp1 $(EXTRA_DEFINE) $(ARCHTYPE) \
    -I$(EOS_HOME)/util/$(OSTYPE)/include

AR     = xiar

SHARED = icc -shared -L$(EOS_HOME)/util/$(OSTYPE)/lib/ruby/1.6/i686-linux -o 

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

HOSTDEPENDENTLIB =  -lm -lc -lnsl -lpthread -L$(EOS_HOME)/util/$(OSTYPE)/lib -lfftw3f_threads -lfftw3f

# X11 
LIBX11         = -lXext -lXt -lSM -lICE -lX11 
INCX11         = -I/usr/include 

# OpenGL/MESA

LIBGL = -L/usr/lib -lGL -lGLU -lglut 

# TCL/TK & VTK
LIBTCLTK    = -L$(EOS_HOME)/util/$(OSTYPE)/lib \
				-lBLT \
				-ltk8.4 -ltcl8.4 -ldl -lpthread \
				 $(LIBX11) 

LIBTCLTKVTK    = -i_dynamic  -fPIC -L$(EOS_HOME)/util/$(OSTYPE)/lib/vtk \
				-L/usr/local/vtk-5.2.0/lib/vtk-5.2 \
				-lvtkCommonTCL    -lvtkFilteringTCL \
				-lvtkGraphicsTCL  -lvtkImagingTCL \
				-lvtkIOTCL 		  -lvtkRenderingTCL \
				-lvtkHybridTCL \
				-lvtkParallelTCL  \
				-lvtkHybrid       -lvtkParallel \
				-lvtkIOTCL  	  -lvtkIO       \
				-lvtkRenderingTCL -lvtkGraphicsTCL \
				-lvtkImagingTCL   -lvtkFilteringTCL \
				-lvtkCommonTCL	  -lvtkRendering \
				-lvtkGraphics     -lvtkImaging   \
				-lvtkFiltering    -lvtkCommon \
				$(LIBTCLTK) -ldl -lpthread -lvtkftgl 


INCTCLTKVTK    = -I$(EOS_HOME)/util/$(OSTYPE)/include \
				 -I$(EOS_HOME)/util/$(OSTYPE)/include/vtk \
				 -I$(EOS_HOME)/util/$(OSTYPE)/include/tk  \
				 -I/usr/local/vtk-5.2.0/include/vtk-5.2/ 
INCTCLTK       = -I$(EOS_HOME)/util/$(OSTYPE)/include \
				 -I$(EOS_HOME)/util/$(OSTYPE)/include/tk 
DEFTCLTK       = 
//DEFTCLTKVTK    = -DHAVE_GETCWD=1 -DHAVE_UNISTD_H=1 -DUSE_TERMIOS=1 -DHAVE_SYS_TIME_H=1 -DTIME_WITH_SYS_TIME=1 \
//				 -DHAVE_TM_ZONE=1 -DHAVE_TIMEZONE_VAR=1 -DHAVE_ST_BLKSIZE=1 -DSTDC_HEADERS=1 -DNO_UNION_WAIT=1 \
//				 -DNEED_MATHERR=1 -DHAVE_SIGNED_CHAR=1 -DHAVE_SYS_IOCTL_H=1  \
//				 -DHAVE_UNISTD_H=1 -DHAVE_LIMITS_H=1 -DSTDC_HEADERS=1 -DHAVE_SYS_TIME_H=1 -DTIME_WITH_SYS_TIME=1

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


#PGSQL
INCPOSTGRES = -I/usr/include/pgsql
POSTGRES_LIBS = -lpq

#MICO
IDL     = idl
MICOCC  = mico-c++
MICOLD  = mico-ld
INCMICO =  -I$(EOS_HOME)/util/$(OSTYPE)/include
LIBMICO =  -I$(EOS_HOME)/util/$(OSTYPE)/lib -lmico2.3.11 -lmicocoss2.3.11

#CUDA
NVCC = nvcc

NVCCOPTS = -ccbin g++ -I../../common/inc  -m64 \
           -gencode arch=compute_10,code=sm_10 \
		   -gencode arch=compute_20,code=sm_20 \
		   -gencode arch=compute_30,code=sm_30 \
		   -gencode arch=compute_35,code=\"sm_35,compute_35\"

NVCCOPTSGDB =  --host-compilation='C++' --use_fast_math -g \
			-Xcompiler='-g' \
			-Xcompiler='-ffast-math' \
			-Xcompiler='-funroll-loops' \
			-Xcompiler='-m64' \
			-Xcompiler='-fPIC'
NVCCOPTSCUDAGDB =  --host-compilation='C++' --use_fast_math -g -G \
			-Xcompiler='-g' \
			-Xcompiler='-ffast-math' \
			-Xcompiler='-funroll-loops' \
			-Xcompiler='-m64' \
			-Xcompiler='-fPIC'
INCCUDA = -I$(EOS_HOME)/util/$(OSTYPE)/cuda/inc -I$(EOS_HOME)/util/$(OSTYPE)/cuda/NVIDIA_CUDA_SDK/inc -I$(EOS_HOME)/util/$(OSTYPE)/cuda/include

LIBCUDA = -L$(EOS_HOME)/util/$(OSTYPE)/cuda/lib64 -L$(EOS_HOME)/util/$(OSTYPE)/cuda/lib64 -lcudart -lcufft

CC=icc $(LIBCUDA) $(ICCUDA)
