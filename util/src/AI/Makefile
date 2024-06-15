.SUFFIXES:
.IGNORE:
SHELL=/bin/ksh

include ${EOS_HOME}/src/Config/${EOS_HOST}.inc
 
MLPACKVERSION=1.0.9
MLPACKNAME=mlpack-$(MLPACKVERSION)
MLPACKWHERE=http://www.mlpack.org/files/$(MLPACKNAME).tar.gz

check: checkMLPACK  

config: configMLPACK 

all: MLPACK 

clean: cleanMLPACK 

checkMLPACK:
	curl -O $(MLPACKWHERE)
	tar xvzf $(MLPACKNAME)

configMLPACK:

cleanAll::
	rm -rf :
