# THIS IS A COMMAND FILE TO RUN TILTALIGN
#
####CreatedVersion#### 3.6.4
#
# To exclude views, add a line "ExcludeList view_list" with the list of views
#
# To specify sets of views to be grouped separately in automapping, add a line
# "SeparateGroup view_list" with the list of views, one line per group
#
$tiltalign -StandardInput
ModelFile	BBb.fid
ImageFile	BBb.preali
#ImageSizeXandY	512,512
ImagesAreBinned	1
OutputModelFile	BBb.3dmod
OutputResidualFile	BBb.resid
OutputFidXYZFile	BBbfid.xyz
OutputTiltFile	BBb.tlt
OutputTransformFile	BBb.tltxf
RotationAngle	-12.5
TiltFile	BBb.rawtlt
#
# ADD a recommended tilt angle change to the existing AngleOffset value
#
AngleOffset	-2.11
RotOption	1
RotDefaultGrouping	5
#
# TiltOption 0 fixes tilts, 2 solves for all tilt angles; change to 5 to solve
# for fewer tilts by grouping views by the amount in TiltDefaultGrouping
#
TiltOption	5
TiltDefaultGrouping	5
MagReferenceView	1
MagOption	1
MagDefaultGrouping	4
#
# To solve for distortion, change both XStretchOption and SkewOption to 3;
# to solve for skew only leave XStretchOption at 0
#
XStretchOption	3
SkewOption	3
XStretchDefaultGrouping	7
SkewDefaultGrouping	11
# 
# Criterion # of S.D's above mean residual to report (- for local mean)
#
ResidualReportCriterion	3.0
SurfacesToAnalyze	2
MetroFactor	0.25
MaximumCycles	1000
#
# ADD a recommended amount to shift up to the existing AxisZShift value
#
AxisZShift	18.7
#
# Set to 1 to do local alignments
#
LocalAlignments	0
OutputLocalFile	BBblocal.xf
#
# Number of local patches to solve for in X and Y
#
NumberOfLocalPatchesXandY	5,5
MinSizeOrOverlapXandY	0.5,0.5
#
# Minimum fiducials total and on one surface if two surfaces
#
MinFidsTotalAndEachSurface	8,3
FixXYZCoordinates	1
LocalOutputOptions	1,0,1
LocalRotOption	3
LocalRotDefaultGrouping	6
LocalTiltOption	5
LocalTiltDefaultGrouping	6
LocalMagReferenceView	1
LocalMagOption	3
LocalMagDefaultGrouping	7
LocalXStretchOption	3
LocalXStretchDefaultGrouping	7
LocalSkewOption	3
LocalSkewDefaultGrouping	11
OutputZFactorFile	BBb.zfac
#
# COMBINE TILT TRANSFORMS WITH PREALIGNMENT TRANSFORMS
#
$xfproduct -StandardInput
InputFile1	BBb.prexg
InputFile2	BBb.tltxf
OutputFile	BBb_fid.xf
$\cp BBb_fid.xf BBb.xf
$\cp BBb.tlt BBb_fid.tlt
#
# CONVERT RESIDUAL FILE TO MODEL
#
$if (-e BBb.resid) patch2imod -s 10 BBb.resid BBb.resmod
$if (-e ./savework) ./savework
