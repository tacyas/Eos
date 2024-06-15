$findsection
64,5	size of patch, number of patches
3,10,4	# pts to average at end & middle, # of points to fit on edge
-176	spacing between sample files
3	number of files
topa.rec
/	sections
	!patches to drop
mida.rec
/	sections
	!patches to drop
bota.rec
/	sections
	!patches to drop
$if (-e ./savework) ./savework
