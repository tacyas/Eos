#$if (! -e ) mkdir 
#
# THIS FILE RUNS WARPVOL 
#
# IT IS RUN ONLY IF YOU HAVE TO DO FINDWARP BY HAND AND
# RESTART THE PROCESS
#
$warpvol -StandardInput
InputFile       BBb.rec
OutputFile      BBb.mat
#TemporaryDirectory      
# The default output size is NZ, NY, NX
OutputSizeXYZ   512 96 512
TransformFile warp.xf
