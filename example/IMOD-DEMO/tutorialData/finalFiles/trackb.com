# Command file for running BEADTRACK
#
####CreatedVersion#### 3.6.4
#
# For beads lighter than background, add a line with "LightBeads"
#
# To restrict tilt alignment to a subset of views, add a line with:
# "MaxViewsInAlign #_of_views"
#
# To exclude views, add a line "SkipViews view_list" with the list of views
#
# To specify sets of views to be grouped separately in automapping, add a line
# "SeparateGroup view_list" with the list of views, one line per group
#
$beadtrack -StandardInput
ImageFile	BBb.preali
InputSeedModel	BBb.seed
OutputModel	BBb.fid
RotationAngle	-12.5
TiltFile	BBb.rawtlt
TiltDefaultGrouping	7
MagDefaultGrouping	5
RotDefaultGrouping	1
CentroidRadius	3.98
FillGaps	
MaxGapSize	5
RoundsOfTracking	2
#
# Set this to 1 to track in local areas
LocalAreaTracking	0
LocalAreaTargetSize	1000
MinBeadsInArea	8
MinOverlapBeads	5
#
# CONTROL PARAMETERS FOR EXPERTS, EXPERIMENTATION, OR SPECIAL CASES
#
# minimum range of tilt angles for finding axis and for finding tilts
MinViewsForTiltalign	4
MinTiltRangeToFindAxis	10.0
MinTiltRangeToFindAngles	20.0
BoxSizeXandY	32,32
MaxBeadsToAverage	4
# points and minimum for extrapolation
PointsToFitMaxAndMin	7,3
# fraction of mean, and # of SD below mean: density criterion for rescue
DensityRescueFractionAndSD	0.6,1.0
# distance criterion for rescue
DistanceRescueCriterion	10.0
# relaxation of criterion for density and distance rescues
RescueRelaxationDensityAndDistance	0.7,0.9
# distance for rescue after fit
PostFitRescueResidual	2.5
# relaxation of density criterion, maximum radius to search
DensityRelaxationPostFit	0.9
MaxRescueDistance	2.5
# Max and min residual changes to use to get mean and SD change
ResidualsToAnalyzeMaxAndMin	9,5
# minimum residual difference, criterion # of sd's
DeletionCriterionMinAndSD	0.04,2.0
$if (-e ./savework) ./savework
