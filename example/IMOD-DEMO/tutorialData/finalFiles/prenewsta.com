# THIS IS A COMMAND FILE TO PRODUCE A PRE-ALIGNED STACK
# 
# The stack will be floated and converted to bytes under the assumption that
# you will go back to the raw stack to make the final aligned stack
#
$xftoxg
# global fit
0
BBa.prexf
BBa.prexg
$newstack -input BBa.st -output BBa.preali -mo 0 -xform BBa.prexg -fl 2
$if (-e ./savework) ./savework
