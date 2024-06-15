require "sdl"
require "rubygems"
require "opengl"
require "glut"
#require 'molvieRuby'
require 'pdbFile'

class Molvie
	def start(info)
		GLUT.Init;
  		GLUT.InitDisplayMode(GLUT::GLUT_DOUBLE | GLUT::GLUT_RGB | GLUT::GLUT_DEPTH);
  		MolvieRuby::lmolvieTest;
	end
end
#	DEBUGPRINT("Program Start\n");

#	exit(EXIT_SUCCESS);

#	return 0;
