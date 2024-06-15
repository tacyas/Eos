include ${EOS_HOME}/src/Config/${EOS_HOST}.inc
include ../../Config/Define.inc
include ../../Config/Target.inc

UTILS=AlsaLIb AlsaOS

ALSALIBVERSION=1.0.29
ALSALIBNAME=alsa-lib
ALSALIBWHERE=ftp://ftp.alsa-project.org/pub/lib/$(ALSALIBNAME)-$(ALSALIBVERSION).tar.bz2

ALSAOSSVERSION=1.0.28
ALSAOSSNAME=alsa-oss
ALSAOSSWHERE=ftp://ftp.alsa-project.org/pub/oss-lib/$(ALSAOSSNAME)-$(ALSAOSSVERSION).tar.bz2

#
# ALSA-LIB
#
AlsaLibCheck:
	curl -O $(ALSALIBWHERE)
	tar xvjf $(ALSALIBNAME)-$(ALSALIBVERSION).tar.bz2

AlsaOSSCheck:
	curl -O $(ALSAOSSWHERE)
	tar xvjf $(ALSAOSSNAME)-$(ALSAOSSVERSION).tar.bz2

AlsaLibConfig: 
	cd $(ALSALIBNAME)-$(ALSALIBVERSION); ./configure --prefix=$(EOS_HOME)/util/$(OSTYPE) ;

AlsaOSSConfig: AlsaLibAll 
	cd $(ALSAOSSNAME)-$(ALSAOSSVERSION); ./configure --prefix=$(EOS_HOME)/util/$(OSTYPE) ;

AlsaLibAll:
	cd $(ALSALIBNAME)-$(ALSALIBVERSION); make; make install

AlsaOSSAll:
	cd $(ALSAOSSNAME)-$(ALSAOSSVERSION); make; make install

AlsaLibClean:
	cd $(ALSALIBNAME)-$(ALSALIBVERSION); make clean
	
ALsaOSSClean:
	cd $(ALSAOSSNAME)-$(ALSAOSSVERSION); make clean

AlsaLibCleanAll:
	rm -rf $(ALSALIBNAME)-$(ALSALIBVERSION)
	rm -f $(ALSALIBNAME)-$(ALSALIBVERSION).tar.bz2

AlsaOSSCleanAll:
	rm -rf $(ALSAOSSNAME)-$(ALSAOSSVERSION)
	rm -f $(ALSAOSSNAME)-$(ALSAOSSVERSION).tar.bz2
