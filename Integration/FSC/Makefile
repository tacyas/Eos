.SUFFIXES: .3dlst .3dFSC
NSEED=0

.3dlst.3dFSC:
	awk 'BEGIN {srand($(NSEED))} { printf("%10.7f %s\n", rand(), $$0); }' $*.3dlst \
			| sort \　
			| awk '{ printf("%s %s %15.6f %15.6f %15.6f %15.6f\n", $$2,$$3,$$4,$$5,$$6,$$7)}' \
			> $*.3dlst.sort
	N1=`wc -l $*.3dlst.sort | awk '{print     int($$1/2)}'`; echo $$N1; \
	N2=`wc -l $*.3dlst.sort | awk '{print $$1-int($$1/2)}'`; echo $$N2; \
	head -n $$N1 $*.3dlst.sort > $*.1.3dlst; \
	tail -n $$N2 $*.3dlst.sort > $*.2.3dlst
	printf "%s\n%s\n" $*.1.3d $*.2.3d | xargs -L 1 -P 2 make 
	mrcImageFourierShellCorrelation -i1 $*.1.3d -i2 $*.2.3d -d $(DelR) > $*.3dFSC

.3d.3dFNC:
	mrcImageLowPassFiltering -i $*.3d -o $*.3dsmooth -hvp 0.05 -m 4
	mrcImageBinalization -i $*.3dsmooth -o $*.mask -m 32
	mrcImageNullImage -o $*.maskback -Nx 80 -Ny 80 -Nz 80 -d 2.0 -v 1
	mrcImageFourierNeighborCorrelation -i $*.3d -o $*.3dFNC -FSC -mask $*.mask -maskBack $*.maskback
