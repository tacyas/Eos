# THIS FILE DOES EVERYTHING FOR COMBINING VOLUMES
#
####CreatedVersion#### 3.8.26
#
# CHANGE THIS VALUE TO SET ReductionFactor NONZERO IN COMBINEFFT
#
$set combinefft_reduce = 0.0
#
# CHANGE THIS VALUE TO SET LowFromBothRadius NONZERO IN COMBINEFFT
#
$set combinefft_lowboth = 0.0
#
$setenv IMOD_BRIEF_HEADER 1
#
# TO RESTART AT A PARTICULAR PIECE, CHANGE 0 IN THE FOLLOWING "goto dopiece0"
# TO THE DESIRED PIECE NUMBER
#
$goto dopiece0
#
$dopiece0:
#
$if (-e ./savework) ./savework
#
$echo "STATUS: RUNNING DENSMATCH TO MATCH DENSITIES"
$echo
#
# Scale the densities in the match file to match the first tomogram.  Inputs:
#     File being matched (first tomogram)
#     File to be scaled (the second tomogram)
#     BLANK LINE TO HAVE SCALED VALUES PUT BACK IN THE SAME FILE
#
$densmatch
BBa.rec
BBb.mat

#
#
# purge some previous versions if necessary: these are the huge files
#
$touch prevent-error
$\rm prevent-err* *.mat~ mat.fft* rec.fft* sum.fft* sum.rec* sum[1-9]*.rec*
#
$echo STATUS: RUNNING FILLTOMO TO FILL IN GRAY AREAS IN THE .MAT FILE
$echo
#
$filltomo
BBb.mat
BBa.rec
BBb.rec
inverse.xf
/
#
$dopiece1:
$echo STATUS: EXTRACTING AND COMBINING PIECE 1 of 2
$echo
#
$taperoutvol
BBa.rec
rec.st
0,511,0,95,0,260
8,4,8
$fftrans -q -3d rec.st rec.fft
$\rm rec.st
$taperoutvol
BBb.mat
mat.st
0,511,0,95,0,260
8,4,8
$fftrans -q -3d mat.st mat.fft
$\rm mat.st
$combinefft -StandardInput
AInputFFT	rec.fft
BInputFFT	mat.fft
InverseTransformFile	inverse.xf
ATiltFile	BBa.tlt
BTiltFile	BBb.tlt
ReductionFraction	$combinefft_reduce
LowFromBothRadius	$combinefft_lowboth
$\rm rec.fft
$fftrans -q -3d -m 1 mat.fft sum1.rec
$\rm mat.fft
#
$dopiece2:
$echo STATUS: EXTRACTING AND COMBINING PIECE 2 of 2
$echo
#
$taperoutvol
BBa.rec
rec.st
0,511,0,95,251,511
8,4,8
$fftrans -q -3d rec.st rec.fft
$\rm rec.st
$taperoutvol
BBb.mat
mat.st
0,511,0,95,251,511
8,4,8
$fftrans -q -3d mat.st mat.fft
$\rm mat.st
$combinefft -StandardInput
AInputFFT	rec.fft
BInputFFT	mat.fft
InverseTransformFile	inverse.xf
ATiltFile	BBa.tlt
BTiltFile	BBb.tlt
ReductionFraction	$combinefft_reduce
LowFromBothRadius	$combinefft_lowboth
$\rm rec.fft
$fftrans -q -3d -m 1 mat.fft sum2.rec
$\rm mat.fft
#
$echo STATUS: REASSEMBLING PIECES
$echo
#
$assemblevol
sum.rec
1,1,2
8,519
4,99
9,264
14,269
sum1.rec
sum2.rec
#
$echo
$echo STATUS: RUNNING FILLTOMO ON FINAL VOLUME
$echo
#
$\rm sum[1-9]*.rec
$filltomo
sum.rec
BBa.rec
BBb.rec
inverse.xf
/
$if (-e ./savework) ./savework
