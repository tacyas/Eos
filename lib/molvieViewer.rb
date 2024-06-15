#!/usr/bin/ruby
require './Swig/molvieRuby'
require 'rubygems'
require 'opengl'
require 'glut'


class MolvieViewer

def Fileread(fname)
molvieInfo info
molvieInfo.In = fname
info.fptIn = MolvieRuby.fopen(info.In,'r')
	if molvieInfo.fptIn == ""
	put('file read error:'+ info.In)
	end
MolvieRuby.lmolviePDBread(info.fptIn);
end

GLUT.Init()
GLUT.InitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH)
GLUT.InitWindowSize(WIN_WIDTH, WIN_HEIGHT)
GLUT.InitWindowPosition(WIN_POSX, WIN_POSY); 
GLUT.CreateWindow(WIN_NAME)

MolvieRuby.LmoolvieInit()

GLUT.IdleFunc(MolvieRuby.lmolvieViewerIdle)
GLUT.KeyboardFunc(MolvieRuby.lmolvieViewerKeyboard)
GLUT.SpecialFunc(MolvieRuby.lmolvieViewerSpecial)
GLUT.MouseFunc(MolvieRuby.lmolvieViewerMouse)
GLUT.MotionFunc(MolvieRuby.lmolvieViewerMouseMotion);
GLUT.PassiveMotionFunc(MolvieRuby.lmolvieViewerMousePassiveMotion);
GLUT.DisplayFunc(MolvieRuby.lmolvieViewerDisplay)
GLUT.ReshapeFunc(MolvieRuby.lmolvieReshapeNormal);
GLUT.MainLoop()

end
