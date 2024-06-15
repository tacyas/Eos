require 'tk_sdl'
#require 'molvie'
require 'PdbFile'
require 'protoSDL'

class Frame
	def initialize
		event = nil
		@event = event
		key = nil
		@key
	end	
	
	def event_num
		return @event
	end
	
	def event_key
		return @key
	end
end

#Frame.frame_create.new

	TkFrame.new{|f|
		pack('fil'=>'x','side'=>'top')
		TkMenubutton.new(f, 'text'=>'molvie', 'underline'=>0){|btn|
			pack('side'=> 'left')
			btn.menu(menu = TkMenu.new(btn, 'tearoff'=>false))
			menu.add('command','label'=>'ファイルを開く','command'=>proc{PdbFile.new.file_read})
			#menu.add('separator')
			#menu.add('command','label'=>'保存','command'=>proc{save_file})
			#menu.add('command','label'=>'別名で保存','command'=>proc{save_as})
			#menu.add('separator')
			menu.add('command', 'label'=>'人間をやめる', 'command'=>proc{exit})
			}
		TkMenubutton.new(f, 'text'=>'molvieVer', 'underline'=>0){|btn|
			pack('side'=> 'left','expand'=>true)
			btn.menu(menu = TkMenu.new(btn, 'tearoff'=>false))
			#menu.add('command','label'=>'ファイルを開く','command'=>proc{open_file})
			#menu.add('separator')
			#menu.add('command','label'=>'保存','command'=>proc{save_file})
			#menu.add('command','label'=>'別名で保存','command'=>proc{save_as})
			#menu.add('separator')
			menu.add('command', 'label'=>'人間をやめる', 'command'=>proc{exit})
			}
		}
	
		frame = SDL.run_on_tk.pack
		#height = TkWinfo.height(frameWW.rb)
		#wigth = TkWinfo.width(frameWW.rb)
		#depth = TkWinfo.depth(frameWW.rb)
		#print"#{height}\n"
	

		frame.bind('Button-1',proc{|x,y| print"clicked at(#{x},#{y}!!)\n"},'%x %y')
		#frame.bind('Button-1',proc{Thread.stop})
		#SDL.setVideoMode_resize()
		
		#event
		#frame.bind ('Button-1', proc { print "Click!\n" })
		#frame.bind ('Double-1', proc { print "Click!\n" })
		 
		tk_thread = Thread.new{Tk.mainloop}
		#Thread.pass
		#sdl_thread= Thread.new{load 'molvie.rb'}# => #<Thread:0xa039de0 join>
		ProtoSDL.new.sdl_start
		#tk_thread.stop
