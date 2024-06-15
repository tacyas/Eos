include ${EOS_HOME}/src/Config/${EOS_HOST}.inc
include ../../Config/Define.inc
include ../../Config/Target.inc

UTILS=tiff jpeg gif

help:
	@echo "make tiff"

TIFFWHERE=http://download.osgeo.org/libtiff/
TIFFNAME=tiff
TIFFVERSION=4.3.0
JPEGWHERE=https://www.ijg.org/files/
JPEGNAME=jpeg
JPEGVERSION=9e
GIFWHERE=https://sourceforge.net/projects/giflib/files/
GIFNAME=giflib
GIFVERSION=5.2.1

#
# TIFF
#
tiff:
	make tiffCheck
	make tiffConfig
	make tiffAll
	make tiffClean
	make tiffCleanAll

tiffCheck:
	curl -o $(TIFFNAME)-$(TIFFVERSION).tar.gz -L $(TIFFWHERE)/$(TIFFNAME)-$(TIFFVERSION).tar.gz
	tar xvzf $(TIFFNAME)-$(TIFFVERSION).tar.gz

tiffConfig:
	cd $(TIFFNAME)-$(TIFFVERSION); ./configure --prefix=${EOS_HOME}/util/${EOS_HOSTDIR}/ 

tiffAll:
	cd $(TIFFNAME)-$(TIFFVERSION); make -i install

tiffClean:
	cd $(TIFFNAME)-$(TIFFVERSION); make clean

tiffCleanAll:
	rm -rf $(TIFFNAME)-$(TIFFVERSION); rm $(TIFFNAME)-$(TIFFVERSION).tar.gz

#
# JPEG
#
jpeg:
	make jpegCheck
	make jpegConfig
	make jpegAll
	make jpegClean
	make jpegCleanAll

jpegCheck:
	curl -o $(JPEGNAME)src.v$(JPEGVERSION).tar.gz -L $(JPEGWHERE)/$(JPEGNAME)src.v$(JPEGVERSION).tar.gz
	tar xvzf $(JPEGNAME)src.v$(JPEGVERSION).tar.gz

jpegConfig:
	cd $(JPEGNAME)-$(JPEGVERSION); ./configure --prefix=${EOS_HOME}/util/${EOS_HOSTDIR}/ 

jpegAll:
	cd $(JPEGNAME)-$(JPEGVERSION); make -i install

jpegClean:
	cd $(JPEGNAME)-$(JPEGVERSION); make clean

jpegCleanAll:
	rm -rf $(JPEGNAME)-$(JPEGVERSION); rm $(JPEGNAME)src.v$(JPEGVERSION).tar.gz

#
# GIF
#

giflib:
	make gifCheck
	make gifConfig
	make gifgAll
	make gifClean
	make gifCleanAll

gifCheck:
	curl -o $(GIFNAME)-$(GIFVERSION).tar.gz -L $(GIFWHERE)/$(GIFNAME)-$(GIFVERSION).tar.gz
	tar xvzf $(GIFNAME)-$(GIFVERSION).tar.gz

gifConfig:
	cd $(GIFNAME)-$(GIFVERSION); ./configure --prefix=${EOS_HOME}/util/${EOS_HOSTDIR}/ 

gifAll:
	cd $(GIFNAME)-$(GIFVERSION); make -i PREFIX=${EOS_HOME}/util/${EOS_HOSTDIR}/ install

gifClean:
	cd $(GIFNAME)-$(GIFVERSION); make clean

gifCleanAll:
	rm -rf $(GIFNAME)-$(GIFVERSION); rm $(GIFNAME)-$(GIFVERSION).tar.gz



