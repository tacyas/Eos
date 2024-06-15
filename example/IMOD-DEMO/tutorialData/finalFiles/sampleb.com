# THIS IS A COMMAND FILE TO MAKE 3 TOMOGRAM SAMPLES
#
####CreatedVersion#### 3.8.25
# 
# The sample aligned stacks will each be 60 pixels in Y
# The sample tomograms will have 10 slices
# To get more slices in the samples, change "sampletilt 25 34" by
# decreasing 25 and increasing 34 by equal amounts, up to 0 and 59
#
# THESE ARE COMMANDS TO MAKE AN ALIGNED STACK FROM THE ORIGINAL STACK
#
####CreatedVersion#### 3.4.4
#
# It assumes that the views are in order in the image stack
#  
# The -size argument should be ,, for the full area or specify the desired 
# size (e.g.: ,10)
#
# The -offset argument should be 0,0 for no offset, 0,300 to take an area
# 300 pixels above the center, etc.
#
$newstack -size ,60 -offset 0,0 -xf BBb.xf BBb.st BBb.ali
$sampletilt 25 34 226 BBb midb.rec tiltb.com
# THESE ARE COMMANDS TO MAKE AN ALIGNED STACK FROM THE ORIGINAL STACK
#
####CreatedVersion#### 3.4.4
#
# It assumes that the views are in order in the image stack
#  
# The -size argument should be ,, for the full area or specify the desired 
# size (e.g.: ,10)
#
# The -offset argument should be 0,0 for no offset, 0,300 to take an area
# 300 pixels above the center, etc.
#
$newstack -size ,60 -offset 0,176 -xf BBb.xf BBb.st BBb.ali
$sampletilt 25 34 402 BBb topb.rec tiltb.com
# THESE ARE COMMANDS TO MAKE AN ALIGNED STACK FROM THE ORIGINAL STACK
#
####CreatedVersion#### 3.4.4
#
# It assumes that the views are in order in the image stack
#  
# The -size argument should be ,, for the full area or specify the desired 
# size (e.g.: ,10)
#
# The -offset argument should be 0,0 for no offset, 0,300 to take an area
# 300 pixels above the center, etc.
#
$newstack -size ,60 -offset 0,-176 -xf BBb.xf BBb.st BBb.ali
$sampletilt 25 34 50 BBb botb.rec tiltb.com
$if (-e ./savework) ./savework
