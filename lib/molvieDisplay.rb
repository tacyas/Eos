#!/usr/bin/ruby

require 'sdl'
#require "opengl"
require "rubygems"
require "opengl"
require "glut"
require 'molvie_ver'
require 'keyboard_Func'
require 'pdbFile'
require 'molvieRuby'

class MolvieDisplay 
	
	def display(width,height)
			#puts "display"
		case Molvie_ver.new.molvie_ver
			
			#molvieViewer
			when 0
				puts "display_mode molvieViewer"
				MolvieRuby::lmolvieInitNormal();
				MolvieRuby::lmolvieDisplayNormal();
				SDL::GL_swap_buffers()
				MolvieRuby::lmolvieReshapeNormal(width ,height);
				
			#molvieFlight
			when 1
				#if ((flag == 0 || 1 )
				MolvieRuby::operationModeSet(1)
				puts "display_mode molvieFlight"	
				MolvieRuby::lmolvieInitNormal();
				MolvieRuby::lmolvieDisplayNormal();
				puts "Into setDriveMyCamera() こいつのせいで消えるみたい。"
				#MolvieRuby::setDriveMyCamera();
				#puts "Into setCameraCentreTag"
				#MolvieRuby::setCameraCentreTag(0);
				puts "Into lmolvieFlightDisplay"
				#MolvieRuby::lmolvieFlightDisplay;
				puts "Into SDL::GL_swap_buffers()"
				SDL::GL_swap_buffers()
				puts "Into lmolvieReshapeNormal"
				MolvieRuby::lmolvieReshapeNormal(width ,height);
			
			#molvieProjection
			when 2
				puts "display_mode molvieProjection"
				MolvieRuby::lmolvieInitParallel();
				#puts "display_Func2: Into lmolvieDisplaySDLNormal()"
				MolvieRuby::lmolvieViewerParallel();
				#puts "display_Func3: SDL::GL_swap_buffers!します"
				SDL::GL_swap_buffers()
				#puts "display_Func4:Into lmolvieReshapeNormal() "
				MolvieRuby::lmolvieReshapeParallel(width ,height);
				#parallelwindow設定作るか検討中				
				#puts "display_Func_End"
			when 3
				#puts "display_Func1: Into lmolvieInitNormal()"
				MolvieRuby::lmolvieInitNormal();
				#puts "display_Func2: Into lmolvieDisplaySDLNormal()"
				MolvieRuby::lmolvieDisplayNormal();
				#puts "display_Func3: SDL::GL_swap_buffers!します"
				SDL::GL_swap_buffers()
				#puts "display_Func4:Into lmolvieReshapeNormal() "
				MolvieRuby::lmolvieReshapeNormal(width ,height);
				#puts "display_Func_End"
			when 4
				#puts "display_Func1: Into lmolvieInitNormal()"
				MolvieRuby::lmolvieInitNormal();
				#puts "display_Func2: Into lmolvieDisplaySDLNormal()"
				MolvieRuby::lmolvieDisplayNormal();
				#puts "display_Func3: SDL::GL_swap_buffers!します"
				SDL::GL_swap_buffers()
				#puts "display_Func4:Into lmolvieReshapeNormal() "
				MolvieRuby::lmolvieReshapeNormal(width ,height);
				#puts "display_Func_End"
			when 5
				#puts "display_Func1: Into lmolvieInitNormal()"
				MolvieRuby::lmolvieInitNormal();
				#puts "display_Func2: Into lmolvieDisplaySDLNormal()"
				MolvieRuby::lmolvieDisplayNormal();
				#puts "display_Func3: SDL::GL_swap_buffers!します"
				SDL::GL_swap_buffers()
				#puts "display_Func4:Into lmolvieReshapeNormal() "
				MolvieRuby::lmolvieReshapeNormal(width ,height);
				#puts "display_Func_End"
			
			else
				MolvieRuby::lmolvieInitNormal();
				GL::Clear(GL::COLOR_BUFFER_BIT)
				#puts "display default2"
				GL::Begin(GL::LINE_LOOP);
				#puts "display default3"
				#GL::Color3d(1.0,0.0,0.0)
				GL::Vertex2d(-0.9, -0.9);
				GL::Vertex2d(0.9, -0.9);
				GL::Vertex2d(0.9, 0.9);
				GL::Vertex2d(-0.9, 0.9);
	  			GL::End()
	  			#puts "display default4"
	 		 	GLUT::SolidTeapot(0.4);
	  			SDL::GL_swap_buffers()
	  			#puts "display default5"
	  			GL.ShadeModel(GL::SMOOTH)
			end
		SDL::GL_swap_buffers()
	end
end
	
