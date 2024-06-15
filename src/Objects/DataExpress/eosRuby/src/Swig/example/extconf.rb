require 'mkmf'
if have_library("Eos") 
	create_makefile("libEosRuby")
end

