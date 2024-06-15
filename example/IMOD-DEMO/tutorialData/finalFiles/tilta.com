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
BBa.ali
BBa.rec
IMAGEBINNED 1
FULLIMAGE 512 512
LOG 0.0
MODE 1
PERPENDICULAR
RADIAL 0.35 0.05
SCALE 1.39 500.0
SUBSETSTART 0 0
THICKNESS 96
TILTFILE BBa.tlt
XAXISTILT 1.83
ZFACTORFILE BBa.zfac
DONE
$if (-e ./savework) ./savework
