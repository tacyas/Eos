include ${EOS_HOME}/src/Config/${EOS_HOST}.inc

#CMAKEVERSION=1.8.3
#CMAKEVERSION=2.6.4
CMAKEVERSION=2.8.1
CMAKEVERSIONDIR=v2.8
#CMAKEVERSION=2.8.4
OPENSSLVERSION=1.0.1j
ZLIBVERSION=1.2.8
YAMLVERSION=0.1.5
GITVERSION=2.6.3

help:
	@echo "You can install cmake, openssl, libyaml zlib, git"  
	@echo ""
	@echo " $ make check "
	@echo " $ make config "
	@echo " $ make all "
	@echo " $ make clean "
	@echo " $ make cleanAll "

check: CmakeCheck OpenSSLCheck zlibCheck libyamlCheck GitCheck

config: CmakeConfig OpenSSLConfig zlibConfig libyamlConfig GitConfig

all: CmakeAll OpenSSLAll zlibAll libyamlAll GitAll

clean: CmakeClean OpenSSLClean zlibClean libyamlClean GitClean

cleanAll: CmakeCleanAll OpenSSLCleanAll zlibCleanAll libyamlCleanAll GitCleanAll

ICUCheck:
	git clone https://github.com/unicode-org/icu.git

ICUConfig:
	cd icu/icu4c/source; ./configure --prefix=$(EOS_HOME)/util/$(OSTYPE) --enable-icu-config

ICUAll:
	cd icu/icu4c/source; make; make install

ICUClean:
	cd icu/icu4c/source; make clean

OpenSSLCheck:
	curl -O https://www.openssl.org/source/openssl-$(OPENSSLVERSION).tar.gz
	gzip -dc openssl-$(OPENSSLVERSION).tar.gz | tar xvf - 

OpenSSLConfig:
	cd openssl-$(OPENSSLVERSION); ./config shared --prefix=$(EOS_HOME)/util/$(OSTYPE)

OpenSSLAll:
	cd openssl-$(OPENSSLVERSION); make; make test; make install

OpenSSLClean:
	cd openssl-$(OPENSSLVERSION); make clean

OpenSSLCleanAll:
	rm -rf openssl-$(OPENSSLVERSION) 
	rm -f openssl-$(OPENSSLVERSION).tar.gz

#
# zlib
#
zlibCheck:
	curl -O http://zlib.net/zlib-$(ZLIBVERSION).tar.gz
	gzip -dc zlib-$(ZLIBVERSION).tar.gz | tar xvf - 

zlibConfig:
	cd zlib-$(ZLIBVERSION); ./configure --prefix=$(EOS_HOME)/util/$(OSTYPE)

zlibAll:
	cd zlib-$(ZLIBVERSION); make; make test; make install

zlibClean:
	cd zlib-$(ZLIBVERSION); make clean

zlibCleanAll:
	rm -rf zlib-$(ZLIBVERSION) 
	rm -f zlib-$(ZLIBVERSION).tar.gz


#
# libyaml
#
libyamlCheck:
	curl -O http://pyyaml.org/download/libyaml/yaml-$(YAMLVERSION).tar.gz
	gzip -dc yaml-$(YAMLVERSION).tar.gz | tar xvf - 

libyamlConfig:
	cd yaml-$(YAMLVERSION); ./configure --prefix=$(EOS_HOME)/util/$(OSTYPE)

libyamlAll:
	cd yaml-$(YAMLVERSION); make; make test; make install

libyamlClean:
	cd yaml-$(YAMLVERSION); make clean

libyamlCleanAll:
	rm -rf yaml-$(YAMLVERSION) 
	rm -f yaml-$(YAMLVERSION).tar.gz


#
#
#
CmakeCheck:
	#ln -sf ../../src/Admin/cmake-$(CMAKEVERSION).tar.gz .
	curl -O http://www.cmake.org/files/$(CMAKEVERSIONDIR)/cmake-$(CMAKEVERSION).tar.gz
	gzip -dc cmake-$(CMAKEVERSION).tar.gz | tar xvf -

CmakeConfig:
	cd cmake-$(CMAKEVERSION); \
	./bootstrap --prefix=$(EOS_HOME)/util/$(OSTYPE)
#	./configure --prefix=$(EOS_HOME)/util/$(OSTYPE)

CmakeAll:
	cd cmake-$(CMAKEVERSION); \
	./bootstrap --prefix=$(EOS_HOME)/util/$(OSTYPE); \
	make ; \
	make install

CmakeClean:
	cd cmake-$(CMAKEVERSION); \
	make clean


CmakeCleanAll:
	rm -rf cmake-$(CMAKEVERSION) 
	rm -f cmake-$(CMAKEVERSION).tar.gz


#
# Git
#
GitCheck:
	curl -O https://www.kernel.org/pub/software/scm/git/git-$(GITVERSION).tar.gz 
	gzip -dc git-$(GITVERSION).tar.gz | tar xvf -

GitConfig:
	cd git-$(GITVERSION); \
	./configure --prefix=$(EOS_HOME)/util/$(OSTYPE);  

GitAll:
	cd git-$(GITVERSION); \
	make; make install; cd contrib/subtree; make ; make install; cd ../..

GitClean:
	cd git-$(GITVERSION); \
	make clean

GitCleanAll:
	rm -f git-$(GITVERSION).tar.gz; 
	rm -rf git-$(GITVERSION); 
