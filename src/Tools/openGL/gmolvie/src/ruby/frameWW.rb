require 'tk_sdl'
require 'molvie'

TkFrame.new{|f|
pack('fil'=>'x','side'=>'top')
TkMenubutton.new(f, 'text'=>'File', 'underline'=>0){|btn|
pack('side'=> 'left')
btn.menu(menu = TkMenu.new(btn, 'tearoff'=>false))
menu.add('command','label'=>'FileOpen','command'=>proc{open_file})
#menu.add('separator')
#menu.add('command','label'=>'FileSave','command'=>proc{save_file})
#menu.add('command','label'=>'FileSaveAs','command'=>proc{save_as})
#menu.add('separator')
menu.add('command', 'label'=>'Exit', 'command'=>proc{exit})
}
TkMenubutton.new(f, 'text'=>'molvieVer', 'underline'=>0){|btn|
pack('side'=> 'left')
btn.menu(menu = TkMenu.new(btn, 'tearoff'=>false))
menu.add('command','label'=>'FileOpen','command'=>proc{open_file})
#menu.add('separator')
#menu.add('command','label'=>'FileSave','command'=>proc{save_file})
#menu.add('command','label'=>'FileSaveAs','command'=>proc{save_as})
#menu.add('separator')
menu.add('command', 'label'=>'Exit', 'command'=>proc{exit})
}
}

frame = SDL.run_on_tk.pack
frame.bind('Button-1',proc{|x,y| print"clicked at(#{x},#{y}!!)\n"},'%x %y')

Thread.new{Tk.mainloop}

load 'rubySDL.rb'
#SDL::Screen.update_rect(0,0,0,0)
