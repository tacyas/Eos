# THIS FILE RUNS CORRSEARCH3D
#
####CreatedVersion#### 3.8.25
#
# TO SPECIFY A MODEL FILE WITH CONTOURS ENCLOSING THE PATCHES TO ANALYZE,
# ADD A LINE WITH "RegionModel   filename"
#
# TO APPLY A SMOOTHING FILTER ADD A LINE WITH "KernelSmooth   sigma"
#
# REMEMBER THAT Y IS THICKNESS HERE
#
$corrsearch3d -StandardInput
ReferenceFile   BBa.rec
FileToAlign     BBb.mat
OutputFile      patch.out
PatchSizeXYZ	64,32,64
NumberOfPatchesXYZ	5,2,5
XMinAndMax	24,488
YMinAndMax	23,76
ZMinAndMax	24,488
BSourceOrSizeXYZ        BBb.rec
BSourceTransform        solve.xf
BSourceBorderXLoHi	24,24
BSourceBorderYZLoHi	24,24
FlipYZMessages
#
# Make a patch vector model
$patch2imod -n "Values are correlation coefficients" patch.out patch_vector_ccc.mod
$if (-e savework-file) savework-file
