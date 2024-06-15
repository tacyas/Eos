-include ${EOS_HOME}/src/Config/${EOS_HOST}.inc
include ../../Config/Define.inc
include ../../Config/Target.inc

UTILS= hdf5

PREFIX=$$EOS_HOME/util/$$EOS_HOSTDIR

help::
	@echo "make hdf5" 
	@echo "make pkg-config"
	@echo "make icu" 
	@echo "make cif_api" 
	@echo "make libcif" 

HDF5-VERSION=1.13.0
HDF5-VERSION2=1-13-0
HDF5-VERSION3=1.12.1

PKG-CONFIG-VERSION=0.29.2

target::
	make pkg-config
	make icu
	make hdf5
	make cif_api
	make libcif 

init-pkg-config::
	curl https://pkgconfig.freedesktop.org/releases/pkg-config-$(PKG-CONFIG-VERSION).tar.gz -O

config-pkg-config::
	#tar xvzf pkg-config-$(PKG-CONFIG-VERSION).tar.gz; cd pkg-config-$(PKG-CONFIG-VERSION); ./configure --prefix=$(PREFIX) GLIB_CFLAGS=--with-internal-glib GLIB_LIBS=--with-internal-glib
	tar xvzf pkg-config-$(PKG-CONFIG-VERSION).tar.gz; cd pkg-config-$(PKG-CONFIG-VERSION); ./configure --prefix=$(PREFIX) --with-internal-glib

all-pkg-config::
	cd pkg-config-$(PKG-CONFIG-VERSION); make install


icu:: 
	make init-icu
	make config-icu
	make all-icu
	make clean-icu
	make cleanAll-icu

init-icu::
	git clone https://github.com/unicode-org/icu.git

config-icu::
	cd icu/icu4c/source; ./configure --enable-release --enable-icuio --enable-static --prefix=$(PREFIX)

all-icu::
	cd icu/icu4c/source; make install

clean-icu::
	cd icu/icu4c/source; make clean

cleanAll-icu::
	rm -rf icu

cif_api:: icu
	make -i init-cif_api
	make -i config-cif_api

init-cif_api::
	git clone https://github.com/COMCIFS/cif_api.git

config-cif_api::
	cd cif_api; ./configure --enable-static --enable-shared --prefix=$(PREFIX) ICU_LIBS=$(PREFIX)/lib


hdf5::
	make hdf5Check
	make hdf5Config
	make hdf5All
	make hdf5Clean
	make hdf5CleanAll

hdf5Check::
	if [ ! -f hdf5-$(HDF5-VERSION3).tar.gz ] ; then \
		curl -o hdf5-$(HDF5-VERSION3).tar.gz -L https://www.hdfgroup.org/package/hdf5-$(HDF5-VERSION2)-tar-gz/?wpdmdl=14582&refresh=5f54487ee2f341599359102 ; \
	fi
	tar xvzf hdf5-$(HDF5-VERSION3).tar.gz

hdf5Config::
	cd hdf5-$(HDF5-VERSION3); ./configure --prefix=${EOS_HOME}/util/$(OSTYPE)/

hdf5All::
	cd hdf5-$(HDF5-VERSION3); make; make test; make install

hdf5Clean::
	cd hdf5-$(HDF5-VERSION3); make clean

hdf5CleanAll::
	rm -f hdf5-$(HDF5-VERSION3).tar.gz; rm -rf hdf5-$(HDF5-VERSION3)

libcif: 
	make init-libcif
	make config-libcif
	make all-libcif
	make clean-libcif
	make cleanAll-libcif

init-libcif:
	git clone https://github.com/ElectronicStructureLibrary/libcif.git
