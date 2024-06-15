$KCODE = 'UTF-8'
require 'tk_sdl'
require 'pdbFile'
require 'molvie_ver'
require 'keyboard_Func'
require 'mouse_func'
require 'molvieDisplay'
require "opengl"
require "glut"

class GLmolvieFrame

	def frame_create
		#GUIのウィンドウフレームの作成	
		$menuFrame = TkFrame.new { |f|
			#pack('fil'=>'x','side'=>'top')
			#各種メニューボタンの作成
			#”ファイル”ボタンの作成
			TkMenubutton.new(f, 'text'=>'File', 'underline'=>0) {|btn|
				pack('side'=> 'left')
				btn.menu(menu = TkMenu.new(btn, 'tearoff'=>false))
				menu.add('command','label'=>'Open File','command'=>proc{
					PdbFile.new.file_read;
					Molvie_ver.new.molvie_Viewer				
			})
				menu.add('command', 'label'=>'Exit', 'command'=>proc{MolvieRuby::lmolvieKeyboard('q'[0], 0,0)})
			}
			#”モード”ボタンの作成
			TkMenubutton.new(f, 'text'=>'Mode', 'underline'=>0){|btn|
				pack('side'=> 'left')
				btn.menu(menu = TkMenu.new(btn, 'tearoff'=>false))
				menu.add('command','label'=>'molvie_Viewer','command'=>proc{Molvie_ver.new.molvie_Viewer})
				menu.add('command','label'=>'molvie_Projection','command'=>proc{Molvie_ver.new.molvie_Projection})
				menu.add('command','label'=>'molvie_Fly','command'=>proc{Molvie_ver.new.molvie_Flight})
				menu.add('command', 'label'=>'molvie_MrcViewer', 'command'=>proc{Molvie_ver.new.molvie_MrcViewer})
				menu.add('command', 'label'=>'molvie_Dock', 'command'=>proc{Molvie_ver.new.molvie_Dock})
			}
			#”表示”ボタンの作成
			TkMenubutton.new(f, 'text'=>'Representation', 'underline'=>0){|btn|
				pack('side'=> 'left')
				btn.menu(menu = TkMenu.new(btn, 'tearoff'=>false))
				menu.add('command','label'=>'SpaceFill::AtomName','command'=>proc{ MolvieRuby::lmolvieKeyboard('1'[0], 0,0) })
				menu.add('command','label'=>'SpaceFill::ResidueNumber','command'=>proc{ MolvieRuby::lmolvieKeyboard('2'[0], 0,0) })
				menu.add('command','label'=>'SpaceFill::Residues','command'=>proc{ MolvieRuby::lmolvieKeyboard('3'[0], 0,0) })
				menu.add('command','label'=>'SpaceFill::TempFactor','command'=>proc{ MolvieRuby::lmolvieKeyboard('4'[0], 0,0) })
				menu.add('command','label'=>'Backbone::ResidueNumber','command'=>proc{ MolvieRuby::lmolvieKeyboard('5'[0], 0,0) })
				menu.add('command','label'=>'Backbone::Residues','command'=>proc{ MolvieRuby::lmolvieKeyboard('6'[0], 0,0) })
				menu.add('command','label'=>'Backbone::TempFactor','command'=>proc{ MolvieRuby::lmolvieKeyboard('7'[0], 0,0) })
				menu.add('command','label'=>'Wireframe','command'=>proc{ MolvieRuby::lmolvieKeyboard('9'[0], 0, 0) })
			}
			#”表示オプション”ボタンの作成
			TkMenubutton.new(f, 'text'=>'RepresentationOption', 'underline'=>0){|btn|
				pack('side'=> 'left')
				btn.menu(menu = TkMenu.new(btn, 'tearoff'=>false))
				menu.add('command','label'=>'Carbon:visible/hidden','command'=>proc{ MolvieRuby::lmolvieKeyboard('c'[0], 0,0) })
				menu.add('command','label'=>'Oxygen:visible/hidden','command'=>proc{ MolvieRuby::lmolvieKeyboard('o'[0], 0,0) })
				menu.add('command','label'=>'Nytrogen:visible/hidden','command'=>proc{ MolvieRuby::lmolvieKeyboard('n'[0], 0,0) })
				menu.add('command','label'=>'Sulpher:visible/hidden','command'=>proc{ MolvieRuby::lmolvieKeyboard('s'[0], 0,0) })
				menu.add('command','label'=>'Phospher:visible/hidden','command'=>proc{ MolvieRuby::lmolvieKeyboard('p'[0], 0,0) })
				menu.add('command','label'=>'Hydorgen:visible/hidden','command'=>proc{ MolvieRuby::lmolvieKeyboard('h'[0], 0,0) })
				menu.add('command','label'=>'FeETC.:visible/hidden','command'=>proc{ MolvieRuby::lmolvieKeyboard('f'[0], 0,0) })
			}
		}
		$menuFrame.pack('fil'=>'x','side'=>'top')
		#SDL用のTkフレームの作成
		$displayFrame = TkFrame.new(nil, 'container'=>true)
		$displayFrame.pack('fill'=>'both','expand'=>'true')
		frame = $displayFrame

		SDL.init(SDL::INIT_EVERYTHING)			#SDLの初期化
		if(SDL.inited_system(SDL::INIT_EVERYTHING))	
		    puts "Success\n"
		else
	    	puts "Fail\n"
		end
		
		#TkフレームでSDLを機能させる、この際のSDLはOPENGLモード
		SDL.run_on_tk($displayFrame) 
		videoInfo = SDL.video_info;
		if(!videoInfo)
			puts "Video query failed:",SDL::GetError(),"\n"
		end
				
		width = 600
		height =600
		bpp=SDL.checkVideoMode(width,height,32,SDL::OPENGL)
		SDL.set_GL_attr(SDL::GL_DOUBLEBUFFER,1)
		w = SDL::Screen.open(width, height, bpp, SDL::OPENGL)
		GLUT.Init
		
		
		###マウスファンクション###
		frame.bind(
			'Button', 
			proc{|b,f,x,y| MolvieRuby.lmolvieMouse(b-1,0,x,y)},
			"%b %f %x %y")
		frame.bind(
			'ButtonRelease', 
			proc{|b,f,x,y| MolvieRuby.lmolvieMouse(b-1,1,x,y)},
			"%b %f %x %y")
		frame.bind(
			'B1-Motion', 
			proc{|x, y| MolvieRuby.lmolvieMouseMotion(x, y)},
			"%x %y")
		frame.bind(
			'B3-Motion', 
			proc{|x, y| MolvieRuby.lmolvieMouseMotion(x, y)},
			"%x %y")
		
		###キーボードファンクション###
		#frame.bind('Enter',proc {},)
		Tk.root.bind(
			'KeyPress', 
			proc{|a,k,n| MolvieRuby::lmolvieKeyboard(a[0], k, n) },
			"%A %k %N")
	   	## Tkループをスレッド化 	
		tk_thread = Thread.new {
			puts "Tkmainloop Start!\n"
			Tk.mainloop
			puts "Tkmainloop End\n"
		}
		## SDLループをスレッド化 
		sdl_thread = Thread.new {
			puts "SDL-Thread Start !"
			loop {
				puts "SDL-Thread in Loop Start !"
				MolvieDisplay.new.display(width,height);
				puts "SDL-Thread Loop !"		
  			}	
			puts "SDL-Thread End !"
		}		
		tk_thread.join
		sdl_thread.join
	end
end

