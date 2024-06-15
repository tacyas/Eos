# THIS IS A COMMAND FILE TO RUN TOMOPITCH ON ONE MODEL
#
####CreatedVersion#### 3.8.7
#
# YOU SHOULD CREATE THE MODEL WITH:
#     3dmod topb.rec midb.rec botb.rec tomopitchb.mod
#
# If you already have 3 model files instead, make 3 ModelFile entries:
#
# ModelFile topb.mod
# ModelFile midb.mod
# ModelFile botb.mod
#
# YOU MAY WANT TO ADJUST THE THICKNESS TO ADD OUTSIDE YOUR MODEL LINES
#
$tomopitch -StandardInput
#
# Pixels to add to thickness on each side, above and below model lines
ExtraThickness	12.0
SpacingInY	-176.0
ScaleFactor	1.0
AngleOffsetOld	-2.12
ZShiftOld	0.0
XAxisTiltOld	0.0
ModelFile	tomopitchb.mod
$if (-e ./savework) ./savework
