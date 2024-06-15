# Command file to run Tilt
#
####CreatedVersion#### 3.6.9
# 
# RADIAL specifies the frequency at which the Gaussian low pass filter begins
#   followed by the standard deviation of the Gaussian roll-off
#
# LOG takes the logarithm of tilt data after adding the given value
#
$tilt
BBb.ali
BBb.rec
IMAGEBINNED 1
FULLIMAGE 512 512
LOG 0.0
MODE 1
PERPENDICULAR
RADIAL 0.35 0.05
SCALE 1.39 500.0
SUBSETSTART 0 0
THICKNESS 96
TILTFILE BBb.tlt
XAXISTILT 0.06
ZFACTORFILE BBb.zfac
DONE
$if (-e ./savework) ./savework
