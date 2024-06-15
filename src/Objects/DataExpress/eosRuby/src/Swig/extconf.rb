require 'mkmf'

dir_config('Eos');
dir_config('EosUtil');
dir_config('GL');
if	have_library('GL') \
	and have_library('GLU') \
	and have_library('glut') \
	and have_library('tcl') \
	and have_library('tk') \
	and have_library('BLT') \
	and have_library('asound') \
	and have_library('gif') \
	and have_library('fftw3f') \
	and have_library('nr') \
	and have_library('nl') \
	and have_library('nsl') \
	and have_library('EosObjects')

	create_makefile("molvieRuby")
end
