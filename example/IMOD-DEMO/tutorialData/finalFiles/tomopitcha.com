# THIS IS A COMMAND FILE TO RUN TOMOPITCH ON ONE MODEL
#
####CreatedVersion#### 3.8.7
#
# YOU SHOULD CREATE THE MODEL WITH:
#     3dmod topa.rec mida.rec bota.rec tomopitcha.mod
#
# If you already have 3 model files instead, make 3 ModelFile entries:
#
# ModelFile topa.mod
# ModelFile mida.mod
# ModelFile bota.mod
#
# YOU MAY WANT TO ADJUST THE THICKNESS TO ADD OUTSIDE YOUR MODEL LINES
#
$tomopitch -StandardInput
#
# Pixels to add to thickness on each side, above and below model lines
ExtraThickness	12.0
SpacingInY	-176.0
ScaleFactor	1.0
AngleOffsetOld	-0.26
ZShiftOld	17.3
XAxisTiltOld	0.0
ModelFile	tomopitcha.mod
$if (-e ./savework) ./savework
