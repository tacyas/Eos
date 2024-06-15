#$if (! -e ) mkdir 
#
# THIS FILE RUNS A SECOND MATCHVOL
# IT IS RUN ONLY IF YOU HAVE TO DO FINDWARP BY HAND, GET A GOOD
# REFINE.XF BY OMITTING ROWS OR COLUMNS, AND HAVE TO RESTART THE PROCESS
#
$matchvol -StandardInput
InputFile       BBb.rec
OutputFile      BBb.mat
#TemporaryDirectory      
# The default output size is NZ, NY, NX
OutputSizeXYZ   512 96 512
TransformFile solve.xf
TransformFile refine.xf
InverseFile inverse.xf
