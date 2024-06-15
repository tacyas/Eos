# CTF Compensation

.SUFFIXES: .tif .mrc .prectf .fft .ctfinfo .ctf

CCD=14.0


.tif.mrc:
	echo "Mag:"; read Mag; RESO=`echo ""| awk -v M=$$Mag 'BEGIN { print $(CCD)/M*10; }'`; \
	echo "Resolution: $$RESOLUTION";  \
	tiff2mrc -i $*.tif -o $*.mrc  -r $$RESOLUTION 

.mrc.prectf:

.prectf.fft:
	mrcImageFFT -i $*.mrc -o $*.fft

.fft.ctfinfo:
	ctfDisplay -i $*.fft -o $*.ctfinfo

.ctfinfo.ctf:
	mrcImageCTFCompensation -i $*.fft -o $*.ctf -info2 $*.ctfinfo -m 1
