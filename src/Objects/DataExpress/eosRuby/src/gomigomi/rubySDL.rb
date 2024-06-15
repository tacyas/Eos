#!/usr/bin/ruby

require 'sdl'
#require "opengl"
require "rubygems"
require "opengl"
require "glut"
require 'tk_sdl'
require 'molvie_ver'

vertices = [
  [[1.0, 0.0, 0.0], [-1.0, -1.0, 0.0]],
  [[0.0, 1.0, 0.0], [ 1.0, -1.0, 0.0]],
  [[0.0, 0.0, 1.0], [ 1.0,  1.0, 0.0]],
  [[1.0, 1.0, 1.0], [-1.0,  1.0, 0.0]]
]

SDL.init(SDL::INIT_VIDEO)
if(SDL.inited_system(SDL::INIT_VIDEO))
puts "初期化されています。nnnn"
else
puts "初期化されていません。"
end
#SDL.set_GL_attr(SDL::GL_DOUBLEBUFFER,1)
SDL::Screen.open(600, 600, 16, SDL::OPENGL)

GL.ClearColor(0.0, 0.0, 0.2, 1.0);
GL::Ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0)
GL::MatrixMode(GL::MODELVIEW);

#next_frame=SDL::get_ticks()
#wait = 1000 / 60
#t=0
#event = SDL::Event2.new
loop { 
   GL.Clear(GL::COLOR_BUFFER_BIT);
   GL::Rotate(1.0, 2.0, 3.0, 1.0);
   GL::Begin(GL::QUADS);
   vertices.each {|v|
     GL::Color(v[0]);
     GL::Vertex(v[1]);	
    }     
  GL::End()  
  SDL::GL_swap_buffers()
 evt = SDL::Event2.poll
 puts SDL::Key::F5

}

#SDL::GL_swap_buffers
