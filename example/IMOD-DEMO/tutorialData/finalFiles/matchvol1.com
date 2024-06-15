#$if (! -e ) mkdir 
#
$if (-e ./savework) ./savework
#
# THIS DOES THE FIRST RUN OF MATCHVOL TO MAKE AN INITIAL MATCHING VOLUME
#
####CreatedVersion#### 3.4.4
#
$matchvol -StandardInput
InputFile       BBb.rec
OutputFile      BBb.mat
#TemporaryDirectory      
# The default output size is NZ, NY, NX
OutputSizeXYZ	512,96,512
TransformFile solve.xf
# Include this output in case you have to run warpvol instead of matchvol later
InverseFile inverse.xf
# Linear interpolation might be better for first stage and will be faster
InterpolationOrder 1
