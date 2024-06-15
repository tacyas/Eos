include ${EOS_HOME}/src/Config/${EOS_HOST}${FLAG_ICC}.inc
include ../../Config/Define.inc
include ../../Config/Target.inc
-include Config/Define.inc

UTILS=fftw gsl

FFTWWHERE=http://www.fftw.org/
FFTWVERSION=3.3.10
NRVERSION=1.1
#GSLVERSION=1.16
GSLVERSION=2.7
GSLNAME=gsl-$(GSLVERSION)
GSLWHERE=ftp://ftp.gnu.org/gnu/gsl
GSLWHERE=ftp://ftp.jaist.ac.jp/pub/GNU/gsl/

help:
	@echo "-- fftw, gsl @MATH --"
	@echo "make fftw"
	@echo "make gsl"

fftw::
	make fftwCheck
	make fftwConfig
	make fftwAll
	make fftwClean
	make fftwCleanAll

fftwCheck::
	#ln -sf ../../src/MATH/fftw-$(FFTWVERSION).tar.gz .
	curl -L $(FFTWWHERE)/fftw-$(FFTWVERSION).tar.gz > fftw-$(FFTWVERSION).tar.gz
	gzip -dc fftw-$(FFTWVERSION).tar.gz | tar xvf -

fftwConfig:
	case $(OSTYPE) in \
		'CELLLINUX64' ) \
			echo "altivec" ; \
			cd  fftw-$(FFTWVERSION) ; ./configure  --prefix=${EOS_HOME}/util/$(OSTYPE)/ CC=spu-gcc --with-gcc -enable-float --enable-cell --enable-type-prefix --enable-fma ; \
			;; \
		'X86LINUX64' ) \
			echo "x86Linux64" ; \
			cd  fftw-$(FFTWVERSION) ; ./configure --prefix=${EOS_HOME}/util/$(OSTYPE)/ -enable-float --enable-fma --enable-threads --enable-shared; \
			;; \
		'X86LINUX64ICC' ) \
			echo "x86Linux64icc" ; \
			cd  fftw-$(FFTWVERSION) ; ./configure --prefix=${EOS_HOME}/util/$(OSTYPE)/ CC=icc CFLAGS=-gcc --with-our-malloc16 --enable-sse2 -enable-float --enable-fma --enable-threads --enable-shared; \
			;; \
		'ARM64MAC64' ) \
			echo "arm64Mac64" ; \
			cd  fftw-$(FFTWVERSION) ; ./configure --prefix=${EOS_HOME}/util/$(OSTYPE)/ --with-gcc -enable-float --enable-type-prefix --enable-threads ; \
			;; \
		*) \
			echo "others" ; \
			cd  fftw-$(FFTWVERSION) ; ./configure --prefix=${EOS_HOME}/util/$(OSTYPE)/ --with-gcc -enable-float --enable-type-prefix --enable-sse --enable-threads ; \
			;; \
	esac

fftwAll:
	cd  fftw-$(FFTWVERSION) ;  make ; make check; make install

fftwClean:
	cd ffw-$(FFTWVERSION); make clean

fftwCleanAll:
	rm -rf fftw-$(FFTWVERSION); rm -f fftw-$(FFTWVERSION).tar.gz 

# GSL
gsl:
	make gslCheck
	make gslConfig
	make gslAll
	make gslClean
	make gslCleanAll

gslCheck:: 
	curl -L $(GSLWHERE)/$(GSLNAME).tar.gz  > $(GSLNAME).tar.gz
	tar xvzf $(GSLNAME).tar.gz  

gslConfig::
	cd $(GSLNAME); ./configure --prefix=${EOS_HOME}/util/$(OSTYPE)/ --with-gnu-ld

gslAll::
	cd $(GSLNAME); make ; make test; make install

gslClean:
	cd $(GSLNAME); make clean

gslCleanAll:
	rm -rf $(GSLNAME)
	rm -f $(GSLNAME).tar.gz

#
# NR
#

nrCheck::
	ln -sf ../../src/MATH/nr-$(NRVERSION).tar.gz .
	gzip -dc nr-$(NRVERSION).tar.gz | tar xvf -	

nrConfig:
	cd nr; make config

nrAll:
	cd nr; make all

nrClean:
	cd nr; make clean
