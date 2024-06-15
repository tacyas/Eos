.SUFFIXES: .bmp .tif .mrc

all: 
	FILES=`ls -1 *.bmp | sed -e s/bmp/mrc/`; \
	echo $$FILES; \
	for i in $$FILES; \
	do \
		make $$i; \
	done

.bmp.mrc:
	bmp2mrc -i $*.bmp -o $*.mrc
