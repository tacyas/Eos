# THIS COMMAND FILE RUNS SOLVEMATCH
#
####CreatedVersion#### 3.8.23
#
# It contains all of the entries needed for the three different modes of
# operation: fiducials only, fiducials and matching models (obsolete), and
# matching models only.
#
$solvematch -StandardInput
AFiducialFile	BBafid.xyz
BFiducialFile	BBbfid.xyz
#
# Uncomment and insert name to use coordinate file from transferfid, makes
# the correspondence lists irrelevant
#
TransferCoordinateFile	transferfid.coord
XAxisTilts	1.83,0.06
AngleOffsetsToTilt	0.,0.
ZShiftsToTilt	0,0
SurfacesOrUseModels	2
AMatchingModel	BBa.matmod
BMatchingModel	BBb.matmod
AFiducialModel	BBa.fid
BFiducialModel	BBb.fid
ATomogramOrSizeXYZ	BBa.rec
BTomogramOrSizeXYZ	BBb.rec
OutputFile	solvezero.xf
MaximumResidual	8.0
LocalFitting	10
CenterShiftLimit	10.0
#
$echo "STATUS: SOLVEMATCH RAN SUCCESSFULLY, NEXT RUNNING MATCHSHIFTS"
#
# Run matchshifts.  If solvezero.xf has shifts, it will just be copied to 
# solve.xf.  Otherwise, if the coordinates in the fiducial lists were not
# absolute, it will get the absolute shifts; the three numbers are the nx, ny,
# and nz of the block used for 3-D cross-correlation.
#
$matchshifts BBa BBb 100 40 100
