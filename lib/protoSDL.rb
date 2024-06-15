#!/usr/bin/ruby

require 'sdl'
#require "opengl"
require "rubygems"
require "opengl"
require "glut"
require 'molvie_ver'
require 'molvie_ver'
require 'keyboard_Func'
require 'Event'

vertices = [
  [[1.0, 0.0, 0.0], [-1.0, -1.0, 0.0]],
  [[0.0, 1.0, 0.0], [ 1.0, -1.0, 0.0]],
  [[0.0, 0.0, 1.0], [ 1.0,  1.0, 0.0]],
  [[1.0, 1.0, 1.0], [-1.0,  1.0, 0.0]]
]

#SDL.init(SDL::INIT_VIDEO)
#if(SDL.inited_system(SDL::INIT_VIDEO))
#	puts "初期化されています。nnnn"
#else
#	puts "初期化されていません。"
#end
#SDL.set_GL_attr(SDL::GL_DOUBLEBUFFER,1)
#SDL::Screen.open(600, 600, 16, SDL::OPENGL)
#GLUT.init
GL.ClearColor(0.0, 0.0, 0.2, 1.0);
GL::Ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0)
GL::MatrixMode(GL::MODELVIEW);

loop { 
	Event.new.lmolvie_keyboard($push_key,$x,$y)
	Event.new.pushedKey_is_molvieVer($push_key,$molvie_ver)
	# Molvie_ver.new.put_molviemode
	# puts ($molvie_ver,"nya")
	# puts ($push_key,"nyanyan")

	#puts Molvie_ver.new.molvie_ver
	   GL.Clear(GL::COLOR_BUFFER_BIT);
	  # GL::Rotate(1.0, 2.0, 3.0, 1.0);
	   GL::Begin(GL::QUADS);
	   vertices.each {|v|
	     GL::Color(v[0]);
	     GL::Vertex(v[1]);	
	    }     
	GL::End()  
	SDL::GL_swap_buffers()
}

#SDL::GL_swap_buffers
