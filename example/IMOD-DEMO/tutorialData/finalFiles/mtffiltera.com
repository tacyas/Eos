# THIS IS A COM FILE FOR RUNNING MTFFILTER
#
####CreatedVersion#### 3.4.4
#
# THE LOW PASS RADIUS AND SIGMA WILL APPLY A TWO-DIMENSIONAL FILTER TO HIGH
# FREQUENCIES AND CAN BE USED TO REPLACE THE ONE-DIMENSIONAL RADIAL
# FILTER IN TILT
#
# TO TEST ON A SUBSET OF VIEWS, INSERT A LINE WITH
#   StartingAndEndingZ      View1,View2
#
# TO APPLY AN INVERSE MTF FILTER, INSERT A LINE WITH
#   MtfFile       filename.mtf
#
# TO USE THE OUTPUT FOR GENERATING A TOMOGRAM, 
#  RENAME BBa_filt.ali TO BBa.ali
#
$mtffilter -StandardInput
InputFile	BBa.ali
OutputFile	BBa_filt.ali
LowPassRadiusSigma	0.35,0.05
InverseRolloffRadiusSigma	0.12,0.05
MaximumInverse	4.0
#
# INSERT NEW LINES ABOVE HERE
$if (-e ./savework) ./savework
