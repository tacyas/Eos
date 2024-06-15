include ../../Config/Define.inc
include ../../../Config/Define.inc
include ../../../../Config/Define.inc
include ../../../../../Config/Define.inc

all: help exec

help:
	@echo "----- Help Message Check -----"
	@../$(OSTYPE)/$(OBJECTNAME)	 -h

exec:
	@echo "----- Execution Check -----"
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.1.info -m 1 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.17.info -m 17 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.2.info -m 2 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.18.info -m 18 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.4.info -m 4 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.20.info -m 20 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.8.info -m  8 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.24.info -m 24 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.56.info -m 56 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.120.info -m 120
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.7.info  -m 7  -a 80 -nDiv 12 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.23.info -m 23 -a 80 -nDiv 12 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.55.info -m 55 -a 80 -nDiv 12 
	../$(OSTYPE)/$(OBJECTNAME) -i data/FlagellaSection.fft -o data/FlagellaSection.119.info -m 119 -a 80 -nDiv 12 
	@echo "----- Calc check -----"		

clean:
